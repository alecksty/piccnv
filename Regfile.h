#pragma once

//	��ʶ������
typedef enum emType{
	//	δ֪����
	TYPE_UNKNOW = 0,
	//	�Ĵ���
	TYPE_REG ,
	//	����
	TYPE_VAR ,
	//	����
	TYPE_SET ,
	//	��ǩ
	TYPE_LABEL ,
	//	�ֶ�
	TYPE_BANK ,
	//	���ֵ
	TYPE_MAX,

}E_TYPE;

class Regfile
{
public:
	//	��ʼ��
	Regfile();
	//	�ͷ�
	~Regfile();

public:
	//	����
	int set(E_TYPE type,E_BANK bank,int addr,int size,const char *pname);
	//	���
	void dump(void);

public:
	//	����
	E_TYPE type;
	//	����
	E_BANK bank;
	//	��ַ
	int addr;
	//	��С
	int size;
	//	����
	char * name;

};

