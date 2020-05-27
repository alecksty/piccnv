#include "stdafx.h"

//==================================================
//
//==================================================
//	原始语言
const int FROM_LANG 		= LANG_PIC;

//==================================================
//	函数：isspace
//	参数：
//	返回：
//	说明：识别空格
//==================================================
int isspace(int c)
{
	switch(c)
	{
	case ' ':
	case '\t':
	case '\r':
	case '\n':
		return 1;
	}
	return 0;
}

//==================================================
//	函数：isnumber
//	参数：
//	返回：
//	说明：识别数字
//==================================================
int isnumber(char c)
{
	if((c >= '0') && (c <= '9'))
		return 1;
	return 0;
}

//==================================================
//	函数：strisnumber
//	参数：
//	返回：
//	说明：识别数字
//==================================================
int str_is_number(const char *s)
{
	const char *ps = s;

	while(*ps){
		if(*ps == '-'||*ps == '+')
		{
		
		}
		else if(isspace(*ps))
		{
		
		}
		else if(isnumber(*ps))
		{
		
		}
		else if(*ps)
		{
			return 0;
		}
		ps++;
	}
	return 1;
}

//==================================================
//	函数：findchar
//	参数：
//	返回：
//	说明：查找字符
//==================================================
int findchar(const char *s,char c)
{
	const char *ps = s;
	int i = 0;
	while((*ps != c) && *ps){
		i++;
		ps++;
	}
	if(*ps == c){
		return (i + 1);
	}
	return 0;
}

//==================================================
//	函数：replacechar
//	参数：
//	返回：
//	说明：替换字符
//==================================================
int replacechar(char *s,char findc,char toc)
{
	char *ps = s;
	int i = 0;

	while(*ps){
		ps++;
		if(*ps == findc){
			i++;
			*ps = toc;
		}
	}
	return i;
}

//==================================================
//	函数：make_express
//	参数：
//	返回：
//	说明：复制一份字符
//
//		func (_a +/- _b) ->(a+b)>>8
//		high (_a + _b)
//		low (_a - _b)->(a+b) & 0xFF
//
//==================================================
char * make_express(char *d,const char *s)
{
	static char s_func[MAX_FILED_LEN];
	static char s_data1[MAX_FILED_LEN];
	static char s_data2[MAX_FILED_LEN];

	static char s_op[3]={0,0,0};

	static char s_buffer[MAX_FILED_LEN];
	static char s_buffer1[MAX_FILED_LEN];
	static char s_buffer2[MAX_FILED_LEN];

	int fnd = 0;
	const char * ps = s;
	char * pd = d;
	char * pe = NULL;

	if(!s)
		return NULL;

	if(!*s)
		return NULL;

	memset(s_func,0,sizeof(s_func));
	memset(s_data1,0,sizeof(s_data1));
	memset(s_data2,0,sizeof(s_data2));
	memset(s_buffer,0,sizeof(s_buffer));

	//============
	//	func 
	//============
	fnd = findchar(ps, ' ');
	if(fnd){
		strncpy_s(s_func,ps,fnd);
		s_func[fnd - 1] = 0;
		ps += fnd;
	}

	while(*ps == ' ')
		ps++;

	while(*ps == '(')
		ps++;

	//============
	//	a - b
	//============
	fnd = findchar(ps, '-');
	if(fnd){
		s_op[0] = '-';
		strncpy_s(s_data1,ps,fnd);
		s_data1[fnd - 1] = 0;
		ps += fnd;
		PRINTF(",data1:%s,",s_data1);
		strcpy_s(s_data2,ps);
		pe = s_data2;
		while(*pe){
			if(*pe == ')'){
				*pe = 0;
			}
			pe++;
		}
		PRINTF(",data2:%s\n",s_data2);
		goto labFindDone;
	}

	//============
	//	a + b
	//============
	fnd = findchar(ps, '+');
	if(fnd){
		s_op[0] = '+';
		strncpy_s(s_data1,ps,fnd);
		s_data1[fnd - 1] = 0;
		ps += fnd;
		PRINTF(",data1:%s,",s_data1);
		strcpy_s(s_data2,ps);
		pe = s_data2;
		while(*pe){
			if(*pe == ')'){
				*pe = 0;
			}
			pe++;
		}
		PRINTF(",data2:%s\n",s_data2);
		goto labFindDone;
	}

	//============
	//	high var1
	//============
	if(s_func[0]){
		s_op[0] = 0;
		strcpy_s(s_data1,ps);
		goto labFindDone;
	}
	
	//	其他
	return maketext(s);
	
labFindDone:
	{
		char *pd1 = str_fix_ident(s_buffer1, s_data1);
		char *pd2 = str_fix_ident(s_buffer2, s_data2);

		PRINTF("func:(%s),",s_func);
		PRINTF("data1:(%s->%s),",s_data1,pd1);
		PRINTF("data2:(%s->%s)\n",s_data2,pd2);

		if(!_stricmp( s_func,"high")){
			sprintf_s(s_buffer,sizeof(s_buffer),"(%s%s%s)>>8",pd1,s_op,pd2);
		}else if(!_stricmp( s_func,"low")){
			sprintf_s(s_buffer,sizeof(s_buffer),"(%s%s%s)&0xff",pd1,s_op,pd2);
		}else{
			sprintf_s(s_buffer,sizeof(s_buffer),"%s%s%s",pd1,s_op,pd2);		
		}

		return maketext(s_buffer);
	}
}

