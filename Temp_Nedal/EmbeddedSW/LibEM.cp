#line 1 "D:/GitHub Repos/Embedded-Project_MediBot/Temp_Nedal/EmbeddedSW/LibEM.c"
sbit LCD_RS at RD2_bit;
sbit LCD_EN at RD3_bit;
sbit LCD_D4 at RD4_bit;
sbit LCD_D5 at RD5_bit;
sbit LCD_D6 at RD6_bit;
sbit LCD_D7 at RD7_bit;

sbit LCD_RS_Direction at TRISD2_bit;
sbit LCD_EN_Direction at TRISD3_bit;
sbit LCD_D4_Direction at TRISD4_bit;
sbit LCD_D5_Direction at TRISD5_bit;
sbit LCD_D6_Direction at TRISD6_bit;
sbit LCD_D7_Direction at TRISD7_bit;

enum { FALSE = 0, TRUE = 1 };
char intro_msg[] = "ELECTRONIC HEART RATE MONITOR";
char temp_str[8], disp_result;
unsigned int tick;
int rate[10];
unsigned long sampleCounter = 0;
unsigned long lastBeatTime = 0;
int Peak = 512;
int Trough = 512;
int thresh = 512;
int amp = 100;
bit firstBeat;
bit secondBeat;
int pulsePin = 0;
int blinkPin = 13;

int runningTotal = 0;

unsigned int BPM;
unsigned int Signal;
unsigned int IBI = 600;
bit Pulse;
bit QS;
int N_cnt, P_cnt;
int i = 0;
void Init()
{
 OPTION_REG = 0x87;


 TMR0 = 248;
 INTCON = 0b11100000;
}
void ADC_init(void) {
 ADCON0 = 0x41;
 ADCON1 = 0xCE;
}
unsigned int ADC_read(void) {
 ADCON0 = ADCON0 | 0x04;
 while (ADCON0 & 0x04);
 return (ADRESH << 8) | ADRESL;
}
void interrupt() {
 if (INTCON & 0x04) {
 TMR0 = 240;
 tick++;


 Signal = ADC_read();
 sampleCounter += 2;
 N_cnt = sampleCounter - lastBeatTime;
 if (Signal < thresh && N_cnt >(IBI / 5) * 3) {
 if (Signal < Trough) {
 Trough = Signal;
 }
 }
 if (Signal > thresh && Signal > P_cnt) {
 P_cnt = Signal;
 }



 if (N_cnt > 250) {
 if ((Signal > thresh) && (Pulse == FALSE) && (N_cnt > (IBI / 5) * 3)) {
 Pulse = TRUE;
 IBI = sampleCounter - lastBeatTime;
 lastBeatTime = sampleCounter;

 if (secondBeat) {
 secondBeat = FALSE;
 for (i = 0; i <= 9; i++) {
 rate[i] = IBI;
 }
 }

 if (firstBeat) {
 firstBeat = FALSE;
 secondBeat = TRUE;

 return;
 }



 runningTotal = 0;

 for (i = 0; i <= 8; i++) {
 rate[i] = rate[i + 1];
 runningTotal += rate[i];
 }

 rate[9] = IBI;
 runningTotal += rate[9];
 runningTotal /= 10;
 BPM = 60000 / runningTotal;
 QS = TRUE;

 }
 }

 if (Signal < thresh && Pulse == TRUE) {

 Pulse = FALSE;
 amp = P_cnt - Trough;
 thresh = amp / 2 + Trough;
 P_cnt = thresh;
 Trough = thresh;
 }

 if (N_cnt > 2500) {
 thresh = 512;
 P_cnt = 512;
 Trough = 512;
 lastBeatTime = sampleCounter;
 firstBeat = TRUE;
 secondBeat = FALSE;
 }
 INTCON &= 0xFB;
 }
}

void main() {
 int g;

 Pulse = FALSE;
 QS = FALSE;
 firstBeat = TRUE;
 secondBeat = FALSE;
 Lcd_Init();
 Lcd_Cmd(_LCD_CLEAR);
 Delay_ms(200);
 Lcd_Cmd(_LCD_CURSOR_OFF);
 Delay_ms(200);
 Lcd_Out(1, 1, intro_msg);
 Delay_ms(1500);
 for (g = 0; g < sizeof(intro_msg) - 16; g++) {
 Lcd_Cmd(_LCD_SHIFT_LEFT);
 Delay_ms(250);
 }

 Lcd_Cmd(_LCD_CLEAR);
 Delay_ms(200);
 ADC_Init();


 while (1) {
 if (QS == TRUE) {
 Lcd_Out(1, 1, "HEART RATE (BPM)");
 Lcd_Out(2, 1, " ");
 IntToStr(BPM, temp_str);
 Lcd_Out(2, 8, temp_str);
 Delay_ms(2000);
 }


 }
}
