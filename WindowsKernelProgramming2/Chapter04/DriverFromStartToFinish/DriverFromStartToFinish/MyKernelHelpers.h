#pragma once
//----------------------------------------------------------------------------------------------------------------------
#define MY_TAG 'XGAT'
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
#if !defined(MACRO_VARIABLE_TO_STRING)
#define MACRO_VARIABLE_TO_STRING(Variable) (void(Variable),#Variable)
#endif
//----------------------------------------------------------------------------------------------------------------------
#if !defined(MACRO_FUNCTION_TO_STRING)
#define MACRO_FUNCTION_TO_STRING(Function) (void(&Function),#Function)
#endif
//----------------------------------------------------------------------------------------------------------------------