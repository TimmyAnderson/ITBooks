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
_STRING_1 BYTE "Value is GREATER or EQUAL than 4 !",0
_STRING_2 BYTE "Value is LOWER than 4 !",0
_STRING_3 BYTE "Value is LOWER than 3 !",0
_STRING_4 BYTE 0
_STRING_5 BYTE "[",0
_STRING_6 BYTE ",",0
_STRING_7 BYTE "]",0
_STRING_8 BYTE "Value is LOWER or NOT EQUAL than 10 !",0
_STRING_9 BYTE "Value is LOWER than 10 !",0
_STRING_10 BYTE "Value is GREATER or NOT EQUAL than 5 !",0
_STRING_11 BYTE "Value is GREATER than 5 !",0
_STRING_12 BYTE "Value is EQUAL to 8 !",0
_STRING_13 BYTE "Value is NOT EQUAL to 9 !",0
_STRING_14 BYTE "Before SORT:",0
_STRING_15 BYTE ": [",0
_STRING_16 BYTE "After SORT:",0
_STRING_17 BYTE "BEGIN of PROGRAM !",0
_STRING_18 BYTE "END of PROGRAM !",0
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

Sort PROC                                         ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Begins procedure [Sort()].
PUSH EBP                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBP to STACK.
PUSH EBX                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBX to STACK.
PUSH ECX                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of ECX to STACK.
MOV EBP,ESP                                       ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Moves ESP to EBP to store begin address of LOCAL VARIABLES.
SUB ESP,0008h                                     ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Allocates memory for local variables.
MOV EAX,0000h                                     ; [CONST -> num] - Moves INT constant to EAX.
MOV ECX,EAX                                       ; [VARIABLE_DECLARATION -> TYPE_SPECIFIER id=CONST;] - Moves value of constant for variable [Counter1] to ECX.
BEFORE_WHILE_Sort_1:                              ; [ITERATION_STATEMENT -> while (EXPRESSION) STATEMENT] - Label to BEGIN of WHILE block.
PUSH ECX                                          ; [VARIABLE -> id] - Pushs value of variable [Counter1] to STACK.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [ArrayToSortSize] to EAX.
ADD EAX,0010h                                     ; [VARIABLE -> id] - Adds offset for symbol [ArrayToSortSize] to EAX. Now EAX contains address of symbol [ArrayToSortSize].
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [ArrayToSortSize] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [ArrayToSortSize] to STACK.
MOV EAX,0001h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Gets OPERAND O1 for operation [SUBTRACTION] to EAX.
SUB EAX,EBX                                       ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Executes operation EAX=EAX-EBX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Gets OPERAND O1 for operation COMPARE to EAX.
CMP EAX,EBX                                       ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Compares O1 to O2.
JL TRUE_Sort_2                                    ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Jumps to TRUE label if O1<O2.
MOV EAX,0000h                                     ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Moves FALSE value (0) to EAX.
JMP FALSE_Sort_2                                  ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Jumps to FALSE label.
TRUE_Sort_2:                                      ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Label TRUE.
MOV EAX,0001h                                     ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Moves TRUE value (1) to EAX.
FALSE_Sort_2:                                     ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Label FALSE.
CMP EAX,0000h                                     ; [ITERATION_STATEMENT -> while (EXPRESSION) STATEMENT] - Compares value of EXPRESSION to 0.
JE AFTER_WHILE_Sort_1                             ; [ITERATION_STATEMENT -> while (EXPRESSION) STATEMENT] - Jumps to end of WHILE block.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Counter2] to EAX.
ADD EAX,-0004h                                    ; [VARIABLE -> id] - Adds offset for symbol [Counter2] to EAX. Now EAX contains address of symbol [Counter2].
PUSH EAX                                          ; [VARIABLE -> id] - Pushs address of variable [Counter2] to STACK.
PUSH ECX                                          ; [VARIABLE -> id] - Pushs value of variable [Counter1] to STACK.
MOV EAX,0001h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Gets OPERAND O1 for operation [ADDITION] to EAX.
ADD EAX,EBX                                       ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Executes operation EAX=EAX+EBX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets address of VARIABLE for operation ASSIGNMENT to EAX.
MOV [EAX],EBX                                     ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Moves value of EXPRESSION to VARIABLE.
BEFORE_WHILE_Sort_3:                              ; [ITERATION_STATEMENT -> while (EXPRESSION) STATEMENT] - Label to BEGIN of WHILE block.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Counter2] to EAX.
ADD EAX,-0004h                                    ; [VARIABLE -> id] - Adds offset for symbol [Counter2] to EAX. Now EAX contains address of symbol [Counter2].
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Counter2] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [Counter2] to STACK.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [ArrayToSortSize] to EAX.
ADD EAX,0010h                                     ; [VARIABLE -> id] - Adds offset for symbol [ArrayToSortSize] to EAX. Now EAX contains address of symbol [ArrayToSortSize].
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [ArrayToSortSize] from address of variable.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Gets OPERAND O1 for operation COMPARE to EAX.
CMP EAX,EBX                                       ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Compares O1 to O2.
JL TRUE_Sort_4                                    ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Jumps to TRUE label if O1<O2.
MOV EAX,0000h                                     ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Moves FALSE value (0) to EAX.
JMP FALSE_Sort_4                                  ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Jumps to FALSE label.
TRUE_Sort_4:                                      ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Label TRUE.
MOV EAX,0001h                                     ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Moves TRUE value (1) to EAX.
FALSE_Sort_4:                                     ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Label FALSE.
CMP EAX,0000h                                     ; [ITERATION_STATEMENT -> while (EXPRESSION) STATEMENT] - Compares value of EXPRESSION to 0.
JE AFTER_WHILE_Sort_3                             ; [ITERATION_STATEMENT -> while (EXPRESSION) STATEMENT] - Jumps to end of WHILE block.
PUSH ECX                                          ; [VARIABLE -> id] - Pushs value of variable [Counter1] to STACK.
POP EAX                                           ; [VARIABLE -> id[EXPRESSION]] - Pops value of EXPRESSION for array [ArrayToSort] to EAX.
MOV EBX,0004h                                     ; [VARIABLE -> id[EXPRESSION]] - Moves SIZEOF(ARRAY_ITEM) for array [ArrayToSort] to EBX.
MUL EBX                                           ; [VARIABLE -> id[EXPRESSION]] - Multiplies EXPRESSION*SIZEOF(ARRAY_ITEM) to calculate array index byte offset for array [ArrayToSort].
MOV EBX,EAX                                       ; [VARIABLE -> id[EXPRESSION]] - Moves array index byte offset EXPRESSION*SIZEOF(ARRAY_ITEM) for array [ArrayToSort] to EBX.
MOV EAX,[EBP+20]                                  ; [VARIABLE -> id[EXPRESSION]] - Moves array base address [EBP+StackOffset] for parameter array [ArrayToSort] to EAX.
ADD EAX,EBX                                       ; [VARIABLE -> id[EXPRESSION]] - Adds array index byt offset for array [ArrayToSort] to EAX. Now EAX contains address of [ArrayToSort[EXPRESSION]].
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [ArrayToSort] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [ArrayToSort] to STACK.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Counter2] to EAX.
ADD EAX,-0004h                                    ; [VARIABLE -> id] - Adds offset for symbol [Counter2] to EAX. Now EAX contains address of symbol [Counter2].
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Counter2] from address of variable.
MOV EBX,0004h                                     ; [VARIABLE -> id[EXPRESSION]] - Moves SIZEOF(ARRAY_ITEM) for array [ArrayToSort] to EBX.
MUL EBX                                           ; [VARIABLE -> id[EXPRESSION]] - Multiplies EXPRESSION*SIZEOF(ARRAY_ITEM) to calculate array index byte offset for array [ArrayToSort].
MOV EBX,EAX                                       ; [VARIABLE -> id[EXPRESSION]] - Moves array index byte offset EXPRESSION*SIZEOF(ARRAY_ITEM) for array [ArrayToSort] to EBX.
MOV EAX,[EBP+20]                                  ; [VARIABLE -> id[EXPRESSION]] - Moves array base address [EBP+StackOffset] for parameter array [ArrayToSort] to EAX.
ADD EAX,EBX                                       ; [VARIABLE -> id[EXPRESSION]] - Adds array index byt offset for array [ArrayToSort] to EAX. Now EAX contains address of [ArrayToSort[EXPRESSION]].
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [ArrayToSort] from address of variable.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Gets OPERAND O1 for operation COMPARE to EAX.
CMP EAX,EBX                                       ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Compares O1 to O2.
JG TRUE_Sort_6                                    ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Jumps to TRUE label if O1>O2
MOV EAX,0000h                                     ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Moves FALSE value (0) to EAX.
JMP FALSE_Sort_6                                  ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Jumps to FALSE label.
TRUE_Sort_6:                                      ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Label TRUE.
MOV EAX,0001h                                     ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Moves TRUE value (1) to EAX.
FALSE_Sort_6:                                     ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Label FALSE.
CMP EAX,0000h                                     ; [SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT] - Compares value of EXPRESSION to 0.
JE AFTER_IF_Sort_5                                ; [SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT] - If value of EXPRESSION==0, jumps to END of IF block.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Temp] to EAX.
ADD EAX,-0008h                                    ; [VARIABLE -> id] - Adds offset for symbol [Temp] to EAX. Now EAX contains address of symbol [Temp].
PUSH EAX                                          ; [VARIABLE -> id] - Pushs address of variable [Temp] to STACK.
PUSH ECX                                          ; [VARIABLE -> id] - Pushs value of variable [Counter1] to STACK.
POP EAX                                           ; [VARIABLE -> id[EXPRESSION]] - Pops value of EXPRESSION for array [ArrayToSort] to EAX.
MOV EBX,0004h                                     ; [VARIABLE -> id[EXPRESSION]] - Moves SIZEOF(ARRAY_ITEM) for array [ArrayToSort] to EBX.
MUL EBX                                           ; [VARIABLE -> id[EXPRESSION]] - Multiplies EXPRESSION*SIZEOF(ARRAY_ITEM) to calculate array index byte offset for array [ArrayToSort].
MOV EBX,EAX                                       ; [VARIABLE -> id[EXPRESSION]] - Moves array index byte offset EXPRESSION*SIZEOF(ARRAY_ITEM) for array [ArrayToSort] to EBX.
MOV EAX,[EBP+20]                                  ; [VARIABLE -> id[EXPRESSION]] - Moves array base address [EBP+StackOffset] for parameter array [ArrayToSort] to EAX.
ADD EAX,EBX                                       ; [VARIABLE -> id[EXPRESSION]] - Adds array index byt offset for array [ArrayToSort] to EAX. Now EAX contains address of [ArrayToSort[EXPRESSION]].
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [ArrayToSort] from address of variable.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets address of VARIABLE for operation ASSIGNMENT to EAX.
MOV [EAX],EBX                                     ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Moves value of EXPRESSION to VARIABLE.
PUSH ECX                                          ; [VARIABLE -> id] - Pushs value of variable [Counter1] to STACK.
POP EAX                                           ; [VARIABLE -> id[EXPRESSION]] - Pops value of EXPRESSION for array [ArrayToSort] to EAX.
MOV EBX,0004h                                     ; [VARIABLE -> id[EXPRESSION]] - Moves SIZEOF(ARRAY_ITEM) for array [ArrayToSort] to EBX.
MUL EBX                                           ; [VARIABLE -> id[EXPRESSION]] - Multiplies EXPRESSION*SIZEOF(ARRAY_ITEM) to calculate array index byte offset for array [ArrayToSort].
MOV EBX,EAX                                       ; [VARIABLE -> id[EXPRESSION]] - Moves array index byte offset EXPRESSION*SIZEOF(ARRAY_ITEM) for array [ArrayToSort] to EBX.
MOV EAX,[EBP+20]                                  ; [VARIABLE -> id[EXPRESSION]] - Moves array base address [EBP+StackOffset] for parameter array [ArrayToSort] to EAX.
ADD EAX,EBX                                       ; [VARIABLE -> id[EXPRESSION]] - Adds array index byt offset for array [ArrayToSort] to EAX. Now EAX contains address of [ArrayToSort[EXPRESSION]].
PUSH EAX                                          ; [VARIABLE -> id[EXPRESSION]] - Pushs address of variable [ArrayToSort[EXPRESSION]] to STACK.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Counter2] to EAX.
ADD EAX,-0004h                                    ; [VARIABLE -> id] - Adds offset for symbol [Counter2] to EAX. Now EAX contains address of symbol [Counter2].
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Counter2] from address of variable.
MOV EBX,0004h                                     ; [VARIABLE -> id[EXPRESSION]] - Moves SIZEOF(ARRAY_ITEM) for array [ArrayToSort] to EBX.
MUL EBX                                           ; [VARIABLE -> id[EXPRESSION]] - Multiplies EXPRESSION*SIZEOF(ARRAY_ITEM) to calculate array index byte offset for array [ArrayToSort].
MOV EBX,EAX                                       ; [VARIABLE -> id[EXPRESSION]] - Moves array index byte offset EXPRESSION*SIZEOF(ARRAY_ITEM) for array [ArrayToSort] to EBX.
MOV EAX,[EBP+20]                                  ; [VARIABLE -> id[EXPRESSION]] - Moves array base address [EBP+StackOffset] for parameter array [ArrayToSort] to EAX.
ADD EAX,EBX                                       ; [VARIABLE -> id[EXPRESSION]] - Adds array index byt offset for array [ArrayToSort] to EAX. Now EAX contains address of [ArrayToSort[EXPRESSION]].
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [ArrayToSort] from address of variable.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets address of VARIABLE for operation ASSIGNMENT to EAX.
MOV [EAX],EBX                                     ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Moves value of EXPRESSION to VARIABLE.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Counter2] to EAX.
ADD EAX,-0004h                                    ; [VARIABLE -> id] - Adds offset for symbol [Counter2] to EAX. Now EAX contains address of symbol [Counter2].
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Counter2] from address of variable.
MOV EBX,0004h                                     ; [VARIABLE -> id[EXPRESSION]] - Moves SIZEOF(ARRAY_ITEM) for array [ArrayToSort] to EBX.
MUL EBX                                           ; [VARIABLE -> id[EXPRESSION]] - Multiplies EXPRESSION*SIZEOF(ARRAY_ITEM) to calculate array index byte offset for array [ArrayToSort].
MOV EBX,EAX                                       ; [VARIABLE -> id[EXPRESSION]] - Moves array index byte offset EXPRESSION*SIZEOF(ARRAY_ITEM) for array [ArrayToSort] to EBX.
MOV EAX,[EBP+20]                                  ; [VARIABLE -> id[EXPRESSION]] - Moves array base address [EBP+StackOffset] for parameter array [ArrayToSort] to EAX.
ADD EAX,EBX                                       ; [VARIABLE -> id[EXPRESSION]] - Adds array index byt offset for array [ArrayToSort] to EAX. Now EAX contains address of [ArrayToSort[EXPRESSION]].
PUSH EAX                                          ; [VARIABLE -> id[EXPRESSION]] - Pushs address of variable [ArrayToSort[EXPRESSION]] to STACK.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Temp] to EAX.
ADD EAX,-0008h                                    ; [VARIABLE -> id] - Adds offset for symbol [Temp] to EAX. Now EAX contains address of symbol [Temp].
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Temp] from address of variable.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets address of VARIABLE for operation ASSIGNMENT to EAX.
MOV [EAX],EBX                                     ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Moves value of EXPRESSION to VARIABLE.
AFTER_IF_Sort_5:                                  ; [SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT] - Label to END of IF block.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Counter2] to EAX.
ADD EAX,-0004h                                    ; [VARIABLE -> id] - Adds offset for symbol [Counter2] to EAX. Now EAX contains address of symbol [Counter2].
PUSH EAX                                          ; [VARIABLE -> id] - Pushs address of variable [Counter2] to STACK.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Counter2] to EAX.
ADD EAX,-0004h                                    ; [VARIABLE -> id] - Adds offset for symbol [Counter2] to EAX. Now EAX contains address of symbol [Counter2].
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Counter2] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [Counter2] to STACK.
MOV EAX,0001h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Gets OPERAND O1 for operation [ADDITION] to EAX.
ADD EAX,EBX                                       ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Executes operation EAX=EAX+EBX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets address of VARIABLE for operation ASSIGNMENT to EAX.
MOV [EAX],EBX                                     ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Moves value of EXPRESSION to VARIABLE.
JMP BEFORE_WHILE_Sort_3                           ; [ITERATION_STATEMENT -> while (EXPRESSION) STATEMENT] - Jumps to end of WHILE block.
AFTER_WHILE_Sort_3:                               ; [ITERATION_STATEMENT -> while (EXPRESSION) STATEMENT] - Label to END of WHILE block.
PUSH ECX                                          ; [VARIABLE -> id] - Pushs value of variable [Counter1] to STACK.
PUSH ECX                                          ; [VARIABLE -> id] - Pushs value of variable [Counter1] to STACK.
MOV EAX,0001h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Gets OPERAND O1 for operation [ADDITION] to EAX.
ADD EAX,EBX                                       ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Executes operation EAX=EAX+EBX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets address of VARIABLE for operation ASSIGNMENT to EAX.
MOV ECX,EBX                                       ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Moves value of EXPRESSION to VARIABLE.
JMP BEFORE_WHILE_Sort_1                           ; [ITERATION_STATEMENT -> while (EXPRESSION) STATEMENT] - Jumps to end of WHILE block.
AFTER_WHILE_Sort_1:                               ; [ITERATION_STATEMENT -> while (EXPRESSION) STATEMENT] - Label to END of WHILE block.
Sort_EXIT:                                        ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Label to procedure [Sort()] exit code.
MOV ESP,EBP                                       ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Deallocates memory of local variables.
POP ECX                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of ECX.
POP EBX                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBX.
POP EBP                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBP.
RET                                               ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Exits procedure [Sort()].
Sort ENDP                                         ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Ends procedure [Sort()].

