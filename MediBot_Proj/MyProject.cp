#line 1 "C:/Users/user1/Desktop/MediBot/MyProject.c"
#line 83 "C:/Users/user1/Desktop/MediBot/MyProject.c"
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


unsigned char naghama[] = { 1, 0, 1, 0, 1, 0, 1 };
unsigned char FollowingMode = 1;
unsigned int speed;
unsigned int v;
unsigned int dis = 0;
char dist[10];
char servot[12];
unsigned int oftmr0 = 0;
unsigned int tick;
unsigned char myscaledVoltage;
unsigned char mysevenseg[10] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F };
unsigned int angle;
unsigned char HL;
unsigned int analog_read;
unsigned int count;
void mydelayms(unsigned int count)
{
 count *= 2;
 tick = 0;
 while (tick < count);
}
int i;
void mydelayus(unsigned int count)
{
 for (i = 0; i < 2*count; i++)
 {
 asm NOP;
 }
}
void ATD_init(void) {
 ADCON0 = 0x41;
 ADCON1 = 0xC4;
 TRISA = 0x01;
}
unsigned int ATD_read(void) {
  ADCON0 |= (1<<2) ;
 while ( ADCON0 & (1<<2) );
 return (ADRESH << 8) | ADRESL;
}
unsigned int Distance() {


 int tdist = 5;
  INTCON |= (1<<5) ;
  PORTC |= (1<<3) ;
 mydelayus(10);
  PORTC &= ~ (1<<3) ;

 while ( ~( PORTC & (1<<4) ) );
 TMR0 = 0;
 oftmr0 = 0;
 while ( PORTC & (1<<4) );
 tdist = oftmr0 * 256 + TMR0;
 tdist = tdist / 58.82;
  INTCON &= ~ (1<<5) ;
 return tdist;
}

void CCPPWM_init() {
 T2CON = 0b00000111;
 CCP1CON = 0x0C;
 PR2 = 250;
 CCPR1L = 0;
}void MotorSpeed(unsigned int speed) {
 CCPR1L = speed;
}
void direction(char dir)
{
 if (dir == 4)
 {
 MotorSpeed(0);
 return;
 }
 else if (dir == 0)
 {

  PORTB &= ~ (1<<1) ;
  PORTB |= (1<<2) ;
  PORTB |= (1<<3) ;
  PORTB &= ~ (1<<4) ;

 }
 else if (dir == 1)
 {
  PORTB |= (1<<1) ;
  PORTB &= ~ (1<<2) ;
  PORTB &= ~ (1<<3) ;
  PORTB |= (1<<4) ;

 }
 else if (dir == 2)
 {
  PORTB |= (1<<1) ;
  PORTB &= ~ (1<<2) ;
  PORTB |= (1<<3) ;
  PORTB &= ~ (1<<4) ;

 }
 else if (dir == 3)
 {
  PORTB &= ~ (1<<1) ;
  PORTB |= (1<<2) ;
  PORTB &= ~ (1<<3) ;
  PORTB |= (1<<4) ;

 }
 MotorSpeed(200);
}
void Init()
{
 HL = 1;
  TRISC &= ~ (1<<3) ;
  TRISC |= (1<<4) ;
  TRISC |= (1<<5) ;
  TRISC |= (1<<6) ;
  TRISE |= (1<<2) ;
  TRISA &= ~ (1<<5) ;
 TRISD = 0;
  TRISC &= ~ (1<<1) ;
  TRISC &= ~ (1<<2) ;
  TRISB |= (1<<0) ;
  TRISB &= ~ (1<<1) ;
  TRISB &= ~ (1<<2) ;
  TRISB &= ~ (1<<3) ;
  TRISB &= ~ (1<<4) ;

 ATD_init();
 CCPPWM_init();
 OPTION_REG = 0x00;
 TMR0 = 0;
 oftmr0 = 0;

 TMR1L = 0;
 TMR1H = 0;
 T1CON = 0x01;
 INTCON = 0B11010000;
  PIE1 |= (1<<2) ;
  PIE1 |= (1<<1) ;
  PIE2 |= (1<<0) ;
 CCP2CON = 0x08;
 CCPR2L = 2000;
 CCPR2H = 2000 >> 8;

 direction(0);
}



unsigned int GetAngle()
{
 analog_read = ATD_read();
 analog_read = analog_read >> 2;

 count = 1000 + ((analog_read * 25) / 2.55);
 if (count < 1000) count = 1000;
 if (count > 3500) count = 3500;
 return count;
}







