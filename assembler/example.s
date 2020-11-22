        AREA    subrout, CODE, READONLY     ; Name this block of code
        ENTRY                     ; Mark first instruction to execute
start   MOV     r0, #10           ; Set up parameters
        MOV     r1, #3
        BL      doadd             ; Call subroutine
stop    MOV     r0, #0x18         ; angel_SWIreason_ReportException
        LDR     r1, =0x20026      ; ADP_Stopped_ApplicationExit
        SVC     #0x123456         ; ARM semihosting (formerly SWI)
doadd   ADD     r0, r0, r1        ; Subroutine code
        BX      lr                ; Return from subroutine
        END                       ; Mark end of file