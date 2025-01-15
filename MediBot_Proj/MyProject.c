#define BIT0 (1<<0)
#define BIT1 (1<<1)
#define BIT2 (1<<2)
#define BIT3 (1<<3)
#define BIT4 (1<<4)
#define BIT5 (1<<5)
#define BIT6 (1<<6)
#define BIT7 (1<<7)
#define GET_BIT0(VAR) VAR & BIT0
#define GET_BIT1(VAR) VAR & BIT1
#define GET_BIT2(VAR) VAR & BIT2
#define GET_BIT3(VAR) VAR & BIT3
#define GET_BIT4(VAR) VAR & BIT4
#define GET_BIT5(VAR) VAR & BIT5
#define GET_BIT6(VAR) VAR & BIT6
#define GET_BIT7(VAR) VAR & BIT7
#define IS_BIT0_HIGH(VAR) GET_BIT0(VAR)
#define IS_BIT1_HIGH(VAR) GET_BIT1(VAR)
#define IS_BIT2_HIGH(VAR) GET_BIT2(VAR)
#define IS_BIT3_HIGH(VAR) GET_BIT3(VAR)
#define IS_BIT4_HIGH(VAR) GET_BIT4(VAR)
#define IS_BIT5_HIGH(VAR) GET_BIT5(VAR)
#define IS_BIT6_HIGH(VAR) GET_BIT6(VAR)
#define IS_BIT7_HIGH(VAR) GET_BIT7(VAR)
#define IS_HIGH(VAR) VAR == 0xFF
#define IS_BIT0_LOW(VAR) ~(GET_BIT0(VAR))
#define IS_BIT1_LOW(VAR) ~(GET_BIT1(VAR))
#define IS_BIT2_LOW(VAR) ~(GET_BIT2(VAR))
#define IS_BIT3_LOW(VAR) ~(GET_BIT3(VAR))
#define IS_BIT4_LOW(VAR) ~(GET_BIT4(VAR))
#define IS_BIT5_LOW(VAR) ~(GET_BIT5(VAR))
#define IS_BIT6_LOW(VAR) ~(GET_BIT6(VAR))
#define IS_BIT7_LOW(VAR) ~(GET_BIT7(VAR))
#define IS_LOW(VAR) VAR == 0x00
#define SET_BIT0_HIGH(VAR) VAR |= BIT0
#define SET_BIT1_HIGH(VAR) VAR |= BIT1
#define SET_BIT2_HIGH(VAR) VAR |= BIT2
#define SET_BIT3_HIGH(VAR) VAR |= BIT3
#define SET_BIT4_HIGH(VAR) VAR |= BIT4
#define SET_BIT5_HIGH(VAR) VAR |= BIT5
#define SET_BIT6_HIGH(VAR) VAR |= BIT6
#define SET_BIT7_HIGH(VAR) VAR |= BIT7
#define SET_HIGH(VAR) VAR = 0xFF
#define SET_BIT0_LOW(VAR) VAR &= ~BIT0
#define SET_BIT1_LOW(VAR) VAR &= ~BIT1
#define SET_BIT2_LOW(VAR) VAR &= ~BIT2
#define SET_BIT3_LOW(VAR) VAR &= ~BIT3
#define SET_BIT4_LOW(VAR) VAR &= ~BIT4
#define SET_BIT5_LOW(VAR) VAR &= ~BIT5
#define SET_BIT6_LOW(VAR) VAR &= ~BIT6
#define SET_BIT7_LOW(VAR) VAR &= ~BIT7
#define SET_LOW(VAR) VAR = 0x00

//#define HRDIR TRISA.B0
//#define HRPIN PORTA.B0
//#define BUZZERDIR TRISA.B5
//#define BUZZERPIN PORTA.B5
//
//
//#define BTNENABLEHRDIR TRISB.B5
//#define BTNENABLEHRPIN PORTB.B5
//#define LEDREDDIR TRISB.B6
//#define LEDREDPIN PORTB.B6
//#define LEDGREENDIR TRISB.B7
//#define LEDGREENPIN PORTB.B7
//
//
//
//#define SONICTRIGDIR TRISC.B3
//#define SONICTRIGPIN PORTC.B3
//#define SONICECHODIR TRISC.B4
//#define SONICECHOPIN PORTC.B4
//#define IRLDIR TRISC.B5
//#define IRLPIN PORTC.B5
//#define IRRDIR TRISC.B6
//#define IRRPIN PORTC.B6
//
//
//#define BTNDISPDIR TRISD.B0
//#define BTNDISPPIN PORTD.B0
//#define DHT11DIR TRISD.B1
//#define DHT11PIN PORTD.B1
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

