// piccnv.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

//==================================================
//=	PIC-CONVERT-TOOLS
//==================================================
//
//	PIC-IDE是8位单片机行业的老大,开发工具功能完备强大。
//	但是美国的单片机太贵了,不划算!	中国大陆的单片机很便宜。
//	
//	但是大陆和台湾的低端单片机,几乎不支持C编程,(不是不能，是懒得做)
//	只有51系列可以支持，可以沾Keil的光。
//	
//	特地制作此工具,利用PIC-IDE生成的LST文件,
//	转换成153系列的汇编代码.
//
//				虽然本工具代码不构成侵权,
//				但是毕竟有用到Microchip的强大工具优势.
//				还是要向Microchip致敬!
//
//				此代码灵感来自于同学闵运华，向他表示感谢！
//
//				特此声明：本软件代码仅用于研究，不可以用于商业用途，后果自负！
//
//									---Aleck.Shi(施探宇)
//										QQ:190376601，WX:18680399436.
//										EMAIL:alecksty@163.com
//
//==================================================

//	全局数据
S_GOBAL g_data;

//==================================================
//	函数：app_show_help
//	参数：
//	返回：
//	说明：显示帮助
//==================================================
void app_show_help(const char * argv)
{
	printf("==================================================\r\n");
	printf(" LIST FILE CONVERT TOOL Version 1.20 (R)\r\n");
	printf("==================================================\r\n");
	printf("usage:%s -i <lst file> -o <asm file> [-type <x53|atw|emc|pic>]\r\n","piccnv");
}

//==================================================
//	函数：main
//	参数：
//	返回：
//	说明：启动函数
//==================================================
int main(int argc,char *argv[])
{
	int i;
	FILE *fpInp;
	FILE *fpOut;
	char *pinp 		= "i.lst";
	char *pout 		= "o.asm";
	char *ptype 	= "x53";

	if(argc < 2){
		app_show_help(argv[0]);
		PRESS_ANY_KEY_TO_CONTINUE();
		return -1;
	}

	for(i = 1; i < argc; i++){
		if(argv[i][0] == '-'){
			if(!strcmp(argv[i],"-i")||!strcmp(argv[i],"-inp")){
				pinp = argv[++i];
				continue;
			}else if(!strcmp(argv[i],"-o")||!strcmp(argv[i],"-out")){
				pout = argv[++i];
				continue;
			}else if(!strcmp(argv[i],"-t")||!strcmp(argv[i],"-type")){
				ptype = argv[++i];
				continue;
			}else{
				printf("Unknow parament : %s\n",argv[i + 1]);
			}
		}
	}

	printf("==================================================\r\n");
	printf(" PIC LIST FILE CONVERT TOOLS Version 1.00 (R)\r\n");
	printf("==================================================\r\n");
	printf("  input file:%s\n",pinp);
	printf(" output file:%s\n",pout);
	printf("    asm type:%s\n",ptype);

	//=============
	//	input
	//=============
	errno_t err = fopen_s(&fpInp,pinp,"rt");
	if(err){
		printf("ERROR:open file %s failed,error:%d\n",pinp,err);
		PRESS_ANY_KEY_TO_CONTINUE();
		return -2;	
	}

	//=============
	//	output
	//=============
	err = fopen_s(&fpOut,pout,"w+t");
	if(err){
		printf("ERROR:open file %s failed,error:%d\n",pout,err);
		PRESS_ANY_KEY_TO_CONTINUE();
		return -3;
	}

	//=============
	//	加载
	//=============
	g_data.load(fpInp);

	//=============
	//	分类
	//=============
	g_data.regist();

	//=============
	//	转换
	//=============
	g_data.convert(LANG_ATW,fpOut);
	
	//=============
	//	关闭
	//=============
	fclose(fpOut);
	fclose(fpInp);

	printf("\n Proccess Done!\n");
	PRESS_ANY_KEY_TO_CONTINUE();
	return 0;
}

//==================================================
//	函数：add_reg
//	参数：
//	返回：
//	说明：添加寄存器
//==================================================
int S_GOBAL::add_reg(E_BANK bank,int addr,const char *pname)
{
	PRINTF("-->add reg : %s\n",pname);
	reg_array[reg_total].set(TYPE_REG,bank,addr,0,pname);
	return ++reg_total;
}

