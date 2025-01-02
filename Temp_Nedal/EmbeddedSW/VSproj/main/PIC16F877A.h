// Individual bit access constants
const char B0 = 0;
const char B1 = 1;
const char B2 = 2;
const char B3 = 3;
const char B4 = 4;
const char B5 = 5;
const char B6 = 6;
const char B7 = 7;

const unsigned long __FLASH_SIZE = 0x00002000;

// Working space s
 unsigned short R0;
 unsigned short R1;
 unsigned short R2;
 unsigned short R3;
 unsigned short R4;
 unsigned short R5;
 unsigned short R6;
 unsigned short R7;
 unsigned short R8;
 unsigned short R9;
 unsigned short R10;
 unsigned short R11;
 unsigned short R12;
 unsigned short R13;
 unsigned short R14;
 unsigned short R15;

const  unsigned short int W = 0;
const  unsigned short int F = 1;

// Special function s (s)

const signed int   PORT_TO_TRIS_OFFSET = 128;

const unsigned short ICS_AUTO = 0;
const unsigned short ICS_OFF = 3;

 unsigned short volatile INDF              = 0x0000;
 unsigned short volatile TMR0              = 0x0001;
 unsigned short volatile PCL               = 0x0002;
 unsigned short volatile STATUS            = 0x0003;
 unsigned short          FSR               = 0x0004;
 unsigned short* FSRPTR = (unsigned short*)(0x0004);
 unsigned short volatile PCLATH            = 0x000A;
 unsigned short volatile INTCON            = 0x000B;
 unsigned short volatile PIR1              = 0x000C;
 unsigned short volatile PIR2              = 0x000D;
 unsigned short volatile TMR1L             = 0x000E;
 unsigned short volatile TMR1H             = 0x000F;
 unsigned short volatile T1CON             = 0x0010;
 unsigned short volatile TMR2              = 0x0011;
 unsigned short volatile T2CON             = 0x0012;
 unsigned short volatile SSPBUF            = 0x0013;
 unsigned short volatile SSPCON            = 0x0014;
 unsigned int   volatile CCPR1             = 0x0015;
 unsigned short volatile CCPR1L            = 0x0015;
 unsigned short volatile CCPR1H            = 0x0016;
 unsigned short volatile CCP1CON           = 0x0017;
 unsigned short volatile RCSTA             = 0x0018;
 unsigned short volatile TXREG             = 0x0019;
 unsigned short volatile RCREG             = 0x001A;
 unsigned short volatile CCP2CON           = 0x001D;
 unsigned short volatile ADRESH            = 0x001E;
 unsigned short volatile ADCON0            = 0x001F;
 unsigned short volatile OPTION_REG        = 0x0081;
 unsigned short volatile PIE1              = 0x008C;
 unsigned short volatile PIE2              = 0x008D;
 unsigned short volatile PCON              = 0x008E;
 unsigned short volatile SSPCON2           = 0x0091;
 unsigned short volatile PR2               = 0x0092;
 unsigned short volatile SSPADD            = 0x0093;
 unsigned short volatile SSPST			   = 0x0094;
 unsigned short volatile TXSTA             = 0x0098;
 unsigned short          SPBRG             = 0x0099;
 unsigned short volatile CMCON             = 0x009C;
 unsigned short volatile CVRCON            = 0x009D;
 unsigned short volatile ADRESL            = 0x009E;
 unsigned short volatile ADCON1            = 0x009F;
 unsigned short volatile EEDATA            = 0x010C;
 unsigned short volatile EEADR             = 0x010D;
 unsigned short volatile EEDATH            = 0x010E;
 unsigned short volatile EEADRH            = 0x010F;
 unsigned short volatile EECON1            = 0x018C;
 unsigned short volatile EECON2            = 0x018D;
 unsigned short volatile PORTA             = 0x0005;
 unsigned short volatile PORTB             = 0x0006;
 unsigned short volatile PORTC             = 0x0007;
 unsigned short volatile PORTD             = 0x0008;
 unsigned short volatile PORTE             = 0x0009;
 unsigned int   volatile CCPR2             = 0x001B;
 unsigned short volatile CCPR2L            = 0x001B;
 unsigned short volatile CCPR2H            = 0x001C;
 unsigned short volatile TRISA             = 0x0085;
 unsigned short volatile TRISB             = 0x0086;
 unsigned short volatile TRISC             = 0x0087;
 unsigned short volatile TRISD             = 0x0088;
 unsigned short volatile TRISE             = 0x0089;



 // STATUS bits
