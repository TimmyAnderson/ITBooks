.486
.model flat, stdcall
option casemap :none

include include\windows.inc
include macros\macros.asm

include include\masm32.inc
include include\user32.inc
include include\kernel32.inc

includelib masm32.lib
includelib user32.lib
includelib kernel32.lib

.DATA
_STRING_1 BYTE "GLOBAL STRING !",0
_STRING_2 BYTE "[5]: ",0
_STRING_3 BYTE " !",0
_STRING_4 BYTE "[6]: ",0
_STRING_5 BYTE "DeltaMK3",0
_STRING_6 BYTE "Timmy Anderson",0
_STRING_7 BYTE "Jenny",0
_STRING_8 BYTE "Timmy",0
_STRING_9 BYTE "LocalIntVariable",0
_STRING_10 BYTE "LocalStringVariable",0
_STRING_11 BYTE "Atreyu",0
_STRING_12 BYTE "BEGIN of PROGRAM !",0
_STRING_13 BYTE "END of PROGRAM !",0
GlobalIntArray DWORD 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
GlobalStringArray DWORD 0,0,0,0,0
GlobalInt DWORD 0
GlobalString DWORD 0
GlobalIntInitialized DWORD 33
GlobalStringInitialized DWORD OFFSET _STRING_1
_ConversionBuffer BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0; Buffer for INT to STRING conversion !
_ConversionString BYTE "%d",0                     ; Conversion string for INT to STRING conversion !
_EmptyLine BYTE 13,10,0                           ; Empty line string !

.CODE

Code:
CALL Main
INVOKE ExitProcess,0

PrintInt PROC                                     ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Begins procedure [PrintInt()].
PUSH EBP                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBP to STACK.
PUSH EBX                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBX to STACK.
PUSH ECX                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of ECX to STACK.
MOV EBP,ESP                                       ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Moves ESP to EBP to store begin address of LOCAL VARIABLES.
SUB ESP,0000h                                     ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Allocates memory for local variables.
MOV EAX,[EBP+16]                                  ; Moves ADDRESS of INTEGER VALUE to EAX.
INVOKE wsprintf, OFFSET _ConversionBuffer, OFFSET _ConversionString, EAX; Calls wsprintf() to fill BUFFER with INTEGER VALUE.
print OFFSET _ConversionBuffer                    ; Prints INTEGER VALUE to CONSOLE.
PrintInt_EXIT:                                    ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Label to procedure [PrintInt()] exit code.
MOV ESP,EBP                                       ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Deallocates memory of local variables.
POP ECX                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of ECX.
POP EBX                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBX.
POP EBP                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBP.
RET                                               ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Exits procedure [PrintInt()].
PrintInt ENDP                                     ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Ends procedure [PrintInt()].

PrintLineInt PROC                                 ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Begins procedure [PrintLineInt()].
PUSH EBP                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBP to STACK.
PUSH EBX                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBX to STACK.
PUSH ECX                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of ECX to STACK.
MOV EBP,ESP                                       ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Moves ESP to EBP to store begin address of LOCAL VARIABLES.
SUB ESP,0000h                                     ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Allocates memory for local variables.
MOV EAX,[EBP+16]                                  ; Moves ADDRESS of INTEGER VALUE to EAX.
INVOKE wsprintf, OFFSET _ConversionBuffer, OFFSET _ConversionString, EAX; Calls wsprintf() to fill BUFFER with INTEGER VALUE.
print OFFSET _ConversionBuffer                    ; Prints INTEGER VALUE to CONSOLE.
print OFFSET _EmptyLine                           ; Prints EMPTY LINE to CONSOLE.
PrintLineInt_EXIT:                                ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Label to procedure [PrintLineInt()] exit code.
MOV ESP,EBP                                       ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Deallocates memory of local variables.
POP ECX                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of ECX.
POP EBX                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBX.
POP EBP                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBP.
RET                                               ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Exits procedure [PrintLineInt()].
PrintLineInt ENDP                                 ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Ends procedure [PrintLineInt()].

PrintString PROC                                  ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Begins procedure [PrintString()].
PUSH EBP                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBP to STACK.
PUSH EBX                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBX to STACK.
PUSH ECX                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of ECX to STACK.
MOV EBP,ESP                                       ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Moves ESP to EBP to store begin address of LOCAL VARIABLES.
SUB ESP,0000h                                     ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Allocates memory for local variables.
MOV EAX,[EBP+16]                                  ; Moves ADDRESS of STRING VALUE to EAX.
print EAX                                         ; Prints STRING VALUE to CONSOLE.
PrintString_EXIT:                                 ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Label to procedure [PrintString()] exit code.
MOV ESP,EBP                                       ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Deallocates memory of local variables.
POP ECX                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of ECX.
POP EBX                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBX.
POP EBP                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBP.
RET                                               ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Exits procedure [PrintString()].
PrintString ENDP                                  ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Ends procedure [PrintString()].

PrintLineString PROC                              ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Begins procedure [PrintLineString()].
PUSH EBP                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBP to STACK.
PUSH EBX                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBX to STACK.
PUSH ECX                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of ECX to STACK.
MOV EBP,ESP                                       ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Moves ESP to EBP to store begin address of LOCAL VARIABLES.
SUB ESP,0000h                                     ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Allocates memory for local variables.
MOV EAX,[EBP+16]                                  ; Moves ADDRESS of STRING VALUE to EAX.
print EAX                                         ; Prints STRING VALUE to CONSOLE.
print OFFSET _EmptyLine                           ; Prints EMPTY LINE to CONSOLE.
PrintLineString_EXIT:                             ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Label to procedure [PrintLineString()] exit code.
MOV ESP,EBP                                       ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Deallocates memory of local variables.
POP ECX                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of ECX.
POP EBX                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBX.
POP EBP                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBP.
RET                                               ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Exits procedure [PrintLineString()].
PrintLineString ENDP                              ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Ends procedure [PrintLineString()].

Print5And6ItemsOfArray PROC                       ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Begins procedure [Print5And6ItemsOfArray()].
PUSH EBP                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBP to STACK.
PUSH EBX                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBX to STACK.
PUSH ECX                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of ECX to STACK.
MOV EBP,ESP                                       ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Moves ESP to EBP to store begin address of LOCAL VARIABLES.
SUB ESP,0000h                                     ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Allocates memory for local variables.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Text1] to EAX.
ADD EAX,001Ch                                     ; [VARIABLE -> id] - Adds offset for symbol [Text1] to EAX. Now EAX contains address of symbol [Text1].
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Text1] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [Text1] to STACK.
CALL PrintString                                  ; [CALL -> id(ARGS)] - Calls procedure [PrintString()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintString()] from STACK.
PUSH OFFSET _STRING_2                             ; [FACTOR -> string_literal] - Pushs address of LITERAL to STACK.
CALL PrintString                                  ; [CALL -> id(ARGS)] - Calls procedure [PrintString()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintString()] from STACK.
MOV EAX,0005h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,0004h                                     ; [VARIABLE -> id[EXPRESSION]] - Moves SIZEOF(ARRAY_ITEM) for array [IntArray] to EBX.
MUL EBX                                           ; [VARIABLE -> id[EXPRESSION]] - Multiplies EXPRESSION*SIZEOF(ARRAY_ITEM) to calculate array index byte offset for array [IntArray].
MOV EBX,EAX                                       ; [VARIABLE -> id[EXPRESSION]] - Moves array index byte offset EXPRESSION*SIZEOF(ARRAY_ITEM) for array [IntArray] to EBX.
MOV EAX,[EBP+20]                                  ; [VARIABLE -> id[EXPRESSION]] - Moves array base address [EBP+StackOffset] for parameter array [IntArray] to EAX.
ADD EAX,EBX                                       ; [VARIABLE -> id[EXPRESSION]] - Adds array index byt offset for array [IntArray] to EAX. Now EAX contains address of [IntArray[EXPRESSION]].
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [IntArray] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [IntArray] to STACK.
CALL PrintInt                                     ; [CALL -> id(ARGS)] - Calls procedure [PrintInt()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintInt()] from STACK.
PUSH OFFSET _STRING_3                             ; [FACTOR -> string_literal] - Pushs address of LITERAL to STACK.
CALL PrintLineString                              ; [CALL -> id(ARGS)] - Calls procedure [PrintLineString()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineString()] from STACK.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Text1] to EAX.
ADD EAX,001Ch                                     ; [VARIABLE -> id] - Adds offset for symbol [Text1] to EAX. Now EAX contains address of symbol [Text1].
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Text1] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [Text1] to STACK.
CALL PrintString                                  ; [CALL -> id(ARGS)] - Calls procedure [PrintString()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintString()] from STACK.
PUSH OFFSET _STRING_4                             ; [FACTOR -> string_literal] - Pushs address of LITERAL to STACK.
CALL PrintString                                  ; [CALL -> id(ARGS)] - Calls procedure [PrintString()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintString()] from STACK.
MOV EAX,0006h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,0004h                                     ; [VARIABLE -> id[EXPRESSION]] - Moves SIZEOF(ARRAY_ITEM) for array [IntArray] to EBX.
MUL EBX                                           ; [VARIABLE -> id[EXPRESSION]] - Multiplies EXPRESSION*SIZEOF(ARRAY_ITEM) to calculate array index byte offset for array [IntArray].
MOV EBX,EAX                                       ; [VARIABLE -> id[EXPRESSION]] - Moves array index byte offset EXPRESSION*SIZEOF(ARRAY_ITEM) for array [IntArray] to EBX.
MOV EAX,[EBP+20]                                  ; [VARIABLE -> id[EXPRESSION]] - Moves array base address [EBP+StackOffset] for parameter array [IntArray] to EAX.
ADD EAX,EBX                                       ; [VARIABLE -> id[EXPRESSION]] - Adds array index byt offset for array [IntArray] to EAX. Now EAX contains address of [IntArray[EXPRESSION]].
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [IntArray] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [IntArray] to STACK.
CALL PrintInt                                     ; [CALL -> id(ARGS)] - Calls procedure [PrintInt()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintInt()] from STACK.
PUSH OFFSET _STRING_3                             ; [FACTOR -> string_literal] - Pushs address of LITERAL to STACK.
CALL PrintLineString                              ; [CALL -> id(ARGS)] - Calls procedure [PrintLineString()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineString()] from STACK.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Text2] to EAX.
ADD EAX,0018h                                     ; [VARIABLE -> id] - Adds offset for symbol [Text2] to EAX. Now EAX contains address of symbol [Text2].
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Text2] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [Text2] to STACK.
CALL PrintString                                  ; [CALL -> id(ARGS)] - Calls procedure [PrintString()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintString()] from STACK.
PUSH OFFSET _STRING_2                             ; [FACTOR -> string_literal] - Pushs address of LITERAL to STACK.
CALL PrintString                                  ; [CALL -> id(ARGS)] - Calls procedure [PrintString()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintString()] from STACK.
MOV EAX,0005h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,0004h                                     ; [VARIABLE -> id[EXPRESSION]] - Moves SIZEOF(ARRAY_ITEM) for array [StringArray] to EBX.
MUL EBX                                           ; [VARIABLE -> id[EXPRESSION]] - Multiplies EXPRESSION*SIZEOF(ARRAY_ITEM) to calculate array index byte offset for array [StringArray].
MOV EBX,EAX                                       ; [VARIABLE -> id[EXPRESSION]] - Moves array index byte offset EXPRESSION*SIZEOF(ARRAY_ITEM) for array [StringArray] to EBX.
MOV EAX,[EBP+16]                                  ; [VARIABLE -> id[EXPRESSION]] - Moves array base address [EBP+StackOffset] for parameter array [StringArray] to EAX.
ADD EAX,EBX                                       ; [VARIABLE -> id[EXPRESSION]] - Adds array index byt offset for array [StringArray] to EAX. Now EAX contains address of [StringArray[EXPRESSION]].
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [StringArray] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [StringArray] to STACK.
CALL PrintString                                  ; [CALL -> id(ARGS)] - Calls procedure [PrintString()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintString()] from STACK.
PUSH OFFSET _STRING_3                             ; [FACTOR -> string_literal] - Pushs address of LITERAL to STACK.
CALL PrintLineString                              ; [CALL -> id(ARGS)] - Calls procedure [PrintLineString()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineString()] from STACK.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Text2] to EAX.
ADD EAX,0018h                                     ; [VARIABLE -> id] - Adds offset for symbol [Text2] to EAX. Now EAX contains address of symbol [Text2].
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Text2] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [Text2] to STACK.
CALL PrintString                                  ; [CALL -> id(ARGS)] - Calls procedure [PrintString()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintString()] from STACK.
PUSH OFFSET _STRING_4                             ; [FACTOR -> string_literal] - Pushs address of LITERAL to STACK.
CALL PrintString                                  ; [CALL -> id(ARGS)] - Calls procedure [PrintString()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintString()] from STACK.
MOV EAX,0006h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,0004h                                     ; [VARIABLE -> id[EXPRESSION]] - Moves SIZEOF(ARRAY_ITEM) for array [StringArray] to EBX.
MUL EBX                                           ; [VARIABLE -> id[EXPRESSION]] - Multiplies EXPRESSION*SIZEOF(ARRAY_ITEM) to calculate array index byte offset for array [StringArray].
MOV EBX,EAX                                       ; [VARIABLE -> id[EXPRESSION]] - Moves array index byte offset EXPRESSION*SIZEOF(ARRAY_ITEM) for array [StringArray] to EBX.
MOV EAX,[EBP+16]                                  ; [VARIABLE -> id[EXPRESSION]] - Moves array base address [EBP+StackOffset] for parameter array [StringArray] to EAX.
ADD EAX,EBX                                       ; [VARIABLE -> id[EXPRESSION]] - Adds array index byt offset for array [StringArray] to EAX. Now EAX contains address of [StringArray[EXPRESSION]].
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [StringArray] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [StringArray] to STACK.
CALL PrintString                                  ; [CALL -> id(ARGS)] - Calls procedure [PrintString()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintString()] from STACK.
PUSH OFFSET _STRING_3                             ; [FACTOR -> string_literal] - Pushs address of LITERAL to STACK.
CALL PrintLineString                              ; [CALL -> id(ARGS)] - Calls procedure [PrintLineString()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineString()] from STACK.
Print5And6ItemsOfArray_EXIT:                      ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Label to procedure [Print5And6ItemsOfArray()] exit code.
MOV ESP,EBP                                       ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Deallocates memory of local variables.
POP ECX                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of ECX.
POP EBX                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBX.
POP EBP                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBP.
RET                                               ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Exits procedure [Print5And6ItemsOfArray()].
Print5And6ItemsOfArray ENDP                       ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Ends procedure [Print5And6ItemsOfArray()].

