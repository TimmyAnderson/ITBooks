//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
#include "CField1.h"
#include "CField2.h"
#include "CField3.h"
#include "CField4.h"
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
extern int														GlobalVariable;
//-----------------------------------------------------------------------------
int GlobalFunction(void);
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CInClassInitializers final
{
//-----------------------------------------------------------------------------
	private:
		// Pouziva sa IN CLASS INITIALIZERS na inicializaciu FIELDS.
		CField1													MValue1{1000};
		CField2													MValue2=2000;
		// !!! IN CLASS INITIALIZERS umoznuju inicializovat FIELDS z VARIABLES, ktore su v SCOPE.
		CField3													MValue3=++GlobalVariable;
		// !!! IN CLASS INITIALIZERS umoznuju inicializovat FIELDS z GLOBAL FUNCTIONS, ktore su v SCOPE.
		CField4													MValue4=GlobalFunction();

	public:
		const CField1& GetValue1(void) const noexcept;
		const CField2& GetValue2(void) const noexcept;
		const CField3& GetValue3(void) const noexcept;
		const CField4& GetValue4(void) const noexcept;

	public:
		CInClassInitializers(int Value1, int Value2);
		CInClassInitializers(int Value1, int Value2, int Value3, int Value4);
		CInClassInitializers(int Value1, int Value2, int Value3, int Value4, int);
		~CInClassInitializers(void);
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------