//==================================================
//	函数：maketext
//	参数：
//	返回：
//	说明：复制一份字符
//==================================================
char * maketext(const char *s)
{
	int i = 0;
	int l = 0;
	char * ps = NULL;

	if(!s)	return NULL;
	if(!*s)	return NULL;

	l = (int)strlen(s);
	ps = (char *)malloc(l + 1);
	if(!ps){
		printf("ERROR:malloc data[%d] failed!\n",l + 1);
		return NULL;
	}

	for(i = 0; i < l; i++){
		ps[i] = s[i];
	}
	ps[l] = 0;
	return ps;
}

//==================================================
//	函数：strlimit
//	参数：
//	返回：
//	说明：紧缩空格
//==================================================
char * strlimit(char *s)
{
	char *ps = s;
	char *pd = s;

	//	beging space
	while(isspace(*ps)){
		ps++;
	}

	while(*ps){
		//	注释;
		if((*ps == '\r')||(*ps == '\n')){
			break;
		}else{
			*pd = *ps;
		}
		pd++;
		ps++;
	}
	*pd = 0;

	//	过滤尾巴的空格
	pd--;
	while(pd > s){
		if(isspace(*pd)){
			*pd = 0;
		}else{
			break;
		}
		pd--;
	}

	return s;
}

//==================================================
//	函数：str_fix_ident
//	参数：
//	返回：
//	说明：紧缩标识符
//==================================================
char * str_fix_ident(char *d,const char *s)
{
	const char *ps = s;
	char *pd = d;

	if (!s)
		return NULL;

	//=========================
	//	beging space
	//=========================
	if(*ps == '?'){
		*pd = 'x';
	}

	//	过滤前面
	while(isspace(*ps)||*ps =='_'){
		ps++;
	}

	//=========================
	//	替换怪字符
	//=========================
	while(*ps){
		if((*ps == '\r')||(*ps == '\n')||(*ps == ':')){
			break;
		}else{
			if(*ps == '?'){
				*pd = 'x';
			}else if(*ps == '@'){
				*pd = '_';
			}else{
				*pd = *ps;
			}
		}
		pd++;
		ps++;
	}
	*pd = 0;

	//=========================
	//	过滤尾巴的空格
	//=========================
	pd--;
	while(pd > s){
		if(isspace(*pd)||(*pd == ':')||(*pd == 0)){
			*pd = 0;
		}else{
			break;
		}
		pd--;
	}

	return d;
}

//==================================================
//	函数：ListItem
//	参数：
//	返回：
//	说明：初始化
//==================================================
ListItem::ListItem(void)
{
	this->index 	= 0;
	this->addr		= 0;
	this->code 		= 0;
	this->text	 	= NULL;
	this->bank 		= BANK_CODE;

	this->label		= NULL;
	this->opcode	= NULL;
	this->param1	= NULL;
	this->param2	= NULL;
	this->comment	= NULL;
}