unsigned short int C = 0;
 //   C_bit =STATUSB0;
unsigned short int DC = 1;
 //   DC_bit =STATUSB1;
unsigned short int Z = 2;
 //   Z_bit =STATUSB2;
unsigned short int NOT_PD = 3;
 //   NOT_PD_bit =STATUSB3;
unsigned short int NOT_TO = 4;
 //   NOT_TO_bit =STATUSB4;
unsigned short int IRP = 7;
 //   IRP_bit =STATUSB7;
unsigned short int RP0 = 5;
 //   RP0_bit =STATUSB5;
unsigned short int RP1 = 6;
 //   RP1_bit =STATUSB6;

 // INTCON bits
unsigned short int RBIF = 0;
 //   RBIF_bit =INTCONB0;
unsigned short int INTF = 1;
 //   INTF_bit =INTCONB1;
unsigned short int TMR0IF = 2;
 //   TMR0IF_bit =INTCONB2;
unsigned short int RBIE = 3;
 //   RBIE_bit =INTCONB3;
unsigned short int INTE = 4;
 //   INTE_bit =INTCONB4;
unsigned short int TMR0IE = 5;
 //   TMR0IE_bit =INTCONB5;
unsigned short int PEIE = 6;
 //   PEIE_bit =INTCONB6;
unsigned short int GIE = 7;
 //   GIE_bit =INTCONB7;
unsigned short int T0IF = 2;
 //   T0IF_bit =INTCONB2;
unsigned short int T0IE = 5;
 //   T0IE_bit =INTCONB5;

 // PIR1 bits
unsigned short int TMR1IF = 0;
 //   TMR1IF_bit =PIR1B0;
unsigned short int TMR2IF = 1;
 //   TMR2IF_bit =PIR1B1;
unsigned short int CCP1IF = 2;
 //   CCP1IF_bit =PIR1B2;
unsigned short int SSPIF = 3;
 //   SSPIF_bit =PIR1B3;
unsigned short int TXIF = 4;
 //   TXIF_bit =PIR1B4;
unsigned short int RCIF = 5;
 //   RCIF_bit =PIR1B5;
unsigned short int ADIF = 6;
 //   ADIF_bit =PIR1B6;
unsigned short int PSPIF = 7;
 //   PSPIF_bit =PIR1B7;

 // PIR2 bits
unsigned short int CCP2IF = 0;
 //   CCP2IF_bit =PIR2B0;
unsigned short int BCLIF = 3;
 //   BCLIF_bit =PIR2B3;
unsigned short int EEIF = 4;
 //   EEIF_bit =PIR2B4;
unsigned short int CMIF = 6;
 //   CMIF_bit =PIR2B6;

 // T1CON bits
unsigned short int TMR1ON = 0;
 //   TMR1ON_bit =T1CONB0;
unsigned short int TMR1CS = 1;
 //   TMR1CS_bit =T1CONB1;
unsigned short int NOT_T1SYNC = 2;
 //   NOT_T1SYNC_bit =T1CONB2;
unsigned short int T1OSCEN = 3;
 //   T1OSCEN_bit =T1CONB3;
unsigned short int T1SYNC = 2;
 //   T1SYNC_bit =T1CONB2;
unsigned short int T1CKPS0 = 4;
 //   T1CKPS0_bit =T1CONB4;
unsigned short int T1CKPS1 = 5;
 //   T1CKPS1_bit =T1CONB5;
