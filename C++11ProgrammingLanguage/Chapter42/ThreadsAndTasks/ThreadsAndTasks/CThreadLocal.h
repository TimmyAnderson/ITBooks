//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include "MyDebug.h"
#include "CConstructorDestructor.h"
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CThreadLocal final
{
//-----------------------------------------------------------------------------
	private:
		// !!!!! KEYWORD [thread_local] moze byt aplikovany IBA na STATIC MEMBERS.
		static thread_local int									MValue;
		static thread_local CConstructorDestructor				MComplexValue;

	public:
		static void InitializeStaticVariable(int Value);
		static int GetStaticVariable(void);

	public:
		static void InitializeComplexStaticVariable(int Value);
		static int GetComplexStaticVariable(void);
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------