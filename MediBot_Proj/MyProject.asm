
_mydelayms:

;MyProject.c,112 :: 		void mydelayms(unsigned int count)
;MyProject.c,114 :: 		count *= 2;
	RLF        FARG_mydelayms_count+0, 1
	RLF        FARG_mydelayms_count+1, 1
	BCF        FARG_mydelayms_count+0, 0
;MyProject.c,115 :: 		tick = 0;
	CLRF       _tick+0
	CLRF       _tick+1
;MyProject.c,116 :: 		while (tick < count);
L_mydelayms0:
	MOVF       FARG_mydelayms_count+1, 0
	SUBWF      _tick+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__mydelayms62
	MOVF       FARG_mydelayms_count+0, 0
	SUBWF      _tick+0, 0
L__mydelayms62:
	BTFSC      STATUS+0, 0
	GOTO       L_mydelayms1
	GOTO       L_mydelayms0
L_mydelayms1:
;MyProject.c,117 :: 		}
L_end_mydelayms:
	RETURN
; end of _mydelayms

_mydelayus:

;MyProject.c,119 :: 		void mydelayus(unsigned int count)
;MyProject.c,121 :: 		for (i = 0; i < 2*count; i++)
	CLRF       _i+0
	CLRF       _i+1
L_mydelayus2:
	MOVF       FARG_mydelayus_count+0, 0
	MOVWF      R1+0
	MOVF       FARG_mydelayus_count+1, 0
	MOVWF      R1+1
	RLF        R1+0, 1
	RLF        R1+1, 1
	BCF        R1+0, 0
	MOVF       R1+1, 0
	SUBWF      _i+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__mydelayus64
	MOVF       R1+0, 0
	SUBWF      _i+0, 0
L__mydelayus64:
	BTFSC      STATUS+0, 0
	GOTO       L_mydelayus3
;MyProject.c,123 :: 		asm NOP;
	NOP
;MyProject.c,121 :: 		for (i = 0; i < 2*count; i++)
	INCF       _i+0, 1
	BTFSC      STATUS+0, 2
	INCF       _i+1, 1
;MyProject.c,124 :: 		}
	GOTO       L_mydelayus2
L_mydelayus3:
;MyProject.c,125 :: 		}
L_end_mydelayus:
	RETURN
; end of _mydelayus

_ATD_init:

;MyProject.c,126 :: 		void ATD_init(void) {
;MyProject.c,127 :: 		ADCON0 = 0x41;           // ON, Channel 0, Fosc/16== 500KHz, Dont Go
	MOVLW      65
	MOVWF      ADCON0+0
;MyProject.c,128 :: 		ADCON1 = 0xC4;           // RA0 Analog, others are Digital, Right Allignment,
	MOVLW      196
	MOVWF      ADCON1+0
;MyProject.c,129 :: 		TRISA = 0x01;
	MOVLW      1
	MOVWF      TRISA+0
;MyProject.c,130 :: 		}
L_end_ATD_init:
	RETURN
; end of _ATD_init

_ATD_read:

;MyProject.c,131 :: 		unsigned int ATD_read(void) {
;MyProject.c,132 :: 		SET_BIT2_HIGH(ADCON0);  // GO
	BSF        ADCON0+0, 2
;MyProject.c,133 :: 		while (IS_BIT2_HIGH(ADCON0));    // wait until DONE
L_ATD_read5:
	BTFSS      ADCON0+0, 2
	GOTO       L_ATD_read6
	GOTO       L_ATD_read5
L_ATD_read6:
;MyProject.c,134 :: 		return (ADRESH << 8) | ADRESL;
	MOVF       ADRESH+0, 0
	MOVWF      R0+1
	CLRF       R0+0
	MOVF       ADRESL+0, 0
	IORWF      R0+0, 1
	MOVLW      0
	IORWF      R0+1, 1
;MyProject.c,135 :: 		}
L_end_ATD_read:
	RETURN
; end of _ATD_read

_Distance:

;MyProject.c,136 :: 		unsigned int Distance() {
;MyProject.c,139 :: 		int tdist = 5;
;MyProject.c,140 :: 		SET_BIT5_HIGH(INTCON);
	BSF        INTCON+0, 5
;MyProject.c,141 :: 		SET_BIT3_HIGH(PORTC);               //TRIGGER HIGH
	BSF        PORTC+0, 3
;MyProject.c,142 :: 		mydelayus(10);               //10uS Delay
	MOVLW      10
	MOVWF      FARG_mydelayus_count+0
	MOVLW      0
	MOVWF      FARG_mydelayus_count+1
	CALL       _mydelayus+0
;MyProject.c,143 :: 		SET_BIT3_LOW(PORTC);           //TRIGGER LOW
	BCF        PORTC+0, 3
;MyProject.c,145 :: 		while (IS_BIT4_LOW(PORTC));           //Waiting for Echo
L_Distance7:
	MOVLW      16
	ANDWF      PORTC+0, 0
	MOVWF      R0+0
	MOVLW      0
	ANDLW      0
	MOVWF      R0+1
	COMF       R0+0, 1
	COMF       R0+1, 1
	MOVF       R0+0, 0
	IORWF      R0+1, 0
	BTFSC      STATUS+0, 2
	GOTO       L_Distance8
	GOTO       L_Distance7
L_Distance8:
;MyProject.c,146 :: 		TMR0 = 0;
	CLRF       TMR0+0
;MyProject.c,147 :: 		oftmr0 = 0;
	CLRF       _oftmr0+0
	CLRF       _oftmr0+1
;MyProject.c,148 :: 		while (IS_BIT4_HIGH(PORTC));            //Waiting for Echo goes LOW
L_Distance9:
	BTFSS      PORTC+0, 4
	GOTO       L_Distance10
	GOTO       L_Distance9
L_Distance10:
;MyProject.c,149 :: 		tdist = oftmr0 * 256 + TMR0;   //Reads Timer Value
	MOVF       _oftmr0+0, 0
	MOVWF      R0+1
	CLRF       R0+0
	MOVF       TMR0+0, 0
	ADDWF      R0+0, 1
	BTFSC      STATUS+0, 0
	INCF       R0+1, 1
;MyProject.c,150 :: 		tdist = tdist / 58.82;                //Converts Time to Distance
	CALL       _int2double+0
	MOVLW      174
	MOVWF      R4+0
	MOVLW      71
	MOVWF      R4+1
	MOVLW      107
	MOVWF      R4+2
	MOVLW      132
	MOVWF      R4+3
	CALL       _Div_32x32_FP+0
	CALL       _double2int+0
;MyProject.c,151 :: 		SET_BIT5_LOW(INTCON);
	BCF        INTCON+0, 5
;MyProject.c,152 :: 		return tdist;
;MyProject.c,153 :: 		}
L_end_Distance:
	RETURN
