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
extern const S_REG_TBL array_dir_atw[];
extern const int count_dir_atw;

extern const S_REG_TBL array_reg_atw[];
extern const int count_reg_atw;

extern const S_CODE_TBL array_code_atw[];
extern const int count_code_atw ;

extern const S_CNV_TBL array_cnv_atw[];
extern const int count_cnv_atw;

extern const char *pre_text_atw;

extern const S_MACRO_TBL array_macro_atw[];
extern const int count_macro_atw;

extern const S_CODE_BASE array_prefix_atw[];
extern const int count_prefix_atw;

extern const S_CODE_BASE array_interrupt_atw[] ;
extern const int count_interrupt_atw;