TestForIf PROC                                    ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Begins procedure [TestForIf()].
PUSH EBP                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBP to STACK.
PUSH EBX                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBX to STACK.
PUSH ECX                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of ECX to STACK.
MOV EBP,ESP                                       ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Moves ESP to EBP to store begin address of LOCAL VARIABLES.
SUB ESP,0000h                                     ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Allocates memory for local variables.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Value] to EAX.
ADD EAX,0010h                                     ; [VARIABLE -> id] - Adds offset for symbol [Value] to EAX. Now EAX contains address of symbol [Value].
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Value] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [Value] to STACK.
MOV EAX,0003h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Gets OPERAND O1 for operation COMPARE to EAX.
CMP EAX,EBX                                       ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Compares O1 to O2.
JGE TRUE_TestForIf_2                              ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Jumps to TRUE label if O1>=O2
MOV EAX,0000h                                     ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Moves FALSE value (0) to EAX.
JMP FALSE_TestForIf_2                             ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Jumps to FALSE label.
TRUE_TestForIf_2:                                 ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Label TRUE.
MOV EAX,0001h                                     ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Moves TRUE value (1) to EAX.
FALSE_TestForIf_2:                                ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Label FALSE.
CMP EAX,0000h                                     ; [SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT else STATEMENT] - Compares value of EXPRESSION to 0.
JE BEFORE_ELSE_TestForIf_1                        ; [SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT else STATEMENT] - If value of EXPRESSION==0, jumps to ELSE block.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Value] to EAX.
ADD EAX,0010h                                     ; [VARIABLE -> id] - Adds offset for symbol [Value] to EAX. Now EAX contains address of symbol [Value].
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Value] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [Value] to STACK.
MOV EAX,0004h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Gets OPERAND O1 for operation COMPARE to EAX.
CMP EAX,EBX                                       ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Compares O1 to O2.
JGE TRUE_TestForIf_4                              ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Jumps to TRUE label if O1>=O2
MOV EAX,0000h                                     ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Moves FALSE value (0) to EAX.
JMP FALSE_TestForIf_4                             ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Jumps to FALSE label.
TRUE_TestForIf_4:                                 ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Label TRUE.
MOV EAX,0001h                                     ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Moves TRUE value (1) to EAX.
FALSE_TestForIf_4:                                ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Label FALSE.
CMP EAX,0000h                                     ; [SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT else STATEMENT] - Compares value of EXPRESSION to 0.
JE BEFORE_ELSE_TestForIf_3                        ; [SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT else STATEMENT] - If value of EXPRESSION==0, jumps to ELSE block.
PUSH OFFSET _STRING_1                             ; [FACTOR -> string_literal] - Pushs address of LITERAL to STACK.
CALL PrintLineString                              ; [CALL -> id(ARGS)] - Calls procedure [PrintLineString()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineString()] from STACK.
JMP AFTER_ELSE_TestForIf_3                        ; [SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT else STATEMENT] - Jumps to END of ELSE block.
BEFORE_ELSE_TestForIf_3:                          ; [SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT else STATEMENT] - Label to BEGIN of ELSE block.
PUSH OFFSET _STRING_2                             ; [FACTOR -> string_literal] - Pushs address of LITERAL to STACK.
CALL PrintLineString                              ; [CALL -> id(ARGS)] - Calls procedure [PrintLineString()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineString()] from STACK.
AFTER_ELSE_TestForIf_3:                           ; [SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT else STATEMENT] - Label to END of ELSE block.
JMP AFTER_ELSE_TestForIf_1                        ; [SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT else STATEMENT] - Jumps to END of ELSE block.
BEFORE_ELSE_TestForIf_1:                          ; [SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT else STATEMENT] - Label to BEGIN of ELSE block.
PUSH OFFSET _STRING_3                             ; [FACTOR -> string_literal] - Pushs address of LITERAL to STACK.
CALL PrintLineString                              ; [CALL -> id(ARGS)] - Calls procedure [PrintLineString()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineString()] from STACK.
AFTER_ELSE_TestForIf_1:                           ; [SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT else STATEMENT] - Label to END of ELSE block.
TestForIf_EXIT:                                   ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Label to procedure [TestForIf()] exit code.
MOV ESP,EBP                                       ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Deallocates memory of local variables.
POP ECX                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of ECX.
POP EBX                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBX.
POP EBP                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBP.
RET                                               ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Exits procedure [TestForIf()].
TestForIf ENDP                                    ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Ends procedure [TestForIf()].

