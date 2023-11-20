//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include <sstream>
#include "CString.h"
#include "MyDebug.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
class SFullTemplateSpecializationClassParameters final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													TEMPLATE_TYPE=TType;
		using													TYPE=int;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! Toto je DECLARATION PRIMARY TEMPLATE CLASS.
template<typename TType1, typename TType2=typename SFullTemplateSpecializationClassParameters<TType1>::TYPE>
class CFullTemplateSpecializationClassParameters;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! Toto je DECLARATION a DEFINITION TEMPLATE CLASS SPECIALIZATION.
template<>
class CFullTemplateSpecializationClassParameters<void> final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													TYPE=typename SFullTemplateSpecializationClassParameters<void>::TYPE;

	private:
		TYPE													MValue;

	public:
		CString Print(void) const;

	public:
		CFullTemplateSpecializationClassParameters(TYPE Value);
		virtual ~CFullTemplateSpecializationClassParameters(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! Toto je DECLARATION TEMPLATE CLASS SPECIALIZATION.
template<>
class CFullTemplateSpecializationClassParameters<CString,CString>;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
inline void FullTemplateSpecializationClassParametersTest1(void)
{
	{
		// !!!!! CODE zbehne OK. Ako 2. TEMPLATE PARAMETER sa pouzije DEFAULT TEMPLATE PARAMETER.
		CFullTemplateSpecializationClassParameters<int>*		Object=nullptr;

		std::wcout << L"OBJECT - TYPE [" << GetTypeInfoName<decltype(Object)>() << L"] VALUE [" << Object << L"]." << std::endl;
	}

	/*
	PrintLineSeparator();

	{
		// !!!!! COMPILER hodi ERROR, pretoze NON-POINTER VARIABLE POTREBUJE DEFINITION PRIMARY TEMPLATE CLASS.
		CFullTemplateSpecializationClassParameters<int>			Object;

		std::wcout << L"OBJECT - TYPE [" << GetTypeInfoName<decltype(Object)>() << L"]." << std::endl;
	}
	*/
}
//----------------------------------------------------------------------------------------------------------------------
inline void FullTemplateSpecializationClassParametersTest2(void)
{
	{
		// !!!!! CODE zbehne OK. Ako 2. TEMPLATE PARAMETER sa pouzije DEFAULT TEMPLATE ARGUMENT.
		CFullTemplateSpecializationClassParameters<void>*		Object=nullptr;

		std::wcout << L"OBJECT - TYPE [" << GetTypeInfoName<decltype(Object)>() << L"] VALUE [" << Object << L"]." << std::endl;
	}

	PrintLineSeparator();

	{
		// !!!!! CODE zbehne OK, pretoze DEFINITION TEMPLATE CLASS SPECIALIZATION je na tomto mieste dostupna. Ako 2. TEMPLATE PARAMETER sa pouzije DEFAULT TEMPLATE ARGUMENT.
		CFullTemplateSpecializationClassParameters<void,int>	Object(100);

		std::wcout << Object.Print();
	}

	/*
	{
		// !!!!! COMPILER hodi ERROR, pretoze CODE vyzaduje instanciu PRIMARY TEMPLATE a ta zatial este NEBOLA na tomto mieste DEFINED.
		CFullTemplateSpecializationClassParameters<int,CString>	Object;

		std::wcout << Object.Print();
	}
	*/

	/*
	PrintLineSeparator();

	{
		// !!!!! COMPILER hodi ERROR, pretoze na tomto mieste este nie je dostupna DEFINITION TEMPLATE CLASS SPECIALIZATION iba jej DECLARATION.
		CFullTemplateSpecializationClassParameters<CString,CString>	Object(100);

		std::wcout << Object.Print();
	}
	*/
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! Toto je DEFINITION PRIMARY TEMPLATE CLASS.
template<typename TType1, typename TType2>
class CFullTemplateSpecializationClassParameters
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TType1													MValue1;
		TType2													MValue2;

	public:
		CString Print(void) const;

	public:
		CFullTemplateSpecializationClassParameters(TType1 Value1, TType2 Value2);
		virtual ~CFullTemplateSpecializationClassParameters(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
CFullTemplateSpecializationClassParameters<TType1,TType2>::CFullTemplateSpecializationClassParameters(TType1 Value1, TType2 Value2)
	: MValue1(Value1), MValue2(Value2)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
CFullTemplateSpecializationClassParameters<TType1,TType2>::~CFullTemplateSpecializationClassParameters(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
CString CFullTemplateSpecializationClassParameters<TType1,TType2>::Print(void) const
{
	std::wstringstream											Stream;

	Stream << L"PRIMARY TEMPLATE - TYPE [" << GetTypeInfoName<decltype(*this)>() << L"] VALUE 1 [" << MValue1 << L"] VALUE 2 [" << MValue2 << L"]." << std::endl;

	CString														Text(Stream.str());

	return(Text);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! Toto je DEFINITION TEMPLATE CLASS SPECIALIZATION.
template<>
class CFullTemplateSpecializationClassParameters<CString,CString>
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		CString													MValue1;
		CString													MValue2;

	public:
		CString Print(void) const;

	public:
		CFullTemplateSpecializationClassParameters(const CString& Value1, const CString& Value2);
		virtual ~CFullTemplateSpecializationClassParameters(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
/*
// !!!!! COMPILER hodi ERROR, pretoze nie je mozne vytvorit TEMPLATE CLASS SPECIALIZATION, ktora by ako 2. TEMPLATE TYPE PARAMETER dosadila VALUE, a nie TYPE.
template<>
class CFullTemplateSpecializationClassParameters<int,100> final
{
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
};
*/
//----------------------------------------------------------------------------------------------------------------------