#define ARRAYLEN(arr) sizeof(arr) / arr[0]
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
unsigned int angle;                                                  // Count value of high - pertaining to the angle
unsigned char HL;                                                    // High Low
unsigned int analog_read;
unsigned int count;
void mydelayms(unsigned int count)
{
    count /= 2;
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
    ADCON0 = 0x41;           // ON, Channel 0, Fosc/16== 500KHz, Dont Go
    ADCON1 = 0xC4;           // RA0 Analog, others are Digital, Right Allignment,
    TRISA = 0x01;
}
unsigned int ATD_read(void) {
    SET_BIT2_HIGH(ADCON0);  // GO
    while (IS_BIT2_HIGH(ADCON0));    // wait until DONE
    return (ADRESH << 8) | ADRESL;
}
unsigned int Distance() {
    //Trigger on RC3 ,, Echo on RC4

    int tdist = 5;
    SET_BIT5_HIGH(INTCON);
    SET_BIT3_HIGH(PORTC);               //TRIGGER HIGH
    mydelayus(10);               //10uS Delay
    SET_BIT3_LOW(PORTC);           //TRIGGER LOW

    while (IS_BIT4_LOW(PORTC));           //Waiting for Echo
    TMR0 = 0;
    oftmr0 = 0;
    while (IS_BIT4_HIGH(PORTC));            //Waiting for Echo goes LOW
    tdist = oftmr0 * 256 + TMR0;   //Reads Timer Value
    tdist = tdist / 58.82;                //Converts Time to Distance
    SET_BIT5_LOW(INTCON);
    return tdist;
}

void CCPPWM_init() { //Configure CCP1 at 2ms period with 50% duty cycle
    T2CON = 0b00000111;//enable Timer2 at Fosc/4 with 1:16 prescaler (8 uS percount 2000uS to count 250 counts)
    CCP1CON = 0x0C;//enable PWM for CCP1
    PR2 = 250;// 250 counts =8uS *250 =2ms period
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

        SET_BIT1_LOW(PORTB);
        SET_BIT2_HIGH(PORTB);
        SET_BIT3_HIGH(PORTB);
        SET_BIT4_LOW(PORTB);

    }
    else if (dir == 1)
    {
        SET_BIT1_HIGH(PORTB);
        SET_BIT2_LOW(PORTB);
        SET_BIT3_LOW(PORTB);
        SET_BIT4_HIGH(PORTB);

    }
    else if (dir == 2)
    {
        SET_BIT1_HIGH(PORTB);
        SET_BIT2_LOW(PORTB);
        SET_BIT3_HIGH(PORTB);
        SET_BIT4_LOW(PORTB);

    }
    else if (dir == 3)
    {
        SET_BIT1_LOW(PORTB);
        SET_BIT2_HIGH(PORTB);
        SET_BIT3_LOW(PORTB);
        SET_BIT4_HIGH(PORTB);

    }
    MotorSpeed(200);
}
void Init()
{
    HL = 1;                // start high
    SET_BIT3_LOW(TRISC);
    SET_BIT4_HIGH(TRISC);
    SET_BIT5_HIGH(TRISC);
    SET_BIT6_HIGH(TRISC);
    SET_BIT2_HIGH(TRISE);
    SET_BIT5_LOW(TRISA);
    TRISD = 0;
    SET_BIT1_LOW(TRISC);
    SET_BIT2_LOW(TRISC);
    SET_BIT0_HIGH(TRISB);
    SET_BIT1_LOW(TRISB);
    SET_BIT2_LOW(TRISB);
    SET_BIT3_LOW(TRISB);
    SET_BIT4_LOW(TRISB);

    ATD_init();
    CCPPWM_init();
    OPTION_REG = 0x00;
    TMR0 = 0;
    oftmr0 = 0;

    TMR1L = 0;
    TMR1H = 0;
    T1CON = 0x01;
    INTCON = 0B11010000;
    SET_BIT2_HIGH(PIE1);
    SET_BIT1_HIGH(PIE1);
    SET_BIT0_HIGH(PIE2);
    CCP2CON = 0x08;        // Compare mode, set output on match
    CCPR2L = 2000;         // Value preset in a program to compare the TMR1L value to
    CCPR2H = 2000 >> 8;      // Value preset in a program to compare the TMR1H value to            - 1ms

    direction(0);
}



