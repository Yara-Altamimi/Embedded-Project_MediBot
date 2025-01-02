



/*
TODO:
- support structs
- see about these
	- code, data, rx, sfr, ldm, at, sbit, bit, iv
*/
//#include <stdint.h>
//#include "PIC16F877A.h"



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
//typedef enum Direction
//{
//	godam, wara, yameen, yasar
//} Direction;
#define DHT11_PIN PORTB.RB5       // Define the DHT11 data pin
#define DHT11_DIR TRISB.TRISB5    // Define the direction register for the DHT11 pin

unsigned char mysevenseg[10] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F };
int tick_ms, tick_us;
void Timer2_Init(void) {
	T2CON.T2CKPS0 = 0;    // Prescaler = 1:1
	T2CON.T2CKPS1 = 0;
	PR2 = 7;        // Set PR2 for 1µs delay (based on 8 MHz clock)
	TMR2 = 0;       // Clear Timer2 register
	T2CON.TMR2ON = 1;     // Enable Timer2
	PIR1.TMR2IF = 0;     // Clear Timer2 interrupt flag
	PIE1.TMR2IE = 1;     // Enable Timer2 interrupt
	INTCON.PEIE = 1;       // Enable peripheral interrupts
	INTCON.GIE = 1;        // Enable global interrupts
}
void Init()
{
	DHT11_DIR = 0;
	OPTION_REG = 0x87; // Use internal clock Fosc/4 with a prescaler of 256
	ADCON1 = 0x06;
	// Fosc=8MHz ==> FTMR0 = 8MHz/4 = 2MHz, TMR0 will increment every 1/2MHz * prescaler
	// 0.5uS * 256 = 128uS (per increment)
	TMR0 = 248; // will count 8 times before the overflow (8 * 128uS = 1ms)
	INTCON = 0b11100000; // GIE, T0IE, peripheral interrupt
	Timer2_Init();
}

void interrupt() {
	if (INTCON & 0x04) { // TMR0 Overflow interrupt, will get here every 1ms
		TMR0 = 248;
		tick_ms++;
		INTCON &= 0xFB; // Clear T0IF
	}
	if (TMR2IF) {               // Check if Timer2 overflowed
		TMR2 = 0;
		tick_us++;
		PIR1.TMR2IF = 0;             // Clear the interrupt flag
	}
}
//#define Delayms(d) Delay_ms(d)
//#define Delayus(d) Delay_us(d)
void Delayms(int const x)
{
		Delay_ms(x);
		//tick_ms = 0;
		//while (tick_ms < x);
}
void Delayus(int const x)
{
		Delay_us(x);
		//tick_us = 0;
		//while (tick_us < x);
}

void ADC_init(void)
{
	ADCON0 = 0x41;//ON, Channel 0, Fosc/16== 500KHz, Dont Go
	ADCON1 = 0xCE;// RA0 Analog, others are Digital, Right Allignment,
}
unsigned int ADC_read(void)
{
	ADCON0 = ADCON0 | 0x04;//GO
	while (ADCON0 & 0x04);//wait until DONE
	return (ADRESH << 8) | ADRESL;
}

/*
TODO: we can read sensors and relate them to global variables for easier use
*/
unsigned int temperature, humidity;


unsigned char DHT11_ReadByte(void)
{
	unsigned char dgdata;
	unsigned char i;
	for (i = 0; i < 8; i++)
	{
		while (!DHT11_PIN);     // Wait for the pin to go high
		Delayus(30);
		if (DHT11_PIN)
		{        // If the pin is still high after 30us
			unsigned char temp = (1 << (7 - i));
			dgdata = dgdata | temp;
		}
		while (DHT11_PIN);      // Wait for the pin to go low again
	}

	return dgdata;
}

unsigned char DHT11_CheckResponse(void)
{
	unsigned char response = 0;

	Delayus(40);
	if (!DHT11_PIN)
	{          // Check if the pin is low
		Delayus(80);
		if (DHT11_PIN)
		{       // Check if the pin is high
			response = 1;
		}
		while (DHT11_PIN);     // Wait for the pin to go low again
	}

	return response;
}
void DHT11_process()
{
	if (DHT11_CheckResponse()) {
		humidity = DHT11_ReadByte();
		DHT11_ReadByte(); // Skip decimal part of humidity
		temperature = DHT11_ReadByte();
		DHT11_ReadByte(); // Skip decimal part of temperature
		DHT11_ReadByte(); // Skip checksum

	}
	// Wait for at least 2 seconds between reads
}
void DHT11_Start(void) {
	// TODO: DHT11_DIR should be initially input

	DHT11_DIR = 0;        // Set RA2 as output
	DHT11_PIN = 0;        // Pull the pin low
	Delayms(30);       // Wait for at least 18ms
	DHT11_PIN = 1;        // Pull the pin high
	Delayus(30);       // Wait for 20-40us
	DHT11_DIR = 1;        // Set RA2 as input
}
void ReadSensors()
{
	// one communication process is about 4ms
	DHT11_Start();
	DHT11_process();
	// read the 40-bit data
}


//void MoveRobot(Direction d)
//{
//
//}
//void StopRobot()
//{
//
//}

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





sbit LCD_RS at RD2_bit;
sbit LCD_EN at RD3_bit;
sbit LCD_D7 at RD7_bit;
sbit LCD_D6 at RD6_bit;
sbit LCD_D5 at RD5_bit;
sbit LCD_D4 at RD4_bit;

