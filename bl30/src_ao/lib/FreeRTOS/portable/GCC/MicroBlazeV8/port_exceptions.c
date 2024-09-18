/*
 * FreeRTOS Kernel V10.0.1
 * Copyright (C) 2017 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
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
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 4 spaces!
 */

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"

/* Hardware includes. */
#include <microblaze_exceptions_i.h>
#include <microblaze_exceptions_g.h>

/* The Xilinx library defined exception entry point stacks a number of
registers.  These definitions are offsets from the stack pointer to the various
stacked register values. */
#define portexR3_STACK_OFFSET	4
#define portexR4_STACK_OFFSET	5
#define portexR5_STACK_OFFSET	6
#define portexR6_STACK_OFFSET	7
#define portexR7_STACK_OFFSET	8
#define portexR8_STACK_OFFSET	9
#define portexR9_STACK_OFFSET	10
#define portexR10_STACK_OFFSET	11
#define portexR11_STACK_OFFSET	12
#define portexR12_STACK_OFFSET	13
#define portexR15_STACK_OFFSET	16
#define portexR18_STACK_OFFSET  19
#define portexMSR_STACK_OFFSET	20
#define portexR19_STACK_OFFSET  -1

/* This is defined to equal the size, in bytes, of the stack frame generated by
the Xilinx standard library exception entry point.  It is required to determine
the stack pointer value prior to the exception being entered. */
#define portexASM_HANDLER_STACK_FRAME_SIZE 84UL

/* The number of bytes a MicroBlaze instruction consumes. */
#define portexINSTRUCTION_SIZE	4

/* Exclude this entire file if the MicroBlaze is not configured to handle
exceptions, or the application defined configuration constant
configINSTALL_EXCEPTION_HANDLERS is not set to 1. */
#if ( MICROBLAZE_EXCEPTIONS_ENABLED == 1 ) && ( configINSTALL_EXCEPTION_HANDLERS == 1 )

/* This variable is set in the exception entry code, before
vPortExceptionHandler is called. */
uint32_t *pulStackPointerOnFunctionEntry = NULL;

/* This is the structure that is filled with the MicroBlaze context as it
existed immediately prior to the exception occurrence.  A pointer to this
structure is passed into the vApplicationExceptionRegisterDump() callback
function, if one is defined. */
static xPortRegisterDump xRegisterDump;

/* This is the FreeRTOS exception handler that is installed for all exception
types.  It is called from vPortExceptionHanlderEntry() - which is itself defined
in portasm.S. */
void vPortExceptionHandler( void *pvExceptionID );
extern void vPortExceptionHandlerEntry( void *pvExceptionID );

/*-----------------------------------------------------------*/

/* vApplicationExceptionRegisterDump() is a callback function that the
application can optionally define to receive a populated xPortRegisterDump
structure.  If the application chooses not to define a version of
vApplicationExceptionRegisterDump() then this weekly defined default
implementation will be called instead. */
extern void vApplicationExceptionRegisterDump( xPortRegisterDump *xRegisterDump ) __attribute__((weak));
void vApplicationExceptionRegisterDump( xPortRegisterDump *xRegisterDump )
{
	( void ) xRegisterDump;

	for( ;; )
	{
		portNOP();
	}
}
/*-----------------------------------------------------------*/

