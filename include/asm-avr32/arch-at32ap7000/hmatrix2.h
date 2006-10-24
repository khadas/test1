/*
 * Register definition for the High-speed Bus Matrix
 */
#ifndef __ASM_AVR32_HMATRIX2_H__
#define __ASM_AVR32_HMATRIX2_H__

/* HMATRIX2 register offsets */
#define HMATRIX2_MCFG0				0x0000
#define HMATRIX2_MCFG1				0x0004
#define HMATRIX2_MCFG2				0x0008
#define HMATRIX2_MCFG3				0x000c
#define HMATRIX2_MCFG4				0x0010
#define HMATRIX2_MCFG5				0x0014
#define HMATRIX2_MCFG6				0x0018
#define HMATRIX2_MCFG7				0x001c
#define HMATRIX2_MCFG8				0x0020
#define HMATRIX2_MCFG9				0x0024
#define HMATRIX2_MCFG10				0x0028
#define HMATRIX2_MCFG11				0x002c
#define HMATRIX2_MCFG12				0x0030
#define HMATRIX2_MCFG13				0x0034
#define HMATRIX2_MCFG14				0x0038
#define HMATRIX2_MCFG15				0x003c
#define HMATRIX2_SCFG0				0x0040
#define HMATRIX2_SCFG1				0x0044
#define HMATRIX2_SCFG2				0x0048
#define HMATRIX2_SCFG3				0x004c
#define HMATRIX2_SCFG4				0x0050
#define HMATRIX2_SCFG5				0x0054
#define HMATRIX2_SCFG6				0x0058
#define HMATRIX2_SCFG7				0x005c
#define HMATRIX2_SCFG8				0x0060
#define HMATRIX2_SCFG9				0x0064
#define HMATRIX2_SCFG10				0x0068
#define HMATRIX2_SCFG11				0x006c
#define HMATRIX2_SCFG12				0x0070
#define HMATRIX2_SCFG13				0x0074
#define HMATRIX2_SCFG14				0x0078
#define HMATRIX2_SCFG15				0x007c
#define HMATRIX2_PRAS0				0x0080
#define HMATRIX2_PRBS0				0x0084
#define HMATRIX2_PRAS1				0x0088
#define HMATRIX2_PRBS1				0x008c
#define HMATRIX2_PRAS2				0x0090
#define HMATRIX2_PRBS2				0x0094
#define HMATRIX2_PRAS3				0x0098
#define HMATRIX2_PRBS3				0x009c
#define HMATRIX2_PRAS4				0x00a0
#define HMATRIX2_PRBS4				0x00a4
#define HMATRIX2_PRAS5				0x00a8
#define HMATRIX2_PRBS5				0x00ac
#define HMATRIX2_PRAS6				0x00b0
#define HMATRIX2_PRBS6				0x00b4
#define HMATRIX2_PRAS7				0x00b8
#define HMATRIX2_PRBS7				0x00bc
#define HMATRIX2_PRAS8				0x00c0
#define HMATRIX2_PRBS8				0x00c4
#define HMATRIX2_PRAS9				0x00c8
#define HMATRIX2_PRBS9				0x00cc
#define HMATRIX2_PRAS10				0x00d0
#define HMATRIX2_PRBS10				0x00d4
#define HMATRIX2_PRAS11				0x00d8
#define HMATRIX2_PRBS11				0x00dc
#define HMATRIX2_PRAS12				0x00e0
#define HMATRIX2_PRBS12				0x00e4
#define HMATRIX2_PRAS13				0x00e8
#define HMATRIX2_PRBS13				0x00ec
#define HMATRIX2_PRAS14				0x00f0
#define HMATRIX2_PRBS14				0x00f4
#define HMATRIX2_PRAS15				0x00f8
#define HMATRIX2_PRBS15				0x00fc
#define HMATRIX2_MRCR				0x0100
#define HMATRIX2_SFR0				0x0110
#define HMATRIX2_SFR1				0x0114
#define HMATRIX2_SFR2				0x0118
#define HMATRIX2_SFR3				0x011c
#define HMATRIX2_SFR4				0x0120
#define HMATRIX2_SFR5				0x0124
#define HMATRIX2_SFR6				0x0128
#define HMATRIX2_SFR7				0x012c
#define HMATRIX2_SFR8				0x0130
#define HMATRIX2_SFR9				0x0134
#define HMATRIX2_SFR10				0x0138
#define HMATRIX2_SFR11				0x013c
#define HMATRIX2_SFR12				0x0140
#define HMATRIX2_SFR13				0x0144
#define HMATRIX2_SFR14				0x0148
#define HMATRIX2_SFR15				0x014c
#define HMATRIX2_VERSION			0x01fc

