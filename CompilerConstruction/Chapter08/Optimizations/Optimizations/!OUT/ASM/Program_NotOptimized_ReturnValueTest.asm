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
_STRING_1 BYTE "Abs1() IF !",0
_STRING_2 BYTE "Abs1() ELSE !",0
_STRING_3 BYTE "Abs2() IF !",0
_STRING_4 BYTE "Abs2() ELSE !",0
_STRING_5 BYTE "Abs3() IF !",0
_STRING_6 BYTE "Abs3() ELSE !",0
_STRING_7 BYTE "Abs4() IF !",0
_STRING_8 BYTE "Abs4() ELSE !",0
_STRING_9 BYTE "Value is LOWER than 10 !",0
_STRING_10 BYTE "Value is GREATER or EQUAL than 10 !",0
_STRING_11 BYTE "BEGIN of PROGRAM !",0
_STRING_12 BYTE "END of PROGRAM !",0
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

Abs1 PROC                                         ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Begins procedure [Abs1()].
PUSH EBP                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBP to STACK.
PUSH EBX                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBX to STACK.
MOV EBP,ESP                                       ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Moves ESP to EBP to store begin address of LOCAL VARIABLES.
SUB ESP,0000h                                     ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Allocates memory for local variables.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Value] to EAX.
ADD EAX,000Ch                                     ; [VARIABLE -> id] - Adds offset for symbol [Value] to EAX. Now EAX contains address of symbol [Value].
PUSH EAX                                          ; [VARIABLE -> id] - Pushs address of variable [Value] to STACK.
POP EAX                                           ; [VARIABLE -> [FACTOR -> VARIABLE]] - Gets address of variable [Value] to EAX.
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Value] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [Value] to STACK.
MOV EAX,0000h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
PUSH EAX                                          ; [FACTOR -> num] - Pushs INT constant to STACK.
POP EBX                                           ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Gets OPERAND O2 for operation COMPARE to EBX.
POP EAX                                           ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Gets OPERAND O1 for operation COMPARE to EAX.
CMP EAX,EBX                                       ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Compares O1 to O2.
JGE TRUE_Abs1_2                                   ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Jumps to TRUE label if O1>=O2
MOV EAX,0000h                                     ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Moves FALSE value (0) to EAX.
JMP FALSE_Abs1_2                                  ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Jumps to FALSE label.
TRUE_Abs1_2:                                      ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Label TRUE.
MOV EAX,0001h                                     ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Moves TRUE value (1) to EAX.
FALSE_Abs1_2:                                     ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Label FALSE.
PUSH EAX                                          ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Pushs result of operation COMPARE to STACK.
POP EAX                                           ; [SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT else STATEMENT] - Gets value of EXPRESSION to EAX.
CMP EAX,0000h                                     ; [SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT else STATEMENT] - Compares value of EXPRESSION to 0.
JE BEFORE_ELSE_Abs1_1                             ; [SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT else STATEMENT] - If value of EXPRESSION==0, jumps to ELSE block.
PUSH OFFSET _STRING_1                             ; [FACTOR -> string_literal] - Pushs address of LITERAL to STACK.
CALL PrintLineString                              ; [CALL -> id(ARGS)] - Calls procedure [PrintLineString()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineString()] from STACK.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Value] to EAX.
ADD EAX,000Ch                                     ; [VARIABLE -> id] - Adds offset for symbol [Value] to EAX. Now EAX contains address of symbol [Value].
PUSH EAX                                          ; [VARIABLE -> id] - Pushs address of variable [Value] to STACK.
POP EAX                                           ; [VARIABLE -> [FACTOR -> VARIABLE]] - Gets address of variable [Value] to EAX.
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Value] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [Value] to STACK.
POP EAX                                           ; [RETURN_STATEMENT -> return(EXPRESSION);] - Gets function [Abs1] result to EAX.
JMP Abs1_EXIT                                     ; [RETURN_STATEMENT -> return(EXPRESSION);] - Jumps to function [Abs1] exit code.
JMP AFTER_ELSE_Abs1_1                             ; [SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT else STATEMENT] - Jumps to END of ELSE block.
BEFORE_ELSE_Abs1_1:                               ; [SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT else STATEMENT] - Label to BEGIN of ELSE block.
PUSH OFFSET _STRING_2                             ; [FACTOR -> string_literal] - Pushs address of LITERAL to STACK.
CALL PrintLineString                              ; [CALL -> id(ARGS)] - Calls procedure [PrintLineString()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineString()] from STACK.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Value] to EAX.
ADD EAX,000Ch                                     ; [VARIABLE -> id] - Adds offset for symbol [Value] to EAX. Now EAX contains address of symbol [Value].
PUSH EAX                                          ; [VARIABLE -> id] - Pushs address of variable [Value] to STACK.
POP EAX                                           ; [VARIABLE -> [FACTOR -> VARIABLE]] - Gets address of variable [Value] to EAX.
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Value] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [Value] to STACK.
MOV EAX,0000h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
PUSH EAX                                          ; [FACTOR -> num] - Pushs INT constant to STACK.
MOV EAX,0001h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
PUSH EAX                                          ; [FACTOR -> num] - Pushs INT constant to STACK.
POP EBX                                           ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Gets OPERAND O2 for operation [SUBTRACTION] to EBX.
POP EAX                                           ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Gets OPERAND O1 for operation [SUBTRACTION] to EAX.
SUB EAX,EBX                                       ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Executes operation EAX=EAX-EBX.
PUSH EAX                                          ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Pushs operation result to STACK.
POP EBX                                           ; [TERM -> TERM MUL_OPERATION FACTOR] - Gets OPERAND O2 for operation [MULTIPLICATION] to EBX.
POP EAX                                           ; [TERM -> TERM MUL_OPERATION FACTOR] - Gets OPERAND O1 for operation [MULTIPLICATION] to EAX.
IMUL EBX                                          ; [TERM -> TERM MUL_OPERATION FACTOR] - Executes operation EDX:EAX=EAX*EBX.
PUSH EAX                                          ; [TERM -> TERM MUL_OPERATION FACTOR] - Pushs operation result to STACK.
POP EAX                                           ; [RETURN_STATEMENT -> return(EXPRESSION);] - Gets function [Abs1] result to EAX.
JMP Abs1_EXIT                                     ; [RETURN_STATEMENT -> return(EXPRESSION);] - Jumps to function [Abs1] exit code.
AFTER_ELSE_Abs1_1:                                ; [SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT else STATEMENT] - Label to END of ELSE block.
Abs1_EXIT:                                        ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Label to procedure [Abs1()] exit code.
MOV ESP,EBP                                       ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Deallocates memory of local variables.
POP EBX                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBX.
POP EBP                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBP.
RET                                               ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Exits procedure [Abs1()].
Abs1 ENDP                                         ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Ends procedure [Abs1()].

