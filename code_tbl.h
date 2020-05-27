#ifndef CODE_TBL_H_
#define CODE_TBL_H_

//==================================================
//	����
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
//	������:	CODE/STRING/BANK0/COMMON
//==================================================
typedef enum emBank
{
	//	����
	BANK_CODE = 0,
	//	�ַ�
	BANK_STRING,
	//	����
	BANK_BANK ,
	//	��ջ
	BANK_COMMON ,
	//	���
	BANK_ENTRY ,
	//	���
	BANK_MAX,

}E_BANK;

//====================================================
//	����ת����
//====================================================
typedef struct tagCodeTbl
{
	//	����
	u16 cod;
	//	��Чλ
	u16 mask;
	//	����λ
	u16 d;
	//	�Ĵ���
	u16 f;
	//	λ��
	u16 b;
	//	������
	u16 k;
	//	�ؼ���
	const char * keyword;
	//	��ʽ
	const char * format;
}S_CODE_TBL;

//====================================================
//	����
//====================================================
typedef struct tagCodeBase
{
	//	��ǩ
	const char * label;
	//	ָ��
	const char * opcode;
	//	����1
	const char * param1;
	//	����2
	const char * param2;

}S_CODE_BASE;

//====================================================
//	�������
//====================================================
typedef struct tagVirtualTbl
{
	//	����
	u16 cod;
	//	�ؼ���
	const char * keyword;
	//	ָ��
	const char * opcode;
	//	����1
	const char * param1;
	//	����2
	const char * param2;

}S_VIRTUAL_TBL;

//====================================================
//	���滻
//====================================================
typedef struct tagMacroTbl
{
	//	ԭʼ����
	S_CODE_BASE from;
	//	����
	int count;
	//	�滻����
	const S_CODE_BASE *array;

}S_MACRO_TBL;

//====================================================
//	�Ĵ�����
//====================================================
typedef struct tagRegTbl
{
	//	�Ĵ���
	u16 reg;
	//	����
	const char * name;

}S_REG_TBL;

//====================================================
//	�ֶ�����
//====================================================
typedef struct tagBankTbl
{
	//	����
	const char * name;
	//	�Ĵ���
	u8 local;
	//	����
	E_BANK bank;

}S_BANK_TBL;

//====================================================
//	�ؼ��ֱ�
//====================================================
typedef struct tagConverTbl
{
	//	����
	u16 code;
	//	�ؼ���
	const char * keyword;

}S_CNV_TBL;

//====================================================
//	�ؼ�ָ��
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