unsigned int GetAngle()
{
    analog_read = ATD_read();
    analog_read = analog_read >> 2;  // divided by 4 ==> 0-255
    //angle = 0.5ms -> 1000 counts; 1.75ms -> 3500 counts
    count = 1000 + ((analog_read * 25) / 2.55);     //angle= 1000 + ((k*2500)/255); 1000count=500uS to 3500count =1750us
    if (count < 1000) count = 1000;      // 0.5ms
    if (count > 3500) count = 3500;      // 1.75ms
    return count;
}







unsigned int ReadSpeed()
{
    unsigned int v = ATD_read();
    return (((v >> 2) * 250) / 255);// 0-250
}
void servoserve()
{
    angle += 600;
}
void interrupt(void) {
    if (IS_BIT1_HIGH(INTCON))
    {
        FollowingMode = (FollowingMode == 1) ? 0 : 1;
        SET_BIT1_LOW(INTCON);
    }
    else if (IS_BIT2_HIGH(INTCON))
    {
        TMR0 = 0;
        oftmr0++;
        SET_BIT2_LOW(INTCON);
    }
    else if (IS_BIT0_HIGH(PIR2)) {                                           // CCP1 interrupt
        if (HL) {                                // high
            CCPR2H = angle >> 8;
            CCPR2L = angle;
            HL = 0;                      // next time low
            CCP2CON = 0x09;              // compare mode, clear output on match
            TMR1H = 0;
            TMR1L = 0;
        }
        else {                                          //low
            CCPR2H = (40000 - angle) >> 8;       // 40000 counts correspond to 20ms
            CCPR2L = (40000 - angle);
            CCP2CON = 0x08;             // compare mode, set output on match
            HL = 1;                     //next time High
            TMR1H = 0;
            TMR1L = 0;
        }
        SET_BIT0_LOW(PIR2);
    }
    else if (IS_BIT1_HIGH(PIR1))
    {
        tick++;
        SET_BIT1_LOW(PIR1);
    }
}


unsigned char Check, T_byte1, T_byte2,
RH_byte1, RH_byte2, Ch;
unsigned Temp, RH, Sum;
void StartSignal() {
    SET_BIT1_LOW(TRISD);
    SET_BIT1_LOW(PORTD);
    mydelayms(18);
    SET_BIT1_HIGH(PORTD);
    mydelayus(30);
    SET_BIT1_HIGH(TRISD);
}
//////////////////////////////
void CheckResponse() {
    Check = 0;
    mydelayus(40);
    if (IS_BIT1_LOW(PORTD)) {
        mydelayus(80);
        if (IS_BIT1_HIGH(PORTD)) Check = 1; mydelayus(40);
    }
}
//////////////////////////////
char ReadData() {
    char i, j;
    for (j = 0; j < 8; j++) {
        while (IS_BIT1_LOW(PORTD));
        mydelayus(30);
        if (IS_BIT1_LOW(PORTD))
            i &= ~(1 << (7 - j));
        else {
            i |= (1 << (7 - j));
            while (IS_BIT1_HIGH(PORTD));
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
            Lcd_Cmd(_LCD_CURSOR_OFF); // cursor off
            Lcd_Cmd(_LCD_CLEAR); // clear LCD
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
    Lcd_Cmd(_LCD_CURSOR_OFF); // cursor off
    Lcd_Cmd(_LCD_CLEAR); // clear LCD
    Init();
    angle = 1200;

    while (1) {
        if (FollowingMode)
        {
            SET_BIT7_HIGH(PORTB);
            dis = Distance();
            if (dis <= 20)
            {
                CCPR1L = 0;
            }
            else
            {
                direction(0);
            }
            SET_BIT0_LOW(PIE2);
            dht11disp();
        }
        else
        {
            SET_BIT7_LOW(PORTB);
            SET_BIT0_HIGH(PIE2);
            CCPR1L = 0;
            if (IS_BIT2_HIGH(PORTE))
            {
                angle += 1000;
                if (angle >= 3500) angle = 1250;
                for (i = 0; i < ARRAYLEN(naghama); i++)
                {
                    if (naghama[i])
                        SET_BIT5_HIGH(PORTA);
                    else
                        SET_BIT5_LOW(PORTA);
                }
            }
            Lcd_Cmd(_LCD_CLEAR);
            Lcd_Out(1, 1, "see pill disp");
            mydelayms(250);
            SET_BIT5_LOW(PORTA);
        }
    }
}
