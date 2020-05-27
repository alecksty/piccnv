//=====================================================================
//	W 	:工作寄存器 (累加器)
//
//	f 	:寄存器文件地址 (0x00 到 0x1F).
//	b 	:8 位文件寄存器中位的地址.
//	k 	:立即数字段,常数或标号.
//	d 	:选择目标寄存器:
//		d = 0 结果存储至 W.
//		d = 1 结果存储至文件寄存器 f.
//		默认值为 d = 1.
//
//======================================================================
#include "stdafx.h"

//======================================================================
//	DIR
//======================================================================
const S_REG_TBL array_dir_atw[]=
{
	{0,"A"},
	{1,"R"},
};
const int count_dir_atw = sizeof(array_dir_atw)/sizeof(array_dir_atw[0]);

//======================================================================
//	REG
//======================================================================
const S_REG_TBL array_reg_atw[]=
{
	{0x00,"INDF"},
	{0x01,"TMR0"},
	{0x02,"PCL"},
	{0x03,"STATUS"},
	{0x04,"FSR"},
	{0x05,"PORTA"},
	{0x06,"PORTB"},
	{0x07,"PORTC"},
	{0x08,"PCON"},
	{0x09,"WUCON"},
	{0x0A,"PCHBUF"},
	{0x0B,"PDCON"},
	{0x0C,"ODCON"},
	{0x0D,"PHCON"},
	{0x0E,"INTEN"},
	{0x0F,"INTFLAG"},

	{0x3D,"ACC_TEMP"},
	{0x3E,"STATUS_TEMP"},
	{0x3F,"FSR_TEMP"},

	//10h~3Fh General Purpose Registers.
};
const int count_reg_atw = sizeof(array_reg_atw)/sizeof(array_reg_atw[0]);

