//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
#include "CMemberInitializerListBase1.h"
#include "CMemberInitializerListBase2.h"
#include "CField1.h"
#include "CField2.h"
#include "CField3.h"
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CMemberInitializerListDerived final : public CMemberInitializerListBase1, public CMemberInitializerListBase2
{
//-----------------------------------------------------------------------------
	private:
		const CField1											MConstField;

	private:
		CField2													MField1;
		CField3													MField2;

	public:
		const CField1& GetConstField(void) const noexcept
		{
			return(MConstField);
		}

		const CField2& GetField1(void) const noexcept
		{
			return(MField1);
		}

		const CField3& GetField2(void) const noexcept
		{
			return(MField2);
		}

	public:
		// !!! BASE CLASS CONSTRUCTORS v MEMBER INITIALIZER LIST sa volaju v poradi v akom su BASE CLASSES definovane v definicii CLASS.
		// !!! FIELDS v MEMBER INITIALIZER LIST su initializovane v poradi v akom su FIELDS definovane v definicii CLASS.
		CMemberInitializerListDerived(int ValueBase1, int ValueBase2, int ConstField, int Field1, int Field2)
			// CONSTRUCTOR 'CMemberInitializerListBase2' je volany pomocou SYNTAX [{}].
			// FIELD 'MField1' je inicializovany pomocou SYNTAX [{}].
			: CMemberInitializerListBase1(ValueBase1), CMemberInitializerListBase2{ValueBase2}, MConstField(ConstField), MField1{Field1}
		{
			std::wcout << L"CONSTRUCTOR CMemberInitializerListDerived CALLED - BEGIN !" << std::endl;

			// FIELD 'MField2' je inicializovany v CONSTRUCTOR BODY.
			MField2=Field2;

			std::wcout << L"CONSTRUCTOR CMemberInitializerListDerived CALLED - END !" << std::endl;
		}

		virtual ~CMemberInitializerListDerived(void) override
		{
			std::wcout << L"DESTRUCTOR ~CMemberInitializerListDerived CALLED !" << std::endl;
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------