void vPortExceptionHandler( void *pvExceptionID )
{
extern void *pxCurrentTCB;

	/* Fill an xPortRegisterDump structure with the MicroBlaze context as it
	was immediately before the exception occurrence. */

	/* First fill in the name and handle of the task that was in the Running
	state when the exception occurred. */
	xRegisterDump.xCurrentTaskHandle = pxCurrentTCB;
	xRegisterDump.pcCurrentTaskName = pcTaskGetName( NULL );

	configASSERT( pulStackPointerOnFunctionEntry );

	/* Obtain the values of registers that were stacked prior to this function
	being called, and may have changed since they were stacked. */
	xRegisterDump.ulR3 = pulStackPointerOnFunctionEntry[ portexR3_STACK_OFFSET ];
	xRegisterDump.ulR4 = pulStackPointerOnFunctionEntry[ portexR4_STACK_OFFSET ];
	xRegisterDump.ulR5 = pulStackPointerOnFunctionEntry[ portexR5_STACK_OFFSET ];
	xRegisterDump.ulR6 = pulStackPointerOnFunctionEntry[ portexR6_STACK_OFFSET ];
	xRegisterDump.ulR7 = pulStackPointerOnFunctionEntry[ portexR7_STACK_OFFSET ];
	xRegisterDump.ulR8 = pulStackPointerOnFunctionEntry[ portexR8_STACK_OFFSET ];
	xRegisterDump.ulR9 = pulStackPointerOnFunctionEntry[ portexR9_STACK_OFFSET ];
	xRegisterDump.ulR10 = pulStackPointerOnFunctionEntry[ portexR10_STACK_OFFSET ];
	xRegisterDump.ulR11 = pulStackPointerOnFunctionEntry[ portexR11_STACK_OFFSET ];
	xRegisterDump.ulR12 = pulStackPointerOnFunctionEntry[ portexR12_STACK_OFFSET ];
	xRegisterDump.ulR15_return_address_from_subroutine = pulStackPointerOnFunctionEntry[ portexR15_STACK_OFFSET ];
	xRegisterDump.ulR18 = pulStackPointerOnFunctionEntry[ portexR18_STACK_OFFSET ];
	xRegisterDump.ulR19 = pulStackPointerOnFunctionEntry[ portexR19_STACK_OFFSET ];
	xRegisterDump.ulMSR = pulStackPointerOnFunctionEntry[ portexMSR_STACK_OFFSET ];

	/* Obtain the value of all other registers. */
	xRegisterDump.ulR2_small_data_area = mfgpr( R2 );
	xRegisterDump.ulR13_read_write_small_data_area = mfgpr( R13 );
	xRegisterDump.ulR14_return_address_from_interrupt = mfgpr( R14 );
	xRegisterDump.ulR16_return_address_from_trap = mfgpr( R16 );
	xRegisterDump.ulR17_return_address_from_exceptions = mfgpr( R17 );
	xRegisterDump.ulR20 = mfgpr( R20 );
	xRegisterDump.ulR21 = mfgpr( R21 );
	xRegisterDump.ulR22 = mfgpr( R22 );
	xRegisterDump.ulR23 = mfgpr( R23 );
	xRegisterDump.ulR24 = mfgpr( R24 );
	xRegisterDump.ulR25 = mfgpr( R25 );
	xRegisterDump.ulR26 = mfgpr( R26 );
	xRegisterDump.ulR27 = mfgpr( R27 );
	xRegisterDump.ulR28 = mfgpr( R28 );
	xRegisterDump.ulR29 = mfgpr( R29 );
	xRegisterDump.ulR30 = mfgpr( R30 );
	xRegisterDump.ulR31 = mfgpr( R31 );
	xRegisterDump.ulR1_SP = ( ( uint32_t ) pulStackPointerOnFunctionEntry ) + portexASM_HANDLER_STACK_FRAME_SIZE;
	xRegisterDump.ulEAR = mfear();
	xRegisterDump.ulESR = mfesr();
	xRegisterDump.ulEDR = mfedr();

	/* Move the saved program counter back to the instruction that was executed
	when the exception occurred.  This is only valid for certain types of
	exception. */
	xRegisterDump.ulPC = xRegisterDump.ulR17_return_address_from_exceptions - portexINSTRUCTION_SIZE;

	#if( XPAR_MICROBLAZE_USE_FPU != 0 )
	{
		xRegisterDump.ulFSR = mffsr();
	}
	#else
	{
		xRegisterDump.ulFSR = 0UL;
	}
	#endif

	/* Also fill in a string that describes what type of exception this is.
	The string uses the same ID names as defined in the MicroBlaze standard
	library exception header files. */
	switch( ( uint32_t ) pvExceptionID )
	{
		case XEXC_ID_FSL :
				xRegisterDump.pcExceptionCause = ( int8_t * const ) "XEXC_ID_FSL";
				break;

		case XEXC_ID_UNALIGNED_ACCESS :
				xRegisterDump.pcExceptionCause = ( int8_t * const ) "XEXC_ID_UNALIGNED_ACCESS";
				break;

		case XEXC_ID_ILLEGAL_OPCODE :
				xRegisterDump.pcExceptionCause = ( int8_t * const ) "XEXC_ID_ILLEGAL_OPCODE";
				break;

		case XEXC_ID_M_AXI_I_EXCEPTION :
				xRegisterDump.pcExceptionCause = ( int8_t * const ) "XEXC_ID_M_AXI_I_EXCEPTION or XEXC_ID_IPLB_EXCEPTION";
				break;

		case XEXC_ID_M_AXI_D_EXCEPTION :
				xRegisterDump.pcExceptionCause = ( int8_t * const ) "XEXC_ID_M_AXI_D_EXCEPTION or XEXC_ID_DPLB_EXCEPTION";
				break;

		case XEXC_ID_DIV_BY_ZERO :
				xRegisterDump.pcExceptionCause = ( int8_t * const ) "XEXC_ID_DIV_BY_ZERO";
				break;

		case XEXC_ID_STACK_VIOLATION :
				xRegisterDump.pcExceptionCause = ( int8_t * const ) "XEXC_ID_STACK_VIOLATION or XEXC_ID_MMU";
				break;

		#if( XPAR_MICROBLAZE_USE_FPU != 0 )

			case XEXC_ID_FPU :
						xRegisterDump.pcExceptionCause = ( int8_t * const ) "XEXC_ID_FPU see ulFSR value";
						break;

		#endif /* XPAR_MICROBLAZE_USE_FPU */
	}

	/* vApplicationExceptionRegisterDump() is a callback function that the
	application can optionally define to receive the populated xPortRegisterDump
	structure.  If the application chooses not to define a version of
	vApplicationExceptionRegisterDump() then the weekly defined default
	implementation within this file will be called instead. */
	vApplicationExceptionRegisterDump( &xRegisterDump );

	/* Must not attempt to leave this function! */
	for( ;; )
	{
		portNOP();
	}
}
/*-----------------------------------------------------------*/