PrintItemOfArray PROC                             ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Begins procedure [PrintItemOfArray()].
PUSH EBP                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBP to STACK.
PUSH EBX                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBX to STACK.
PUSH ECX                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of ECX to STACK.
MOV EBP,ESP                                       ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Moves ESP to EBP to store begin address of LOCAL VARIABLES.
SUB ESP,0000h                                     ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Allocates memory for local variables.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Index] to EAX.
ADD EAX,0010h                                     ; [VARIABLE -> id] - Adds offset for symbol [Index] to EAX. Now EAX contains address of symbol [Index].
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Index] from address of variable.
MOV EBX,0004h                                     ; [VARIABLE -> id[EXPRESSION]] - Moves SIZEOF(ARRAY_ITEM) for array [IntArray] to EBX.
MUL EBX                                           ; [VARIABLE -> id[EXPRESSION]] - Multiplies EXPRESSION*SIZEOF(ARRAY_ITEM) to calculate array index byte offset for array [IntArray].
MOV EBX,EAX                                       ; [VARIABLE -> id[EXPRESSION]] - Moves array index byte offset EXPRESSION*SIZEOF(ARRAY_ITEM) for array [IntArray] to EBX.
MOV EAX,[EBP+20]                                  ; [VARIABLE -> id[EXPRESSION]] - Moves array base address [EBP+StackOffset] for parameter array [IntArray] to EAX.
ADD EAX,EBX                                       ; [VARIABLE -> id[EXPRESSION]] - Adds array index byt offset for array [IntArray] to EAX. Now EAX contains address of [IntArray[EXPRESSION]].
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [IntArray] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [IntArray] to STACK.
CALL PrintLineInt                                 ; [CALL -> id(ARGS)] - Calls procedure [PrintLineInt()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineInt()] from STACK.
PrintItemOfArray_EXIT:                            ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Label to procedure [PrintItemOfArray()] exit code.
MOV ESP,EBP                                       ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Deallocates memory of local variables.
POP ECX                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of ECX.
POP EBX                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBX.
POP EBP                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBP.
RET                                               ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Exits procedure [PrintItemOfArray()].
PrintItemOfArray ENDP                             ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Ends procedure [PrintItemOfArray()].

ParameterIntArray PROC                            ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Begins procedure [ParameterIntArray()].
PUSH EBP                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBP to STACK.
PUSH EBX                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBX to STACK.
PUSH ECX                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of ECX to STACK.
MOV EBP,ESP                                       ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Moves ESP to EBP to store begin address of LOCAL VARIABLES.
SUB ESP,0000h                                     ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Allocates memory for local variables.
MOV EAX,0001h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,0004h                                     ; [VARIABLE -> id[EXPRESSION]] - Moves SIZEOF(ARRAY_ITEM) for array [Array] to EBX.
MUL EBX                                           ; [VARIABLE -> id[EXPRESSION]] - Multiplies EXPRESSION*SIZEOF(ARRAY_ITEM) to calculate array index byte offset for array [Array].
MOV EBX,EAX                                       ; [VARIABLE -> id[EXPRESSION]] - Moves array index byte offset EXPRESSION*SIZEOF(ARRAY_ITEM) for array [Array] to EBX.
MOV EAX,[EBP+16]                                  ; [VARIABLE -> id[EXPRESSION]] - Moves array base address [EBP+StackOffset] for parameter array [Array] to EAX.
ADD EAX,EBX                                       ; [VARIABLE -> id[EXPRESSION]] - Adds array index byt offset for array [Array] to EAX. Now EAX contains address of [Array[EXPRESSION]].
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Array] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [Array] to STACK.
CALL PrintLineInt                                 ; [CALL -> id(ARGS)] - Calls procedure [PrintLineInt()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineInt()] from STACK.
ParameterIntArray_EXIT:                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Label to procedure [ParameterIntArray()] exit code.
MOV ESP,EBP                                       ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Deallocates memory of local variables.
POP ECX                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of ECX.
POP EBX                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBX.
POP EBP                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBP.
RET                                               ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Exits procedure [ParameterIntArray()].
ParameterIntArray ENDP                            ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Ends procedure [ParameterIntArray()].

PassParameterIntArray PROC                        ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Begins procedure [PassParameterIntArray()].
PUSH EBP                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBP to STACK.
PUSH EBX                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBX to STACK.
PUSH ECX                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of ECX to STACK.
MOV EBP,ESP                                       ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Moves ESP to EBP to store begin address of LOCAL VARIABLES.
SUB ESP,0000h                                     ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Allocates memory for local variables.
MOV EAX,[EBP+16]                                  ; [VARIABLE -> id] - Moves array base address [EBP+StackOffset] for parameter array [Array] to EAX.
PUSH EAX                                          ; [VARIABLE -> id] - Pushs address of variable [Array] to STACK.
CALL ParameterIntArray                            ; [CALL -> id(ARGS)] - Calls procedure [ParameterIntArray()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [ParameterIntArray()] from STACK.
MOV EAX,0001h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,0004h                                     ; [VARIABLE -> id[EXPRESSION]] - Moves SIZEOF(ARRAY_ITEM) for array [Array] to EBX.
MUL EBX                                           ; [VARIABLE -> id[EXPRESSION]] - Multiplies EXPRESSION*SIZEOF(ARRAY_ITEM) to calculate array index byte offset for array [Array].
MOV EBX,EAX                                       ; [VARIABLE -> id[EXPRESSION]] - Moves array index byte offset EXPRESSION*SIZEOF(ARRAY_ITEM) for array [Array] to EBX.
MOV EAX,[EBP+16]                                  ; [VARIABLE -> id[EXPRESSION]] - Moves array base address [EBP+StackOffset] for parameter array [Array] to EAX.
ADD EAX,EBX                                       ; [VARIABLE -> id[EXPRESSION]] - Adds array index byt offset for array [Array] to EAX. Now EAX contains address of [Array[EXPRESSION]].
PUSH EAX                                          ; [VARIABLE -> id[EXPRESSION]] - Pushs address of variable [Array[EXPRESSION]] to STACK.
MOV EAX,0001h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,0004h                                     ; [VARIABLE -> id[EXPRESSION]] - Moves SIZEOF(ARRAY_ITEM) for array [Array] to EBX.
MUL EBX                                           ; [VARIABLE -> id[EXPRESSION]] - Multiplies EXPRESSION*SIZEOF(ARRAY_ITEM) to calculate array index byte offset for array [Array].
MOV EBX,EAX                                       ; [VARIABLE -> id[EXPRESSION]] - Moves array index byte offset EXPRESSION*SIZEOF(ARRAY_ITEM) for array [Array] to EBX.
MOV EAX,[EBP+16]                                  ; [VARIABLE -> id[EXPRESSION]] - Moves array base address [EBP+StackOffset] for parameter array [Array] to EAX.
ADD EAX,EBX                                       ; [VARIABLE -> id[EXPRESSION]] - Adds array index byt offset for array [Array] to EAX. Now EAX contains address of [Array[EXPRESSION]].
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Array] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [Array] to STACK.
MOV EAX,0001h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Gets OPERAND O1 for operation [ADDITION] to EAX.
ADD EAX,EBX                                       ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Executes operation EAX=EAX+EBX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets address of VARIABLE for operation ASSIGNMENT to EAX.
MOV [EAX],EBX                                     ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Moves value of EXPRESSION to VARIABLE.
MOV EAX,[EBP+16]                                  ; [VARIABLE -> id] - Moves array base address [EBP+StackOffset] for parameter array [Array] to EAX.
PUSH EAX                                          ; [VARIABLE -> id] - Pushs address of variable [Array] to STACK.
CALL ParameterIntArray                            ; [CALL -> id(ARGS)] - Calls procedure [ParameterIntArray()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [ParameterIntArray()] from STACK.
PassParameterIntArray_EXIT:                       ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Label to procedure [PassParameterIntArray()] exit code.
MOV ESP,EBP                                       ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Deallocates memory of local variables.
POP ECX                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of ECX.
POP EBX                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBX.
POP EBP                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBP.
RET                                               ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Exits procedure [PassParameterIntArray()].
PassParameterIntArray ENDP                        ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Ends procedure [PassParameterIntArray()].

ParameterStringArray PROC                         ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Begins procedure [ParameterStringArray()].
PUSH EBP                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBP to STACK.
PUSH EBX                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBX to STACK.
PUSH ECX                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of ECX to STACK.
MOV EBP,ESP                                       ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Moves ESP to EBP to store begin address of LOCAL VARIABLES.
SUB ESP,0000h                                     ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Allocates memory for local variables.
MOV EAX,0001h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,0004h                                     ; [VARIABLE -> id[EXPRESSION]] - Moves SIZEOF(ARRAY_ITEM) for array [Array] to EBX.
MUL EBX                                           ; [VARIABLE -> id[EXPRESSION]] - Multiplies EXPRESSION*SIZEOF(ARRAY_ITEM) to calculate array index byte offset for array [Array].
MOV EBX,EAX                                       ; [VARIABLE -> id[EXPRESSION]] - Moves array index byte offset EXPRESSION*SIZEOF(ARRAY_ITEM) for array [Array] to EBX.
MOV EAX,[EBP+16]                                  ; [VARIABLE -> id[EXPRESSION]] - Moves array base address [EBP+StackOffset] for parameter array [Array] to EAX.
ADD EAX,EBX                                       ; [VARIABLE -> id[EXPRESSION]] - Adds array index byt offset for array [Array] to EAX. Now EAX contains address of [Array[EXPRESSION]].
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Array] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [Array] to STACK.
CALL PrintLineString                              ; [CALL -> id(ARGS)] - Calls procedure [PrintLineString()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineString()] from STACK.
ParameterStringArray_EXIT:                        ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Label to procedure [ParameterStringArray()] exit code.
MOV ESP,EBP                                       ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Deallocates memory of local variables.
POP ECX                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of ECX.
POP EBX                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBX.
POP EBP                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBP.
RET                                               ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Exits procedure [ParameterStringArray()].
ParameterStringArray ENDP                         ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Ends procedure [ParameterStringArray()].

PassParameterStringArray PROC                     ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Begins procedure [PassParameterStringArray()].
PUSH EBP                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBP to STACK.
PUSH EBX                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBX to STACK.
PUSH ECX                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of ECX to STACK.
MOV EBP,ESP                                       ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Moves ESP to EBP to store begin address of LOCAL VARIABLES.
SUB ESP,0000h                                     ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Allocates memory for local variables.
MOV EAX,[EBP+16]                                  ; [VARIABLE -> id] - Moves array base address [EBP+StackOffset] for parameter array [Array] to EAX.
PUSH EAX                                          ; [VARIABLE -> id] - Pushs address of variable [Array] to STACK.
CALL ParameterStringArray                         ; [CALL -> id(ARGS)] - Calls procedure [ParameterStringArray()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [ParameterStringArray()] from STACK.
PassParameterStringArray_EXIT:                    ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Label to procedure [PassParameterStringArray()] exit code.
MOV ESP,EBP                                       ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Deallocates memory of local variables.
POP ECX                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of ECX.
POP EBX                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBX.
POP EBP                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBP.
RET                                               ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Exits procedure [PassParameterStringArray()].
PassParameterStringArray ENDP                     ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Ends procedure [PassParameterStringArray()].

ParameterInt PROC                                 ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Begins procedure [ParameterInt()].
PUSH EBP                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBP to STACK.
PUSH EBX                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBX to STACK.
PUSH ECX                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of ECX to STACK.
MOV EBP,ESP                                       ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Moves ESP to EBP to store begin address of LOCAL VARIABLES.
SUB ESP,0000h                                     ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Allocates memory for local variables.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Value] to EAX.
ADD EAX,0010h                                     ; [VARIABLE -> id] - Adds offset for symbol [Value] to EAX. Now EAX contains address of symbol [Value].
PUSH EAX                                          ; [VARIABLE -> id] - Pushs address of variable [Value] to STACK.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Value] to EAX.
ADD EAX,0010h                                     ; [VARIABLE -> id] - Adds offset for symbol [Value] to EAX. Now EAX contains address of symbol [Value].
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Value] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [Value] to STACK.
MOV EAX,0001h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Gets OPERAND O1 for operation [ADDITION] to EAX.
ADD EAX,EBX                                       ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Executes operation EAX=EAX+EBX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets address of VARIABLE for operation ASSIGNMENT to EAX.
MOV [EAX],EBX                                     ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Moves value of EXPRESSION to VARIABLE.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Value] to EAX.
ADD EAX,0010h                                     ; [VARIABLE -> id] - Adds offset for symbol [Value] to EAX. Now EAX contains address of symbol [Value].
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Value] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [Value] to STACK.
CALL PrintLineInt                                 ; [CALL -> id(ARGS)] - Calls procedure [PrintLineInt()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineInt()] from STACK.
ParameterInt_EXIT:                                ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Label to procedure [ParameterInt()] exit code.
MOV ESP,EBP                                       ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Deallocates memory of local variables.
POP ECX                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of ECX.
POP EBX                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBX.
POP EBP                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBP.
RET                                               ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Exits procedure [ParameterInt()].
ParameterInt ENDP                                 ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Ends procedure [ParameterInt()].

