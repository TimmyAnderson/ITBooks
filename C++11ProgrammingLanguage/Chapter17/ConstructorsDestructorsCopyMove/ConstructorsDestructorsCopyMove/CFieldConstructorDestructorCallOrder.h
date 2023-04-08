//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
#include "CField1.h"
#include "CField2.h"
#include "CField3.h"
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CFieldConstructorDestructorCallOrder final
{
//-----------------------------------------------------------------------------
	private:
		CField1													MValue1;
		CField2													MValue2;
		CField3													MValue3;

	public:
		const CField1& GetValue1(void) const noexcept
		{
			return(MValue1);
		}

		const CField2& GetValue2(void) const noexcept
		{
			return(MValue2);
		}

		const CField3& GetValue3(void) const noexcept
		{
			return(MValue3);
		}

	public:
		// !!! CONSTRUCTORS jednotlivych FIELDS sa vola v PORADI v akom su FIELDS DEKLAROVANE v CLASS.
		CFieldConstructorDestructorCallOrder(int Value1, int Value2, int Value3)
			: MValue1(Value1), MValue2(Value2), MValue3(Value3)
		{
			std::wcout << L"CONSTRUCTOR CFieldConstructorDestructorCallOrder CALLED !" << std::endl;
		}

		// !!! DESTRUCTORS jednotlivych FIELDS sa vola v OPACNOM PORADI v akom su FIELDS DEKLAROVANE v CLASS.
		~CFieldConstructorDestructorCallOrder(void)
		{
			std::wcout << L"DESTRUCTOR ~CFieldConstructorDestructorCallOrder CALLED !" << std::endl;
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------