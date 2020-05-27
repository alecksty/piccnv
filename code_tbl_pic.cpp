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
//
//======================================================================
const S_REG_TBL array_dir_pic[]=
{
	{0,"W"},
	{1,"F"},
};
const int count_dir_pic = sizeof(array_dir_pic)/sizeof(array_dir_pic[0]);

//======================================================================
//
//======================================================================
const S_REG_TBL array_reg_pic[]=
{
	{0x00,"INDF"},
	{0x01,"TMR0"},
	{0x02,"PCL"},
	{0x03,"STATUS"},
	{0x04,"FSR"},
	{0x05,"PORTA"},
	{0x06,"PORTB"},
	{0x07,"PORTC"},
	{0x08,"PORTD"},
	{0x09,"PORTE"},
};
const int count_reg_pic = sizeof(array_reg_pic)/sizeof(array_reg_pic[0]);

//======================================================================
//	PIC16F630/676
//======================================================================
const S_CODE_TBL array_code_pic[]=
{
	//===================================================================
	//code		,cod_msk	,d_msk		,f_msk,		b_msk,		k_msk,		keyword, 	format
	//===================================================================
	{0x000		,0xfff,		0,			0,			0,			0,			"NOP",		"%s"},
	{0x002		,0xfff,		0,			0,			0,			0,			"OPTION",	"%s"},
	{0x003		,0xfff,		0,			0,			0,			0,			"SLEEP",	"%s"},
	{0x004		,0xfff,		0,			0,			0,			0,			"CLRWDT",	"%s"},
	{0x040		,0xfff,		0,			0,			0,			0,			"CLRW",		"%s"},

	{0x160		,0xfe0,		0,			0x01f,		0,			0,			"CLRF",		"%s %s"},
	{0x020		,0xfe0,		0,			0x01f,		0,			0,			"MOVWF",	"%s %s"},

	{0x1c0		,0xfc0,		0x020,		0x01f,		0,			0,			"ADDWF",	"%s %s,%s"},
	{0x140		,0xfc0,		0x020,		0x01f,		0,			0,			"ANDWF",	"%s %s,%s"},
	{0x240		,0xfc0,		0x020,		0x01f,		0,			0,			"COMF",		"%s %s,%s"},
	{0x0c0		,0xfc0,		0x020,		0x01f,		0,			0,			"DECF",		"%s %s,%s"},
	{0x2c0		,0xfc0,		0x020,		0x01f,		0,			0,			"DECFSZ",	"%s %s,%s"},
	{0x280		,0xfc0,		0x020,		0x01f,		0,			0,			"INCF",		"%s %s,%s"},
	{0x3c0		,0xfc0,		0x020,		0x01f,		0,			0,			"INCFSZ",	"%s %s,%s"},
	{0x100		,0xfc0,		0x020,		0x01f,		0,			0,			"IORWF",	"%s %s,%s"},
	{0x200		,0xfc0,		0x020,		0x01f,		0,			0,			"MOVF",		"%s %s %s"},	
	{0x340		,0xfc0,		0x020,		0x01f,		0,			0,			"RLF",		"%s %s,%s"},
	{0x300		,0xfc0,		0x020,		0x01f,		0,			0,			"RRF",		"%s %s,%s"},
	{0x080		,0xfc0,		0x020,		0x01f,		0,			0,			"SUBWF",	"%s %s,%s"},
	{0x380		,0xfc0,		0x020,		0x01f,		0,			0,			"SWAPF",	"%s %s,%s"},
	{0x180		,0xfc0,		0x020,		0x01f,		0,			0,			"XORWF",	"%s %s,%s"},

	//===================================================================
	//	bits functions
	//===================================================================
	{0x400		,0xf00,		0,			0x01f,		0x0e0,		0,			"BCF",		"%s %s,%s"},
	{0x500		,0xf00,		0,			0x01f,		0x0e0,		0,			"BSF",		"%s %s,%s"},
	{0x600		,0xf00,		0,			0x01f,		0x0e0,		0,			"BTFSC",	"%s %s,%s"},
	{0x700		,0xf00,		0,			0x01f,		0x0e0,		0,			"BTFSS",	"%s %s,%s"},

	//===================================================================
	//	number pcode
	//===================================================================
	{0x800		,0xf00,		0,			0,			0,			0x0ff,		"ADDLW",	"%s %s"},
	{0x800		,0xf00,		0,			0,			0,			0x0ff,		"SUBLW",	"%s %s"},

	{0x800		,0xf00,		0,			0,			0,			0x0ff,		"RETLW",	"%s %s"},
	{0x900		,0xf00,		0,			0,			0,			0x0ff,		"CALL",		"%s %s"},
	{0xa00		,0xe00,		0,			0,			0,			0x1ff,		"GOTO",		"%s %s"},

	{0xd00		,0xf00,		0,			0,			0,			0x0ff,		"IORLW",	"%s %s"},
	{0xc00		,0xf00,		0,			0,			0,			0x0ff,		"MOVLW",	"%s %s"},
	{0xe00		,0xf00,		0,			0,			0,			0x0ff,		"ANDLW",	"%s %s"},
	{0xf00		,0xf00,		0,			0,			0,			0x0ff,		"XORLW",	"%s %s"},

	{0x000		,0xff8,		0,			0x007,		0,			0,			"TRIS",		"%s %s"},

	{0x800		,0xf00,		0,			0,			0,			0,			"RETURN",	"%s"},
	{0x800		,0xf00,		0,			0,			0,			0,			"RETFIE",	"%s"},
};