PassParameterInt PROC                             ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Begins procedure [PassParameterInt()].
PUSH EBP                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBP to STACK.
PUSH EBX                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBX to STACK.
PUSH ECX                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of ECX to STACK.
MOV EBP,ESP                                       ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Moves ESP to EBP to store begin address of LOCAL VARIABLES.
SUB ESP,0000h                                     ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Allocates memory for local variables.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Value] to EAX.
ADD EAX,0010h                                     ; [VARIABLE -> id] - Adds offset for symbol [Value] to EAX. Now EAX contains address of symbol [Value].
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Value] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [Value] to STACK.
CALL ParameterInt                                 ; [CALL -> id(ARGS)] - Calls procedure [ParameterInt()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [ParameterInt()] from STACK.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Value] to EAX.
ADD EAX,0010h                                     ; [VARIABLE -> id] - Adds offset for symbol [Value] to EAX. Now EAX contains address of symbol [Value].
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Value] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [Value] to STACK.
CALL PrintLineInt                                 ; [CALL -> id(ARGS)] - Calls procedure [PrintLineInt()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineInt()] from STACK.
PassParameterInt_EXIT:                            ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Label to procedure [PassParameterInt()] exit code.
MOV ESP,EBP                                       ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Deallocates memory of local variables.
POP ECX                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of ECX.
POP EBX                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBX.
POP EBP                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBP.
RET                                               ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Exits procedure [PassParameterInt()].
PassParameterInt ENDP                             ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Ends procedure [PassParameterInt()].

ParameterString PROC                              ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Begins procedure [ParameterString()].
PUSH EBP                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBP to STACK.
PUSH EBX                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBX to STACK.
PUSH ECX                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of ECX to STACK.
MOV EBP,ESP                                       ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Moves ESP to EBP to store begin address of LOCAL VARIABLES.
SUB ESP,0000h                                     ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Allocates memory for local variables.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Value] to EAX.
ADD EAX,0010h                                     ; [VARIABLE -> id] - Adds offset for symbol [Value] to EAX. Now EAX contains address of symbol [Value].
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Value] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [Value] to STACK.
CALL PrintLineString                              ; [CALL -> id(ARGS)] - Calls procedure [PrintLineString()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineString()] from STACK.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Value] to EAX.
ADD EAX,0010h                                     ; [VARIABLE -> id] - Adds offset for symbol [Value] to EAX. Now EAX contains address of symbol [Value].
PUSH EAX                                          ; [VARIABLE -> id] - Pushs address of variable [Value] to STACK.
PUSH OFFSET _STRING_5                             ; [FACTOR -> string_literal] - Pushs address of LITERAL to STACK.
POP EBX                                           ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets value of EXPRESSION for operation ASSIGNMENT to EBX.
POP EAX                                           ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets address of VARIABLE for operation ASSIGNMENT to EAX.
MOV [EAX],EBX                                     ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Moves value of EXPRESSION to VARIABLE.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Value] to EAX.
ADD EAX,0010h                                     ; [VARIABLE -> id] - Adds offset for symbol [Value] to EAX. Now EAX contains address of symbol [Value].
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Value] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [Value] to STACK.
CALL PrintLineString                              ; [CALL -> id(ARGS)] - Calls procedure [PrintLineString()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineString()] from STACK.
ParameterString_EXIT:                             ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Label to procedure [ParameterString()] exit code.
MOV ESP,EBP                                       ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Deallocates memory of local variables.
POP ECX                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of ECX.
POP EBX                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBX.
POP EBP                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBP.
RET                                               ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Exits procedure [ParameterString()].
ParameterString ENDP                              ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Ends procedure [ParameterString()].

PassParameterString PROC                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Begins procedure [PassParameterString()].
PUSH EBP                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBP to STACK.
PUSH EBX                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBX to STACK.
PUSH ECX                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of ECX to STACK.
MOV EBP,ESP                                       ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Moves ESP to EBP to store begin address of LOCAL VARIABLES.
SUB ESP,0000h                                     ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Allocates memory for local variables.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Value] to EAX.
ADD EAX,0010h                                     ; [VARIABLE -> id] - Adds offset for symbol [Value] to EAX. Now EAX contains address of symbol [Value].
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Value] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [Value] to STACK.
CALL ParameterString                              ; [CALL -> id(ARGS)] - Calls procedure [ParameterString()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [ParameterString()] from STACK.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Value] to EAX.
ADD EAX,0010h                                     ; [VARIABLE -> id] - Adds offset for symbol [Value] to EAX. Now EAX contains address of symbol [Value].
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Value] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [Value] to STACK.
CALL PrintLineString                              ; [CALL -> id(ARGS)] - Calls procedure [PrintLineString()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineString()] from STACK.
PassParameterString_EXIT:                         ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Label to procedure [PassParameterString()] exit code.
MOV ESP,EBP                                       ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Deallocates memory of local variables.
POP ECX                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of ECX.
POP EBX                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBX.
POP EBP                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBP.
RET                                               ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Exits procedure [PassParameterString()].
PassParameterString ENDP                          ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Ends procedure [PassParameterString()].

Test1 PROC                                        ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Begins procedure [Test1()].
PUSH EBP                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBP to STACK.
PUSH EBX                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBX to STACK.
PUSH ECX                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of ECX to STACK.
MOV EBP,ESP                                       ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Moves ESP to EBP to store begin address of LOCAL VARIABLES.
SUB ESP,0000h                                     ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Allocates memory for local variables.
MOV EAX,0003h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,0004h                                     ; [VARIABLE -> id[EXPRESSION]] - Moves SIZEOF(ARRAY_ITEM) for array [GlobalIntArray] to EBX.
MUL EBX                                           ; [VARIABLE -> id[EXPRESSION]] - Multiplies EXPRESSION*SIZEOF(ARRAY_ITEM) to calculate array index byte offset for array [GlobalIntArray].
MOV EBX,EAX                                       ; [VARIABLE -> id[EXPRESSION]] - Moves array index byte offset EXPRESSION*SIZEOF(ARRAY_ITEM) for array [GlobalIntArray] to EBX.
MOV EAX,OFFSET GlobalIntArray                     ; [VARIABLE -> id[EXPRESSION]] - Moves base array address for global variable array [GlobalIntArray] to EAX.
ADD EAX,EBX                                       ; [VARIABLE -> id[EXPRESSION]] - Adds array index byt offset for array [GlobalIntArray] to EAX. Now EAX contains address of [GlobalIntArray[EXPRESSION]].
PUSH EAX                                          ; [VARIABLE -> id[EXPRESSION]] - Pushs address of variable [GlobalIntArray[EXPRESSION]] to STACK.
MOV EAX,0003h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets address of VARIABLE for operation ASSIGNMENT to EAX.
MOV [EAX],EBX                                     ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Moves value of EXPRESSION to VARIABLE.
MOV EAX,0004h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,0004h                                     ; [VARIABLE -> id[EXPRESSION]] - Moves SIZEOF(ARRAY_ITEM) for array [GlobalStringArray] to EBX.
MUL EBX                                           ; [VARIABLE -> id[EXPRESSION]] - Multiplies EXPRESSION*SIZEOF(ARRAY_ITEM) to calculate array index byte offset for array [GlobalStringArray].
MOV EBX,EAX                                       ; [VARIABLE -> id[EXPRESSION]] - Moves array index byte offset EXPRESSION*SIZEOF(ARRAY_ITEM) for array [GlobalStringArray] to EBX.
MOV EAX,OFFSET GlobalStringArray                  ; [VARIABLE -> id[EXPRESSION]] - Moves base array address for global variable array [GlobalStringArray] to EAX.
ADD EAX,EBX                                       ; [VARIABLE -> id[EXPRESSION]] - Adds array index byt offset for array [GlobalStringArray] to EAX. Now EAX contains address of [GlobalStringArray[EXPRESSION]].
PUSH EAX                                          ; [VARIABLE -> id[EXPRESSION]] - Pushs address of variable [GlobalStringArray[EXPRESSION]] to STACK.
PUSH OFFSET _STRING_6                             ; [FACTOR -> string_literal] - Pushs address of LITERAL to STACK.
POP EBX                                           ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets value of EXPRESSION for operation ASSIGNMENT to EBX.
POP EAX                                           ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets address of VARIABLE for operation ASSIGNMENT to EAX.
MOV [EAX],EBX                                     ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Moves value of EXPRESSION to VARIABLE.
MOV EAX,0003h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,0004h                                     ; [VARIABLE -> id[EXPRESSION]] - Moves SIZEOF(ARRAY_ITEM) for array [GlobalIntArray] to EBX.
MUL EBX                                           ; [VARIABLE -> id[EXPRESSION]] - Multiplies EXPRESSION*SIZEOF(ARRAY_ITEM) to calculate array index byte offset for array [GlobalIntArray].
MOV EBX,EAX                                       ; [VARIABLE -> id[EXPRESSION]] - Moves array index byte offset EXPRESSION*SIZEOF(ARRAY_ITEM) for array [GlobalIntArray] to EBX.
MOV EAX,OFFSET GlobalIntArray                     ; [VARIABLE -> id[EXPRESSION]] - Moves base array address for global variable array [GlobalIntArray] to EAX.
ADD EAX,EBX                                       ; [VARIABLE -> id[EXPRESSION]] - Adds array index byt offset for array [GlobalIntArray] to EAX. Now EAX contains address of [GlobalIntArray[EXPRESSION]].
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [GlobalIntArray] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [GlobalIntArray] to STACK.
CALL PrintLineInt                                 ; [CALL -> id(ARGS)] - Calls procedure [PrintLineInt()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineInt()] from STACK.
MOV EAX,0004h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,0004h                                     ; [VARIABLE -> id[EXPRESSION]] - Moves SIZEOF(ARRAY_ITEM) for array [GlobalStringArray] to EBX.
MUL EBX                                           ; [VARIABLE -> id[EXPRESSION]] - Multiplies EXPRESSION*SIZEOF(ARRAY_ITEM) to calculate array index byte offset for array [GlobalStringArray].
MOV EBX,EAX                                       ; [VARIABLE -> id[EXPRESSION]] - Moves array index byte offset EXPRESSION*SIZEOF(ARRAY_ITEM) for array [GlobalStringArray] to EBX.
MOV EAX,OFFSET GlobalStringArray                  ; [VARIABLE -> id[EXPRESSION]] - Moves base array address for global variable array [GlobalStringArray] to EAX.
ADD EAX,EBX                                       ; [VARIABLE -> id[EXPRESSION]] - Adds array index byt offset for array [GlobalStringArray] to EAX. Now EAX contains address of [GlobalStringArray[EXPRESSION]].
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [GlobalStringArray] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [GlobalStringArray] to STACK.
CALL PrintLineString                              ; [CALL -> id(ARGS)] - Calls procedure [PrintLineString()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineString()] from STACK.
MOV EAX,OFFSET GlobalInt                          ; Moves ADDRESS of [GlobalInt] to EAX.
PUSH EAX                                          ; [VARIABLE -> id] - Pushs address of variable [GlobalInt] to STACK.
MOV EAX,0007h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets address of VARIABLE for operation ASSIGNMENT to EAX.
MOV [EAX],EBX                                     ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Moves value of EXPRESSION to VARIABLE.
MOV EAX,OFFSET GlobalString                       ; Moves ADDRESS of [GlobalString] to EAX.
PUSH EAX                                          ; [VARIABLE -> id] - Pushs address of variable [GlobalString] to STACK.
PUSH OFFSET _STRING_7                             ; [FACTOR -> string_literal] - Pushs address of LITERAL to STACK.
POP EBX                                           ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets value of EXPRESSION for operation ASSIGNMENT to EBX.
POP EAX                                           ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets address of VARIABLE for operation ASSIGNMENT to EAX.
MOV [EAX],EBX                                     ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Moves value of EXPRESSION to VARIABLE.
MOV EAX,OFFSET GlobalInt                          ; Moves ADDRESS of [GlobalInt] to EAX.
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [GlobalInt] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [GlobalInt] to STACK.
CALL PrintLineInt                                 ; [CALL -> id(ARGS)] - Calls procedure [PrintLineInt()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineInt()] from STACK.
MOV EAX,OFFSET GlobalString                       ; Moves ADDRESS of [GlobalString] to EAX.
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [GlobalString] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [GlobalString] to STACK.
CALL PrintLineString                              ; [CALL -> id(ARGS)] - Calls procedure [PrintLineString()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineString()] from STACK.
MOV EAX,OFFSET GlobalIntInitialized               ; Moves ADDRESS of [GlobalIntInitialized] to EAX.
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [GlobalIntInitialized] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [GlobalIntInitialized] to STACK.
CALL PrintLineInt                                 ; [CALL -> id(ARGS)] - Calls procedure [PrintLineInt()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineInt()] from STACK.
MOV EAX,OFFSET GlobalStringInitialized            ; Moves ADDRESS of [GlobalStringInitialized] to EAX.
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [GlobalStringInitialized] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [GlobalStringInitialized] to STACK.
CALL PrintLineString                              ; [CALL -> id(ARGS)] - Calls procedure [PrintLineString()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineString()] from STACK.
Test1_EXIT:                                       ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Label to procedure [Test1()] exit code.
MOV ESP,EBP                                       ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Deallocates memory of local variables.
POP ECX                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of ECX.
POP EBX                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBX.
POP EBP                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBP.
RET                                               ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Exits procedure [Test1()].
Test1 ENDP                                        ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Ends procedure [Test1()].

