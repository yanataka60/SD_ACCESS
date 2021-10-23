;MP-85 Sample
; LEDを右回りに点滅
        ORG     7C00H   

LED1    EQU     7F4AH
LED2    EQU     7F49H
LED3    EQU     7F48H
LED4    EQU     7F47H
LED5    EQU     7F46H
LED6    EQU     7F45H
DOT     EQU     7F44H

START:  CALL    CLR
        CALL    TIMER
STRT1:  CALL    CLR
        LD      HL,LED1
        LD      (HL),01H
        CALL    TIMER   
        CALL    CLR
        LD      HL,LED2
        LD      (HL),01H
        CALL    TIMER   
        CALL    CLR
        LD      HL,LED3
        LD      (HL),01H
        CALL    TIMER   
        CALL    CLR
        LD      HL,LED4
        LD      (HL),01H
        CALL    TIMER   
        CALL    CLR
        LD      HL,LED5
        LD      (HL),01H
        CALL    TIMER   
        CALL    CLR
        LD      HL,LED6
        LD      (HL),01H
        CALL    TIMER   
        CALL    CLR
        LD      HL,LED6
        LD      (HL),02H
        CALL    TIMER   
        CALL    CLR
        LD      HL,LED6
        LD      (HL),04H
        CALL    TIMER   
        CALL    CLR
        LD      HL,LED6
        LD      (HL),08H
        CALL    TIMER   
        CALL    CLR
        LD      HL,LED5
        LD      (HL),08H
        CALL    TIMER   
        CALL    CLR
        LD      HL,LED4
        LD      (HL),08H
        CALL    TIMER   
        CALL    CLR
        LD      HL,LED3
        LD      (HL),08H
        CALL    TIMER   
        CALL    CLR
        LD      HL,LED2
        LD      (HL),08H
        CALL    TIMER   
        CALL    CLR
        LD      HL,LED1
        LD      (HL),08H
        CALL    TIMER   
        CALL    CLR
        LD      HL,LED1
        LD      (HL),10H
        CALL    TIMER   
        CALL    CLR
        LD      HL,LED1
        LD      (HL),20H
        CALL    TIMER   

        CALL    CLR
        LD      HL,DOT
        LD      (HL),01H
        CALL    TIMER   
        CALL    TIMER   
        CALL    CLR
        LD      HL,DOT
        LD      (HL),02H
        CALL    TIMER   
        CALL    TIMER   
        CALL    CLR
        LD      HL,DOT
        LD      (HL),04H
        CALL    TIMER   
        CALL    TIMER   
        CALL    CLR
        LD      HL,DOT
        LD      (HL),08H
        CALL    TIMER   
        CALL    TIMER   
        CALL    CLR
        LD      HL,DOT
        LD      (HL),10H
        CALL    TIMER   
        CALL    TIMER   
        CALL    CLR
        LD      HL,DOT
        LD      (HL),20H
        CALL    TIMER   
        CALL    TIMER   
        CALL    CLR
        LD      HL,DOT
        LD      (HL),10H
        CALL    TIMER   
        CALL    TIMER   
        CALL    CLR
        LD      HL,DOT
        LD      (HL),08H
        CALL    TIMER   
        CALL    TIMER   
        CALL    CLR
        LD      HL,DOT
        LD      (HL),04H
        CALL    TIMER   
        CALL    TIMER   
        CALL    CLR
        LD      HL,DOT
        LD      (HL),02H
        CALL    TIMER   
        CALL    TIMER   
        CALL    CLR
        LD      HL,DOT
        LD      (HL),01H
        CALL    TIMER   
        CALL    TIMER   

        JP      STRT1

TIMER:
        CALL    04E7H
        LD      A,20H
LOP1:   LD      D,0FFH
LOP2:   DEC     D       
        JP      NZ,LOP2    
        DEC     A       
        JP      NZ,LOP1
        RET
            
CLR:    XOR     A
        LD      HL,LED1
        LD      (HL),A
        DEC     HL      
        LD      (HL),A
        DEC     HL      
        LD      (HL),A
        DEC     HL      
        LD      (HL),A
        DEC     HL      
        LD      (HL),A
        DEC     HL      
        LD      (HL),A
        DEC     HL      
        LD      (HL),A
        RET
        
        END
