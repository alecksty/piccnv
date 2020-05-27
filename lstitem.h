

class S_GOBAL;
//==================================================
//	�б�
//==================================================
class ListItem
{
public:
	ListItem(void);
	~ListItem(void);

public:
	//	���
	u16 index;
	//	��ַ
	u16 addr;
	//	����
	u16 code; 
	//	�ı�
	char * text;

	//=================================
	//	CODE/STRING/BANK0/COMMON
	//=================================
	E_BANK bank;

	//=================================
	//	�ֽ�������
	//=================================
	//	psect bank
	//label:opcode param1,param2 ;comment
	//=================================
	//	���
	char * label;
	//	����
	char * opcode;
	//	����1
	char * param1;
	//	����2
	char * param2;
	//	���
	char * comment;

public:
	//	���
	int check(class S_GOBAL * pd, const char * s);
	//	�ֽ�
	int parser(class S_GOBAL * pd,char * s);
	//	ת��
	ListItem * convert(class S_GOBAL * pd,E_LANG lang);
	//	�滻
	int replace(const S_VIRTUAL_TBL *tbl,int count);
	//	����
	int copy(ListItem *p);
	//	���
	void dump(void);
	//	д��
	int write(FILE *fp);

	//	�Ĵ���	
	int is_reg_set(void);
	//	����
	int is_var_set(void);
	//	��ǩ
	int is_valid_label(const char * s);
	//	������
	int is_valid_opcode(const char * s);
	//	ע��
	int is_valid_comment(const char * s);

	//	д��
	int writeto(FILE *fp,const char *plabel,const char *popcode,const char *pparam1,const char *pparam2,const char *pcomment);
	//	���滻
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