// Pin direction
sbit LCD_RS_Direction at TRISD2_bit;
sbit LCD_EN_Direction at TRISD3_bit;
sbit LCD_D7_Direction at TRISD7_bit;
sbit LCD_D6_Direction at TRISD6_bit;
sbit LCD_D5_Direction at TRISD5_bit;
sbit LCD_D4_Direction at TRISD4_bit;
int sdfx = 0;
char text[10] = { 0 };
void main() {
	LCD_init();
	Delay_ms(500);

	Lcd_Cmd(_LCD_CLEAR);
	Delay_ms(100);

	Lcd_Cmd(_LCD_CURSOR_OFF);
	Delay_ms(100);
	Lcd_Cmd(_LCD_CLEAR);
	Delay_ms(100);
	Init();
	while (1)
	{
		ReadSensors();
		sprintl(&text, "COUNT = %d", temperature);
		Lcd_Out(1, 1, text);
		Delay_ms(2000);
	}
}













//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// Heart Rate Monitoring using MAX30102 for PIC16F877A
// With LCD Integration

// Configuration Bits
#pragma config FOSC = HS        // High-speed Oscillator
#pragma config WDTE = OFF       // Watchdog Timer Disabled
#pragma config PWRTE = ON       // Power-up Timer Enabled
#pragma config CP = OFF         // Code Protection Disabled
#pragma config BOREN = ON       // Brown-out Reset Enabled
#pragma config LVP = OFF        // Low Voltage Programming Disabled

// Define Oscillator Frequency
#define _XTAL_FREQ 8000000 // 8MHz Oscillator Frequency

#include <stdint.h>
#include <stdbool.h>
#include "i2c.h" // Include custom I2C functions for MAX30102 communication
#include "lcd.h" // Include custom or library LCD functions

// MAX30102 I2C Address
#define MAX30102_ADDRESS 0x57

// MAX30102 Registers
#define REG_INTR_STATUS_1 0x00
#define REG_INTR_STATUS_2 0x01
#define REG_INTR_ENABLE_1 0x02
#define REG_INTR_ENABLE_2 0x03
#define REG_FIFO_WR_PTR 0x04
#define REG_FIFO_RD_PTR 0x06
#define REG_FIFO_DATA 0x07
#define REG_MODE_CONFIG 0x09
#define REG_SPO2_CONFIG 0x0A
#define REG_LED1_PA 0x0C
#define REG_LED2_PA 0x0D

// Global Variables
unsigned int heart_rate = 0;
char temp_str[16];

// Function Prototypes
void max30102_init();
void max30102_read_fifo(unsigned int* red_val, unsigned int* ir_val);
void calculate_heart_rate(unsigned int red_val, unsigned int ir_val);
void lcd_display_heart_rate();

void main() {
	unsigned int red_val = 0, ir_val = 0;

	// Initialize peripherals
	I2C_Init();
	Lcd_Init();
	max30102_init();

	Lcd_Cmd(_LCD_CLEAR);
	Lcd_Out(1, 1, "Heart Rate Monitor");
	__delay_ms(2000);

	while (1) {
		max30102_read_fifo(&red_val, &ir_val);
		calculate_heart_rate(red_val, ir_val);
		lcd_display_heart_rate();
		__delay_ms(1000);
	}
}

// MAX30102 Initialization
void max30102_init() {
	I2C_Start();
	I2C_Write(MAX30102_ADDRESS << 1);
	I2C_Write(REG_MODE_CONFIG);
	I2C_Write(0x40); // Reset the MAX30102
	I2C_Stop();

	__delay_ms(100);

	I2C_Start();
	I2C_Write(MAX30102_ADDRESS << 1);
	I2C_Write(REG_INTR_ENABLE_1);
	I2C_Write(0xC0); // Enable interrupts for new data
	I2C_Write(0x00); // Disable other interrupts
	I2C_Stop();

	I2C_Start();
	I2C_Write(MAX30102_ADDRESS << 1);
	I2C_Write(REG_SPO2_CONFIG);
	I2C_Write(0x27); // SPO2 ADC range and resolution
	I2C_Stop();

	I2C_Start();
	I2C_Write(MAX30102_ADDRESS << 1);
	I2C_Write(REG_LED1_PA);
	I2C_Write(0x24); // Set LED1 (Red) current
	I2C_Write(0x24); // Set LED2 (IR) current
	I2C_Stop();
}

// Read FIFO Data from MAX30102
void max30102_read_fifo(unsigned int* red_val, unsigned int* ir_val) {
	I2C_Start();
	I2C_Write(MAX30102_ADDRESS << 1);
	I2C_Write(REG_FIFO_DATA);
	I2C_Stop();

	I2C_Start();
	I2C_Write((MAX30102_ADDRESS << 1) | 1);
	*red_val = (I2C_Read(1) << 8) | I2C_Read(1);
	*ir_val = (I2C_Read(1) << 8) | I2C_Read(0);
	I2C_Stop();
}

// Calculate Heart Rate (Basic Implementation)
void calculate_heart_rate(unsigned int red_val, unsigned int ir_val) {
	// Simplified placeholder algorithm for demonstration purposes
	if (red_val > 50000 && ir_val > 50000) {
		heart_rate = (red_val + ir_val) / 1000; // Example calculation
	}
	else {
		heart_rate = 0; // No valid pulse detected
	}
}

// Display Heart Rate on LCD
void lcd_display_heart_rate() {
	Lcd_Cmd(_LCD_CLEAR);
	Lcd_Out(1, 1, "Heart Rate:");
	sprintf(temp_str, "%u BPM", heart_rate);
	Lcd_Out(2, 1, temp_str);
}




