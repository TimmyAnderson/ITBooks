//-----------------------------------------------------------------------------
#include "CThreadLocal.h"
//-----------------------------------------------------------------------------
// !!! KEYWORD [thread_local] MUSI byt aplikovany aj v .CPP FILE.
thread_local int												CThreadLocal::MValue=0;
thread_local CConstructorDestructor								CThreadLocal::MComplexValue(0);
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void CThreadLocal::InitializeStaticVariable(int Value)
{
	MValue=Value;
}
//-----------------------------------------------------------------------------
int CThreadLocal::GetStaticVariable(void)
{
	return(MValue);
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void CThreadLocal::InitializeComplexStaticVariable(int Value)
{
	MComplexValue=CConstructorDestructor(Value);
}
//-----------------------------------------------------------------------------
int CThreadLocal::GetComplexStaticVariable(void)
{
	return(MComplexValue.GetValue());
}
//-----------------------------------------------------------------------------