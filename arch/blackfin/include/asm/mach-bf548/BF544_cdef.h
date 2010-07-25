/* DO NOT EDIT THIS FILE
 * Automatically generated by generate-cdef-headers.xsl
 * DO NOT EDIT THIS FILE
 */

#ifndef __BFIN_CDEF_ADSP_BF544_proc__
#define __BFIN_CDEF_ADSP_BF544_proc__

#include "../mach-common/ADSP-EDN-core_cdef.h"

#include "ADSP-EDN-BF544-extended_cdef.h"

#define bfin_read_CHIPID()             bfin_read32(CHIPID)
#define bfin_write_CHIPID(val)         bfin_write32(CHIPID, val)
#define bfin_read_SWRST()              bfin_read16(SWRST)
#define bfin_write_SWRST(val)          bfin_write16(SWRST, val)
#define bfin_read_SYSCR()              bfin_read16(SYSCR)
#define bfin_write_SYSCR(val)          bfin_write16(SYSCR, val)
#define bfin_read_SRAM_BASE_ADDR()     bfin_readPTR(SRAM_BASE_ADDR)
#define bfin_write_SRAM_BASE_ADDR(val) bfin_writePTR(SRAM_BASE_ADDR, val)
#define bfin_read_DMEM_CONTROL()       bfin_read32(DMEM_CONTROL)
#define bfin_write_DMEM_CONTROL(val)   bfin_write32(DMEM_CONTROL, val)
#define bfin_read_DCPLB_STATUS()       bfin_read32(DCPLB_STATUS)
#define bfin_write_DCPLB_STATUS(val)   bfin_write32(DCPLB_STATUS, val)
#define bfin_read_DCPLB_FAULT_ADDR()   bfin_readPTR(DCPLB_FAULT_ADDR)
#define bfin_write_DCPLB_FAULT_ADDR(val) bfin_writePTR(DCPLB_FAULT_ADDR, val)
#define bfin_read_DCPLB_ADDR0()        bfin_readPTR(DCPLB_ADDR0)
#define bfin_write_DCPLB_ADDR0(val)    bfin_writePTR(DCPLB_ADDR0, val)
#define bfin_read_DCPLB_ADDR1()        bfin_readPTR(DCPLB_ADDR1)
#define bfin_write_DCPLB_ADDR1(val)    bfin_writePTR(DCPLB_ADDR1, val)
#define bfin_read_DCPLB_ADDR2()        bfin_readPTR(DCPLB_ADDR2)
#define bfin_write_DCPLB_ADDR2(val)    bfin_writePTR(DCPLB_ADDR2, val)
#define bfin_read_DCPLB_ADDR3()        bfin_readPTR(DCPLB_ADDR3)
#define bfin_write_DCPLB_ADDR3(val)    bfin_writePTR(DCPLB_ADDR3, val)
#define bfin_read_DCPLB_ADDR4()        bfin_readPTR(DCPLB_ADDR4)
#define bfin_write_DCPLB_ADDR4(val)    bfin_writePTR(DCPLB_ADDR4, val)
#define bfin_read_DCPLB_ADDR5()        bfin_readPTR(DCPLB_ADDR5)
#define bfin_write_DCPLB_ADDR5(val)    bfin_writePTR(DCPLB_ADDR5, val)
#define bfin_read_DCPLB_ADDR6()        bfin_readPTR(DCPLB_ADDR6)
#define bfin_write_DCPLB_ADDR6(val)    bfin_writePTR(DCPLB_ADDR6, val)
#define bfin_read_DCPLB_ADDR7()        bfin_readPTR(DCPLB_ADDR7)
#define bfin_write_DCPLB_ADDR7(val)    bfin_writePTR(DCPLB_ADDR7, val)
#define bfin_read_DCPLB_ADDR8()        bfin_readPTR(DCPLB_ADDR8)
#define bfin_write_DCPLB_ADDR8(val)    bfin_writePTR(DCPLB_ADDR8, val)
#define bfin_read_DCPLB_ADDR9()        bfin_readPTR(DCPLB_ADDR9)
#define bfin_write_DCPLB_ADDR9(val)    bfin_writePTR(DCPLB_ADDR9, val)
#define bfin_read_DCPLB_ADDR10()       bfin_readPTR(DCPLB_ADDR10)
#define bfin_write_DCPLB_ADDR10(val)   bfin_writePTR(DCPLB_ADDR10, val)
#define bfin_read_DCPLB_ADDR11()       bfin_readPTR(DCPLB_ADDR11)
#define bfin_write_DCPLB_ADDR11(val)   bfin_writePTR(DCPLB_ADDR11, val)
#define bfin_read_DCPLB_ADDR12()       bfin_readPTR(DCPLB_ADDR12)
#define bfin_write_DCPLB_ADDR12(val)   bfin_writePTR(DCPLB_ADDR12, val)
#define bfin_read_DCPLB_ADDR13()       bfin_readPTR(DCPLB_ADDR13)
#define bfin_write_DCPLB_ADDR13(val)   bfin_writePTR(DCPLB_ADDR13, val)
#define bfin_read_DCPLB_ADDR14()       bfin_readPTR(DCPLB_ADDR14)
#define bfin_write_DCPLB_ADDR14(val)   bfin_writePTR(DCPLB_ADDR14, val)
#define bfin_read_DCPLB_ADDR15()       bfin_readPTR(DCPLB_ADDR15)
#define bfin_write_DCPLB_ADDR15(val)   bfin_writePTR(DCPLB_ADDR15, val)
#define bfin_read_DCPLB_DATA0()        bfin_read32(DCPLB_DATA0)
#define bfin_write_DCPLB_DATA0(val)    bfin_write32(DCPLB_DATA0, val)
#define bfin_read_DCPLB_DATA1()        bfin_read32(DCPLB_DATA1)
#define bfin_write_DCPLB_DATA1(val)    bfin_write32(DCPLB_DATA1, val)
#define bfin_read_DCPLB_DATA2()        bfin_read32(DCPLB_DATA2)
#define bfin_write_DCPLB_DATA2(val)    bfin_write32(DCPLB_DATA2, val)
#define bfin_read_DCPLB_DATA3()        bfin_read32(DCPLB_DATA3)
#define bfin_write_DCPLB_DATA3(val)    bfin_write32(DCPLB_DATA3, val)
#define bfin_read_DCPLB_DATA4()        bfin_read32(DCPLB_DATA4)
#define bfin_write_DCPLB_DATA4(val)    bfin_write32(DCPLB_DATA4, val)
#define bfin_read_DCPLB_DATA5()        bfin_read32(DCPLB_DATA5)
#define bfin_write_DCPLB_DATA5(val)    bfin_write32(DCPLB_DATA5, val)
#define bfin_read_DCPLB_DATA6()        bfin_read32(DCPLB_DATA6)
#define bfin_write_DCPLB_DATA6(val)    bfin_write32(DCPLB_DATA6, val)
#define bfin_read_DCPLB_DATA7()        bfin_read32(DCPLB_DATA7)
#define bfin_write_DCPLB_DATA7(val)    bfin_write32(DCPLB_DATA7, val)
#define bfin_read_DCPLB_DATA8()        bfin_read32(DCPLB_DATA8)
#define bfin_write_DCPLB_DATA8(val)    bfin_write32(DCPLB_DATA8, val)
#define bfin_read_DCPLB_DATA9()        bfin_read32(DCPLB_DATA9)
#define bfin_write_DCPLB_DATA9(val)    bfin_write32(DCPLB_DATA9, val)
#define bfin_read_DCPLB_DATA10()       bfin_read32(DCPLB_DATA10)
#define bfin_write_DCPLB_DATA10(val)   bfin_write32(DCPLB_DATA10, val)
#define bfin_read_DCPLB_DATA11()       bfin_read32(DCPLB_DATA11)
#define bfin_write_DCPLB_DATA11(val)   bfin_write32(DCPLB_DATA11, val)
#define bfin_read_DCPLB_DATA12()       bfin_read32(DCPLB_DATA12)
#define bfin_write_DCPLB_DATA12(val)   bfin_write32(DCPLB_DATA12, val)
#define bfin_read_DCPLB_DATA13()       bfin_read32(DCPLB_DATA13)
#define bfin_write_DCPLB_DATA13(val)   bfin_write32(DCPLB_DATA13, val)
#define bfin_read_DCPLB_DATA14()       bfin_read32(DCPLB_DATA14)
#define bfin_write_DCPLB_DATA14(val)   bfin_write32(DCPLB_DATA14, val)
#define bfin_read_DCPLB_DATA15()       bfin_read32(DCPLB_DATA15)
#define bfin_write_DCPLB_DATA15(val)   bfin_write32(DCPLB_DATA15, val)
#define bfin_read_DTEST_COMMAND()      bfin_read32(DTEST_COMMAND)
#define bfin_write_DTEST_COMMAND(val)  bfin_write32(DTEST_COMMAND, val)
#define bfin_read_DTEST_DATA0()        bfin_read32(DTEST_DATA0)
#define bfin_write_DTEST_DATA0(val)    bfin_write32(DTEST_DATA0, val)
#define bfin_read_DTEST_DATA1()        bfin_read32(DTEST_DATA1)
#define bfin_write_DTEST_DATA1(val)    bfin_write32(DTEST_DATA1, val)
#define bfin_read_IMEM_CONTROL()       bfin_read32(IMEM_CONTROL)
#define bfin_write_IMEM_CONTROL(val)   bfin_write32(IMEM_CONTROL, val)
#define bfin_read_ICPLB_STATUS()       bfin_read32(ICPLB_STATUS)
#define bfin_write_ICPLB_STATUS(val)   bfin_write32(ICPLB_STATUS, val)
#define bfin_read_ICPLB_FAULT_ADDR()   bfin_readPTR(ICPLB_FAULT_ADDR)
#define bfin_write_ICPLB_FAULT_ADDR(val) bfin_writePTR(ICPLB_FAULT_ADDR, val)
#define bfin_read_ICPLB_ADDR0()        bfin_readPTR(ICPLB_ADDR0)
#define bfin_write_ICPLB_ADDR0(val)    bfin_writePTR(ICPLB_ADDR0, val)
#define bfin_read_ICPLB_ADDR1()        bfin_readPTR(ICPLB_ADDR1)
#define bfin_write_ICPLB_ADDR1(val)    bfin_writePTR(ICPLB_ADDR1, val)
#define bfin_read_ICPLB_ADDR2()        bfin_readPTR(ICPLB_ADDR2)
#define bfin_write_ICPLB_ADDR2(val)    bfin_writePTR(ICPLB_ADDR2, val)
#define bfin_read_ICPLB_ADDR3()        bfin_readPTR(ICPLB_ADDR3)
#define bfin_write_ICPLB_ADDR3(val)    bfin_writePTR(ICPLB_ADDR3, val)
#define bfin_read_ICPLB_ADDR4()        bfin_readPTR(ICPLB_ADDR4)
#define bfin_write_ICPLB_ADDR4(val)    bfin_writePTR(ICPLB_ADDR4, val)
#define bfin_read_ICPLB_ADDR5()        bfin_readPTR(ICPLB_ADDR5)
#define bfin_write_ICPLB_ADDR5(val)    bfin_writePTR(ICPLB_ADDR5, val)
#define bfin_read_ICPLB_ADDR6()        bfin_readPTR(ICPLB_ADDR6)
#define bfin_write_ICPLB_ADDR6(val)    bfin_writePTR(ICPLB_ADDR6, val)
#define bfin_read_ICPLB_ADDR7()        bfin_readPTR(ICPLB_ADDR7)
#define bfin_write_ICPLB_ADDR7(val)    bfin_writePTR(ICPLB_ADDR7, val)
#define bfin_read_ICPLB_ADDR8()        bfin_readPTR(ICPLB_ADDR8)
#define bfin_write_ICPLB_ADDR8(val)    bfin_writePTR(ICPLB_ADDR8, val)
#define bfin_read_ICPLB_ADDR9()        bfin_readPTR(ICPLB_ADDR9)
#define bfin_write_ICPLB_ADDR9(val)    bfin_writePTR(ICPLB_ADDR9, val)
#define bfin_read_ICPLB_ADDR10()       bfin_readPTR(ICPLB_ADDR10)
#define bfin_write_ICPLB_ADDR10(val)   bfin_writePTR(ICPLB_ADDR10, val)
#define bfin_read_ICPLB_ADDR11()       bfin_readPTR(ICPLB_ADDR11)
#define bfin_write_ICPLB_ADDR11(val)   bfin_writePTR(ICPLB_ADDR11, val)
#define bfin_read_ICPLB_ADDR12()       bfin_readPTR(ICPLB_ADDR12)
#define bfin_write_ICPLB_ADDR12(val)   bfin_writePTR(ICPLB_ADDR12, val)
#define bfin_read_ICPLB_ADDR13()       bfin_readPTR(ICPLB_ADDR13)
#define bfin_write_ICPLB_ADDR13(val)   bfin_writePTR(ICPLB_ADDR13, val)
#define bfin_read_ICPLB_ADDR14()       bfin_readPTR(ICPLB_ADDR14)
#define bfin_write_ICPLB_ADDR14(val)   bfin_writePTR(ICPLB_ADDR14, val)
#define bfin_read_ICPLB_ADDR15()       bfin_readPTR(ICPLB_ADDR15)
#define bfin_write_ICPLB_ADDR15(val)   bfin_writePTR(ICPLB_ADDR15, val)
#define bfin_read_ICPLB_DATA0()        bfin_read32(ICPLB_DATA0)
#define bfin_write_ICPLB_DATA0(val)    bfin_write32(ICPLB_DATA0, val)
#define bfin_read_ICPLB_DATA1()        bfin_read32(ICPLB_DATA1)
#define bfin_write_ICPLB_DATA1(val)    bfin_write32(ICPLB_DATA1, val)
#define bfin_read_ICPLB_DATA2()        bfin_read32(ICPLB_DATA2)
#define bfin_write_ICPLB_DATA2(val)    bfin_write32(ICPLB_DATA2, val)
#define bfin_read_ICPLB_DATA3()        bfin_read32(ICPLB_DATA3)
#define bfin_write_ICPLB_DATA3(val)    bfin_write32(ICPLB_DATA3, val)
#define bfin_read_ICPLB_DATA4()        bfin_read32(ICPLB_DATA4)
#define bfin_write_ICPLB_DATA4(val)    bfin_write32(ICPLB_DATA4, val)
#define bfin_read_ICPLB_DATA5()        bfin_read32(ICPLB_DATA5)
#define bfin_write_ICPLB_DATA5(val)    bfin_write32(ICPLB_DATA5, val)
#define bfin_read_ICPLB_DATA6()        bfin_read32(ICPLB_DATA6)
#define bfin_write_ICPLB_DATA6(val)    bfin_write32(ICPLB_DATA6, val)
#define bfin_read_ICPLB_DATA7()        bfin_read32(ICPLB_DATA7)
#define bfin_write_ICPLB_DATA7(val)    bfin_write32(ICPLB_DATA7, val)
#define bfin_read_ICPLB_DATA8()        bfin_read32(ICPLB_DATA8)
#define bfin_write_ICPLB_DATA8(val)    bfin_write32(ICPLB_DATA8, val)
#define bfin_read_ICPLB_DATA9()        bfin_read32(ICPLB_DATA9)
#define bfin_write_ICPLB_DATA9(val)    bfin_write32(ICPLB_DATA9, val)
#define bfin_read_ICPLB_DATA10()       bfin_read32(ICPLB_DATA10)
#define bfin_write_ICPLB_DATA10(val)   bfin_write32(ICPLB_DATA10, val)
#define bfin_read_ICPLB_DATA11()       bfin_read32(ICPLB_DATA11)
#define bfin_write_ICPLB_DATA11(val)   bfin_write32(ICPLB_DATA11, val)
#define bfin_read_ICPLB_DATA12()       bfin_read32(ICPLB_DATA12)
#define bfin_write_ICPLB_DATA12(val)   bfin_write32(ICPLB_DATA12, val)
#define bfin_read_ICPLB_DATA13()       bfin_read32(ICPLB_DATA13)
#define bfin_write_ICPLB_DATA13(val)   bfin_write32(ICPLB_DATA13, val)
#define bfin_read_ICPLB_DATA14()       bfin_read32(ICPLB_DATA14)
#define bfin_write_ICPLB_DATA14(val)   bfin_write32(ICPLB_DATA14, val)
#define bfin_read_ICPLB_DATA15()       bfin_read32(ICPLB_DATA15)
#define bfin_write_ICPLB_DATA15(val)   bfin_write32(ICPLB_DATA15, val)
#define bfin_read_ITEST_COMMAND()      bfin_read32(ITEST_COMMAND)
#define bfin_write_ITEST_COMMAND(val)  bfin_write32(ITEST_COMMAND, val)
#define bfin_read_ITEST_DATA0()        bfin_read32(ITEST_DATA0)
#define bfin_write_ITEST_DATA0(val)    bfin_write32(ITEST_DATA0, val)
#define bfin_read_ITEST_DATA1()        bfin_read32(ITEST_DATA1)
#define bfin_write_ITEST_DATA1(val)    bfin_write32(ITEST_DATA1, val)
#define bfin_read_EVT0()               bfin_readPTR(EVT0)
#define bfin_write_EVT0(val)           bfin_writePTR(EVT0, val)
#define bfin_read_EVT1()               bfin_readPTR(EVT1)
#define bfin_write_EVT1(val)           bfin_writePTR(EVT1, val)
#define bfin_read_EVT2()               bfin_readPTR(EVT2)
#define bfin_write_EVT2(val)           bfin_writePTR(EVT2, val)
#define bfin_read_EVT3()               bfin_readPTR(EVT3)
#define bfin_write_EVT3(val)           bfin_writePTR(EVT3, val)
#define bfin_read_EVT4()               bfin_readPTR(EVT4)
#define bfin_write_EVT4(val)           bfin_writePTR(EVT4, val)
#define bfin_read_EVT5()               bfin_readPTR(EVT5)
#define bfin_write_EVT5(val)           bfin_writePTR(EVT5, val)
#define bfin_read_EVT6()               bfin_readPTR(EVT6)
#define bfin_write_EVT6(val)           bfin_writePTR(EVT6, val)
#define bfin_read_EVT7()               bfin_readPTR(EVT7)
#define bfin_write_EVT7(val)           bfin_writePTR(EVT7, val)
#define bfin_read_EVT8()               bfin_readPTR(EVT8)
#define bfin_write_EVT8(val)           bfin_writePTR(EVT8, val)
#define bfin_read_EVT9()               bfin_readPTR(EVT9)
#define bfin_write_EVT9(val)           bfin_writePTR(EVT9, val)
#define bfin_read_EVT10()              bfin_readPTR(EVT10)
#define bfin_write_EVT10(val)          bfin_writePTR(EVT10, val)
#define bfin_read_EVT11()              bfin_readPTR(EVT11)
#define bfin_write_EVT11(val)          bfin_writePTR(EVT11, val)
#define bfin_read_EVT12()              bfin_readPTR(EVT12)
#define bfin_write_EVT12(val)          bfin_writePTR(EVT12, val)
#define bfin_read_EVT13()              bfin_readPTR(EVT13)
#define bfin_write_EVT13(val)          bfin_writePTR(EVT13, val)
#define bfin_read_EVT14()              bfin_readPTR(EVT14)
#define bfin_write_EVT14(val)          bfin_writePTR(EVT14, val)
#define bfin_read_EVT15()              bfin_readPTR(EVT15)
#define bfin_write_EVT15(val)          bfin_writePTR(EVT15, val)
#define bfin_read_ILAT()               bfin_read32(ILAT)
#define bfin_write_ILAT(val)           bfin_write32(ILAT, val)
#define bfin_read_IMASK()              bfin_read32(IMASK)
#define bfin_write_IMASK(val)          bfin_write32(IMASK, val)
#define bfin_read_IPEND()              bfin_read32(IPEND)
#define bfin_write_IPEND(val)          bfin_write32(IPEND, val)
#define bfin_read_IPRIO()              bfin_read32(IPRIO)
#define bfin_write_IPRIO(val)          bfin_write32(IPRIO, val)
#define bfin_read_TBUFCTL()            bfin_read32(TBUFCTL)
#define bfin_write_TBUFCTL(val)        bfin_write32(TBUFCTL, val)
#define bfin_read_TBUFSTAT()           bfin_read32(TBUFSTAT)
#define bfin_write_TBUFSTAT(val)       bfin_write32(TBUFSTAT, val)
#define bfin_read_TBUF()               bfin_readPTR(TBUF)
#define bfin_write_TBUF(val)           bfin_writePTR(TBUF, val)

#endif /* __BFIN_CDEF_ADSP_BF544_proc__ */