Test2 PROC                                        ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Begins procedure [Test2()].
PUSH EBP                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBP to STACK.
PUSH EBX                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBX to STACK.
PUSH ECX                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of ECX to STACK.
MOV EBP,ESP                                       ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Moves ESP to EBP to store begin address of LOCAL VARIABLES.
SUB ESP,0038h                                     ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Allocates memory for local variables.
MOV EAX,0005h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,0004h                                     ; [VARIABLE -> id[EXPRESSION]] - Moves SIZEOF(ARRAY_ITEM) for array [LocalIntVariable] to EBX.
MUL EBX                                           ; [VARIABLE -> id[EXPRESSION]] - Multiplies EXPRESSION*SIZEOF(ARRAY_ITEM) to calculate array index byte offset for array [LocalIntVariable].
MOV EBX,EAX                                       ; [VARIABLE -> id[EXPRESSION]] - Moves array index byte offset EXPRESSION*SIZEOF(ARRAY_ITEM) for array [LocalIntVariable] to EBX.
MOV EAX,EBP                                       ; [VARIABLE -> id[EXPRESSION]] - Moves EBP for local variable array [LocalIntVariable] to EAX.
ADD EAX,-001Ch                                    ; [VARIABLE -> id[EXPRESSION]] - Adds local variable offset for local variable array [LocalIntVariable] to EAX. Now EAX contains base array address of array [LocalIntVariable].
ADD EAX,EBX                                       ; [VARIABLE -> id[EXPRESSION]] - Adds array index byt offset for array [LocalIntVariable] to EAX. Now EAX contains address of [LocalIntVariable[EXPRESSION]].
PUSH EAX                                          ; [VARIABLE -> id[EXPRESSION]] - Pushs address of variable [LocalIntVariable[EXPRESSION]] to STACK.
MOV EAX,000Fh                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets address of VARIABLE for operation ASSIGNMENT to EAX.
MOV [EAX],EBX                                     ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Moves value of EXPRESSION to VARIABLE.
MOV EAX,0006h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,0004h                                     ; [VARIABLE -> id[EXPRESSION]] - Moves SIZEOF(ARRAY_ITEM) for array [LocalIntVariable] to EBX.
MUL EBX                                           ; [VARIABLE -> id[EXPRESSION]] - Multiplies EXPRESSION*SIZEOF(ARRAY_ITEM) to calculate array index byte offset for array [LocalIntVariable].
MOV EBX,EAX                                       ; [VARIABLE -> id[EXPRESSION]] - Moves array index byte offset EXPRESSION*SIZEOF(ARRAY_ITEM) for array [LocalIntVariable] to EBX.
MOV EAX,EBP                                       ; [VARIABLE -> id[EXPRESSION]] - Moves EBP for local variable array [LocalIntVariable] to EAX.
ADD EAX,-001Ch                                    ; [VARIABLE -> id[EXPRESSION]] - Adds local variable offset for local variable array [LocalIntVariable] to EAX. Now EAX contains base array address of array [LocalIntVariable].
ADD EAX,EBX                                       ; [VARIABLE -> id[EXPRESSION]] - Adds array index byt offset for array [LocalIntVariable] to EAX. Now EAX contains address of [LocalIntVariable[EXPRESSION]].
PUSH EAX                                          ; [VARIABLE -> id[EXPRESSION]] - Pushs address of variable [LocalIntVariable[EXPRESSION]] to STACK.
MOV EAX,0010h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets address of VARIABLE for operation ASSIGNMENT to EAX.
MOV [EAX],EBX                                     ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Moves value of EXPRESSION to VARIABLE.
MOV EAX,0005h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,0004h                                     ; [VARIABLE -> id[EXPRESSION]] - Moves SIZEOF(ARRAY_ITEM) for array [LocalStringVariable] to EBX.
MUL EBX                                           ; [VARIABLE -> id[EXPRESSION]] - Multiplies EXPRESSION*SIZEOF(ARRAY_ITEM) to calculate array index byte offset for array [LocalStringVariable].
MOV EBX,EAX                                       ; [VARIABLE -> id[EXPRESSION]] - Moves array index byte offset EXPRESSION*SIZEOF(ARRAY_ITEM) for array [LocalStringVariable] to EBX.
MOV EAX,EBP                                       ; [VARIABLE -> id[EXPRESSION]] - Moves EBP for local variable array [LocalStringVariable] to EAX.
ADD EAX,-0038h                                    ; [VARIABLE -> id[EXPRESSION]] - Adds local variable offset for local variable array [LocalStringVariable] to EAX. Now EAX contains base array address of array [LocalStringVariable].
ADD EAX,EBX                                       ; [VARIABLE -> id[EXPRESSION]] - Adds array index byt offset for array [LocalStringVariable] to EAX. Now EAX contains address of [LocalStringVariable[EXPRESSION]].
PUSH EAX                                          ; [VARIABLE -> id[EXPRESSION]] - Pushs address of variable [LocalStringVariable[EXPRESSION]] to STACK.
PUSH OFFSET _STRING_8                             ; [FACTOR -> string_literal] - Pushs address of LITERAL to STACK.
POP EBX                                           ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets value of EXPRESSION for operation ASSIGNMENT to EBX.
POP EAX                                           ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets address of VARIABLE for operation ASSIGNMENT to EAX.
MOV [EAX],EBX                                     ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Moves value of EXPRESSION to VARIABLE.
MOV EAX,0006h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,0004h                                     ; [VARIABLE -> id[EXPRESSION]] - Moves SIZEOF(ARRAY_ITEM) for array [LocalStringVariable] to EBX.
MUL EBX                                           ; [VARIABLE -> id[EXPRESSION]] - Multiplies EXPRESSION*SIZEOF(ARRAY_ITEM) to calculate array index byte offset for array [LocalStringVariable].
MOV EBX,EAX                                       ; [VARIABLE -> id[EXPRESSION]] - Moves array index byte offset EXPRESSION*SIZEOF(ARRAY_ITEM) for array [LocalStringVariable] to EBX.
MOV EAX,EBP                                       ; [VARIABLE -> id[EXPRESSION]] - Moves EBP for local variable array [LocalStringVariable] to EAX.
ADD EAX,-0038h                                    ; [VARIABLE -> id[EXPRESSION]] - Adds local variable offset for local variable array [LocalStringVariable] to EAX. Now EAX contains base array address of array [LocalStringVariable].
ADD EAX,EBX                                       ; [VARIABLE -> id[EXPRESSION]] - Adds array index byt offset for array [LocalStringVariable] to EAX. Now EAX contains address of [LocalStringVariable[EXPRESSION]].
PUSH EAX                                          ; [VARIABLE -> id[EXPRESSION]] - Pushs address of variable [LocalStringVariable[EXPRESSION]] to STACK.
PUSH OFFSET _STRING_7                             ; [FACTOR -> string_literal] - Pushs address of LITERAL to STACK.
POP EBX                                           ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets value of EXPRESSION for operation ASSIGNMENT to EBX.
POP EAX                                           ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets address of VARIABLE for operation ASSIGNMENT to EAX.
MOV [EAX],EBX                                     ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Moves value of EXPRESSION to VARIABLE.
PUSH OFFSET _STRING_9                             ; [FACTOR -> string_literal] - Pushs address of LITERAL to STACK.
PUSH OFFSET _STRING_10                            ; [FACTOR -> string_literal] - Pushs address of LITERAL to STACK.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [LocalIntVariable] to EAX.
ADD EAX,-001Ch                                    ; [VARIABLE -> id] - Adds local variable offset for local variable array [LocalIntVariable] to EAX. Now EAX contains base array address of array [LocalIntVariable].
PUSH EAX                                          ; [VARIABLE -> id] - Pushs address of variable [LocalIntVariable] to STACK.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [LocalStringVariable] to EAX.
ADD EAX,-0038h                                    ; [VARIABLE -> id] - Adds local variable offset for local variable array [LocalStringVariable] to EAX. Now EAX contains base array address of array [LocalStringVariable].
PUSH EAX                                          ; [VARIABLE -> id] - Pushs address of variable [LocalStringVariable] to STACK.
CALL Print5And6ItemsOfArray                       ; [CALL -> id(ARGS)] - Calls procedure [Print5And6ItemsOfArray()].
ADD ESP,0010h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [Print5And6ItemsOfArray()] from STACK.
Test2_EXIT:                                       ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Label to procedure [Test2()] exit code.
MOV ESP,EBP                                       ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Deallocates memory of local variables.
POP ECX                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of ECX.
POP EBX                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBX.
POP EBP                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBP.
RET                                               ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Exits procedure [Test2()].
Test2 ENDP                                        ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Ends procedure [Test2()].

