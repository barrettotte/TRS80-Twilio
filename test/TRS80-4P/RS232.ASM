; TEST INPUT FROM KEYBOARD OR RS232
;
; RS232 INITIALIZATION
; $16888 - 
; $16889 -
;
        XOR     A                  DON'T WAIT
        LD      (16890),A
        CALL    RSINIT
        CALL    VDCLS
KEYIN   CALL    KBCHAR             CHECK KEYBOARD
        CP      0
        JR      Z,RSIN             IF NONE,CHECK RS232
        CALL    VDCHAR             ECHO
        CALL    RSTX               SEND TO RS232
RSIN    LD      HL,16872           HL=CHAR INPUT BUFFER
        CALL    RSRCV              CHECK RS232 INPUT
        LD      A,(HL)             GET BUFFER
        CP      0
        JR      Z,KEYIN            IF NONE,CHECK KEYBOARD
        CALL    VDCHAR             ELSE DISPLAY CHAR
        JR      KEYIN              CHECK KEYBOARD
        JP      READY              RETURN TO BASIC