//==================================================
//	函数：~ListItem
//	参数：
//	返回：
//	说明：析构函数
//==================================================
ListItem::~ListItem(void)
{
	this->index 	= 0;
	this->addr 		= 0;
	this->code 		= 0;
	this->bank 		= BANK_CODE;

	if(this->text != NULL){
		free(this->text);
		this->text = NULL;
	}

	if(this->label != NULL){
		free(this->label);
		this->label = NULL;
	}

	if(this->opcode != NULL){
		free(this->opcode);
		this->opcode = NULL;
	}

	if(this->param1 != NULL){
		free(this->param1);
		this->param1 = NULL;
	}

	if(this->param2 != NULL){
		free(this->param2);
		this->param2 = NULL;
	}

	if(this->comment != NULL){
		free(this->comment);
		this->comment = NULL;
	}
}

//==================================================
//	函数：check
//	参数：
//	返回：
//	说明：分解各段
//==================================================
int ListItem::check(class S_GOBAL *pd,const char * s)
{
	const int FILED_WIDTH = 6;
	const char *ps = s;

	static char s_index[FILED_WIDTH+1];
	static char s_addr[FILED_WIDTH+1];
	static char s_code[FILED_WIDTH+1];
	static char s_content[TEXT_BUFFER_MAX];

	int len = (int)strlen(s);

	if(!s)
		return 0;

	if(!*s)
		return 0;

	if(len > FILED_WIDTH ){

		//	序号
		strncpy_s(s_index,ps,FILED_WIDTH);
		//	序号
		this->index = (u16)strtol(s_index,NULL,10);

		//	有效
		if(this->index > 0){

			ps += FILED_WIDTH;

			//=====================
			//	跳过注释
			//=====================
			if(ps[2] == ';'||ps[1] == ';'){
				return 0;
			}

			//=====================
			//	行号
			//=====================
			strncpy_s(s_addr,ps,FILED_WIDTH);
			//	地址
			this->addr = (u16)strtol(s_addr,NULL,16);
			if(this->addr){
				ps += FILED_WIDTH;
			}

			//=====================
			//	操作码
			//=====================
			strncpy_s(s_code,ps,FILED_WIDTH);
			//	代码
			this->code = (u16)strtol(s_code,NULL,16);
			ps += FILED_WIDTH;

			//	内容
			strcpy_s(s_content,ps);

			//	长度
			len			= (int)strlen(s_content);

			//	分配
			this->text 	= (char *)malloc(len + 1);

			//=====================
			//	分配有效
			//=====================
			if(this->text){
				//	地址/操作码
				if(this->addr|this->code){
					//	内容
					strcpy_s(s_content,ps);
				}else{
					strcpy_s(s_content,ps);
				}

				//	复制数据
				strcpy_s(this->text,len + 1,s_content);
				//	数据整理
				this->text = strlimit(this->text);
			}

			//=====================
			//	有效指令
			//=====================
			if(this->parser(pd,this->text)){
				//	输出
				this->dump();

				return 1;
			}
		}
	}

	return 0;
}

