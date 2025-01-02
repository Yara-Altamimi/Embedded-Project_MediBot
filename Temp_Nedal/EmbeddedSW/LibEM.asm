
_Init:

;LibEM.c,40 :: 		void Init()
;LibEM.c,42 :: 		OPTION_REG = 0x87; // Use internal clock Fosc/4 with a prescaler of 256
	MOVLW      135
	MOVWF      OPTION_REG+0
;LibEM.c,45 :: 		TMR0 = 248; // will count 8 times before the overflow (8 * 128uS = 1ms)
	MOVLW      248
	MOVWF      TMR0+0
;LibEM.c,46 :: 		INTCON = 0b11100000; // GIE, T0IE, peripheral interrupt
	MOVLW      224
	MOVWF      INTCON+0
;LibEM.c,47 :: 		}
L_end_Init:
	RETURN
; end of _Init

_ADC_init:

;LibEM.c,48 :: 		void ADC_init(void) {
;LibEM.c,49 :: 		ADCON0 = 0x41;//ON, Channel 0, Fosc/16== 500KHz, Dont Go
	MOVLW      65
	MOVWF      ADCON0+0
;LibEM.c,50 :: 		ADCON1 = 0xCE;// RA0 Analog, others are Digital, Right Allignment,
	MOVLW      206
	MOVWF      ADCON1+0
;LibEM.c,51 :: 		}
L_end_ADC_init:
	RETURN
; end of _ADC_init

_ADC_read:

;LibEM.c,52 :: 		unsigned int ADC_read(void) {
;LibEM.c,53 :: 		ADCON0 = ADCON0 | 0x04;//GO
	BSF        ADCON0+0, 2
;LibEM.c,54 :: 		while (ADCON0 & 0x04);//wait until DONE
L_ADC_read0:
	BTFSS      ADCON0+0, 2
	GOTO       L_ADC_read1
	GOTO       L_ADC_read0
L_ADC_read1:
;LibEM.c,55 :: 		return (ADRESH << 8) | ADRESL;
	MOVF       ADRESH+0, 0
	MOVWF      R0+1
	CLRF       R0+0
	MOVF       ADRESL+0, 0
	IORWF      R0+0, 1
	MOVLW      0
	IORWF      R0+1, 1
;LibEM.c,56 :: 		}
L_end_ADC_read:
	RETURN
; end of _ADC_read

_interrupt:
	MOVWF      R15+0
	SWAPF      STATUS+0, 0
	CLRF       STATUS+0
	MOVWF      ___saveSTATUS+0
	MOVF       PCLATH+0, 0
	MOVWF      ___savePCLATH+0
	CLRF       PCLATH+0