unsigned short int T1INSYNC = 2;
 //   T1INSYNC_bit =T1CONB2;

 // T2CON bits
unsigned short int TMR2ON = 2;
 //   TMR2ON_bit =T2CONB2;
unsigned short int T2CKPS0 = 0;
 //   T2CKPS0_bit =T2CONB0;
unsigned short int T2CKPS1 = 1;
 //   T2CKPS1_bit =T2CONB1;
unsigned short int TOUTPS0 = 3;
 //   TOUTPS0_bit =T2CONB3;
unsigned short int TOUTPS1 = 4;
 //   TOUTPS1_bit =T2CONB4;
unsigned short int TOUTPS2 = 5;
 //   TOUTPS2_bit =T2CONB5;
unsigned short int TOUTPS3 = 6;
 //   TOUTPS3_bit =T2CONB6;

 // SSPCON bits
unsigned short int CKP = 4;
 //   CKP_bit =SSPCONB4;
unsigned short int SSPEN = 5;
 //   SSPEN_bit =SSPCONB5;
unsigned short int SSPOV = 6;
 //   SSPOV_bit =SSPCONB6;
unsigned short int WCOL = 7;
 //   WCOL_bit =SSPCONB7;
unsigned short int SSPM0 = 0;
 //   SSPM0_bit =SSPCONB0;
unsigned short int SSPM1 = 1;
 //   SSPM1_bit =SSPCONB1;
unsigned short int SSPM2 = 2;
 //   SSPM2_bit =SSPCONB2;
unsigned short int SSPM3 = 3;
 //   SSPM3_bit =SSPCONB3;

 // CCP1CON bits
unsigned short int CCP1Y = 4;
 //   CCP1Y_bit =CCP1CONB4;
unsigned short int CCP1X = 5;
 //   CCP1X_bit =CCP1CONB5;
unsigned short int CCP1M0 = 0;
 //   CCP1M0_bit =CCP1CONB0;
unsigned short int CCP1M1 = 1;
 //   CCP1M1_bit =CCP1CONB1;
unsigned short int CCP1M2 = 2;
 //   CCP1M2_bit =CCP1CONB2;
unsigned short int CCP1M3 = 3;
 //   CCP1M3_bit =CCP1CONB3;

 // RCSTA bits
 //const  unsigned short int 9D = 0;
 //   9D_bit =RCSTAB0;
unsigned short int OERR = 1;
 //   OERR_bit =RCSTAB1;
unsigned short int FERR = 2;
 //   FERR_bit =RCSTAB2;
unsigned short int ADDEN = 3;
 //   ADDEN_bit =RCSTAB3;
unsigned short int CREN = 4;
 //   CREN_bit =RCSTAB4;
unsigned short int SREN = 5;
 //   SREN_bit =RCSTAB5;
 //const  unsigned short int 9 = 6;
 //   9_bit =RCSTAB6;
unsigned short int SPEN = 7;
 //   SPEN_bit =RCSTAB7;
unsigned short int RCD8 = 0;
 //   RCD8_bit =RCSTAB0;
unsigned short int RC9 = 6;
 //   RC9_bit =RCSTAB6;
unsigned short int NOT_RC8 = 6;
 //   NOT_RC8_bit =RCSTAB6;
unsigned short int RC8_9 = 6;
 //   RC8_9_bit =RCSTAB6;

 // CCP2CON bits
unsigned short int CCP2Y = 4;
 //   CCP2Y_bit =CCP2CONB4;
unsigned short int CCP2X = 5;
 //   CCP2X_bit =CCP2CONB5;
unsigned short int CCP2M0 = 0;
 //   CCP2M0_bit =CCP2CONB0;
unsigned short int CCP2M1 = 1;
 //   CCP2M1_bit =CCP2CONB1;
unsigned short int CCP2M2 = 2;
 //   CCP2M2_bit =CCP2CONB2;
