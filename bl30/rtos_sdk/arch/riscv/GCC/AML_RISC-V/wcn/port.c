/*
 * FreeRTOS Kernel V10.5.1
 * Copyright (C) 2021 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */

/*
 * Copyright (c) 2021-2022 Amlogic, Inc. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

/*-----------------------------------------------------------
 * Implementation of functions defined in portable.h for the RISC-V port.
 *----------------------------------------------------------*/

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "portmacro.h"

/* Standard includes. */
#include "string.h"

/* Chip hardware includes. */
#include "riscv_encoding.h"
#include "interrupt_control_eclic.h"

#ifdef configCLINT_BASE_ADDRESS
    #warning The configCLINT_BASE_ADDRESS constant has been deprecated.  configMTIME_BASE_ADDRESS and configMTIMECMP_BASE_ADDRESS are currently being derived from the (possibly 0) configCLINT_BASE_ADDRESS setting.  Please update to define configMTIME_BASE_ADDRESS and configMTIMECMP_BASE_ADDRESS directly in place of configCLINT_BASE_ADDRESS.  See https://www.FreeRTOS.org/Using-FreeRTOS-on-RISC-V.html
#endif

#ifndef configMTIME_BASE_ADDRESS
    #warning configMTIME_BASE_ADDRESS must be defined in FreeRTOSConfig.h.  If the target chip includes a memory-mapped mtime register then set configMTIME_BASE_ADDRESS to the mapped address.  Otherwise set configMTIME_BASE_ADDRESS to 0.  See https://www.FreeRTOS.org/Using-FreeRTOS-on-RISC-V.html
#endif

#ifndef configMTIMECMP_BASE_ADDRESS
    #warning configMTIMECMP_BASE_ADDRESS must be defined in FreeRTOSConfig.h.  If the target chip includes a memory-mapped mtimecmp register then set configMTIMECMP_BASE_ADDRESS to the mapped address.  Otherwise set configMTIMECMP_BASE_ADDRESS to 0.  See https://www.FreeRTOS.org/Using-FreeRTOS-on-RISC-V.html
#endif

/* Let the user override the pre-loading of the initial RA. */
#ifdef configTASK_RETURN_ADDRESS
    #define portTASK_RETURN_ADDRESS    configTASK_RETURN_ADDRESS
#else
    #define portTASK_RETURN_ADDRESS    0
#endif

/* The stack used by interrupt service routines.  Set configISR_STACK_SIZE_WORDS
 * to use a statically allocated array as the interrupt stack.  Alternative leave
 * configISR_STACK_SIZE_WORDS undefined and update the linker script so that a
 * linker variable names __freertos_irq_stack_top has the same value as the top
 * of the stack used by main.  Using the linker script method will repurpose the
 * stack that was used by main before the scheduler was started for use as the
 * interrupt stack after the scheduler has started. */
#ifdef configISR_STACK_SIZE_WORDS
    static __attribute__ ((aligned(16))) StackType_t xISRStack[ configISR_STACK_SIZE_WORDS ] = { 0 };
    const StackType_t xISRStackTop = ( StackType_t ) &( xISRStack[ configISR_STACK_SIZE_WORDS & ~portBYTE_ALIGNMENT_MASK ] );

    /* Don't use 0xa5 as the stack fill bytes as that is used by the kernerl for
    the task stacks, and so will legitimately appear in many positions within
    the ISR stack. */
    #define portISR_STACK_FILL_BYTE    0xee
#else
    extern const uint32_t __freertos_irq_stack_top[];
    const StackType_t xISRStackTop = ( StackType_t ) __freertos_irq_stack_top;
#endif

/*
 * Setup the timer to generate the tick interrupts.  The implementation in this
 * file is weak to allow application writers to change the timer used to
 * generate the tick interrupt.
 */
void vPortSetupTimerInterrupt( void ) __attribute__(( weak ));

/*-----------------------------------------------------------*/

