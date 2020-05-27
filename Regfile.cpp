
#include "stdafx.h"

//==================================================
//	������Regfile
//	������
//	���أ�
//	˵����
//==================================================
Regfile::Regfile()
{
	type = TYPE_UNKNOW;
	addr = 0;
	size = 0;
	name = NULL;
}

//==================================================
//	������~Regfile
//	������
//	���أ�
//	˵����
//==================================================
Regfile::~Regfile()
{
	if (name != NULL) {
		free(name);
		name = NULL;
	}
}

//==================================================
//	������dump
//	������
//	���أ�
//	˵�����������
//==================================================
void Regfile::dump(void)
{
#ifdef _DEBUG
	printf("type:%d,",type);
	printf("bank:%d,",bank);
	printf("addr:%04x,",addr);
	printf("size:%d,",size);
	printf("name:(%s)",name);
	printf("\n");
#endif
}

//==================================================
//	������set
//	������
//	���أ�
//	˵����
//==================================================
int Regfile::set(E_TYPE type,E_BANK bank,int addr,int size,const char *pname)
{
	this->type 	= type;
	this->bank 	= bank;
	this->addr 	= addr;
	this->size 	= size;
	this->name 	= maketext(pname);
	return 1;
}