/* Bitfields in MCFG0 */
#define HMATRIX2_ULBT_OFFSET			0
#define HMATRIX2_ULBT_SIZE			3

/* Bitfields in SCFG0 */
#define HMATRIX2_SLOT_CYCLE_OFFSET		0
#define HMATRIX2_SLOT_CYCLE_SIZE		8
#define HMATRIX2_DEFMSTR_TYPE_OFFSET		16
#define HMATRIX2_DEFMSTR_TYPE_SIZE		2
#define HMATRIX2_FIXED_DEFMSTR_OFFSET		18
#define HMATRIX2_FIXED_DEFMSTR_SIZE		4
#define HMATRIX2_ARBT_OFFSET			24
#define HMATRIX2_ARBT_SIZE			2

/* Bitfields in PRAS0 */
#define HMATRIX2_M0PR_OFFSET			0
#define HMATRIX2_M0PR_SIZE			4
#define HMATRIX2_M1PR_OFFSET			4
#define HMATRIX2_M1PR_SIZE			4
#define HMATRIX2_M2PR_OFFSET			8
#define HMATRIX2_M2PR_SIZE			4
#define HMATRIX2_M3PR_OFFSET			12
#define HMATRIX2_M3PR_SIZE			4
#define HMATRIX2_M4PR_OFFSET			16
#define HMATRIX2_M4PR_SIZE			4
#define HMATRIX2_M5PR_OFFSET			20
#define HMATRIX2_M5PR_SIZE			4
#define HMATRIX2_M6PR_OFFSET			24
#define HMATRIX2_M6PR_SIZE			4
#define HMATRIX2_M7PR_OFFSET			28
#define HMATRIX2_M7PR_SIZE			4

/* Bitfields in PRBS0 */
#define HMATRIX2_M8PR_OFFSET			0
#define HMATRIX2_M8PR_SIZE			4
#define HMATRIX2_M9PR_OFFSET			4
#define HMATRIX2_M9PR_SIZE			4
#define HMATRIX2_M10PR_OFFSET			8
#define HMATRIX2_M10PR_SIZE			4
#define HMATRIX2_M11PR_OFFSET			12
#define HMATRIX2_M11PR_SIZE			4
#define HMATRIX2_M12PR_OFFSET			16
#define HMATRIX2_M12PR_SIZE			4
#define HMATRIX2_M13PR_OFFSET			20
#define HMATRIX2_M13PR_SIZE			4
#define HMATRIX2_M14PR_OFFSET			24
#define HMATRIX2_M14PR_SIZE			4
#define HMATRIX2_M15PR_OFFSET			28
#define HMATRIX2_M15PR_SIZE			4

