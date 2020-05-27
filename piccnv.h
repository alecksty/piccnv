// piccnv.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

//==================================================
//=	PIC-CONVERT-TOOLS
//==================================================
//
//	PIC-IDE是8位单片机行业的老大,开发工具功能完备强大。
//	但是美国的单片机太贵了。不划算!
//	大陆的单片机很便宜
//	
//	但是大陆和台湾的单片机,几乎不支持C编程.
//	只有51系列可以支持.
//	
//	特地制作此工具,利用PIC-IDE生成的LST文件,
//	转换成153系列的汇编代码.
//
//				虽然本工具不构成侵权,
//				但是毕竟有用到Microchip的强大工具优势.
//				还是要向Microchip致敬!
//
//									---Aleck.Shi(施探宇)
//										QQ:190376601
//										EMAIL:alecksty@163.com
//
//==================================================

//	代码上限4K
#define MAX_LIST_ITEM					(1024 * 4)

//	寄存器上限256
#define MAX_MEM_ITEM					(256)

//	段落宽度
#define MAX_FILED_LEN 					(128)

//	缓存大小
#define TEXT_BUFFER_MAX 				(256)

//
#define CFG_SUPPORT_SAME_WIDTH			1

//==================================================
//	全局上下文
//==================================================
class S_GOBAL{

public:
	//
	//	0 - UPCASE,1 - LOWCASE.2 - KEEP
	//
	u8 uplow;

	//	当前段类型
	E_BANK bank;

	//	起始地址
	int reg_addr;

	//	数量
	int list_total;

	//	数据
	ListItem list_array[MAX_LIST_ITEM];

	//	数量
	int reg_total;
	
	//	数据(标号/变量/段)
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
//	函数接口
//==================================================
void app_show_help(const char * argv);