//==================================================
//	函数：convert
//	参数：
//	返回：
//	说明：分解数据
//==================================================
int ListItem::parser(class S_GOBAL *pd,char * s)
{
	char * ps = s;
	int fnd = 0;
	int l = 0;

	static char s_commen[MAX_FILED_LEN];
	static char s_lable[MAX_FILED_LEN];
	static char s_opcode[MAX_FILED_LEN];
	static char s_param1[MAX_FILED_LEN];
	static char s_param2[MAX_FILED_LEN];
	static char s_psect[MAX_FILED_LEN];

	//	;注释
	//	label:;注释
	//	label:opcode pa1;注释
	//	label:opcode pa1,pa2;注释
	memset(s_commen,0,sizeof(s_commen));
	memset(s_lable,0,sizeof(s_lable));
	memset(s_opcode,0,sizeof(s_opcode));
	memset(s_param1,0,sizeof(s_param1));
	memset(s_param2,0,sizeof(s_param2));
	memset(s_psect,0,sizeof(s_psect));

	if(!s)
		return 0;

	//=================
	//	找到第一个<;>
	//	分解注释
	//=================
	fnd = findchar(ps, ';');
	if(fnd){
		//	分割数据
		strcpy_s(s_commen,ps + fnd);
		//	切断后面的
		ps[fnd -1] = 0;
	} 

	//=================
	//	找到标号<:>
	//	分解标号
	//=================
	fnd = findchar(ps, ':');
	if(fnd){
		strncpy_s(s_lable,ps,fnd);
		//	移动位置
		ps += fnd;

		//	无效标签
		//	??___function:
		if(!is_valid_label(s_lable)){
			return 0;
		}
	}

	//	替换tab	到空格!
	replacechar(ps,'\t',' ');
	//	紧缩
	strlimit(ps);
	//	查找空格
	fnd = findchar(ps, ' ');
	if(fnd){
		strncpy_s(s_opcode,ps,fnd);
		s_opcode[fnd - 1] = 0;

		//=============
		//	登记段
		//=============
		if(!_stricmp(s_opcode,"psect")){
			strcpy_s(s_psect,ps);
			//	分解段定义
			pd->parser_bank(s_psect);
			return 0;
		}

		//	移动位置
		ps += fnd;

		//=============
		//	过滤无效代码
		//=============
		if(!is_valid_opcode(s_opcode)){
			return 0;
		}

	}else{
		//	只有一个参数
		strcpy_s(s_opcode,ps);
		ps += strlen(ps);
	}

	//	查找分割
	fnd = findchar(ps, ',');
	if(fnd){
		//	找到第一个参数
		strncpy_s(s_param1,ps,fnd);
		//	结尾补空
		s_param1[fnd - 1] = 0;
		//	移动位置
		ps += fnd;
		//	第二个参数
		strcpy_s(s_param2,ps);
	}else{
		//	只有一个参数
		strcpy_s(s_param1,ps);
	}

	//====================
	// 分解'var set 23'
	//	psect	idataBANK0,global,class=CODE,delta=2
	//====================
	//	错位了,纠正.
	if(!_strnicmp(s_param1,"set ",4) && !s_lable[0]){
		strcpy_s(s_lable,s_opcode);
		strcpy_s(s_opcode,"set");
		strcpy_s(s_param1,&s_param1[4]);
	}

	//	当前的
	bank		= pd->bank;
	comment 	= maketext(s_commen);
	label 		= maketext(s_lable);
	opcode		= maketext(s_opcode);
	param1		= maketext(s_param1);
	param2		= maketext(s_param2);
	return 1;
}

//==================================================
//	函数：copy
//	参数：
//	返回：
//	说明：复制数据
//==================================================
int ListItem::copy(ListItem *p)
{
	//	序号
	this->index 		= p->index;
	//	行号
	this->addr			= p->addr;
	//	代码
	this->code			= p->code;
	//	分段
	this->bank			= p->bank;
	
	//	参数
	this->text			= maketext(p->text);

	//	标签
	this->label			= maketext(p->label);
	//	操作码
	this->opcode		= maketext(p->opcode);
	//	参数
	this->param1		= maketext(p->param1);
	//	参数
	this->param2		= maketext(p->param2);
	//	注释
	this->comment		= maketext(p->comment);

	return 1;
}

//==================================================
//	函数：dump
//	参数：
//	返回：
//	说明：输出内容
//==================================================
void ListItem::dump(void)
{
#ifdef _DEBUG

	printf("%4d,",index);
	printf("%04x,",addr);
	printf("%04x,",code);
	printf("%d,",bank);
	printf(":%-24s|",text);

	if(label){
		printf("%-18s",label);
	}else{
		printf("%-18s","");
	}
	if(opcode){
		printf("%-12s",opcode);
	}else{
		printf("%-12s","");
	}
	if(param1){
		printf("%-16s",param1);
	}else{
		printf("%-16s","");
	}
	if(param2){
		printf(",%-4s",param2);
	}else{
		printf(" %-4s","");
	}
	if(comment){
		printf(";%s",comment);
	}else{
		printf("%s","");
	}
	printf("\n");

#endif //_DEBUG

}