Test3 PROC                                        ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Begins procedure [Test3()].
PUSH EBP                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBP to STACK.
PUSH EBX                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBX to STACK.
PUSH ECX                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of ECX to STACK.
MOV EBP,ESP                                       ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Moves ESP to EBP to store begin address of LOCAL VARIABLES.
SUB ESP,0078h                                     ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Allocates memory for local variables.
MOV EAX,0009h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,0004h                                     ; [VARIABLE -> id[EXPRESSION]] - Moves SIZEOF(ARRAY_ITEM) for array [Array1] to EBX.
MUL EBX                                           ; [VARIABLE -> id[EXPRESSION]] - Multiplies EXPRESSION*SIZEOF(ARRAY_ITEM) to calculate array index byte offset for array [Array1].
MOV EBX,EAX                                       ; [VARIABLE -> id[EXPRESSION]] - Moves array index byte offset EXPRESSION*SIZEOF(ARRAY_ITEM) for array [Array1] to EBX.
MOV EAX,EBP                                       ; [VARIABLE -> id[EXPRESSION]] - Moves EBP for local variable array [Array1] to EAX.
ADD EAX,-0028h                                    ; [VARIABLE -> id[EXPRESSION]] - Adds local variable offset for local variable array [Array1] to EAX. Now EAX contains base array address of array [Array1].
ADD EAX,EBX                                       ; [VARIABLE -> id[EXPRESSION]] - Adds array index byt offset for array [Array1] to EAX. Now EAX contains address of [Array1[EXPRESSION]].
PUSH EAX                                          ; [VARIABLE -> id[EXPRESSION]] - Pushs address of variable [Array1[EXPRESSION]] to STACK.
MOV EAX,0001h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets address of VARIABLE for operation ASSIGNMENT to EAX.
MOV [EAX],EBX                                     ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Moves value of EXPRESSION to VARIABLE.
MOV EAX,0009h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,0004h                                     ; [VARIABLE -> id[EXPRESSION]] - Moves SIZEOF(ARRAY_ITEM) for array [Array1] to EBX.
MUL EBX                                           ; [VARIABLE -> id[EXPRESSION]] - Multiplies EXPRESSION*SIZEOF(ARRAY_ITEM) to calculate array index byte offset for array [Array1].
MOV EBX,EAX                                       ; [VARIABLE -> id[EXPRESSION]] - Moves array index byte offset EXPRESSION*SIZEOF(ARRAY_ITEM) for array [Array1] to EBX.
MOV EAX,EBP                                       ; [VARIABLE -> id[EXPRESSION]] - Moves EBP for local variable array [Array1] to EAX.
ADD EAX,-0028h                                    ; [VARIABLE -> id[EXPRESSION]] - Adds local variable offset for local variable array [Array1] to EAX. Now EAX contains base array address of array [Array1].
ADD EAX,EBX                                       ; [VARIABLE -> id[EXPRESSION]] - Adds array index byt offset for array [Array1] to EAX. Now EAX contains address of [Array1[EXPRESSION]].
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Array1] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [Array1] to STACK.
CALL PrintLineInt                                 ; [CALL -> id(ARGS)] - Calls procedure [PrintLineInt()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineInt()] from STACK.
MOV EAX,0009h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,0004h                                     ; [VARIABLE -> id[EXPRESSION]] - Moves SIZEOF(ARRAY_ITEM) for array [Array1] to EBX.
MUL EBX                                           ; [VARIABLE -> id[EXPRESSION]] - Multiplies EXPRESSION*SIZEOF(ARRAY_ITEM) to calculate array index byte offset for array [Array1].
MOV EBX,EAX                                       ; [VARIABLE -> id[EXPRESSION]] - Moves array index byte offset EXPRESSION*SIZEOF(ARRAY_ITEM) for array [Array1] to EBX.
MOV EAX,EBP                                       ; [VARIABLE -> id[EXPRESSION]] - Moves EBP for local variable array [Array1] to EAX.
ADD EAX,-0028h                                    ; [VARIABLE -> id[EXPRESSION]] - Adds local variable offset for local variable array [Array1] to EAX. Now EAX contains base array address of array [Array1].
ADD EAX,EBX                                       ; [VARIABLE -> id[EXPRESSION]] - Adds array index byt offset for array [Array1] to EAX. Now EAX contains address of [Array1[EXPRESSION]].
PUSH EAX                                          ; [VARIABLE -> id[EXPRESSION]] - Pushs address of variable [Array1[EXPRESSION]] to STACK.
MOV EAX,0002h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets address of VARIABLE for operation ASSIGNMENT to EAX.
MOV [EAX],EBX                                     ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Moves value of EXPRESSION to VARIABLE.
MOV EAX,0009h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,0004h                                     ; [VARIABLE -> id[EXPRESSION]] - Moves SIZEOF(ARRAY_ITEM) for array [Array2] to EBX.
MUL EBX                                           ; [VARIABLE -> id[EXPRESSION]] - Multiplies EXPRESSION*SIZEOF(ARRAY_ITEM) to calculate array index byte offset for array [Array2].
MOV EBX,EAX                                       ; [VARIABLE -> id[EXPRESSION]] - Moves array index byte offset EXPRESSION*SIZEOF(ARRAY_ITEM) for array [Array2] to EBX.
MOV EAX,EBP                                       ; [VARIABLE -> id[EXPRESSION]] - Moves EBP for local variable array [Array2] to EAX.
ADD EAX,-0050h                                    ; [VARIABLE -> id[EXPRESSION]] - Adds local variable offset for local variable array [Array2] to EAX. Now EAX contains base array address of array [Array2].
ADD EAX,EBX                                       ; [VARIABLE -> id[EXPRESSION]] - Adds array index byt offset for array [Array2] to EAX. Now EAX contains address of [Array2[EXPRESSION]].
PUSH EAX                                          ; [VARIABLE -> id[EXPRESSION]] - Pushs address of variable [Array2[EXPRESSION]] to STACK.
MOV EAX,000Ch                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets address of VARIABLE for operation ASSIGNMENT to EAX.
MOV [EAX],EBX                                     ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Moves value of EXPRESSION to VARIABLE.
MOV EAX,0009h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,0004h                                     ; [VARIABLE -> id[EXPRESSION]] - Moves SIZEOF(ARRAY_ITEM) for array [Array1] to EBX.
MUL EBX                                           ; [VARIABLE -> id[EXPRESSION]] - Multiplies EXPRESSION*SIZEOF(ARRAY_ITEM) to calculate array index byte offset for array [Array1].
MOV EBX,EAX                                       ; [VARIABLE -> id[EXPRESSION]] - Moves array index byte offset EXPRESSION*SIZEOF(ARRAY_ITEM) for array [Array1] to EBX.
MOV EAX,EBP                                       ; [VARIABLE -> id[EXPRESSION]] - Moves EBP for local variable array [Array1] to EAX.
ADD EAX,-0028h                                    ; [VARIABLE -> id[EXPRESSION]] - Adds local variable offset for local variable array [Array1] to EAX. Now EAX contains base array address of array [Array1].
ADD EAX,EBX                                       ; [VARIABLE -> id[EXPRESSION]] - Adds array index byt offset for array [Array1] to EAX. Now EAX contains address of [Array1[EXPRESSION]].
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Array1] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [Array1] to STACK.
CALL PrintLineInt                                 ; [CALL -> id(ARGS)] - Calls procedure [PrintLineInt()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineInt()] from STACK.
MOV EAX,0009h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,0004h                                     ; [VARIABLE -> id[EXPRESSION]] - Moves SIZEOF(ARRAY_ITEM) for array [Array2] to EBX.
MUL EBX                                           ; [VARIABLE -> id[EXPRESSION]] - Multiplies EXPRESSION*SIZEOF(ARRAY_ITEM) to calculate array index byte offset for array [Array2].
MOV EBX,EAX                                       ; [VARIABLE -> id[EXPRESSION]] - Moves array index byte offset EXPRESSION*SIZEOF(ARRAY_ITEM) for array [Array2] to EBX.
MOV EAX,EBP                                       ; [VARIABLE -> id[EXPRESSION]] - Moves EBP for local variable array [Array2] to EAX.
ADD EAX,-0050h                                    ; [VARIABLE -> id[EXPRESSION]] - Adds local variable offset for local variable array [Array2] to EAX. Now EAX contains base array address of array [Array2].
ADD EAX,EBX                                       ; [VARIABLE -> id[EXPRESSION]] - Adds array index byt offset for array [Array2] to EAX. Now EAX contains address of [Array2[EXPRESSION]].
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Array2] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [Array2] to STACK.
CALL PrintLineInt                                 ; [CALL -> id(ARGS)] - Calls procedure [PrintLineInt()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineInt()] from STACK.
MOV EAX,0009h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,0004h                                     ; [VARIABLE -> id[EXPRESSION]] - Moves SIZEOF(ARRAY_ITEM) for array [Array1] to EBX.
MUL EBX                                           ; [VARIABLE -> id[EXPRESSION]] - Multiplies EXPRESSION*SIZEOF(ARRAY_ITEM) to calculate array index byte offset for array [Array1].
MOV EBX,EAX                                       ; [VARIABLE -> id[EXPRESSION]] - Moves array index byte offset EXPRESSION*SIZEOF(ARRAY_ITEM) for array [Array1] to EBX.
MOV EAX,EBP                                       ; [VARIABLE -> id[EXPRESSION]] - Moves EBP for local variable array [Array1] to EAX.
ADD EAX,-0028h                                    ; [VARIABLE -> id[EXPRESSION]] - Adds local variable offset for local variable array [Array1] to EAX. Now EAX contains base array address of array [Array1].
ADD EAX,EBX                                       ; [VARIABLE -> id[EXPRESSION]] - Adds array index byt offset for array [Array1] to EAX. Now EAX contains address of [Array1[EXPRESSION]].
PUSH EAX                                          ; [VARIABLE -> id[EXPRESSION]] - Pushs address of variable [Array1[EXPRESSION]] to STACK.
MOV EAX,0003h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets address of VARIABLE for operation ASSIGNMENT to EAX.
MOV [EAX],EBX                                     ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Moves value of EXPRESSION to VARIABLE.
MOV EAX,0009h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,0004h                                     ; [VARIABLE -> id[EXPRESSION]] - Moves SIZEOF(ARRAY_ITEM) for array [Array2] to EBX.
MUL EBX                                           ; [VARIABLE -> id[EXPRESSION]] - Multiplies EXPRESSION*SIZEOF(ARRAY_ITEM) to calculate array index byte offset for array [Array2].
MOV EBX,EAX                                       ; [VARIABLE -> id[EXPRESSION]] - Moves array index byte offset EXPRESSION*SIZEOF(ARRAY_ITEM) for array [Array2] to EBX.
MOV EAX,EBP                                       ; [VARIABLE -> id[EXPRESSION]] - Moves EBP for local variable array [Array2] to EAX.
ADD EAX,-0050h                                    ; [VARIABLE -> id[EXPRESSION]] - Adds local variable offset for local variable array [Array2] to EAX. Now EAX contains base array address of array [Array2].
ADD EAX,EBX                                       ; [VARIABLE -> id[EXPRESSION]] - Adds array index byt offset for array [Array2] to EAX. Now EAX contains address of [Array2[EXPRESSION]].
PUSH EAX                                          ; [VARIABLE -> id[EXPRESSION]] - Pushs address of variable [Array2[EXPRESSION]] to STACK.
MOV EAX,000Dh                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets address of VARIABLE for operation ASSIGNMENT to EAX.
MOV [EAX],EBX                                     ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Moves value of EXPRESSION to VARIABLE.
MOV EAX,0009h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,0004h                                     ; [VARIABLE -> id[EXPRESSION]] - Moves SIZEOF(ARRAY_ITEM) for array [Array3] to EBX.
MUL EBX                                           ; [VARIABLE -> id[EXPRESSION]] - Multiplies EXPRESSION*SIZEOF(ARRAY_ITEM) to calculate array index byte offset for array [Array3].
MOV EBX,EAX                                       ; [VARIABLE -> id[EXPRESSION]] - Moves array index byte offset EXPRESSION*SIZEOF(ARRAY_ITEM) for array [Array3] to EBX.
MOV EAX,EBP                                       ; [VARIABLE -> id[EXPRESSION]] - Moves EBP for local variable array [Array3] to EAX.
ADD EAX,-0078h                                    ; [VARIABLE -> id[EXPRESSION]] - Adds local variable offset for local variable array [Array3] to EAX. Now EAX contains base array address of array [Array3].
ADD EAX,EBX                                       ; [VARIABLE -> id[EXPRESSION]] - Adds array index byt offset for array [Array3] to EAX. Now EAX contains address of [Array3[EXPRESSION]].
PUSH EAX                                          ; [VARIABLE -> id[EXPRESSION]] - Pushs address of variable [Array3[EXPRESSION]] to STACK.
MOV EAX,0017h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets address of VARIABLE for operation ASSIGNMENT to EAX.
MOV [EAX],EBX                                     ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Moves value of EXPRESSION to VARIABLE.
MOV EAX,0009h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,0004h                                     ; [VARIABLE -> id[EXPRESSION]] - Moves SIZEOF(ARRAY_ITEM) for array [Array1] to EBX.
MUL EBX                                           ; [VARIABLE -> id[EXPRESSION]] - Multiplies EXPRESSION*SIZEOF(ARRAY_ITEM) to calculate array index byte offset for array [Array1].
MOV EBX,EAX                                       ; [VARIABLE -> id[EXPRESSION]] - Moves array index byte offset EXPRESSION*SIZEOF(ARRAY_ITEM) for array [Array1] to EBX.
MOV EAX,EBP                                       ; [VARIABLE -> id[EXPRESSION]] - Moves EBP for local variable array [Array1] to EAX.
ADD EAX,-0028h                                    ; [VARIABLE -> id[EXPRESSION]] - Adds local variable offset for local variable array [Array1] to EAX. Now EAX contains base array address of array [Array1].
ADD EAX,EBX                                       ; [VARIABLE -> id[EXPRESSION]] - Adds array index byt offset for array [Array1] to EAX. Now EAX contains address of [Array1[EXPRESSION]].
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Array1] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [Array1] to STACK.
CALL PrintLineInt                                 ; [CALL -> id(ARGS)] - Calls procedure [PrintLineInt()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineInt()] from STACK.
MOV EAX,0009h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,0004h                                     ; [VARIABLE -> id[EXPRESSION]] - Moves SIZEOF(ARRAY_ITEM) for array [Array2] to EBX.
MUL EBX                                           ; [VARIABLE -> id[EXPRESSION]] - Multiplies EXPRESSION*SIZEOF(ARRAY_ITEM) to calculate array index byte offset for array [Array2].
MOV EBX,EAX                                       ; [VARIABLE -> id[EXPRESSION]] - Moves array index byte offset EXPRESSION*SIZEOF(ARRAY_ITEM) for array [Array2] to EBX.
MOV EAX,EBP                                       ; [VARIABLE -> id[EXPRESSION]] - Moves EBP for local variable array [Array2] to EAX.
ADD EAX,-0050h                                    ; [VARIABLE -> id[EXPRESSION]] - Adds local variable offset for local variable array [Array2] to EAX. Now EAX contains base array address of array [Array2].
ADD EAX,EBX                                       ; [VARIABLE -> id[EXPRESSION]] - Adds array index byt offset for array [Array2] to EAX. Now EAX contains address of [Array2[EXPRESSION]].
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Array2] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [Array2] to STACK.
CALL PrintLineInt                                 ; [CALL -> id(ARGS)] - Calls procedure [PrintLineInt()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineInt()] from STACK.
MOV EAX,0009h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,0004h                                     ; [VARIABLE -> id[EXPRESSION]] - Moves SIZEOF(ARRAY_ITEM) for array [Array3] to EBX.
MUL EBX                                           ; [VARIABLE -> id[EXPRESSION]] - Multiplies EXPRESSION*SIZEOF(ARRAY_ITEM) to calculate array index byte offset for array [Array3].
MOV EBX,EAX                                       ; [VARIABLE -> id[EXPRESSION]] - Moves array index byte offset EXPRESSION*SIZEOF(ARRAY_ITEM) for array [Array3] to EBX.
MOV EAX,EBP                                       ; [VARIABLE -> id[EXPRESSION]] - Moves EBP for local variable array [Array3] to EAX.
ADD EAX,-0078h                                    ; [VARIABLE -> id[EXPRESSION]] - Adds local variable offset for local variable array [Array3] to EAX. Now EAX contains base array address of array [Array3].
ADD EAX,EBX                                       ; [VARIABLE -> id[EXPRESSION]] - Adds array index byt offset for array [Array3] to EAX. Now EAX contains address of [Array3[EXPRESSION]].
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Array3] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [Array3] to STACK.
CALL PrintLineInt                                 ; [CALL -> id(ARGS)] - Calls procedure [PrintLineInt()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineInt()] from STACK.
MOV EAX,0000h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,0004h                                     ; [VARIABLE -> id[EXPRESSION]] - Moves SIZEOF(ARRAY_ITEM) for array [Array1] to EBX.
MUL EBX                                           ; [VARIABLE -> id[EXPRESSION]] - Multiplies EXPRESSION*SIZEOF(ARRAY_ITEM) to calculate array index byte offset for array [Array1].
MOV EBX,EAX                                       ; [VARIABLE -> id[EXPRESSION]] - Moves array index byte offset EXPRESSION*SIZEOF(ARRAY_ITEM) for array [Array1] to EBX.
MOV EAX,EBP                                       ; [VARIABLE -> id[EXPRESSION]] - Moves EBP for local variable array [Array1] to EAX.
ADD EAX,-0028h                                    ; [VARIABLE -> id[EXPRESSION]] - Adds local variable offset for local variable array [Array1] to EAX. Now EAX contains base array address of array [Array1].
ADD EAX,EBX                                       ; [VARIABLE -> id[EXPRESSION]] - Adds array index byt offset for array [Array1] to EAX. Now EAX contains address of [Array1[EXPRESSION]].
PUSH EAX                                          ; [VARIABLE -> id[EXPRESSION]] - Pushs address of variable [Array1[EXPRESSION]] to STACK.
MOV EAX,0000h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets address of VARIABLE for operation ASSIGNMENT to EAX.
MOV [EAX],EBX                                     ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Moves value of EXPRESSION to VARIABLE.
MOV EAX,0000h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,0004h                                     ; [VARIABLE -> id[EXPRESSION]] - Moves SIZEOF(ARRAY_ITEM) for array [Array2] to EBX.
MUL EBX                                           ; [VARIABLE -> id[EXPRESSION]] - Multiplies EXPRESSION*SIZEOF(ARRAY_ITEM) to calculate array index byte offset for array [Array2].
MOV EBX,EAX                                       ; [VARIABLE -> id[EXPRESSION]] - Moves array index byte offset EXPRESSION*SIZEOF(ARRAY_ITEM) for array [Array2] to EBX.
MOV EAX,EBP                                       ; [VARIABLE -> id[EXPRESSION]] - Moves EBP for local variable array [Array2] to EAX.
ADD EAX,-0050h                                    ; [VARIABLE -> id[EXPRESSION]] - Adds local variable offset for local variable array [Array2] to EAX. Now EAX contains base array address of array [Array2].
ADD EAX,EBX                                       ; [VARIABLE -> id[EXPRESSION]] - Adds array index byt offset for array [Array2] to EAX. Now EAX contains address of [Array2[EXPRESSION]].
PUSH EAX                                          ; [VARIABLE -> id[EXPRESSION]] - Pushs address of variable [Array2[EXPRESSION]] to STACK.
MOV EAX,000Ah                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets address of VARIABLE for operation ASSIGNMENT to EAX.
MOV [EAX],EBX                                     ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Moves value of EXPRESSION to VARIABLE.
MOV EAX,0000h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,0004h                                     ; [VARIABLE -> id[EXPRESSION]] - Moves SIZEOF(ARRAY_ITEM) for array [Array3] to EBX.
MUL EBX                                           ; [VARIABLE -> id[EXPRESSION]] - Multiplies EXPRESSION*SIZEOF(ARRAY_ITEM) to calculate array index byte offset for array [Array3].
MOV EBX,EAX                                       ; [VARIABLE -> id[EXPRESSION]] - Moves array index byte offset EXPRESSION*SIZEOF(ARRAY_ITEM) for array [Array3] to EBX.
MOV EAX,EBP                                       ; [VARIABLE -> id[EXPRESSION]] - Moves EBP for local variable array [Array3] to EAX.
ADD EAX,-0078h                                    ; [VARIABLE -> id[EXPRESSION]] - Adds local variable offset for local variable array [Array3] to EAX. Now EAX contains base array address of array [Array3].
ADD EAX,EBX                                       ; [VARIABLE -> id[EXPRESSION]] - Adds array index byt offset for array [Array3] to EAX. Now EAX contains address of [Array3[EXPRESSION]].
PUSH EAX                                          ; [VARIABLE -> id[EXPRESSION]] - Pushs address of variable [Array3[EXPRESSION]] to STACK.
MOV EAX,0014h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets address of VARIABLE for operation ASSIGNMENT to EAX.
MOV [EAX],EBX                                     ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Moves value of EXPRESSION to VARIABLE.
MOV EAX,0000h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,0004h                                     ; [VARIABLE -> id[EXPRESSION]] - Moves SIZEOF(ARRAY_ITEM) for array [Array1] to EBX.
MUL EBX                                           ; [VARIABLE -> id[EXPRESSION]] - Multiplies EXPRESSION*SIZEOF(ARRAY_ITEM) to calculate array index byte offset for array [Array1].
MOV EBX,EAX                                       ; [VARIABLE -> id[EXPRESSION]] - Moves array index byte offset EXPRESSION*SIZEOF(ARRAY_ITEM) for array [Array1] to EBX.
MOV EAX,EBP                                       ; [VARIABLE -> id[EXPRESSION]] - Moves EBP for local variable array [Array1] to EAX.
ADD EAX,-0028h                                    ; [VARIABLE -> id[EXPRESSION]] - Adds local variable offset for local variable array [Array1] to EAX. Now EAX contains base array address of array [Array1].
ADD EAX,EBX                                       ; [VARIABLE -> id[EXPRESSION]] - Adds array index byt offset for array [Array1] to EAX. Now EAX contains address of [Array1[EXPRESSION]].
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Array1] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [Array1] to STACK.
CALL PrintLineInt                                 ; [CALL -> id(ARGS)] - Calls procedure [PrintLineInt()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineInt()] from STACK.
MOV EAX,0000h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,0004h                                     ; [VARIABLE -> id[EXPRESSION]] - Moves SIZEOF(ARRAY_ITEM) for array [Array2] to EBX.
MUL EBX                                           ; [VARIABLE -> id[EXPRESSION]] - Multiplies EXPRESSION*SIZEOF(ARRAY_ITEM) to calculate array index byte offset for array [Array2].
MOV EBX,EAX                                       ; [VARIABLE -> id[EXPRESSION]] - Moves array index byte offset EXPRESSION*SIZEOF(ARRAY_ITEM) for array [Array2] to EBX.
MOV EAX,EBP                                       ; [VARIABLE -> id[EXPRESSION]] - Moves EBP for local variable array [Array2] to EAX.
ADD EAX,-0050h                                    ; [VARIABLE -> id[EXPRESSION]] - Adds local variable offset for local variable array [Array2] to EAX. Now EAX contains base array address of array [Array2].
ADD EAX,EBX                                       ; [VARIABLE -> id[EXPRESSION]] - Adds array index byt offset for array [Array2] to EAX. Now EAX contains address of [Array2[EXPRESSION]].
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Array2] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [Array2] to STACK.
CALL PrintLineInt                                 ; [CALL -> id(ARGS)] - Calls procedure [PrintLineInt()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineInt()] from STACK.
MOV EAX,0000h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,0004h                                     ; [VARIABLE -> id[EXPRESSION]] - Moves SIZEOF(ARRAY_ITEM) for array [Array3] to EBX.
MUL EBX                                           ; [VARIABLE -> id[EXPRESSION]] - Multiplies EXPRESSION*SIZEOF(ARRAY_ITEM) to calculate array index byte offset for array [Array3].
MOV EBX,EAX                                       ; [VARIABLE -> id[EXPRESSION]] - Moves array index byte offset EXPRESSION*SIZEOF(ARRAY_ITEM) for array [Array3] to EBX.
MOV EAX,EBP                                       ; [VARIABLE -> id[EXPRESSION]] - Moves EBP for local variable array [Array3] to EAX.
ADD EAX,-0078h                                    ; [VARIABLE -> id[EXPRESSION]] - Adds local variable offset for local variable array [Array3] to EAX. Now EAX contains base array address of array [Array3].
ADD EAX,EBX                                       ; [VARIABLE -> id[EXPRESSION]] - Adds array index byt offset for array [Array3] to EAX. Now EAX contains address of [Array3[EXPRESSION]].
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Array3] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [Array3] to STACK.
CALL PrintLineInt                                 ; [CALL -> id(ARGS)] - Calls procedure [PrintLineInt()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineInt()] from STACK.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Array1] to EAX.
ADD EAX,-0028h                                    ; [VARIABLE -> id] - Adds local variable offset for local variable array [Array1] to EAX. Now EAX contains base array address of array [Array1].
PUSH EAX                                          ; [VARIABLE -> id] - Pushs address of variable [Array1] to STACK.
MOV EAX,0009h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
PUSH EAX                                          ; [FACTOR -> num] - Pushs INT constant to STACK.
CALL PrintItemOfArray                             ; [CALL -> id(ARGS)] - Calls procedure [PrintItemOfArray()].
ADD ESP,0008h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintItemOfArray()] from STACK.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Array1] to EAX.
ADD EAX,-0028h                                    ; [VARIABLE -> id] - Adds local variable offset for local variable array [Array1] to EAX. Now EAX contains base array address of array [Array1].
PUSH EAX                                          ; [VARIABLE -> id] - Pushs address of variable [Array1] to STACK.
MOV EAX,0000h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
PUSH EAX                                          ; [FACTOR -> num] - Pushs INT constant to STACK.
CALL PrintItemOfArray                             ; [CALL -> id(ARGS)] - Calls procedure [PrintItemOfArray()].
ADD ESP,0008h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintItemOfArray()] from STACK.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Array2] to EAX.
ADD EAX,-0050h                                    ; [VARIABLE -> id] - Adds local variable offset for local variable array [Array2] to EAX. Now EAX contains base array address of array [Array2].
PUSH EAX                                          ; [VARIABLE -> id] - Pushs address of variable [Array2] to STACK.
MOV EAX,0009h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
PUSH EAX                                          ; [FACTOR -> num] - Pushs INT constant to STACK.
CALL PrintItemOfArray                             ; [CALL -> id(ARGS)] - Calls procedure [PrintItemOfArray()].
ADD ESP,0008h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintItemOfArray()] from STACK.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Array2] to EAX.
ADD EAX,-0050h                                    ; [VARIABLE -> id] - Adds local variable offset for local variable array [Array2] to EAX. Now EAX contains base array address of array [Array2].
PUSH EAX                                          ; [VARIABLE -> id] - Pushs address of variable [Array2] to STACK.
MOV EAX,0000h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
PUSH EAX                                          ; [FACTOR -> num] - Pushs INT constant to STACK.
CALL PrintItemOfArray                             ; [CALL -> id(ARGS)] - Calls procedure [PrintItemOfArray()].
ADD ESP,0008h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintItemOfArray()] from STACK.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Array3] to EAX.
ADD EAX,-0078h                                    ; [VARIABLE -> id] - Adds local variable offset for local variable array [Array3] to EAX. Now EAX contains base array address of array [Array3].
PUSH EAX                                          ; [VARIABLE -> id] - Pushs address of variable [Array3] to STACK.
MOV EAX,0009h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
PUSH EAX                                          ; [FACTOR -> num] - Pushs INT constant to STACK.
CALL PrintItemOfArray                             ; [CALL -> id(ARGS)] - Calls procedure [PrintItemOfArray()].
ADD ESP,0008h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintItemOfArray()] from STACK.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Array3] to EAX.
ADD EAX,-0078h                                    ; [VARIABLE -> id] - Adds local variable offset for local variable array [Array3] to EAX. Now EAX contains base array address of array [Array3].
PUSH EAX                                          ; [VARIABLE -> id] - Pushs address of variable [Array3] to STACK.
MOV EAX,0000h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
PUSH EAX                                          ; [FACTOR -> num] - Pushs INT constant to STACK.
CALL PrintItemOfArray                             ; [CALL -> id(ARGS)] - Calls procedure [PrintItemOfArray()].
ADD ESP,0008h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintItemOfArray()] from STACK.
MOV EAX,0009h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,0004h                                     ; [VARIABLE -> id[EXPRESSION]] - Moves SIZEOF(ARRAY_ITEM) for array [Array1] to EBX.
MUL EBX                                           ; [VARIABLE -> id[EXPRESSION]] - Multiplies EXPRESSION*SIZEOF(ARRAY_ITEM) to calculate array index byte offset for array [Array1].
MOV EBX,EAX                                       ; [VARIABLE -> id[EXPRESSION]] - Moves array index byte offset EXPRESSION*SIZEOF(ARRAY_ITEM) for array [Array1] to EBX.
MOV EAX,EBP                                       ; [VARIABLE -> id[EXPRESSION]] - Moves EBP for local variable array [Array1] to EAX.
ADD EAX,-0028h                                    ; [VARIABLE -> id[EXPRESSION]] - Adds local variable offset for local variable array [Array1] to EAX. Now EAX contains base array address of array [Array1].
ADD EAX,EBX                                       ; [VARIABLE -> id[EXPRESSION]] - Adds array index byt offset for array [Array1] to EAX. Now EAX contains address of [Array1[EXPRESSION]].
PUSH EAX                                          ; [VARIABLE -> id[EXPRESSION]] - Pushs address of variable [Array1[EXPRESSION]] to STACK.
MOV EAX,0004h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets address of VARIABLE for operation ASSIGNMENT to EAX.
MOV [EAX],EBX                                     ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Moves value of EXPRESSION to VARIABLE.
MOV EAX,0009h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,0004h                                     ; [VARIABLE -> id[EXPRESSION]] - Moves SIZEOF(ARRAY_ITEM) for array [Array4] to EBX.
MUL EBX                                           ; [VARIABLE -> id[EXPRESSION]] - Multiplies EXPRESSION*SIZEOF(ARRAY_ITEM) to calculate array index byte offset for array [Array4].
MOV EBX,EAX                                       ; [VARIABLE -> id[EXPRESSION]] - Moves array index byte offset EXPRESSION*SIZEOF(ARRAY_ITEM) for array [Array4] to EBX.
MOV EAX,EBP                                       ; [VARIABLE -> id[EXPRESSION]] - Moves EBP for local variable array [Array4] to EAX.
ADD EAX,-0050h                                    ; [VARIABLE -> id[EXPRESSION]] - Adds local variable offset for local variable array [Array4] to EAX. Now EAX contains base array address of array [Array4].
ADD EAX,EBX                                       ; [VARIABLE -> id[EXPRESSION]] - Adds array index byt offset for array [Array4] to EAX. Now EAX contains address of [Array4[EXPRESSION]].
PUSH EAX                                          ; [VARIABLE -> id[EXPRESSION]] - Pushs address of variable [Array4[EXPRESSION]] to STACK.
MOV EAX,000Eh                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets address of VARIABLE for operation ASSIGNMENT to EAX.
MOV [EAX],EBX                                     ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Moves value of EXPRESSION to VARIABLE.
MOV EAX,0009h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,0004h                                     ; [VARIABLE -> id[EXPRESSION]] - Moves SIZEOF(ARRAY_ITEM) for array [Array1] to EBX.
MUL EBX                                           ; [VARIABLE -> id[EXPRESSION]] - Multiplies EXPRESSION*SIZEOF(ARRAY_ITEM) to calculate array index byte offset for array [Array1].
MOV EBX,EAX                                       ; [VARIABLE -> id[EXPRESSION]] - Moves array index byte offset EXPRESSION*SIZEOF(ARRAY_ITEM) for array [Array1] to EBX.
MOV EAX,EBP                                       ; [VARIABLE -> id[EXPRESSION]] - Moves EBP for local variable array [Array1] to EAX.
ADD EAX,-0028h                                    ; [VARIABLE -> id[EXPRESSION]] - Adds local variable offset for local variable array [Array1] to EAX. Now EAX contains base array address of array [Array1].
ADD EAX,EBX                                       ; [VARIABLE -> id[EXPRESSION]] - Adds array index byt offset for array [Array1] to EAX. Now EAX contains address of [Array1[EXPRESSION]].
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Array1] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [Array1] to STACK.
CALL PrintLineInt                                 ; [CALL -> id(ARGS)] - Calls procedure [PrintLineInt()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineInt()] from STACK.
MOV EAX,0009h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,0004h                                     ; [VARIABLE -> id[EXPRESSION]] - Moves SIZEOF(ARRAY_ITEM) for array [Array4] to EBX.
MUL EBX                                           ; [VARIABLE -> id[EXPRESSION]] - Multiplies EXPRESSION*SIZEOF(ARRAY_ITEM) to calculate array index byte offset for array [Array4].
MOV EBX,EAX                                       ; [VARIABLE -> id[EXPRESSION]] - Moves array index byte offset EXPRESSION*SIZEOF(ARRAY_ITEM) for array [Array4] to EBX.
MOV EAX,EBP                                       ; [VARIABLE -> id[EXPRESSION]] - Moves EBP for local variable array [Array4] to EAX.
ADD EAX,-0050h                                    ; [VARIABLE -> id[EXPRESSION]] - Adds local variable offset for local variable array [Array4] to EAX. Now EAX contains base array address of array [Array4].
ADD EAX,EBX                                       ; [VARIABLE -> id[EXPRESSION]] - Adds array index byt offset for array [Array4] to EAX. Now EAX contains address of [Array4[EXPRESSION]].
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Array4] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [Array4] to STACK.
CALL PrintLineInt                                 ; [CALL -> id(ARGS)] - Calls procedure [PrintLineInt()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineInt()] from STACK.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Array1] to EAX.
ADD EAX,-0028h                                    ; [VARIABLE -> id] - Adds local variable offset for local variable array [Array1] to EAX. Now EAX contains base array address of array [Array1].
PUSH EAX                                          ; [VARIABLE -> id] - Pushs address of variable [Array1] to STACK.
MOV EAX,0009h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
PUSH EAX                                          ; [FACTOR -> num] - Pushs INT constant to STACK.
CALL PrintItemOfArray                             ; [CALL -> id(ARGS)] - Calls procedure [PrintItemOfArray()].
ADD ESP,0008h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintItemOfArray()] from STACK.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Array4] to EAX.
ADD EAX,-0050h                                    ; [VARIABLE -> id] - Adds local variable offset for local variable array [Array4] to EAX. Now EAX contains base array address of array [Array4].
PUSH EAX                                          ; [VARIABLE -> id] - Pushs address of variable [Array4] to STACK.
MOV EAX,0009h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
PUSH EAX                                          ; [FACTOR -> num] - Pushs INT constant to STACK.
CALL PrintItemOfArray                             ; [CALL -> id(ARGS)] - Calls procedure [PrintItemOfArray()].
ADD ESP,0008h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintItemOfArray()] from STACK.
Test3_EXIT:                                       ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Label to procedure [Test3()] exit code.
MOV ESP,EBP                                       ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Deallocates memory of local variables.
POP ECX                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of ECX.
POP EBX                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBX.
POP EBP                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBP.
RET                                               ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Exits procedure [Test3()].
Test3 ENDP                                        ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Ends procedure [Test3()].

