;======================================================
;= PIC LIST CONVERT TOOLS VERIOSN 1.12(R).
;=                                  (May 27 2020)|(08:33:21)
;=                                  ---Aleck.Shi
;======================================================
#define              C         0
#define              HC        1
#define              Z         2
#define              PF        3
#define              TF        4
;======================================================
#define              A         0
#define              R         1
;======================================================
;======================================================
;= REGISTER DECLARE 
;======================================================
INDF                     EQU 0x00
TMR0                     EQU 0x01
PCL                      EQU 0x02
STATUS                   EQU 0x03
FSR                      EQU 0x04
PORTA                    EQU 0x05
PORTB                    EQU 0x06
PORTC                    EQU 0x07
PCON                     EQU 0x08
WUCON                    EQU 0x09
PCHBUF                   EQU 0x0a
PDCON                    EQU 0x0b
ODCON                    EQU 0x0c
PHCON                    EQU 0x0d
INTEN                    EQU 0x0e
INTFLAG                  EQU 0x0f
ACC_TEMP                 EQU 0x3d
STATUS_TEMP              EQU 0x3e
FSR_TEMP                 EQU 0x3f
;======================================================
;= VARIABLE DECLARE
;======================================================
key_state                EQU 0x26 ;variable:38,bank:2
rep_state                EQU 0x24 ;variable:36,bank:2
old_state                EQU 0x27 ;variable:39,bank:2
x_Delay_ms               EQU 0x20 ;variable:32,bank:2
x_Init_Io                EQU 0x20 ;variable:32,bank:2
x_set_bt_fm              EQU 0x20 ;variable:32,bank:2
x_Interrupt_T0           EQU 0x20 ;variable:32,bank:2
x_Interrupt_PB           EQU 0x20 ;variable:32,bank:2
x_Interrupt_Ex           EQU 0x20 ;variable:32,bank:2
x_main                   EQU 0x20 ;variable:32,bank:2
x___bmul                 EQU 0x20 ;variable:32,bank:2
Delay_ms_Cnt             EQU 0x20 ;variable:32,bank:2
set_bt_fm_n              EQU 0x20 ;variable:32,bank:2
bmul_multiplicand        EQU 0x20 ;variable:32,bank:2
bmul_product             EQU 0x21 ;variable:33,bank:2
bmul_multiplier          EQU 0x22 ;variable:34,bank:2
main_abc                 EQU 0x23 ;variable:35,bank:2
;======================================================
;= PROGRAM START
;======================================================
                         ORG         00h                      ;for prefix 
                         GOTO        initialization             ;for prefix 
                         NOP                                  ;for prefix 
                         ORG         08h                      ;for prefix 
                         GOTO        interrput                ;for prefix 
                         NOP                                  ;for prefix 
                                                              ;initializer for _old_state 
                         RETIA       0xff                     
stringtab:
                                                              ;	global	stringdir,stringtab,__stringbase 
stringcode:
                                                              ;	String table - string pointers are 1 byte each 
stringdir:
                         MOVIA       (stringdir)>>8             
                         MOVAR       PCHBUF                   
                         MOVR        FSR         ,A           
                         INCR        FSR         ,R           
                         ADDAR       PCL         ,R           
stringbase:
                         RETIA       0x00                     
end_of__stringtab:
array:
                         RETIA       0x00                     
                         RETIA       0x01                     
                         RETIA       0x02                     
                         RETIA       0x03                     
                         RETIA       0x04                     
                         RETIA       0x05                     
                         RETIA       0x06                     
                         RETIA       0x07                     
                         RETIA       0x08                     
                         RETIA       0x09                     
end_of_array:
arrayX:
                         RETIA       0x00                     
                         RETIA       0x01                     
                         RETIA       0x02                     
                         RETIA       0x03                     
                         RETIA       0x04                     
                         RETIA       0x05                     
                         RETIA       0x06                     
                         RETIA       0x07                     
                         RETIA       0x08                     
                         RETIA       0x09                     
end_of_arrayX:
start_initialization:
                                                              ; #config settings 
initialization:
end_of_initialization:
                                                              ;End of C runtime variable initialization code 
