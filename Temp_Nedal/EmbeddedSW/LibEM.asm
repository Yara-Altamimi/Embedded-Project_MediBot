
_interrupt:
	MOVWF      R15+0
	SWAPF      STATUS+0, 0
	CLRF       STATUS+0
	MOVWF      ___saveSTATUS+0
	MOVF       PCLATH+0, 0
	MOVWF      ___savePCLATH+0
	CLRF       PCLATH+0

;LibEM.c,66 :: 		void interrupt(void)
;LibEM.c,69 :: 		}
L_end_interrupt:
L__interrupt1:
	MOVF       ___savePCLATH+0, 0
	MOVWF      PCLATH+0
	SWAPF      ___saveSTATUS+0, 0
	MOVWF      STATUS+0
	SWAPF      R15+0, 1
	SWAPF      R15+0, 0
	RETFIE
; end of _interrupt

_main:

;LibEM.c,71 :: 		void main()
;LibEM.c,73 :: 		SET_BIT1_INPUT(PORTA);
	BSF        PORTA+0, 1
;LibEM.c,74 :: 		SET_BIT0_OUTPUT(PORTA);
	BCF        PORTA+0, 0
;LibEM.c,78 :: 		}
L_end_main:
	GOTO       $+0
; end of _main