unsigned short int CCP2M3 = 3;
 //   CCP2M3_bit =CCP2CONB3;

 // ADCON0 bits
unsigned short int ADON = 0;
 //   ADON_bit =ADCON0B0;
unsigned short int GO_NOT_DONE = 2;
 //   GO_NOT_DONE_bit =ADCON0B2;
unsigned short int GO = 2;
 //   GO_bit =ADCON0B2;
unsigned short int CHS0 = 3;
 //   CHS0_bit =ADCON0B3;
unsigned short int CHS1 = 4;
 //   CHS1_bit =ADCON0B4;
unsigned short int CHS2 = 5;
 //   CHS2_bit =ADCON0B5;
unsigned short int ADCS0 = 6;
 //   ADCS0_bit =ADCON0B6;
unsigned short int ADCS1 = 7;
 //   ADCS1_bit =ADCON0B7;
unsigned short int NOT_DONE = 2;
 //   NOT_DONE_bit =ADCON0B2;
unsigned short int GO_DONE = 2;
 //   GO_DONE_bit =ADCON0B2;

 // OPTION_REG bits
unsigned short int PSA = 3;
 //   PSA_bit =OPTION_REGB3;
unsigned short int T0SE = 4;
 //   T0SE_bit =OPTION_REGB4;
unsigned short int T0CS = 5;
 //   T0CS_bit =OPTION_REGB5;
unsigned short int INTEDG = 6;
 //   INTEDG_bit =OPTION_REGB6;
unsigned short int NOT_RBPU = 7;
 //   NOT_RBPU_bit =OPTION_REGB7;
unsigned short int PS0 = 0;
 //   PS0_bit =OPTION_REGB0;
unsigned short int PS1 = 1;
 //   PS1_bit =OPTION_REGB1;
unsigned short int PS2 = 2;
 //   PS2_bit =OPTION_REGB2;

 // Alternative bit function
unsigned short int PSPMODE = 4;
 //   PSPMODE_bit =TRISEB4;

 // Alternative bit function
unsigned short int IBOV = 5;
 //   IBOV_bit =TRISEB5;

 // Alternative bit function
unsigned short int OBF = 6;
 //   OBF_bit =TRISEB6;

 // Alternative bit function
unsigned short int IBF = 7;
 //   IBF_bit =TRISEB7;

 // PIE1 bits
unsigned short int TMR1IE = 0;
 //   TMR1IE_bit =PIE1B0;
unsigned short int TMR2IE = 1;
 //   TMR2IE_bit =PIE1B1;
unsigned short int CCP1IE = 2;
 //   CCP1IE_bit =PIE1B2;
unsigned short int SSPIE = 3;
 //   SSPIE_bit =PIE1B3;
unsigned short int TXIE = 4;
 //   TXIE_bit =PIE1B4;
unsigned short int RCIE = 5;
 //   RCIE_bit =PIE1B5;
unsigned short int ADIE = 6;
 //   ADIE_bit =PIE1B6;
unsigned short int PSPIE = 7;
 //   PSPIE_bit =PIE1B7;

 // PIE2 bits
unsigned short int CCP2IE = 0;
 //   CCP2IE_bit =PIE2B0;
unsigned short int BCLIE = 3;
 //   BCLIE_bit =PIE2B3;
unsigned short int EEIE = 4;
 //   EEIE_bit =PIE2B4;
unsigned short int CMIE = 6;
 //   CMIE_bit =PIE2B6;

 // PCON bits
unsigned short int NOT_BOR = 0;
 //   NOT_BOR_bit =PCONB0;
unsigned short int NOT_POR = 1;
 //   NOT_POR_bit =PCONB1;
unsigned short int NOT_BO = 0;
 //   NOT_BO_bit =PCONB0;

 // SSPCON2 bits
unsigned short int SEN = 0;
 //   SEN_bit =SSPCON2B0;
unsigned short int RSEN = 1;
 //   RSEN_bit =SSPCON2B1;
