#ifndef CODE_TBL_H_
#define CODE_TBL_H_

//==================================================
//	语言
//==================================================
typedef enum emLang
{
	LANG_UNKNOW = -1,
	//	microchip
	LANG_PIC = 0,
	//	emc
	LANG_EMC ,
	//	atw
	LANG_ATW ,

	LANG_MAX,

}E_LANG;

//==================================================
//	段类型:	CODE/STRING/BANK0/COMMON
//==================================================
typedef enum emBank
{
	//	代码
	BANK_CODE = 0,
	//	字符
	BANK_STRING,
	//	数据
	BANK_BANK ,
	//	堆栈
	BANK_COMMON ,
	//	入口
	BANK_ENTRY ,
	//	最大
	BANK_MAX,

}E_BANK;

//====================================================
//	代码转换表
//====================================================
typedef struct tagCodeTbl
{
	//	编码
	u16 cod;
	//	有效位
	u16 mask;
	//	方向位
	u16 d;
	//	寄存器
	u16 f;
	//	位数
	u16 b;
	//	立即数
	u16 k;
	//	关键字
	const char * keyword;
	//	格式
	const char * format;
}S_CODE_TBL;

//====================================================
//	代码
//====================================================
typedef struct tagCodeBase
{
	//	标签
	const char * label;
	//	指令
	const char * opcode;
	//	参数1
	const char * param1;
	//	参数2
	const char * param2;

}S_CODE_BASE;

//====================================================
//	虚拟代码
//====================================================
typedef struct tagVirtualTbl
{
	//	编码
	u16 cod;
	//	关键字
	const char * keyword;
	//	指令
	const char * opcode;
	//	参数1
	const char * param1;
	//	参数2
	const char * param2;

}S_VIRTUAL_TBL;

//====================================================
//	宏替换
//====================================================
typedef struct tagMacroTbl
{
	//	原始代码
	S_CODE_BASE from;
	//	数量
	int count;
	//	替换代码
	const S_CODE_BASE *array;

}S_MACRO_TBL;

//====================================================
//	寄存器表
//====================================================
typedef struct tagRegTbl
{
	//	寄存器
	u16 reg;
	//	名称
	const char * name;

}S_REG_TBL;

//====================================================
//	分段类型
//====================================================
typedef struct tagBankTbl
{
	//	名称
	const char * name;
	//	寄存器
	u8 local;
	//	类型
	E_BANK bank;

}S_BANK_TBL;

//====================================================
//	关键字表
//====================================================
typedef struct tagConverTbl
{
	//	编码
	u16 code;
	//	关键字
	const char * keyword;

}S_CNV_TBL;

//====================================================
//	关键指令
//====================================================
typedef enum emInstruct
{
	COD_NAME=0,
	
	COD_BCR=1,
	COD_BSR,
	COD_BTRSC,
	COD_BTRSS,
	COD_NOP,
	COD_CLRWDT,
	COD_OPTION,
	COD_SLEEP,
	COD_INT,
	COD_DAA,
	COD_DAS,
	COD_RETURN,
	COD_RETFIE,
	COD_CLRA,
	COD_IOST,
	COD_CLRR,
	COD_MOVAR,
	COD_MOVR,
	COD_DECR,
	COD_DECRSZ,
	COD_INCR,
	COD_INCRSZ,
	COD_ADDAR,
	COD_SUBAR,
	COD_ADCAR,
	COD_SBCAR,
	COD_ANDAR,
	COD_IORAR,
	COD_XORAR,
	COD_COMR,
	COD_RRR,
	COD_RLR,
	COD_SWAPR,
	COD_MOVIA,
	COD_ADDIA,
	COD_SUBIA,
	COD_ANDIA,
	COD_IORIA,
	COD_XORIA,
	COD_RETIA,
	COD_CALL,
	COD_GOTO,

	COD_MAX,

}E_CODE_INS;

#endif //CODE_TBL_H_