//==================================================
//	函数：add_var
//	参数：
//	返回：
//	说明：添加变量
//==================================================
int S_GOBAL::add_var(E_BANK bank,int addr,int size,const char *pname)
{
	PRINTF("-->add var : %s\n",pname);
	reg_array[reg_total].set(TYPE_VAR,bank,addr,size,pname);
	return ++reg_total;
}

//==================================================
//	函数：add_set
//	参数：
//	返回：
//	说明：添加变量
//==================================================
int S_GOBAL::add_set(E_BANK bank,int addr,int size,const char *pname)
{
	PRINTF("-->add set : %s\n",pname);
	reg_array[reg_total].set(TYPE_SET,bank,addr,size,pname);
	return ++reg_total;
}

//==================================================
//	函数：add_lab
//	参数：
//	返回：
//	说明：添加标签
//==================================================
int S_GOBAL::add_lab(E_BANK bank,int addr,const char *pname)
{
	PRINTF("-->add label : %s\n",pname);
	reg_array[reg_total].set(TYPE_LABEL,bank,addr,0,pname);
	return ++reg_total;
}

//==================================================
//	函数：app_add_bank
//	参数：
//	返回：
//	说明：添加段落
//			psect	idataBANK0,global,class=CODE,delta=2
//==================================================
int S_GOBAL::add_bank(const char * pclass,const char *pname)
{
	E_BANK b = BANK_CODE;

	if(!pname)
		return 0;

	if(!pclass)
		return 0;

	if(!_stricmp(pclass,"CODE")){
		b = BANK_CODE;
	}else if(!_stricmp(pclass,"STRING")){
		b = BANK_STRING;
	}else if(!_strnicmp(pclass,"BANK",4)){
		b = BANK_BANK;
	}else if(!_stricmp(pclass,"COMMON")){
		b = BANK_COMMON;
	}else if(!_stricmp(pclass,"ENTRY")){
		b = BANK_COMMON;
	}else{
		PRINTF("#ERROR:Unknow Bank Class:<%s>\n",pclass);
		return 0;
	}

	PRINTF("add_bank(class:%s,name:%s)=%d\n",pclass,pname,b);
	
	reg_array[reg_total].set(TYPE_BANK,(bank = b),0,0,pname);
	return ++reg_total;
}

//==================================================
//	函数：find_byname
//	参数：
//	返回：
//	说明：查找
//==================================================
Regfile * S_GOBAL::find_byname(const char *name,E_TYPE type)
{
	int i = 0;

	if(!name)
		return NULL;

	for(i = 0; i < reg_total; i++){
		Regfile *prf = &reg_array[i];
		//	查找名字和类别
		if(!_stricmp(prf->name,name) && (prf->type == type)){
			PRINTF("-->find text %s\n",name);
			return prf;
		}
	}
	return NULL;
}

//==================================================
//	函数：app_find_byaddr
//	参数：
//	返回：
//	说明：查找变量
//==================================================
Regfile * S_GOBAL::find_byaddr(int addr,E_TYPE type,int dir)
{
	int i = 0;

	//	往后找
	if(dir == 0){
		for(i = 0; i <reg_total; i++){
			Regfile *prf = &reg_array[i];
			if((prf->addr == addr) && (prf->type == type)){
				return prf;
			}
		}
	//	往前找
	}else{
		for(i = reg_total - 1; i >= 0; i--){
			Regfile *prf = &reg_array[i];
			if((prf->addr == addr) && (prf->type == type)){
				return prf;
			}
		}
	}
	return NULL;
}