unsigned short int PEN = 2;
 //   PEN_bit =SSPCON2B2;
unsigned short int RCEN = 3;
 //   RCEN_bit =SSPCON2B3;
unsigned short int ACKEN = 4;
 //   ACKEN_bit =SSPCON2B4;
unsigned short int ACKDT = 5;
 //   ACKDT_bit =SSPCON2B5;
unsigned short int ACKST = 6;
 //   ACKSTAT_bit =SSPCON2B6;
unsigned short int GCEN = 7;
 //   GCEN_bit =SSPCON2B7;

 // SSPST=bits
unsigned short int BF = 0;
 //   BF_bit =SSPSTATB0;
unsigned short int UA = 1;
 //   UA_bit =SSPSTATB1;
unsigned short int R_NOT_W = 2;
 //   R_NOT_W_bit =SSPSTATB2;
unsigned short int S = 3;
 //   S_bit =SSPSTATB3;
unsigned short int P = 4;
 //   P_bit =SSPSTATB4;
unsigned short int D_NOT_A = 5;
 //   D_NOT_A_bit =SSPSTATB5;
unsigned short int CKE = 6;
 //   CKE_bit =SSPSTATB6;
unsigned short int SMP = 7;
 //   SMP_bit =SSPSTATB7;
unsigned short int R = 2;
 //   R_bit =SSPSTATB2;
unsigned short int D = 5;
 //   D_bit =SSPSTATB5;
unsigned short int NOT_W = 2;
 //   NOT_W_bit =SSPSTATB2;
unsigned short int NOT_A = 5;
 //   NOT_A_bit =SSPSTATB5;
unsigned short int NOT_WRITE = 2;
 //   NOT_WRITE_bit =SSPSTATB2;
unsigned short int NOT_ADDRESS = 5;
 //   NOT_ADDRESS_bit =SSPSTATB5;
unsigned short int R_W = 2;
 //   R_W_bit =SSPSTATB2;
unsigned short int D_A = 5;
 //   D_A_bit =SSPSTATB5;
unsigned short int READ_WRITE = 2;
 //   READ_WRITE_bit =SSPSTATB2;
unsigned short int DATA_ADDRESS = 5;
 //   DATA_ADDRESS_bit =SSPSTATB5;

 // TXSTA bits
unsigned short int TX9D = 0;
 //   TX9D_bit =TXSTAB0;
unsigned short int TRMT = 1;
 //   TRMT_bit =TXSTAB1;
unsigned short int BRGH = 2;
 //   BRGH_bit =TXSTAB2;
unsigned short int SYNC = 4;
 //   SYNC_bit =TXSTAB4;
unsigned short int TXEN = 5;
 //   TXEN_bit =TXSTAB5;
unsigned short int TX9 = 6;
 //   TX9_bit =TXSTAB6;
unsigned short int CSRC = 7;
 //   CSRC_bit =TXSTAB7;
unsigned short int TXD8 = 0;
 //   TXD8_bit =TXSTAB0;
unsigned short int NOT_TX8 = 6;
 //   NOT_TX8_bit =TXSTAB6;
unsigned short int TX8_9 = 6;
 //   TX8_9_bit =TXSTAB6;

 // CMCON bits
unsigned short int CIS = 3;
 //   CIS_bit =CMCONB3;
unsigned short int C1INV = 4;
 //   C1INV_bit =CMCONB4;
unsigned short int C2INV = 5;
 //   C2INV_bit =CMCONB5;
unsigned short int C1OUT = 6;
 //   C1OUT_bit =CMCONB6;
unsigned short int C2OUT = 7;
 //   C2OUT_bit =CMCONB7;
unsigned short int CM0 = 0;
 //   CM0_bit =CMCONB0;
unsigned short int CM1 = 1;
 //   CM1_bit =CMCONB1;
unsigned short int CM2 = 2;
 //   CM2_bit =CMCONB2;

 // CVRCON bits
unsigned short int CVRR = 5;
 //   CVRR_bit =CVRCONB5;