unsigned int ReadSpeed()
{
 unsigned int v = ATD_read();
 return (((v >> 2) * 250) / 255);
}
void servoserve()
{
 angle += 600;
}
void interrupt(void) {
 if ( INTCON & (1<<1) )
 {
 FollowingMode = (FollowingMode == 1) ? 0 : 1;
  INTCON &= ~ (1<<1) ;
 }
 else if ( INTCON & (1<<2) )
 {
 TMR0 = 0;
 oftmr0++;
  INTCON &= ~ (1<<2) ;
 }
 else if ( PIR2 & (1<<0) ) {
 if (HL) {
 CCPR2H = angle >> 8;
 CCPR2L = angle;
 HL = 0;
 CCP2CON = 0x09;
 TMR1H = 0;
 TMR1L = 0;
 }
 else {
 CCPR2H = (40000 - angle) >> 8;
 CCPR2L = (40000 - angle);
 CCP2CON = 0x08;
 HL = 1;
 TMR1H = 0;
 TMR1L = 0;
 }
  PIR2 &= ~ (1<<0) ;
 }
 else if ( PIR1 & (1<<1) )
 {
 tick++;
  PIR1 &= ~ (1<<1) ;
 }
}


unsigned char Check, T_byte1, T_byte2,
RH_byte1, RH_byte2, Ch;
unsigned Temp, RH, Sum;
void StartSignal() {
  TRISD &= ~ (1<<1) ;
  PORTD &= ~ (1<<1) ;
 mydelayms(18);
  PORTD |= (1<<1) ;
 mydelayus(30);
  TRISD |= (1<<1) ;
}

void CheckResponse() {
 Check = 0;
 mydelayus(40);
 if ( ~( PORTD & (1<<1) ) ) {
 mydelayus(80);
 if ( PORTD & (1<<1) ) Check = 1; mydelayus(40);
 }
}

char ReadData() {
 char i, j;
 for (j = 0; j < 8; j++) {
 while ( ~( PORTD & (1<<1) ) );
 mydelayus(30);
 if ( ~( PORTD & (1<<1) ) )
 i &= ~(1 << (7 - j));
 else {
 i |= (1 << (7 - j));
 while ( PORTD & (1<<1) );
 }
 }
 return i;
}
void dht11disp()
{
 StartSignal();
 CheckResponse();
 if (Check == 1) {
 RH_byte1 = ReadData();
 RH_byte2 = ReadData();
 T_byte1 = ReadData();
 T_byte2 = ReadData();
 Sum = ReadData();
 if (Sum == ((RH_byte1 + RH_byte2 + T_byte1 + T_byte2) & 0XFF)) {
 Temp = T_byte1;
 RH = RH_byte1;
 Lcd_Cmd(_LCD_CLEAR);
 Lcd_Out(1, 6, "Temp: C");
 Lcd_Out(2, 2, "Humidity: %");
 LCD_Chr(1, 12, 48 + ((Temp / 10) % 10));
 LCD_Chr(1, 13, 48 + (Temp % 10));
 LCD_Chr(2, 12, 48 + ((RH / 10) % 10));
 LCD_Chr(2, 13, 48 + (RH % 10));
 }
 else {
 Lcd_Cmd(_LCD_CURSOR_OFF);
 Lcd_Cmd(_LCD_CLEAR);
 Lcd_Out(1, 1, "Check sum error");
 }
 }
 else {

 Lcd_Out(1, 3, "No response");
 Lcd_Out(2, 1, "from the sensor");
 Lcd_Cmd(_LCD_CLEAR);
 }
 mydelayms(1000);
}
void DCMOTOR()
{
 dis = Distance();
}

void main() {
 Lcd_Init();
 Lcd_Cmd(_LCD_CURSOR_OFF);
 Lcd_Cmd(_LCD_CLEAR);
 Init();
 angle = 1200;

 while (1) {
 if (FollowingMode)
 {
  PORTB |= (1<<7) ;
 dis = Distance();
 if (dis <= 20)
 {
 CCPR1L = 0;
 }
 else
 {
 direction(0);
 }
  PIE2 &= ~ (1<<0) ;
 dht11disp();
 }
 else
 {
  PORTB &= ~ (1<<7) ;
  PIE2 |= (1<<0) ;
 CCPR1L = 0;
 if ( PORTE & (1<<2) )
 {
 angle += 1000;
 if (angle >= 3500) angle = 1250;
 for (i = 0; i <  sizeof(naghama) / naghama[0] ; i++)
 {
 if (naghama[i])
  PORTA |= (1<<5) ;
 else
  PORTA &= ~ (1<<5) ;
 }
 }
 Lcd_Cmd(_LCD_CLEAR);
 Lcd_Out(1, 1, "see pill disp");
 mydelayms(250);
  PORTA &= ~ (1<<5) ;
 }
 }
}
