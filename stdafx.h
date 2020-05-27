// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
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

// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�

#ifdef _DEBUG
	#define PRESS_ANY_KEY_TO_CONTINUE()			{printf("\nPress Any Key To Continue!\n");getchar();}
	#define PRINTF								printf
	#define DBUG()								{printf("%d,%s,%s\n", __LINE__ ,__FILE__,__FUNCTION__);}
#else
	#define PRESS_ANY_KEY_TO_CONTINUE()			{printf("\nPress Any Key To Continue!\n");}
	#define PRINTF(...)							{}
	#define DBUG()								{}
#endif

