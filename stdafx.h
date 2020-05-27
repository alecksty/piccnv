// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <stdlib.h>
#include <string.h>

#include "typedef.h"

#include "code_tbl.h"
#include "code_tbl_pic.h"
#include "code_tbl_emc.h"
#include "code_tbl_atw.h"

#include "lstitem.h"
#include "Regfile.h"
#include "piccnv.h"

// TODO:  在此处引用程序需要的其他头文件

#ifdef _DEBUG
	#define PRESS_ANY_KEY_TO_CONTINUE()			{printf("\nPress Any Key To Continue!\n");getchar();}
	#define PRINTF								printf
	#define DBUG()								{printf("%d,%s,%s\n", __LINE__ ,__FILE__,__FUNCTION__);}
#else
	#define PRESS_ANY_KEY_TO_CONTINUE()			{printf("\nPress Any Key To Continue!\n");}
	#define PRINTF(...)							{}
	#define DBUG()								{}
#endif

