//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
// !!! Toto je DECLARATION SHARED VARIABLE. DEFINITION je v TRANSLATION UNIT 'CTranslationUnit1'.
extern int														ExternVariable;
//----------------------------------------------------------------------------------------------------------------------
/*
// !!! COMPILER hodi ERROR, pretoze VARIABLE 'ErrorSharedVariable' je DEFINED v TRANSLATION UNIT 'CTranslationUnit1' aj TRANSLATION UNIT 'CTranslationUnit2'.
int																ErrorSharedVariable;
*/
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int GetStaticVariable1(void);
//----------------------------------------------------------------------------------------------------------------------
void SetStaticVariable1(int Value);
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int GetNamespaceVariable1(void);
//----------------------------------------------------------------------------------------------------------------------
void SetNamespaceVariable1(int Value);
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void CallNamespaceFunction1(void);
//----------------------------------------------------------------------------------------------------------------------