//==================================================
//	函数：convert
//	参数：
//	返回：
//	说明：转换
//==================================================
ListItem * ListItem::convert(class S_GOBAL * pd,E_LANG lang)
{
	static char buffer[TEXT_BUFFER_MAX];
	
	ListItem * pi = new ListItem();

	pi->index 	= index;
	pi->addr 	= addr;
	pi->code 	= code;
	pi->bank	= bank;
	pi->text 	= maketext(text);
	pi->label 	= maketext(label);
	pi->comment = maketext(comment);

	if(opcode){
		
		//	关键字对照转换
		const S_CNV_TBL *pvtbl = findProgramWord(opcode,lang);

		//	查到关键字
		if(pvtbl){
			//	语法转换
			const S_CODE_TBL *pcod = findConvertItem(pvtbl->keyword,lang);
			if(pcod){

				//=============
				//	操作码
				//=============
				pi->opcode = maketext(pcod->keyword);

				//=============
				//	有变量或寄存器
				//=============
				if(pcod->f){
					if(param1){
						//
						//	数字替换成寄存器名称!
						//
						if(str_is_number(param1)){
							int n = atoi(param1);
							if(pd){
								//==============
								//	查找寄存器
								//==============
								Regfile *pf = pd->find_byaddr(n, TYPE_REG, 0);
								if(pf){
									pi->param1 = maketext(pf->name);
								}else{
									//==============
									//	替换常量
									//==============
									pf = pd->find_byaddr(n, TYPE_SET, 0);
									if(pf){
										pi->param1 = maketext(pf->name);
									}else{
										pi->param1 = maketext(param1);
									}
								}
							}else{
								PRINTF("-->pd is (null)\n");
							}
						}else{
							//
							//	high __varlabel
							//	low (a-b)
							//
							pi->param1 = make_express(buffer,param1);
							//pi->param1 = maketext(param1);
						}
					}else{
						PRINTF("-->miss reg param1 is (null),f = %x\n",pcod->f);
					}
				}else{
					pi->param1 = maketext(param1);
				}

				//=============
				//	立即数
				//=============
				if(pcod->k){
					if(param1){
						//	数字
						if(str_is_number(param1)){
							int d = atoi(param1);
							//	数字串
							char buff[32];
							sprintf_s(buff,32,"0x%02x",d & 0xff);
							free(param1);
							param1 = NULL;
							pi->param1 = maketext(buff);
						}else{
							pi->param1 = make_express(buffer,param1);
						}
					}
				}
				
				//=============
				//	方向
				//=============
				if(pcod->d){
					//	替换方向
					const S_REG_TBL *pr = findDirWord(param2,lang);
					if(pr){
						pi->param2 = maketext(pr->name);
					}else{
						pi->param2 = maketext(param2);
					}
				}else{
					pi->param2 = maketext(param2);
				}

				//=============
				//	注释
				//=============
				pi->comment = maketext(comment);
				return pi;
			}
			else
			{
				//=============
				//	找不到转换
				//=============
				pi->opcode 		= maketext(opcode);
				pi->param1 		= maketext(param1);
				pi->param2 		= maketext(param2);
				pi->comment 	= maketext(comment);
				return pi;
			}
		}
		else
		{
			//=============
			//	找不到转换
			//=============
			pi->opcode 			= maketext(opcode);
			pi->param1 			= maketext(param1);
			pi->param2 			= maketext(param2);
			pi->comment 		= maketext(comment);
			return pi;			
		}
	}

	//==============
	//	标签
	//==============
	if(label){
		return pi;
	}

	//==============
	//	注释
	//==============
	if(comment){
		//	过滤无效字符
		if(is_valid_comment(comment)){		
			return pi;
		}
	}
	
	//	删除临时的
	delete pi;

	return NULL;
}