end_of__initialization:
                         CLRR        STATUS                   
                         GOTO        main                     ;jump to C main() function 
                                                              
                        ;=====================================
                        ;= function : _main()
                        ;= parament : 
                        ;=   return : 
                        ;=   script : 
                        ;=====================================
main:
                                                              ;main.c: 138: Init_Io(); 
                                                              ; Regs used in _main: [wreg-fsr0h+status,2+status,0+pclath+cstack] 
                         CALL        Init_Io                  
                         MOVIA       0xff                     
                                                              ;main.c: 140: key_state = 0; 
                         CLRR        key_state                
                                                              ;main.c: 141: old_state = -1; 
                         MOVAR       old_state                
                         MOVIA       array-stringbase             
                                                              ;main.c: 142: rep_state = 0; 
                         CLRR        rep_state                
                         CLRR        rep_state+1              
                                                              ;main.c: 144: abc = array[key_state]; 
                         MOVAR       FSR                      
                         CALL        stringdir                
                         MOVAR       main_abc                 
                                                              ;main.c: 145: abc *= key_state; 
                         MOVAR       x___bmul                 
                         MOVIA       0x00                     
                         CALL        bmul                     
                         MOVAR       main_abc                 
                                                              ;main.c: 146: abc /= 4; 
                         BCR         STATUS      ,C           
                         RRR         main_abc    ,R           
                         BCR         STATUS      ,C           
                         RRR         main_abc    ,R           
                                                              ;main.c: 148: key_state = abc; 
                         MOVR        main_abc    ,A           
                         MOVAR       key_state                
                                                              ;main.c: 149: abc = arrayX[key_state]; 
                         ADDIA       (arrayX-stringbase)&0xff             
                         MOVAR       FSR                      
                         CALL        stringdir                
                         MOVAR       main_abc                 
                                                              ;main.c: 150: key_state = abc; 
                         MOVAR       key_state                
                                                              ;main.c: 152: Interrupt_T0(); 
                         CALL        Interrupt_T0             
                                                              ;main.c: 153: Interrupt_PB(); 
                         CALL        Interrupt_PB             
                                                              ;main.c: 154: Interrupt_Ex(); 
                         CALL        Interrupt_Ex             
