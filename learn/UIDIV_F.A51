;
; Unsigned Integer Division & Modulo for classic 8051
;
;    R6|R7 = R6|R7 / R4|R5;
;    R4|R5 = R6|R7 % R4|R5;
;

                NAME    ?C?UIDIV
?C?LIB_CODE     SEGMENT         CODE

                RSEG    ?C?LIB_CODE

                PUBLIC  ?C?UIDIV

?C?UIDIV:       CJNE    R4,#0,DIV16BIT
                CJNE    R6,#0,DIV8BIT
                MOV     A,R7
                MOV     B,R5
                DIV     AB
                MOV     R7,A
                MOV     R5,B
                RET

DIV16BIT:       CLR     A               ; clear modulo value 
                XCH     A,R4
                MOV     R0,A
                MOV     B,#8            ; number of bits 
DIV16LOOP:      MOV     A,R7            ; shift operation
                ADD     A,R7
                MOV     R7,A
                MOV     A,R6
                RLC     A
                MOV     R6,A
                MOV     A,R4
                RLC     A
                MOV     R4,A
; test if remainder > divisor
                MOV     A,R6
                SUBB    A,R5
                MOV     A,R4
                SUBB    A,R0
                JC      NO16DIV
; subtract
                MOV     R4,A
                MOV     A,R6
                SUBB    A,R5
                MOV     R6,A
                INC     R7              ; Increment Result

NO16DIV:        DJNZ    B,DIV16LOOP
                CLR     A
                XCH     A,R6
                MOV     R5,A
                RET


DIV8BIT:        MOV     A,R5
                MOV     R0,A
                MOV     B,A
                MOV     A,R6
                CJNE    A,#16,$+3
                JC      DIV8_12
                DIV     AB
                JB      OV,RETURN
                MOV     R6,A
                MOV     R5,B
                MOV     B,#8            ; number of bits 
DIV8LOOP:       MOV     A,R7            ; Shift operation
                ADD     A,R7
                MOV     R7,A
                MOV     A,R5
                RLC     A
                MOV     R5,A
                JC      DO8SUB
                SUBB    A,R0
                JNC     DO8SUB2
                DJNZ    B,DIV8LOOP
                RET

DO8SUB:         CLR     C
                SUBB    A,R0
DO8SUB2:        MOV     R5,A
                INC     R7
                DJNZ    B,DIV8LOOP
RETURN:         RET


DIV8_12:        MOV     A,R7                 ; Division of bit 4..11 / bit 0..7
                SWAP    A
                MOV     R7,A
                ANL     A,#0FH
                XCH     A,R6
                SWAP    A
                ORL     A,R6
                DIV     AB
                JB      OV,RETURN
                MOV     R6,A
                MOV     R5,B

                MOV     A,R7
                ANL     A,#0F0H
                ADD     A,ACC
                MOV     R7,A
                MOV     A,R5
                RLC     A
                MOV     R5,A
                JC      aDO8SUB
                SUBB    A,R0
                JNC     aDO8SUB2
                JC      aDO8SUB3
aDO8SUB:        CLR     C
                SUBB    A,R0
aDO8SUB2:       MOV     R5,A
                INC     R7
aDO8SUB3:
;
                REPT    3
LOCAL   bDO8SUB, bDO8SUB2, bDO8SUB3
                MOV     A,R7            ; Shift Operation
                ADD     A,R7
                MOV     R7,A
                MOV     A,R5
                RLC     A
                MOV     R5,A
                JC      bDO8SUB
                SUBB    A,R0
                JNC     bDO8SUB2
                JC      bDO8SUB3

bDO8SUB:        CLR     C
                SUBB    A,R0
bDO8SUB2:       MOV     R5,A
                INC     R7
bDO8SUB3:

                ENDM

                MOV     A,R6
                SWAP    A
                ANL     A,#00FH
                XCH     A,R6
                SWAP    A
                ANL     A,#0F0H
                XCH     A,R7
                ANL     A,#00FH
                ORL     A,R7
                MOV     R7,A

                RET

                END
