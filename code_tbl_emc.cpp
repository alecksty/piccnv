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
const S_REG_TBL array_dir_emc[]=
{
	{0,"A"},
	{1,"R"},
};
const int count_dir_emc = sizeof(array_dir_emc)/sizeof(array_dir_emc[0]);

//======================================================================
//
//======================================================================
const S_REG_TBL array_reg_emc[]=
{
	{0x00,"R0"},
	{0x01,"TCC"},
	{0x02,"PC"},
	{0x03,"STATUS"},
	{0x04,"RSR"},
	{0x05,"PORT5"},
	{0x06,"PORT6"},
	{0x07,"PORT7"},
	{0x08,"PORT8"},
	{0x09,"PORT9"},
	{0x0F,"RF"},

	{0x0B,"IOCB"},// Pull down
	{0x0C,"IOCC"},// Open Daring
	{0x0D,"IOCD"},// Pull high
	{0x0E,"IOCE"}, // WDT COntrol
	{0x0F,"IOCF"}, // Inerrupt

};
const int count_reg_emc = sizeof(array_reg_emc)/sizeof(array_reg_emc[0]);

//======================================================================
//
//======================================================================
const S_CODE_TBL array_code_emc[]=
{
	//===================================================================
	//code		,cod_msk	,d_msk		,f_msk,		b_msk,		k_msk,		keyword, 	format
	//===================================================================
	{0x0000,	0x1fff,		0,			0,			0,			0,			"NOP",		"%s"},
	{0x0001,	0x1fff,		0,			0,			0,			0,			"DAA",		"%s"},
	{0x0002,	0x1fff,		0,			0,			0,			0,			"CONTW",	"%s"},
	{0x0003,	0x1fff,		0,			0,			0,			0,			"SLEP",		"%s"},
	{0x0004,	0x1fff,		0,			0,			0,			0,			"WDTC",		"%s"},
	{0x0000,	0x1ff0,		0,			0x00f,		0,			0,			"IOWR",		"%s %s"},
	{0x0010,	0x1fff,		0,			0x00f,		0,			0,			"ENI",		"%s %s"},
	{0x0011,	0x1fff,		0,			0x00f,		0,			0,			"DISI",		"%s %s"},
	{0x0012,	0x1fff,		0,			0x00f,		0,			0,			"RET",		"%s %s"},
	{0x0013,	0x1fff,		0,			0x00f,		0,			0,			"RETI",		"%s %s"},
	{0x0014,	0x1fff,		0,			0,			0,			0,			"CONTR",	"%s %s"},
	{0x0010,	0x1fff,		0,			0x00f,		0,			0,			"IOR",		"%s %s"},
	{0x0040,	0x1fc0,		0x040,		0x03f,		0,			0,			"MOV",		"%s %s,A"},
	{0x0080,	0x1fff,		0,			0,			0,			0,			"CLRA",		"%s %s"},	
	{0x00c0,	0x1fc0,		0,			0x03f,		0,			0,			"CLR",		"%s %s"},

	//===================================================================
	//	d = 1:R->A | d = 0:A->R
	//===================================================================
	{0x0100		,0x1fc0,	0x040,		0x03f,		0,			0,			"SUB",		"%s %s,%s"},
	{0x0180		,0x1fc0,	0x040,		0x03f,		0,			0,			"DEC",		"%s %s"},
	{0x0200		,0x1fc0,	0x040,		0x03f,		0,			0,			"OR",		"%s %s,%s"},
	{0x0280		,0x1fc0,	0x040,		0x03f,		0,			0,			"AND",		"%s %s,%s"},
	{0x0300		,0x1fc0,	0x040,		0x03f,		0,			0,			"XOR",		"%s %s,%s"},
	{0x0380		,0x1fc0,	0x040,		0x03f,		0,			0,			"ADD",		"%s %s,%s"},
	{0x0400		,0x1fc0,	0x040,		0x03f,		0,			0,			"MOV",		"%s %s,%s"},
	{0x0480		,0x1fc0,	0x040,		0x03f,		0,			0,			"COM",		"%s %s"},
	{0x0500		,0x1fc0,	0x040,		0x03f,		0,			0,			"INC",		"%s %s"},
	{0x0580		,0x1fc0,	0x040,		0x03f,		0,			0,			"DJZ",		"%s %s"},
	{0x0600		,0x1fc0,	0x040,		0x03f,		0,			0,			"RRC",		"%s %s"},
	{0x0680		,0x1fc0,	0x040,		0x03f,		0,			0,			"RLC",		"%s %s"},
	{0x0700		,0x1fc0,	0x040,		0x03f,		0,			0,			"SWAP",		"%s %s"},
	{0x0780		,0x1fc0,	0x040,		0x03f,		0,			0,			"JZ",		"%s %s"},

	//===================================================================
	//	xxx R,b
	//===================================================================
	{0x0800		,0x1e00,		0,		0x03f,		0x01c0,		0,			"BC",		"%s %s,%s"},
	{0x0900		,0x1e00,		0,		0x03f,		0x01c0,		0,			"BS",		"%s %s,%s"},
	{0x0a00		,0x1e00,		0,		0x03f,		0x01c0,		0,			"JBC",		"%s %s,%s"},
	{0x0b00		,0x1e00,		0,		0x03f,		0x01c0,		0,			"JBS",		"%s %s,%s"},

	//===================================================================
	//	
	//===================================================================
	{0x1000		,0x1c00,		0,		0,			0,			0x3ff,		"CALL",		"%s %s"},
	{0x1400		,0x1c00,		0,		0,			0,			0x3ff,		"JMP",		"%s %s"},
	{0x1800		,0x1f00,		0,		0,			0,			0x0ff,		"MOV",		"%s A,%s"},
	{0x1900		,0x1f00,		0,		0,			0,			0x0ff,		"OR",		"%s A,%s"},
	{0x1a00		,0x1f00,		0,		0,			0,			0x0ff,		"AND",		"%s A,%s"},
	{0x1b00		,0x1f00,		0,		0,			0,			0x0ff,		"XOR",		"%s A,%s"},
	{0x1c00		,0x1f00,		0,		0,			0,			0x0ff,		"RETL",		"%s %s"},
	{0x1d00		,0x1f00,		0,		0,			0,			0x0ff,		"SUB",		"%s A,%s"},
	{0x1e01		,0x1fff,		0,		0,			0,			0,			"INT",		"%s"},
	{0x1f00		,0x1f00,		0,		0,			0,			0x0ff,		"ADD",		"%s A,%s"},
};