//======================================================================
//	这个表格可能是错误的(机器码没有对照表)
//======================================================================
const S_CODE_TBL array_code_atw[]=
{
	//===================================================================
	//code		,cod_msk	,d_msk		,f_msk,		b_msk,		k_msk,		keyword, 	format
	//===================================================================
	{0x0000,	0xfff,		0,			0,			0,			0,			"NOP",		"%s"},

	{0x0001,	0xfff,		0,			0,			0,			0,			"DAA",		"%s"},			// EXT
	{0x0001,	0xfff,		0,			0,			0,			0,			"DAS",		"%s"},			// EXT
	
	{0x0004,	0xfff,		0,			0,			0,			0,			"CLRWDT",	"%s"},
	{0x0002,	0xfff,		0,			0,			0,			0,			"OPTION",	"%s"},
	{0x0003,	0xfff,		0,			0,			0,			0,			"SLEEP",	"%s"},

	{0x1e01,	0x1fff,		0,			0,			0,			0,			"INT",		"%s"},				// EXT
	{0x0010,	0x1fff,		0,			0x00f,		0,			0,			"ENI",		"%s %s"},		// EXT
	{0x0011,	0x1fff,		0,			0x00f,		0,			0,			"DISI",		"%s %s"},		// EXT
	{0x0012,	0x1fff,		0,			0,			0,			0,			"RETURN",	"%s %s"},		// EXT
	{0x0013,	0x1fff,		0,			0,			0,			0x00f,		"RETIA",	"%s %s"},		// EXT
	{0x0080,	0x1fff,		0,			0,			0,			0,			"CLRA",		"%s %s"},			// EXT

	{0x0160		,0xfe0,		0,			0x01f,		0,			0,			"CLRR",		"%s %s"},
	{0x0020		,0xfe0,		0,			0x01f,		0,			0,			"MOVAR",	"%s %s"},

	{0x01c0		,0xfc0,		0x020,		0,			0,			0xff,		"ADDIA",	"%s %s,%s"},	//EXT
	{0x01c0		,0xfc0,		0x020,		0,			0,			0xff,		"SUBIA",	"%s %s,%s"},	//EXT
	{0x01c0		,0xfc0,		0x020,		0x01f,		0,			0,			"ADCAR",	"%s %s,%s"},	//EXT
	{0x01c0		,0xfc0,		0x020,		0x01f,		0,			0,			"SBCAR",	"%s %s,%s"},	//EXT

	{0x01c0		,0xfc0,		0x020,		0x01f,		0,			0,			"ADDAR",	"%s %s,%s"},
	{0x0140		,0xfc0,		0x020,		0x01f,		0,			0,			"ANDAR",	"%s %s,%s"},
	{0x0240		,0xfc0,		0x020,		0x01f,		0,			0,			"COMR",		"%s %s,%s"},
	{0x00c0		,0xfc0,		0x020,		0x01f,		0,			0,			"DECR",		"%s %s,%s"},
	{0x02c0		,0xfc0,		0x020,		0x01f,		0,			0,			"DECRSZ",	"%s %s,%s"},
	{0x0280		,0xfc0,		0x020,		0x01f,		0,			0,			"INCR",		"%s %s,%s"},
	{0x03c0		,0xfc0,		0x020,		0x01f,		0,			0,			"INCRSZ",	"%s %s,%s"},
	{0x0100		,0xfc0,		0x020,		0x01f,		0,			0,			"IORAR",	"%s %s,%s"},
	{0x0200		,0xfc0,		0x020,		0x01f,		0,			0,			"MOVR",		"%s %s %s"},
	{0x0340		,0xfc0,		0x020,		0x01f,		0,			0,			"RRR",		"%s %s,%s"},
	{0x0300		,0xfc0,		0x020,		0x01f,		0,			0,			"RLR",		"%s %s,%s"},
	{0x0080		,0xfc0,		0x020,		0x01f,		0,			0,			"SUBAR",	"%s %s,%s"},
	{0x0380		,0xfc0,		0x020,		0x01f,		0,			0,			"SWAPR",	"%s %s,%s"},
	{0x0180		,0xfc0,		0x020,		0x01f,		0,			0,			"XORAR",	"%s %s,%s"},

	//===================================================================
	//	bits functions
	//===================================================================
	{0x0400		,0xf00,		0,			0x01f,		0x0e0,		0,			"BCR",		"%s %s,%s"},
	{0x0500		,0xf00,		0,			0x01f,		0x0e0,		0,			"BSR",		"%s %s,%s"},
	{0x0600		,0xf00,		0,			0x01f,		0x0e0,		0,			"BTRSC",	"%s %s,%s"},
	{0x0700		,0xf00,		0,			0x01f,		0x0e0,		0,			"BTRSS",	"%s %s,%s"},

	//===================================================================
	//	number pcode
	//===================================================================
	{0x0e00		,0xf00,		0,			0,			0,			0x0ff,		"ANDIA",	"%s %s"},
	{0x0d00		,0xf00,		0,			0,			0,			0x0ff,		"IORIA",	"%s %s"},
	{0x0c00		,0xf00,		0,			0,			0,			0x0ff,		"MOVIA",	"%s %s"},
	{0x0800		,0xf00,		0,			0,			0,			0x0ff,		"RETIA",	"%s %s"},
	{0x0f00		,0xf00,		0,			0,			0,			0x0ff,		"XORIA",	"%s %s"},
	{0x0900		,0xf00,		0,			0,			0,			0x0ff,		"CALL",		"%s %s"},
	{0x0a00		,0xe00,		0,			0,			0,			0x1ff,		"GOTO",	    "%s %s"},
	{0x0000		,0xff8,		0,			0x007,		0,			0,			"IOST",		"%s %s"},
};

const int count_code_atw = sizeof(array_code_atw)/sizeof(array_code_atw[0]);