; end of _Distance

_CCPPWM_init:

;MyProject.c,155 :: 		void CCPPWM_init() { //Configure CCP1 at 2ms period with 50% duty cycle
;MyProject.c,156 :: 		T2CON = 0b00000111;//enable Timer2 at Fosc/4 with 1:16 prescaler (8 uS percount 2000uS to count 250 counts)
	MOVLW      7
	MOVWF      T2CON+0
;MyProject.c,157 :: 		CCP1CON = 0x0C;//enable PWM for CCP1
	MOVLW      12
	MOVWF      CCP1CON+0
;MyProject.c,158 :: 		PR2 = 250;// 250 counts =8uS *250 =2ms period
	MOVLW      250
	MOVWF      PR2+0
;MyProject.c,159 :: 		CCPR1L = 0;
	CLRF       CCPR1L+0
;MyProject.c,160 :: 		}void MotorSpeed(unsigned int speed) {
L_end_CCPPWM_init:
	RETURN
; end of _CCPPWM_init

_MotorSpeed:

;MyProject.c,161 :: 		CCPR1L = speed;
	MOVF       FARG_MotorSpeed_speed+0, 0
	MOVWF      CCPR1L+0
;MyProject.c,162 :: 		}
L_end_MotorSpeed:
	RETURN
; end of _MotorSpeed

_direction:

;MyProject.c,163 :: 		void direction(char dir)
;MyProject.c,165 :: 		if (dir == 4)
	MOVF       FARG_direction_dir+0, 0
	XORLW      4
	BTFSS      STATUS+0, 2
	GOTO       L_direction11
;MyProject.c,167 :: 		MotorSpeed(0);
	CLRF       FARG_MotorSpeed_speed+0
	CLRF       FARG_MotorSpeed_speed+1
	CALL       _MotorSpeed+0
;MyProject.c,168 :: 		return;
	GOTO       L_end_direction
;MyProject.c,169 :: 		}
L_direction11:
;MyProject.c,170 :: 		else if (dir == 0)
	MOVF       FARG_direction_dir+0, 0
	XORLW      0
	BTFSS      STATUS+0, 2
	GOTO       L_direction13
;MyProject.c,173 :: 		SET_BIT1_LOW(PORTB);
	BCF        PORTB+0, 1
;MyProject.c,174 :: 		SET_BIT2_HIGH(PORTB);
	BSF        PORTB+0, 2
;MyProject.c,175 :: 		SET_BIT3_HIGH(PORTB);
	BSF        PORTB+0, 3
;MyProject.c,176 :: 		SET_BIT4_LOW(PORTB);
	BCF        PORTB+0, 4
;MyProject.c,178 :: 		}
	GOTO       L_direction14
L_direction13:
;MyProject.c,179 :: 		else if (dir == 1)
	MOVF       FARG_direction_dir+0, 0
	XORLW      1
	BTFSS      STATUS+0, 2
	GOTO       L_direction15
;MyProject.c,181 :: 		SET_BIT1_HIGH(PORTB);
	BSF        PORTB+0, 1
;MyProject.c,182 :: 		SET_BIT2_LOW(PORTB);
	BCF        PORTB+0, 2
;MyProject.c,183 :: 		SET_BIT3_LOW(PORTB);
	BCF        PORTB+0, 3
;MyProject.c,184 :: 		SET_BIT4_HIGH(PORTB);
	BSF        PORTB+0, 4
;MyProject.c,186 :: 		}
	GOTO       L_direction16
L_direction15:
;MyProject.c,187 :: 		else if (dir == 2)
	MOVF       FARG_direction_dir+0, 0
	XORLW      2
	BTFSS      STATUS+0, 2
	GOTO       L_direction17
;MyProject.c,189 :: 		SET_BIT1_HIGH(PORTB);
	BSF        PORTB+0, 1
;MyProject.c,190 :: 		SET_BIT2_LOW(PORTB);
	BCF        PORTB+0, 2
;MyProject.c,191 :: 		SET_BIT3_HIGH(PORTB);
	BSF        PORTB+0, 3
;MyProject.c,192 :: 		SET_BIT4_LOW(PORTB);
	BCF        PORTB+0, 4
;MyProject.c,194 :: 		}
	GOTO       L_direction18
L_direction17:
;MyProject.c,195 :: 		else if (dir == 3)
	MOVF       FARG_direction_dir+0, 0
	XORLW      3
	BTFSS      STATUS+0, 2
	GOTO       L_direction19
;MyProject.c,197 :: 		SET_BIT1_LOW(PORTB);
	BCF        PORTB+0, 1
;MyProject.c,198 :: 		SET_BIT2_HIGH(PORTB);
	BSF        PORTB+0, 2
;MyProject.c,199 :: 		SET_BIT3_LOW(PORTB);
	BCF        PORTB+0, 3
;MyProject.c,200 :: 		SET_BIT4_HIGH(PORTB);
	BSF        PORTB+0, 4
;MyProject.c,202 :: 		}
L_direction19:
L_direction18:
L_direction16:
L_direction14:
;MyProject.c,203 :: 		MotorSpeed(200);
	MOVLW      200
	MOVWF      FARG_MotorSpeed_speed+0
	CLRF       FARG_MotorSpeed_speed+1
	CALL       _MotorSpeed+0
;MyProject.c,204 :: 		}
L_end_direction:
	RETURN
; end of _direction

_Init:

;MyProject.c,205 :: 		void Init()
;MyProject.c,207 :: 		HL = 1;                // start high
	MOVLW      1
	MOVWF      _HL+0
;MyProject.c,208 :: 		SET_BIT3_LOW(TRISC);
	BCF        TRISC+0, 3
;MyProject.c,209 :: 		SET_BIT4_HIGH(TRISC);
	BSF        TRISC+0, 4