Abs2 PROC                                         ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Begins procedure [Abs2()].
PUSH EBP                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBP to STACK.
PUSH EBX                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBX to STACK.
MOV EBP,ESP                                       ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Moves ESP to EBP to store begin address of LOCAL VARIABLES.
SUB ESP,0000h                                     ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Allocates memory for local variables.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Value] to EAX.
ADD EAX,000Ch                                     ; [VARIABLE -> id] - Adds offset for symbol [Value] to EAX. Now EAX contains address of symbol [Value].
PUSH EAX                                          ; [VARIABLE -> id] - Pushs address of variable [Value] to STACK.
POP EAX                                           ; [VARIABLE -> [FACTOR -> VARIABLE]] - Gets address of variable [Value] to EAX.
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Value] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [Value] to STACK.
MOV EAX,0000h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
PUSH EAX                                          ; [FACTOR -> num] - Pushs INT constant to STACK.
POP EBX                                           ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Gets OPERAND O2 for operation COMPARE to EBX.
POP EAX                                           ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Gets OPERAND O1 for operation COMPARE to EAX.
CMP EAX,EBX                                       ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Compares O1 to O2.
JLE TRUE_Abs2_2                                   ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Jumps to TRUE label if O1<=O2
MOV EAX,0000h                                     ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Moves FALSE value (0) to EAX.
JMP FALSE_Abs2_2                                  ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Jumps to FALSE label.
TRUE_Abs2_2:                                      ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Label TRUE.
MOV EAX,0001h                                     ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Moves TRUE value (1) to EAX.
FALSE_Abs2_2:                                     ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Label FALSE.
PUSH EAX                                          ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Pushs result of operation COMPARE to STACK.
POP EAX                                           ; [SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT else STATEMENT] - Gets value of EXPRESSION to EAX.
CMP EAX,0000h                                     ; [SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT else STATEMENT] - Compares value of EXPRESSION to 0.
JE BEFORE_ELSE_Abs2_1                             ; [SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT else STATEMENT] - If value of EXPRESSION==0, jumps to ELSE block.
PUSH OFFSET _STRING_3                             ; [FACTOR -> string_literal] - Pushs address of LITERAL to STACK.
CALL PrintLineString                              ; [CALL -> id(ARGS)] - Calls procedure [PrintLineString()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineString()] from STACK.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Value] to EAX.
ADD EAX,000Ch                                     ; [VARIABLE -> id] - Adds offset for symbol [Value] to EAX. Now EAX contains address of symbol [Value].
PUSH EAX                                          ; [VARIABLE -> id] - Pushs address of variable [Value] to STACK.
POP EAX                                           ; [VARIABLE -> [FACTOR -> VARIABLE]] - Gets address of variable [Value] to EAX.
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Value] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [Value] to STACK.
MOV EAX,0000h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
PUSH EAX                                          ; [FACTOR -> num] - Pushs INT constant to STACK.
MOV EAX,0001h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
PUSH EAX                                          ; [FACTOR -> num] - Pushs INT constant to STACK.
POP EBX                                           ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Gets OPERAND O2 for operation [SUBTRACTION] to EBX.
POP EAX                                           ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Gets OPERAND O1 for operation [SUBTRACTION] to EAX.
SUB EAX,EBX                                       ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Executes operation EAX=EAX-EBX.
PUSH EAX                                          ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Pushs operation result to STACK.
POP EBX                                           ; [TERM -> TERM MUL_OPERATION FACTOR] - Gets OPERAND O2 for operation [MULTIPLICATION] to EBX.
POP EAX                                           ; [TERM -> TERM MUL_OPERATION FACTOR] - Gets OPERAND O1 for operation [MULTIPLICATION] to EAX.
IMUL EBX                                          ; [TERM -> TERM MUL_OPERATION FACTOR] - Executes operation EDX:EAX=EAX*EBX.
PUSH EAX                                          ; [TERM -> TERM MUL_OPERATION FACTOR] - Pushs operation result to STACK.
POP EAX                                           ; [RETURN_STATEMENT -> return(EXPRESSION);] - Gets function [Abs2] result to EAX.
JMP Abs2_EXIT                                     ; [RETURN_STATEMENT -> return(EXPRESSION);] - Jumps to function [Abs2] exit code.
JMP AFTER_ELSE_Abs2_1                             ; [SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT else STATEMENT] - Jumps to END of ELSE block.
BEFORE_ELSE_Abs2_1:                               ; [SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT else STATEMENT] - Label to BEGIN of ELSE block.
PUSH OFFSET _STRING_4                             ; [FACTOR -> string_literal] - Pushs address of LITERAL to STACK.
CALL PrintLineString                              ; [CALL -> id(ARGS)] - Calls procedure [PrintLineString()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineString()] from STACK.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Value] to EAX.
ADD EAX,000Ch                                     ; [VARIABLE -> id] - Adds offset for symbol [Value] to EAX. Now EAX contains address of symbol [Value].
PUSH EAX                                          ; [VARIABLE -> id] - Pushs address of variable [Value] to STACK.
POP EAX                                           ; [VARIABLE -> [FACTOR -> VARIABLE]] - Gets address of variable [Value] to EAX.
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Value] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [Value] to STACK.
POP EAX                                           ; [RETURN_STATEMENT -> return(EXPRESSION);] - Gets function [Abs2] result to EAX.
JMP Abs2_EXIT                                     ; [RETURN_STATEMENT -> return(EXPRESSION);] - Jumps to function [Abs2] exit code.
AFTER_ELSE_Abs2_1:                                ; [SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT else STATEMENT] - Label to END of ELSE block.
Abs2_EXIT:                                        ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Label to procedure [Abs2()] exit code.
MOV ESP,EBP                                       ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Deallocates memory of local variables.
POP EBX                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBX.
POP EBP                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBP.
RET                                               ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Exits procedure [Abs2()].
Abs2 ENDP                                         ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Ends procedure [Abs2()].

Abs3 PROC                                         ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Begins procedure [Abs3()].
PUSH EBP                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBP to STACK.
PUSH EBX                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBX to STACK.
MOV EBP,ESP                                       ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Moves ESP to EBP to store begin address of LOCAL VARIABLES.
SUB ESP,0000h                                     ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Allocates memory for local variables.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Value] to EAX.
ADD EAX,000Ch                                     ; [VARIABLE -> id] - Adds offset for symbol [Value] to EAX. Now EAX contains address of symbol [Value].
PUSH EAX                                          ; [VARIABLE -> id] - Pushs address of variable [Value] to STACK.
POP EAX                                           ; [VARIABLE -> [FACTOR -> VARIABLE]] - Gets address of variable [Value] to EAX.
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Value] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [Value] to STACK.
MOV EAX,0000h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
PUSH EAX                                          ; [FACTOR -> num] - Pushs INT constant to STACK.
POP EBX                                           ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Gets OPERAND O2 for operation COMPARE to EBX.
POP EAX                                           ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Gets OPERAND O1 for operation COMPARE to EAX.
CMP EAX,EBX                                       ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Compares O1 to O2.
JG TRUE_Abs3_2                                    ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Jumps to TRUE label if O1>O2
MOV EAX,0000h                                     ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Moves FALSE value (0) to EAX.
JMP FALSE_Abs3_2                                  ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Jumps to FALSE label.
TRUE_Abs3_2:                                      ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Label TRUE.
MOV EAX,0001h                                     ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Moves TRUE value (1) to EAX.
FALSE_Abs3_2:                                     ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Label FALSE.
PUSH EAX                                          ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Pushs result of operation COMPARE to STACK.
POP EAX                                           ; [SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT else STATEMENT] - Gets value of EXPRESSION to EAX.
CMP EAX,0000h                                     ; [SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT else STATEMENT] - Compares value of EXPRESSION to 0.
JE BEFORE_ELSE_Abs3_1                             ; [SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT else STATEMENT] - If value of EXPRESSION==0, jumps to ELSE block.
PUSH OFFSET _STRING_5                             ; [FACTOR -> string_literal] - Pushs address of LITERAL to STACK.
CALL PrintLineString                              ; [CALL -> id(ARGS)] - Calls procedure [PrintLineString()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineString()] from STACK.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Value] to EAX.
ADD EAX,000Ch                                     ; [VARIABLE -> id] - Adds offset for symbol [Value] to EAX. Now EAX contains address of symbol [Value].
PUSH EAX                                          ; [VARIABLE -> id] - Pushs address of variable [Value] to STACK.
POP EAX                                           ; [VARIABLE -> [FACTOR -> VARIABLE]] - Gets address of variable [Value] to EAX.
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Value] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [Value] to STACK.
POP EAX                                           ; [RETURN_STATEMENT -> return(EXPRESSION);] - Gets function [Abs3] result to EAX.
JMP Abs3_EXIT                                     ; [RETURN_STATEMENT -> return(EXPRESSION);] - Jumps to function [Abs3] exit code.
JMP AFTER_ELSE_Abs3_1                             ; [SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT else STATEMENT] - Jumps to END of ELSE block.
BEFORE_ELSE_Abs3_1:                               ; [SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT else STATEMENT] - Label to BEGIN of ELSE block.
PUSH OFFSET _STRING_6                             ; [FACTOR -> string_literal] - Pushs address of LITERAL to STACK.
CALL PrintLineString                              ; [CALL -> id(ARGS)] - Calls procedure [PrintLineString()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineString()] from STACK.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Value] to EAX.
ADD EAX,000Ch                                     ; [VARIABLE -> id] - Adds offset for symbol [Value] to EAX. Now EAX contains address of symbol [Value].
PUSH EAX                                          ; [VARIABLE -> id] - Pushs address of variable [Value] to STACK.
POP EAX                                           ; [VARIABLE -> [FACTOR -> VARIABLE]] - Gets address of variable [Value] to EAX.
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Value] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [Value] to STACK.
MOV EAX,0000h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
PUSH EAX                                          ; [FACTOR -> num] - Pushs INT constant to STACK.
MOV EAX,0001h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
PUSH EAX                                          ; [FACTOR -> num] - Pushs INT constant to STACK.
POP EBX                                           ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Gets OPERAND O2 for operation [SUBTRACTION] to EBX.
POP EAX                                           ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Gets OPERAND O1 for operation [SUBTRACTION] to EAX.
SUB EAX,EBX                                       ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Executes operation EAX=EAX-EBX.
PUSH EAX                                          ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Pushs operation result to STACK.
POP EBX                                           ; [TERM -> TERM MUL_OPERATION FACTOR] - Gets OPERAND O2 for operation [MULTIPLICATION] to EBX.
POP EAX                                           ; [TERM -> TERM MUL_OPERATION FACTOR] - Gets OPERAND O1 for operation [MULTIPLICATION] to EAX.
IMUL EBX                                          ; [TERM -> TERM MUL_OPERATION FACTOR] - Executes operation EDX:EAX=EAX*EBX.
PUSH EAX                                          ; [TERM -> TERM MUL_OPERATION FACTOR] - Pushs operation result to STACK.
POP EAX                                           ; [RETURN_STATEMENT -> return(EXPRESSION);] - Gets function [Abs3] result to EAX.
JMP Abs3_EXIT                                     ; [RETURN_STATEMENT -> return(EXPRESSION);] - Jumps to function [Abs3] exit code.
AFTER_ELSE_Abs3_1:                                ; [SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT else STATEMENT] - Label to END of ELSE block.
Abs3_EXIT:                                        ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Label to procedure [Abs3()] exit code.
MOV ESP,EBP                                       ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Deallocates memory of local variables.
POP EBX                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBX.
POP EBP                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBP.
RET                                               ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Exits procedure [Abs3()].
Abs3 ENDP                                         ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Ends procedure [Abs3()].

