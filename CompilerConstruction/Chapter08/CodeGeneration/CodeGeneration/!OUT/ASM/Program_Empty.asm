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
_STRING_1 BYTE "BEGIN of PROGRAM !",0
_STRING_2 BYTE "END of PROGRAM !",0
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
MOV EBP,ESP                                       ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Moves ESP to EBP to store begin address of LOCAL VARIABLES.
SUB ESP,0000h                                     ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Allocates memory for local variables.
MOV EAX,[EBP+12]                                  ; Moves ADDRESS of INTEGER VALUE to EAX.
INVOKE wsprintf, OFFSET _ConversionBuffer, OFFSET _ConversionString, EAX; Calls wsprintf() to fill BUFFER with INTEGER VALUE.
print OFFSET _ConversionBuffer                    ; Prints INTEGER VALUE to CONSOLE.
PrintInt_EXIT:                                    ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Label to procedure [PrintInt()] exit code.
MOV ESP,EBP                                       ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Deallocates memory of local variables.
POP EBX                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBX.
POP EBP                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBP.
RET                                               ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Exits procedure [PrintInt()].
PrintInt ENDP                                     ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Ends procedure [PrintInt()].

PrintLineInt PROC                                 ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Begins procedure [PrintLineInt()].
PUSH EBP                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBP to STACK.
PUSH EBX                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBX to STACK.
MOV EBP,ESP                                       ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Moves ESP to EBP to store begin address of LOCAL VARIABLES.
SUB ESP,0000h                                     ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Allocates memory for local variables.
MOV EAX,[EBP+12]                                  ; Moves ADDRESS of INTEGER VALUE to EAX.
INVOKE wsprintf, OFFSET _ConversionBuffer, OFFSET _ConversionString, EAX; Calls wsprintf() to fill BUFFER with INTEGER VALUE.
print OFFSET _ConversionBuffer                    ; Prints INTEGER VALUE to CONSOLE.
print OFFSET _EmptyLine                           ; Prints EMPTY LINE to CONSOLE.
PrintLineInt_EXIT:                                ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Label to procedure [PrintLineInt()] exit code.
MOV ESP,EBP                                       ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Deallocates memory of local variables.
POP EBX                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBX.
POP EBP                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBP.
RET                                               ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Exits procedure [PrintLineInt()].
PrintLineInt ENDP                                 ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Ends procedure [PrintLineInt()].

PrintString PROC                                  ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Begins procedure [PrintString()].
PUSH EBP                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBP to STACK.
PUSH EBX                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBX to STACK.
MOV EBP,ESP                                       ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Moves ESP to EBP to store begin address of LOCAL VARIABLES.
SUB ESP,0000h                                     ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Allocates memory for local variables.
MOV EAX,[EBP+12]                                  ; Moves ADDRESS of STRING VALUE to EAX.
print EAX                                         ; Prints STRING VALUE to CONSOLE.
PrintString_EXIT:                                 ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Label to procedure [PrintString()] exit code.
MOV ESP,EBP                                       ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Deallocates memory of local variables.
POP EBX                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBX.
POP EBP                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBP.
RET                                               ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Exits procedure [PrintString()].
PrintString ENDP                                  ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Ends procedure [PrintString()].

PrintLineString PROC                              ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Begins procedure [PrintLineString()].
PUSH EBP                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBP to STACK.
PUSH EBX                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBX to STACK.
MOV EBP,ESP                                       ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Moves ESP to EBP to store begin address of LOCAL VARIABLES.
SUB ESP,0000h                                     ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Allocates memory for local variables.
MOV EAX,[EBP+12]                                  ; Moves ADDRESS of STRING VALUE to EAX.
print EAX                                         ; Prints STRING VALUE to CONSOLE.
print OFFSET _EmptyLine                           ; Prints EMPTY LINE to CONSOLE.
PrintLineString_EXIT:                             ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Label to procedure [PrintLineString()] exit code.
MOV ESP,EBP                                       ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Deallocates memory of local variables.
POP EBX                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBX.
POP EBP                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBP.
RET                                               ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Exits procedure [PrintLineString()].
PrintLineString ENDP                              ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Ends procedure [PrintLineString()].

Main PROC                                         ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Begins procedure [Main()].
PUSH EBP                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBP to STACK.
PUSH EBX                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBX to STACK.
MOV EBP,ESP                                       ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Moves ESP to EBP to store begin address of LOCAL VARIABLES.
SUB ESP,0000h                                     ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Allocates memory for local variables.
PUSH OFFSET _STRING_1                             ; [FACTOR -> string_literal] - Pushs address of LITERAL to STACK.
CALL PrintLineString                              ; [CALL -> id(ARGS)] - Calls procedure [PrintLineString()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineString()] from STACK.
PUSH OFFSET _STRING_2                             ; [FACTOR -> string_literal] - Pushs address of LITERAL to STACK.
CALL PrintLineString                              ; [CALL -> id(ARGS)] - Calls procedure [PrintLineString()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineString()] from STACK.
Main_EXIT:                                        ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Label to procedure [Main()] exit code.
MOV ESP,EBP                                       ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Deallocates memory of local variables.
POP EBX                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBX.
POP EBP                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBP.
RET                                               ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Exits procedure [Main()].
Main ENDP                                         ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Ends procedure [Main()].


END Code