;MyProject.c,210 :: 		SET_BIT5_HIGH(TRISC);
	BSF        TRISC+0, 5
;MyProject.c,211 :: 		SET_BIT6_HIGH(TRISC);
	BSF        TRISC+0, 6
;MyProject.c,212 :: 		SET_BIT2_HIGH(TRISE);
	BSF        TRISE+0, 2
;MyProject.c,213 :: 		SET_BIT5_LOW(TRISA);
	BCF        TRISA+0, 5
;MyProject.c,214 :: 		TRISD = 0;
	CLRF       TRISD+0
;MyProject.c,215 :: 		SET_BIT1_LOW(TRISC);
	BCF        TRISC+0, 1
;MyProject.c,216 :: 		SET_BIT2_LOW(TRISC);
	BCF        TRISC+0, 2
;MyProject.c,217 :: 		SET_BIT0_HIGH(TRISB);
	BSF        TRISB+0, 0
;MyProject.c,218 :: 		SET_BIT1_LOW(TRISB);
	BCF        TRISB+0, 1
;MyProject.c,219 :: 		SET_BIT2_LOW(TRISB);
	BCF        TRISB+0, 2
;MyProject.c,220 :: 		SET_BIT3_LOW(TRISB);
	BCF        TRISB+0, 3
;MyProject.c,221 :: 		SET_BIT4_LOW(TRISB);
	BCF        TRISB+0, 4
;MyProject.c,223 :: 		ATD_init();
	CALL       _ATD_init+0
;MyProject.c,224 :: 		CCPPWM_init();
	CALL       _CCPPWM_init+0
;MyProject.c,225 :: 		OPTION_REG = 0x00;
	CLRF       OPTION_REG+0
;MyProject.c,226 :: 		TMR0 = 0;
	CLRF       TMR0+0
;MyProject.c,227 :: 		oftmr0 = 0;
	CLRF       _oftmr0+0
	CLRF       _oftmr0+1
;MyProject.c,229 :: 		TMR1L = 0;
	CLRF       TMR1L+0
;MyProject.c,230 :: 		TMR1H = 0;
	CLRF       TMR1H+0
;MyProject.c,231 :: 		T1CON = 0x01;
	MOVLW      1
	MOVWF      T1CON+0
;MyProject.c,232 :: 		INTCON = 0B11010000;
	MOVLW      208
	MOVWF      INTCON+0
;MyProject.c,233 :: 		SET_BIT2_HIGH(PIE1);
	BSF        PIE1+0, 2
;MyProject.c,234 :: 		SET_BIT1_HIGH(PIE1);
	BSF        PIE1+0, 1
;MyProject.c,235 :: 		SET_BIT0_HIGH(PIE2);
	BSF        PIE2+0, 0
;MyProject.c,236 :: 		CCP2CON = 0x08;        // Compare mode, set output on match
	MOVLW      8
	MOVWF      CCP2CON+0
;MyProject.c,237 :: 		CCPR2L = 2000;         // Value preset in a program to compare the TMR1L value to
	MOVLW      208
	MOVWF      CCPR2L+0
;MyProject.c,238 :: 		CCPR2H = 2000 >> 8;      // Value preset in a program to compare the TMR1H value to            - 1ms
	MOVLW      7
	MOVWF      CCPR2H+0
;MyProject.c,240 :: 		direction(0);
	CLRF       FARG_direction_dir+0
	CALL       _direction+0
;MyProject.c,241 :: 		}
L_end_Init:
	RETURN
; end of _Init

_GetAngle:

;MyProject.c,245 :: 		unsigned int GetAngle()
;MyProject.c,247 :: 		analog_read = ATD_read();
	CALL       _ATD_read+0
	MOVF       R0+0, 0
	MOVWF      _analog_read+0
	MOVF       R0+1, 0
	MOVWF      _analog_read+1
;MyProject.c,248 :: 		analog_read = analog_read >> 2;  // divided by 4 ==> 0-255
	MOVF       R0+0, 0
	MOVWF      R4+0
	MOVF       R0+1, 0
	MOVWF      R4+1
	RRF        R4+1, 1
	RRF        R4+0, 1
	BCF        R4+1, 7
	RRF        R4+1, 1
	RRF        R4+0, 1
	BCF        R4+1, 7
	MOVF       R4+0, 0
	MOVWF      _analog_read+0
	MOVF       R4+1, 0
	MOVWF      _analog_read+1
;MyProject.c,250 :: 		count = 1000 + ((analog_read * 25) / 2.55);     //angle= 1000 + ((k*2500)/255); 1000count=500uS to 3500count =1750us
	MOVLW      25
	MOVWF      R0+0
	MOVLW      0
	MOVWF      R0+1
	CALL       _Mul_16X16_U+0
	CALL       _word2double+0
	MOVLW      51
	MOVWF      R4+0
	MOVLW      51
	MOVWF      R4+1
	MOVLW      35
	MOVWF      R4+2
	MOVLW      128
	MOVWF      R4+3
	CALL       _Div_32x32_FP+0
	MOVLW      0
	MOVWF      R4+0
	MOVLW      0
	MOVWF      R4+1
	MOVLW      122
	MOVWF      R4+2
	MOVLW      136
	MOVWF      R4+3
	CALL       _Add_32x32_FP+0
	CALL       _double2word+0
	MOVF       R0+0, 0
	MOVWF      _count+0
	MOVF       R0+1, 0
	MOVWF      _count+1
;MyProject.c,251 :: 		if (count < 1000) count = 1000;      // 0.5ms
	MOVLW      3
	SUBWF      R0+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__GetAngle73
	MOVLW      232
	SUBWF      R0+0, 0
L__GetAngle73:
	BTFSC      STATUS+0, 0
	GOTO       L_GetAngle20
	MOVLW      232
	MOVWF      _count+0
	MOVLW      3
	MOVWF      _count+1
L_GetAngle20:
;MyProject.c,252 :: 		if (count > 3500) count = 3500;      // 1.75ms
	MOVF       _count+1, 0
	SUBLW      13
	BTFSS      STATUS+0, 2
	GOTO       L__GetAngle74
	MOVF       _count+0, 0
	SUBLW      172