Abs4 PROC                                         ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Begins procedure [Abs4()].
PUSH EBP                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBP to STACK.
PUSH EBX                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBX to STACK.
MOV EBP,ESP                                       ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Moves ESP to EBP to store begin address of LOCAL VARIABLES.
SUB ESP,0000h                                     ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Allocates memory for local variables.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Value] to EAX.
ADD EAX,000Ch                                     ; [VARIABLE -> id] - Adds offset for symbol [Value] to EAX. Now EAX contains address of symbol [Value].
PUSH EAX                                          ; [VARIABLE -> id] - Pushs address of variable [Value] to STACK.
POP EAX                                           ; [VARIABLE -> [FACTOR -> VARIABLE]] - Gets address of variable [Value] to EAX.
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Value] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [Value] to STACK.
MOV EAX,0000h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
PUSH EAX                                          ; [FACTOR -> num] - Pushs INT constant to STACK.
POP EBX                                           ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Gets OPERAND O2 for operation COMPARE to EBX.
POP EAX                                           ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Gets OPERAND O1 for operation COMPARE to EAX.
CMP EAX,EBX                                       ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Compares O1 to O2.
JL TRUE_Abs4_2                                    ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Jumps to TRUE label if O1<O2.
MOV EAX,0000h                                     ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Moves FALSE value (0) to EAX.
JMP FALSE_Abs4_2                                  ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Jumps to FALSE label.
TRUE_Abs4_2:                                      ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Label TRUE.
MOV EAX,0001h                                     ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Moves TRUE value (1) to EAX.
FALSE_Abs4_2:                                     ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Label FALSE.
PUSH EAX                                          ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Pushs result of operation COMPARE to STACK.
POP EAX                                           ; [SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT else STATEMENT] - Gets value of EXPRESSION to EAX.
CMP EAX,0000h                                     ; [SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT else STATEMENT] - Compares value of EXPRESSION to 0.
JE BEFORE_ELSE_Abs4_1                             ; [SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT else STATEMENT] - If value of EXPRESSION==0, jumps to ELSE block.
PUSH OFFSET _STRING_7                             ; [FACTOR -> string_literal] - Pushs address of LITERAL to STACK.
CALL PrintLineString                              ; [CALL -> id(ARGS)] - Calls procedure [PrintLineString()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineString()] from STACK.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Value] to EAX.
ADD EAX,000Ch                                     ; [VARIABLE -> id] - Adds offset for symbol [Value] to EAX. Now EAX contains address of symbol [Value].
PUSH EAX                                          ; [VARIABLE -> id] - Pushs address of variable [Value] to STACK.
POP EAX                                           ; [VARIABLE -> [FACTOR -> VARIABLE]] - Gets address of variable [Value] to EAX.
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Value] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [Value] to STACK.
MOV EAX,0000h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
PUSH EAX                                          ; [FACTOR -> num] - Pushs INT constant to STACK.
MOV EAX,0001h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
PUSH EAX                                          ; [FACTOR -> num] - Pushs INT constant to STACK.
POP EBX                                           ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Gets OPERAND O2 for operation [SUBTRACTION] to EBX.
POP EAX                                           ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Gets OPERAND O1 for operation [SUBTRACTION] to EAX.
SUB EAX,EBX                                       ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Executes operation EAX=EAX-EBX.
PUSH EAX                                          ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Pushs operation result to STACK.
POP EBX                                           ; [TERM -> TERM MUL_OPERATION FACTOR] - Gets OPERAND O2 for operation [MULTIPLICATION] to EBX.
POP EAX                                           ; [TERM -> TERM MUL_OPERATION FACTOR] - Gets OPERAND O1 for operation [MULTIPLICATION] to EAX.
IMUL EBX                                          ; [TERM -> TERM MUL_OPERATION FACTOR] - Executes operation EDX:EAX=EAX*EBX.
PUSH EAX                                          ; [TERM -> TERM MUL_OPERATION FACTOR] - Pushs operation result to STACK.
POP EAX                                           ; [RETURN_STATEMENT -> return(EXPRESSION);] - Gets function [Abs4] result to EAX.
JMP Abs4_EXIT                                     ; [RETURN_STATEMENT -> return(EXPRESSION);] - Jumps to function [Abs4] exit code.
JMP AFTER_ELSE_Abs4_1                             ; [SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT else STATEMENT] - Jumps to END of ELSE block.
BEFORE_ELSE_Abs4_1:                               ; [SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT else STATEMENT] - Label to BEGIN of ELSE block.
PUSH OFFSET _STRING_8                             ; [FACTOR -> string_literal] - Pushs address of LITERAL to STACK.
CALL PrintLineString                              ; [CALL -> id(ARGS)] - Calls procedure [PrintLineString()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineString()] from STACK.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Value] to EAX.
ADD EAX,000Ch                                     ; [VARIABLE -> id] - Adds offset for symbol [Value] to EAX. Now EAX contains address of symbol [Value].
PUSH EAX                                          ; [VARIABLE -> id] - Pushs address of variable [Value] to STACK.
POP EAX                                           ; [VARIABLE -> [FACTOR -> VARIABLE]] - Gets address of variable [Value] to EAX.
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Value] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [Value] to STACK.
POP EAX                                           ; [RETURN_STATEMENT -> return(EXPRESSION);] - Gets function [Abs4] result to EAX.
JMP Abs4_EXIT                                     ; [RETURN_STATEMENT -> return(EXPRESSION);] - Jumps to function [Abs4] exit code.
AFTER_ELSE_Abs4_1:                                ; [SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT else STATEMENT] - Label to END of ELSE block.
Abs4_EXIT:                                        ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Label to procedure [Abs4()] exit code.
MOV ESP,EBP                                       ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Deallocates memory of local variables.
POP EBX                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBX.
POP EBP                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBP.
RET                                               ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Exits procedure [Abs4()].
Abs4 ENDP                                         ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Ends procedure [Abs4()].