//==================================================
//	函数：write
//	参数：
//	返回：
//	说明：写入代码段
//==================================================
int ListItem::write(FILE *fp)
{
	//====================
	//	常量
	//====================
	if(is_reg_set())
		return 0;

	//====================
	//	变量
	//====================
	if(is_var_set())
		return 0;	

	//====================
	//	过滤
	//====================
	switch(bank){
	//	这个段没有代码!
	case BANK_BANK:
	case BANK_COMMON:
		return 0;

	default:
		break;
	}

	//====================
	//	宏替换
	//====================
	if(domacro(fp, array_macro_atw,count_macro_atw)){
		// 	do nothing
	}else{
		//	write to file
		writeto(fp,label,opcode,param1,param2,comment);
	}

	return 1;
}

//==================================================
//	函数：writeto
//	参数：
//	返回：
//	说明：转换
//==================================================
int ListItem::writeto(FILE *fp,const char *plabel,const char *popcode,const char *pparam1,const char *pparam2,const char *pcomment)
{
	static char buffer[TEXT_BUFFER_MAX];

	memset(buffer,0,sizeof(buffer));

	//	过滤无效
	if(!plabel && !popcode && !pparam1 && !strcmp(pcomment,"#")){
		return 1;
	}
	
	//	短标签,左边对齐.
	if(plabel && !popcode){
		fprintf(fp,"%s:",str_fix_ident(buffer,plabel));
		goto labWriteEnd;
	}

	//	标签
	if(plabel){
		//	修复格式
		fprintf(fp,"%-24s:",str_fix_ident(buffer,plabel));
	}else{
		fprintf(fp,"%-24s ","");
	}

	//	机器码
	if(popcode){
		fprintf(fp,"%-12s",popcode);
	}else{
#ifdef CFG_SUPPORT_SAME_WIDTH
		fprintf(fp,"%-12s","");
#endif //CFG_SUPPORT_SAME_WIDTH
	}

	//	参数1
	if(pparam1){
		//	修复格式
		fprintf(fp,"%-12s",str_fix_ident(buffer,pparam1));
	}else{
#ifdef CFG_SUPPORT_SAME_WIDTH
		fprintf(fp,"%-12s","");
#endif //CFG_SUPPORT_SAME_WIDTH
	}

	//	参数2
	if(pparam2){
		fprintf(fp,",%-12s",pparam2);
	}else{
#ifdef CFG_SUPPORT_SAME_WIDTH
		fprintf(fp," %-12s","");
#endif //CFG_SUPPORT_SAME_WIDTH
	}

	//	注释
	if(pcomment){
		if(!_strnicmp(pcomment,"psect for function",17)){
			//
		}else{
			fprintf(fp,";%s ",pcomment);
		}
	}

labWriteEnd:

	fprintf(fp,"\n");

	//========================
	//	函数接口
	//	;psect for function _Delay_ms
	//========================
#if 0
	if(plabel){
		if(!_strnicmp(plabel,"__end_of_",9)){
			fprintf(fp,"\n","");		
			fprintf(fp,"%-24s;=====================================\n","");		
			fprintf(fp,"%-24s;= Function:\n","");
			fprintf(fp,"%-24s;= Parament:\n","");
			fprintf(fp,"%-24s;= Return  :\n","");
			fprintf(fp,"%-24s;=====================================\n","");		
		}		
	}
#else
	if(pcomment){
		if(!_strnicmp(pcomment,"psect for function",17)){
			fprintf(fp,"%-24s;=====================================\n","");		
			fprintf(fp,"%-24s;= function : %s()\n","",pcomment+19);
			fprintf(fp,"%-24s;= parament : \n","");
			fprintf(fp,"%-24s;=   return : \n","");
			fprintf(fp,"%-24s;=   script : \n","");
			fprintf(fp,"%-24s;=====================================\n","");		
		}		
	}

#endif
	return 1;
}

