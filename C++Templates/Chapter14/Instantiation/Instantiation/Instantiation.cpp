//----------------------------------------------------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <concepts>
#include <functional>
#include "MyDebug.h"
#include "CString.h"
#include "CAutomaticInstantiation1.h"
#include "CAutomaticInstantiation2.h"
#include "CPartialInstantiation.h"
#include "CInstantiatedComponentsMembers.h"
#include "CInstantiatedComponentsVirtual.h"
#include "CInstantiatedComponentsOperatorMemeberDereference.h"
#include "CTwoPhaseLookup.h"
#include "CPointOfInstantiation1.h"
#include "CPointOfInstantiation2.h"
#include "CPointOfInstantiation3.h"
#include "CPointOfInstantiation4.h"
#include "CImplementationSchemes.h"
#include "CExplicitInstantiation.h"
#include "CManualInstantiation.h"
#include "CExplicitInstantiationDeclaration.h"
//----------------------------------------------------------------------------------------------------------------------
#ifdef _MSC_VER
#pragma warning( disable : 4804 )
#pragma warning( disable : 6287 )
#pragma warning( disable : 4244 )
#undef min
#undef max
#endif
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestAutomaticInstantiation(void)
{
	PrintLineSeparator();

	{
		CAutomaticInstantiation1<int>							Object(100);

		TestAutomaticInstantiation1(Object);
	}

	PrintLineSeparator();

	{
		// !!!!! C++ MOZE vykonat aj INSTANTIATION FUNCTION [void TestAutomaticInstantiation2(CAutomaticInstantiation2<double> Parameter)], pocas OVERLOADING RESOLUTION, hoci tuto FUNCTION napokon C++ NEVOLA.
		TestAutomaticInstantiation2(100);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestPartialInstantiation(void)
{
	PrintLineSeparator();

	{
		wcout << L"PartialInstantiationVariable1 VALUE [" << PartialInstantiationVariable1 << L"]." << endl;
	}

	/*
	PrintLineSeparator();

	// !!!!! COMPILER hodi ERROR, pretoze sa vykonava FULL INSTANTIATION a TYPE [int] NEMA SUBTYPE [Type].
	{
		wcout << L"PartialInstantiationVariable2 VALUE [" << PartialInstantiationVariable2 << L"]." << endl;
	}
	*/

	PrintLineSeparator();

	{
		wcout << L"PartialInstantiationVariable3 VALUE [" << PartialInstantiationVariable3 << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestInstantiatedComponents(void)
{
	PrintLineSeparator();

	{
		CInstantiatedComponentsMembers<int,3>					Object;

		Object.Test1(100);

		PrintLineSeparator();

		int														Array[3]={100,200,300};

		Object.Test2(&Array);
	}

	/*
	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	{
		// !!!!! COMPILER hodi MNOZSTVO ERROR, pretoze ARRAYS NEMOZU mat ZAPORNU DLZKU.
		CInstantiatedComponentsMembers<int,-3>					Object;

		Object.Test1(100);

		PrintLineSeparator();

		int														Array[3]={100,200,300};

		Object.Test2(&Array);
	}
	*/

	/*
	PrintLineSeparator();

	{
		// !!!!! COMPILER MOZE hodit ERROR, kedze CLASS ma VIRTUAL METHOD, ktora nema DEFINITION. Ale je to implementacne zavisle ci COMPILER naozaj hodi ERROR.
		CInstantiatedComponentsVirtual<int>						Object;

		Object.Test();
	}
	*/

	PrintLineSeparator();

	{
		// !!!!! COMPILER NEGENERUJE ERROR, hoci OPERATOR [OPERATOR->] NEMA ako RETURN TYPE POINTER TYPE, alebo TYPE na ktory je mozne aplikovat dalsi OPERATOR [OPERATOR->].
		CInstantiatedComponentsOperatorMemeberDereference<int>	Object;

		Object.Test();

		// !!!!! COMPILER NEGENERUJE ERROR, hoci OPERATOR [OPERATOR->] NEMA ako RETURN TYPE POINTER TYPE, alebo TYPE na ktory je mozne aplikovat dalsi OPERATOR [OPERATOR->].
		int														Value=Object.operator->();

		std::wcout << L"VALUE [" << Value << L"]." << std::endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTwoPhaseLookup(void)
{
	PrintLineSeparator();

	TwoPhaseLookupTest(TwoPhaseLookupNamespace::E_VALUE);

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestPointOfInstantiation(void)
{
	PrintLineSeparator();

	{
		PointOfInstantiation1Test1();
	}

	/*
	PrintLineSeparator();

	{
		PointOfInstantiation1Test2();
	}
	*/

	PrintLineSeparator();

	{
		PointOfInstantiation2Test1();
	}

	/*
	PrintLineSeparator();

	{
		PointOfInstantiation2Test2();
	}
	*/

	PrintLineSeparator();

	{
		PointOfInstantiation3Test();
	}

	PrintLineSeparator();

	{
		PointOfInstantiation4Test();
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestImplementationSchemes(void)
{
	PrintLineSeparator();

	ImplementationSchemesTest();

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! EXPLICIT SPECIALIZATION TEMPLATE CLASS.
template class CExplicitInstantiation<int>;
//----------------------------------------------------------------------------------------------------------------------
// !!!!! EXPLICIT SPECIALIZATION TEMPLATE METHOD.
template const double& CExplicitInstantiation<double>::GetValue(void) const noexcept;
//----------------------------------------------------------------------------------------------------------------------
// !!!!! EXPLICIT SPECIALIZATION TEMPLATE FUNCTION.
template void ExplicitInstantiationFunction1<int>(const int& Value);
template void ExplicitInstantiationFunction1<>(const double& Value);
template void ExplicitInstantiationFunction1(const CString& Value);
template void ExplicitInstantiationFunction2<int>(int& Value);
template void ExplicitInstantiationFunction2<>(double& Value);
// !!!!! COMPILER hodi ERROR, pretoze TYPE [CString] nema definovany OPERATOR [OPERATOR++], ktory FUNCTION vyzaduje.
//template void ExplicitInstantiationFunction2(const CString& Value);
//----------------------------------------------------------------------------------------------------------------------
void TestExplicitInstantiation(void)
{
	PrintLineSeparator();

	{
		CExplicitInstantiation<int>								Object(100);

		wcout << L"OBJECT - TYPE [" << GetTypeInfoName<decltype(Object)>() <<"] VALUE [" << Object.GetValue() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CExplicitInstantiation<double>							Object(123.456);

		wcout << L"OBJECT - TYPE [" << GetTypeInfoName<decltype(Object)>() <<"] VALUE [" << Object.GetValue() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		ExplicitInstantiationFunction1(100);
	}

	PrintLineSeparator();

	{
		ExplicitInstantiationFunction1(123.456);
	}

	PrintLineSeparator();

	{
		ExplicitInstantiationFunction1(CString(L"Timmy"));
	}

	PrintLineSeparator();

	{
		int														Value=100;

		ExplicitInstantiationFunction2(Value);
	}

	PrintLineSeparator();

	{
		double													Value=100;

		ExplicitInstantiationFunction2(Value);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestManualInstantiation(void)
{
	PrintLineSeparator();

	{
		// !!!!! Kedze HEADER FILE obsahuje iba DECLARATIONS TEMPLATE METHODS, ale nie ich DEFINITONS, C++ v tomto TRANSLATION UNIT NEDOKAZE vygenerovany BINARY CODE pre TEMPLATE METHODS.
		CManualInstantiation<int>								Object(100);

		wcout << L"OBJECT - TYPE [" << GetTypeInfoName<decltype(Object)>() <<"] VALUE [" << Object.GetValue() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!!!! Kedze HEADER FILE obsahuje iba DECLARATION TEMPLATE FUNCTION, ale nie jej DEFINITON, C++ v tomto TRANSLATION UNIT NEDOKAZE vygenerovany BINARY CODE pre TEMPLATE FUNCTION.
		ManualInstantiationFunction(200);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestExplicitInstantiationDeclaration(void)
{
	PrintLineSeparator();

	{
		// !!!!! C++ pre TEMPLATE ARGUMENT [int] vyuzije existujucu EXPLICIT INSTANTIATION DECLARATION.
		CExplicitInstantiationDeclaration<int>					Object(100);

		wcout << L"OBJECT - TYPE [" << GetTypeInfoName<decltype(Object)>() <<"] VALUE [" << Object.GetValue() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!!!! Kedze pre TEMPLATE ARGUMENT [double] NEEXISTUJE EXPLICIT INSTANTIATION DECLARATION, tak C++ vykona AUTOMATIC INSTANTIATION.
		CExplicitInstantiationDeclaration<double>				Object(123.456);

		wcout << L"OBJECT - TYPE [" << GetTypeInfoName<decltype(Object)>() <<"] VALUE [" << Object.GetValue() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!!!! C++ pre TEMPLATE ARGUMENT [int] vyuzije existujucu EXPLICIT INSTANTIATION DECLARATION.
		ExplicitInstantiationDeclarationFunction(100);
	}

	PrintLineSeparator();

	{
		// !!!!! Kedze pre TEMPLATE ARGUMENT [double] NEEXISTUJE EXPLICIT INSTANTIATION DECLARATION, tak C++ vykona AUTOMATIC INSTANTIATION.
		ExplicitInstantiationDeclarationFunction(123.456);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
auto ConstExprIfInstantiationTemplate(TType Value)
{
	if constexpr (is_same<TType,CString>::value==true)
	{
		return(Value.GetField());
	}
	else
	{
		return(Value);
	}
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! FUNCTION je iba DECLARED, ale NIE DEFINED.
void ConstExprIfInstantiationUndefinedFunction(void);
//----------------------------------------------------------------------------------------------------------------------
void ConstExprIfInstantiationFunction(void)
{
	if (sizeof(int)==0)
	{
		wcout << L"IF BRANCH CALLED." << endl;

#ifndef _MSC_VER
		// !!!!! G++ LINKER NEHODI ERROR, pretoze IF BRANCH NIE JE INSTANTIATED a tym padom NEVADI, ze FUNCTION [void ConstExprIfInstantiationUndefinedFunction(void)] je iba DECLARED, ale NIE DEFINED.
		ConstExprIfInstantiationUndefinedFunction();
#endif
	}
	else
	{
		wcout << L"ELSE BRANCH CALLED." << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestConstExprIfInstantiation(void)
{
	PrintLineSeparator();

	{
		auto													Value=ConstExprIfInstantiationTemplate(100);

		wcout << L"TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		auto													Value=ConstExprIfInstantiationTemplate(CString(L"Timmy"));

		wcout << L"TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		ConstExprIfInstantiationFunction();
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestAutomaticInstantiation();
	//TestPartialInstantiation();
	//TestInstantiatedComponents();
	//TestTwoPhaseLookup();
	//TestPointOfInstantiation();
	//TestImplementationSchemes();
	//TestExplicitInstantiation();
	//TestManualInstantiation();
	//TestExplicitInstantiationDeclaration();
	TestConstExprIfInstantiation();

	ShowExitLine();

	return(0);
}
//----------------------------------------------------------------------------------------------------------------------