Test4 PROC                                        ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Begins procedure [Test4()].
PUSH EBP                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBP to STACK.
PUSH EBX                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBX to STACK.
PUSH ECX                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of ECX to STACK.
MOV EBP,ESP                                       ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Moves ESP to EBP to store begin address of LOCAL VARIABLES.
SUB ESP,0044h                                     ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Allocates memory for local variables.
MOV EAX,000Ah                                     ; [CONST -> num] - Moves INT constant to EAX.
MOV ECX,EAX                                       ; [VARIABLE_DECLARATION -> TYPE_SPECIFIER id=CONST;] - Moves value of constant for variable [IntValue] to ECX.
PUSH OFFSET _STRING_11                            ; [CONST -> string_literal] - Pushs address of LITERAL to STACK.
POP EAX                                           ; [VARIABLE_DECLARATION -> TYPE_SPECIFIER id=CONST;] - Gets value of constant for variable [StringValue] to EAX.
MOV [EBP-36],EAX                                  ; [VARIABLE_DECLARATION -> TYPE_SPECIFIER id=CONST;] - Moves value of constant for variable [StringValue] to STACK.
MOV EAX,0001h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,0004h                                     ; [VARIABLE -> id[EXPRESSION]] - Moves SIZEOF(ARRAY_ITEM) for array [IntArray1] to EBX.
MUL EBX                                           ; [VARIABLE -> id[EXPRESSION]] - Multiplies EXPRESSION*SIZEOF(ARRAY_ITEM) to calculate array index byte offset for array [IntArray1].
MOV EBX,EAX                                       ; [VARIABLE -> id[EXPRESSION]] - Moves array index byte offset EXPRESSION*SIZEOF(ARRAY_ITEM) for array [IntArray1] to EBX.
MOV EAX,EBP                                       ; [VARIABLE -> id[EXPRESSION]] - Moves EBP for local variable array [IntArray1] to EAX.
ADD EAX,-000Ch                                    ; [VARIABLE -> id[EXPRESSION]] - Adds local variable offset for local variable array [IntArray1] to EAX. Now EAX contains base array address of array [IntArray1].
ADD EAX,EBX                                       ; [VARIABLE -> id[EXPRESSION]] - Adds array index byt offset for array [IntArray1] to EAX. Now EAX contains address of [IntArray1[EXPRESSION]].
PUSH EAX                                          ; [VARIABLE -> id[EXPRESSION]] - Pushs address of variable [IntArray1[EXPRESSION]] to STACK.
MOV EAX,0001h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets address of VARIABLE for operation ASSIGNMENT to EAX.
MOV [EAX],EBX                                     ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Moves value of EXPRESSION to VARIABLE.
MOV EAX,0001h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,0004h                                     ; [VARIABLE -> id[EXPRESSION]] - Moves SIZEOF(ARRAY_ITEM) for array [StringArray1] to EBX.
MUL EBX                                           ; [VARIABLE -> id[EXPRESSION]] - Multiplies EXPRESSION*SIZEOF(ARRAY_ITEM) to calculate array index byte offset for array [StringArray1].
MOV EBX,EAX                                       ; [VARIABLE -> id[EXPRESSION]] - Moves array index byte offset EXPRESSION*SIZEOF(ARRAY_ITEM) for array [StringArray1] to EBX.
MOV EAX,EBP                                       ; [VARIABLE -> id[EXPRESSION]] - Moves EBP for local variable array [StringArray1] to EAX.
ADD EAX,-0020h                                    ; [VARIABLE -> id[EXPRESSION]] - Adds local variable offset for local variable array [StringArray1] to EAX. Now EAX contains base array address of array [StringArray1].
ADD EAX,EBX                                       ; [VARIABLE -> id[EXPRESSION]] - Adds array index byt offset for array [StringArray1] to EAX. Now EAX contains address of [StringArray1[EXPRESSION]].
PUSH EAX                                          ; [VARIABLE -> id[EXPRESSION]] - Pushs address of variable [StringArray1[EXPRESSION]] to STACK.
PUSH OFFSET _STRING_8                             ; [FACTOR -> string_literal] - Pushs address of LITERAL to STACK.
POP EBX                                           ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets value of EXPRESSION for operation ASSIGNMENT to EBX.
POP EAX                                           ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets address of VARIABLE for operation ASSIGNMENT to EAX.
MOV [EAX],EBX                                     ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Moves value of EXPRESSION to VARIABLE.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [IntArray1] to EAX.
ADD EAX,-000Ch                                    ; [VARIABLE -> id] - Adds local variable offset for local variable array [IntArray1] to EAX. Now EAX contains base array address of array [IntArray1].
PUSH EAX                                          ; [VARIABLE -> id] - Pushs address of variable [IntArray1] to STACK.
CALL PassParameterIntArray                        ; [CALL -> id(ARGS)] - Calls procedure [PassParameterIntArray()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PassParameterIntArray()] from STACK.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [StringArray1] to EAX.
ADD EAX,-0020h                                    ; [VARIABLE -> id] - Adds local variable offset for local variable array [StringArray1] to EAX. Now EAX contains base array address of array [StringArray1].
PUSH EAX                                          ; [VARIABLE -> id] - Pushs address of variable [StringArray1] to STACK.
CALL PassParameterStringArray                     ; [CALL -> id(ARGS)] - Calls procedure [PassParameterStringArray()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PassParameterStringArray()] from STACK.
PUSH ECX                                          ; [VARIABLE -> id] - Pushs value of variable [IntValue] to STACK.
CALL PassParameterInt                             ; [CALL -> id(ARGS)] - Calls procedure [PassParameterInt()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PassParameterInt()] from STACK.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [StringValue] to EAX.
ADD EAX,-0024h                                    ; [VARIABLE -> id] - Adds offset for symbol [StringValue] to EAX. Now EAX contains address of symbol [StringValue].
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [StringValue] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [StringValue] to STACK.
CALL PassParameterString                          ; [CALL -> id(ARGS)] - Calls procedure [PassParameterString()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PassParameterString()] from STACK.
MOV EAX,0001h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,0004h                                     ; [VARIABLE -> id[EXPRESSION]] - Moves SIZEOF(ARRAY_ITEM) for array [IntArray2] to EBX.
MUL EBX                                           ; [VARIABLE -> id[EXPRESSION]] - Multiplies EXPRESSION*SIZEOF(ARRAY_ITEM) to calculate array index byte offset for array [IntArray2].
MOV EBX,EAX                                       ; [VARIABLE -> id[EXPRESSION]] - Moves array index byte offset EXPRESSION*SIZEOF(ARRAY_ITEM) for array [IntArray2] to EBX.
MOV EAX,EBP                                       ; [VARIABLE -> id[EXPRESSION]] - Moves EBP for local variable array [IntArray2] to EAX.
ADD EAX,-0038h                                    ; [VARIABLE -> id[EXPRESSION]] - Adds local variable offset for local variable array [IntArray2] to EAX. Now EAX contains base array address of array [IntArray2].
ADD EAX,EBX                                       ; [VARIABLE -> id[EXPRESSION]] - Adds array index byt offset for array [IntArray2] to EAX. Now EAX contains address of [IntArray2[EXPRESSION]].
PUSH EAX                                          ; [VARIABLE -> id[EXPRESSION]] - Pushs address of variable [IntArray2[EXPRESSION]] to STACK.
MOV EAX,0002h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets address of VARIABLE for operation ASSIGNMENT to EAX.
MOV [EAX],EBX                                     ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Moves value of EXPRESSION to VARIABLE.
MOV EAX,0001h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,0004h                                     ; [VARIABLE -> id[EXPRESSION]] - Moves SIZEOF(ARRAY_ITEM) for array [StringArray2] to EBX.
MUL EBX                                           ; [VARIABLE -> id[EXPRESSION]] - Multiplies EXPRESSION*SIZEOF(ARRAY_ITEM) to calculate array index byte offset for array [StringArray2].
MOV EBX,EAX                                       ; [VARIABLE -> id[EXPRESSION]] - Moves array index byte offset EXPRESSION*SIZEOF(ARRAY_ITEM) for array [StringArray2] to EBX.
MOV EAX,EBP                                       ; [VARIABLE -> id[EXPRESSION]] - Moves EBP for local variable array [StringArray2] to EAX.
ADD EAX,-0044h                                    ; [VARIABLE -> id[EXPRESSION]] - Adds local variable offset for local variable array [StringArray2] to EAX. Now EAX contains base array address of array [StringArray2].
ADD EAX,EBX                                       ; [VARIABLE -> id[EXPRESSION]] - Adds array index byt offset for array [StringArray2] to EAX. Now EAX contains address of [StringArray2[EXPRESSION]].
PUSH EAX                                          ; [VARIABLE -> id[EXPRESSION]] - Pushs address of variable [StringArray2[EXPRESSION]] to STACK.
PUSH OFFSET _STRING_7                             ; [FACTOR -> string_literal] - Pushs address of LITERAL to STACK.
POP EBX                                           ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets value of EXPRESSION for operation ASSIGNMENT to EBX.
POP EAX                                           ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets address of VARIABLE for operation ASSIGNMENT to EAX.
MOV [EAX],EBX                                     ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Moves value of EXPRESSION to VARIABLE.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [IntArray2] to EAX.
ADD EAX,-0038h                                    ; [VARIABLE -> id] - Adds local variable offset for local variable array [IntArray2] to EAX. Now EAX contains base array address of array [IntArray2].
PUSH EAX                                          ; [VARIABLE -> id] - Pushs address of variable [IntArray2] to STACK.
CALL PassParameterIntArray                        ; [CALL -> id(ARGS)] - Calls procedure [PassParameterIntArray()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PassParameterIntArray()] from STACK.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [StringArray2] to EAX.
ADD EAX,-0044h                                    ; [VARIABLE -> id] - Adds local variable offset for local variable array [StringArray2] to EAX. Now EAX contains base array address of array [StringArray2].
PUSH EAX                                          ; [VARIABLE -> id] - Pushs address of variable [StringArray2] to STACK.
CALL PassParameterStringArray                     ; [CALL -> id(ARGS)] - Calls procedure [PassParameterStringArray()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PassParameterStringArray()] from STACK.
Test4_EXIT:                                       ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Label to procedure [Test4()] exit code.
MOV ESP,EBP                                       ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Deallocates memory of local variables.
POP ECX                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of ECX.
POP EBX                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBX.
POP EBP                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBP.
RET                                               ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Exits procedure [Test4()].
Test4 ENDP                                        ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Ends procedure [Test4()].