const int count_code_pic = sizeof(array_code_pic)/sizeof(array_code_pic[0]);

//======================================================================
//
//======================================================================
const S_CNV_TBL array_cnv_pic[]=
{
	//==============================
	//CODE			KEYWORD
	//==============================
	{COD_NAME,		"-PIC-" },
	
	{COD_BCR,		"BCF"},
	{COD_BSR,		"BSF"},
	{COD_BTRSC,		"BTFSC"},
	{COD_BTRSS,		"BTFSS"},
	{COD_NOP,		"NOP"},
	{COD_CLRWDT,	"CLRWDT"},
	{COD_OPTION,	"OPTION"},
	{COD_SLEEP,		"SLEEP"},
	{COD_INT,		"-"},
	{COD_DAA,		"-"},
	{COD_DAS,		"-"},
	{COD_RETURN,	"RETURN"},
	{COD_RETFIE,	"RETFIE"},
	{COD_CLRA,		"-"},
	{COD_IOST,		"TRIS"},
	{COD_CLRR,		"CLRF"},
	{COD_MOVAR,		"MOVWF"},
	{COD_MOVR,		"MOVF"},
	{COD_DECR,		"DECF"},
	{COD_DECRSZ,	"DECFSZ"},
	{COD_INCR,		"INCF"},
	{COD_INCRSZ,	"INCFSZ"},
	{COD_ADDAR,		"ADDWF"},
	{COD_SUBAR,		"SUBWF"},
	{COD_ADCAR,		"-"},
	{COD_SBCAR,		"-"},
	{COD_ANDAR,		"ANDWF"},
	{COD_IORAR,		"IORWF"},
	{COD_XORAR,		"XORWF"},
	{COD_COMR,		"COMF"},
	{COD_RRR,		"RRF"},
	{COD_RLR,		"RLF"},
	{COD_SWAPR,		"SWAPF"},
	{COD_MOVIA,		"MOVLW"},
	{COD_ADDIA,		"ADDLW"},
	{COD_SUBIA,		"SUBLW"},
	{COD_ANDIA,		"ANDLW"},
	{COD_IORIA,		"IORLW"},
	{COD_XORIA,		"XORLW"},
	{COD_RETIA,		"RETLW"},
	{COD_CALL,		"CALL"},
	{COD_GOTO,		"GOTO"},
};

const int count_cnv_pic = sizeof(array_cnv_pic)/sizeof(array_cnv_pic[0]);

//======================================================================
//	虚拟指令(编译器生成的中间代码)
//======================================================================
const S_VIRTUAL_TBL array_vir_pic[]=
{
	{COD_CALL		,"FCALL"	,"CALL"		,NULL,NULL},
	{COD_CALL		,"LCALL"	,"CALL"		,NULL,NULL},

	{COD_GOTO		,"LJMP"		,"GOTO"		,NULL,NULL},
	{COD_GOTO		,"FJMP"		,"GOTO"		,NULL,NULL},

	{COD_BCR		,"CLRC"		,"BCF"		,"STATUS","C"},
	{COD_BCR		,"CLRZ"		,"BCF"		,"STATUS","Z"},
	
	{COD_BTRSS		,"SKIPZ"	,"BTFSS"	,"STATUS","Z"},
	{COD_BTRSC		,"SKIPNZ"	,"BTFSC"	,"STATUS","Z"},
	{COD_BTRSS		,"SKIPC"	,"BTFSS"	,"STATUS","C"},
	{COD_BTRSC		,"SKIPNC"	,"BTFSC"	,"STATUS","C"},
};

const int count_vir_pic = sizeof(array_vir_pic)/sizeof(array_vir_pic[0]);

//======================================================================
//		文件头
//======================================================================
const char *pre_text_pic = 
	"\n"
	"#define			C		0 \n"
	"#define			DC		1\n"
	"#define			Z		2\n"
	"#define			PF		3\n"
	"#define			TF		4\n"
	"\n"
	"#define			F		1\n"
	"#define			W		0\n"
	"\n"
	"INDF			set		0x00\n"
	"TMR0			set		0x01\n"
	"PCL			set		0x02\n"
	"STATUS			set		0x03\n"
	"FSR			set		0x04\n"
	"PORTA			set		0x05\n"
	"PORTB			set		0x06\n"
	"PORTC			set		0x07\n"
	"PCON			set		0x08\n"
	"WUCON			set		0x09\n"
	"\n"
	"PCHBUF			set		0x0A\n"
	"PDCON			set		0x0B\n"
	"ODCON			set		0x0C\n"
	"PHCON			set		0x0D\n"
	"INTEN			set		0x0E\n"
	"INTFLAG		set		0x0F\n"
	"\n"
	"ACC_TEMP		set		0x03D\n"
	"STATUS_TEMP	set		0x03E\n"
	"FSR_TEMP		set		0x03F\n";

