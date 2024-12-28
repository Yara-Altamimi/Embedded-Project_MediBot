



/*
TODO:
- support structs
- see about these
	- code, data, rx, sfr, ldm, at, sbit, bit, iv
*/






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





/*
MikroC INFO:

	- Number of the allowed nested calls decreases by one
	if you use any of the following operators in the code: * / %.

	- // puts x in data ram (explicitely mention)
	data unsigned char x;

	- this has a problem when written separately (read -> modify -> write)
	PORTB.B0 = 1;
	PORTB.B1 = 1;
	because reading the port is from the actuall pin
*/

/*
here we initialize all our ports and other things
we can also make a reset function when MCLR is pressed
*/
void Init()
{
	OPTION_REG = 0x87; // Use internal clock Fosc/4 with a prescaler of 256
	// Fosc=8MHz ==> FTMR0 = 8MHz/4 = 2MHz, TMR0 will increment every 1/2MHz * prescaler
	// 0.5uS * 256 = 128uS (per increment)
	TMR0 = 248; // will count 8 times before the overflow (8 * 128uS = 1ms)
	INTCON = 0b11100000; // GIE, T0IE, peripheral interrupt
}

void interrupt() {
	if (INTCON & 0x04) { // TMR0 Overflow interrupt, will get here every 1ms
		TMR0 = 248;
		tick++;
		INTCON &= 0xFB; // Clear T0IF
	}
}

void Delay(int const x) {
	tick = 0;
	while (tick < x);
}

void ADC_init(void) {
	ADCON0 = 0x41;//ON, Channel 0, Fosc/16== 500KHz, Dont Go
	ADCON1 = 0xCE;// RA0 Analog, others are Digital, Right Allignment,
}
unsigned int ADC_read(void) {
	ADCON0 = ADCON0 | 0x04;//GO
	while (ADCON0 & 0x04);//wait until DONE
	return (ADRESH << 8) | ADRESL;
}

/*
TODO: we can read sensors and relate them to global variables for easier use
*/
void ReadSensors();


typedef enum Direction
{
	godam, wara, yameen, yasar
};
void MoveRobot(Direction d);
void StopRobot();

/* CCP related modules*/
void CCPPWM_init(void) { //Configure CCP1 and CCP2 at 2ms period with 50% duty cycle
	T2CON = 0b00000111;//enable Timer2 at Fosc/4 with 1:16 prescaler (8 uS percount 2000uS to count 250 counts)
	CCP2CON = 0x0C;//enable PWM for CCP2
	CCP1CON = 0x0C;//enable PWM for CCP1
	PR2 = 250;// 250 counts =8uS *250 =2ms period
	CCPR2L = 0;
	CCPR1L = 0;

}
void motor(unsigned int speed) {
	CCPR2L = speed;
}
void motor2(unsigned int speed) {
	CCPR1L = speed;
}



void main()
{

}