/* Bitfields in MRCR */
#define HMATRIX2_RBC0_OFFSET			0
#define HMATRIX2_RBC0_SIZE			1
#define HMATRIX2_RBC1_OFFSET			1
#define HMATRIX2_RBC1_SIZE			1
#define HMATRIX2_RBC2_OFFSET			2
#define HMATRIX2_RBC2_SIZE			1
#define HMATRIX2_RBC3_OFFSET			3
#define HMATRIX2_RBC3_SIZE			1
#define HMATRIX2_RBC4_OFFSET			4
#define HMATRIX2_RBC4_SIZE			1
#define HMATRIX2_RBC5_OFFSET			5
#define HMATRIX2_RBC5_SIZE			1
#define HMATRIX2_RBC6_OFFSET			6
#define HMATRIX2_RBC6_SIZE			1
#define HMATRIX2_RBC7_OFFSET			7
#define HMATRIX2_RBC7_SIZE			1
#define HMATRIX2_RBC8_OFFSET			8
#define HMATRIX2_RBC8_SIZE			1
#define HMATRIX2_RBC9_OFFSET			9
#define HMATRIX2_RBC9_SIZE			1
#define HMATRIX2_RBC10_OFFSET			10
#define HMATRIX2_RBC10_SIZE			1
#define HMATRIX2_RBC11_OFFSET			11
#define HMATRIX2_RBC11_SIZE			1
#define HMATRIX2_RBC12_OFFSET			12
#define HMATRIX2_RBC12_SIZE			1
#define HMATRIX2_RBC13_OFFSET			13
#define HMATRIX2_RBC13_SIZE			1
#define HMATRIX2_RBC14_OFFSET			14
#define HMATRIX2_RBC14_SIZE			1
#define HMATRIX2_RBC15_OFFSET			15
#define HMATRIX2_RBC15_SIZE			1

/* Bitfields in SFR0 */
#define HMATRIX2_SFR_OFFSET			0
#define HMATRIX2_SFR_SIZE			32

/* Bitfields in SFR4 */
#define HMATRIX2_CS1A_OFFSET			1
#define HMATRIX2_CS1A_SIZE			1
#define HMATRIX2_CS3A_OFFSET			3
#define HMATRIX2_CS3A_SIZE			1
#define HMATRIX2_CS4A_OFFSET			4
#define HMATRIX2_CS4A_SIZE			1
#define HMATRIX2_CS5A_OFFSET			5
#define HMATRIX2_CS5A_SIZE			1
#define HMATRIX2_DBPUC_OFFSET			8
#define HMATRIX2_DBPUC_SIZE			1

/* Bitfields in VERSION */
#define HMATRIX2_VERSION_OFFSET			0
#define HMATRIX2_VERSION_SIZE			12
#define HMATRIX2_MFN_OFFSET			16
#define HMATRIX2_MFN_SIZE			3

/* Constants for ULBT */
#define HMATRIX2_ULBT_INFINITE			0
#define HMATRIX2_ULBT_SINGLE			1
#define HMATRIX2_ULBT_FOUR_BEAT			2
#define HMATRIX2_ULBT_SIXTEEN_BEAT		4

/* Constants for DEFMSTR_TYPE */
#define HMATRIX2_DEFMSTR_TYPE_NO_DEFAULT	0
#define HMATRIX2_DEFMSTR_TYPE_LAST_DEFAULT	1
#define HMATRIX2_DEFMSTR_TYPE_FIXED_DEFAULT	2

/* Constants for ARBT */
#define HMATRIX2_ARBT_ROUND_ROBIN		0
#define HMATRIX2_ARBT_FIXED_PRIORITY		1

/* Bit manipulation macros */
#define HMATRIX2_BIT(name)					\
	(1 << HMATRIX2_##name##_OFFSET)
#define HMATRIX2_BF(name,value)					\
	(((value) & ((1 << HMATRIX2_##name##_SIZE) - 1))	\
	 << HMATRIX2_##name##_OFFSET)
#define HMATRIX2_BFEXT(name,value)				\
	(((value) >> HMATRIX2_##name##_OFFSET)			\
	 & ((1 << HMATRIX2_##name##_SIZE) - 1))
#define HMATRIX2_BFINS(name,value,old)				\
	(((old) & ~(((1 << HMATRIX2_##name##_SIZE) - 1)		\
		    << HMATRIX2_##name##_OFFSET))		\
	 | HMATRIX2_BF(name,value))

/* Register access macros */
#define hmatrix2_readl(port,reg)				\
	readl((port)->regs + HMATRIX2_##reg)
#define hmatrix2_writel(port,reg,value)				\
	writel((value), (port)->regs + HMATRIX2_##reg)

#endif /* __ASM_AVR32_HMATRIX2_H__ */