//======================================================================
//	指令表
//======================================================================
const S_CNV_TBL array_cnv_atw[]=
{
	//==============================
	//CODE			KEYWORD
	//==============================
	{COD_NAME,		"-ATW-"},

	{COD_BCR,			"BCR"},
	{COD_BSR,			"BSR"},
	{COD_BTRSC,		"BTRSC"},
	{COD_BTRSS,		"BTRSS"},
	{COD_NOP,			"NOP"},
	{COD_CLRWDT,	"CLRWDT"},
	{COD_OPTION,		"OPTION"},
	{COD_SLEEP,			"SLEEP"},
	
	{COD_INT,			"INT"},
	{COD_DAA,			"DAA"},
	{COD_DAS,			"DAS"},
	{COD_RETURN,		"RETURN"},
	{COD_RETFIE,		"RETIA"},
	{COD_CLRA,			"CLRA"},
	{COD_IOST,			"IOST"},

	{COD_CLRR,			"CLRR"},
	{COD_MOVAR,		"MOVAR"},
	{COD_MOVR,		"MOVR"},
	{COD_DECR,			"DECR"},
	{COD_DECRSZ,		"DECRSZ"},
	{COD_INCR,			"INCR"},
	{COD_INCRSZ,		"INCRSZ"},
	{COD_ADDAR,		"ADDAR"},
	{COD_SUBAR,		"SUBAR"},
	{COD_ADCAR,		"ADCAR"},
	{COD_SBCAR,		"SBCAR"},
	{COD_ANDAR,		"ANDAR"},
	{COD_IORAR,		"IORAR"},
	{COD_XORAR,		"XORAR"},
	{COD_COMR,		"COMR"},
	{COD_RRR,			"RRR"},
	{COD_RLR,			"RLR"},
	{COD_SWAPR,		"SWAPR"},
	{COD_MOVIA,		"MOVIA"},
	{COD_ADDIA,		"ADDIA"},
	{COD_SUBIA,		"SUBIA"},
	{COD_ANDIA,		"ANDIA"},
	{COD_IORIA,			"IORIA"},
	{COD_XORIA,		"XORIA"},
	{COD_RETIA,			"RETIA"},
	{COD_CALL,			"CALL"},
	{COD_GOTO,		"GOTO"},
};

const int count_cnv_atw = sizeof(array_cnv_atw)/sizeof(array_cnv_atw[0]);

//======================================================================
//	文件头
//======================================================================
const char *pre_text_atw = 
	";======================================================\n"
	";= PIC LIST CONVERT TOOLS VERIOSN 1.12(R).\n"
	";=                                  (" __DATE__ ")|(" __TIME__ ")\n"
	";=                                  ---Aleck.Shi\n"
	";======================================================\n"
	"#define              C         0\n"
	"#define              HC        1\n"
	"#define              Z         2\n"
	"#define              PF        3\n"
	"#define              TF        4\n"
	";======================================================\n"
	"#define              A         0\n"
	"#define              R         1\n"	
	";======================================================\n";

//======================================================================
//	宏替换
//======================================================================
const S_CODE_BASE array_m_clrr_trisa[]		= {{NULL,"MOVIA"	,"0"	,NULL},{NULL,"IOST","PORTA",NULL}};
const S_CODE_BASE array_m_clrr_trisb[]		= {{NULL,"MOVIA"	,"0"	,NULL},{NULL,"IOST","PORTB",NULL}};
const S_CODE_BASE array_m_movar_trisa[]		= {{NULL,"IOST"		,"PORTA",NULL},};
const S_CODE_BASE array_m_movar_trisb[]		= {{NULL,"IOST"		,"PORTB",NULL},};
const S_CODE_BASE array_m_movar_option[]  	= {{NULL,"OPTION"	,NULL	,NULL},};

