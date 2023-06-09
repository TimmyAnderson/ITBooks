//----------------------------------------------------------------------------------------------------------------------
#include "CTemplateVariablesCompilationUnit2.h"
#include "CTemplateVariablesDefinition.h"
//----------------------------------------------------------------------------------------------------------------------
int CompilationUnit2GetValueInt(void)
{
	return(MyTemplateVariable<int>);
}
//----------------------------------------------------------------------------------------------------------------------
void CompilationUnit2SetValueInt(int Value)
{
	// !!!!! Medzi CHARACTER '>' a CHARACTER '=' MUSI byt MEDZERA.
	MyTemplateVariable<int> =Value;
}
//----------------------------------------------------------------------------------------------------------------------
double CompilationUnit2GetValueDouble(void)
{
	return(MyTemplateVariable<double>);
}
//----------------------------------------------------------------------------------------------------------------------
void CompilationUnit2SetValueDouble(double Value)
{
	// !!!!! Medzi CHARACTER '>' a CHARACTER '=' MUSI byt MEDZERA.
	MyTemplateVariable<double> =Value;
}
//----------------------------------------------------------------------------------------------------------------------