L__GetAngle74:
	BTFSC      STATUS+0, 0
	GOTO       L_GetAngle21
	MOVLW      172
	MOVWF      _count+0
	MOVLW      13
	MOVWF      _count+1
L_GetAngle21:
;MyProject.c,253 :: 		return count;
	MOVF       _count+0, 0
	MOVWF      R0+0
	MOVF       _count+1, 0
	MOVWF      R0+1
;MyProject.c,254 :: 		}
L_end_GetAngle:
	RETURN
; end of _GetAngle

_ReadSpeed:

;MyProject.c,262 :: 		unsigned int ReadSpeed()
;MyProject.c,264 :: 		unsigned int v = ATD_read();
	CALL       _ATD_read+0
;MyProject.c,265 :: 		return (((v >> 2) * 250) / 255);// 0-250
	MOVF       R0+0, 0
	MOVWF      R4+0
	MOVF       R0+1, 0
	MOVWF      R4+1
	RRF        R4+1, 1
	RRF        R4+0, 1
	BCF        R4+1, 7
	RRF        R4+1, 1
	RRF        R4+0, 1
	BCF        R4+1, 7
	MOVLW      250
	MOVWF      R0+0
	CLRF       R0+1
	CALL       _Mul_16X16_U+0
	MOVLW      255
	MOVWF      R4+0
	CLRF       R4+1
	CALL       _Div_16X16_U+0
;MyProject.c,266 :: 		}
L_end_ReadSpeed:
	RETURN
; end of _ReadSpeed

_servoserve:

;MyProject.c,267 :: 		void servoserve()
;MyProject.c,269 :: 		angle += 600;
	MOVLW      88
	ADDWF      _angle+0, 1
	MOVLW      2
	BTFSC      STATUS+0, 0
	ADDLW      1
	ADDWF      _angle+1, 1
;MyProject.c,270 :: 		}
L_end_servoserve:
	RETURN
; end of _servoserve

_interrupt:
	MOVWF      R15+0
	SWAPF      STATUS+0, 0
	CLRF       STATUS+0
	MOVWF      ___saveSTATUS+0
	MOVF       PCLATH+0, 0
	MOVWF      ___savePCLATH+0
	CLRF       PCLATH+0

;MyProject.c,271 :: 		void interrupt(void) {
;MyProject.c,272 :: 		if (IS_BIT1_HIGH(INTCON))
	BTFSS      INTCON+0, 1
	GOTO       L_interrupt22
;MyProject.c,274 :: 		FollowingMode = (FollowingMode == 1) ? 0 : 1;
	MOVF       _FollowingMode+0, 0
	XORLW      1
	BTFSS      STATUS+0, 2
	GOTO       L_interrupt23
	CLRF       R5+0
	GOTO       L_interrupt24
L_interrupt23:
	MOVLW      1
	MOVWF      R5+0
L_interrupt24:
	MOVF       R5+0, 0
	MOVWF      _FollowingMode+0
;MyProject.c,275 :: 		SET_BIT1_LOW(INTCON);
	BCF        INTCON+0, 1
;MyProject.c,276 :: 		}
	GOTO       L_interrupt25
L_interrupt22:
;MyProject.c,277 :: 		else if (IS_BIT2_HIGH(INTCON))
	BTFSS      INTCON+0, 2
	GOTO       L_interrupt26
;MyProject.c,279 :: 		TMR0 = 0;
	CLRF       TMR0+0
;MyProject.c,280 :: 		oftmr0++;
	INCF       _oftmr0+0, 1
	BTFSC      STATUS+0, 2
	INCF       _oftmr0+1, 1
;MyProject.c,281 :: 		SET_BIT2_LOW(INTCON);
	BCF        INTCON+0, 2
;MyProject.c,282 :: 		}
	GOTO       L_interrupt27
L_interrupt26:
;MyProject.c,283 :: 		else if (IS_BIT0_HIGH(PIR2)) {                                           // CCP1 interrupt
	BTFSS      PIR2+0, 0
	GOTO       L_interrupt28
;MyProject.c,284 :: 		if (HL) {                                // high
	MOVF       _HL+0, 0
	BTFSC      STATUS+0, 2
	GOTO       L_interrupt29
;MyProject.c,285 :: 		CCPR2H = angle >> 8;
	MOVF       _angle+1, 0
	MOVWF      R0+0
	CLRF       R0+1
	MOVF       R0+0, 0
	MOVWF      CCPR2H+0
;MyProject.c,286 :: 		CCPR2L = angle;
	MOVF       _angle+0, 0
	MOVWF      CCPR2L+0
;MyProject.c,287 :: 		HL = 0;                      // next time low
	CLRF       _HL+0
;MyProject.c,288 :: 		CCP2CON = 0x09;              // compare mode, clear output on match
	MOVLW      9
	MOVWF      CCP2CON+0
;MyProject.c,289 :: 		TMR1H = 0;
	CLRF       TMR1H+0
;MyProject.c,290 :: 		TMR1L = 0;
	CLRF       TMR1L+0
;MyProject.c,291 :: 		}
	GOTO       L_interrupt30
L_interrupt29:
;MyProject.c,293 :: 		CCPR2H = (40000 - angle) >> 8;       // 40000 counts correspond to 20ms
	MOVF       _angle+0, 0
	SUBLW      64
	MOVWF      R3+0
	MOVF       _angle+1, 0
	BTFSS      STATUS+0, 0
	ADDLW      1
	SUBLW      156
	MOVWF      R3+1
	MOVF       R3+1, 0
	MOVWF      R0+0
	CLRF       R0+1
	MOVF       R0+0, 0
	MOVWF      CCPR2H+0
;MyProject.c,294 :: 		CCPR2L = (40000 - angle);
	MOVF       R3+0, 0
	MOVWF      CCPR2L+0
;MyProject.c,295 :: 		CCP2CON = 0x08;             // compare mode, set output on match
	MOVLW      8
	MOVWF      CCP2CON+0
;MyProject.c,296 :: 		HL = 1;                     //next time High
	MOVLW      1
	MOVWF      _HL+0
;MyProject.c,297 :: 		TMR1H = 0;
	CLRF       TMR1H+0
;MyProject.c,298 :: 		TMR1L = 0;
	CLRF       TMR1L+0
;MyProject.c,299 :: 		}
L_interrupt30:
;MyProject.c,300 :: 		SET_BIT0_LOW(PIR2);
	BCF        PIR2+0, 0
