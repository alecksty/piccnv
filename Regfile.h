#pragma once

//	标识符类型
typedef enum emType{
	//	未知类型
	TYPE_UNKNOW = 0,
	//	寄存器
	TYPE_REG ,
	//	变量
	TYPE_VAR ,
	//	常量
	TYPE_SET ,
	//	标签
	TYPE_LABEL ,
	//	分段
	TYPE_BANK ,
	//	最大值
	TYPE_MAX,

}E_TYPE;

class Regfile
{
public:
	//	初始化
	Regfile();
	//	释放
	~Regfile();

public:
	//	设置
	int set(E_TYPE type,E_BANK bank,int addr,int size,const char *pname);
	//	输出
	void dump(void);

public:
	//	类型
	E_TYPE type;
	//	属性
	E_BANK bank;
	//	地址
	int addr;
	//	大小
	int size;
	//	名称
	char * name;

};