Test5 PROC                                        ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Begins procedure [Test5()].
PUSH EBP                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBP to STACK.
PUSH EBX                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBX to STACK.
PUSH ECX                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of ECX to STACK.
MOV EBP,ESP                                       ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Moves ESP to EBP to store begin address of LOCAL VARIABLES.
SUB ESP,0004h                                     ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Allocates memory for local variables.
MOV EAX,000Ah                                     ; [CONST -> num] - Moves INT constant to EAX.
MOV ECX,EAX                                       ; [VARIABLE_DECLARATION -> TYPE_SPECIFIER id=CONST;] - Moves value of constant for variable [Value1] to ECX.
PUSH ECX                                          ; [VARIABLE -> id] - Pushs value of variable [Value1] to STACK.
CALL PrintLineInt                                 ; [CALL -> id(ARGS)] - Calls procedure [PrintLineInt()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineInt()] from STACK.
MOV EAX,0014h                                     ; [CONST -> num] - Moves INT constant to EAX.
MOV [EBP-4],EAX                                   ; [VARIABLE_DECLARATION -> TYPE_SPECIFIER id=CONST;] - Moves value of constant for variable [Value2] to STACK.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Value2] to EAX.
ADD EAX,-0004h                                    ; [VARIABLE -> id] - Adds offset for symbol [Value2] to EAX. Now EAX contains address of symbol [Value2].
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Value2] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [Value2] to STACK.
CALL PrintLineInt                                 ; [CALL -> id(ARGS)] - Calls procedure [PrintLineInt()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineInt()] from STACK.
PUSH ECX                                          ; [VARIABLE -> id] - Pushs value of variable [Value1] to STACK.
PUSH ECX                                          ; [VARIABLE -> id] - Pushs value of variable [Value1] to STACK.
MOV EAX,0001h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Gets OPERAND O1 for operation [ADDITION] to EAX.
ADD EAX,EBX                                       ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Executes operation EAX=EAX+EBX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets address of VARIABLE for operation ASSIGNMENT to EAX.
MOV ECX,EBX                                       ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Moves value of EXPRESSION to VARIABLE.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Value2] to EAX.
ADD EAX,-0004h                                    ; [VARIABLE -> id] - Adds offset for symbol [Value2] to EAX. Now EAX contains address of symbol [Value2].
PUSH EAX                                          ; [VARIABLE -> id] - Pushs address of variable [Value2] to STACK.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Value2] to EAX.
ADD EAX,-0004h                                    ; [VARIABLE -> id] - Adds offset for symbol [Value2] to EAX. Now EAX contains address of symbol [Value2].
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Value2] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [Value2] to STACK.
MOV EAX,0001h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Gets OPERAND O1 for operation [ADDITION] to EAX.
ADD EAX,EBX                                       ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Executes operation EAX=EAX+EBX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets address of VARIABLE for operation ASSIGNMENT to EAX.
MOV [EAX],EBX                                     ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Moves value of EXPRESSION to VARIABLE.
PUSH ECX                                          ; [VARIABLE -> id] - Pushs value of variable [Value1] to STACK.
CALL PrintLineInt                                 ; [CALL -> id(ARGS)] - Calls procedure [PrintLineInt()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineInt()] from STACK.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Value2] to EAX.
ADD EAX,-0004h                                    ; [VARIABLE -> id] - Adds offset for symbol [Value2] to EAX. Now EAX contains address of symbol [Value2].
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Value2] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [Value2] to STACK.
CALL PrintLineInt                                 ; [CALL -> id(ARGS)] - Calls procedure [PrintLineInt()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineInt()] from STACK.
Test5_EXIT:                                       ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Label to procedure [Test5()] exit code.
MOV ESP,EBP                                       ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Deallocates memory of local variables.
POP ECX                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of ECX.
POP EBX                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBX.
POP EBP                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBP.
RET                                               ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Exits procedure [Test5()].
Test5 ENDP                                        ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Ends procedure [Test5()].