const int count_code_emc = sizeof(array_code_emc)/sizeof(array_code_emc[0]);

//======================================================================
//
//======================================================================
const S_CNV_TBL array_cnv_emc[] =
{
	//==============================
	//CODE			KEYWORD
	//==============================
	{COD_NAME,		"-EMC-"},

	{COD_BCR,		"BC"},
	{COD_BSR,		"BS"},
	{COD_BTRSC,		"JBC"},
	{COD_BTRSS,		"JBS"},
	{COD_NOP,		"NOP"},
	{COD_CLRWDT,	"WDTC"},
	{COD_OPTION,	"CONTW"},
	{COD_SLEEP,		"SLEP"},

	{COD_INT,		"INT"},
	{COD_DAA,		"-"},
	{COD_DAS,		"-"},
	{COD_RETURN,	"RET"},
	{COD_RETFIE,	"RETI"},
	{COD_CLRA,		"CLRA"},
	{COD_IOST,		"IOW"},

	{COD_CLRR,		"CLR"},
	{COD_MOVAR,		"MOV"},
	{COD_MOVR,		"MOV"},
	{COD_DECR,		"DEC"},		// DIR
	{COD_DECRSZ,	"DJZ"},		// DIR
	{COD_INCR,		"INC"},		// DIR
	{COD_INCRSZ,	"JZ"},
	{COD_ADDAR,		"ADD"},		// DIR
	{COD_SUBAR,		"SUB"},		// DIR
	{COD_ADCAR,		"-"},
	{COD_SBCAR,		"-"},
	{COD_ANDAR,		"AND"},		// DIR
	{COD_IORAR,		"OR"},		// DIR		
	{COD_XORAR,		"XOR"},		// DIR
	{COD_COMR,		"COM"},
	{COD_RRR,		"RRC"},
	{COD_RLR,		"RLC"},
	{COD_SWAPR,		"SWAPA"},	// DIR
	{COD_MOVIA,		"MOV"},
	{COD_ADDIA,		"ADD"},
	{COD_SUBIA,		"SUB"},
	{COD_ANDIA,		"AND"},
	{COD_IORIA,		"OR"},
	{COD_XORIA,		"XOR"},
	{COD_RETIA,		"RETIL"},
	{COD_CALL,		"CALL"},
	{COD_GOTO,		"JMP"},

};

const int count_cnv_emc = sizeof(array_cnv_emc)/sizeof(array_cnv_emc[0]);

//======================================================================
//
//======================================================================
const char *pre_text_emc = 
	";======================================================\n"
	"#define		C		0 \n"
	"#define		HC		1\n"
	"#define		Z		2\n"
	"#define		PF		3\n"
	"#define		TF		4\n"
	";======================================================\n"
	"#define		R		1\n"
	"#define		A		0\n"
	";======================================================\n"
	"INDF			EQU		00H\n"
	"TMR0			EQU		01H\n"
	"PCL			EQU		02H\n"
	"STATUS			EQU		03H\n"
	"FSR			EQU		04H\n"
	"PORTA			EQU		05H\n"
	"PORTB			EQU		06H\n"
	"PCON			EQU		08H\n"
	"WUCON			EQU		09H\n"
	"PCHBUF			EQU		0AH\n"
	"PDCON			EQU		0BH\n"
	"ODCON			EQU		0CH\n"
	"PHCON			EQU		0DH\n"
	"INTEN			EQU		0EH\n"
	"INTFLAG		EQU		0FH\n"
	";======================================================\n"
	"ACC_TEMP		EQU		03DH\n"
	"STATUS_TEMP	EQU		03EH\n"
	"FSR_TEMP		EQU		03FH\n"
	";======================================================\n"
	;