//==================================================
//	函数：分解数据
//	参数：
//	返回：
//	说明：启动函数
//									psect	idataBANK0,global,class=CODE,delta=2
//                                	psect	strings,global,class=STRING,delta=2
//                              	psect	nvBANK0,global,class=BANK0,space=1,delta=1
//==================================================
int S_GOBAL::parser_bank(const char * sbank)
{
	static char s_name[MAX_FILED_LEN];
	static char s_global[MAX_FILED_LEN];
	static char s_class[MAX_FILED_LEN];

	int fnd = 0;
	const char *ps = sbank;
	char *pc = NULL;

	if(!sbank)
		return 0;

	ps += 6;

	memset(s_name,0,sizeof(s_name));
	memset(s_global,0,sizeof(s_global));
	memset(s_class,0,sizeof(s_class));
	
	//============
	//	name,
	//============
	fnd = findchar(ps, ',');
	if(fnd){
		strncpy_s(s_name,ps,fnd);
		s_name[fnd - 1] = 0;
//		PRINTF("name:%s\n",s_name);
		ps += fnd;
	}else{
		//	单独的
		strcpy_s(s_name,ps);
		Regfile *prf = find_byname(s_name, TYPE_BANK);
		if(prf){
			//	类型
			bank = prf->bank;
		}
		PRINTF("->>Set Bank(%s)=%d\n",s_name,bank);
		return 0;
	}

	//============
	//	global/local
	//============
	fnd = findchar(ps, ',');
	if(fnd){
		strncpy_s(s_global,ps,fnd);
		s_global[fnd - 1] = 0;
//		PRINTF("global:%s\n",s_global);
		ps += fnd;
	}else{
		//	设置当前段
	}

	//============
	//	class=CODE
	//============
	fnd = findchar(ps, ',');
	if(fnd){
		strncpy_s(s_class,ps,fnd);
		s_class[fnd - 1] = 0;
		//PRINTF("class:%s\n",s_class);
		ps += fnd;
		if(!_strnicmp(s_class,"class=",6)){
			pc = &s_class[6];
			//	注册
			add_bank(pc,s_name);
			return 1;
		}else{
			PRINTF("unknow class:%s\n",s_class);
		}
	}
	
	return 0;
}

//==================================================
//	函数：load
//	参数：
//	返回：
//	说明：启动函数
//==================================================
int S_GOBAL::load(FILE *fi)
{
	static char buffer[MAX_LIST_ITEM];
	ListItem li;

	DBUG();

	//	清空
	list_total = 0;

	while(!feof(fi)){

		buffer[0] = 0;
		//	读取行
		fgets(buffer,MAX_LIST_ITEM,fi);
		//	检查有效
		if(li.check(this,buffer)){
			//	添加
			list_array[list_total].copy(&li);
			//	数据
			list_total++;
		}
	}

	return list_total;
}

//==================================================
//	函数：register
//	参数：
//	返回：
//	说明：
//==================================================
int S_GOBAL::regist(void)
{
	int i;
	int n = 0;
	int addr = 0;
	int size = 0;

	DBUG();

	//	添加默认的寄存器
	for(i = 0; i < count_reg_atw; i++)
	{
		add_reg(BANK_BANK,array_reg_atw[i].reg,array_reg_atw[i].name);
	}

	for(i = 0; i < list_total; i++)
	{
		ListItem * pi = &list_array[i];

		n = 0;

		//=================
		//	登记寄存器:	label:reg opcode:set param1:num param2:null
		//=================
		if(pi->is_reg_set())
		{
			size = 1;
			//	寄存器
			addr = atoi(pi->param1);
			//	查看重复的
			Regfile * prf = find_byname(pi->label,TYPE_SET);
			if(!prf){
				n = add_set(pi->bank, pi->addr, size, pi->label);
			}
		}
		//=================
		//	登记变量:	label ds size
		//=================
		else if(pi->is_var_set())
		{
			//	大小
			size = atoi(pi->param1);
			//	查找名称
			Regfile *prf = find_byaddr(pi->addr, TYPE_LABEL,1);
			//	添加变量
			if (prf) {
				n = add_var(pi->bank, pi->addr, size, prf->name);
			}else {
				PRINTF("ERROR:prf is (null),find label on addr:%x\n", pi->addr);
			}
		}
		//=================
		//	标签
		//=================
		else if(pi->label)
		{
			//	添加标签
			n = add_lab(pi->bank,pi->addr,pi->label);
		}

		if(n)
		{
			reg_array[reg_total - 1].dump();
		}
	}
	
	return reg_total;
}