Test6 PROC                                        ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Begins procedure [Test6()].
PUSH EBP                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBP to STACK.
PUSH EBX                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBX to STACK.
PUSH ECX                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of ECX to STACK.
MOV EBP,ESP                                       ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Moves ESP to EBP to store begin address of LOCAL VARIABLES.
SUB ESP,0004h                                     ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Allocates memory for local variables.
PUSH OFFSET _STRING_6                             ; [CONST -> string_literal] - Pushs address of LITERAL to STACK.
POP EAX                                           ; [VARIABLE_DECLARATION -> TYPE_SPECIFIER id=CONST;] - Gets value of constant for variable [Value1] to EAX.
MOV [EBP-4],EAX                                   ; [VARIABLE_DECLARATION -> TYPE_SPECIFIER id=CONST;] - Moves value of constant for variable [Value1] to STACK.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Value1] to EAX.
ADD EAX,-0004h                                    ; [VARIABLE -> id] - Adds offset for symbol [Value1] to EAX. Now EAX contains address of symbol [Value1].
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Value1] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [Value1] to STACK.
CALL PrintLineString                              ; [CALL -> id(ARGS)] - Calls procedure [PrintLineString()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineString()] from STACK.
MOV EAX,0014h                                     ; [CONST -> num] - Moves INT constant to EAX.
MOV ECX,EAX                                       ; [VARIABLE_DECLARATION -> TYPE_SPECIFIER id=CONST;] - Moves value of constant for variable [Value2] to ECX.
PUSH ECX                                          ; [VARIABLE -> id] - Pushs value of variable [Value2] to STACK.
CALL PrintLineInt                                 ; [CALL -> id(ARGS)] - Calls procedure [PrintLineInt()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineInt()] from STACK.
PUSH ECX                                          ; [VARIABLE -> id] - Pushs value of variable [Value2] to STACK.
PUSH ECX                                          ; [VARIABLE -> id] - Pushs value of variable [Value2] to STACK.
MOV EAX,0001h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Gets OPERAND O1 for operation [ADDITION] to EAX.
ADD EAX,EBX                                       ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Executes operation EAX=EAX+EBX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets address of VARIABLE for operation ASSIGNMENT to EAX.
MOV ECX,EBX                                       ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Moves value of EXPRESSION to VARIABLE.
PUSH ECX                                          ; [VARIABLE -> id] - Pushs value of variable [Value2] to STACK.
CALL PrintLineInt                                 ; [CALL -> id(ARGS)] - Calls procedure [PrintLineInt()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineInt()] from STACK.
Test6_EXIT:                                       ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Label to procedure [Test6()] exit code.
MOV ESP,EBP                                       ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Deallocates memory of local variables.
POP ECX                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of ECX.
POP EBX                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBX.
POP EBP                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBP.
RET                                               ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Exits procedure [Test6()].
Test6 ENDP                                        ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Ends procedure [Test6()].

Test7 PROC                                        ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Begins procedure [Test7()].
PUSH EBP                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBP to STACK.
PUSH EBX                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBX to STACK.
PUSH ECX                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of ECX to STACK.
MOV EBP,ESP                                       ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Moves ESP to EBP to store begin address of LOCAL VARIABLES.
SUB ESP,0004h                                     ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Allocates memory for local variables.
PUSH OFFSET _STRING_6                             ; [CONST -> string_literal] - Pushs address of LITERAL to STACK.
POP EAX                                           ; [VARIABLE_DECLARATION -> TYPE_SPECIFIER id=CONST;] - Gets value of constant for variable [Value1] to EAX.
MOV [EBP-4],EAX                                   ; [VARIABLE_DECLARATION -> TYPE_SPECIFIER id=CONST;] - Moves value of constant for variable [Value1] to STACK.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Value1] to EAX.
ADD EAX,-0004h                                    ; [VARIABLE -> id] - Adds offset for symbol [Value1] to EAX. Now EAX contains address of symbol [Value1].
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Value1] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [Value1] to STACK.
CALL PrintLineString                              ; [CALL -> id(ARGS)] - Calls procedure [PrintLineString()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineString()] from STACK.
MOV EAX,0014h                                     ; [CONST -> num] - Moves INT constant to EAX.
MOV ECX,EAX                                       ; [VARIABLE_DECLARATION -> TYPE_SPECIFIER id=CONST;] - Moves value of constant for variable [Value2] to ECX.
PUSH ECX                                          ; [VARIABLE -> id] - Pushs value of variable [Value2] to STACK.
CALL PrintLineInt                                 ; [CALL -> id(ARGS)] - Calls procedure [PrintLineInt()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineInt()] from STACK.
CALL Test5                                        ; [CALL -> id(ARGS)] - Calls procedure [Test5()].
ADD ESP,0000h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [Test5()] from STACK.
PUSH ECX                                          ; [VARIABLE -> id] - Pushs value of variable [Value2] to STACK.
PUSH ECX                                          ; [VARIABLE -> id] - Pushs value of variable [Value2] to STACK.
MOV EAX,0001h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Gets OPERAND O1 for operation [ADDITION] to EAX.
ADD EAX,EBX                                       ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Executes operation EAX=EAX+EBX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets address of VARIABLE for operation ASSIGNMENT to EAX.
MOV ECX,EBX                                       ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Moves value of EXPRESSION to VARIABLE.
CALL Test6                                        ; [CALL -> id(ARGS)] - Calls procedure [Test6()].
ADD ESP,0000h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [Test6()] from STACK.
PUSH ECX                                          ; [VARIABLE -> id] - Pushs value of variable [Value2] to STACK.
CALL PrintLineInt                                 ; [CALL -> id(ARGS)] - Calls procedure [PrintLineInt()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineInt()] from STACK.
MOV EAX,OFFSET GlobalIntInitialized               ; Moves ADDRESS of [GlobalIntInitialized] to EAX.
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [GlobalIntInitialized] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [GlobalIntInitialized] to STACK.
CALL PrintLineInt                                 ; [CALL -> id(ARGS)] - Calls procedure [PrintLineInt()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineInt()] from STACK.
Test7_EXIT:                                       ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Label to procedure [Test7()] exit code.
MOV ESP,EBP                                       ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Deallocates memory of local variables.
POP ECX                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of ECX.
POP EBX                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBX.
POP EBP                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBP.
RET                                               ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Exits procedure [Test7()].
Test7 ENDP                                        ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Ends procedure [Test7()].

Main PROC                                         ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Begins procedure [Main()].
PUSH EBP                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBP to STACK.
PUSH EBX                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBX to STACK.
PUSH ECX                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of ECX to STACK.
MOV EBP,ESP                                       ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Moves ESP to EBP to store begin address of LOCAL VARIABLES.
SUB ESP,0000h                                     ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Allocates memory for local variables.
PUSH OFFSET _STRING_12                            ; [FACTOR -> string_literal] - Pushs address of LITERAL to STACK.
CALL PrintLineString                              ; [CALL -> id(ARGS)] - Calls procedure [PrintLineString()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineString()] from STACK.
CALL Test7                                        ; [CALL -> id(ARGS)] - Calls procedure [Test7()].
ADD ESP,0000h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [Test7()] from STACK.
PUSH OFFSET _STRING_13                            ; [FACTOR -> string_literal] - Pushs address of LITERAL to STACK.
CALL PrintLineString                              ; [CALL -> id(ARGS)] - Calls procedure [PrintLineString()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineString()] from STACK.
Main_EXIT:                                        ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Label to procedure [Main()] exit code.
MOV ESP,EBP                                       ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Deallocates memory of local variables.
POP ECX                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of ECX.
POP EBX                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBX.
POP EBP                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBP.
RET                                               ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Exits procedure [Main()].
Main ENDP                                         ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Ends procedure [Main()].


END Code
