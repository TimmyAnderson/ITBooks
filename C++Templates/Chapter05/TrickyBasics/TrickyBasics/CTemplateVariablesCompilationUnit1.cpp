//----------------------------------------------------------------------------------------------------------------------
#include "CTemplateVariablesCompilationUnit1.h"
#include "CTemplateVariablesDefinition.h"
//----------------------------------------------------------------------------------------------------------------------
int CompilationUnit1GetValueInt(void)
{
	return(MyTemplateVariable<int>);
}
//----------------------------------------------------------------------------------------------------------------------
void CompilationUnit1SetValueInt(int Value)
{
	// !!!!! Medzi CHARACTER '>' a CHARACTER '=' MUSI byt MEDZERA.
	MyTemplateVariable<int> =Value;
}
//----------------------------------------------------------------------------------------------------------------------
double CompilationUnit1GetValueDouble(void)
{
	return(MyTemplateVariable<double>);
}
//----------------------------------------------------------------------------------------------------------------------
void CompilationUnit1SetValueDouble(double Value)
{
	// !!!!! Medzi CHARACTER '>' a CHARACTER '=' MUSI byt MEDZERA.
	MyTemplateVariable<double> =Value;
}
//----------------------------------------------------------------------------------------------------------------------