;MyProject.c,301 :: 		}
	GOTO       L_interrupt31
L_interrupt28:
;MyProject.c,302 :: 		else if (IS_BIT1_HIGH(PIR1))
	BTFSS      PIR1+0, 1
	GOTO       L_interrupt32
;MyProject.c,304 :: 		tick++;
	INCF       _tick+0, 1
	BTFSC      STATUS+0, 2
	INCF       _tick+1, 1
;MyProject.c,305 :: 		SET_BIT1_LOW(PIR1);
	BCF        PIR1+0, 1
;MyProject.c,306 :: 		}
L_interrupt32:
L_interrupt31:
L_interrupt27:
L_interrupt25:
;MyProject.c,307 :: 		}
L_end_interrupt:
L__interrupt78:
	MOVF       ___savePCLATH+0, 0
	MOVWF      PCLATH+0
	SWAPF      ___saveSTATUS+0, 0
	MOVWF      STATUS+0
	SWAPF      R15+0, 1
	SWAPF      R15+0, 0
	RETFIE
; end of _interrupt

_StartSignal:

;MyProject.c,313 :: 		void StartSignal() {
;MyProject.c,314 :: 		SET_BIT1_LOW(TRISD);
	BCF        TRISD+0, 1
;MyProject.c,315 :: 		SET_BIT1_LOW(PORTD);
	BCF        PORTD+0, 1
;MyProject.c,316 :: 		mydelayms(18);
	MOVLW      18
	MOVWF      FARG_mydelayms_count+0
	MOVLW      0
	MOVWF      FARG_mydelayms_count+1
	CALL       _mydelayms+0
;MyProject.c,317 :: 		SET_BIT1_HIGH(PORTD);
	BSF        PORTD+0, 1
;MyProject.c,318 :: 		mydelayus(30);
	MOVLW      30
	MOVWF      FARG_mydelayus_count+0
	MOVLW      0
	MOVWF      FARG_mydelayus_count+1
	CALL       _mydelayus+0
;MyProject.c,319 :: 		SET_BIT1_HIGH(TRISD);
	BSF        TRISD+0, 1
;MyProject.c,320 :: 		}
L_end_StartSignal:
	RETURN
; end of _StartSignal

_CheckResponse:

;MyProject.c,322 :: 		void CheckResponse() {
;MyProject.c,323 :: 		Check = 0;
	CLRF       _Check+0
;MyProject.c,324 :: 		mydelayus(40);
	MOVLW      40
	MOVWF      FARG_mydelayus_count+0
	MOVLW      0
	MOVWF      FARG_mydelayus_count+1
	CALL       _mydelayus+0
;MyProject.c,325 :: 		if (IS_BIT1_LOW(PORTD)) {
	MOVLW      2
	ANDWF      PORTD+0, 0
	MOVWF      R0+0
	MOVLW      0
	ANDLW      0
	MOVWF      R0+1
	COMF       R0+0, 1
	COMF       R0+1, 1
	MOVF       R0+0, 0
	IORWF      R0+1, 0
	BTFSC      STATUS+0, 2
	GOTO       L_CheckResponse33
;MyProject.c,326 :: 		mydelayus(80);
	MOVLW      80
	MOVWF      FARG_mydelayus_count+0
	MOVLW      0
	MOVWF      FARG_mydelayus_count+1
	CALL       _mydelayus+0
;MyProject.c,327 :: 		if (IS_BIT1_HIGH(PORTD)) Check = 1; mydelayus(40);
	BTFSS      PORTD+0, 1
	GOTO       L_CheckResponse34
	MOVLW      1
	MOVWF      _Check+0
L_CheckResponse34:
	MOVLW      40
	MOVWF      FARG_mydelayus_count+0
	MOVLW      0
	MOVWF      FARG_mydelayus_count+1
	CALL       _mydelayus+0
;MyProject.c,328 :: 		}
L_CheckResponse33:
;MyProject.c,329 :: 		}
L_end_CheckResponse:
	RETURN
; end of _CheckResponse

_ReadData:

;MyProject.c,331 :: 		char ReadData() {
;MyProject.c,333 :: 		for (j = 0; j < 8; j++) {
	CLRF       ReadData_j_L0+0
L_ReadData35:
	MOVLW      8
	SUBWF      ReadData_j_L0+0, 0
	BTFSC      STATUS+0, 0
	GOTO       L_ReadData36
;MyProject.c,334 :: 		while (IS_BIT1_LOW(PORTD));
L_ReadData38:
	MOVLW      2
	ANDWF      PORTD+0, 0
	MOVWF      R0+0
	MOVLW      0
	ANDLW      0
	MOVWF      R0+1
	COMF       R0+0, 1
	COMF       R0+1, 1
	MOVF       R0+0, 0
	IORWF      R0+1, 0
	BTFSC      STATUS+0, 2
	GOTO       L_ReadData39
	GOTO       L_ReadData38
L_ReadData39:
;MyProject.c,335 :: 		mydelayus(30);
	MOVLW      30
	MOVWF      FARG_mydelayus_count+0
	MOVLW      0
	MOVWF      FARG_mydelayus_count+1
	CALL       _mydelayus+0
;MyProject.c,336 :: 		if (IS_BIT1_LOW(PORTD))
	MOVLW      2
	ANDWF      PORTD+0, 0
	MOVWF      R0+0
	MOVLW      0
	ANDLW      0
	MOVWF      R0+1
	COMF       R0+0, 1
	COMF       R0+1, 1
	MOVF       R0+0, 0
	IORWF      R0+1, 0
	BTFSC      STATUS+0, 2
	GOTO       L_ReadData40
;MyProject.c,337 :: 		i &= ~(1 << (7 - j));
	MOVF       ReadData_j_L0+0, 0
	SUBLW      7
	MOVWF      R0+0
	MOVF       R0+0, 0
	MOVWF      R1+0
	MOVLW      1
	MOVWF      R0+0
	MOVF       R1+0, 0
L__ReadData82:
	BTFSC      STATUS+0, 2
	GOTO       L__ReadData83
	RLF        R0+0, 1
	BCF        R0+0, 0
	ADDLW      255
	GOTO       L__ReadData82
L__ReadData83:
	COMF       R0+0, 1
	MOVF       R0+0, 0
	ANDWF      ReadData_i_L0+0, 1
	GOTO       L_ReadData41
L_ReadData40:
;MyProject.c,339 :: 		i |= (1 << (7 - j));
	MOVF       ReadData_j_L0+0, 0
	SUBLW      7
	MOVWF      R0+0
	MOVF       R0+0, 0
	MOVWF      R1+0
	MOVLW      1
	MOVWF      R0+0
	MOVF       R1+0, 0
L__ReadData84:
	BTFSC      STATUS+0, 2
	GOTO       L__ReadData85
	RLF        R0+0, 1
	BCF        R0+0, 0
	ADDLW      255
	GOTO       L__ReadData84
L__ReadData85:
	MOVF       R0+0, 0
	IORWF      ReadData_i_L0+0, 1
;MyProject.c,340 :: 		while (IS_BIT1_HIGH(PORTD));
L_ReadData42:
	BTFSS      PORTD+0, 1
	GOTO       L_ReadData43
	GOTO       L_ReadData42
L_ReadData43:
;MyProject.c,341 :: 		}
L_ReadData41:
;MyProject.c,333 :: 		for (j = 0; j < 8; j++) {
	INCF       ReadData_j_L0+0, 1
;MyProject.c,342 :: 		}
	GOTO       L_ReadData35
L_ReadData36:
;MyProject.c,343 :: 		return i;
	MOVF       ReadData_i_L0+0, 0
	MOVWF      R0+0
;MyProject.c,344 :: 		}
L_end_ReadData:
	RETURN