Test1 PROC                                        ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Begins procedure [Test1()].
PUSH EBP                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBP to STACK.
PUSH EBX                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBX to STACK.
PUSH ECX                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of ECX to STACK.
MOV EBP,ESP                                       ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Moves ESP to EBP to store begin address of LOCAL VARIABLES.
SUB ESP,0008h                                     ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Allocates memory for local variables.
MOV EAX,000Ah                                     ; [CONST -> num] - Moves INT constant to EAX.
MOV ECX,EAX                                       ; [VARIABLE_DECLARATION -> TYPE_SPECIFIER id=CONST;] - Moves value of constant for variable [X] to ECX.
MOV EAX,0003h                                     ; [CONST -> num] - Moves INT constant to EAX.
MOV [EBP-4],EAX                                   ; [VARIABLE_DECLARATION -> TYPE_SPECIFIER id=CONST;] - Moves value of constant for variable [Y] to STACK.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Result] to EAX.
ADD EAX,-0008h                                    ; [VARIABLE -> id] - Adds offset for symbol [Result] to EAX. Now EAX contains address of symbol [Result].
PUSH EAX                                          ; [VARIABLE -> id] - Pushs address of variable [Result] to STACK.
PUSH ECX                                          ; [VARIABLE -> id] - Pushs value of variable [X] to STACK.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Y] to EAX.
ADD EAX,-0004h                                    ; [VARIABLE -> id] - Adds offset for symbol [Y] to EAX. Now EAX contains address of symbol [Y].
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Y] from address of variable.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [TERM -> TERM MUL_OPERATION FACTOR] - Gets OPERAND O1 for operation [MULTIPLICATION] to EAX.
IMUL EBX                                          ; [TERM -> TERM MUL_OPERATION FACTOR] - Executes operation EDX:EAX=EAX*EBX.
PUSH EAX                                          ; [TERM -> TERM MUL_OPERATION FACTOR] - Pushs operation result to STACK.
MOV EAX,0002h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Gets OPERAND O1 for operation [ADDITION] to EAX.
ADD EAX,EBX                                       ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Executes operation EAX=EAX+EBX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets address of VARIABLE for operation ASSIGNMENT to EAX.
MOV [EAX],EBX                                     ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Moves value of EXPRESSION to VARIABLE.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Result] to EAX.
ADD EAX,-0008h                                    ; [VARIABLE -> id] - Adds offset for symbol [Result] to EAX. Now EAX contains address of symbol [Result].
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Result] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [Result] to STACK.
CALL PrintLineInt                                 ; [CALL -> id(ARGS)] - Calls procedure [PrintLineInt()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineInt()] from STACK.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Result] to EAX.
ADD EAX,-0008h                                    ; [VARIABLE -> id] - Adds offset for symbol [Result] to EAX. Now EAX contains address of symbol [Result].
PUSH EAX                                          ; [VARIABLE -> id] - Pushs address of variable [Result] to STACK.
PUSH ECX                                          ; [VARIABLE -> id] - Pushs value of variable [X] to STACK.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Y] to EAX.
ADD EAX,-0004h                                    ; [VARIABLE -> id] - Adds offset for symbol [Y] to EAX. Now EAX contains address of symbol [Y].
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Y] from address of variable.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [TERM -> TERM MUL_OPERATION FACTOR] - Gets OPERAND O1 for operation [MULTIPLICATION] to EAX.
IMUL EBX                                          ; [TERM -> TERM MUL_OPERATION FACTOR] - Executes operation EDX:EAX=EAX*EBX.
PUSH EAX                                          ; [TERM -> TERM MUL_OPERATION FACTOR] - Pushs operation result to STACK.
MOV EAX,0002h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Gets OPERAND O1 for operation [ADDITION] to EAX.
ADD EAX,EBX                                       ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Executes operation EAX=EAX+EBX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets address of VARIABLE for operation ASSIGNMENT to EAX.
MOV [EAX],EBX                                     ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Moves value of EXPRESSION to VARIABLE.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Result] to EAX.
ADD EAX,-0008h                                    ; [VARIABLE -> id] - Adds offset for symbol [Result] to EAX. Now EAX contains address of symbol [Result].
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Result] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [Result] to STACK.
CALL PrintLineInt                                 ; [CALL -> id(ARGS)] - Calls procedure [PrintLineInt()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineInt()] from STACK.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Result] to EAX.
ADD EAX,-0008h                                    ; [VARIABLE -> id] - Adds offset for symbol [Result] to EAX. Now EAX contains address of symbol [Result].
PUSH EAX                                          ; [VARIABLE -> id] - Pushs address of variable [Result] to STACK.
PUSH ECX                                          ; [VARIABLE -> id] - Pushs value of variable [X] to STACK.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Y] to EAX.
ADD EAX,-0004h                                    ; [VARIABLE -> id] - Adds offset for symbol [Y] to EAX. Now EAX contains address of symbol [Y].
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Y] from address of variable.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [TERM -> TERM MUL_OPERATION FACTOR] - Gets OPERAND O1 for operation [MULTIPLICATION] to EAX.
IMUL EBX                                          ; [TERM -> TERM MUL_OPERATION FACTOR] - Executes operation EDX:EAX=EAX*EBX.
PUSH EAX                                          ; [TERM -> TERM MUL_OPERATION FACTOR] - Pushs operation result to STACK.
MOV EAX,0002h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Gets OPERAND O1 for operation [ADDITION] to EAX.
ADD EAX,EBX                                       ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Executes operation EAX=EAX+EBX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets address of VARIABLE for operation ASSIGNMENT to EAX.
MOV [EAX],EBX                                     ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Moves value of EXPRESSION to VARIABLE.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Result] to EAX.
ADD EAX,-0008h                                    ; [VARIABLE -> id] - Adds offset for symbol [Result] to EAX. Now EAX contains address of symbol [Result].
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Result] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [Result] to STACK.
CALL PrintLineInt                                 ; [CALL -> id(ARGS)] - Calls procedure [PrintLineInt()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineInt()] from STACK.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Result] to EAX.
ADD EAX,-0008h                                    ; [VARIABLE -> id] - Adds offset for symbol [Result] to EAX. Now EAX contains address of symbol [Result].
PUSH EAX                                          ; [VARIABLE -> id] - Pushs address of variable [Result] to STACK.
PUSH ECX                                          ; [VARIABLE -> id] - Pushs value of variable [X] to STACK.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Y] to EAX.
ADD EAX,-0004h                                    ; [VARIABLE -> id] - Adds offset for symbol [Y] to EAX. Now EAX contains address of symbol [Y].
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Y] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [Y] to STACK.
MOV EAX,0002h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Gets OPERAND O1 for operation [ADDITION] to EAX.
ADD EAX,EBX                                       ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Executes operation EAX=EAX+EBX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [TERM -> TERM MUL_OPERATION FACTOR] - Gets OPERAND O1 for operation [MULTIPLICATION] to EAX.
IMUL EBX                                          ; [TERM -> TERM MUL_OPERATION FACTOR] - Executes operation EDX:EAX=EAX*EBX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets address of VARIABLE for operation ASSIGNMENT to EAX.
MOV [EAX],EBX                                     ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Moves value of EXPRESSION to VARIABLE.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Result] to EAX.
ADD EAX,-0008h                                    ; [VARIABLE -> id] - Adds offset for symbol [Result] to EAX. Now EAX contains address of symbol [Result].
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Result] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [Result] to STACK.
CALL PrintLineInt                                 ; [CALL -> id(ARGS)] - Calls procedure [PrintLineInt()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineInt()] from STACK.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Result] to EAX.
ADD EAX,-0008h                                    ; [VARIABLE -> id] - Adds offset for symbol [Result] to EAX. Now EAX contains address of symbol [Result].
PUSH EAX                                          ; [VARIABLE -> id] - Pushs address of variable [Result] to STACK.
PUSH ECX                                          ; [VARIABLE -> id] - Pushs value of variable [X] to STACK.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Y] to EAX.
ADD EAX,-0004h                                    ; [VARIABLE -> id] - Adds offset for symbol [Y] to EAX. Now EAX contains address of symbol [Y].
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Y] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [Y] to STACK.
MOV EAX,0005h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Gets OPERAND O1 for operation [SUBTRACTION] to EAX.
SUB EAX,EBX                                       ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Executes operation EAX=EAX-EBX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [TERM -> TERM MUL_OPERATION FACTOR] - Gets OPERAND O1 for operation [MULTIPLICATION] to EAX.
IMUL EBX                                          ; [TERM -> TERM MUL_OPERATION FACTOR] - Executes operation EDX:EAX=EAX*EBX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets address of VARIABLE for operation ASSIGNMENT to EAX.
MOV [EAX],EBX                                     ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Moves value of EXPRESSION to VARIABLE.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Result] to EAX.
ADD EAX,-0008h                                    ; [VARIABLE -> id] - Adds offset for symbol [Result] to EAX. Now EAX contains address of symbol [Result].
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Result] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [Result] to STACK.
CALL PrintLineInt                                 ; [CALL -> id(ARGS)] - Calls procedure [PrintLineInt()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineInt()] from STACK.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Result] to EAX.
ADD EAX,-0008h                                    ; [VARIABLE -> id] - Adds offset for symbol [Result] to EAX. Now EAX contains address of symbol [Result].
PUSH EAX                                          ; [VARIABLE -> id] - Pushs address of variable [Result] to STACK.
MOV EAX,0000h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
PUSH EAX                                          ; [FACTOR -> num] - Pushs INT constant to STACK.
MOV EAX,0005h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Gets OPERAND O1 for operation [SUBTRACTION] to EAX.
SUB EAX,EBX                                       ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Executes operation EAX=EAX-EBX.
PUSH EAX                                          ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Pushs operation result to STACK.
MOV EAX,0000h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
PUSH EAX                                          ; [FACTOR -> num] - Pushs INT constant to STACK.
MOV EAX,0005h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Gets OPERAND O1 for operation [SUBTRACTION] to EAX.
SUB EAX,EBX                                       ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Executes operation EAX=EAX-EBX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [TERM -> TERM MUL_OPERATION FACTOR] - Gets OPERAND O1 for operation [MULTIPLICATION] to EAX.
IMUL EBX                                          ; [TERM -> TERM MUL_OPERATION FACTOR] - Executes operation EDX:EAX=EAX*EBX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets address of VARIABLE for operation ASSIGNMENT to EAX.
MOV [EAX],EBX                                     ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Moves value of EXPRESSION to VARIABLE.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Result] to EAX.
ADD EAX,-0008h                                    ; [VARIABLE -> id] - Adds offset for symbol [Result] to EAX. Now EAX contains address of symbol [Result].
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Result] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [Result] to STACK.
CALL PrintLineInt                                 ; [CALL -> id(ARGS)] - Calls procedure [PrintLineInt()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineInt()] from STACK.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Result] to EAX.
ADD EAX,-0008h                                    ; [VARIABLE -> id] - Adds offset for symbol [Result] to EAX. Now EAX contains address of symbol [Result].
PUSH EAX                                          ; [VARIABLE -> id] - Pushs address of variable [Result] to STACK.
MOV EAX,0000h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
PUSH EAX                                          ; [FACTOR -> num] - Pushs INT constant to STACK.
MOV EAX,0014h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Gets OPERAND O1 for operation [SUBTRACTION] to EAX.
SUB EAX,EBX                                       ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Executes operation EAX=EAX-EBX.
PUSH EAX                                          ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Pushs operation result to STACK.
MOV EAX,0000h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
PUSH EAX                                          ; [FACTOR -> num] - Pushs INT constant to STACK.
MOV EAX,0003h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Gets OPERAND O1 for operation [SUBTRACTION] to EAX.
SUB EAX,EBX                                       ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Executes operation EAX=EAX-EBX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [TERM -> TERM MUL_OPERATION FACTOR] - Gets OPERAND O1 for operation [DIVISION] to EAX.
CDQ                                               ; [TERM -> TERM MUL_OPERATION FACTOR] - Converts EAX to EDX:EAX.
IDIV EBX                                          ; [TERM -> TERM MUL_OPERATION FACTOR] - Executes operation EAX=EDX:EAX/EBX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets address of VARIABLE for operation ASSIGNMENT to EAX.
MOV [EAX],EBX                                     ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Moves value of EXPRESSION to VARIABLE.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Result] to EAX.
ADD EAX,-0008h                                    ; [VARIABLE -> id] - Adds offset for symbol [Result] to EAX. Now EAX contains address of symbol [Result].
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Result] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [Result] to STACK.
CALL PrintLineInt                                 ; [CALL -> id(ARGS)] - Calls procedure [PrintLineInt()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineInt()] from STACK.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Result] to EAX.
ADD EAX,-0008h                                    ; [VARIABLE -> id] - Adds offset for symbol [Result] to EAX. Now EAX contains address of symbol [Result].
PUSH EAX                                          ; [VARIABLE -> id] - Pushs address of variable [Result] to STACK.
MOV EAX,0000h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
PUSH EAX                                          ; [FACTOR -> num] - Pushs INT constant to STACK.
MOV EAX,0014h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Gets OPERAND O1 for operation [SUBTRACTION] to EAX.
SUB EAX,EBX                                       ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Executes operation EAX=EAX-EBX.
PUSH EAX                                          ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Pushs operation result to STACK.
MOV EAX,0003h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [TERM -> TERM MUL_OPERATION FACTOR] - Gets OPERAND O1 for operation [DIVISION] to EAX.
CDQ                                               ; [TERM -> TERM MUL_OPERATION FACTOR] - Converts EAX to EDX:EAX.
IDIV EBX                                          ; [TERM -> TERM MUL_OPERATION FACTOR] - Executes operation EAX=EDX:EAX/EBX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets address of VARIABLE for operation ASSIGNMENT to EAX.
MOV [EAX],EBX                                     ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Moves value of EXPRESSION to VARIABLE.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Result] to EAX.
ADD EAX,-0008h                                    ; [VARIABLE -> id] - Adds offset for symbol [Result] to EAX. Now EAX contains address of symbol [Result].
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Result] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [Result] to STACK.
CALL PrintLineInt                                 ; [CALL -> id(ARGS)] - Calls procedure [PrintLineInt()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineInt()] from STACK.
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
SUB ESP,0000h                                     ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Allocates memory for local variables.
MOV EAX,0002h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
PUSH EAX                                          ; [FACTOR -> num] - Pushs INT constant to STACK.
CALL TestForIf                                    ; [CALL -> id(ARGS)] - Calls procedure [TestForIf()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [TestForIf()] from STACK.
PUSH OFFSET _STRING_4                             ; [FACTOR -> string_literal] - Pushs address of LITERAL to STACK.
CALL PrintLineString                              ; [CALL -> id(ARGS)] - Calls procedure [PrintLineString()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineString()] from STACK.
MOV EAX,0003h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
PUSH EAX                                          ; [FACTOR -> num] - Pushs INT constant to STACK.
CALL TestForIf                                    ; [CALL -> id(ARGS)] - Calls procedure [TestForIf()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [TestForIf()] from STACK.
PUSH OFFSET _STRING_4                             ; [FACTOR -> string_literal] - Pushs address of LITERAL to STACK.
CALL PrintLineString                              ; [CALL -> id(ARGS)] - Calls procedure [PrintLineString()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineString()] from STACK.
MOV EAX,0004h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
PUSH EAX                                          ; [FACTOR -> num] - Pushs INT constant to STACK.
CALL TestForIf                                    ; [CALL -> id(ARGS)] - Calls procedure [TestForIf()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [TestForIf()] from STACK.
PUSH OFFSET _STRING_4                             ; [FACTOR -> string_literal] - Pushs address of LITERAL to STACK.
CALL PrintLineString                              ; [CALL -> id(ARGS)] - Calls procedure [PrintLineString()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineString()] from STACK.
MOV EAX,0005h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
PUSH EAX                                          ; [FACTOR -> num] - Pushs INT constant to STACK.
CALL TestForIf                                    ; [CALL -> id(ARGS)] - Calls procedure [TestForIf()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [TestForIf()] from STACK.
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
SUB ESP,0004h                                     ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Allocates memory for local variables.
MOV EAX,0001h                                     ; [CONST -> num] - Moves INT constant to EAX.
MOV ECX,EAX                                       ; [VARIABLE_DECLARATION -> TYPE_SPECIFIER id=CONST;] - Moves value of constant for variable [Counter1] to ECX.
MOV EAX,0001h                                     ; [CONST -> num] - Moves INT constant to EAX.
MOV [EBP-4],EAX                                   ; [VARIABLE_DECLARATION -> TYPE_SPECIFIER id=CONST;] - Moves value of constant for variable [Counter2] to STACK.
BEFORE_WHILE_Test3_1:                             ; [ITERATION_STATEMENT -> while (EXPRESSION) STATEMENT] - Label to BEGIN of WHILE block.
PUSH ECX                                          ; [VARIABLE -> id] - Pushs value of variable [Counter1] to STACK.
MOV EAX,000Ah                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Gets OPERAND O1 for operation COMPARE to EAX.
CMP EAX,EBX                                       ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Compares O1 to O2.
JLE TRUE_Test3_2                                  ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Jumps to TRUE label if O1<=O2
MOV EAX,0000h                                     ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Moves FALSE value (0) to EAX.
JMP FALSE_Test3_2                                 ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Jumps to FALSE label.
TRUE_Test3_2:                                     ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Label TRUE.
MOV EAX,0001h                                     ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Moves TRUE value (1) to EAX.
FALSE_Test3_2:                                    ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Label FALSE.
CMP EAX,0000h                                     ; [ITERATION_STATEMENT -> while (EXPRESSION) STATEMENT] - Compares value of EXPRESSION to 0.
JE AFTER_WHILE_Test3_1                            ; [ITERATION_STATEMENT -> while (EXPRESSION) STATEMENT] - Jumps to end of WHILE block.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Counter2] to EAX.
ADD EAX,-0004h                                    ; [VARIABLE -> id] - Adds offset for symbol [Counter2] to EAX. Now EAX contains address of symbol [Counter2].
PUSH EAX                                          ; [VARIABLE -> id] - Pushs address of variable [Counter2] to STACK.
MOV EAX,0001h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets address of VARIABLE for operation ASSIGNMENT to EAX.
MOV [EAX],EBX                                     ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Moves value of EXPRESSION to VARIABLE.
BEFORE_WHILE_Test3_3:                             ; [ITERATION_STATEMENT -> while (EXPRESSION) STATEMENT] - Label to BEGIN of WHILE block.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Counter2] to EAX.
ADD EAX,-0004h                                    ; [VARIABLE -> id] - Adds offset for symbol [Counter2] to EAX. Now EAX contains address of symbol [Counter2].
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Counter2] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [Counter2] to STACK.
MOV EAX,000Ah                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Gets OPERAND O1 for operation COMPARE to EAX.
CMP EAX,EBX                                       ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Compares O1 to O2.
JLE TRUE_Test3_4                                  ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Jumps to TRUE label if O1<=O2
MOV EAX,0000h                                     ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Moves FALSE value (0) to EAX.
JMP FALSE_Test3_4                                 ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Jumps to FALSE label.
TRUE_Test3_4:                                     ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Label TRUE.
MOV EAX,0001h                                     ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Moves TRUE value (1) to EAX.
FALSE_Test3_4:                                    ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Label FALSE.
CMP EAX,0000h                                     ; [ITERATION_STATEMENT -> while (EXPRESSION) STATEMENT] - Compares value of EXPRESSION to 0.
JE AFTER_WHILE_Test3_3                            ; [ITERATION_STATEMENT -> while (EXPRESSION) STATEMENT] - Jumps to end of WHILE block.
PUSH OFFSET _STRING_5                             ; [FACTOR -> string_literal] - Pushs address of LITERAL to STACK.
CALL PrintString                                  ; [CALL -> id(ARGS)] - Calls procedure [PrintString()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintString()] from STACK.
PUSH ECX                                          ; [VARIABLE -> id] - Pushs value of variable [Counter1] to STACK.
CALL PrintInt                                     ; [CALL -> id(ARGS)] - Calls procedure [PrintInt()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintInt()] from STACK.
PUSH OFFSET _STRING_6                             ; [FACTOR -> string_literal] - Pushs address of LITERAL to STACK.
CALL PrintString                                  ; [CALL -> id(ARGS)] - Calls procedure [PrintString()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintString()] from STACK.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Counter2] to EAX.
ADD EAX,-0004h                                    ; [VARIABLE -> id] - Adds offset for symbol [Counter2] to EAX. Now EAX contains address of symbol [Counter2].
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Counter2] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [Counter2] to STACK.
CALL PrintInt                                     ; [CALL -> id(ARGS)] - Calls procedure [PrintInt()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintInt()] from STACK.
PUSH OFFSET _STRING_7                             ; [FACTOR -> string_literal] - Pushs address of LITERAL to STACK.
CALL PrintLineString                              ; [CALL -> id(ARGS)] - Calls procedure [PrintLineString()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineString()] from STACK.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Counter2] to EAX.
ADD EAX,-0004h                                    ; [VARIABLE -> id] - Adds offset for symbol [Counter2] to EAX. Now EAX contains address of symbol [Counter2].
PUSH EAX                                          ; [VARIABLE -> id] - Pushs address of variable [Counter2] to STACK.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Counter2] to EAX.
ADD EAX,-0004h                                    ; [VARIABLE -> id] - Adds offset for symbol [Counter2] to EAX. Now EAX contains address of symbol [Counter2].
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Counter2] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [Counter2] to STACK.
MOV EAX,0001h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Gets OPERAND O1 for operation [ADDITION] to EAX.
ADD EAX,EBX                                       ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Executes operation EAX=EAX+EBX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets address of VARIABLE for operation ASSIGNMENT to EAX.
MOV [EAX],EBX                                     ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Moves value of EXPRESSION to VARIABLE.
JMP BEFORE_WHILE_Test3_3                          ; [ITERATION_STATEMENT -> while (EXPRESSION) STATEMENT] - Jumps to end of WHILE block.
AFTER_WHILE_Test3_3:                              ; [ITERATION_STATEMENT -> while (EXPRESSION) STATEMENT] - Label to END of WHILE block.
PUSH ECX                                          ; [VARIABLE -> id] - Pushs value of variable [Counter1] to STACK.
PUSH ECX                                          ; [VARIABLE -> id] - Pushs value of variable [Counter1] to STACK.
MOV EAX,0001h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Gets OPERAND O1 for operation [ADDITION] to EAX.
ADD EAX,EBX                                       ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Executes operation EAX=EAX+EBX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets address of VARIABLE for operation ASSIGNMENT to EAX.
MOV ECX,EBX                                       ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Moves value of EXPRESSION to VARIABLE.
JMP BEFORE_WHILE_Test3_1                          ; [ITERATION_STATEMENT -> while (EXPRESSION) STATEMENT] - Jumps to end of WHILE block.
AFTER_WHILE_Test3_1:                              ; [ITERATION_STATEMENT -> while (EXPRESSION) STATEMENT] - Label to END of WHILE block.
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
SUB ESP,0000h                                     ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Allocates memory for local variables.
MOV EAX,0008h                                     ; [CONST -> num] - Moves INT constant to EAX.
MOV ECX,EAX                                       ; [VARIABLE_DECLARATION -> TYPE_SPECIFIER id=CONST;] - Moves value of constant for variable [Value] to ECX.
PUSH ECX                                          ; [VARIABLE -> id] - Pushs value of variable [Value] to STACK.
MOV EAX,000Ah                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Gets OPERAND O1 for operation COMPARE to EAX.
CMP EAX,EBX                                       ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Compares O1 to O2.
JLE TRUE_Test4_2                                  ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Jumps to TRUE label if O1<=O2
MOV EAX,0000h                                     ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Moves FALSE value (0) to EAX.
JMP FALSE_Test4_2                                 ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Jumps to FALSE label.
TRUE_Test4_2:                                     ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Label TRUE.
MOV EAX,0001h                                     ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Moves TRUE value (1) to EAX.
FALSE_Test4_2:                                    ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Label FALSE.
CMP EAX,0000h                                     ; [SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT] - Compares value of EXPRESSION to 0.
JE AFTER_IF_Test4_1                               ; [SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT] - If value of EXPRESSION==0, jumps to END of IF block.
PUSH OFFSET _STRING_8                             ; [FACTOR -> string_literal] - Pushs address of LITERAL to STACK.
CALL PrintLineString                              ; [CALL -> id(ARGS)] - Calls procedure [PrintLineString()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineString()] from STACK.
AFTER_IF_Test4_1:                                 ; [SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT] - Label to END of IF block.
PUSH ECX                                          ; [VARIABLE -> id] - Pushs value of variable [Value] to STACK.
MOV EAX,000Ah                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Gets OPERAND O1 for operation COMPARE to EAX.
CMP EAX,EBX                                       ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Compares O1 to O2.
JL TRUE_Test4_4                                   ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Jumps to TRUE label if O1<O2.
MOV EAX,0000h                                     ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Moves FALSE value (0) to EAX.
JMP FALSE_Test4_4                                 ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Jumps to FALSE label.
TRUE_Test4_4:                                     ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Label TRUE.
MOV EAX,0001h                                     ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Moves TRUE value (1) to EAX.
FALSE_Test4_4:                                    ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Label FALSE.
CMP EAX,0000h                                     ; [SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT] - Compares value of EXPRESSION to 0.
JE AFTER_IF_Test4_3                               ; [SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT] - If value of EXPRESSION==0, jumps to END of IF block.
PUSH OFFSET _STRING_9                             ; [FACTOR -> string_literal] - Pushs address of LITERAL to STACK.
CALL PrintLineString                              ; [CALL -> id(ARGS)] - Calls procedure [PrintLineString()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineString()] from STACK.
AFTER_IF_Test4_3:                                 ; [SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT] - Label to END of IF block.
PUSH ECX                                          ; [VARIABLE -> id] - Pushs value of variable [Value] to STACK.
MOV EAX,0005h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Gets OPERAND O1 for operation COMPARE to EAX.
CMP EAX,EBX                                       ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Compares O1 to O2.
JGE TRUE_Test4_6                                  ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Jumps to TRUE label if O1>=O2
MOV EAX,0000h                                     ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Moves FALSE value (0) to EAX.
JMP FALSE_Test4_6                                 ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Jumps to FALSE label.
TRUE_Test4_6:                                     ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Label TRUE.
MOV EAX,0001h                                     ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Moves TRUE value (1) to EAX.
FALSE_Test4_6:                                    ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Label FALSE.
CMP EAX,0000h                                     ; [SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT] - Compares value of EXPRESSION to 0.
JE AFTER_IF_Test4_5                               ; [SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT] - If value of EXPRESSION==0, jumps to END of IF block.
PUSH OFFSET _STRING_10                            ; [FACTOR -> string_literal] - Pushs address of LITERAL to STACK.
CALL PrintLineString                              ; [CALL -> id(ARGS)] - Calls procedure [PrintLineString()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineString()] from STACK.
AFTER_IF_Test4_5:                                 ; [SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT] - Label to END of IF block.
PUSH ECX                                          ; [VARIABLE -> id] - Pushs value of variable [Value] to STACK.
MOV EAX,0005h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Gets OPERAND O1 for operation COMPARE to EAX.
CMP EAX,EBX                                       ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Compares O1 to O2.
JG TRUE_Test4_8                                   ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Jumps to TRUE label if O1>O2
MOV EAX,0000h                                     ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Moves FALSE value (0) to EAX.
JMP FALSE_Test4_8                                 ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Jumps to FALSE label.
TRUE_Test4_8:                                     ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Label TRUE.
MOV EAX,0001h                                     ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Moves TRUE value (1) to EAX.
FALSE_Test4_8:                                    ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Label FALSE.
CMP EAX,0000h                                     ; [SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT] - Compares value of EXPRESSION to 0.
JE AFTER_IF_Test4_7                               ; [SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT] - If value of EXPRESSION==0, jumps to END of IF block.
PUSH OFFSET _STRING_11                            ; [FACTOR -> string_literal] - Pushs address of LITERAL to STACK.
CALL PrintLineString                              ; [CALL -> id(ARGS)] - Calls procedure [PrintLineString()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineString()] from STACK.
AFTER_IF_Test4_7:                                 ; [SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT] - Label to END of IF block.
PUSH ECX                                          ; [VARIABLE -> id] - Pushs value of variable [Value] to STACK.
MOV EAX,0008h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Gets OPERAND O1 for operation COMPARE to EAX.
CMP EAX,EBX                                       ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Compares O1 to O2.
JE TRUE_Test4_10                                  ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Jumps to TRUE label if O1==O2
MOV EAX,0000h                                     ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Moves FALSE value (0) to EAX.
JMP FALSE_Test4_10                                ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Jumps to FALSE label.
TRUE_Test4_10:                                    ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Label TRUE.
MOV EAX,0001h                                     ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Moves TRUE value (1) to EAX.
FALSE_Test4_10:                                   ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Label FALSE.
CMP EAX,0000h                                     ; [SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT] - Compares value of EXPRESSION to 0.
JE AFTER_IF_Test4_9                               ; [SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT] - If value of EXPRESSION==0, jumps to END of IF block.
PUSH OFFSET _STRING_12                            ; [FACTOR -> string_literal] - Pushs address of LITERAL to STACK.
CALL PrintLineString                              ; [CALL -> id(ARGS)] - Calls procedure [PrintLineString()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineString()] from STACK.
AFTER_IF_Test4_9:                                 ; [SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT] - Label to END of IF block.
PUSH ECX                                          ; [VARIABLE -> id] - Pushs value of variable [Value] to STACK.
MOV EAX,0009h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Gets OPERAND O1 for operation COMPARE to EAX.
CMP EAX,EBX                                       ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Compares O1 to O2.
JNE TRUE_Test4_12                                 ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Jumps to TRUE label if O1!=O2
MOV EAX,0000h                                     ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Moves FALSE value (0) to EAX.
JMP FALSE_Test4_12                                ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Jumps to FALSE label.
TRUE_Test4_12:                                    ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Label TRUE.
MOV EAX,0001h                                     ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Moves TRUE value (1) to EAX.
FALSE_Test4_12:                                   ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Label FALSE.
CMP EAX,0000h                                     ; [SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT] - Compares value of EXPRESSION to 0.
JE AFTER_IF_Test4_11                              ; [SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT] - If value of EXPRESSION==0, jumps to END of IF block.
PUSH OFFSET _STRING_13                            ; [FACTOR -> string_literal] - Pushs address of LITERAL to STACK.
CALL PrintLineString                              ; [CALL -> id(ARGS)] - Calls procedure [PrintLineString()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineString()] from STACK.
AFTER_IF_Test4_11:                                ; [SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT] - Label to END of IF block.
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
SUB ESP,0028h                                     ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Allocates memory for local variables.
MOV EAX,0000h                                     ; [CONST -> num] - Moves INT constant to EAX.
MOV ECX,EAX                                       ; [VARIABLE_DECLARATION -> TYPE_SPECIFIER id=CONST;] - Moves value of constant for variable [Counter] to ECX.
MOV EAX,0003h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,0004h                                     ; [VARIABLE -> id[EXPRESSION]] - Moves SIZEOF(ARRAY_ITEM) for array [Values] to EBX.
MUL EBX                                           ; [VARIABLE -> id[EXPRESSION]] - Multiplies EXPRESSION*SIZEOF(ARRAY_ITEM) to calculate array index byte offset for array [Values].
MOV EBX,EAX                                       ; [VARIABLE -> id[EXPRESSION]] - Moves array index byte offset EXPRESSION*SIZEOF(ARRAY_ITEM) for array [Values] to EBX.
MOV EAX,EBP                                       ; [VARIABLE -> id[EXPRESSION]] - Moves EBP for local variable array [Values] to EAX.
ADD EAX,-0028h                                    ; [VARIABLE -> id[EXPRESSION]] - Adds local variable offset for local variable array [Values] to EAX. Now EAX contains base array address of array [Values].
ADD EAX,EBX                                       ; [VARIABLE -> id[EXPRESSION]] - Adds array index byt offset for array [Values] to EAX. Now EAX contains address of [Values[EXPRESSION]].
PUSH EAX                                          ; [VARIABLE -> id[EXPRESSION]] - Pushs address of variable [Values[EXPRESSION]] to STACK.
MOV EAX,0007h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets address of VARIABLE for operation ASSIGNMENT to EAX.
MOV [EAX],EBX                                     ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Moves value of EXPRESSION to VARIABLE.
MOV EAX,0008h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,0004h                                     ; [VARIABLE -> id[EXPRESSION]] - Moves SIZEOF(ARRAY_ITEM) for array [Values] to EBX.
MUL EBX                                           ; [VARIABLE -> id[EXPRESSION]] - Multiplies EXPRESSION*SIZEOF(ARRAY_ITEM) to calculate array index byte offset for array [Values].
MOV EBX,EAX                                       ; [VARIABLE -> id[EXPRESSION]] - Moves array index byte offset EXPRESSION*SIZEOF(ARRAY_ITEM) for array [Values] to EBX.
MOV EAX,EBP                                       ; [VARIABLE -> id[EXPRESSION]] - Moves EBP for local variable array [Values] to EAX.
ADD EAX,-0028h                                    ; [VARIABLE -> id[EXPRESSION]] - Adds local variable offset for local variable array [Values] to EAX. Now EAX contains base array address of array [Values].
ADD EAX,EBX                                       ; [VARIABLE -> id[EXPRESSION]] - Adds array index byt offset for array [Values] to EAX. Now EAX contains address of [Values[EXPRESSION]].
PUSH EAX                                          ; [VARIABLE -> id[EXPRESSION]] - Pushs address of variable [Values[EXPRESSION]] to STACK.
MOV EAX,0008h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets address of VARIABLE for operation ASSIGNMENT to EAX.
MOV [EAX],EBX                                     ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Moves value of EXPRESSION to VARIABLE.
MOV EAX,0009h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,0004h                                     ; [VARIABLE -> id[EXPRESSION]] - Moves SIZEOF(ARRAY_ITEM) for array [Values] to EBX.
MUL EBX                                           ; [VARIABLE -> id[EXPRESSION]] - Multiplies EXPRESSION*SIZEOF(ARRAY_ITEM) to calculate array index byte offset for array [Values].
MOV EBX,EAX                                       ; [VARIABLE -> id[EXPRESSION]] - Moves array index byte offset EXPRESSION*SIZEOF(ARRAY_ITEM) for array [Values] to EBX.
MOV EAX,EBP                                       ; [VARIABLE -> id[EXPRESSION]] - Moves EBP for local variable array [Values] to EAX.
ADD EAX,-0028h                                    ; [VARIABLE -> id[EXPRESSION]] - Adds local variable offset for local variable array [Values] to EAX. Now EAX contains base array address of array [Values].
ADD EAX,EBX                                       ; [VARIABLE -> id[EXPRESSION]] - Adds array index byt offset for array [Values] to EAX. Now EAX contains address of [Values[EXPRESSION]].
PUSH EAX                                          ; [VARIABLE -> id[EXPRESSION]] - Pushs address of variable [Values[EXPRESSION]] to STACK.
MOV EAX,000Ah                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets address of VARIABLE for operation ASSIGNMENT to EAX.
MOV [EAX],EBX                                     ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Moves value of EXPRESSION to VARIABLE.
MOV EAX,0001h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,0004h                                     ; [VARIABLE -> id[EXPRESSION]] - Moves SIZEOF(ARRAY_ITEM) for array [Values] to EBX.
MUL EBX                                           ; [VARIABLE -> id[EXPRESSION]] - Multiplies EXPRESSION*SIZEOF(ARRAY_ITEM) to calculate array index byte offset for array [Values].
MOV EBX,EAX                                       ; [VARIABLE -> id[EXPRESSION]] - Moves array index byte offset EXPRESSION*SIZEOF(ARRAY_ITEM) for array [Values] to EBX.
MOV EAX,EBP                                       ; [VARIABLE -> id[EXPRESSION]] - Moves EBP for local variable array [Values] to EAX.
ADD EAX,-0028h                                    ; [VARIABLE -> id[EXPRESSION]] - Adds local variable offset for local variable array [Values] to EAX. Now EAX contains base array address of array [Values].
ADD EAX,EBX                                       ; [VARIABLE -> id[EXPRESSION]] - Adds array index byt offset for array [Values] to EAX. Now EAX contains address of [Values[EXPRESSION]].
PUSH EAX                                          ; [VARIABLE -> id[EXPRESSION]] - Pushs address of variable [Values[EXPRESSION]] to STACK.
MOV EAX,0004h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets address of VARIABLE for operation ASSIGNMENT to EAX.
MOV [EAX],EBX                                     ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Moves value of EXPRESSION to VARIABLE.
MOV EAX,0002h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,0004h                                     ; [VARIABLE -> id[EXPRESSION]] - Moves SIZEOF(ARRAY_ITEM) for array [Values] to EBX.
MUL EBX                                           ; [VARIABLE -> id[EXPRESSION]] - Multiplies EXPRESSION*SIZEOF(ARRAY_ITEM) to calculate array index byte offset for array [Values].
MOV EBX,EAX                                       ; [VARIABLE -> id[EXPRESSION]] - Moves array index byte offset EXPRESSION*SIZEOF(ARRAY_ITEM) for array [Values] to EBX.
MOV EAX,EBP                                       ; [VARIABLE -> id[EXPRESSION]] - Moves EBP for local variable array [Values] to EAX.
ADD EAX,-0028h                                    ; [VARIABLE -> id[EXPRESSION]] - Adds local variable offset for local variable array [Values] to EAX. Now EAX contains base array address of array [Values].
ADD EAX,EBX                                       ; [VARIABLE -> id[EXPRESSION]] - Adds array index byt offset for array [Values] to EAX. Now EAX contains address of [Values[EXPRESSION]].
PUSH EAX                                          ; [VARIABLE -> id[EXPRESSION]] - Pushs address of variable [Values[EXPRESSION]] to STACK.
MOV EAX,0005h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets address of VARIABLE for operation ASSIGNMENT to EAX.
MOV [EAX],EBX                                     ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Moves value of EXPRESSION to VARIABLE.
MOV EAX,0004h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,0004h                                     ; [VARIABLE -> id[EXPRESSION]] - Moves SIZEOF(ARRAY_ITEM) for array [Values] to EBX.
MUL EBX                                           ; [VARIABLE -> id[EXPRESSION]] - Multiplies EXPRESSION*SIZEOF(ARRAY_ITEM) to calculate array index byte offset for array [Values].
MOV EBX,EAX                                       ; [VARIABLE -> id[EXPRESSION]] - Moves array index byte offset EXPRESSION*SIZEOF(ARRAY_ITEM) for array [Values] to EBX.
MOV EAX,EBP                                       ; [VARIABLE -> id[EXPRESSION]] - Moves EBP for local variable array [Values] to EAX.
ADD EAX,-0028h                                    ; [VARIABLE -> id[EXPRESSION]] - Adds local variable offset for local variable array [Values] to EAX. Now EAX contains base array address of array [Values].
ADD EAX,EBX                                       ; [VARIABLE -> id[EXPRESSION]] - Adds array index byt offset for array [Values] to EAX. Now EAX contains address of [Values[EXPRESSION]].
PUSH EAX                                          ; [VARIABLE -> id[EXPRESSION]] - Pushs address of variable [Values[EXPRESSION]] to STACK.
MOV EAX,0006h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets address of VARIABLE for operation ASSIGNMENT to EAX.
MOV [EAX],EBX                                     ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Moves value of EXPRESSION to VARIABLE.
MOV EAX,0007h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,0004h                                     ; [VARIABLE -> id[EXPRESSION]] - Moves SIZEOF(ARRAY_ITEM) for array [Values] to EBX.
MUL EBX                                           ; [VARIABLE -> id[EXPRESSION]] - Multiplies EXPRESSION*SIZEOF(ARRAY_ITEM) to calculate array index byte offset for array [Values].
MOV EBX,EAX                                       ; [VARIABLE -> id[EXPRESSION]] - Moves array index byte offset EXPRESSION*SIZEOF(ARRAY_ITEM) for array [Values] to EBX.
MOV EAX,EBP                                       ; [VARIABLE -> id[EXPRESSION]] - Moves EBP for local variable array [Values] to EAX.
ADD EAX,-0028h                                    ; [VARIABLE -> id[EXPRESSION]] - Adds local variable offset for local variable array [Values] to EAX. Now EAX contains base array address of array [Values].
ADD EAX,EBX                                       ; [VARIABLE -> id[EXPRESSION]] - Adds array index byt offset for array [Values] to EAX. Now EAX contains address of [Values[EXPRESSION]].
PUSH EAX                                          ; [VARIABLE -> id[EXPRESSION]] - Pushs address of variable [Values[EXPRESSION]] to STACK.
MOV EAX,0003h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets address of VARIABLE for operation ASSIGNMENT to EAX.
MOV [EAX],EBX                                     ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Moves value of EXPRESSION to VARIABLE.
MOV EAX,0006h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,0004h                                     ; [VARIABLE -> id[EXPRESSION]] - Moves SIZEOF(ARRAY_ITEM) for array [Values] to EBX.
MUL EBX                                           ; [VARIABLE -> id[EXPRESSION]] - Multiplies EXPRESSION*SIZEOF(ARRAY_ITEM) to calculate array index byte offset for array [Values].
MOV EBX,EAX                                       ; [VARIABLE -> id[EXPRESSION]] - Moves array index byte offset EXPRESSION*SIZEOF(ARRAY_ITEM) for array [Values] to EBX.
MOV EAX,EBP                                       ; [VARIABLE -> id[EXPRESSION]] - Moves EBP for local variable array [Values] to EAX.
ADD EAX,-0028h                                    ; [VARIABLE -> id[EXPRESSION]] - Adds local variable offset for local variable array [Values] to EAX. Now EAX contains base array address of array [Values].
ADD EAX,EBX                                       ; [VARIABLE -> id[EXPRESSION]] - Adds array index byt offset for array [Values] to EAX. Now EAX contains address of [Values[EXPRESSION]].
PUSH EAX                                          ; [VARIABLE -> id[EXPRESSION]] - Pushs address of variable [Values[EXPRESSION]] to STACK.
MOV EAX,0001h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets address of VARIABLE for operation ASSIGNMENT to EAX.
MOV [EAX],EBX                                     ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Moves value of EXPRESSION to VARIABLE.
MOV EAX,0005h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,0004h                                     ; [VARIABLE -> id[EXPRESSION]] - Moves SIZEOF(ARRAY_ITEM) for array [Values] to EBX.
MUL EBX                                           ; [VARIABLE -> id[EXPRESSION]] - Multiplies EXPRESSION*SIZEOF(ARRAY_ITEM) to calculate array index byte offset for array [Values].
MOV EBX,EAX                                       ; [VARIABLE -> id[EXPRESSION]] - Moves array index byte offset EXPRESSION*SIZEOF(ARRAY_ITEM) for array [Values] to EBX.
MOV EAX,EBP                                       ; [VARIABLE -> id[EXPRESSION]] - Moves EBP for local variable array [Values] to EAX.
ADD EAX,-0028h                                    ; [VARIABLE -> id[EXPRESSION]] - Adds local variable offset for local variable array [Values] to EAX. Now EAX contains base array address of array [Values].
ADD EAX,EBX                                       ; [VARIABLE -> id[EXPRESSION]] - Adds array index byt offset for array [Values] to EAX. Now EAX contains address of [Values[EXPRESSION]].
PUSH EAX                                          ; [VARIABLE -> id[EXPRESSION]] - Pushs address of variable [Values[EXPRESSION]] to STACK.
MOV EAX,0002h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets address of VARIABLE for operation ASSIGNMENT to EAX.
MOV [EAX],EBX                                     ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Moves value of EXPRESSION to VARIABLE.
MOV EAX,0000h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,0004h                                     ; [VARIABLE -> id[EXPRESSION]] - Moves SIZEOF(ARRAY_ITEM) for array [Values] to EBX.
MUL EBX                                           ; [VARIABLE -> id[EXPRESSION]] - Multiplies EXPRESSION*SIZEOF(ARRAY_ITEM) to calculate array index byte offset for array [Values].
MOV EBX,EAX                                       ; [VARIABLE -> id[EXPRESSION]] - Moves array index byte offset EXPRESSION*SIZEOF(ARRAY_ITEM) for array [Values] to EBX.
MOV EAX,EBP                                       ; [VARIABLE -> id[EXPRESSION]] - Moves EBP for local variable array [Values] to EAX.
ADD EAX,-0028h                                    ; [VARIABLE -> id[EXPRESSION]] - Adds local variable offset for local variable array [Values] to EAX. Now EAX contains base array address of array [Values].
ADD EAX,EBX                                       ; [VARIABLE -> id[EXPRESSION]] - Adds array index byt offset for array [Values] to EAX. Now EAX contains address of [Values[EXPRESSION]].
PUSH EAX                                          ; [VARIABLE -> id[EXPRESSION]] - Pushs address of variable [Values[EXPRESSION]] to STACK.
MOV EAX,0009h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets address of VARIABLE for operation ASSIGNMENT to EAX.
MOV [EAX],EBX                                     ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Moves value of EXPRESSION to VARIABLE.
PUSH OFFSET _STRING_14                            ; [FACTOR -> string_literal] - Pushs address of LITERAL to STACK.
CALL PrintLineString                              ; [CALL -> id(ARGS)] - Calls procedure [PrintLineString()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineString()] from STACK.
BEFORE_WHILE_Test5_1:                             ; [ITERATION_STATEMENT -> while (EXPRESSION) STATEMENT] - Label to BEGIN of WHILE block.
PUSH ECX                                          ; [VARIABLE -> id] - Pushs value of variable [Counter] to STACK.
MOV EAX,000Ah                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Gets OPERAND O1 for operation COMPARE to EAX.
CMP EAX,EBX                                       ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Compares O1 to O2.
JL TRUE_Test5_2                                   ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Jumps to TRUE label if O1<O2.
MOV EAX,0000h                                     ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Moves FALSE value (0) to EAX.
JMP FALSE_Test5_2                                 ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Jumps to FALSE label.
TRUE_Test5_2:                                     ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Label TRUE.
MOV EAX,0001h                                     ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Moves TRUE value (1) to EAX.
FALSE_Test5_2:                                    ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Label FALSE.
CMP EAX,0000h                                     ; [ITERATION_STATEMENT -> while (EXPRESSION) STATEMENT] - Compares value of EXPRESSION to 0.
JE AFTER_WHILE_Test5_1                            ; [ITERATION_STATEMENT -> while (EXPRESSION) STATEMENT] - Jumps to end of WHILE block.
PUSH ECX                                          ; [VARIABLE -> id] - Pushs value of variable [Counter] to STACK.
CALL PrintInt                                     ; [CALL -> id(ARGS)] - Calls procedure [PrintInt()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintInt()] from STACK.
PUSH OFFSET _STRING_15                            ; [FACTOR -> string_literal] - Pushs address of LITERAL to STACK.
CALL PrintString                                  ; [CALL -> id(ARGS)] - Calls procedure [PrintString()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintString()] from STACK.
PUSH ECX                                          ; [VARIABLE -> id] - Pushs value of variable [Counter] to STACK.
POP EAX                                           ; [VARIABLE -> id[EXPRESSION]] - Pops value of EXPRESSION for array [Values] to EAX.
MOV EBX,0004h                                     ; [VARIABLE -> id[EXPRESSION]] - Moves SIZEOF(ARRAY_ITEM) for array [Values] to EBX.
MUL EBX                                           ; [VARIABLE -> id[EXPRESSION]] - Multiplies EXPRESSION*SIZEOF(ARRAY_ITEM) to calculate array index byte offset for array [Values].
MOV EBX,EAX                                       ; [VARIABLE -> id[EXPRESSION]] - Moves array index byte offset EXPRESSION*SIZEOF(ARRAY_ITEM) for array [Values] to EBX.
MOV EAX,EBP                                       ; [VARIABLE -> id[EXPRESSION]] - Moves EBP for local variable array [Values] to EAX.
ADD EAX,-0028h                                    ; [VARIABLE -> id[EXPRESSION]] - Adds local variable offset for local variable array [Values] to EAX. Now EAX contains base array address of array [Values].
ADD EAX,EBX                                       ; [VARIABLE -> id[EXPRESSION]] - Adds array index byt offset for array [Values] to EAX. Now EAX contains address of [Values[EXPRESSION]].
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Values] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [Values] to STACK.
CALL PrintInt                                     ; [CALL -> id(ARGS)] - Calls procedure [PrintInt()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintInt()] from STACK.
PUSH OFFSET _STRING_7                             ; [FACTOR -> string_literal] - Pushs address of LITERAL to STACK.
CALL PrintLineString                              ; [CALL -> id(ARGS)] - Calls procedure [PrintLineString()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineString()] from STACK.
PUSH ECX                                          ; [VARIABLE -> id] - Pushs value of variable [Counter] to STACK.
PUSH ECX                                          ; [VARIABLE -> id] - Pushs value of variable [Counter] to STACK.
MOV EAX,0001h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Gets OPERAND O1 for operation [ADDITION] to EAX.
ADD EAX,EBX                                       ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Executes operation EAX=EAX+EBX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets address of VARIABLE for operation ASSIGNMENT to EAX.
MOV ECX,EBX                                       ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Moves value of EXPRESSION to VARIABLE.
JMP BEFORE_WHILE_Test5_1                          ; [ITERATION_STATEMENT -> while (EXPRESSION) STATEMENT] - Jumps to end of WHILE block.
AFTER_WHILE_Test5_1:                              ; [ITERATION_STATEMENT -> while (EXPRESSION) STATEMENT] - Label to END of WHILE block.
PUSH OFFSET _STRING_4                             ; [FACTOR -> string_literal] - Pushs address of LITERAL to STACK.
CALL PrintLineString                              ; [CALL -> id(ARGS)] - Calls procedure [PrintLineString()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineString()] from STACK.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Values] to EAX.
ADD EAX,-0028h                                    ; [VARIABLE -> id] - Adds local variable offset for local variable array [Values] to EAX. Now EAX contains base array address of array [Values].
PUSH EAX                                          ; [VARIABLE -> id] - Pushs address of variable [Values] to STACK.
MOV EAX,000Ah                                     ; [FACTOR -> num] - Moves INT constant to EAX.
PUSH EAX                                          ; [FACTOR -> num] - Pushs INT constant to STACK.
CALL Sort                                         ; [CALL -> id(ARGS)] - Calls procedure [Sort()].
ADD ESP,0008h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [Sort()] from STACK.
PUSH OFFSET _STRING_16                            ; [FACTOR -> string_literal] - Pushs address of LITERAL to STACK.
CALL PrintLineString                              ; [CALL -> id(ARGS)] - Calls procedure [PrintLineString()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineString()] from STACK.
PUSH ECX                                          ; [VARIABLE -> id] - Pushs value of variable [Counter] to STACK.
MOV EAX,0000h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets address of VARIABLE for operation ASSIGNMENT to EAX.
MOV ECX,EBX                                       ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Moves value of EXPRESSION to VARIABLE.
BEFORE_WHILE_Test5_3:                             ; [ITERATION_STATEMENT -> while (EXPRESSION) STATEMENT] - Label to BEGIN of WHILE block.
PUSH ECX                                          ; [VARIABLE -> id] - Pushs value of variable [Counter] to STACK.
MOV EAX,000Ah                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Gets OPERAND O1 for operation COMPARE to EAX.
CMP EAX,EBX                                       ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Compares O1 to O2.
JL TRUE_Test5_4                                   ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Jumps to TRUE label if O1<O2.
MOV EAX,0000h                                     ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Moves FALSE value (0) to EAX.
JMP FALSE_Test5_4                                 ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Jumps to FALSE label.
TRUE_Test5_4:                                     ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Label TRUE.
MOV EAX,0001h                                     ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Moves TRUE value (1) to EAX.
FALSE_Test5_4:                                    ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Label FALSE.
CMP EAX,0000h                                     ; [ITERATION_STATEMENT -> while (EXPRESSION) STATEMENT] - Compares value of EXPRESSION to 0.
JE AFTER_WHILE_Test5_3                            ; [ITERATION_STATEMENT -> while (EXPRESSION) STATEMENT] - Jumps to end of WHILE block.
PUSH ECX                                          ; [VARIABLE -> id] - Pushs value of variable [Counter] to STACK.
CALL PrintInt                                     ; [CALL -> id(ARGS)] - Calls procedure [PrintInt()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintInt()] from STACK.
PUSH OFFSET _STRING_15                            ; [FACTOR -> string_literal] - Pushs address of LITERAL to STACK.
CALL PrintString                                  ; [CALL -> id(ARGS)] - Calls procedure [PrintString()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintString()] from STACK.
PUSH ECX                                          ; [VARIABLE -> id] - Pushs value of variable [Counter] to STACK.
POP EAX                                           ; [VARIABLE -> id[EXPRESSION]] - Pops value of EXPRESSION for array [Values] to EAX.
MOV EBX,0004h                                     ; [VARIABLE -> id[EXPRESSION]] - Moves SIZEOF(ARRAY_ITEM) for array [Values] to EBX.
MUL EBX                                           ; [VARIABLE -> id[EXPRESSION]] - Multiplies EXPRESSION*SIZEOF(ARRAY_ITEM) to calculate array index byte offset for array [Values].
MOV EBX,EAX                                       ; [VARIABLE -> id[EXPRESSION]] - Moves array index byte offset EXPRESSION*SIZEOF(ARRAY_ITEM) for array [Values] to EBX.
MOV EAX,EBP                                       ; [VARIABLE -> id[EXPRESSION]] - Moves EBP for local variable array [Values] to EAX.
ADD EAX,-0028h                                    ; [VARIABLE -> id[EXPRESSION]] - Adds local variable offset for local variable array [Values] to EAX. Now EAX contains base array address of array [Values].
ADD EAX,EBX                                       ; [VARIABLE -> id[EXPRESSION]] - Adds array index byt offset for array [Values] to EAX. Now EAX contains address of [Values[EXPRESSION]].
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Values] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [Values] to STACK.
CALL PrintInt                                     ; [CALL -> id(ARGS)] - Calls procedure [PrintInt()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintInt()] from STACK.
PUSH OFFSET _STRING_7                             ; [FACTOR -> string_literal] - Pushs address of LITERAL to STACK.
CALL PrintLineString                              ; [CALL -> id(ARGS)] - Calls procedure [PrintLineString()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineString()] from STACK.
PUSH ECX                                          ; [VARIABLE -> id] - Pushs value of variable [Counter] to STACK.
PUSH ECX                                          ; [VARIABLE -> id] - Pushs value of variable [Counter] to STACK.
MOV EAX,0001h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Gets OPERAND O1 for operation [ADDITION] to EAX.
ADD EAX,EBX                                       ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Executes operation EAX=EAX+EBX.
MOV EBX,EAX                                       ; !!! OPTIMIZATION - PUSH EAX and POP EBX were REPLACED with MOV EBX,EAX.
POP EAX                                           ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets address of VARIABLE for operation ASSIGNMENT to EAX.
MOV ECX,EBX                                       ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Moves value of EXPRESSION to VARIABLE.
JMP BEFORE_WHILE_Test5_3                          ; [ITERATION_STATEMENT -> while (EXPRESSION) STATEMENT] - Jumps to end of WHILE block.
AFTER_WHILE_Test5_3:                              ; [ITERATION_STATEMENT -> while (EXPRESSION) STATEMENT] - Label to END of WHILE block.
Test5_EXIT:                                       ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Label to procedure [Test5()] exit code.
MOV ESP,EBP                                       ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Deallocates memory of local variables.
POP ECX                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of ECX.
POP EBX                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBX.
POP EBP                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBP.
RET                                               ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Exits procedure [Test5()].
Test5 ENDP                                        ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Ends procedure [Test5()].

Main PROC                                         ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Begins procedure [Main()].
PUSH EBP                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBP to STACK.
PUSH EBX                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBX to STACK.
PUSH ECX                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of ECX to STACK.
MOV EBP,ESP                                       ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Moves ESP to EBP to store begin address of LOCAL VARIABLES.
SUB ESP,0000h                                     ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Allocates memory for local variables.
PUSH OFFSET _STRING_17                            ; [FACTOR -> string_literal] - Pushs address of LITERAL to STACK.
CALL PrintLineString                              ; [CALL -> id(ARGS)] - Calls procedure [PrintLineString()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineString()] from STACK.
CALL Test5                                        ; [CALL -> id(ARGS)] - Calls procedure [Test5()].
ADD ESP,0000h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [Test5()] from STACK.
PUSH OFFSET _STRING_18                            ; [FACTOR -> string_literal] - Pushs address of LITERAL to STACK.
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