const S_MACRO_TBL array_macro_atw[]=
{
	//=======================================================
	//	替换表
	//=======================================================
	//	CLRR TRISA  -->		MOVIA 0
	//									IOST PORTA
	//
	{{0,"CLRR","TRISA",NULL},2,array_m_clrr_trisa},

	//	CLRR TRISB  -->		MOVIA 0
	//									IOST PORTB
	//
	{{0,"CLRR","TRISB",NULL},2,array_m_clrr_trisb},

	//	MOVAR TRISA	---> IOST PORTA
	{{0,"MOVAR","TRISA",NULL},1,array_m_movar_trisa},

	//	MOVAR TRISB	---> IOST PORTA
	{{0,"MOVAR","TRISB",NULL},1,array_m_movar_trisb},

	//	MOVAR OPTION ---> OPTION
	{{0,"MOVAR","OPTION",NULL},1,array_m_movar_option},
};

const int count_macro_atw = sizeof(array_macro_atw)/sizeof(array_macro_atw[0]);

//======================================================================
//	头部代码
//======================================================================
const S_CODE_BASE array_prefix_atw[]    = 
{
	{NULL			,"ORG"		,"00h"				,NULL},
	{NULL			,"GOTO"		,"initialization"	,NULL},
	{NULL			,"NOP"		,NULL				,NULL},
	
	{NULL			,"ORG"		,"08h"				,NULL},
	{NULL			,"GOTO"		,"interrput"		,NULL},
	{NULL			,"NOP"		,NULL				,NULL},
};
const int count_prefix_atw = sizeof(array_prefix_atw)/sizeof(array_prefix_atw[0]);

//======================================================================
//	尾部代码
//======================================================================
const S_CODE_BASE array_interrupt_atw[]    = 
{
	{"interrput"	,NULL			,NULL			,NULL},
	{NULL			,"MOVAR"		,"ACC_TEMP"		,NULL},
	{NULL			,"SWAPR"		,"STATUS"		,"A"},
	{NULL			,"MOVAR"		,"STATUS_TEMP"	,NULL},
	{NULL			,"MOVR"			,"FSR"			,"A"},
	{NULL			,"MOVAR"		,"FSR_TEMP"		,NULL},

	{"int_tim0"		,NULL			,NULL			,NULL},
	{NULL			,"BTRSS"		,"INTFLAG"		,"0"},	// TMR0
	{NULL			,"GOTO"			,"int_pin"		,NULL},
	{NULL			,"NOP"			,NULL			,NULL},
	{NULL			,"CALL"			,"_Interrupt_T0"	,NULL},

	{"int_pin"		,NULL			,NULL			,NULL},
	{NULL			,"BTRSS"		,"INTFLAG"		,"1"},	// PIN
	{NULL			,"GOTO"			,"int_ext"		,NULL},
	{NULL			,"NOP"			,NULL			,NULL},
	{NULL			,"CALL"			,"_Interrupt_PB"	,NULL},

	{"int_ext"		,NULL			,NULL			,NULL},
	{NULL			,"BTRSS"		,"INTFLAG"		,"2"},	// EXT
	{NULL			,"GOTO"			,"int_end"		,NULL},
	{NULL			,"NOP"			,NULL			,NULL},
	{NULL			,"CALL"			,"_Interrupt_Ex"	,NULL},

	{"int_end"		,NULL			,NULL			,NULL},
	{NULL			,"CLRR"			,"INTFLAG"		,NULL},
	{NULL			,"MOVR"			,"FSR_TEMP"		,"A"},
	{NULL			,"MOVAR"		,"FSR"			,NULL},
	{NULL			,"SWAPR"		,"STATUS_TEMP"	,"A"},
	{NULL			,"MOVAR"		,"STATUS"		,NULL},
	{NULL			,"SWAPR"		,"ACC_TEMP"		,"R"},
	{NULL			,"SWAPR"		,"ACC_TEMP"		,"A"},
	{NULL			,"RETFIE"		,NULL			,NULL},
	{"end_of_interrput",NULL		,NULL			,NULL},
};
const int count_interrupt_atw = sizeof(array_interrupt_atw)/sizeof(array_interrupt_atw[0]);