;LibEM.c,57 :: 		void interrupt() {
;LibEM.c,58 :: 		if (INTCON & 0x04) { // TMR0 Overflow interrupt, will get here every 1ms
	BTFSS      INTCON+0, 2
	GOTO       L_interrupt2
;LibEM.c,59 :: 		TMR0 = 240;
	MOVLW      240
	MOVWF      TMR0+0
;LibEM.c,60 :: 		tick++;
	INCF       _tick+0, 1
	BTFSC      STATUS+0, 2
	INCF       _tick+1, 1
;LibEM.c,63 :: 		Signal = ADC_read();
	CALL       _ADC_read+0
	MOVF       R0+0, 0
	MOVWF      _Signal+0
	MOVF       R0+1, 0
	MOVWF      _Signal+1
;LibEM.c,64 :: 		sampleCounter += 2;
	MOVLW      2
	MOVWF      R2+0
	CLRF       R2+1
	CLRF       R2+2
	CLRF       R2+3
	MOVF       _sampleCounter+0, 0
	ADDWF      R2+0, 1
	MOVF       _sampleCounter+1, 0
	BTFSC      STATUS+0, 0
	INCFSZ     _sampleCounter+1, 0
	ADDWF      R2+1, 1
	MOVF       _sampleCounter+2, 0
	BTFSC      STATUS+0, 0
	INCFSZ     _sampleCounter+2, 0
	ADDWF      R2+2, 1
	MOVF       _sampleCounter+3, 0
	BTFSC      STATUS+0, 0
	INCFSZ     _sampleCounter+3, 0
	ADDWF      R2+3, 1
	MOVF       R2+0, 0
	MOVWF      _sampleCounter+0
	MOVF       R2+1, 0
	MOVWF      _sampleCounter+1
	MOVF       R2+2, 0
	MOVWF      _sampleCounter+2
	MOVF       R2+3, 0
	MOVWF      _sampleCounter+3
;LibEM.c,65 :: 		N_cnt = sampleCounter - lastBeatTime;
	MOVF       _lastBeatTime+0, 0
	SUBWF      R2+0, 0
	MOVWF      _N_cnt+0
	MOVF       _lastBeatTime+1, 0
	BTFSS      STATUS+0, 0
	ADDLW      1
	SUBWF      R2+1, 0
	MOVWF      _N_cnt+1
;LibEM.c,66 :: 		if (Signal < thresh && N_cnt >(IBI / 5) * 3) {
	MOVF       _thresh+1, 0
	SUBWF      R0+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__interrupt47
	MOVF       _thresh+0, 0
	SUBWF      R0+0, 0
L__interrupt47:
	BTFSC      STATUS+0, 0
	GOTO       L_interrupt5
	MOVLW      5
	MOVWF      R4+0
	MOVLW      0
	MOVWF      R4+1
	MOVF       _IBI+0, 0
	MOVWF      R0+0
	MOVF       _IBI+1, 0
	MOVWF      R0+1
	CALL       _Div_16X16_U+0
	MOVLW      3
	MOVWF      R4+0
	MOVLW      0
	MOVWF      R4+1
	CALL       _Mul_16X16_U+0
	MOVF       _N_cnt+1, 0
	SUBWF      R0+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__interrupt48
	MOVF       _N_cnt+0, 0
	SUBWF      R0+0, 0
L__interrupt48:
	BTFSC      STATUS+0, 0
	GOTO       L_interrupt5
L__interrupt41:
;LibEM.c,67 :: 		if (Signal < Trough) {
	MOVF       _Trough+1, 0
	SUBWF      _Signal+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__interrupt49
	MOVF       _Trough+0, 0
	SUBWF      _Signal+0, 0
L__interrupt49:
	BTFSC      STATUS+0, 0
	GOTO       L_interrupt6
;LibEM.c,68 :: 		Trough = Signal;
	MOVF       _Signal+0, 0
	MOVWF      _Trough+0
	MOVF       _Signal+1, 0
	MOVWF      _Trough+1
;LibEM.c,69 :: 		}
L_interrupt6:
;LibEM.c,70 :: 		}
L_interrupt5:
;LibEM.c,71 :: 		if (Signal > thresh && Signal > P_cnt) {
	MOVF       _Signal+1, 0
	SUBWF      _thresh+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__interrupt50
	MOVF       _Signal+0, 0
	SUBWF      _thresh+0, 0
L__interrupt50:
	BTFSC      STATUS+0, 0
	GOTO       L_interrupt9
	MOVF       _Signal+1, 0
	SUBWF      _P_cnt+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__interrupt51
	MOVF       _Signal+0, 0
	SUBWF      _P_cnt+0, 0
L__interrupt51:
	BTFSC      STATUS+0, 0
	GOTO       L_interrupt9
L__interrupt40:
;LibEM.c,72 :: 		P_cnt = Signal;
	MOVF       _Signal+0, 0
	MOVWF      _P_cnt+0
	MOVF       _Signal+1, 0
	MOVWF      _P_cnt+1
;LibEM.c,73 :: 		}
L_interrupt9:
;LibEM.c,77 :: 		if (N_cnt > 250) { // avoid high frequency noise
	MOVLW      128
	MOVWF      R0+0
	MOVLW      128
	XORWF      _N_cnt+1, 0
	SUBWF      R0+0, 0
	BTFSS      STATUS+0, 2
	GOTO       L__interrupt52
	MOVF       _N_cnt+0, 0
	SUBLW      250
L__interrupt52:
	BTFSC      STATUS+0, 0
	GOTO       L_interrupt10
;LibEM.c,78 :: 		if ((Signal > thresh) && (Pulse == FALSE) && (N_cnt > (IBI / 5) * 3)) {
	MOVF       _Signal+1, 0
	SUBWF      _thresh+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__interrupt53
	MOVF       _Signal+0, 0
	SUBWF      _thresh+0, 0
L__interrupt53:
	BTFSC      STATUS+0, 0
	GOTO       L_interrupt13
	BTFSC      _Pulse+0, BitPos(_Pulse+0)
	GOTO       L_interrupt13
	MOVLW      5
	MOVWF      R4+0
	MOVLW      0
	MOVWF      R4+1
	MOVF       _IBI+0, 0
	MOVWF      R0+0
	MOVF       _IBI+1, 0
	MOVWF      R0+1
	CALL       _Div_16X16_U+0
	MOVLW      3
	MOVWF      R4+0
	MOVLW      0
	MOVWF      R4+1
	CALL       _Mul_16X16_U+0
	MOVF       _N_cnt+1, 0
	SUBWF      R0+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__interrupt54
	MOVF       _N_cnt+0, 0
	SUBWF      R0+0, 0
L__interrupt54:
	BTFSC      STATUS+0, 0
	GOTO       L_interrupt13
L__interrupt39:
;LibEM.c,79 :: 		Pulse = TRUE; // set the Pulse flag when we think there is a pulse
	BSF        _Pulse+0, BitPos(_Pulse+0)
;LibEM.c,80 :: 		IBI = sampleCounter - lastBeatTime; // measure time between beats in mS
	MOVF       _lastBeatTime+0, 0
	SUBWF      _sampleCounter+0, 0
	MOVWF      _IBI+0
	MOVF       _lastBeatTime+1, 0
	BTFSS      STATUS+0, 0
	ADDLW      1
	SUBWF      _sampleCounter+1, 0
	MOVWF      _IBI+1
;LibEM.c,81 :: 		lastBeatTime = sampleCounter; // keep track of time for next pulse
	MOVF       _sampleCounter+0, 0
	MOVWF      _lastBeatTime+0
	MOVF       _sampleCounter+1, 0
	MOVWF      _lastBeatTime+1
	MOVF       _sampleCounter+2, 0
	MOVWF      _lastBeatTime+2
	MOVF       _sampleCounter+3, 0
	MOVWF      _lastBeatTime+3
;LibEM.c,83 :: 		if (secondBeat) { // if this is the second beat, if secondBeat == TRUE
	BTFSS      _secondBeat+0, BitPos(_secondBeat+0)
	GOTO       L_interrupt14
;LibEM.c,84 :: 		secondBeat = FALSE; // clear secondBeat flag
	BCF        _secondBeat+0, BitPos(_secondBeat+0)
;LibEM.c,85 :: 		for (i = 0; i <= 9; i++) { // seed the running total to get a realisitic BPM at startup
	CLRF       _i+0
	CLRF       _i+1
L_interrupt15:
	MOVLW      128
	MOVWF      R0+0
	MOVLW      128
	XORWF      _i+1, 0
	SUBWF      R0+0, 0
	BTFSS      STATUS+0, 2
	GOTO       L__interrupt55
	MOVF       _i+0, 0
	SUBLW      9
L__interrupt55:
	BTFSS      STATUS+0, 0
	GOTO       L_interrupt16
;LibEM.c,86 :: 		rate[i] = IBI;
	MOVF       _i+0, 0
	MOVWF      R0+0
	MOVF       _i+1, 0
	MOVWF      R0+1
	RLF        R0+0, 1
	RLF        R0+1, 1
	BCF        R0+0, 0
	MOVF       R0+0, 0
	ADDLW      _rate+0
	MOVWF      FSR
	MOVF       _IBI+0, 0
	MOVWF      INDF+0
	MOVF       _IBI+1, 0
	INCF       FSR, 1
	MOVWF      INDF+0
;LibEM.c,85 :: 		for (i = 0; i <= 9; i++) { // seed the running total to get a realisitic BPM at startup
	INCF       _i+0, 1
	BTFSC      STATUS+0, 2
	INCF       _i+1, 1
;LibEM.c,87 :: 		}
	GOTO       L_interrupt15
L_interrupt16:
;LibEM.c,88 :: 		}
L_interrupt14:
;LibEM.c,90 :: 		if (firstBeat) { // if it's the first time we found a beat, if firstBeat == TRUE
	BTFSS      _firstBeat+0, BitPos(_firstBeat+0)
	GOTO       L_interrupt18
;LibEM.c,91 :: 		firstBeat = FALSE; // clear firstBeat flag
	BCF        _firstBeat+0, BitPos(_firstBeat+0)
;LibEM.c,92 :: 		secondBeat = TRUE; // set the second beat flag
	BSF        _secondBeat+0, BitPos(_secondBeat+0)
;LibEM.c,94 :: 		return; // IBI value is unreliable so discard it
	GOTO       L__interrupt46
;LibEM.c,95 :: 		}
L_interrupt18:
;LibEM.c,99 :: 		runningTotal = 0; // clear the runningTotal variable
	CLRF       _runningTotal+0
	CLRF       _runningTotal+1
;LibEM.c,101 :: 		for (i = 0; i <= 8; i++) { // shift data in the rate array
	CLRF       _i+0
	CLRF       _i+1
L_interrupt19:
	MOVLW      128
	MOVWF      R0+0
	MOVLW      128
	XORWF      _i+1, 0
	SUBWF      R0+0, 0
	BTFSS      STATUS+0, 2
	GOTO       L__interrupt56
	MOVF       _i+0, 0
	SUBLW      8
L__interrupt56:
	BTFSS      STATUS+0, 0
	GOTO       L_interrupt20
;LibEM.c,102 :: 		rate[i] = rate[i + 1]; // and drop the oldest IBI value
	MOVF       _i+0, 0
	MOVWF      R0+0
	MOVF       _i+1, 0
	MOVWF      R0+1
	RLF        R0+0, 1
	RLF        R0+1, 1
	BCF        R0+0, 0
	MOVF       R0+0, 0
	ADDLW      _rate+0
	MOVWF      R5+0
	MOVF       _i+0, 0
	ADDLW      1
	MOVWF      R3+0
	MOVLW      0
	BTFSC      STATUS+0, 0
	ADDLW      1
	ADDWF      _i+1, 0
	MOVWF      R3+1
	MOVF       R3+0, 0
	MOVWF      R0+0
	MOVF       R3+1, 0
	MOVWF      R0+1
	RLF        R0+0, 1
	RLF        R0+1, 1
	BCF        R0+0, 0
	MOVF       R0+0, 0
	ADDLW      _rate+0
	MOVWF      FSR
	MOVF       INDF+0, 0
	MOVWF      R0+0
	INCF       FSR, 1
	MOVF       INDF+0, 0
	MOVWF      R0+1
	MOVF       R5+0, 0
	MOVWF      FSR
	MOVF       R0+0, 0
	MOVWF      INDF+0
	MOVF       R0+1, 0
	INCF       FSR, 1
	MOVWF      INDF+0
;LibEM.c,103 :: 		runningTotal += rate[i]; // add up the 9 oldest IBI values
	MOVF       _i+0, 0
	MOVWF      R0+0
	MOVF       _i+1, 0
	MOVWF      R0+1
	RLF        R0+0, 1
	RLF        R0+1, 1
	BCF        R0+0, 0
	MOVF       R0+0, 0
	ADDLW      _rate+0
	MOVWF      FSR
	MOVF       INDF+0, 0
	ADDWF      _runningTotal+0, 1
	INCF       FSR, 1
	MOVF       INDF+0, 0
	BTFSC      STATUS+0, 0
	ADDLW      1
	ADDWF      _runningTotal+1, 1
;LibEM.c,101 :: 		for (i = 0; i <= 8; i++) { // shift data in the rate array
	INCF       _i+0, 1
	BTFSC      STATUS+0, 2
	INCF       _i+1, 1
;LibEM.c,104 :: 		}
	GOTO       L_interrupt19
L_interrupt20:
;LibEM.c,106 :: 		rate[9] = IBI; // add the latest IBI to the rate array
	MOVF       _IBI+0, 0
	MOVWF      _rate+18
	MOVF       _IBI+1, 0
	MOVWF      _rate+19
;LibEM.c,107 :: 		runningTotal += rate[9]; // add the latest IBI to runningTotal
	MOVF       _IBI+0, 0
	ADDWF      _runningTotal+0, 0
	MOVWF      R0+0
	MOVF       _runningTotal+1, 0
	BTFSC      STATUS+0, 0
	ADDLW      1
	ADDWF      _IBI+1, 0
	MOVWF      R0+1
	MOVF       R0+0, 0
	MOVWF      _runningTotal+0
	MOVF       R0+1, 0
	MOVWF      _runningTotal+1
;LibEM.c,108 :: 		runningTotal /= 10; // average the last 10 IBI values
	MOVLW      10
	MOVWF      R4+0
	MOVLW      0
	MOVWF      R4+1
	CALL       _Div_16x16_S+0
	MOVF       R0+0, 0
	MOVWF      _runningTotal+0
	MOVF       R0+1, 0
	MOVWF      _runningTotal+1
;LibEM.c,109 :: 		BPM = 60000 / runningTotal; // how many beats can fit into a minute? that's BPM!
	MOVF       R0+0, 0
	MOVWF      R4+0
	MOVF       R0+1, 0
	MOVWF      R4+1
	MOVLW      96
	MOVWF      R0+0
	MOVLW      234
	MOVWF      R0+1
	CALL       _Div_16X16_U+0
	MOVF       R0+0, 0
	MOVWF      _BPM+0
	MOVF       R0+1, 0
	MOVWF      _BPM+1
;LibEM.c,110 :: 		QS = TRUE; // set Quantified Self flag
	BSF        _QS+0, BitPos(_QS+0)
;LibEM.c,112 :: 		}
L_interrupt13:
;LibEM.c,113 :: 		}
L_interrupt10:
;LibEM.c,115 :: 		if (Signal < thresh && Pulse == TRUE) { // when the values are going down, the beat is over
	MOVF       _thresh+1, 0
	SUBWF      _Signal+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__interrupt57
	MOVF       _thresh+0, 0
	SUBWF      _Signal+0, 0
L__interrupt57:
	BTFSC      STATUS+0, 0
	GOTO       L_interrupt24
	BTFSS      _Pulse+0, BitPos(_Pulse+0)
	GOTO       L_interrupt24
L__interrupt38:
;LibEM.c,117 :: 		Pulse = FALSE; // reset the Pulse flag so we can do it again
	BCF        _Pulse+0, BitPos(_Pulse+0)
;LibEM.c,118 :: 		amp = P_cnt - Trough; // get amplitude of the pulse wave
	MOVF       _Trough+0, 0
	SUBWF      _P_cnt+0, 0
	MOVWF      R3+0
	MOVF       _Trough+1, 0
	BTFSS      STATUS+0, 0
	ADDLW      1
	SUBWF      _P_cnt+1, 0
	MOVWF      R3+1
	MOVF       R3+0, 0
	MOVWF      _amp+0
	MOVF       R3+1, 0
	MOVWF      _amp+1
;LibEM.c,119 :: 		thresh = amp / 2 + Trough; // set thresh at 50% of the amplitude
	MOVF       R3+0, 0
	MOVWF      R0+0
	MOVF       R3+1, 0
	MOVWF      R0+1
	RRF        R0+1, 1
	RRF        R0+0, 1
	BCF        R0+1, 7
	BTFSC      R0+1, 6
	BSF        R0+1, 7
	BTFSS      R0+1, 7
	GOTO       L__interrupt58
	BTFSS      STATUS+0, 0
	GOTO       L__interrupt58
	INCF       R0+0, 1
	BTFSC      STATUS+0, 2
	INCF       R0+1, 1
L__interrupt58:
	MOVF       _Trough+0, 0
	ADDWF      R0+0, 1
	MOVF       _Trough+1, 0
	BTFSC      STATUS+0, 0
	ADDLW      1
	ADDWF      R0+1, 1
	MOVF       R0+0, 0
	MOVWF      _thresh+0
	MOVF       R0+1, 0
	MOVWF      _thresh+1
;LibEM.c,120 :: 		P_cnt = thresh; // reset these for next time
	MOVF       R0+0, 0
	MOVWF      _P_cnt+0
	MOVF       R0+1, 0
	MOVWF      _P_cnt+1
;LibEM.c,121 :: 		Trough = thresh;
	MOVF       R0+0, 0
	MOVWF      _Trough+0
	MOVF       R0+1, 0
	MOVWF      _Trough+1
;LibEM.c,122 :: 		}
L_interrupt24:
;LibEM.c,124 :: 		if (N_cnt > 2500) { // if 2.5 seconds go by without a beat
	MOVLW      128
	XORLW      9
	MOVWF      R0+0
	MOVLW      128
	XORWF      _N_cnt+1, 0
	SUBWF      R0+0, 0
	BTFSS      STATUS+0, 2
	GOTO       L__interrupt59
	MOVF       _N_cnt+0, 0
	SUBLW      196
L__interrupt59:
	BTFSC      STATUS+0, 0
	GOTO       L_interrupt25
;LibEM.c,125 :: 		thresh = 512; // set thresh default
	MOVLW      0
	MOVWF      _thresh+0
	MOVLW      2
	MOVWF      _thresh+1
;LibEM.c,126 :: 		P_cnt = 512; // set P default
	MOVLW      0
	MOVWF      _P_cnt+0
	MOVLW      2
	MOVWF      _P_cnt+1
;LibEM.c,127 :: 		Trough = 512; // set T default
	MOVLW      0
	MOVWF      _Trough+0
	MOVLW      2
	MOVWF      _Trough+1
;LibEM.c,128 :: 		lastBeatTime = sampleCounter; // bring the lastBeatTime up to date
	MOVF       _sampleCounter+0, 0
	MOVWF      _lastBeatTime+0
	MOVF       _sampleCounter+1, 0
	MOVWF      _lastBeatTime+1
	MOVF       _sampleCounter+2, 0
	MOVWF      _lastBeatTime+2
	MOVF       _sampleCounter+3, 0
	MOVWF      _lastBeatTime+3
;LibEM.c,129 :: 		firstBeat = TRUE; // set these to avoid noise
	BSF        _firstBeat+0, BitPos(_firstBeat+0)
;LibEM.c,130 :: 		secondBeat = FALSE; // when we get the heartbeat back
	BCF        _secondBeat+0, BitPos(_secondBeat+0)
;LibEM.c,131 :: 		}
L_interrupt25:
;LibEM.c,132 :: 		INTCON &= 0xFB; // Clear T0IF
	MOVLW      251
	ANDWF      INTCON+0, 1
;LibEM.c,133 :: 		}
L_interrupt2:
;LibEM.c,134 :: 		}
L_end_interrupt:
L__interrupt46:
	MOVF       ___savePCLATH+0, 0
	MOVWF      PCLATH+0
	SWAPF      ___saveSTATUS+0, 0
	MOVWF      STATUS+0
	SWAPF      R15+0, 1
	SWAPF      R15+0, 0
	RETFIE
; end of _interrupt

_main:

;LibEM.c,136 :: 		void main() {
;LibEM.c,139 :: 		Pulse = FALSE;
	BCF        _Pulse+0, BitPos(_Pulse+0)
;LibEM.c,140 :: 		QS = FALSE;
	BCF        _QS+0, BitPos(_QS+0)
;LibEM.c,141 :: 		firstBeat = TRUE;
	BSF        _firstBeat+0, BitPos(_firstBeat+0)
;LibEM.c,142 :: 		secondBeat = FALSE;
	BCF        _secondBeat+0, BitPos(_secondBeat+0)
;LibEM.c,143 :: 		Lcd_Init(); //initialize LCD
	CALL       _Lcd_Init+0
;LibEM.c,144 :: 		Lcd_Cmd(_LCD_CLEAR); // Clear display
	MOVLW      1
	MOVWF      FARG_Lcd_Cmd_out_char+0
	CALL       _Lcd_Cmd+0
;LibEM.c,145 :: 		Delay_ms(200);
	MOVLW      3
	MOVWF      R11+0
	MOVLW      8
	MOVWF      R12+0
	MOVLW      119
	MOVWF      R13+0
L_main26:
	DECFSZ     R13+0, 1
	GOTO       L_main26
	DECFSZ     R12+0, 1
	GOTO       L_main26
	DECFSZ     R11+0, 1
	GOTO       L_main26
;LibEM.c,146 :: 		Lcd_Cmd(_LCD_CURSOR_OFF);
	MOVLW      12
	MOVWF      FARG_Lcd_Cmd_out_char+0
	CALL       _Lcd_Cmd+0
;LibEM.c,147 :: 		Delay_ms(200);
	MOVLW      3
	MOVWF      R11+0
	MOVLW      8
	MOVWF      R12+0
	MOVLW      119
	MOVWF      R13+0
L_main27:
	DECFSZ     R13+0, 1
	GOTO       L_main27
	DECFSZ     R12+0, 1
	GOTO       L_main27
	DECFSZ     R11+0, 1
	GOTO       L_main27
;LibEM.c,148 :: 		Lcd_Out(1, 1, intro_msg);
	MOVLW      1
	MOVWF      FARG_Lcd_Out_row+0
	MOVLW      1
	MOVWF      FARG_Lcd_Out_column+0
	MOVLW      _intro_msg+0
	MOVWF      FARG_Lcd_Out_text+0
	CALL       _Lcd_Out+0
;LibEM.c,149 :: 		Delay_ms(1500); // First row
	MOVLW      16
	MOVWF      R11+0
	MOVLW      57
	MOVWF      R12+0
	MOVLW      13
	MOVWF      R13+0
L_main28:
	DECFSZ     R13+0, 1
	GOTO       L_main28
	DECFSZ     R12+0, 1
	GOTO       L_main28
	DECFSZ     R11+0, 1
	GOTO       L_main28
	NOP
	NOP
;LibEM.c,150 :: 		for (g = 0; g < sizeof(intro_msg) - 16; g++) { // Move text to the right 4 times
	CLRF       main_g_L0+0
	CLRF       main_g_L0+1
L_main29:
	MOVLW      128
	XORWF      main_g_L0+1, 0
	MOVWF      R0+0
	MOVLW      128
	XORLW      0
	SUBWF      R0+0, 0
	BTFSS      STATUS+0, 2
	GOTO       L__main61
	MOVLW      14
	SUBWF      main_g_L0+0, 0
L__main61:
	BTFSC      STATUS+0, 0
	GOTO       L_main30
;LibEM.c,151 :: 		Lcd_Cmd(_LCD_SHIFT_LEFT);
	MOVLW      24
	MOVWF      FARG_Lcd_Cmd_out_char+0
	CALL       _Lcd_Cmd+0
;LibEM.c,152 :: 		Delay_ms(250);
	MOVLW      3
	MOVWF      R11+0
	MOVLW      138
	MOVWF      R12+0
	MOVLW      85
	MOVWF      R13+0
L_main32:
	DECFSZ     R13+0, 1
	GOTO       L_main32
	DECFSZ     R12+0, 1
	GOTO       L_main32
	DECFSZ     R11+0, 1
	GOTO       L_main32
	NOP
	NOP
;LibEM.c,150 :: 		for (g = 0; g < sizeof(intro_msg) - 16; g++) { // Move text to the right 4 times
	INCF       main_g_L0+0, 1
	BTFSC      STATUS+0, 2
	INCF       main_g_L0+1, 1
;LibEM.c,153 :: 		}
	GOTO       L_main29
L_main30:
;LibEM.c,155 :: 		Lcd_Cmd(_LCD_CLEAR); // Clear display
	MOVLW      1
	MOVWF      FARG_Lcd_Cmd_out_char+0
	CALL       _Lcd_Cmd+0
;LibEM.c,156 :: 		Delay_ms(200);
	MOVLW      3
	MOVWF      R11+0
	MOVLW      8
	MOVWF      R12+0
	MOVLW      119
	MOVWF      R13+0
L_main33:
	DECFSZ     R13+0, 1
	GOTO       L_main33
	DECFSZ     R12+0, 1
	GOTO       L_main33
	DECFSZ     R11+0, 1
	GOTO       L_main33
;LibEM.c,157 :: 		ADC_Init();
	CALL       _ADC_init+0
;LibEM.c,160 :: 		while (1) {
L_main34:
;LibEM.c,161 :: 		if (QS == TRUE) { //New Pulse detected
	BTFSS      _QS+0, BitPos(_QS+0)
	GOTO       L_main36
;LibEM.c,162 :: 		Lcd_Out(1, 1, "HEART RATE (BPM)");
	MOVLW      1
	MOVWF      FARG_Lcd_Out_row+0
	MOVLW      1
	MOVWF      FARG_Lcd_Out_column+0
	MOVLW      ?lstr1_LibEM+0
	MOVWF      FARG_Lcd_Out_text+0
	CALL       _Lcd_Out+0
;LibEM.c,163 :: 		Lcd_Out(2, 1, " ");
	MOVLW      2
	MOVWF      FARG_Lcd_Out_row+0
	MOVLW      1
	MOVWF      FARG_Lcd_Out_column+0
	MOVLW      ?lstr2_LibEM+0
	MOVWF      FARG_Lcd_Out_text+0
	CALL       _Lcd_Out+0
;LibEM.c,164 :: 		IntToStr(BPM, temp_str);
	MOVF       _BPM+0, 0
	MOVWF      FARG_IntToStr_input+0
	MOVF       _BPM+1, 0
	MOVWF      FARG_IntToStr_input+1
	MOVLW      _temp_str+0
	MOVWF      FARG_IntToStr_output+0
	CALL       _IntToStr+0
;LibEM.c,165 :: 		Lcd_Out(2, 8, temp_str);
	MOVLW      2
	MOVWF      FARG_Lcd_Out_row+0
	MOVLW      8
	MOVWF      FARG_Lcd_Out_column+0
	MOVLW      _temp_str+0
	MOVWF      FARG_Lcd_Out_text+0
	CALL       _Lcd_Out+0
;LibEM.c,166 :: 		Delay_ms(2000);
	MOVLW      21
	MOVWF      R11+0
	MOVLW      75
	MOVWF      R12+0
	MOVLW      190
	MOVWF      R13+0
L_main37:
	DECFSZ     R13+0, 1
	GOTO       L_main37
	DECFSZ     R12+0, 1
	GOTO       L_main37
	DECFSZ     R11+0, 1
	GOTO       L_main37
	NOP
;LibEM.c,167 :: 		}
L_main36:
;LibEM.c,170 :: 		}
	GOTO       L_main34
;LibEM.c,171 :: 		}
L_end_main:
	GOTO       $+0
; end of _main