void vPortExceptionsInstallHandlers( void )
{
static uint32_t ulHandlersAlreadyInstalled = pdFALSE;

	if( ulHandlersAlreadyInstalled == pdFALSE )
	{
		ulHandlersAlreadyInstalled = pdTRUE;

		#if XPAR_MICROBLAZE_UNALIGNED_EXCEPTIONS == 1
			microblaze_register_exception_handler( XEXC_ID_UNALIGNED_ACCESS, vPortExceptionHandlerEntry, ( void * ) XEXC_ID_UNALIGNED_ACCESS );
		#endif /* XPAR_MICROBLAZE_UNALIGNED_EXCEPTIONS*/

		#if XPAR_MICROBLAZE_ILL_OPCODE_EXCEPTION == 1
			microblaze_register_exception_handler( XEXC_ID_ILLEGAL_OPCODE, vPortExceptionHandlerEntry, ( void * ) XEXC_ID_ILLEGAL_OPCODE );
		#endif /* XPAR_MICROBLAZE_ILL_OPCODE_EXCEPTION */

		#if XPAR_MICROBLAZE_M_AXI_I_BUS_EXCEPTION == 1
			microblaze_register_exception_handler( XEXC_ID_M_AXI_I_EXCEPTION, vPortExceptionHandlerEntry, ( void * ) XEXC_ID_M_AXI_I_EXCEPTION );
		#endif /* XPAR_MICROBLAZE_M_AXI_I_BUS_EXCEPTION */

		#if XPAR_MICROBLAZE_M_AXI_D_BUS_EXCEPTION == 1
			microblaze_register_exception_handler( XEXC_ID_M_AXI_D_EXCEPTION, vPortExceptionHandlerEntry, ( void * ) XEXC_ID_M_AXI_D_EXCEPTION );
		#endif /* XPAR_MICROBLAZE_M_AXI_D_BUS_EXCEPTION */

		#if XPAR_MICROBLAZE_IPLB_BUS_EXCEPTION == 1
			microblaze_register_exception_handler( XEXC_ID_IPLB_EXCEPTION, vPortExceptionHandlerEntry, ( void * ) XEXC_ID_IPLB_EXCEPTION );
		#endif /* XPAR_MICROBLAZE_IPLB_BUS_EXCEPTION */

		#if XPAR_MICROBLAZE_DPLB_BUS_EXCEPTION == 1
			microblaze_register_exception_handler( XEXC_ID_DPLB_EXCEPTION, vPortExceptionHandlerEntry, ( void * ) XEXC_ID_DPLB_EXCEPTION );
		#endif /* XPAR_MICROBLAZE_DPLB_BUS_EXCEPTION */

		#if XPAR_MICROBLAZE_DIV_ZERO_EXCEPTION == 1
			microblaze_register_exception_handler( XEXC_ID_DIV_BY_ZERO, vPortExceptionHandlerEntry, ( void * ) XEXC_ID_DIV_BY_ZERO );
		#endif /* XPAR_MICROBLAZE_DIV_ZERO_EXCEPTION */

		#if XPAR_MICROBLAZE_FPU_EXCEPTION == 1
			microblaze_register_exception_handler( XEXC_ID_FPU, vPortExceptionHandlerEntry, ( void * ) XEXC_ID_FPU );
		#endif /* XPAR_MICROBLAZE_FPU_EXCEPTION */

		#if XPAR_MICROBLAZE_FSL_EXCEPTION == 1
			microblaze_register_exception_handler( XEXC_ID_FSL, vPortExceptionHandlerEntry, ( void * ) XEXC_ID_FSL );
		#endif /* XPAR_MICROBLAZE_FSL_EXCEPTION */

		microblaze_enable_exceptions();
	}
}

/* Exclude the entire file if the MicroBlaze is not configured to handle
exceptions, or the application defined configuration item
configINSTALL_EXCEPTION_HANDLERS is not set to 1. */
#endif /* ( MICROBLAZE_EXCEPTIONS_ENABLED == 1 ) && ( configINSTALL_EXCEPTION_HANDLERS == 1 ) */