l71:
                                                              ;main.c: 156: while(1){ 
                         CLRWDT                               ;# 
                                                              ;main.c: 165: if(RB2){ 
                         BCR         STATUS      ,5           ;RP0=0, select bank0 
                         BTRSS       PORTB       ,2           ;volatile 
                         GOTO        l724                     
                                                              ;main.c: 166: key_state = 1; 
                         CLRR        key_state                
                         INCR        key_state   ,R           
                                                              ;main.c: 167: }else{ 
                         GOTO        l726                     
l724:
                                                              ;main.c: 168: key_state = 0; 
                         CLRR        key_state                
l726:
                                                              ;main.c: 169: } 
                                                              ;main.c: 174: if(old_state != key_state){ 
                         MOVR        old_state   ,A           
                         XORAR       key_state   ,A           
                         BTRSC       STATUS      ,Z           
                         GOTO        l732                     
                                                              ;main.c: 175: old_state = key_state; 
                         MOVR        key_state   ,A           
                         MOVAR       old_state                
                                                              ;main.c: 176: rep_state = 0; 
                         CLRR        rep_state                
                         CLRR        rep_state+1              
                                                              ;main.c: 177: }else{ 
                         GOTO        l75                      
l732:
                                                              ;main.c: 178: rep_state++; 
                         INCR        rep_state   ,R           
                         BTRSC       STATUS      ,Z           
                         INCR        rep_state+1 ,R           
                                                              ;main.c: 179: if(rep_state > 32){ 
                         MOVIA       0x00                     
                         SUBAR       rep_state+1 ,A           
                         MOVIA       0x21                     
                         BTRSC       STATUS      ,Z           
                         SUBAR       rep_state   ,A           
                         BTRSS       STATUS      ,C           
                         GOTO        l75                      
                                                              ;main.c: 180: set_bt_fm(key_state); 
                         MOVR        key_state   ,A           
                         CALL        set_bt_fm                
l75:
                                                              ;main.c: 181: } 
                                                              ;main.c: 182: } 
                                                              ;main.c: 185: Delay_ms(10); 
                         MOVIA       0x0a                     
                         CALL        Delay_ms                 
                         GOTO        l71                      
end_of_main:
                                                              
                        ;=====================================
                        ;= function : _Interrupt_PB()
                        ;= parament : 
                        ;=   return : 
                        ;=   script : 
                        ;=====================================
Interrupt_PB:
                                                              ; Regs used in _Interrupt_PB: [] 
                         RETURN                               
end_of_Interrupt_PB:
                                                              
                        ;=====================================
                        ;= function : _Delay_ms()
                        ;= parament : 
                        ;=   return : 
                        ;=   script : 
                        ;=====================================
Delay_ms:
                                                              ; Regs used in _Delay_ms: [wreg+status,2+status,0] 
                                                              ;Delay_ms@Cnt stored from wreg 
                         MOVAR       Delay_ms_Cnt             
                                                              ;main.c: 34: while(Cnt--){ 
                         GOTO        l652                     
l48:
                         CLRWDT                               ;# 
l648:
                         MOVIA       0xfa                     
                         BCR         STATUS      ,5           ;RP0=0, select bank0 
                         SUBAR       TMR0        ,A           ;volatile 
                         BTRSS       STATUS      ,C           
                         GOTO        l48                      
                                                              ;main.c: 38: } 
                                                              ;main.c: 39: TMR0 = 0; 
                         CLRR        TMR0                     ;volatile 
l652:
                         DECR        Delay_ms_Cnt,R           
                         MOVR        Delay_ms_Cnt,A           
                         XORIA       0xff                     
                         BTRSC       STATUS      ,2           
                         RETURN                               
                         GOTO        l648                     
end_of_Delay_ms:
                                                              
                        ;=====================================
                        ;= function : _Init_Io()
                        ;= parament : 
                        ;=   return : 
                        ;=   script : 
                        ;=====================================
Init_Io:
                                                              ;main.c: 51: PORTA = 0; 
                                                              ; Regs used in _Init_Io: [wreg+status,2] 
                         CLRR        PORTA                    ;volatile 
                                                              ;main.c: 53: TRISA = 0; 
                         MOVIA       0                        ; Replaced With Macro. 
                         IOST        PORTA                    ; Replaced With Macro. 
                                                              ;main.c: 55: PORTA = 0; 
                         CLRR        PORTA                    ;volatile 
                                                              ;main.c: 60: PORTB = 0; 
                         CLRR        PORTB                    ;volatile 
                                                              ;main.c: 62: TRISB = 0|((1<<2)); 
                         MOVIA       0x04                     
                         IOST        PORTB                    ; Replaced With Macro. 
                                                              ;main.c: 64: PORTB = 0; 
                         CLRR        PORTB                    ;volatile 
                                                              ;main.c: 69: PCON = 0xA0; 
                         MOVIA       0xa0                     
                         MOVAR       PCON                     ;volatile 
                                                              ;main.c: 74: WUCON = 0; 
                         CLRR        WUCON                    ;volatile 
                                                              ;main.c: 76: PDCON = 0xFF; 
                         MOVIA       0xff                     
                         MOVAR       PDCON                    ;volatile 
                                                              ;main.c: 78: PHCON = 0xFF & (~(1<<2)); 
                         MOVIA       0xfb                     
                         MOVAR       PHCON                    ;volatile 
                                                              ;main.c: 80: ODCON = 0; 
                         CLRR        ODCON                    ;volatile 
                                                              ;main.c: 82: INTFLAG = 0; 
                         CLRR        INTFLAG                  ;volatile 
                                                              ;main.c: 84: TMR0 = 0; 
                         CLRR        TMR0                     ;volatile 
                                                              ;main.c: 86: INTEN = 0x80; 
                         MOVIA       0x80                     
                         MOVAR       INTEN                    ;volatile 
                                                              ;main.c: 90: OPTION = 1; 
                         MOVIA       0x01                     
                         OPTION                               ; Replaced With Macro. 
                         RETURN                               
end_of_Init_Io:
                                                              
                        ;=====================================
                        ;= function : _Interrupt_T0()
                        ;= parament : 
                        ;=   return : 
                        ;=   script : 
                        ;=====================================
Interrupt_T0:
                                                              ; Regs used in _Interrupt_T0: [] 
                         RETURN                               
end_of_Interrupt_T0:
                                                              
                        ;=====================================
                        ;= function : _set_bt_fm()
                        ;= parament : 
                        ;=   return : 
                        ;=   script : 
                        ;=====================================
set_bt_fm:
                                                              ; Regs used in _set_bt_fm: [wreg] 
                                                              ;set_bt_fm@n stored from wreg 
                         MOVAR       set_bt_fm_n              
                                                              ;main.c: 98: if(n){ 
                         MOVR        set_bt_fm_n ,A           
                         BTRSC       STATUS      ,2           
                         GOTO        l57                      
                                                              ;main.c: 99: RB0 = 1; 
                         BSR         PORTB       ,0           ;volatile 
                                                              ;main.c: 100: RB1 = 0; 
                         BCR         PORTB       ,1           ;volatile 
                                                              ;main.c: 101: }else{ 
                         RETURN                               
l57:
                                                              ;main.c: 102: RB0 = 0; 
                         BCR         PORTB       ,0           ;volatile 
                                                              ;main.c: 103: RB1 = 1; 
                         BSR         PORTB       ,1           ;volatile 
                         RETURN                               
end_of_set_bt_fm:
                                                              
                        ;=====================================
                        ;= function : _Interrupt_Ex()
                        ;= parament : 
                        ;=   return : 
                        ;=   script : 
                        ;=====================================
Interrupt_Ex:
                                                              ; Regs used in _Interrupt_Ex: [] 
                         RETURN                               
end_of_Interrupt_Ex:
                                                              
                        ;=====================================
                        ;= function : ___bmul()
                        ;= parament : 
                        ;=   return : 
                        ;=   script : 
                        ;=====================================
bmul:
                                                              ; Regs used in ___bmul: [wreg+status,2+status,0] 
                                                              ;___bmul@multiplier stored from wreg 
                         MOVAR       bmul_multiplier             
                         CLRR        bmul_product             
l678:
                         MOVR        bmul_multiplicand,A           
                         BTRSC       bmul_multiplier,0           
                         ADDAR       bmul_product,R           
                         BCR         STATUS      ,C           
                         RLR         bmul_multiplicand,R           
                         BCR         STATUS      ,C           
                         RRR         bmul_multiplier,R           
                         MOVR        bmul_multiplier,R           
                         BTRSS       STATUS      ,Z           
                         GOTO        l678                     
                         MOVR        bmul_product,A           
                         RETURN                               
end_of___bmul:
                                                              
                        ;=====================================
                        ;= function : ___bmul()
                        ;= parament : 
                        ;=   return : 
                        ;=   script : 
                        ;=====================================
interrput:
                         MOVAR       ACC_TEMP                 ;for interrupts 
                         SWAPR       STATUS      ,A           ;for interrupts 
                         MOVAR       STATUS_TEMP              ;for interrupts 
                         MOVR        FSR         ,A           ;for interrupts 
                         MOVAR       FSR_TEMP                 ;for interrupts 
int_tim0:
                         BTRSS       INTFLAG     ,0           ;for interrupts 
                         GOTO        int_pin                  ;for interrupts 
                         NOP                                  ;for interrupts 
                         CALL        Interrupt_T0             ;for interrupts 
int_pin:
                         BTRSS       INTFLAG     ,1           ;for interrupts 
                         GOTO        int_ext                  ;for interrupts 
                         NOP                                  ;for interrupts 
                         CALL        Interrupt_PB             ;for interrupts 
int_ext:
                         BTRSS       INTFLAG     ,2           ;for interrupts 
                         GOTO        int_end                  ;for interrupts 
                         NOP                                  ;for interrupts 
                         CALL        Interrupt_Ex             ;for interrupts 
int_end:
                         CLRR        INTFLAG                  ;for interrupts 
                         MOVR        FSR_TEMP    ,A           ;for interrupts 
                         MOVAR       FSR                      ;for interrupts 
                         SWAPR       STATUS_TEMP ,A           ;for interrupts 
                         MOVAR       STATUS                   ;for interrupts 
                         SWAPR       ACC_TEMP    ,R           ;for interrupts 
                         SWAPR       ACC_TEMP    ,A           ;for interrupts 
                         RETFIE                               ;for interrupts 
end_of_interrput:
