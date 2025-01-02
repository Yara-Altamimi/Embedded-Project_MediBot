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
int rate[10]; // array to hold last ten IBI values
unsigned long sampleCounter = 0; // used to determine pulse timing
unsigned long lastBeatTime = 0; // used to find IBI
int Peak = 512; // used to find peak in pulse wave, seeded
int Trough = 512; // used to find trough in pulse wave, seeded
int thresh = 512; // used to find instant moment of heart beat, seeded
int amp = 100; // used to hold amplitude of pulse waveform, seeded
bit firstBeat; // used to seed rate array so we startup with reasonable BPM
bit secondBeat; // used to seed rate array so we startup with reasonable BPM
int pulsePin = 0; // Pulse Sensor purple wire connected to analog pin 0
int blinkPin = 13; // pin to blink led at each beat

int runningTotal = 0; // clear the runningTotal variable
// these variables are volatile because they are used during the interrupt service routine!
unsigned int BPM; // used to hold the pulse rate
unsigned int Signal; // holds the incoming raw data
unsigned int IBI = 600; // holds the time between beats, must be seeded!
bit Pulse; // true when pulse wave is high, false when it's low
bit QS;
int N_cnt, P_cnt;
int i = 0;
void Init()
{
        OPTION_REG = 0x87; // Use internal clock Fosc/4 with a prescaler of 256
        // Fosc=8MHz ==> FTMR0 = 8MHz/4 = 2MHz, TMR0 will increment every 1/2MHz * prescaler
        // 0.5uS * 256 = 128uS (per increment)
        TMR0 = 248; // will count 8 times before the overflow (8 * 128uS = 1ms)
        INTCON = 0b11100000; // GIE, T0IE, peripheral interrupt
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
void interrupt() {
        if (INTCON & 0x04) { // TMR0 Overflow interrupt, will get here every 1ms
                TMR0 = 240;
                tick++;

                //READ HEART RATE FROM LCD
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

                // NOW IT'S TIME TO LOOK FOR THE HEART BEAT
                // signal surges up in value every time there is a pulse
                if (N_cnt > 250) { // avoid high frequency noise
                        if ((Signal > thresh) && (Pulse == FALSE) && (N_cnt > (IBI / 5) * 3)) {
                                Pulse = TRUE; // set the Pulse flag when we think there is a pulse
                                IBI = sampleCounter - lastBeatTime; // measure time between beats in mS
                                lastBeatTime = sampleCounter; // keep track of time for next pulse

                                if (secondBeat) { // if this is the second beat, if secondBeat == TRUE
                                        secondBeat = FALSE; // clear secondBeat flag
                                        for (i = 0; i <= 9; i++) { // seed the running total to get a realisitic BPM at startup
                                                rate[i] = IBI;
                                        }
                                }

                                if (firstBeat) { // if it's the first time we found a beat, if firstBeat == TRUE
                                        firstBeat = FALSE; // clear firstBeat flag
                                        secondBeat = TRUE; // set the second beat flag

                                        return; // IBI value is unreliable so discard it
                                }


                                // keep a running total of the last 10 IBI values
                                runningTotal = 0; // clear the runningTotal variable

                                for (i = 0; i <= 8; i++) { // shift data in the rate array
                                        rate[i] = rate[i + 1]; // and drop the oldest IBI value
                                        runningTotal += rate[i]; // add up the 9 oldest IBI values
                                }

                                rate[9] = IBI; // add the latest IBI to the rate array
                                runningTotal += rate[9]; // add the latest IBI to runningTotal
                                runningTotal /= 10; // average the last 10 IBI values
                                BPM = 60000 / runningTotal; // how many beats can fit into a minute? that's BPM!
                                QS = TRUE; // set Quantified Self flag
                                // QS FLAG IS NOT CLEARED INSIDE THIS ISR
                        }
                }

                if (Signal < thresh && Pulse == TRUE) { // when the values are going down, the beat is over

                        Pulse = FALSE; // reset the Pulse flag so we can do it again
                        amp = P_cnt - Trough; // get amplitude of the pulse wave
                        thresh = amp / 2 + Trough; // set thresh at 50% of the amplitude
                        P_cnt = thresh; // reset these for next time
                        Trough = thresh;
                }

                if (N_cnt > 2500) { // if 2.5 seconds go by without a beat
                        thresh = 512; // set thresh default
                        P_cnt = 512; // set P default
                        Trough = 512; // set T default
                        lastBeatTime = sampleCounter; // bring the lastBeatTime up to date
                        firstBeat = TRUE; // set these to avoid noise
                        secondBeat = FALSE; // when we get the heartbeat back
                }
                INTCON &= 0xFB; // Clear T0IF
        }
}

void main() {
        int g;

        Pulse = FALSE;
        QS = FALSE;
        firstBeat = TRUE;
        secondBeat = FALSE;
        Lcd_Init(); //initialize LCD
        Lcd_Cmd(_LCD_CLEAR); // Clear display
        Delay_ms(200);
        Lcd_Cmd(_LCD_CURSOR_OFF);
        Delay_ms(200);
        Lcd_Out(1, 1, intro_msg);
        Delay_ms(1500); // First row
        for (g = 0; g < sizeof(intro_msg) - 16; g++) { // Move text to the right 4 times
                Lcd_Cmd(_LCD_SHIFT_LEFT);
                Delay_ms(250);
        }

        Lcd_Cmd(_LCD_CLEAR); // Clear display
        Delay_ms(200);
        ADC_Init();


        while (1) {
                if (QS) { //New Pulse detected
                        // WE SHOULD CLEAR THE QS FLAG HERE : QS = FALSE;
                        Lcd_Out(1, 1, "HEART RATE (BPM)");
                        Lcd_Out(2, 1, " ");
                        IntToStr(BPM, temp_str);
                        Lcd_Out(2, 8, temp_str);
                        Delay_ms(2000);
                }


        }
}