; end of _ReadData

_dht11disp:

;MyProject.c,345 :: 		void dht11disp()
;MyProject.c,347 :: 		StartSignal();
	CALL       _StartSignal+0
;MyProject.c,348 :: 		CheckResponse();
	CALL       _CheckResponse+0
;MyProject.c,349 :: 		if (Check == 1) {
	MOVF       _Check+0, 0
	XORLW      1
	BTFSS      STATUS+0, 2
	GOTO       L_dht11disp44
;MyProject.c,350 :: 		RH_byte1 = ReadData();
	CALL       _ReadData+0
	MOVF       R0+0, 0
	MOVWF      _RH_byte1+0
;MyProject.c,351 :: 		RH_byte2 = ReadData();
	CALL       _ReadData+0
	MOVF       R0+0, 0
	MOVWF      _RH_byte2+0
;MyProject.c,352 :: 		T_byte1 = ReadData();
	CALL       _ReadData+0
	MOVF       R0+0, 0
	MOVWF      _T_byte1+0
;MyProject.c,353 :: 		T_byte2 = ReadData();
	CALL       _ReadData+0
	MOVF       R0+0, 0
	MOVWF      _T_byte2+0
;MyProject.c,354 :: 		Sum = ReadData();
	CALL       _ReadData+0
	MOVF       R0+0, 0
	MOVWF      _Sum+0
	CLRF       _Sum+1
;MyProject.c,355 :: 		if (Sum == ((RH_byte1 + RH_byte2 + T_byte1 + T_byte2) & 0XFF)) {
	MOVF       _RH_byte2+0, 0
	ADDWF      _RH_byte1+0, 0
	MOVWF      R0+0
	CLRF       R0+1
	BTFSC      STATUS+0, 0
	INCF       R0+1, 1
	MOVF       _T_byte1+0, 0
	ADDWF      R0+0, 1
	BTFSC      STATUS+0, 0
	INCF       R0+1, 1
	MOVF       _T_byte2+0, 0
	ADDWF      R0+0, 1
	BTFSC      STATUS+0, 0
	INCF       R0+1, 1
	MOVLW      255
	ANDWF      R0+0, 0
	MOVWF      R2+0
	MOVF       R0+1, 0
	MOVWF      R2+1
	MOVLW      0
	ANDWF      R2+1, 1
	MOVF       _Sum+1, 0
	XORWF      R2+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__dht11disp87
	MOVF       R2+0, 0
	XORWF      _Sum+0, 0
L__dht11disp87:
	BTFSS      STATUS+0, 2
	GOTO       L_dht11disp45
;MyProject.c,356 :: 		Temp = T_byte1;
	MOVF       _T_byte1+0, 0
	MOVWF      _Temp+0
	CLRF       _Temp+1
;MyProject.c,357 :: 		RH = RH_byte1;
	MOVF       _RH_byte1+0, 0
	MOVWF      _RH+0
	CLRF       _RH+1
;MyProject.c,358 :: 		Lcd_Cmd(_LCD_CLEAR);
	MOVLW      1
	MOVWF      FARG_Lcd_Cmd_out_char+0
	CALL       _Lcd_Cmd+0
;MyProject.c,359 :: 		Lcd_Out(1, 6, "Temp: C");
	MOVLW      1
	MOVWF      FARG_Lcd_Out_row+0
	MOVLW      6
	MOVWF      FARG_Lcd_Out_column+0
	MOVLW      ?lstr1_MyProject+0
	MOVWF      FARG_Lcd_Out_text+0
	CALL       _Lcd_Out+0
;MyProject.c,360 :: 		Lcd_Out(2, 2, "Humidity: %");
	MOVLW      2
	MOVWF      FARG_Lcd_Out_row+0
	MOVLW      2
	MOVWF      FARG_Lcd_Out_column+0
	MOVLW      ?lstr2_MyProject+0
	MOVWF      FARG_Lcd_Out_text+0
	CALL       _Lcd_Out+0
;MyProject.c,361 :: 		LCD_Chr(1, 12, 48 + ((Temp / 10) % 10));
	MOVLW      1
	MOVWF      FARG_Lcd_Chr_row+0
	MOVLW      12
	MOVWF      FARG_Lcd_Chr_column+0
	MOVLW      10
	MOVWF      R4+0
	MOVLW      0
	MOVWF      R4+1
	MOVF       _Temp+0, 0
	MOVWF      R0+0
	MOVF       _Temp+1, 0
	MOVWF      R0+1
	CALL       _Div_16X16_U+0
	MOVLW      10
	MOVWF      R4+0
	MOVLW      0
	MOVWF      R4+1
	CALL       _Div_16X16_U+0
	MOVF       R8+0, 0
	MOVWF      R0+0
	MOVF       R8+1, 0
	MOVWF      R0+1
	MOVF       R0+0, 0
	ADDLW      48
	MOVWF      FARG_Lcd_Chr_out_char+0
	CALL       _Lcd_Chr+0
;MyProject.c,362 :: 		LCD_Chr(1, 13, 48 + (Temp % 10));
	MOVLW      1
	MOVWF      FARG_Lcd_Chr_row+0
	MOVLW      13
	MOVWF      FARG_Lcd_Chr_column+0
	MOVLW      10
	MOVWF      R4+0
	MOVLW      0
	MOVWF      R4+1
	MOVF       _Temp+0, 0
	MOVWF      R0+0
	MOVF       _Temp+1, 0
	MOVWF      R0+1
	CALL       _Div_16X16_U+0
	MOVF       R8+0, 0
	MOVWF      R0+0
	MOVF       R8+1, 0
	MOVWF      R0+1
	MOVF       R0+0, 0
	ADDLW      48
	MOVWF      FARG_Lcd_Chr_out_char+0
	CALL       _Lcd_Chr+0
;MyProject.c,363 :: 		LCD_Chr(2, 12, 48 + ((RH / 10) % 10));
	MOVLW      2
	MOVWF      FARG_Lcd_Chr_row+0
	MOVLW      12
	MOVWF      FARG_Lcd_Chr_column+0
	MOVLW      10
	MOVWF      R4+0
	MOVLW      0
	MOVWF      R4+1
	MOVF       _RH+0, 0
	MOVWF      R0+0
	MOVF       _RH+1, 0
	MOVWF      R0+1
	CALL       _Div_16X16_U+0
	MOVLW      10
	MOVWF      R4+0
	MOVLW      0
	MOVWF      R4+1
	CALL       _Div_16X16_U+0
	MOVF       R8+0, 0
	MOVWF      R0+0
	MOVF       R8+1, 0
	MOVWF      R0+1
	MOVF       R0+0, 0
	ADDLW      48
	MOVWF      FARG_Lcd_Chr_out_char+0
	CALL       _Lcd_Chr+0
;MyProject.c,364 :: 		LCD_Chr(2, 13, 48 + (RH % 10));
	MOVLW      2
	MOVWF      FARG_Lcd_Chr_row+0
	MOVLW      13
	MOVWF      FARG_Lcd_Chr_column+0
	MOVLW      10
	MOVWF      R4+0
	MOVLW      0
	MOVWF      R4+1
	MOVF       _RH+0, 0
	MOVWF      R0+0
	MOVF       _RH+1, 0
	MOVWF      R0+1
	CALL       _Div_16X16_U+0
	MOVF       R8+0, 0
	MOVWF      R0+0
	MOVF       R8+1, 0
	MOVWF      R0+1
	MOVF       R0+0, 0
	ADDLW      48
	MOVWF      FARG_Lcd_Chr_out_char+0
	CALL       _Lcd_Chr+0
;MyProject.c,365 :: 		}
	GOTO       L_dht11disp46
L_dht11disp45:
;MyProject.c,367 :: 		Lcd_Cmd(_LCD_CURSOR_OFF); // cursor off
	MOVLW      12
	MOVWF      FARG_Lcd_Cmd_out_char+0
	CALL       _Lcd_Cmd+0
;MyProject.c,368 :: 		Lcd_Cmd(_LCD_CLEAR); // clear LCD
	MOVLW      1
	MOVWF      FARG_Lcd_Cmd_out_char+0
	CALL       _Lcd_Cmd+0
;MyProject.c,369 :: 		Lcd_Out(1, 1, "Check sum error");
	MOVLW      1
	MOVWF      FARG_Lcd_Out_row+0
	MOVLW      1
	MOVWF      FARG_Lcd_Out_column+0
	MOVLW      ?lstr3_MyProject+0
	MOVWF      FARG_Lcd_Out_text+0
	CALL       _Lcd_Out+0
;MyProject.c,370 :: 		}
L_dht11disp46:
;MyProject.c,371 :: 		}
	GOTO       L_dht11disp47