AddValues PROC                                    ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Begins procedure [AddValues()].
PUSH EBP                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBP to STACK.
PUSH EBX                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBX to STACK.
MOV EBP,ESP                                       ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Moves ESP to EBP to store begin address of LOCAL VARIABLES.
SUB ESP,0000h                                     ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Allocates memory for local variables.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [X] to EAX.
ADD EAX,0010h                                     ; [VARIABLE -> id] - Adds offset for symbol [X] to EAX. Now EAX contains address of symbol [X].
PUSH EAX                                          ; [VARIABLE -> id] - Pushs address of variable [X] to STACK.
POP EAX                                           ; [VARIABLE -> [FACTOR -> VARIABLE]] - Gets address of variable [X] to EAX.
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [X] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [X] to STACK.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Y] to EAX.
ADD EAX,000Ch                                     ; [VARIABLE -> id] - Adds offset for symbol [Y] to EAX. Now EAX contains address of symbol [Y].
PUSH EAX                                          ; [VARIABLE -> id] - Pushs address of variable [Y] to STACK.
POP EAX                                           ; [VARIABLE -> [FACTOR -> VARIABLE]] - Gets address of variable [Y] to EAX.
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Y] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [Y] to STACK.
POP EBX                                           ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Gets OPERAND O2 for operation [ADDITION] to EBX.
POP EAX                                           ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Gets OPERAND O1 for operation [ADDITION] to EAX.
ADD EAX,EBX                                       ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Executes operation EAX=EAX+EBX.
PUSH EAX                                          ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Pushs operation result to STACK.
POP EAX                                           ; [RETURN_STATEMENT -> return(EXPRESSION);] - Gets function [AddValues] result to EAX.
JMP AddValues_EXIT                                ; [RETURN_STATEMENT -> return(EXPRESSION);] - Jumps to function [AddValues] exit code.
AddValues_EXIT:                                   ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Label to procedure [AddValues()] exit code.
MOV ESP,EBP                                       ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Deallocates memory of local variables.
POP EBX                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBX.
POP EBP                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBP.
RET                                               ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Exits procedure [AddValues()].
AddValues ENDP                                    ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Ends procedure [AddValues()].

CalculateFactorial PROC                           ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Begins procedure [CalculateFactorial()].
PUSH EBP                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBP to STACK.
PUSH EBX                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBX to STACK.
MOV EBP,ESP                                       ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Moves ESP to EBP to store begin address of LOCAL VARIABLES.
SUB ESP,0000h                                     ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Allocates memory for local variables.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Value] to EAX.
ADD EAX,000Ch                                     ; [VARIABLE -> id] - Adds offset for symbol [Value] to EAX. Now EAX contains address of symbol [Value].
PUSH EAX                                          ; [VARIABLE -> id] - Pushs address of variable [Value] to STACK.
POP EAX                                           ; [VARIABLE -> [FACTOR -> VARIABLE]] - Gets address of variable [Value] to EAX.
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Value] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [Value] to STACK.
MOV EAX,0000h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
PUSH EAX                                          ; [FACTOR -> num] - Pushs INT constant to STACK.
POP EBX                                           ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Gets OPERAND O2 for operation COMPARE to EBX.
POP EAX                                           ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Gets OPERAND O1 for operation COMPARE to EAX.
CMP EAX,EBX                                       ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Compares O1 to O2.
JE TRUE_CalculateFactorial_2                      ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Jumps to TRUE label if O1==O2
MOV EAX,0000h                                     ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Moves FALSE value (0) to EAX.
JMP FALSE_CalculateFactorial_2                    ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Jumps to FALSE label.
TRUE_CalculateFactorial_2:                        ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Label TRUE.
MOV EAX,0001h                                     ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Moves TRUE value (1) to EAX.
FALSE_CalculateFactorial_2:                       ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Label FALSE.
PUSH EAX                                          ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Pushs result of operation COMPARE to STACK.
POP EAX                                           ; [SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT] - Gets value of EXPRESSION to EAX.
CMP EAX,0000h                                     ; [SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT] - Compares value of EXPRESSION to 0.
JE AFTER_IF_CalculateFactorial_1                  ; [SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT] - If value of EXPRESSION==0, jumps to END of IF block.
MOV EAX,0001h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
PUSH EAX                                          ; [FACTOR -> num] - Pushs INT constant to STACK.
POP EAX                                           ; [RETURN_STATEMENT -> return(EXPRESSION);] - Gets function [CalculateFactorial] result to EAX.
JMP CalculateFactorial_EXIT                       ; [RETURN_STATEMENT -> return(EXPRESSION);] - Jumps to function [CalculateFactorial] exit code.
AFTER_IF_CalculateFactorial_1:                    ; [SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT] - Label to END of IF block.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Value] to EAX.
ADD EAX,000Ch                                     ; [VARIABLE -> id] - Adds offset for symbol [Value] to EAX. Now EAX contains address of symbol [Value].
PUSH EAX                                          ; [VARIABLE -> id] - Pushs address of variable [Value] to STACK.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Value] to EAX.
ADD EAX,000Ch                                     ; [VARIABLE -> id] - Adds offset for symbol [Value] to EAX. Now EAX contains address of symbol [Value].
PUSH EAX                                          ; [VARIABLE -> id] - Pushs address of variable [Value] to STACK.
POP EAX                                           ; [VARIABLE -> [FACTOR -> VARIABLE]] - Gets address of variable [Value] to EAX.
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Value] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [Value] to STACK.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Value] to EAX.
ADD EAX,000Ch                                     ; [VARIABLE -> id] - Adds offset for symbol [Value] to EAX. Now EAX contains address of symbol [Value].
PUSH EAX                                          ; [VARIABLE -> id] - Pushs address of variable [Value] to STACK.
POP EAX                                           ; [VARIABLE -> [FACTOR -> VARIABLE]] - Gets address of variable [Value] to EAX.
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Value] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [Value] to STACK.
MOV EAX,0001h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
PUSH EAX                                          ; [FACTOR -> num] - Pushs INT constant to STACK.
POP EBX                                           ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Gets OPERAND O2 for operation [SUBTRACTION] to EBX.
POP EAX                                           ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Gets OPERAND O1 for operation [SUBTRACTION] to EAX.
SUB EAX,EBX                                       ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Executes operation EAX=EAX-EBX.
PUSH EAX                                          ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Pushs operation result to STACK.
CALL CalculateFactorial                           ; [CALL -> id(ARGS)] - Calls procedure [CalculateFactorial()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [CalculateFactorial()] from STACK.
PUSH EAX                                          ; [CALL -> id(ARGS)] - Pushs RETURN VALUE of procedure [CalculateFactorial()] to STACK.
POP EBX                                           ; [TERM -> TERM MUL_OPERATION FACTOR] - Gets OPERAND O2 for operation [MULTIPLICATION] to EBX.
POP EAX                                           ; [TERM -> TERM MUL_OPERATION FACTOR] - Gets OPERAND O1 for operation [MULTIPLICATION] to EAX.
IMUL EBX                                          ; [TERM -> TERM MUL_OPERATION FACTOR] - Executes operation EDX:EAX=EAX*EBX.
PUSH EAX                                          ; [TERM -> TERM MUL_OPERATION FACTOR] - Pushs operation result to STACK.
POP EBX                                           ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets value of EXPRESSION for operation ASSIGNMENT to EBX.
POP EAX                                           ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets address of VARIABLE for operation ASSIGNMENT to EAX.
MOV [EAX],EBX                                     ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Moves value of EXPRESSION to VARIABLE.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Value] to EAX.
ADD EAX,000Ch                                     ; [VARIABLE -> id] - Adds offset for symbol [Value] to EAX. Now EAX contains address of symbol [Value].
PUSH EAX                                          ; [VARIABLE -> id] - Pushs address of variable [Value] to STACK.
POP EAX                                           ; [VARIABLE -> [FACTOR -> VARIABLE]] - Gets address of variable [Value] to EAX.
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Value] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [Value] to STACK.
POP EAX                                           ; [RETURN_STATEMENT -> return(EXPRESSION);] - Gets function [CalculateFactorial] result to EAX.
JMP CalculateFactorial_EXIT                       ; [RETURN_STATEMENT -> return(EXPRESSION);] - Jumps to function [CalculateFactorial] exit code.
CalculateFactorial_EXIT:                          ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Label to procedure [CalculateFactorial()] exit code.
MOV ESP,EBP                                       ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Deallocates memory of local variables.
POP EBX                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBX.
POP EBP                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBP.
RET                                               ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Exits procedure [CalculateFactorial()].
CalculateFactorial ENDP                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Ends procedure [CalculateFactorial()].

