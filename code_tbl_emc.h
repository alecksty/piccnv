//=====================================================================
//	W 	:工作寄存器 (累加器)
//
//	f 	:寄存器文件地址 (0x00 到 0x1F).
//	b 	:8 位文件寄存器中位的地址.
//	k 	:立即数字段,常数或标号.
//	d 	:选择目标寄存器:
//		d = 0 结果存储至 W.
//		d = 1 结果存储至文件寄存器 f.
//		默认值为 d = 1.
//
//======================================================================
extern const S_REG_TBL array_dir_emc[];
extern const int count_dir_emc;

extern const S_REG_TBL array_reg_emc[];
extern const int count_reg_emc;

extern const S_CODE_TBL array_code_emc[];
extern const int count_code_emc;

extern const S_CNV_TBL array_cnv_emc[];
extern const int count_cnv_emc;

extern const char *pre_text_emc;

