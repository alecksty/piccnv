

class S_GOBAL;
//==================================================
//	列表
//==================================================
class ListItem
{
public:
	ListItem(void);
	~ListItem(void);

public:
	//	序号
	u16 index;
	//	地址
	u16 addr;
	//	编码
	u16 code; 
	//	文本
	char * text;

	//=================================
	//	CODE/STRING/BANK0/COMMON
	//=================================
	E_BANK bank;

	//=================================
	//	分解后的数据
	//=================================
	//	psect bank
	//label:opcode param1,param2 ;comment
	//=================================
	//	标号
	char * label;
	//	操作
	char * opcode;
	//	参数1
	char * param1;
	//	参数2
	char * param2;
	//	标号
	char * comment;

public:
	//	检查
	int check(class S_GOBAL * pd, const char * s);
	//	分解
	int parser(class S_GOBAL * pd,char * s);
	//	转码
	ListItem * convert(class S_GOBAL * pd,E_LANG lang);
	//	替换
	int replace(const S_VIRTUAL_TBL *tbl,int count);
	//	复制
	int copy(ListItem *p);
	//	输出
	void dump(void);
	//	写入
	int write(FILE *fp);

	//	寄存器	
	int is_reg_set(void);
	//	变量
	int is_var_set(void);
	//	标签
	int is_valid_label(const char * s);
	//	操作码
	int is_valid_opcode(const char * s);
	//	注释
	int is_valid_comment(const char * s);

	//	写入
	int writeto(FILE *fp,const char *plabel,const char *popcode,const char *pparam1,const char *pparam2,const char *pcomment);
	//	宏替换
	int domacro(FILE *fp,const S_MACRO_TBL *arr,int cnt);
};

//==================================================
//
//==================================================
int 	isspace(int c);
int 	findchar(const char *s,char c);
int 	replacechar(const char *s,char findc,char toc);
char * 	maketext(const char *s);
char * 	strlimit(char *s);
char * 	str_fix_ident(char *d,const char *s);
int 	str_is_number(const char *s);

//==================================================
//
//==================================================
const S_REG_TBL * findDirWord(const char * keyword,E_LANG lang);
const S_CNV_TBL * findProgramWord(const char * keyword,E_LANG lang);
const S_CODE_TBL * findConvertItem(const char * keyword,E_LANG lang);