//==================================================
//	函数：app_convert_asm
//	参数：
//	返回：
//	说明：
//==================================================
int S_GOBAL::convert(E_LANG lan,FILE *fp)
{
	int i;
	int n = 0;
	int addr = 0;
	int size = 0;
	static char buffer[TEXT_BUFFER_MAX];

	const char * array_equ[LANG_MAX]=
	{
		"SET",
		"==",
		"EQU",
	};
	
	const int count_regs[LANG_MAX]=
	{
		count_reg_pic,
		count_reg_emc,
		count_reg_atw,
	};
	
	const S_REG_TBL* array_regs[LANG_MAX]=
	{
		array_reg_pic,
		array_reg_emc,
		array_reg_atw,
	};
	
	DBUG();

	//=====================
	//	文件头
	//=====================
	fprintf(fp,pre_text_atw);

	fprintf(fp,";======================================================\n");
	fprintf(fp,";= REGISTER DECLARE \n");
	fprintf(fp,";======================================================\n");

	//=====================
	//	寄存器
	//=====================
	for(i = 0; i < count_regs[lan % LANG_MAX]; i++){
		const S_REG_TBL * ptbl = &array_regs[lan % LANG_MAX][i];
		fprintf(fp,"%-24s %s 0x%02x\n",ptbl->name,array_equ[lan%LANG_MAX],ptbl->reg);
	}

	//	列表
	fprintf(fp,";======================================================\n");
	fprintf(fp,";= VARIABLE DECLARE\n");
	fprintf(fp,";======================================================\n");

	//=====================
	//	变量
	//=====================
	for(i = 0; i < reg_total; i++){
		Regfile * pr = &reg_array[i];
		if (pr) {
			//=====================
			//	变量定义
			//=====================
			if((pr->type == TYPE_LABEL) && (pr->bank == BANK_BANK)){
				//	编译生成的,过滤掉
				fprintf(fp,"%-24s %s 0x%02x ;variable:%d,bank:%d\n",str_fix_ident(buffer,pr->name),array_equ[lan%LANG_MAX],pr->addr,pr->addr,pr->bank);
			}else if(pr->type == TYPE_VAR){
				//fprintf(fp,";%-23s %s 0x%02x ;VAR:%d,bank:%d\n",str_fix_ident(buffer,pr->name),array_equ[lan%LANG_MAX],pr->addr,pr->addr,pr->bank);
			}else if(pr->type == TYPE_SET /*&& (pr->bank == BANK_CODE)*/){
				//fprintf(fp,";%-23s %s 0x%02x ;const:%d,bank:%d\n",str_fix_ident(buffer,pr->name),array_equ[lan%LANG_MAX],pr->addr,pr->addr,pr->bank);
			}else if(pr->type == TYPE_REG){
				//fprintf(fp,";%-23s %s 0x%02x ;register:%d,bank:%d\n",str_fix_ident(buffer,pr->name),array_equ[lan%LANG_MAX],pr->addr,pr->addr,pr->bank);
			}
		}
	}

	//	代码
	fprintf(fp,";======================================================\n");
	fprintf(fp,";= PROGRAM START\n");
	fprintf(fp,";======================================================\n");

	//=====================
	//	代码开头
	//=====================
	for(i = 0; i < count_prefix_atw; i++){
		const S_CODE_BASE *pcb = &array_prefix_atw[i];
		ListItem * pi = &list_array[0];
		if (pcb) {
			pi->writeto(fp, pcb->label,pcb->opcode, pcb->param1, pcb->param2, "for prefix");
		}
	}

	//=====================
	//	列表
	//=====================
	for(i = 0; i < list_total; i++){
		ListItem * pi = &list_array[i];
		if (pi) {
			//===================
			//	虚拟指令
			//===================
			pi->replace(array_vir_pic, count_vir_pic);

			//===================
			//	转换指令
			//===================
			ListItem * po = pi->convert(this,lan);

			if (po) {
				//	输出
				po->dump();
				//	写文件
				po->write(fp);
			}
		}
	}

	//=====================
	//	结尾代码
	//=====================
	for(i = 0; i < count_interrupt_atw; i++){
		const S_CODE_BASE *pcb = &array_interrupt_atw[i];
		ListItem * pi = &list_array[0];
		if (pcb) {
			pi->writeto(fp, pcb->label,pcb->opcode, pcb->param1, pcb->param2, "for interrupts");
		}
	}

	return reg_total;
}