/* Used to program the machine timer compare register. */
uint64_t ullNextTime = 0ULL;
const uint64_t *pullNextTime = &ullNextTime;
const size_t uxTimerIncrementsForOneTick = ( size_t ) ( ( configCPU_CLOCK_HZ ) / ( configTICK_RATE_HZ ) ); /* Assumes increment won't go over 32-bits. */
uint32_t const ullMachineTimerCompareRegisterBase = configMTIMECMP_BASE_ADDRESS;
volatile uint64_t * pullMachineTimerCompareRegister = NULL;

/* Holds the critical nesting value - deliberately non-zero at start up to
 * ensure interrupts are not accidentally enabled before the scheduler starts. */
size_t xCriticalNesting = ( size_t ) 0xaaaaaaaa;
size_t *pxCriticalNesting = &xCriticalNesting;

/* Used to catch tasks that attempt to return from their implementing function. */
size_t xTaskReturnAddress = ( size_t ) portTASK_RETURN_ADDRESS;

/* Set configCHECK_FOR_STACK_OVERFLOW to 3 to add ISR stack checking to task
 * stack checking.  A problem in the ISR stack will trigger an assert, not call
 * the stack overflow hook function (because the stack overflow hook is specific
 * to a task stack, not the ISR stack). */
#if defined( configISR_STACK_SIZE_WORDS ) && ( configCHECK_FOR_STACK_OVERFLOW > 2 )
    #warning This path not tested, or even compiled yet.

    static const uint8_t ucExpectedStackBytes[] = {
                                    portISR_STACK_FILL_BYTE, portISR_STACK_FILL_BYTE, portISR_STACK_FILL_BYTE, portISR_STACK_FILL_BYTE,        \
                                    portISR_STACK_FILL_BYTE, portISR_STACK_FILL_BYTE, portISR_STACK_FILL_BYTE, portISR_STACK_FILL_BYTE,        \
                                    portISR_STACK_FILL_BYTE, portISR_STACK_FILL_BYTE, portISR_STACK_FILL_BYTE, portISR_STACK_FILL_BYTE,        \
                                    portISR_STACK_FILL_BYTE, portISR_STACK_FILL_BYTE, portISR_STACK_FILL_BYTE, portISR_STACK_FILL_BYTE,        \
                                    portISR_STACK_FILL_BYTE, portISR_STACK_FILL_BYTE, portISR_STACK_FILL_BYTE, portISR_STACK_FILL_BYTE };    \

    #define portCHECK_ISR_STACK() configASSERT( ( memcmp( ( void * ) xISRStack, ( void * ) ucExpectedStackBytes, sizeof( ucExpectedStackBytes ) ) == 0 ) )
#else
    /* Define the function away. */
    #define portCHECK_ISR_STACK()
#endif /* configCHECK_FOR_STACK_OVERFLOW > 2 */

/*-----------------------------------------------------------*/
#if( configMTIME_BASE_ADDRESS != 0 ) && ( configMTIMECMP_BASE_ADDRESS != 0 )
void vPortSetupTimerInterrupt(void)
{
    volatile uint64_t *mtime  = (uint64_t*) (TIMER_CTRL_ADDR + TIMER_MTIME/*TIMER_MTIME*/);
    volatile uint64_t *mtimecmp  = (uint64_t*) (TIMER_CTRL_ADDR + TIMER_MTIMECMP/*TIMER_MTIMECMP*/);
    uint64_t now = *mtime;
    uint64_t then = now + (configCPU_CLOCK_HZ / configTICK_RATE_HZ);

    *mtimecmp = then;
    eclic_set_trig(ECLIC_INT_MTIP, ECLIC_INT_ATTR_TRIG_LEVEL);
    eclic_set_vmode(ECLIC_INT_MTIP);
    eclic_set_irq_lvl(ECLIC_INT_MTIP, /*RV_PIC_LVL_TIMR*/ 0 << (8 - 3));
    eclic_enable_interrupt(ECLIC_INT_MTIP);

    eclic_set_vmode(ECLIC_INT_MSIP);
    eclic_set_irq_lvl(ECLIC_INT_MSIP, /*RV_PIC_LVL_TIMR*/ 0 << (8 - 3));
    eclic_enable_interrupt(ECLIC_INT_MSIP);

    // Enable the Machine-External bit in MIE
    set_csr(mie, MIE_MEIE);
    // Enable the Machine-Timer bit in MIE
    set_csr(mie, MIE_MTIE);
    // Enable interrupts in general.
    set_csr(mstatus, MSTATUS_MIE);

}
#endif
/*-----------------------------------------------------------*/