CompareTo10 PROC                                  ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Begins procedure [CompareTo10()].
PUSH EBP                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBP to STACK.
PUSH EBX                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBX to STACK.
MOV EBP,ESP                                       ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Moves ESP to EBP to store begin address of LOCAL VARIABLES.
SUB ESP,0000h                                     ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Allocates memory for local variables.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Value] to EAX.
ADD EAX,000Ch                                     ; [VARIABLE -> id] - Adds offset for symbol [Value] to EAX. Now EAX contains address of symbol [Value].
PUSH EAX                                          ; [VARIABLE -> id] - Pushs address of variable [Value] to STACK.
POP EAX                                           ; [VARIABLE -> [FACTOR -> VARIABLE]] - Gets address of variable [Value] to EAX.
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Value] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [Value] to STACK.
MOV EAX,000Ah                                     ; [FACTOR -> num] - Moves INT constant to EAX.
PUSH EAX                                          ; [FACTOR -> num] - Pushs INT constant to STACK.
POP EBX                                           ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Gets OPERAND O2 for operation COMPARE to EBX.
POP EAX                                           ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Gets OPERAND O1 for operation COMPARE to EAX.
CMP EAX,EBX                                       ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Compares O1 to O2.
JL TRUE_CompareTo10_2                             ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Jumps to TRUE label if O1<O2.
MOV EAX,0000h                                     ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Moves FALSE value (0) to EAX.
JMP FALSE_CompareTo10_2                           ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Jumps to FALSE label.
TRUE_CompareTo10_2:                               ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Label TRUE.
MOV EAX,0001h                                     ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Moves TRUE value (1) to EAX.
FALSE_CompareTo10_2:                              ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Label FALSE.
PUSH EAX                                          ; [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Pushs result of operation COMPARE to STACK.
POP EAX                                           ; [SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT] - Gets value of EXPRESSION to EAX.
CMP EAX,0000h                                     ; [SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT] - Compares value of EXPRESSION to 0.
JE AFTER_IF_CompareTo10_1                         ; [SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT] - If value of EXPRESSION==0, jumps to END of IF block.
PUSH OFFSET _STRING_9                             ; [FACTOR -> string_literal] - Pushs address of LITERAL to STACK.
CALL PrintLineString                              ; [CALL -> id(ARGS)] - Calls procedure [PrintLineString()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineString()] from STACK.
JMP CompareTo10_EXIT                              ; [RETURN_STATEMENT -> return(EXPRESSION);] - Jumps to function [CompareTo10] exit code.
AFTER_IF_CompareTo10_1:                           ; [SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT] - Label to END of IF block.
PUSH OFFSET _STRING_10                            ; [FACTOR -> string_literal] - Pushs address of LITERAL to STACK.
CALL PrintLineString                              ; [CALL -> id(ARGS)] - Calls procedure [PrintLineString()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineString()] from STACK.
JMP CompareTo10_EXIT                              ; [RETURN_STATEMENT -> return(EXPRESSION);] - Jumps to function [CompareTo10] exit code.
CompareTo10_EXIT:                                 ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Label to procedure [CompareTo10()] exit code.
MOV ESP,EBP                                       ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Deallocates memory of local variables.
POP EBX                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBX.
POP EBP                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBP.
RET                                               ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Exits procedure [CompareTo10()].
CompareTo10 ENDP                                  ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Ends procedure [CompareTo10()].

Test1 PROC                                        ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Begins procedure [Test1()].
PUSH EBP                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBP to STACK.
PUSH EBX                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBX to STACK.
MOV EBP,ESP                                       ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Moves ESP to EBP to store begin address of LOCAL VARIABLES.
SUB ESP,0004h                                     ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Allocates memory for local variables.
MOV EAX,000Ah                                     ; [FACTOR -> num] - Moves INT constant to EAX.
PUSH EAX                                          ; [FACTOR -> num] - Pushs INT constant to STACK.
MOV EAX,0002h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
PUSH EAX                                          ; [FACTOR -> num] - Pushs INT constant to STACK.
CALL AddValues                                    ; [CALL -> id(ARGS)] - Calls procedure [AddValues()].
ADD ESP,0008h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [AddValues()] from STACK.
PUSH EAX                                          ; [CALL -> id(ARGS)] - Pushs RETURN VALUE of procedure [AddValues()] to STACK.
POP EAX                                           ; [EXPRESSION_STATEMENT -> CALL;] - Removes UNUSED RETURN VALUE from STACK.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [RetValue] to EAX.
ADD EAX,-0004h                                    ; [VARIABLE -> id] - Adds offset for symbol [RetValue] to EAX. Now EAX contains address of symbol [RetValue].
PUSH EAX                                          ; [VARIABLE -> id] - Pushs address of variable [RetValue] to STACK.
MOV EAX,000Ah                                     ; [FACTOR -> num] - Moves INT constant to EAX.
PUSH EAX                                          ; [FACTOR -> num] - Pushs INT constant to STACK.
MOV EAX,0002h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
PUSH EAX                                          ; [FACTOR -> num] - Pushs INT constant to STACK.
CALL AddValues                                    ; [CALL -> id(ARGS)] - Calls procedure [AddValues()].
ADD ESP,0008h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [AddValues()] from STACK.
PUSH EAX                                          ; [CALL -> id(ARGS)] - Pushs RETURN VALUE of procedure [AddValues()] to STACK.
POP EBX                                           ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets value of EXPRESSION for operation ASSIGNMENT to EBX.
POP EAX                                           ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets address of VARIABLE for operation ASSIGNMENT to EAX.
MOV [EAX],EBX                                     ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Moves value of EXPRESSION to VARIABLE.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [RetValue] to EAX.
ADD EAX,-0004h                                    ; [VARIABLE -> id] - Adds offset for symbol [RetValue] to EAX. Now EAX contains address of symbol [RetValue].
PUSH EAX                                          ; [VARIABLE -> id] - Pushs address of variable [RetValue] to STACK.
POP EAX                                           ; [VARIABLE -> [FACTOR -> VARIABLE]] - Gets address of variable [RetValue] to EAX.
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [RetValue] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [RetValue] to STACK.
CALL PrintLineInt                                 ; [CALL -> id(ARGS)] - Calls procedure [PrintLineInt()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineInt()] from STACK.
MOV EAX,000Ah                                     ; [FACTOR -> num] - Moves INT constant to EAX.
PUSH EAX                                          ; [FACTOR -> num] - Pushs INT constant to STACK.
MOV EAX,0002h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
PUSH EAX                                          ; [FACTOR -> num] - Pushs INT constant to STACK.
CALL AddValues                                    ; [CALL -> id(ARGS)] - Calls procedure [AddValues()].
ADD ESP,0008h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [AddValues()] from STACK.
PUSH EAX                                          ; [CALL -> id(ARGS)] - Pushs RETURN VALUE of procedure [AddValues()] to STACK.
POP EAX                                           ; [EXPRESSION_STATEMENT -> CALL;] - Removes UNUSED RETURN VALUE from STACK.
Test1_EXIT:                                       ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Label to procedure [Test1()] exit code.
MOV ESP,EBP                                       ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Deallocates memory of local variables.
POP EBX                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBX.
POP EBP                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBP.
RET                                               ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Exits procedure [Test1()].
Test1 ENDP                                        ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Ends procedure [Test1()].

Test2 PROC                                        ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Begins procedure [Test2()].
PUSH EBP                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBP to STACK.
PUSH EBX                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBX to STACK.
MOV EBP,ESP                                       ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Moves ESP to EBP to store begin address of LOCAL VARIABLES.
SUB ESP,0004h                                     ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Allocates memory for local variables.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Factorial] to EAX.
ADD EAX,-0004h                                    ; [VARIABLE -> id] - Adds offset for symbol [Factorial] to EAX. Now EAX contains address of symbol [Factorial].
PUSH EAX                                          ; [VARIABLE -> id] - Pushs address of variable [Factorial] to STACK.
MOV EAX,000Ah                                     ; [FACTOR -> num] - Moves INT constant to EAX.
PUSH EAX                                          ; [FACTOR -> num] - Pushs INT constant to STACK.
CALL CalculateFactorial                           ; [CALL -> id(ARGS)] - Calls procedure [CalculateFactorial()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [CalculateFactorial()] from STACK.
PUSH EAX                                          ; [CALL -> id(ARGS)] - Pushs RETURN VALUE of procedure [CalculateFactorial()] to STACK.
POP EBX                                           ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets value of EXPRESSION for operation ASSIGNMENT to EBX.
POP EAX                                           ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets address of VARIABLE for operation ASSIGNMENT to EAX.
MOV [EAX],EBX                                     ; [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Moves value of EXPRESSION to VARIABLE.
MOV EAX,EBP                                       ; [VARIABLE -> id] - Moves EBP for local variable array [Factorial] to EAX.
ADD EAX,-0004h                                    ; [VARIABLE -> id] - Adds offset for symbol [Factorial] to EAX. Now EAX contains address of symbol [Factorial].
PUSH EAX                                          ; [VARIABLE -> id] - Pushs address of variable [Factorial] to STACK.
POP EAX                                           ; [VARIABLE -> [FACTOR -> VARIABLE]] - Gets address of variable [Factorial] to EAX.
MOV EAX,[EAX]                                     ; [VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [Factorial] from address of variable.
PUSH EAX                                          ; [VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [Factorial] to STACK.
CALL PrintLineInt                                 ; [CALL -> id(ARGS)] - Calls procedure [PrintLineInt()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineInt()] from STACK.
Test2_EXIT:                                       ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Label to procedure [Test2()] exit code.
MOV ESP,EBP                                       ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Deallocates memory of local variables.
POP EBX                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBX.
POP EBP                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBP.
RET                                               ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Exits procedure [Test2()].
Test2 ENDP                                        ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Ends procedure [Test2()].

Test3 PROC                                        ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Begins procedure [Test3()].
PUSH EBP                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBP to STACK.
PUSH EBX                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBX to STACK.
MOV EBP,ESP                                       ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Moves ESP to EBP to store begin address of LOCAL VARIABLES.
SUB ESP,0000h                                     ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Allocates memory for local variables.
MOV EAX,001Eh                                     ; [FACTOR -> num] - Moves INT constant to EAX.
PUSH EAX                                          ; [FACTOR -> num] - Pushs INT constant to STACK.
CALL Abs1                                         ; [CALL -> id(ARGS)] - Calls procedure [Abs1()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [Abs1()] from STACK.
PUSH EAX                                          ; [CALL -> id(ARGS)] - Pushs RETURN VALUE of procedure [Abs1()] to STACK.
CALL PrintLineInt                                 ; [CALL -> id(ARGS)] - Calls procedure [PrintLineInt()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineInt()] from STACK.
MOV EAX,001Eh                                     ; [FACTOR -> num] - Moves INT constant to EAX.
PUSH EAX                                          ; [FACTOR -> num] - Pushs INT constant to STACK.
MOV EAX,0000h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
PUSH EAX                                          ; [FACTOR -> num] - Pushs INT constant to STACK.
MOV EAX,0001h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
PUSH EAX                                          ; [FACTOR -> num] - Pushs INT constant to STACK.
POP EBX                                           ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Gets OPERAND O2 for operation [SUBTRACTION] to EBX.
POP EAX                                           ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Gets OPERAND O1 for operation [SUBTRACTION] to EAX.
SUB EAX,EBX                                       ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Executes operation EAX=EAX-EBX.
PUSH EAX                                          ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Pushs operation result to STACK.
POP EBX                                           ; [TERM -> TERM MUL_OPERATION FACTOR] - Gets OPERAND O2 for operation [MULTIPLICATION] to EBX.
POP EAX                                           ; [TERM -> TERM MUL_OPERATION FACTOR] - Gets OPERAND O1 for operation [MULTIPLICATION] to EAX.
IMUL EBX                                          ; [TERM -> TERM MUL_OPERATION FACTOR] - Executes operation EDX:EAX=EAX*EBX.
PUSH EAX                                          ; [TERM -> TERM MUL_OPERATION FACTOR] - Pushs operation result to STACK.
CALL Abs1                                         ; [CALL -> id(ARGS)] - Calls procedure [Abs1()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [Abs1()] from STACK.
PUSH EAX                                          ; [CALL -> id(ARGS)] - Pushs RETURN VALUE of procedure [Abs1()] to STACK.
CALL PrintLineInt                                 ; [CALL -> id(ARGS)] - Calls procedure [PrintLineInt()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineInt()] from STACK.
MOV EAX,0000h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
PUSH EAX                                          ; [FACTOR -> num] - Pushs INT constant to STACK.
CALL Abs1                                         ; [CALL -> id(ARGS)] - Calls procedure [Abs1()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [Abs1()] from STACK.
PUSH EAX                                          ; [CALL -> id(ARGS)] - Pushs RETURN VALUE of procedure [Abs1()] to STACK.
CALL PrintLineInt                                 ; [CALL -> id(ARGS)] - Calls procedure [PrintLineInt()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineInt()] from STACK.
MOV EAX,001Eh                                     ; [FACTOR -> num] - Moves INT constant to EAX.
PUSH EAX                                          ; [FACTOR -> num] - Pushs INT constant to STACK.
CALL Abs2                                         ; [CALL -> id(ARGS)] - Calls procedure [Abs2()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [Abs2()] from STACK.
PUSH EAX                                          ; [CALL -> id(ARGS)] - Pushs RETURN VALUE of procedure [Abs2()] to STACK.
CALL PrintLineInt                                 ; [CALL -> id(ARGS)] - Calls procedure [PrintLineInt()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineInt()] from STACK.
MOV EAX,001Eh                                     ; [FACTOR -> num] - Moves INT constant to EAX.
PUSH EAX                                          ; [FACTOR -> num] - Pushs INT constant to STACK.
MOV EAX,0000h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
PUSH EAX                                          ; [FACTOR -> num] - Pushs INT constant to STACK.
MOV EAX,0001h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
PUSH EAX                                          ; [FACTOR -> num] - Pushs INT constant to STACK.
POP EBX                                           ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Gets OPERAND O2 for operation [SUBTRACTION] to EBX.
POP EAX                                           ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Gets OPERAND O1 for operation [SUBTRACTION] to EAX.
SUB EAX,EBX                                       ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Executes operation EAX=EAX-EBX.
PUSH EAX                                          ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Pushs operation result to STACK.
POP EBX                                           ; [TERM -> TERM MUL_OPERATION FACTOR] - Gets OPERAND O2 for operation [MULTIPLICATION] to EBX.
POP EAX                                           ; [TERM -> TERM MUL_OPERATION FACTOR] - Gets OPERAND O1 for operation [MULTIPLICATION] to EAX.
IMUL EBX                                          ; [TERM -> TERM MUL_OPERATION FACTOR] - Executes operation EDX:EAX=EAX*EBX.
PUSH EAX                                          ; [TERM -> TERM MUL_OPERATION FACTOR] - Pushs operation result to STACK.
CALL Abs2                                         ; [CALL -> id(ARGS)] - Calls procedure [Abs2()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [Abs2()] from STACK.
PUSH EAX                                          ; [CALL -> id(ARGS)] - Pushs RETURN VALUE of procedure [Abs2()] to STACK.
CALL PrintLineInt                                 ; [CALL -> id(ARGS)] - Calls procedure [PrintLineInt()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineInt()] from STACK.
MOV EAX,0000h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
PUSH EAX                                          ; [FACTOR -> num] - Pushs INT constant to STACK.
CALL Abs2                                         ; [CALL -> id(ARGS)] - Calls procedure [Abs2()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [Abs2()] from STACK.
PUSH EAX                                          ; [CALL -> id(ARGS)] - Pushs RETURN VALUE of procedure [Abs2()] to STACK.
CALL PrintLineInt                                 ; [CALL -> id(ARGS)] - Calls procedure [PrintLineInt()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineInt()] from STACK.
MOV EAX,001Eh                                     ; [FACTOR -> num] - Moves INT constant to EAX.
PUSH EAX                                          ; [FACTOR -> num] - Pushs INT constant to STACK.
CALL Abs3                                         ; [CALL -> id(ARGS)] - Calls procedure [Abs3()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [Abs3()] from STACK.
PUSH EAX                                          ; [CALL -> id(ARGS)] - Pushs RETURN VALUE of procedure [Abs3()] to STACK.
CALL PrintLineInt                                 ; [CALL -> id(ARGS)] - Calls procedure [PrintLineInt()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineInt()] from STACK.
MOV EAX,001Eh                                     ; [FACTOR -> num] - Moves INT constant to EAX.
PUSH EAX                                          ; [FACTOR -> num] - Pushs INT constant to STACK.
MOV EAX,0000h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
PUSH EAX                                          ; [FACTOR -> num] - Pushs INT constant to STACK.
MOV EAX,0001h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
PUSH EAX                                          ; [FACTOR -> num] - Pushs INT constant to STACK.
POP EBX                                           ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Gets OPERAND O2 for operation [SUBTRACTION] to EBX.
POP EAX                                           ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Gets OPERAND O1 for operation [SUBTRACTION] to EAX.
SUB EAX,EBX                                       ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Executes operation EAX=EAX-EBX.
PUSH EAX                                          ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Pushs operation result to STACK.
POP EBX                                           ; [TERM -> TERM MUL_OPERATION FACTOR] - Gets OPERAND O2 for operation [MULTIPLICATION] to EBX.
POP EAX                                           ; [TERM -> TERM MUL_OPERATION FACTOR] - Gets OPERAND O1 for operation [MULTIPLICATION] to EAX.
IMUL EBX                                          ; [TERM -> TERM MUL_OPERATION FACTOR] - Executes operation EDX:EAX=EAX*EBX.
PUSH EAX                                          ; [TERM -> TERM MUL_OPERATION FACTOR] - Pushs operation result to STACK.
CALL Abs3                                         ; [CALL -> id(ARGS)] - Calls procedure [Abs3()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [Abs3()] from STACK.
PUSH EAX                                          ; [CALL -> id(ARGS)] - Pushs RETURN VALUE of procedure [Abs3()] to STACK.
CALL PrintLineInt                                 ; [CALL -> id(ARGS)] - Calls procedure [PrintLineInt()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineInt()] from STACK.
MOV EAX,0000h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
PUSH EAX                                          ; [FACTOR -> num] - Pushs INT constant to STACK.
CALL Abs3                                         ; [CALL -> id(ARGS)] - Calls procedure [Abs3()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [Abs3()] from STACK.
PUSH EAX                                          ; [CALL -> id(ARGS)] - Pushs RETURN VALUE of procedure [Abs3()] to STACK.
CALL PrintLineInt                                 ; [CALL -> id(ARGS)] - Calls procedure [PrintLineInt()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineInt()] from STACK.
MOV EAX,001Eh                                     ; [FACTOR -> num] - Moves INT constant to EAX.
PUSH EAX                                          ; [FACTOR -> num] - Pushs INT constant to STACK.
CALL Abs4                                         ; [CALL -> id(ARGS)] - Calls procedure [Abs4()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [Abs4()] from STACK.
PUSH EAX                                          ; [CALL -> id(ARGS)] - Pushs RETURN VALUE of procedure [Abs4()] to STACK.
CALL PrintLineInt                                 ; [CALL -> id(ARGS)] - Calls procedure [PrintLineInt()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineInt()] from STACK.
MOV EAX,001Eh                                     ; [FACTOR -> num] - Moves INT constant to EAX.
PUSH EAX                                          ; [FACTOR -> num] - Pushs INT constant to STACK.
MOV EAX,0000h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
PUSH EAX                                          ; [FACTOR -> num] - Pushs INT constant to STACK.
MOV EAX,0001h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
PUSH EAX                                          ; [FACTOR -> num] - Pushs INT constant to STACK.
POP EBX                                           ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Gets OPERAND O2 for operation [SUBTRACTION] to EBX.
POP EAX                                           ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Gets OPERAND O1 for operation [SUBTRACTION] to EAX.
SUB EAX,EBX                                       ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Executes operation EAX=EAX-EBX.
PUSH EAX                                          ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Pushs operation result to STACK.
POP EBX                                           ; [TERM -> TERM MUL_OPERATION FACTOR] - Gets OPERAND O2 for operation [MULTIPLICATION] to EBX.
POP EAX                                           ; [TERM -> TERM MUL_OPERATION FACTOR] - Gets OPERAND O1 for operation [MULTIPLICATION] to EAX.
IMUL EBX                                          ; [TERM -> TERM MUL_OPERATION FACTOR] - Executes operation EDX:EAX=EAX*EBX.
PUSH EAX                                          ; [TERM -> TERM MUL_OPERATION FACTOR] - Pushs operation result to STACK.
CALL Abs4                                         ; [CALL -> id(ARGS)] - Calls procedure [Abs4()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [Abs4()] from STACK.
PUSH EAX                                          ; [CALL -> id(ARGS)] - Pushs RETURN VALUE of procedure [Abs4()] to STACK.
CALL PrintLineInt                                 ; [CALL -> id(ARGS)] - Calls procedure [PrintLineInt()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineInt()] from STACK.
MOV EAX,0000h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
PUSH EAX                                          ; [FACTOR -> num] - Pushs INT constant to STACK.
CALL Abs4                                         ; [CALL -> id(ARGS)] - Calls procedure [Abs4()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [Abs4()] from STACK.
PUSH EAX                                          ; [CALL -> id(ARGS)] - Pushs RETURN VALUE of procedure [Abs4()] to STACK.
CALL PrintLineInt                                 ; [CALL -> id(ARGS)] - Calls procedure [PrintLineInt()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineInt()] from STACK.
Test3_EXIT:                                       ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Label to procedure [Test3()] exit code.
MOV ESP,EBP                                       ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Deallocates memory of local variables.
POP EBX                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBX.
POP EBP                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBP.
RET                                               ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Exits procedure [Test3()].
Test3 ENDP                                        ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Ends procedure [Test3()].

Test4 PROC                                        ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Begins procedure [Test4()].
PUSH EBP                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBP to STACK.
PUSH EBX                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBX to STACK.
MOV EBP,ESP                                       ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Moves ESP to EBP to store begin address of LOCAL VARIABLES.
SUB ESP,0000h                                     ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Allocates memory for local variables.
MOV EAX,000Fh                                     ; [FACTOR -> num] - Moves INT constant to EAX.
PUSH EAX                                          ; [FACTOR -> num] - Pushs INT constant to STACK.
CALL CompareTo10                                  ; [CALL -> id(ARGS)] - Calls procedure [CompareTo10()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [CompareTo10()] from STACK.
MOV EAX,0005h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
PUSH EAX                                          ; [FACTOR -> num] - Pushs INT constant to STACK.
CALL CompareTo10                                  ; [CALL -> id(ARGS)] - Calls procedure [CompareTo10()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [CompareTo10()] from STACK.
Test4_EXIT:                                       ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Label to procedure [Test4()] exit code.
MOV ESP,EBP                                       ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Deallocates memory of local variables.
POP EBX                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBX.
POP EBP                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBP.
RET                                               ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Exits procedure [Test4()].
Test4 ENDP                                        ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Ends procedure [Test4()].

Test5 PROC                                        ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Begins procedure [Test5()].
PUSH EBP                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBP to STACK.
PUSH EBX                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBX to STACK.
MOV EBP,ESP                                       ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Moves ESP to EBP to store begin address of LOCAL VARIABLES.
SUB ESP,0000h                                     ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Allocates memory for local variables.
MOV EAX,0000h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
PUSH EAX                                          ; [FACTOR -> num] - Pushs INT constant to STACK.
MOV EAX,000Ah                                     ; [FACTOR -> num] - Moves INT constant to EAX.
PUSH EAX                                          ; [FACTOR -> num] - Pushs INT constant to STACK.
POP EBX                                           ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Gets OPERAND O2 for operation [SUBTRACTION] to EBX.
POP EAX                                           ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Gets OPERAND O1 for operation [SUBTRACTION] to EAX.
SUB EAX,EBX                                       ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Executes operation EAX=EAX-EBX.
PUSH EAX                                          ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Pushs operation result to STACK.
CALL Abs1                                         ; [CALL -> id(ARGS)] - Calls procedure [Abs1()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [Abs1()] from STACK.
PUSH EAX                                          ; [CALL -> id(ARGS)] - Pushs RETURN VALUE of procedure [Abs1()] to STACK.
MOV EAX,000Ah                                     ; [FACTOR -> num] - Moves INT constant to EAX.
PUSH EAX                                          ; [FACTOR -> num] - Pushs INT constant to STACK.
CALL Abs2                                         ; [CALL -> id(ARGS)] - Calls procedure [Abs2()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [Abs2()] from STACK.
PUSH EAX                                          ; [CALL -> id(ARGS)] - Pushs RETURN VALUE of procedure [Abs2()] to STACK.
POP EBX                                           ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Gets OPERAND O2 for operation [ADDITION] to EBX.
POP EAX                                           ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Gets OPERAND O1 for operation [ADDITION] to EAX.
ADD EAX,EBX                                       ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Executes operation EAX=EAX+EBX.
PUSH EAX                                          ; [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Pushs operation result to STACK.
MOV EAX,0004h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
PUSH EAX                                          ; [FACTOR -> num] - Pushs INT constant to STACK.
CALL Abs3                                         ; [CALL -> id(ARGS)] - Calls procedure [Abs3()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [Abs3()] from STACK.
PUSH EAX                                          ; [CALL -> id(ARGS)] - Pushs RETURN VALUE of procedure [Abs3()] to STACK.
POP EBX                                           ; [TERM -> TERM MUL_OPERATION FACTOR] - Gets OPERAND O2 for operation [MULTIPLICATION] to EBX.
POP EAX                                           ; [TERM -> TERM MUL_OPERATION FACTOR] - Gets OPERAND O1 for operation [MULTIPLICATION] to EAX.
IMUL EBX                                          ; [TERM -> TERM MUL_OPERATION FACTOR] - Executes operation EDX:EAX=EAX*EBX.
PUSH EAX                                          ; [TERM -> TERM MUL_OPERATION FACTOR] - Pushs operation result to STACK.
MOV EAX,0002h                                     ; [FACTOR -> num] - Moves INT constant to EAX.
PUSH EAX                                          ; [FACTOR -> num] - Pushs INT constant to STACK.
CALL Abs4                                         ; [CALL -> id(ARGS)] - Calls procedure [Abs4()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [Abs4()] from STACK.
PUSH EAX                                          ; [CALL -> id(ARGS)] - Pushs RETURN VALUE of procedure [Abs4()] to STACK.
POP EBX                                           ; [TERM -> TERM MUL_OPERATION FACTOR] - Gets OPERAND O2 for operation [DIVISION] to EBX.
POP EAX                                           ; [TERM -> TERM MUL_OPERATION FACTOR] - Gets OPERAND O1 for operation [DIVISION] to EAX.
CDQ                                               ; [TERM -> TERM MUL_OPERATION FACTOR] - Converts EAX to EDX:EAX.
IDIV EBX                                          ; [TERM -> TERM MUL_OPERATION FACTOR] - Executes operation EAX=EDX:EAX/EBX.
PUSH EAX                                          ; [TERM -> TERM MUL_OPERATION FACTOR] - Pushs operation result to STACK.
CALL PrintLineInt                                 ; [CALL -> id(ARGS)] - Calls procedure [PrintLineInt()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineInt()] from STACK.
Test5_EXIT:                                       ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Label to procedure [Test5()] exit code.
MOV ESP,EBP                                       ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Deallocates memory of local variables.
POP EBX                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBX.
POP EBP                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBP.
RET                                               ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Exits procedure [Test5()].
Test5 ENDP                                        ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Ends procedure [Test5()].

Main PROC                                         ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Begins procedure [Main()].
PUSH EBP                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBP to STACK.
PUSH EBX                                          ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBX to STACK.
MOV EBP,ESP                                       ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Moves ESP to EBP to store begin address of LOCAL VARIABLES.
SUB ESP,0000h                                     ; [VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Allocates memory for local variables.
PUSH OFFSET _STRING_11                            ; [FACTOR -> string_literal] - Pushs address of LITERAL to STACK.
CALL PrintLineString                              ; [CALL -> id(ARGS)] - Calls procedure [PrintLineString()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineString()] from STACK.
CALL Test5                                        ; [CALL -> id(ARGS)] - Calls procedure [Test5()].
ADD ESP,0000h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [Test5()] from STACK.
PUSH OFFSET _STRING_12                            ; [FACTOR -> string_literal] - Pushs address of LITERAL to STACK.
CALL PrintLineString                              ; [CALL -> id(ARGS)] - Calls procedure [PrintLineString()].
ADD ESP,0004h                                     ; [CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [PrintLineString()] from STACK.
Main_EXIT:                                        ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Label to procedure [Main()] exit code.
MOV ESP,EBP                                       ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Deallocates memory of local variables.
POP EBX                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBX.
POP EBP                                           ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Restores original value of EBP.
RET                                               ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Exits procedure [Main()].
Main ENDP                                         ; [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}] - Ends procedure [Main()].


END Code
