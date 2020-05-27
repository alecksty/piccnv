// piccnv.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

//==================================================
//=	PIC-CONVERT-TOOLS
//==================================================
//
//	PIC-IDE��8λ��Ƭ����ҵ���ϴ�,�������߹����걸ǿ��
//	���������ĵ�Ƭ��̫���ˡ�������!
//	��½�ĵ�Ƭ���ܱ���
//	
//	���Ǵ�½��̨��ĵ�Ƭ��,������֧��C���.
//	ֻ��51ϵ�п���֧��.
//	
//	�ص������˹���,����PIC-IDE���ɵ�LST�ļ�,
//	ת����153ϵ�еĻ�����.
//
//				��Ȼ�����߲�������Ȩ,
//				���ǱϾ����õ�Microchip��ǿ�󹤾�����.
//				����Ҫ��Microchip�¾�!
//
//									---Aleck.Shi(ʩ̽��)
//										QQ:190376601
//										EMAIL:alecksty@163.com
//
//==================================================

//	��������4K
#define MAX_LIST_ITEM					(1024 * 4)

//	�Ĵ�������256
#define MAX_MEM_ITEM					(256)

//	������
#define MAX_FILED_LEN 					(128)

//	�����С
#define TEXT_BUFFER_MAX 				(256)

//
#define CFG_SUPPORT_SAME_WIDTH			1

//==================================================
//	ȫ��������
//==================================================
class S_GOBAL{

public:
	//
	//	0 - UPCASE,1 - LOWCASE.2 - KEEP
	//
	u8 uplow;

	//	��ǰ������
	E_BANK bank;

	//	��ʼ��ַ
	int reg_addr;

	//	����
	int list_total;

	//	����
	ListItem list_array[MAX_LIST_ITEM];

	//	����
	int reg_total;
	
	//	����(���/����/��)
	Regfile reg_array[MAX_MEM_ITEM];

public:
	int load(FILE *fp);
	int check(void);
	int regist(void);
	int convert(E_LANG lan,FILE *fp);

	int add_reg(E_BANK bank,int addr,const char *pname);
	int add_lab(E_BANK bank,int addr,const char *pname);
	int add_set(E_BANK bank,int addr,int size,const char *pname);
	int add_var(E_BANK bank,int addr,int size,const char *pname);
	int add_bank(const char *pclass,const char *pname);

	Regfile * find_byname(const char *name,E_TYPE type);
	Regfile * find_byaddr(int addr,E_TYPE type,int dir);

	int parser_bank(const char * sbank);
};

//==================================================
//	�����ӿ�
//==================================================
void app_show_help(const char * argv);