//==================================================
//	函数：domacro
//	参数：
//	返回：
//	说明：转换
//==================================================
int ListItem::domacro(FILE *fp,const S_MACRO_TBL *arr,int cnt)
{
	int i = 0;
	int n = 0;
	static char buffer[TEXT_BUFFER_MAX];
	const S_MACRO_TBL *p = NULL;

	if(!fp)
		return 0;

	if(!arr)
		return 0;

	if(!opcode)
		return 0;

	for(i = 0; i < cnt; i++)
	{
		p = &arr[i];

		//	关键字相同
		if(!_stricmp(p->from.opcode,opcode))
		{
			//	第一个参数相同
			if(p->from.param1)
			{
				if(!_stricmp(p->from.param1,str_fix_ident(buffer, param1)))
				{
					//	第二个参数相同
					if(p->from.param2)
					{
						if(!_stricmp(p->from.param2,str_fix_ident(buffer, param2)))
						{
							//	执行替换
							n = 1;	
							break;
						}
					}
					else
					{
						n = 1;
						break;
					}
				}
			}
			else
			{
				n = 1;
				break;
			}
		}
	}

	//====================
	//	找到有效内容
	//====================
	if(n && p){

		//PRINTF("Find Macro!<%d>\n",p->count);

		n = 0;
		for(i = 0; i < p->count; i++){
			const S_CODE_BASE *ptbl = &p->array[i];
			if(ptbl){
				writeto(fp, NULL, ptbl->opcode, ptbl->param1, ptbl->param2, " Replaced With Macro.");
				n++;
			}else{
				PRINTF("Find Macro Error <%d>!\n",i);
			}
		}

		if(n > 0){
			return 1;
		}
	}

	return 0;
}

//==================================================
//	函数：is_reg_set
//	参数：
//	返回：
//	说明：常量
//==================================================
int ListItem::is_reg_set(void)
{
	//=================
	//	操作码:	name set addr
	//=================
	if(opcode && !_stricmp(opcode,"set"))
		return 1;
	return 0;
}

//==================================================
//	函数：is_var_set
//	参数：
//	返回：
//	说明：变量
//==================================================
int ListItem::is_var_set(void)
{
	//=================
	//	操作码:	label ds size
	//=================
	if(opcode && !_stricmp(opcode,"ds"))
		return 1;
	return 0;
}

//==================================================
//	函数：is_valid_label
//	参数：
//	返回：
//	说明：标签
//==================================================
int ListItem::is_valid_label(const char * s)
{
	//=================
	//	操作码:	label :
	//=================
	if(s){
		//	过滤无效
		if((s[0] == '?')&&(s[1] == '?') && (s[2] == '_') &&  (s[3] == '_')){
			return 0;
		}

		//	过滤无效
		if(!strncmp(s,"__ptext",7)){
			return 0;
		}

		if(!strncmp(s,"__pmaintext",11)){
			return 0;
		}
		
		if(!strncmp(s,"__pcstackBANK",13)){
			return 0;
		}

		if(!strncmp(s,"__pcstackCOMMON",15)){
			return 0;
		}

		if(!strncmp(s,"__pbssBANK",10)){
			return 0;
		}

		if(!strncmp(s,"__pidataBANK",12)){
			return 0;
		}

		if(!strncmp(s,"__pdataBANK",11)){
			return 0;
		}

		if(!strncmp(s,"__pnvBANK",9)){
			return 0;
		}

		if(!strncmp(s,"__pstrings",10)){
			return 0;
		}

		if(!strncmp(s,"__stringtab",11)){
			return 0;
		}

	}
	return 1;
}

//==================================================
//	函数：is_valid_comment
//	参数：
//	返回：
//	说明：
//==================================================
int ListItem::is_valid_comment(const char * s)
{
	//=================
	//	操作码:	0 bytes @ 0x0 
	//=================
	if(s){
		//	过滤无效
		if(!strncmp(s," 0 bytes @",10)){
			return 0;
		}
		if(!strncmp(s," 1 bytes @",10)){
			return 0;
		}
		if(!strncmp(s," 2 bytes @",10)){
			return 0;
		}
		if(!strncmp(s," 4 bytes @",10)){
			return 0;
		}
	}
	return 1;
}