void prvTaskExitError( void )
{
    /* A function that implements a task must not exit or attempt to return to
    its caller as there is nothing to return to.  If a task wants to exit it
    should instead call vTaskDelete( NULL ).
    Artificially force an assert() to be triggered if configASSERT() is
    defined, then stop here so application writers can catch the error. */
    configASSERT( xCriticalNesting == ~0UL );
    portDISABLE_INTERRUPTS();

    for ( ;; );
}
/*-----------------------------------------------------------*/

/*Entry Point for Machine Timer Interrupt Handler*/
void vPortSysTickHandler(void)
{
    uint64_t then = 0;
    volatile uint64_t * mtime       = (uint64_t*) (TIMER_CTRL_ADDR + TIMER_MTIME);
    volatile uint64_t * mtimecmp    = (uint64_t*) (TIMER_CTRL_ADDR + TIMER_MTIMECMP);
    uint64_t now = *mtime;

    then = now + (configCPU_CLOCK_HZ / (configTICK_RATE_HZ));
    *mtimecmp = then;
    /* Increment the RTOS tick. */
    if ( xTaskIncrementTick() != pdFALSE )
    {
        vTaskSwitchContext();
    }
}
/*-----------------------------------------------------------*/

void vPortSWIHandler(void)
{
    *(uint32_t*)(TIMER_CTRL_ADDR + TIMER_MSIP) &= ~0x01;
    vTaskSwitchContext();
}

BaseType_t xPortStartScheduler( void )
{
extern void xPortStartFirstTask( void );

    #if( configASSERT_DEFINED == 1 )
    {
        /* Check alignment of the interrupt stack - which is the same as the
         * stack that was being used by main() prior to the scheduler being
         * started. */
        configASSERT( ( xISRStackTop & portBYTE_ALIGNMENT_MASK ) == 0 );

        #ifdef configISR_STACK_SIZE_WORDS
        {
            memset( ( void * ) xISRStack, portISR_STACK_FILL_BYTE, sizeof( xISRStack ) );
        }
        #endif /* configISR_STACK_SIZE_WORDS */
    }
    #endif /* configASSERT_DEFINED */

    /* If there is a CLINT then it is ok to use the default implementation
     * in this file, otherwise vPortSetupTimerInterrupt() must be implemented to
     * configure whichever clock is to be used to generate the tick interrupt. */
    vPortSetupTimerInterrupt();

    #if( ( configMTIME_BASE_ADDRESS != 0 ) && ( configMTIMECMP_BASE_ADDRESS != 0 ) )
    {
        /* Enable mtime and external interrupts.  1<<7 for timer interrupt,
         * 1<<11 for external interrupt.  _RB_ What happens here when mtime is
         * not present as with pulpino? */
        __asm volatile( "csrs mie, %0" :: "r"(0x880) );
    }
    #endif /* ( configMTIME_BASE_ADDRESS != 0 ) && ( configMTIMECMP_BASE_ADDRESS != 0 ) */

     /* Initialise the critical nesting count ready for the first task. */
     xCriticalNesting = 0;

    xPortStartFirstTask();

    /* Should not get here as after calling xPortStartFirstTask() only tasks
     * should be executing. */
    return pdFAIL;
}
/*-----------------------------------------------------------*/

void vPortEndScheduler( void )
{
    /* Not implemented. */
    for( ;; );
}
/*-----------------------------------------------------------*/

/* AML extend definitions. */
/* Set interrupt mask and return current interrupt enable register */
int xPortSetInterruptMask()
{
    int int_mask=0;

    int_mask=eclic_get_mth();
    eclic_set_mth ((configMAX_SYSCALL_INTERRUPT_PRIORITY)<<4);

    return int_mask;
}
/*-----------------------------------------------------------*/

/* Clear current interrupt mask and set given mask */
void vPortClearInterruptMask(int int_mask)
{
    eclic_set_mth (int_mask);
}
/*-----------------------------------------------------------*/