L_dht11disp44:
;MyProject.c,374 :: 		Lcd_Out(1, 3, "No response");
	MOVLW      1
	MOVWF      FARG_Lcd_Out_row+0
	MOVLW      3
	MOVWF      FARG_Lcd_Out_column+0
	MOVLW      ?lstr4_MyProject+0
	MOVWF      FARG_Lcd_Out_text+0
	CALL       _Lcd_Out+0
;MyProject.c,375 :: 		Lcd_Out(2, 1, "from the sensor");
	MOVLW      2
	MOVWF      FARG_Lcd_Out_row+0
	MOVLW      1
	MOVWF      FARG_Lcd_Out_column+0
	MOVLW      ?lstr5_MyProject+0
	MOVWF      FARG_Lcd_Out_text+0
	CALL       _Lcd_Out+0
;MyProject.c,376 :: 		Lcd_Cmd(_LCD_CLEAR);
	MOVLW      1
	MOVWF      FARG_Lcd_Cmd_out_char+0
	CALL       _Lcd_Cmd+0
;MyProject.c,377 :: 		}
L_dht11disp47:
;MyProject.c,378 :: 		mydelayms(1000);
	MOVLW      232
	MOVWF      FARG_mydelayms_count+0
	MOVLW      3
	MOVWF      FARG_mydelayms_count+1
	CALL       _mydelayms+0
;MyProject.c,379 :: 		}
L_end_dht11disp:
	RETURN
; end of _dht11disp

_DCMOTOR:

;MyProject.c,380 :: 		void DCMOTOR()
;MyProject.c,382 :: 		dis = Distance();
	CALL       _Distance+0
	MOVF       R0+0, 0
	MOVWF      _dis+0
	MOVF       R0+1, 0
	MOVWF      _dis+1
;MyProject.c,383 :: 		}
L_end_DCMOTOR:
	RETURN
; end of _DCMOTOR

_main:

;MyProject.c,385 :: 		void main() {
;MyProject.c,386 :: 		Lcd_Init();
	CALL       _Lcd_Init+0
;MyProject.c,387 :: 		Lcd_Cmd(_LCD_CURSOR_OFF); // cursor off
	MOVLW      12
	MOVWF      FARG_Lcd_Cmd_out_char+0
	CALL       _Lcd_Cmd+0
;MyProject.c,388 :: 		Lcd_Cmd(_LCD_CLEAR); // clear LCD
	MOVLW      1
	MOVWF      FARG_Lcd_Cmd_out_char+0
	CALL       _Lcd_Cmd+0
;MyProject.c,389 :: 		Init();
	CALL       _Init+0
;MyProject.c,390 :: 		angle = 1200;
	MOVLW      176
	MOVWF      _angle+0
	MOVLW      4
	MOVWF      _angle+1
;MyProject.c,392 :: 		while (1) {
L_main48:
;MyProject.c,393 :: 		if (FollowingMode)
	MOVF       _FollowingMode+0, 0
	BTFSC      STATUS+0, 2
	GOTO       L_main50
;MyProject.c,395 :: 		SET_BIT7_HIGH(PORTB);
	BSF        PORTB+0, 7
;MyProject.c,396 :: 		dis = Distance();
	CALL       _Distance+0
	MOVF       R0+0, 0
	MOVWF      _dis+0
	MOVF       R0+1, 0
	MOVWF      _dis+1
;MyProject.c,397 :: 		if (dis <= 20)
	MOVF       R0+1, 0
	SUBLW      0
	BTFSS      STATUS+0, 2
	GOTO       L__main90
	MOVF       R0+0, 0
	SUBLW      20
L__main90:
	BTFSS      STATUS+0, 0
	GOTO       L_main51
;MyProject.c,399 :: 		CCPR1L = 0;
	CLRF       CCPR1L+0
;MyProject.c,400 :: 		}
	GOTO       L_main52
L_main51:
;MyProject.c,403 :: 		direction(0);
	CLRF       FARG_direction_dir+0
	CALL       _direction+0
;MyProject.c,404 :: 		}
L_main52:
;MyProject.c,405 :: 		SET_BIT0_LOW(PIE2);
	BCF        PIE2+0, 0
;MyProject.c,406 :: 		dht11disp();
	CALL       _dht11disp+0
;MyProject.c,407 :: 		}
	GOTO       L_main53
L_main50:
;MyProject.c,410 :: 		SET_BIT7_LOW(PORTB);
	BCF        PORTB+0, 7
;MyProject.c,411 :: 		SET_BIT0_HIGH(PIE2);
	BSF        PIE2+0, 0
;MyProject.c,412 :: 		CCPR1L = 0;
	CLRF       CCPR1L+0
;MyProject.c,413 :: 		if (IS_BIT2_HIGH(PORTE))
	BTFSS      PORTE+0, 2
	GOTO       L_main54
;MyProject.c,415 :: 		angle += 1000;
	MOVLW      232
	ADDWF      _angle+0, 0
	MOVWF      R1+0
	MOVF       _angle+1, 0
	BTFSC      STATUS+0, 0
	ADDLW      1
	ADDLW      3
	MOVWF      R1+1
	MOVF       R1+0, 0
	MOVWF      _angle+0
	MOVF       R1+1, 0
	MOVWF      _angle+1
;MyProject.c,416 :: 		if (angle >= 3500) angle = 1250;
	MOVLW      13
	SUBWF      R1+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__main91
	MOVLW      172
	SUBWF      R1+0, 0
L__main91:
	BTFSS      STATUS+0, 0
	GOTO       L_main55
	MOVLW      226
	MOVWF      _angle+0
	MOVLW      4
	MOVWF      _angle+1
L_main55:
;MyProject.c,417 :: 		for (i = 0; i < ARRAYLEN(naghama); i++)
	CLRF       _i+0
	CLRF       _i+1
L_main56:
	MOVF       _naghama+0, 0
	MOVWF      R4+0
	MOVLW      7
	MOVWF      R0+0
	CALL       _Div_8X8_U+0
	MOVLW      128
	XORWF      _i+1, 0
	MOVWF      R1+0
	MOVLW      128
	SUBWF      R1+0, 0
	BTFSS      STATUS+0, 2
	GOTO       L__main92
	MOVF       R0+0, 0
	SUBWF      _i+0, 0
L__main92:
	BTFSC      STATUS+0, 0
	GOTO       L_main57
;MyProject.c,419 :: 		if (naghama[i])
	MOVF       _i+0, 0
	ADDLW      _naghama+0
	MOVWF      FSR
	MOVF       INDF+0, 0
	BTFSC      STATUS+0, 2
	GOTO       L_main59
;MyProject.c,420 :: 		SET_BIT5_HIGH(PORTA);
	BSF        PORTA+0, 5
	GOTO       L_main60
L_main59:
;MyProject.c,422 :: 		SET_BIT5_LOW(PORTA);
	BCF        PORTA+0, 5
L_main60:
;MyProject.c,417 :: 		for (i = 0; i < ARRAYLEN(naghama); i++)
	INCF       _i+0, 1
	BTFSC      STATUS+0, 2
	INCF       _i+1, 1
;MyProject.c,423 :: 		}
	GOTO       L_main56
L_main57:
;MyProject.c,424 :: 		}
L_main54:
;MyProject.c,425 :: 		Lcd_Cmd(_LCD_CLEAR);
	MOVLW      1
	MOVWF      FARG_Lcd_Cmd_out_char+0
	CALL       _Lcd_Cmd+0
;MyProject.c,426 :: 		Lcd_Out(1, 1, "see pill disp");
	MOVLW      1
	MOVWF      FARG_Lcd_Out_row+0
	MOVLW      1
	MOVWF      FARG_Lcd_Out_column+0
	MOVLW      ?lstr6_MyProject+0
	MOVWF      FARG_Lcd_Out_text+0
	CALL       _Lcd_Out+0
;MyProject.c,427 :: 		mydelayms(250);
	MOVLW      250
	MOVWF      FARG_mydelayms_count+0
	CLRF       FARG_mydelayms_count+1
	CALL       _mydelayms+0
;MyProject.c,428 :: 		SET_BIT5_LOW(PORTA);
	BCF        PORTA+0, 5
;MyProject.c,429 :: 		}
L_main53:
;MyProject.c,430 :: 		}
	GOTO       L_main48
;MyProject.c,431 :: 		}
L_end_main:
	GOTO       $+0
; end of _main