//==================================================
//	函数：is_valid_opcode
//	参数：
//	返回：
//	说明：
//==================================================
int ListItem::is_valid_opcode(const char * s)
{
	// 	processor   16F676                   
	//  opt         pw 120                   
	//  opt         pm                       
	//  dabs        1,0x5E,2      
	//=================
	//	操作码:	label ds size
	//=================
	if(s){

		//	过滤无效
		if(!strncmp(s,"processor",9)){
			return 0;
		}

		if(!strncmp(s,"opt",3)){
			return 0;
		}

		if(!strncmp(s,"dabs",4)){
			return 0;
		}

		if(!strncmp(s,"psect",5)){
			return 0;
		}
	}
	return 1;
}

//==================================================
//	函数：replace
//	参数：
//	返回：
//	说明：转换
//==================================================
int ListItem::replace(const S_VIRTUAL_TBL *tbl,int count)
{
	int i;

	if(!tbl)
		return 0;

	if(!opcode)
		return 0;

	for(i = 0; i < count; i++){
		
		const S_VIRTUAL_TBL * ptbl = &tbl[i];

		//	有效指令
		if(!_stricmp(opcode,ptbl->keyword)){

			if(opcode){
				free(opcode);
			}
			opcode = maketext(ptbl->opcode);

			if(ptbl->param1){
				if(param1){
					free(param1);
				}
				param1= maketext(ptbl->param1);
			}

			if(ptbl->param2){
				if(param2){
					free(param2);
				}
				param2= maketext(ptbl->param2);
			}
			return 1;
		}
	}
	return 0;
}

//==================================================
//	函数：findDirWord
//	参数：
//	返回：
//	说明：转换
//==================================================
const S_REG_TBL * findDirWord(const char * keyword,E_LANG lang)
{
	int i;

	//	转换表
	const S_REG_TBL *array_name[] = 
	{
		array_dir_pic,
		array_dir_emc,
		array_dir_atw,
	};

	const int count_name[] = 
	{
		count_dir_pic,
		count_dir_emc,
		count_dir_atw,
	};

	if (!keyword)
		return NULL;

	for(i = 0; i < count_name[FROM_LANG % LANG_MAX];i++){
		//	转码
		const S_REG_TBL * ptbl = &array_name[FROM_LANG % LANG_MAX][i];
		//	找编码
		if(!_stricmp(keyword,ptbl->name)){
			//	转码
			return &array_name[lang % LANG_MAX][i];
		}
	}

	PRINTF("-->NO FIND DIR (%s)\n",keyword);

	return NULL;
}

//==================================================
//	函数：findProgramWord
//	参数：
//	返回：
//	说明：转换
//==================================================
const S_CNV_TBL *findProgramWord(const char * keyword,E_LANG lang)
{
	int i;

	//	转换表
	const S_CNV_TBL *array_name[] = 
	{
		array_cnv_pic,
		array_cnv_emc,
		array_cnv_atw,
	};

	const int count_name[] = 
	{
		count_cnv_pic,
		count_cnv_emc,
		count_cnv_atw,
	};

	//	
	if (!keyword)
		return NULL;

	for(i = 0; i < count_name[FROM_LANG % LANG_MAX];i++){
		//	找编码
		if(!_stricmp(keyword,array_name[FROM_LANG % LANG_MAX][i].keyword)){
			//	转码
			return &array_name[lang % LANG_MAX][i];
		}
	}

	//PRINTF("-->NO FIND KEYWORD (%s)\n",keyword);

	return NULL;
}

//==================================================
//	函数：findConvertItem
//	参数：
//	返回：
//	说明：转换
//==================================================
const S_CODE_TBL *findConvertItem(const char * keyword,E_LANG lang)
{
	int i;

	const S_CODE_TBL *array_code[] = 
	{
		array_code_pic,
		array_code_emc,
		array_code_atw,
	};
	
	const int count_code[] = 
	{
		count_code_pic,
		count_code_emc,
		count_code_atw,
	};

	if (!keyword)
		return NULL;

	//	查表
	for(i = 0; i < count_code[lang % LANG_MAX];i++ ){
		//	代码
		const S_CODE_TBL *p = &array_code[lang % LANG_MAX][i];
		//	比较
		if(!_strcmpi(keyword,p->keyword)){
			return p;
		}
	}

	PRINTF("-->NO FIND ITEM (%s)\n",keyword);

	return NULL;
}