unsigned short int CVROE = 6;
 //   CVROE_bit =CVRCONB6;
unsigned short int CVREN = 7;
 //   CVREN_bit =CVRCONB7;
unsigned short int CVR0 = 0;
 //   CVR0_bit =CVRCONB0;
unsigned short int CVR1 = 1;
 //   CVR1_bit =CVRCONB1;
unsigned short int CVR2 = 2;
 //   CVR2_bit =CVRCONB2;
unsigned short int CVR3 = 3;
 //   CVR3_bit =CVRCONB3;

 // ADCON1 bits
unsigned short int ADCS2 = 6;
 //   ADCS2_bit =ADCON1B6;
unsigned short int ADFM = 7;
 //   ADFM_bit =ADCON1B7;
unsigned short int PCFG0 = 0;
 //   PCFG0_bit =ADCON1B0;
unsigned short int PCFG1 = 1;
 //   PCFG1_bit =ADCON1B1;
unsigned short int PCFG2 = 2;
 //   PCFG2_bit =ADCON1B2;
unsigned short int PCFG3 = 3;
 //   PCFG3_bit =ADCON1B3;

 // EECON1 bits
unsigned short int RD = 0;
 //   RD_bit =EECON1B0;
unsigned short int WR = 1;
 //   WR_bit =EECON1B1;
unsigned short int WREN = 2;
 //   WREN_bit =EECON1B2;
unsigned short int WRERR = 3;
 //   WRERR_bit =EECON1B3;
unsigned short int EEPGD = 7;
 //   EEPGD_bit =EECON1B7;

 // PORTA bits
unsigned short int RA5 = 5;
 //   RA5_bit =PORTAB5;
unsigned short int RA4 = 4;
 //   RA4_bit =PORTAB4;
unsigned short int RA3 = 3;
 //   RA3_bit =PORTAB3;
unsigned short int RA2 = 2;
 //   RA2_bit =PORTAB2;
unsigned short int RA1 = 1;
 //   RA1_bit =PORTAB1;
unsigned short int RA0 = 0;
 //   RA0_bit =PORTAB0;

 // PORTB bits
unsigned short int RB7 = 7;
 //   RB7_bit =PORTBB7;
unsigned short int RB6 = 6;
 //   RB6_bit =PORTBB6;
unsigned short int RB5 = 5;
 //   RB5_bit =PORTBB5;
unsigned short int RB4 = 4;
 //   RB4_bit =PORTBB4;
unsigned short int RB3 = 3;
 //   RB3_bit =PORTBB3;
unsigned short int RB2 = 2;
 //   RB2_bit =PORTBB2;
unsigned short int RB1 = 1;
 //   RB1_bit =PORTBB1;
unsigned short int RB0 = 0;
 //   RB0_bit =PORTBB0;

 // PORTC bits
unsigned short int RC7 = 7;
 //   RC7_bit =PORTCB7;
unsigned short int RC6 = 6;
 //   RC6_bit =PORTCB6;
unsigned short int RC5 = 5;
 //   RC5_bit =PORTCB5;
unsigned short int RC4 = 4;
 //   RC4_bit =PORTCB4;
unsigned short int RC3 = 3;
 //   RC3_bit =PORTCB3;
unsigned short int RC2 = 2;
 //   RC2_bit =PORTCB2;
unsigned short int RC1 = 1;
 //   RC1_bit =PORTCB1;
unsigned short int RC0 = 0;
 //   RC0_bit =PORTCB0;

 // PORTD bits
unsigned short int RD7 = 7;
 //   RD7_bit =PORTDB7;
unsigned short int RD6 = 6;
 //   RD6_bit =PORTDB6;
unsigned short int RD5 = 5;
 //   RD5_bit =PORTDB5;
unsigned short int RD4 = 4;
 //   RD4_bit =PORTDB4;
unsigned short int RD3 = 3;
 //   RD3_bit =PORTDB3;
