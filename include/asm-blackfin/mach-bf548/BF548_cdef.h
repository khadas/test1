/* DO NOT EDIT THIS FILE
 * Automatically generated by generate-cdef-headers.xsl
 * DO NOT EDIT THIS FILE
 */

#ifndef __BFIN_CDEF_ADSP_BF548_proc__
#define __BFIN_CDEF_ADSP_BF548_proc__

#include "../mach-common/ADSP-EDN-core_cdef.h"

#include "ADSP-EDN-BF548-extended_cdef.h"

#define pCHIPID                        ((uint32_t volatile *)CHIPID)
#define bfin_read_CHIPID()             bfin_read32(CHIPID)
#define bfin_write_CHIPID(val)         bfin_write32(CHIPID, val)
#define pSWRST                         ((uint16_t volatile *)SWRST) /* Software Reset Register */
#define bfin_read_SWRST()              bfin_read16(SWRST)
#define bfin_write_SWRST(val)          bfin_write16(SWRST, val)
#define pSYSCR                         ((uint16_t volatile *)SYSCR) /* System Configuration register */
#define bfin_read_SYSCR()              bfin_read16(SYSCR)
#define bfin_write_SYSCR(val)          bfin_write16(SYSCR, val)
#define pSRAM_BASE_ADDR                ((void * volatile *)SRAM_BASE_ADDR) /* SRAM Base Address (Read Only) */
#define bfin_read_SRAM_BASE_ADDR()     bfin_readPTR(SRAM_BASE_ADDR)
#define bfin_write_SRAM_BASE_ADDR(val) bfin_writePTR(SRAM_BASE_ADDR, val)
#define pDMEM_CONTROL                  ((uint32_t volatile *)DMEM_CONTROL) /* Data memory control */
#define bfin_read_DMEM_CONTROL()       bfin_read32(DMEM_CONTROL)
#define bfin_write_DMEM_CONTROL(val)   bfin_write32(DMEM_CONTROL, val)
#define pDCPLB_STATUS                  ((uint32_t volatile *)DCPLB_STATUS) /* Data Cache Programmable Look-Aside Buffer Status */
#define bfin_read_DCPLB_STATUS()       bfin_read32(DCPLB_STATUS)
#define bfin_write_DCPLB_STATUS(val)   bfin_write32(DCPLB_STATUS, val)
#define pDCPLB_FAULT_ADDR              ((void * volatile *)DCPLB_FAULT_ADDR) /* Data Cache Programmable Look-Aside Buffer Fault Address */
#define bfin_read_DCPLB_FAULT_ADDR()   bfin_readPTR(DCPLB_FAULT_ADDR)
#define bfin_write_DCPLB_FAULT_ADDR(val) bfin_writePTR(DCPLB_FAULT_ADDR, val)
#define pDCPLB_ADDR0                   ((void * volatile *)DCPLB_ADDR0) /* Data Cache Protection Lookaside Buffer 0 */
#define bfin_read_DCPLB_ADDR0()        bfin_readPTR(DCPLB_ADDR0)
#define bfin_write_DCPLB_ADDR0(val)    bfin_writePTR(DCPLB_ADDR0, val)
#define pDCPLB_ADDR1                   ((void * volatile *)DCPLB_ADDR1) /* Data Cache Protection Lookaside Buffer 1 */
#define bfin_read_DCPLB_ADDR1()        bfin_readPTR(DCPLB_ADDR1)
#define bfin_write_DCPLB_ADDR1(val)    bfin_writePTR(DCPLB_ADDR1, val)
#define pDCPLB_ADDR2                   ((void * volatile *)DCPLB_ADDR2) /* Data Cache Protection Lookaside Buffer 2 */
#define bfin_read_DCPLB_ADDR2()        bfin_readPTR(DCPLB_ADDR2)
#define bfin_write_DCPLB_ADDR2(val)    bfin_writePTR(DCPLB_ADDR2, val)
#define pDCPLB_ADDR3                   ((void * volatile *)DCPLB_ADDR3) /* Data Cache Protection Lookaside Buffer 3 */
#define bfin_read_DCPLB_ADDR3()        bfin_readPTR(DCPLB_ADDR3)
#define bfin_write_DCPLB_ADDR3(val)    bfin_writePTR(DCPLB_ADDR3, val)
#define pDCPLB_ADDR4                   ((void * volatile *)DCPLB_ADDR4) /* Data Cache Protection Lookaside Buffer 4 */
#define bfin_read_DCPLB_ADDR4()        bfin_readPTR(DCPLB_ADDR4)
#define bfin_write_DCPLB_ADDR4(val)    bfin_writePTR(DCPLB_ADDR4, val)
#define pDCPLB_ADDR5                   ((void * volatile *)DCPLB_ADDR5) /* Data Cache Protection Lookaside Buffer 5 */
#define bfin_read_DCPLB_ADDR5()        bfin_readPTR(DCPLB_ADDR5)
#define bfin_write_DCPLB_ADDR5(val)    bfin_writePTR(DCPLB_ADDR5, val)
#define pDCPLB_ADDR6                   ((void * volatile *)DCPLB_ADDR6) /* Data Cache Protection Lookaside Buffer 6 */
#define bfin_read_DCPLB_ADDR6()        bfin_readPTR(DCPLB_ADDR6)
#define bfin_write_DCPLB_ADDR6(val)    bfin_writePTR(DCPLB_ADDR6, val)
#define pDCPLB_ADDR7                   ((void * volatile *)DCPLB_ADDR7) /* Data Cache Protection Lookaside Buffer 7 */
#define bfin_read_DCPLB_ADDR7()        bfin_readPTR(DCPLB_ADDR7)
#define bfin_write_DCPLB_ADDR7(val)    bfin_writePTR(DCPLB_ADDR7, val)
#define pDCPLB_ADDR8                   ((void * volatile *)DCPLB_ADDR8) /* Data Cache Protection Lookaside Buffer 8 */
#define bfin_read_DCPLB_ADDR8()        bfin_readPTR(DCPLB_ADDR8)
#define bfin_write_DCPLB_ADDR8(val)    bfin_writePTR(DCPLB_ADDR8, val)
#define pDCPLB_ADDR9                   ((void * volatile *)DCPLB_ADDR9) /* Data Cache Protection Lookaside Buffer 9 */
#define bfin_read_DCPLB_ADDR9()        bfin_readPTR(DCPLB_ADDR9)
#define bfin_write_DCPLB_ADDR9(val)    bfin_writePTR(DCPLB_ADDR9, val)
#define pDCPLB_ADDR10                  ((void * volatile *)DCPLB_ADDR10) /* Data Cache Protection Lookaside Buffer 10 */
#define bfin_read_DCPLB_ADDR10()       bfin_readPTR(DCPLB_ADDR10)
#define bfin_write_DCPLB_ADDR10(val)   bfin_writePTR(DCPLB_ADDR10, val)
#define pDCPLB_ADDR11                  ((void * volatile *)DCPLB_ADDR11) /* Data Cache Protection Lookaside Buffer 11 */
#define bfin_read_DCPLB_ADDR11()       bfin_readPTR(DCPLB_ADDR11)
#define bfin_write_DCPLB_ADDR11(val)   bfin_writePTR(DCPLB_ADDR11, val)
#define pDCPLB_ADDR12                  ((void * volatile *)DCPLB_ADDR12) /* Data Cache Protection Lookaside Buffer 12 */
#define bfin_read_DCPLB_ADDR12()       bfin_readPTR(DCPLB_ADDR12)
#define bfin_write_DCPLB_ADDR12(val)   bfin_writePTR(DCPLB_ADDR12, val)
#define pDCPLB_ADDR13                  ((void * volatile *)DCPLB_ADDR13) /* Data Cache Protection Lookaside Buffer 13 */
#define bfin_read_DCPLB_ADDR13()       bfin_readPTR(DCPLB_ADDR13)
#define bfin_write_DCPLB_ADDR13(val)   bfin_writePTR(DCPLB_ADDR13, val)
#define pDCPLB_ADDR14                  ((void * volatile *)DCPLB_ADDR14) /* Data Cache Protection Lookaside Buffer 14 */
#define bfin_read_DCPLB_ADDR14()       bfin_readPTR(DCPLB_ADDR14)
#define bfin_write_DCPLB_ADDR14(val)   bfin_writePTR(DCPLB_ADDR14, val)
#define pDCPLB_ADDR15                  ((void * volatile *)DCPLB_ADDR15) /* Data Cache Protection Lookaside Buffer 15 */
#define bfin_read_DCPLB_ADDR15()       bfin_readPTR(DCPLB_ADDR15)
#define bfin_write_DCPLB_ADDR15(val)   bfin_writePTR(DCPLB_ADDR15, val)
#define pDCPLB_DATA0                   ((uint32_t volatile *)DCPLB_DATA0) /* Data Cache 0 Status */
#define bfin_read_DCPLB_DATA0()        bfin_read32(DCPLB_DATA0)
#define bfin_write_DCPLB_DATA0(val)    bfin_write32(DCPLB_DATA0, val)
#define pDCPLB_DATA1                   ((uint32_t volatile *)DCPLB_DATA1) /* Data Cache 1 Status */
#define bfin_read_DCPLB_DATA1()        bfin_read32(DCPLB_DATA1)
#define bfin_write_DCPLB_DATA1(val)    bfin_write32(DCPLB_DATA1, val)
#define pDCPLB_DATA2                   ((uint32_t volatile *)DCPLB_DATA2) /* Data Cache 2 Status */
#define bfin_read_DCPLB_DATA2()        bfin_read32(DCPLB_DATA2)
#define bfin_write_DCPLB_DATA2(val)    bfin_write32(DCPLB_DATA2, val)
#define pDCPLB_DATA3                   ((uint32_t volatile *)DCPLB_DATA3) /* Data Cache 3 Status */
#define bfin_read_DCPLB_DATA3()        bfin_read32(DCPLB_DATA3)
#define bfin_write_DCPLB_DATA3(val)    bfin_write32(DCPLB_DATA3, val)
#define pDCPLB_DATA4                   ((uint32_t volatile *)DCPLB_DATA4) /* Data Cache 4 Status */
#define bfin_read_DCPLB_DATA4()        bfin_read32(DCPLB_DATA4)
#define bfin_write_DCPLB_DATA4(val)    bfin_write32(DCPLB_DATA4, val)
#define pDCPLB_DATA5                   ((uint32_t volatile *)DCPLB_DATA5) /* Data Cache 5 Status */
#define bfin_read_DCPLB_DATA5()        bfin_read32(DCPLB_DATA5)
#define bfin_write_DCPLB_DATA5(val)    bfin_write32(DCPLB_DATA5, val)
#define pDCPLB_DATA6                   ((uint32_t volatile *)DCPLB_DATA6) /* Data Cache 6 Status */
#define bfin_read_DCPLB_DATA6()        bfin_read32(DCPLB_DATA6)
#define bfin_write_DCPLB_DATA6(val)    bfin_write32(DCPLB_DATA6, val)
#define pDCPLB_DATA7                   ((uint32_t volatile *)DCPLB_DATA7) /* Data Cache 7 Status */
#define bfin_read_DCPLB_DATA7()        bfin_read32(DCPLB_DATA7)
#define bfin_write_DCPLB_DATA7(val)    bfin_write32(DCPLB_DATA7, val)
#define pDCPLB_DATA8                   ((uint32_t volatile *)DCPLB_DATA8) /* Data Cache 8 Status */
#define bfin_read_DCPLB_DATA8()        bfin_read32(DCPLB_DATA8)
#define bfin_write_DCPLB_DATA8(val)    bfin_write32(DCPLB_DATA8, val)
#define pDCPLB_DATA9                   ((uint32_t volatile *)DCPLB_DATA9) /* Data Cache 9 Status */
#define bfin_read_DCPLB_DATA9()        bfin_read32(DCPLB_DATA9)
#define bfin_write_DCPLB_DATA9(val)    bfin_write32(DCPLB_DATA9, val)
#define pDCPLB_DATA10                  ((uint32_t volatile *)DCPLB_DATA10) /* Data Cache 10 Status */
#define bfin_read_DCPLB_DATA10()       bfin_read32(DCPLB_DATA10)
#define bfin_write_DCPLB_DATA10(val)   bfin_write32(DCPLB_DATA10, val)
#define pDCPLB_DATA11                  ((uint32_t volatile *)DCPLB_DATA11) /* Data Cache 11 Status */
#define bfin_read_DCPLB_DATA11()       bfin_read32(DCPLB_DATA11)
#define bfin_write_DCPLB_DATA11(val)   bfin_write32(DCPLB_DATA11, val)
#define pDCPLB_DATA12                  ((uint32_t volatile *)DCPLB_DATA12) /* Data Cache 12 Status */
#define bfin_read_DCPLB_DATA12()       bfin_read32(DCPLB_DATA12)
#define bfin_write_DCPLB_DATA12(val)   bfin_write32(DCPLB_DATA12, val)
#define pDCPLB_DATA13                  ((uint32_t volatile *)DCPLB_DATA13) /* Data Cache 13 Status */
#define bfin_read_DCPLB_DATA13()       bfin_read32(DCPLB_DATA13)
#define bfin_write_DCPLB_DATA13(val)   bfin_write32(DCPLB_DATA13, val)
#define pDCPLB_DATA14                  ((uint32_t volatile *)DCPLB_DATA14) /* Data Cache 14 Status */
#define bfin_read_DCPLB_DATA14()       bfin_read32(DCPLB_DATA14)
#define bfin_write_DCPLB_DATA14(val)   bfin_write32(DCPLB_DATA14, val)
#define pDCPLB_DATA15                  ((uint32_t volatile *)DCPLB_DATA15) /* Data Cache 15 Status */
#define bfin_read_DCPLB_DATA15()       bfin_read32(DCPLB_DATA15)
#define bfin_write_DCPLB_DATA15(val)   bfin_write32(DCPLB_DATA15, val)
#define pDTEST_COMMAND                 ((uint32_t volatile *)DTEST_COMMAND) /* Data Test Command Register */
#define bfin_read_DTEST_COMMAND()      bfin_read32(DTEST_COMMAND)
#define bfin_write_DTEST_COMMAND(val)  bfin_write32(DTEST_COMMAND, val)
#define pDTEST_DATA0                   ((uint32_t volatile *)DTEST_DATA0) /* Data Test Data Register */
#define bfin_read_DTEST_DATA0()        bfin_read32(DTEST_DATA0)
#define bfin_write_DTEST_DATA0(val)    bfin_write32(DTEST_DATA0, val)
#define pDTEST_DATA1                   ((uint32_t volatile *)DTEST_DATA1) /* Data Test Data Register */
#define bfin_read_DTEST_DATA1()        bfin_read32(DTEST_DATA1)
#define bfin_write_DTEST_DATA1(val)    bfin_write32(DTEST_DATA1, val)
#define pIMEM_CONTROL                  ((uint32_t volatile *)IMEM_CONTROL) /* Instruction Memory Control */
#define bfin_read_IMEM_CONTROL()       bfin_read32(IMEM_CONTROL)
#define bfin_write_IMEM_CONTROL(val)   bfin_write32(IMEM_CONTROL, val)
#define pICPLB_STATUS                  ((uint32_t volatile *)ICPLB_STATUS) /* Instruction Cache Programmable Look-Aside Buffer Status */
#define bfin_read_ICPLB_STATUS()       bfin_read32(ICPLB_STATUS)
#define bfin_write_ICPLB_STATUS(val)   bfin_write32(ICPLB_STATUS, val)
#define pICPLB_FAULT_ADDR              ((void * volatile *)ICPLB_FAULT_ADDR) /* Instruction Cache Programmable Look-Aside Buffer Fault Address */
#define bfin_read_ICPLB_FAULT_ADDR()   bfin_readPTR(ICPLB_FAULT_ADDR)
#define bfin_write_ICPLB_FAULT_ADDR(val) bfin_writePTR(ICPLB_FAULT_ADDR, val)
#define pICPLB_ADDR0                   ((void * volatile *)ICPLB_ADDR0) /* Instruction Cacheability Protection Lookaside Buffer 0 */
#define bfin_read_ICPLB_ADDR0()        bfin_readPTR(ICPLB_ADDR0)
#define bfin_write_ICPLB_ADDR0(val)    bfin_writePTR(ICPLB_ADDR0, val)
#define pICPLB_ADDR1                   ((void * volatile *)ICPLB_ADDR1) /* Instruction Cacheability Protection Lookaside Buffer 1 */
#define bfin_read_ICPLB_ADDR1()        bfin_readPTR(ICPLB_ADDR1)
#define bfin_write_ICPLB_ADDR1(val)    bfin_writePTR(ICPLB_ADDR1, val)
#define pICPLB_ADDR2                   ((void * volatile *)ICPLB_ADDR2) /* Instruction Cacheability Protection Lookaside Buffer 2 */
#define bfin_read_ICPLB_ADDR2()        bfin_readPTR(ICPLB_ADDR2)
#define bfin_write_ICPLB_ADDR2(val)    bfin_writePTR(ICPLB_ADDR2, val)
#define pICPLB_ADDR3                   ((void * volatile *)ICPLB_ADDR3) /* Instruction Cacheability Protection Lookaside Buffer 3 */
#define bfin_read_ICPLB_ADDR3()        bfin_readPTR(ICPLB_ADDR3)
#define bfin_write_ICPLB_ADDR3(val)    bfin_writePTR(ICPLB_ADDR3, val)
#define pICPLB_ADDR4                   ((void * volatile *)ICPLB_ADDR4) /* Instruction Cacheability Protection Lookaside Buffer 4 */
#define bfin_read_ICPLB_ADDR4()        bfin_readPTR(ICPLB_ADDR4)
#define bfin_write_ICPLB_ADDR4(val)    bfin_writePTR(ICPLB_ADDR4, val)
#define pICPLB_ADDR5                   ((void * volatile *)ICPLB_ADDR5) /* Instruction Cacheability Protection Lookaside Buffer 5 */
#define bfin_read_ICPLB_ADDR5()        bfin_readPTR(ICPLB_ADDR5)
#define bfin_write_ICPLB_ADDR5(val)    bfin_writePTR(ICPLB_ADDR5, val)
#define pICPLB_ADDR6                   ((void * volatile *)ICPLB_ADDR6) /* Instruction Cacheability Protection Lookaside Buffer 6 */
#define bfin_read_ICPLB_ADDR6()        bfin_readPTR(ICPLB_ADDR6)
#define bfin_write_ICPLB_ADDR6(val)    bfin_writePTR(ICPLB_ADDR6, val)
#define pICPLB_ADDR7                   ((void * volatile *)ICPLB_ADDR7) /* Instruction Cacheability Protection Lookaside Buffer 7 */
#define bfin_read_ICPLB_ADDR7()        bfin_readPTR(ICPLB_ADDR7)
#define bfin_write_ICPLB_ADDR7(val)    bfin_writePTR(ICPLB_ADDR7, val)
#define pICPLB_ADDR8                   ((void * volatile *)ICPLB_ADDR8) /* Instruction Cacheability Protection Lookaside Buffer 8 */
#define bfin_read_ICPLB_ADDR8()        bfin_readPTR(ICPLB_ADDR8)
#define bfin_write_ICPLB_ADDR8(val)    bfin_writePTR(ICPLB_ADDR8, val)
#define pICPLB_ADDR9                   ((void * volatile *)ICPLB_ADDR9) /* Instruction Cacheability Protection Lookaside Buffer 9 */
#define bfin_read_ICPLB_ADDR9()        bfin_readPTR(ICPLB_ADDR9)
#define bfin_write_ICPLB_ADDR9(val)    bfin_writePTR(ICPLB_ADDR9, val)
#define pICPLB_ADDR10                  ((void * volatile *)ICPLB_ADDR10) /* Instruction Cacheability Protection Lookaside Buffer 10 */
#define bfin_read_ICPLB_ADDR10()       bfin_readPTR(ICPLB_ADDR10)
#define bfin_write_ICPLB_ADDR10(val)   bfin_writePTR(ICPLB_ADDR10, val)
#define pICPLB_ADDR11                  ((void * volatile *)ICPLB_ADDR11) /* Instruction Cacheability Protection Lookaside Buffer 11 */
#define bfin_read_ICPLB_ADDR11()       bfin_readPTR(ICPLB_ADDR11)
#define bfin_write_ICPLB_ADDR11(val)   bfin_writePTR(ICPLB_ADDR11, val)
#define pICPLB_ADDR12                  ((void * volatile *)ICPLB_ADDR12) /* Instruction Cacheability Protection Lookaside Buffer 12 */
#define bfin_read_ICPLB_ADDR12()       bfin_readPTR(ICPLB_ADDR12)
#define bfin_write_ICPLB_ADDR12(val)   bfin_writePTR(ICPLB_ADDR12, val)
#define pICPLB_ADDR13                  ((void * volatile *)ICPLB_ADDR13) /* Instruction Cacheability Protection Lookaside Buffer 13 */
#define bfin_read_ICPLB_ADDR13()       bfin_readPTR(ICPLB_ADDR13)
#define bfin_write_ICPLB_ADDR13(val)   bfin_writePTR(ICPLB_ADDR13, val)
#define pICPLB_ADDR14                  ((void * volatile *)ICPLB_ADDR14) /* Instruction Cacheability Protection Lookaside Buffer 14 */
#define bfin_read_ICPLB_ADDR14()       bfin_readPTR(ICPLB_ADDR14)
#define bfin_write_ICPLB_ADDR14(val)   bfin_writePTR(ICPLB_ADDR14, val)
#define pICPLB_ADDR15                  ((void * volatile *)ICPLB_ADDR15) /* Instruction Cacheability Protection Lookaside Buffer 15 */
#define bfin_read_ICPLB_ADDR15()       bfin_readPTR(ICPLB_ADDR15)
#define bfin_write_ICPLB_ADDR15(val)   bfin_writePTR(ICPLB_ADDR15, val)
#define pICPLB_DATA0                   ((uint32_t volatile *)ICPLB_DATA0) /* Instruction Cache 0 Status */
#define bfin_read_ICPLB_DATA0()        bfin_read32(ICPLB_DATA0)
#define bfin_write_ICPLB_DATA0(val)    bfin_write32(ICPLB_DATA0, val)
#define pICPLB_DATA1                   ((uint32_t volatile *)ICPLB_DATA1) /* Instruction Cache 1 Status */
#define bfin_read_ICPLB_DATA1()        bfin_read32(ICPLB_DATA1)
#define bfin_write_ICPLB_DATA1(val)    bfin_write32(ICPLB_DATA1, val)
#define pICPLB_DATA2                   ((uint32_t volatile *)ICPLB_DATA2) /* Instruction Cache 2 Status */
#define bfin_read_ICPLB_DATA2()        bfin_read32(ICPLB_DATA2)
#define bfin_write_ICPLB_DATA2(val)    bfin_write32(ICPLB_DATA2, val)
#define pICPLB_DATA3                   ((uint32_t volatile *)ICPLB_DATA3) /* Instruction Cache 3 Status */
#define bfin_read_ICPLB_DATA3()        bfin_read32(ICPLB_DATA3)
#define bfin_write_ICPLB_DATA3(val)    bfin_write32(ICPLB_DATA3, val)
#define pICPLB_DATA4                   ((uint32_t volatile *)ICPLB_DATA4) /* Instruction Cache 4 Status */
#define bfin_read_ICPLB_DATA4()        bfin_read32(ICPLB_DATA4)
#define bfin_write_ICPLB_DATA4(val)    bfin_write32(ICPLB_DATA4, val)
#define pICPLB_DATA5                   ((uint32_t volatile *)ICPLB_DATA5) /* Instruction Cache 5 Status */
#define bfin_read_ICPLB_DATA5()        bfin_read32(ICPLB_DATA5)
#define bfin_write_ICPLB_DATA5(val)    bfin_write32(ICPLB_DATA5, val)
#define pICPLB_DATA6                   ((uint32_t volatile *)ICPLB_DATA6) /* Instruction Cache 6 Status */
#define bfin_read_ICPLB_DATA6()        bfin_read32(ICPLB_DATA6)
#define bfin_write_ICPLB_DATA6(val)    bfin_write32(ICPLB_DATA6, val)
#define pICPLB_DATA7                   ((uint32_t volatile *)ICPLB_DATA7) /* Instruction Cache 7 Status */
#define bfin_read_ICPLB_DATA7()        bfin_read32(ICPLB_DATA7)
#define bfin_write_ICPLB_DATA7(val)    bfin_write32(ICPLB_DATA7, val)
#define pICPLB_DATA8                   ((uint32_t volatile *)ICPLB_DATA8) /* Instruction Cache 8 Status */
#define bfin_read_ICPLB_DATA8()        bfin_read32(ICPLB_DATA8)
#define bfin_write_ICPLB_DATA8(val)    bfin_write32(ICPLB_DATA8, val)
#define pICPLB_DATA9                   ((uint32_t volatile *)ICPLB_DATA9) /* Instruction Cache 9 Status */
#define bfin_read_ICPLB_DATA9()        bfin_read32(ICPLB_DATA9)
#define bfin_write_ICPLB_DATA9(val)    bfin_write32(ICPLB_DATA9, val)
#define pICPLB_DATA10                  ((uint32_t volatile *)ICPLB_DATA10) /* Instruction Cache 10 Status */
#define bfin_read_ICPLB_DATA10()       bfin_read32(ICPLB_DATA10)
#define bfin_write_ICPLB_DATA10(val)   bfin_write32(ICPLB_DATA10, val)
#define pICPLB_DATA11                  ((uint32_t volatile *)ICPLB_DATA11) /* Instruction Cache 11 Status */
#define bfin_read_ICPLB_DATA11()       bfin_read32(ICPLB_DATA11)
#define bfin_write_ICPLB_DATA11(val)   bfin_write32(ICPLB_DATA11, val)
#define pICPLB_DATA12                  ((uint32_t volatile *)ICPLB_DATA12) /* Instruction Cache 12 Status */
#define bfin_read_ICPLB_DATA12()       bfin_read32(ICPLB_DATA12)
#define bfin_write_ICPLB_DATA12(val)   bfin_write32(ICPLB_DATA12, val)
#define pICPLB_DATA13                  ((uint32_t volatile *)ICPLB_DATA13) /* Instruction Cache 13 Status */
#define bfin_read_ICPLB_DATA13()       bfin_read32(ICPLB_DATA13)
#define bfin_write_ICPLB_DATA13(val)   bfin_write32(ICPLB_DATA13, val)
#define pICPLB_DATA14                  ((uint32_t volatile *)ICPLB_DATA14) /* Instruction Cache 14 Status */
#define bfin_read_ICPLB_DATA14()       bfin_read32(ICPLB_DATA14)
#define bfin_write_ICPLB_DATA14(val)   bfin_write32(ICPLB_DATA14, val)
#define pICPLB_DATA15                  ((uint32_t volatile *)ICPLB_DATA15) /* Instruction Cache 15 Status */
#define bfin_read_ICPLB_DATA15()       bfin_read32(ICPLB_DATA15)
#define bfin_write_ICPLB_DATA15(val)   bfin_write32(ICPLB_DATA15, val)
#define pITEST_COMMAND                 ((uint32_t volatile *)ITEST_COMMAND) /* Instruction Test Command Register */
#define bfin_read_ITEST_COMMAND()      bfin_read32(ITEST_COMMAND)
#define bfin_write_ITEST_COMMAND(val)  bfin_write32(ITEST_COMMAND, val)
#define pITEST_DATA0                   ((uint32_t volatile *)ITEST_DATA0) /* Instruction Test Data Register */
#define bfin_read_ITEST_DATA0()        bfin_read32(ITEST_DATA0)
#define bfin_write_ITEST_DATA0(val)    bfin_write32(ITEST_DATA0, val)
#define pITEST_DATA1                   ((uint32_t volatile *)ITEST_DATA1) /* Instruction Test Data Register */
#define bfin_read_ITEST_DATA1()        bfin_read32(ITEST_DATA1)
#define bfin_write_ITEST_DATA1(val)    bfin_write32(ITEST_DATA1, val)
#define pEVT0                          ((void * volatile *)EVT0) /* Event Vector 0 ESR Address */
#define bfin_read_EVT0()               bfin_readPTR(EVT0)
#define bfin_write_EVT0(val)           bfin_writePTR(EVT0, val)
#define pEVT1                          ((void * volatile *)EVT1) /* Event Vector 1 ESR Address */
#define bfin_read_EVT1()               bfin_readPTR(EVT1)
#define bfin_write_EVT1(val)           bfin_writePTR(EVT1, val)
#define pEVT2                          ((void * volatile *)EVT2) /* Event Vector 2 ESR Address */
#define bfin_read_EVT2()               bfin_readPTR(EVT2)
#define bfin_write_EVT2(val)           bfin_writePTR(EVT2, val)
#define pEVT3                          ((void * volatile *)EVT3) /* Event Vector 3 ESR Address */
#define bfin_read_EVT3()               bfin_readPTR(EVT3)
#define bfin_write_EVT3(val)           bfin_writePTR(EVT3, val)
#define pEVT4                          ((void * volatile *)EVT4) /* Event Vector 4 ESR Address */
#define bfin_read_EVT4()               bfin_readPTR(EVT4)
#define bfin_write_EVT4(val)           bfin_writePTR(EVT4, val)
#define pEVT5                          ((void * volatile *)EVT5) /* Event Vector 5 ESR Address */
#define bfin_read_EVT5()               bfin_readPTR(EVT5)
#define bfin_write_EVT5(val)           bfin_writePTR(EVT5, val)
#define pEVT6                          ((void * volatile *)EVT6) /* Event Vector 6 ESR Address */
#define bfin_read_EVT6()               bfin_readPTR(EVT6)
#define bfin_write_EVT6(val)           bfin_writePTR(EVT6, val)
#define pEVT7                          ((void * volatile *)EVT7) /* Event Vector 7 ESR Address */
#define bfin_read_EVT7()               bfin_readPTR(EVT7)
#define bfin_write_EVT7(val)           bfin_writePTR(EVT7, val)
#define pEVT8                          ((void * volatile *)EVT8) /* Event Vector 8 ESR Address */
#define bfin_read_EVT8()               bfin_readPTR(EVT8)
#define bfin_write_EVT8(val)           bfin_writePTR(EVT8, val)
#define pEVT9                          ((void * volatile *)EVT9) /* Event Vector 9 ESR Address */
#define bfin_read_EVT9()               bfin_readPTR(EVT9)
#define bfin_write_EVT9(val)           bfin_writePTR(EVT9, val)
#define pEVT10                         ((void * volatile *)EVT10) /* Event Vector 10 ESR Address */
#define bfin_read_EVT10()              bfin_readPTR(EVT10)
#define bfin_write_EVT10(val)          bfin_writePTR(EVT10, val)
#define pEVT11                         ((void * volatile *)EVT11) /* Event Vector 11 ESR Address */
#define bfin_read_EVT11()              bfin_readPTR(EVT11)
#define bfin_write_EVT11(val)          bfin_writePTR(EVT11, val)
#define pEVT12                         ((void * volatile *)EVT12) /* Event Vector 12 ESR Address */
#define bfin_read_EVT12()              bfin_readPTR(EVT12)
#define bfin_write_EVT12(val)          bfin_writePTR(EVT12, val)
#define pEVT13                         ((void * volatile *)EVT13) /* Event Vector 13 ESR Address */
#define bfin_read_EVT13()              bfin_readPTR(EVT13)
#define bfin_write_EVT13(val)          bfin_writePTR(EVT13, val)
#define pEVT14                         ((void * volatile *)EVT14) /* Event Vector 14 ESR Address */
#define bfin_read_EVT14()              bfin_readPTR(EVT14)
#define bfin_write_EVT14(val)          bfin_writePTR(EVT14, val)
#define pEVT15                         ((void * volatile *)EVT15) /* Event Vector 15 ESR Address */
#define bfin_read_EVT15()              bfin_readPTR(EVT15)
#define bfin_write_EVT15(val)          bfin_writePTR(EVT15, val)
#define pILAT                          ((uint32_t volatile *)ILAT) /* Interrupt Latch Register */
#define bfin_read_ILAT()               bfin_read32(ILAT)
#define bfin_write_ILAT(val)           bfin_write32(ILAT, val)
#define pIMASK                         ((uint32_t volatile *)IMASK) /* Interrupt Mask Register */
#define bfin_read_IMASK()              bfin_read32(IMASK)
#define bfin_write_IMASK(val)          bfin_write32(IMASK, val)
#define pIPEND                         ((uint32_t volatile *)IPEND) /* Interrupt Pending Register */
#define bfin_read_IPEND()              bfin_read32(IPEND)
#define bfin_write_IPEND(val)          bfin_write32(IPEND, val)
#define pIPRIO                         ((uint32_t volatile *)IPRIO) /* Interrupt Priority Register */
#define bfin_read_IPRIO()              bfin_read32(IPRIO)
#define bfin_write_IPRIO(val)          bfin_write32(IPRIO, val)
#define pTBUFCTL                       ((uint32_t volatile *)TBUFCTL) /* Trace Buffer Control Register */
#define bfin_read_TBUFCTL()            bfin_read32(TBUFCTL)
#define bfin_write_TBUFCTL(val)        bfin_write32(TBUFCTL, val)
#define pTBUFSTAT                      ((uint32_t volatile *)TBUFSTAT) /* Trace Buffer Status Register */
#define bfin_read_TBUFSTAT()           bfin_read32(TBUFSTAT)
#define bfin_write_TBUFSTAT(val)       bfin_write32(TBUFSTAT, val)
#define pTBUF                          ((void * volatile *)TBUF) /* Trace Buffer */
#define bfin_read_TBUF()               bfin_readPTR(TBUF)
#define bfin_write_TBUF(val)           bfin_writePTR(TBUF, val)

#endif /* __BFIN_CDEF_ADSP_BF548_proc__ */