unsigned short int RD2 = 2;
 //   RD2_bit =PORTDB2;
unsigned short int RD1 = 1;
 //   RD1_bit =PORTDB1;
unsigned short int RD0 = 0;
 //   RD0_bit =PORTDB0;

 // PORTE bits
unsigned short int RE2 = 2;
 //   RE2_bit =PORTEB2;
unsigned short int RE1 = 1;
 //   RE1_bit =PORTEB1;
unsigned short int RE0 = 0;
 //   RE0_bit =PORTEB0;

 // TRISA bits
unsigned short int TRISA5 = 5;
 //   TRISA5_bit =TRISAB5;
unsigned short int TRISA4 = 4;
 //   TRISA4_bit =TRISAB4;
unsigned short int TRISA3 = 3;
 //   TRISA3_bit =TRISAB3;
unsigned short int TRISA2 = 2;
 //   TRISA2_bit =TRISAB2;
unsigned short int TRISA1 = 1;
 //   TRISA1_bit =TRISAB1;
unsigned short int TRISA0 = 0;
 //   TRISA0_bit =TRISAB0;

 // TRISB bits
unsigned short int TRISB7 = 7;
 //   TRISB7_bit =TRISBB7;
unsigned short int TRISB6 = 6;
 //   TRISB6_bit =TRISBB6;
unsigned short int TRISB5 = 5;
 //   TRISB5_bit =TRISBB5;
unsigned short int TRISB4 = 4;
 //   TRISB4_bit =TRISBB4;
unsigned short int TRISB3 = 3;
 //   TRISB3_bit =TRISBB3;
unsigned short int TRISB2 = 2;
 //   TRISB2_bit =TRISBB2;
unsigned short int TRISB1 = 1;
 //   TRISB1_bit =TRISBB1;
unsigned short int TRISB0 = 0;
 //   TRISB0_bit =TRISBB0;

 // TRISC bits
unsigned short int TRISC7 = 7;
 //   TRISC7_bit =TRISCB7;
unsigned short int TRISC6 = 6;
 //   TRISC6_bit =TRISCB6;
unsigned short int TRISC5 = 5;
 //   TRISC5_bit =TRISCB5;
unsigned short int TRISC4 = 4;
 //   TRISC4_bit =TRISCB4;
unsigned short int TRISC3 = 3;
 //   TRISC3_bit =TRISCB3;
unsigned short int TRISC2 = 2;
 //   TRISC2_bit =TRISCB2;
unsigned short int TRISC1 = 1;
 //   TRISC1_bit =TRISCB1;
unsigned short int TRISC0 = 0;
 //   TRISC0_bit =TRISCB0;

 // TRISD bits
unsigned short int TRISD7 = 7;
 //   TRISD7_bit =TRISDB7;
unsigned short int TRISD6 = 6;
 //   TRISD6_bit =TRISDB6;
unsigned short int TRISD5 = 5;
 //   TRISD5_bit =TRISDB5;
unsigned short int TRISD4 = 4;
 //   TRISD4_bit =TRISDB4;
unsigned short int TRISD3 = 3;
 //   TRISD3_bit =TRISDB3;
unsigned short int TRISD2 = 2;
 //   TRISD2_bit =TRISDB2;
unsigned short int TRISD1 = 1;
 //   TRISD1_bit =TRISDB1;
unsigned short int TRISD0 = 0;
 //   TRISD0_bit =TRISDB0;

 // TRISE bits
 //   IBF_TRISE_bit =TRISEB7;
 //   OBF_TRISE_bit =TRISEB6;
 //   IBOV_TRISE_bit =TRISEB5;
 //   PSPMODE_TRISE_bit =TRISEB4;
unsigned short int TRISE2 = 2;
 //   TRISE2_bit =TRISEB2;
unsigned short int TRISE1 = 1;
 //   TRISE1_bit =TRISEB1;
unsigned short int TRISE0 = 0;
 //   TRISE0_bit =TRISEB0;
