//----------------------------------------------------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <concepts>
#include "MyDebug.h"
#include "CString.h"
#include "CException.h"
#include "CTransparentCustomization.h"
#include "COverloadingSignatures1.h"
#include "COverloadingSignatures2.h"
#include "CTemplateAndNonTemplateFunctionOverloading.h"
#include "CTuple.h"
#include "CFullTemplateSpecializationClassSyntax.h"
#include "CFullTemplateSpecializationClassParameters.h"
#include "CFullTemplateSpecializationClassMembers.h"
#include "CTemplateClassFullSpecializationsAndInstantination.h"
#include "CTemplateClassFullSpecializationsAndInstantinationUnits1.h"
#include "CTemplateClassFullSpecializationsAndInstantinationUnits2.h"
#include "CTemplateFunctionFullSpecializationODR.h"
#include "CFullTemplateSpecializationNonTemplateMethods.h"
#include "CFullTemplateSpecializationSpecializedMembers.h"
#include "CTemplateClassSpecializedFields.h"
#include "CFullTemplateSpecializationClassNestedClasses.h"
#include "CPartialTemplateSpecializationSyntax.h"
#include "CPartialSpecializationTemplateClassLimits.h"
#include "CPartialSpecializationTemplateClassLimitsVariadic.h"
#include "CPartialTemplateSpecializationNumberOfParameters.h"
#include "CPartialTemplateSpecializationPriority.h"
#include "CPartialTemplateSpecializationVariadic.h"
#include "CPartialTemplateSpecializationDefaultArguments.h"
//----------------------------------------------------------------------------------------------------------------------
#ifdef _MSC_VER
#pragma warning( disable : 4804 )
#pragma warning( disable : 6287 )
#pragma warning( disable : 4244 )
#pragma warning( disable : 26478 )
#undef min
#undef max
#endif
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void TransparentCustomizationTemplate(TType Value)
{
	wcout << L"FUNCTION [TType] CALLED. VALUE [" << Value << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void TransparentCustomizationTemplate(CTransparentCustomization<TType> Value)
{
	wcout << L"FUNCTION [CTransparentCustomization<TType>] CALLED. VALUE [" << Value.GetValue() << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestTransparentCustomization(void)
{
	PrintLineSeparator();

	{
		int														Value(100);

		// !!!!! Vola sa VERSION TEMPLATE FUNCTION s PARAMETER [TType].
		TransparentCustomizationTemplate(Value);
	}

	PrintLineSeparator();

	{
		CTransparentCustomization<int>							Object(100);

		// !!!!! Vola sa VERSION TEMPLATE FUNCTION s PARAMETER [CTransparentCustomization<TType>].
		TransparentCustomizationTemplate(Object);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void TemplateFunctionOverloadingTemplate(TType Value)
{
	wcout << L"FUNCTION [TType] CALLED. TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void TemplateFunctionOverloadingTemplate(TType* Value)
{
	wcout << L"FUNCTION [TType*] CALLED. TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateFunctionOverloading(void)
{
	PrintLineSeparator();

	{
		// !!!!! Vola sa OVERLOADED FUNCTION s PARAMETER [TType].
		// !!!!! Kedze sa pouzila EXPLICIT TEMPLATE ARGUMENT SYNTAX, tak C++ do OVERLOAD SET zaradi nasledujuce FUNCTIONS.
		// !!! 1. Z FUNCTION [void TemplateFunctionOverloadingTemplate(TType Value)] sa vytvori FUNCTION [void TemplateFunctionOverloadingTemplate<int*>(int* Value)].
		// !!! 2. Z FUNCTION [void TemplateFunctionOverloadingTemplate(TType* Value)] sa vytvori FUNCTION [void TemplateFunctionOverloadingTemplate<int*>(int** Value)].
		// !!!!! Kedze TEMPLATE ARGUMENT ma TYPE [int*], tak za vyberie 1. FUNCTION, pretoze jeho TYPE zodpoveda TYPE daneho PARAMETER.
		TemplateFunctionOverloadingTemplate<int*>(static_cast<int*>(nullptr));
	}

	PrintLineSeparator();

	{
		// !!!!! Vola sa OVERLOADED FUNCTION s PARAMETER [TType*].
		// !!!!! Kedze sa pouzila EXPLICIT TEMPLATE ARGUMENT SYNTAX, tak C++ do OVERLOAD SET zaradi nasledujuce FUNCTIONS.
		// !!! 1. Z FUNCTION [void TemplateFunctionOverloadingTemplate(TType Value)] sa vytvori FUNCTION [void TemplateFunctionOverloadingTemplate<int>(int Value)].
		// !!! 2. Z FUNCTION [void TemplateFunctionOverloadingTemplate(TType* Value)] sa vytvori FUNCTION [void TemplateFunctionOverloadingTemplate<int>(int* Value)].
		// !!!!! Kedze TEMPLATE ARGUMENT ma TYPE [int*], tak za vyberie 2. FUNCTION, pretoze jeho TYPE zodpoveda TYPE daneho PARAMETER.
		TemplateFunctionOverloadingTemplate<int>(static_cast<int*>(nullptr));
	}

	PrintLineSeparator();

	{
		// !!!!! Vola sa OVERLOADED FUNCTION s PARAMETER [TType*].
		// !!!!! C++ vykonava DEDUCTION pre TEMPLATE PARAMETER TYPE [int*].
		TemplateFunctionOverloadingTemplate(static_cast<int*>(nullptr));
	}

	PrintLineSeparator();

	{
		// !!!!! Vola sa OVERLOADED FUNCTION s PARAMETER [TType].
		// !!!!! Kedze sa pouzila EXPLICIT TEMPLATE ARGUMENT SYNTAX, tak C++ do OVERLOAD SET zaradi nasledujuce FUNCTIONS.
		// !!! 1. Z FUNCTION [void TemplateFunctionOverloadingTemplate(TType Value)] sa vytvori FUNCTION [void TemplateFunctionOverloadingTemplate<int*>(int* Value)].
		// !!! 2. Z FUNCTION [void TemplateFunctionOverloadingTemplate(TType* Value)] sa vytvori FUNCTION [void TemplateFunctionOverloadingTemplate<int*>(int** Value)].
		// !!!!! Kedze TEMPLATE ARGUMENT ma TYPE POINTER, tak za vyberie 2. FUNCTION, pretoze POINTER na POINTER je preferovany pred POINTER.
		TemplateFunctionOverloadingTemplate<int*>(nullptr);
	}

	PrintLineSeparator();

	{
		// !!!!! Vola sa OVERLOADED FUNCTION s PARAMETER [TType*].
		// !!!!! Kedze sa pouzila EXPLICIT TEMPLATE ARGUMENT SYNTAX, tak C++ do OVERLOAD SET zaradi nasledujuce FUNCTIONS.
		// !!! 1. Z FUNCTION [void TemplateFunctionOverloadingTemplate(TType Value)] sa vytvori FUNCTION [void TemplateFunctionOverloadingTemplate<int>(int Value)].
		// !!! 2. Z FUNCTION [void TemplateFunctionOverloadingTemplate(TType* Value)] sa vytvori FUNCTION [void TemplateFunctionOverloadingTemplate<int>(int* Value)].
		// !!!!! Kedze TEMPLATE ARGUMENT ma TYPE [int*], tak za vyberie 2. FUNCTION, pretoze jeho TYPE zodpoveda TYPE daneho PARAMETER.
		TemplateFunctionOverloadingTemplate<int>(nullptr);
	}

	PrintLineSeparator();

	{
		// !!!!! Vola sa OVERLOADED FUNCTION s PARAMETER [TType].
		// !!!!! C++ vykonava DEDUCTION pre TEMPLATE PARAMETER TYPE [nullptr_t]. Do OVERLOAD SET zaradi nasledujuce FUNCTIONS.
		// !!! 1. Z FUNCTION [void TemplateFunctionOverloadingTemplate(TType Value)] sa vytvori FUNCTION [void TemplateFunctionOverloadingTemplate<nullptr_t>(nullptr_t Value)].
		// !!! 2. Z FUNCTION [void TemplateFunctionOverloadingTemplate(TType* Value)] sa vytvori FUNCTION [void TemplateFunctionOverloadingTemplate<nullptr_t>(nullptr_t* Value)].
		// !!!!! Kedze TEMPLATE ARGUMENT ma TYPE [nullptr_t], tak za vyberie 1. FUNCTION, pretoze jeho TYPE zodpoveda TYPE daneho PARAMETER.
		TemplateFunctionOverloadingTemplate(nullptr);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! C++ umoznuje, aby tieto 2 FUNCTION boli OVERLOADED. Je to preto, lebo maju ROZLICNE SIGNATURES. Sucastou SIGNATURES su aj RETURN VALUE TYPES, ak sa jedna o TEMPLATE FUNCTIONS.
// !!!!! 1. OVERLOADED FUNCTION ma SIGNATURE [int NAME<TType>(TType)].
// !!!!! 2. OVERLOADED FUNCTION ma SIGNATURE [double NAME<TType>(TType)].
// !!!!! Kedze SIGNATURES sa LISIA, tak mozu byt OVERLOADED.
template<typename TType>
int TemplateFunctionOverloadingSignatures1(TType Value)
{
	wcout << L"FUNCTION TEMPLATE 1-A CALLED. TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << endl;

	return(100);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
double TemplateFunctionOverloadingSignatures1(TType Value)
{
	wcout << L"FUNCTION TEMPLATE 1-B CALLED. TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << endl;

	return(123.456);
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! C++ umoznuje, aby tieto 2 FUNCTION boli OVERLOADED. Je to preto, lebo maju ROZLICNE SIGNATURES. Sucastou SIGNATURES su aj FUNCTION PARAMETERS a TEMPLATE PARAMETERS.
// !!!!! 1. OVERLOADED FUNCTION ma SIGNATURE [void NAME<TType1,TType2>(TType1,TType2)].
// !!!!! 2. OVERLOADED FUNCTION ma SIGNATURE [void NAME<TType1,TType2>(TType2,TType2)].
// !!!!! Kedze SIGNATURES sa LISIA, tak mozu byt OVERLOADED.
template<typename TType1, typename TType2>
void TemplateFunctionOverloadingSignatures2(TType1 Value1, TType2 Value2)
{
	wcout << L"FUNCTION TEMPLATE 2-A CALLED. TYPE 1 [" << GetTypeInfoName<decltype(Value1)>() << L"] VALUE 1 [" << Value1 << L"] TYPE 2 [" << GetTypeInfoName<decltype(Value2)>() << L"] VALUE 2 [" << Value2 << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
void TemplateFunctionOverloadingSignatures2(TType2 Value1, TType1 Value2)
{
	wcout << L"FUNCTION TEMPLATE 2-B CALLED. TYPE 1 [" << GetTypeInfoName<decltype(Value1)>() << L"] VALUE 1 [" << Value1 << L"] TYPE 2 [" << GetTypeInfoName<decltype(Value2)>() << L"] VALUE 2 [" << Value2 << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateFunctionOverloadingSignatures(void)
{
	PrintLineSeparator();

	{
		// !!!!! C++ na zaklade RETURN VALUE TYPE dokaze urcit, ktoru z OVERLOADED FUNCTIONS volat.
		// !!!!! Vola sa 1. OVERLOADED FUNCTION [int TemplateFunctionOverloadingSignatures1(TType Value)].
		int														(*Pointer)(CString)=&TemplateFunctionOverloadingSignatures1;

		int														ReturnValue=(*Pointer)(L"Timmy");

		wcout << L"RETURN VALUE - TYPE [" << GetTypeInfoName<decltype(ReturnValue)>() << L"] VALUE [" << ReturnValue << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!!!! C++ na zaklade RETURN VALUE TYPE dokaze urcit, ktoru z OVERLOADED FUNCTIONS volat.
		// !!!!! Vola sa 2. OVERLOADED FUNCTION [double TemplateFunctionOverloadingSignatures1(TType Value)].
		double													(*Pointer)(CString)=&TemplateFunctionOverloadingSignatures1;

		double													ReturnValue=(*Pointer)(L"Timmy");

		wcout << L"RETURN VALUE - TYPE [" << GetTypeInfoName<decltype(ReturnValue)>() << L"] VALUE [" << ReturnValue << L"]." << endl;
	}

	/*
	PrintLineSeparator();

	{
		// !!!!! COMPILER hodi ERROR, pretoze doslo k FUNCTION AMBIGUITY. C++ nedokaze len na zaklade RETURN VALUE TYPE rozlisit ktoru FUNCTION ma volat.
		int														ReturnValue=TemplateFunctionOverloadingSignatures1<int>(100);

		wcout << L"RETURN VALUE - TYPE [" << GetTypeInfoName<decltype(ReturnValue)>() << L"] VALUE [" << ReturnValue << L"]." << endl;
	}
	*/

	/*
	PrintLineSeparator();

	{
		// !!!!! COMPILER hodi ERROR, pretoze doslo k FUNCTION AMBIGUITY. C++ nedokaze len na zaklade RETURN VALUE TYPE rozlisit ktoru FUNCTION ma volat.
		int														ReturnValue=TemplateFunctionOverloadingSignatures1(100);

		wcout << L"RETURN VALUE - TYPE [" << GetTypeInfoName<decltype(ReturnValue)>() << L"] VALUE [" << ReturnValue << L"]." << endl;
	}
	*/

	PrintLineSeparator();

	{
		// !!!!! COMPILER vyberie 1. FUNCTION [void TemplateFunctionOverloadingSignatures2(TType1 Value1, TType2 Value2)], pretoze na zaklade kombinacie TEMPLATE AGRUMENT TYPES a FUNCTION ARGUMENTS dokaze jednoznacne urcit aka TEMPLATE FUNCTION a ma volat.
		TemplateFunctionOverloadingSignatures2<int,double>(100,123.456);
	}

	PrintLineSeparator();

	{
		// !!!!! COMPILER vyberie 2. FUNCTION [void TemplateFunctionOverloadingSignatures2(TType2 Value1, TType1 Value2)], pretoze na zaklade kombinacie TEMPLATE AGRUMENT TYPES a FUNCTION ARGUMENTS dokaze jednoznacne urcit aka TEMPLATE FUNCTION a ma volat.
		TemplateFunctionOverloadingSignatures2<int,double>(123.456,100);
	}

	/*
	PrintLineSeparator();

	{
		// !!!!! COMPILER hodi ERROR, pretoze obe FUNCTIONS vyhovuju zadanym TEMPLATE PARAMETERS a FUNCTION PARAMETERS.
		TemplateFunctionOverloadingSignatures2(100,123.456);
	}
	*/

	/*
	PrintLineSeparator();

	{
		// !!!!! COMPILER hodi ERROR, pretoze obe FUNCTIONS vyhovuju zadanym TEMPLATE PARAMETERS a FUNCTION PARAMETERS.
		TemplateFunctionOverloadingSignatures2<int,int>(100,200);
	}
	*/

	PrintLineSeparator();

	{
		// !!!!! Interne vola FUNCTION [void TemplateOverloadingSignaturesShared(TType1 Value1, TType2 Value2)] s PARAMETERS [(100,200)]. C++ to umozni, pretoze FUNCTION [void TemplateOverloadingSignaturesShared(TType2 Value1, TType1 Value2)], ktora by v 1 TRANSLATION UNIT sposobila AMBIGUITY ju nesposobi, kedze obe FUNCTIONS su v inych TRANSLATION UNITS.
		// !!!!! V G++ sa vola spravna FUNCTION. Vo VISUAL C++ sa vsak NESPRAVNE vola v oboch pripadoch FUNCTION z TRANSLATION UNIT 1.
		OverloadingSignaturesTest1();
	}

	PrintLineSeparator();

	{
		// !!!!! Interne vola FUNCTION [void TemplateOverloadingSignaturesShared(TType2 Value1, TType1 Value2)] s PARAMETERS [(100,200)]. C++ to umozni, pretoze FUNCTION [void TemplateOverloadingSignaturesShared(TType1 Value1, TType2 Value2)], ktora by v 1 TRANSLATION UNIT sposobila AMBIGUITY ju nesposobi, kedze obe FUNCTIONS su v inych TRANSLATION UNITS.
		// !!!!! V G++ sa vola spravna FUNCTION. Vo VISUAL C++ sa vsak NESPRAVNE vola v oboch pripadoch FUNCTION z TRANSLATION UNIT 1.
		OverloadingSignaturesTest2();
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void TemplateFunctionOverloadingPartialOrderingTemplate1(TType Value)
{
	wcout << L"TEMPLATE FUNCTION 1 A - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void TemplateFunctionOverloadingPartialOrderingTemplate1(TType* Value)
{
	wcout << L"TEMPLATE FUNCTION 1 B - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void TemplateFunctionOverloadingPartialOrderingTemplate2(TType* Value1, const TType* Value2=nullptr, ...)
{
	wcout << L"TEMPLATE FUNCTION 1 B - TYPE 1 [" << GetTypeInfoName<decltype(Value1)>() << L"] VALUE 1 [" << Value1 << L"] TYPE 2 [" << GetTypeInfoName<decltype(Value2)>() << L"] VALUE 2 [" << Value2 << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void TemplateFunctionOverloadingPartialOrderingTemplate2(const TType* Value1, TType* Value2, TType* Value3=nullptr)
{
	wcout << L"TEMPLATE FUNCTION 2 B - TYPE 1 [" << GetTypeInfoName<decltype(Value1)>() << L"] VALUE 1 [" << Value1 << L"] TYPE 2 [" << GetTypeInfoName<decltype(Value2)>() << L"] VALUE 2 [" << Value2 << L"] TYPE 3 [" << GetTypeInfoName<decltype(Value3)>() << L"] VALUE 3 [" << Value3 << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateFunctionOverloadingPartialOrdering(void)
{
	PrintLineSeparator();

	{
		// !!!!! Vola sa 1. OVERLOADED FUNCTION [void TemplateFunctionOverloadingPartialOrderingTemplate1(TType Value)]. Je to preto, lebo AGRUMENT ma TYPE [int] a NIE JE POINTER.
		TemplateFunctionOverloadingPartialOrderingTemplate1(0);
	}

	PrintLineSeparator();

	{
		// !!!!! Vola sa 1. OVERLOADED FUNCTION [void TemplateFunctionOverloadingPartialOrderingTemplate1(TType Value)]. Je to preto, lebo AGRUMENT ma TYPE [nullptr_t] a NIE JE POINTER.
		TemplateFunctionOverloadingPartialOrderingTemplate1(nullptr);
	}

	PrintLineSeparator();

	{
		// !!!!! Vola sa 2. OVERLOADED FUNCTION [void TemplateFunctionOverloadingPartialOrderingTemplate1(TType* Value)]. Je to preto, lebo AGRUMENT ma TYPE [int*], tak ako PARAMETER 2. OVERLOADED FUNCTION. V takom pripade je preferovana MORE SPECIALIZED TEMPLATE FUNCTION.
		// !!!!! Aplikuje sa PARTIAL ORDERING RULE. C++ vygeneruje 2 ARTIFICIAL LISTS.
		// !!!!! 1. ARTIFICIAL LIST obsahuje TYPE [A], kde TYPE [A] je INVENTED TYPE.
		// !!!!! 2. ARTIFICIAL LIST obsahuje TYPE [B*], kde TYPE [B] je INVENTED TYPE.
		// !!!!! 1. ARTIFICIAL LIST [A] sa aplikuje na 2. OVERLOADED TEMPLATE FUNCTION [void TemplateFunctionOverloadingPartialOrderingTemplate1(TType* Value)].
		// !!!!! Vysledkom je FUNCTION [void TemplateFunctionOverloadingPartialOrderingTemplate1<???>(A)], ktora NEMA ZIADEN MATCH s 2. OVERLOADED TEMPLATE FUNCTION [void TemplateFunctionOverloadingPartialOrderingTemplate1(TType* Value)].
		// !!!!! 2. ARTIFICIAL LIST [B*] sa aplikuje na 1. OVERLOADED TEMPLATE FUNCTION [void TemplateFunctionOverloadingPartialOrderingTemplate1(TType Value)].
		// !!!!! Vysledkom je FUNCTION [void TemplateFunctionOverloadingPartialOrderingTemplate1<B*>(B*)], ktora MA EXACT MATCH s 1. OVERLOADED TEMPLATE FUNCTION [void TemplateFunctionOverloadingPartialOrderingTemplate1(TType Value)].
		// !!!!! Kedze plati, ze TEMPLATE ARGUMENT DEDUCTION pre 1. TEMPLATE FUNCTION voci 2. ARTIFICIAL LIST ARGUMENT TYPES ma EXACT MATCH, ale 2. TEMPLATE FUNCTION voci 1. ARTIFICIAL LIST ARGUMENT TYPES NEMA ZIADEN MATCH, 2. TEMPLATE FUNCTION je MORE SPECIALIZED ako 1. TEMPLATE FUNCTION.
		TemplateFunctionOverloadingPartialOrderingTemplate1(static_cast<int*>(nullptr));
	}

	/*
	PrintLineSeparator();

	{
		int														Value=100;
		int*													Pointer=&Value;

		// !!!!! COMPILER hodi ERROR, pretoze doslo k AMBIGUITY.
		// !!!!! Aplikuje sa PARTIAL ORDERING RULE. C++ najprv eliminuje PARAMETERS, ktore boli inicializovane pomocou DEFAULT ARGUMENTS a takisto nepouzity ELLIPSIS PARAMETER.
		// !!!!! V 1. TEMPLATE FUNCTION [void TemplateFunctionOverloadingPartialOrderingTemplate2(TType* Value1, const TType* Value2=nullptr, ...)] je ignorovany ELLIPSIS PARAMETER, pretoze nebol pouzity.
		// !!!!! V 2. TEMPLATE FUNCTION [void TemplateFunctionOverloadingPartialOrderingTemplate2(const TType* Value1, TType* Value2, TType* Value3=nullptr)] je ignorovany posledny PARAMETER, pretoze bol inicializovany pomocou DEFAULT ARGUMENT.
		// !!!!! C++ nasledne vygeneruje 2 ARTIFICIAL LISTS.
		// !!!!! 1. ARTIFICIAL LIST obsahuje TYPES [A*,const A*], kde TYPE [A] je INVENTED TYPE.
		// !!!!! 2. ARTIFICIAL LIST obsahuje TYPES [const B*,B*], kde TYPE [B] je INVENTED TYPE.
		// !!!!! 1. ARTIFICIAL LIST [A*,const A*] sa aplikuje na 2. OVERLOADED TEMPLATE FUNCTION [void TemplateFunctionOverloadingPartialOrderingTemplate2(const TType* Value1, TType* Value2, TType* Value3=nullptr)].
		// !!!!! Vysledkom je FUNCTION [void TemplateFunctionOverloadingPartialOrderingTemplate2<A>(A*,const A*)], ktora NEMA EXACT MATCH s 2. OVERLOADED TEMPLATE FUNCTION [void TemplateFunctionOverloadingPartialOrderingTemplate2(const TType* Value1, TType* Value2, TType* Value3=nullptr)].
		// !!!!! 2. ARTIFICIAL LIST [const B*,B*] sa aplikuje na 1. OVERLOADED TEMPLATE FUNCTION [void TemplateFunctionOverloadingPartialOrderingTemplate2(TType* Value1, const TType* Value2=nullptr, ...)].
		// !!!!! Vysledkom je FUNCTION [void TemplateFunctionOverloadingPartialOrderingTemplate2<B>(const B*,B*)], ktora NEMA EXACT MATCH s 1. OVERLOADED TEMPLATE FUNCTION [void TemplateFunctionOverloadingPartialOrderingTemplate2(TType* Value1, const TType* Value2=nullptr, ...)].
		// !!!!! Kedze sa NENASIEL EXACT MATCH, tak PARTIAL ORDERING RULE ZLYHA a dochadza k AMBIGUITY, ktoru COMPILER hodi ako ERROR.
		TemplateFunctionOverloadingPartialOrderingTemplate2(Pointer,Pointer);
	}
	*/

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void TemplateAndNonTemplateFunctionOverloading1(TType Value)
{
	wcout << L"TEMPLATE FUNCTION 1 - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TemplateAndNonTemplateFunctionOverloading1(int& Value)
{
	wcout << L"NON-TEMPLATE FUNCTION 1 - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void TemplateAndNonTemplateFunctionOverloading2(TType& Value)
{
	wcout << L"TEMPLATE FUNCTION 2 - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TemplateAndNonTemplateFunctionOverloading2(const int& Value)
{
	wcout << L"NON-TEMPLATE FUNCTION 2 - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateAndNonTemplateFunctionOverloading(void)
{
	PrintLineSeparator();

	{
		int														Value=100;

		// !!!!! Kedze TEMPLATE FUNCTION aj NON-TEMPLATE FUNCTION maju ROVNAKY MATCH, tak C++ vyberie NON-TEMPLATE FUNCTION.
		TemplateAndNonTemplateFunctionOverloading1(Value);
	}

	PrintLineSeparator();

	{
		int														Value=100;

		// !!!!! Kedze TEMPLATE FUNCTION ma LEPSI MATCH ako NON-TEMPLATE FUNCTION, pretoze NON-TEMPLATE FUNCTION vyzaduje TYPE [const int&] a NIE TYPE [int&], je vybrata TEMPLATE FUNCTION.
		TemplateAndNonTemplateFunctionOverloading2(Value);
	}

	PrintLineSeparator();

	{
		const int												Value=100;

		// !!!!! Kedze TEMPLATE FUNCTION aj NON-TEMPLATE FUNCTION maju ROVNAKY MATCH, lebo dostavaju TYPE [const int&], ktory ocakava NON-TEMPLATE FUNCTION a vyhovuje aj TEMPLATE FUNCTION, tak C++ vyberie NON-TEMPLATE FUNCTION.
		TemplateAndNonTemplateFunctionOverloading2(Value);
	}

	PrintLineSeparator();

	{
		CTemplateAndNonTemplateFunctionOverloading				OriginalObject(100);

		// !!!!! Vola sa TEMPLATE MOVE CONSTRUCTOR a nie logickejsi NON-TEMPLATE COPY CONSTRUCTOR. Je to preto, lebo NON-TEMPLATE COPY CONSTRUCTOR vyzaduje TYPE [const CTemplateAndNonTemplateFunctionOverloading&], avsak ARGUMENT ma TYPE [CTemplateAndNonTemplateFunctionOverloading&]. Kedze TEMPLATE MOVE CONSTRUCTOR ma LEPSI MATCH, ako NON-TEMPLATE COPY CONSTRUCTOR, tak je vybrany TEMPLATE MOVE CONSTRUCTOR.
		CTemplateAndNonTemplateFunctionOverloading				Object{OriginalObject};

		wcout << L"VALUE [" << Object.GetValue() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CTemplateAndNonTemplateFunctionOverloading				OriginalObject(100);

		// !!!!! Vola sa NON-TEMPLATE MOVE CONSTRUCTOR. Je to preto, lebo NON-TEMPLATE MOVE CONSTRUCTOR ocakava TYPE [CTemplateAndNonTemplateFunctionOverloading&&] co je EXACT MATCH voci ARGUMENT TYPE [CTemplateAndNonTemplateFunctionOverloading&&]. Aj NON-TEMPLATE MOVE CONSTRUCTOR ma EXACT MATCH, ale kedze C++ preferuje NON-TEMPLATE FUNCTIONS, pred TEMPLATE FUNCTIONS, vyberie NON-TEMPLATE MOVE CONSTRUCTOR, a NIE TEMPLATE MOVE CONSTRUCTOR.
		CTemplateAndNonTemplateFunctionOverloading				Object{move(OriginalObject)};

		wcout << L"VALUE [" << Object.GetValue() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		const CTemplateAndNonTemplateFunctionOverloading		OriginalObject(100);

		// !!!!! Vola sa NON-TEMPLATE COPY CONSTRUCTOR. Je to preto, lebo NON-TEMPLATE COPY CONSTRUCTOR ockava ako PARAMETER TYPE [const CTemplateAndNonTemplateFunctionOverloading&] a to je EXACT MATCH voci ARGUMENT TYPE [const CTemplateAndNonTemplateFunctionOverloading&].
		CTemplateAndNonTemplateFunctionOverloading				Object{OriginalObject};

		wcout << L"VALUE [" << Object.GetValue() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		const CTemplateAndNonTemplateFunctionOverloading		OriginalObject(100);

		// !!!!! Vola sa TEMPLATE MOVE CONSTRUCTOR namiesto NON-TEMPLATE MOVE CONSTRUCTOR. Je to preto, AGRUMENT ma TYPE [const CTemplateAndNonTemplateFunctionOverloading&&], ktory sa nezhoduje s PARAMETER, ktory ocakava NON-TEMPLATE MOVE CONSTRUCTOR, ktory ocakava TYPE [CTemplateAndNonTemplateFunctionOverloading&&]. TEMPLATE MOVE CONSTRUCTOR naopak, akceptuje aj TYPE [const CTemplateAndNonTemplateFunctionOverloading&&], takze C++ vyberie TEMPLATE MOVE CONSTRUCTOR.
		CTemplateAndNonTemplateFunctionOverloading				Object{move(OriginalObject)};

		wcout << L"VALUE [" << Object.GetValue() << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename... TTypes>
void PrintTemplateFunctionOverloadingPartialOrderingVariadic(size_t Index, TType Value, TTypes... Values)
{
	wcout << L"\tINDEX [" << Index << L"] TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << endl;

	if constexpr (sizeof...(Values)>0)
	{
		PrintTemplateFunctionOverloadingPartialOrderingVariadic(Index+1,Values...);
	}
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void TemplateFunctionOverloadingPartialOrderingVariadic1(TType* Value)
{
	wcout << L"NON-VARIADIC TEMPLATE FUNCTION 1 - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTypes>
void TemplateFunctionOverloadingPartialOrderingVariadic1(TTypes... Values)
{
	wcout << L"VARIADIC TEMPLATE FUNCTION 2 CALLED." << endl;

	PrintTemplateFunctionOverloadingPartialOrderingVariadic(1,Values...);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTypes>
void TemplateFunctionOverloadingPartialOrderingVariadic1(TTypes*... Values)
{
	wcout << L"VARIADIC TEMPLATE FUNCTION 3 CALLED." << endl;

	PrintTemplateFunctionOverloadingPartialOrderingVariadic(1,Values...);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void TemplateFunctionOverloadingPartialOrderingVariadic2(CTuple<TType*> Value)
{
	CString														Text=Value.Print(L"TUPLE VARIADIC TEMPLATE FUNCTION 1.");

	wcout << Text;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTypes>
void TemplateFunctionOverloadingPartialOrderingVariadic2(CTuple<TTypes...> Value)
{
	CString														Text=Value.Print(L"TUPLE VARIADIC TEMPLATE FUNCTION 2.");

	wcout << Text;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTypes>
void TemplateFunctionOverloadingPartialOrderingVariadic2(CTuple<TTypes*...> Value)
{
	CString														Text=Value.Print(L"TUPLE VARIADIC TEMPLATE FUNCTION 3.");

	wcout << Text;
}
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateFunctionOverloadingPartialOrderingVariadic(void)
{
	PrintLineSeparator();

	{
		// !!!!! Vola 1. OVERLOADED FUNCTION [void TemplateFunctionOverloadingPartialOrderingVariadic1(TType* Value)].
		// !!!!! 2. OVERLOADED FUNCTION [void TemplateFunctionOverloadingPartialOrderingVariadic1(TTypes... Value)] vsak USPEJE, ale nasledne je vyradena aplikovanim PARTIAL ORDERING RULE.
		// !!!!! 3. OVERLOADED FUNCTION [void TemplateFunctionOverloadingPartialOrderingVariadic1(TTypes*... Values)] vsak USPEJE, ale nasledne je vyradena aplikovanim PARTIAL ORDERING RULE.
		// !!!!! PARTIAL ORDERING RULE sa aplikuje pre rozhodovanie ci vybrat 1. OVERLOADED FUNCTION, 2. OVERLOADED FUNCTION, alebo 3. OVERLOADED FUNCTION.
		// !!!!! C++ nasledne vygeneruje 3 ARTIFICIAL LISTS.
		// !!!!! 1. ARTIFICIAL LIST obsahuje TYPE [A*], kde TYPE [A*] je INVENTED TYPE. Tento ARTIFICIAL LIST bol vytvoreny z NON-VARIADIC TEMPLATE FUNCTION.
		// !!!!! 2. ARTIFICIAL LIST obsahuje TYPE [B], kde TYPE [B] je INVENTED TYPE. Tento ARTIFICIAL LIST bol vytvoreny z VARIADIC TEMPLATE FUNCTION.
		// !!!!! 3. ARTIFICIAL LIST obsahuje TYPE [C*], kde TYPE [C] je INVENTED TYPE. Tento ARTIFICIAL LIST bol vytvoreny z VARIADIC TEMPLATE FUNCTION.
		// !!!!! 1. ARTIFICIAL LIST [A*] sa aplikuje na 2. OVERLOADED TEMPLATE FUNCTION [void TemplateFunctionOverloadingPartialOrderingVariadic1(TTypes... Values)].
		// !!!!! Vysledkom je FUNCTION [void TemplateFunctionOverloadingPartialOrderingVariadic1<A*>(A*...)], ktora ma EXACT MATCH s 2. OVERLOADED TEMPLATE FUNCTION [void TemplateFunctionOverloadingPartialOrderingVariadic1(TTypes... Values)].
		// !!!!! 1. ARTIFICIAL LIST [A*] sa aplikuje na 3. OVERLOADED TEMPLATE FUNCTION [void TemplateFunctionOverloadingPartialOrderingVariadic1(TTypes*... Values)].
		// !!!!! Vysledkom je FUNCTION [void TemplateFunctionOverloadingPartialOrderingVariadic1<A>(A*...)], ktora ma EXACT MATCH s 3. OVERLOADED TEMPLATE FUNCTION [void TemplateFunctionOverloadingPartialOrderingVariadic1(TTypes*... Values)].
		// !!!!! 2. ARTIFICIAL LIST [B] sa aplikuje na 1. OVERLOADED TEMPLATE FUNCTION [void TemplateFunctionOverloadingPartialOrderingVariadic1(TType* Value)].
		// !!!!! Vysledkom je FUNCTION [void TemplateFunctionOverloadingPartialOrderingVariadic1<???>(B*)], ktora NEMA DEDUCTION pre 1. OVERLOADED TEMPLATE FUNCTION [void TemplateFunctionOverloadingPartialOrderingVariadic1(TType* Value)].
		// !!!!! 2. ARTIFICIAL LIST [B] sa aplikuje na 3. OVERLOADED TEMPLATE FUNCTION [void TemplateFunctionOverloadingPartialOrderingVariadic1(TTypes*... Values)].
		// !!!!! Vysledkom je FUNCTION [void TemplateFunctionOverloadingPartialOrderingVariadic1<B>(B)], ktora NEMA DEDUCTION pre 3. OVERLOADED TEMPLATE FUNCTION [void TemplateFunctionOverloadingPartialOrderingVariadic1(TTypes*... Values)].
		// !!!!! 3. ARTIFICIAL LIST [C*] sa aplikuje na 1. OVERLOADED TEMPLATE FUNCTION [void TemplateFunctionOverloadingPartialOrderingVariadic1(TType* Value)].
		// !!!!! Vysledkom je FUNCTION [void TemplateFunctionOverloadingPartialOrderingVariadic1<C>(C*)], ktora ma EXACT MATCH s 1. OVERLOADED TEMPLATE FUNCTION [void TemplateFunctionOverloadingPartialOrderingVariadic1(TType* Value)]. Avsak kedze ARTIFICIAL LIST, ktory vznikol z VARIADIC TEMPLATE FUNCTION NIE je mozne subsituovat do NON-VARIADIC TEMPLATE FUNCTION, tak NEDOCHADZA k MATCH.
		// !!!!! 3. ARTIFICIAL LIST [C*] sa aplikuje na 2. OVERLOADED TEMPLATE FUNCTION [void TemplateFunctionOverloadingPartialOrderingVariadic1(TTypes... Values)].
		// !!!!! Vysledkom je FUNCTION [void TemplateFunctionOverloadingPartialOrderingVariadic1<???>(C*...)], ktora NEMA DEDUCTION pre 2. OVERLOADED TEMPLATE FUNCTION [void TemplateFunctionOverloadingPartialOrderingVariadic1(TTypes... Values)].
		// !!!!! 1. OVERLOADED FUNCTION NEMA EXACT MATCH s 2. ARTIFICIAL LIST, ale 2. OVERLOADED FUNCTION MA EXACT MATCH s 1. ARTIFICIAL LIST. To znamena, ze 1. OVERLOADED FUNCTION je MORE SPECIALIZED ako 2. OVERLOADED FUNCTION.
		// !!!!! 1. OVERLOADED FUNCTION NEMA EXACT MATCH s 3. ARTIFICIAL LIST, ale 3. OVERLOADED FUNCTION MA EXACT MATCH s 1. ARTIFICIAL LIST. To znamena, ze 1. OVERLOADED FUNCTION je MORE SPECIALIZED ako 3. OVERLOADED FUNCTION.
		// !!!!! 2. OVERLOADED FUNCTION NEMA EXACT MATCH s 3. ARTIFICIAL LIST, a ani 3. OVERLOADED FUNCTION NEMA EXACT MATCH s 2. ARTIFICIAL LIST. To znamena, ze 2. OVERLOADED FUNCTION je ROVNAKO SPECIALIZED ako 3. OVERLOADED FUNCTION.
		// !!!!! Z vysledkov subsitucie ARTIFICIAL LISTS do OVERLOADED FUNCTIONS plati, ze 1. OVERLOADED FUNCTION je MOST SPECIALIZED.
		TemplateFunctionOverloadingPartialOrderingVariadic1(static_cast<int*>(nullptr));
	}

	PrintLineSeparator();

	{
		// !!!!! Vola 2. OVERLOADED FUNCTION [void TemplateFunctionOverloadingPartialOrderingVariadic1(TTypes... Value)].
		// !!!!! 1. OVERLOADED FUNCTION [void TemplateFunctionOverloadingPartialOrderingVariadic1(TType* Value)] je VYRADENA, pretoze nesedi pocet PARAMETERS.
		// !!!!! 3. OVERLOADED FUNCTION [void TemplateFunctionOverloadingPartialOrderingVariadic1(TTypes*... Values)] je VYRADENA, pretoze z AGRUMENTS [int,double], nie je mozne spravit POINTERS ako to ocakava VARIADIC TEMPLATE FUNCITION PARAMETERS PACK [TTypes*...].
		TemplateFunctionOverloadingPartialOrderingVariadic1(0,0.0);
	}

	PrintLineSeparator();

	{
		// !!!!! Vola 3. OVERLOADED FUNCTION [void TemplateFunctionOverloadingPartialOrderingVariadic1(TTypes*... Values)].
		// !!!!! 1. OVERLOADED FUNCTION [void TemplateFunctionOverloadingPartialOrderingVariadic1(TType* Value)] je VYRADENA, pretoze nesedi pocet PARAMETERS.
		// !!!!! 2. OVERLOADED FUNCTION [void TemplateFunctionOverloadingPartialOrderingVariadic1(TTypes... Value)] vsak USPEJE, ale nasledne je vyradena aplikovanim PARTIAL ORDERING RULE.
		// !!!!! PARTIAL ORDERING RULE sa aplikuje pre rozhodovanie ci vybrat 2. OVERLOADED FUNCTION, alebo 3. OVERLOADED FUNCTION.
		// !!!!! C++ nasledne vygeneruje 2 ARTIFICIAL LISTS.
		// !!!!! 1. ARTIFICIAL LIST obsahuje TYPE [A], kde TYPE [A] je INVENTED TYPE. Tento ARTIFICIAL LIST bol vytvoreny z VARIADIC TEMPLATE FUNCTION.
		// !!!!! 2. ARTIFICIAL LIST obsahuje TYPE [B*], kde TYPE [B] je INVENTED TYPE. Tento ARTIFICIAL LIST bol vytvoreny z VARIADIC TEMPLATE FUNCTION.
		// !!!!! 1. ARTIFICIAL LIST [A] sa aplikuje na 3. OVERLOADED TEMPLATE FUNCTION [void TemplateFunctionOverloadingPartialOrderingVariadic1(TTypes*... Values)].
		// !!!!! Vysledkom je FUNCTION [void TemplateFunctionOverloadingPartialOrderingVariadic1<???>(A...)], ktora NEMA ZIADEN MATCH s 3. OVERLOADED TEMPLATE FUNCTION [void TemplateFunctionOverloadingPartialOrderingVariadic1(TTypes*... Values)].
		// !!!!! 2. ARTIFICIAL LIST [B*] sa aplikuje na 2. OVERLOADED TEMPLATE FUNCTION [void TemplateFunctionOverloadingPartialOrderingVariadic1(TTypes... Values)].
		// !!!!! Vysledkom je FUNCTION [void TemplateFunctionOverloadingPartialOrderingVariadic1<B*>(B*...)], ktora MA EXACT MATCH s 2. OVERLOADED TEMPLATE FUNCTION [void TemplateFunctionOverloadingPartialOrderingVariadic1(TTypes... Values)].
		// !!!!! Kedze plati, ze TEMPLATE ARGUMENT DEDUCTION pre 2. TEMPLATE FUNCTION voci 2. ARTIFICIAL LIST ARGUMENT TYPES ma EXACT MATCH, ale 3. TEMPLATE FUNCTION voci 1. ARTIFICIAL LIST ARGUMENT TYPES NEMA ZIADEN MATCH, 3. TEMPLATE FUNCTION je MORE SPECIALIZED ako 2. TEMPLATE FUNCTION.
		TemplateFunctionOverloadingPartialOrderingVariadic1(static_cast<int*>(nullptr),static_cast<double*>(nullptr));
	}

	PrintLineSeparator();

	{
		int														Value=100;
		CTuple<int*>											Object(&Value);

		// !!!!! Vola 1. OVERLOADED FUNCTION [void TemplateFunctionOverloadingPartialOrderingVariadic2(CTuple<TType*> Value)].
		TemplateFunctionOverloadingPartialOrderingVariadic2(Object);
	}

	PrintLineSeparator();

	{
		CTuple<int,double>										Object(100,123.456);

		// !!!!! Vola 2. OVERLOADED FUNCTION [void TemplateFunctionOverloadingPartialOrderingVariadic2(CTuple<TTypes...> Value)].
		TemplateFunctionOverloadingPartialOrderingVariadic2(Object);
	}

	PrintLineSeparator();

	{
		int														Value1=100;
		double													Value2=123.456;
		CTuple<int*,double*>									Object(&Value1,&Value2);

		// !!!!! Vola 3. OVERLOADED FUNCTION [void TemplateFunctionOverloadingPartialOrderingVariadic2(CTuple<TTypes*...> Value)].
		TemplateFunctionOverloadingPartialOrderingVariadic2(Object);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateClassFullSpecializationsSyntax(void)
{
	PrintLineSeparator();

	{
		// !!! Vytvara sa instancia PRIMARY TEMPLATE CLASS.
		CFullTemplateSpecializationClassSyntax<int>				Object(100);

		Object.Print();
	}

	PrintLineSeparator();

	{
		// !!! Vytvara sa instancia TEMPLATE CLASS SPECIALIZATION.
		CFullTemplateSpecializationClassSyntax<void>			Object;
		CString													Value=Object.ToString();

		wcout << L"VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateClassFullSpecializationsParameters(void)
{
	PrintLineSeparator();

	{
		FullTemplateSpecializationClassParametersTest1();
	}

	PrintLineSeparator();

	{
		// !!!!! CODE zbehne OK, pretoze DEFINITION PRIMARY TEMPLATE CLASS je na tomto mieste dostupna.
		CFullTemplateSpecializationClassParameters<int>			Object(100,200);

		wcout << Object.Print();
	}

	PrintLineSeparator();

	{
		FullTemplateSpecializationClassParametersTest2();
	}

	PrintLineSeparator();

	{
		// !!!!! CODE zbehne OK, pretoze DEFINITION PRIMARY TEMPLATE CLASS je na tomto mieste dostupna.
		CFullTemplateSpecializationClassParameters<int,CString>	Object(100,L"Timmy");

		wcout << Object.Print();
	}

	PrintLineSeparator();

	{
		// !!!!! CODE zbehne OK, pretoze DEFINITION TEMPLATE CLASS SPECIALIZATION je na tomto mieste dostupna.
		CFullTemplateSpecializationClassParameters<CString,CString>	Object(L"Timmy",L"Anderson");

		wcout << Object.Print();
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateClassFullSpecializationsMembers(void)
{
	PrintLineSeparator();

	{
		// !!! Vola sa PRIMARY TEMPLATE CLASS.
		CFullTemplateSpecializationClassMembersOutside<int>		Object;

		Object.PrintPrimaryTemplateOutside(100);
	}

	PrintLineSeparator();

	{
		// !!! Vola sa PRIMARY TEMPLATE CLASS.
		CFullTemplateSpecializationClassMembersOutside<int>::CFullTemplateSpecializationClassMembersInside<double>	Object;

		Object.PrintPrimaryTemplateInside(123.456);
	}

	PrintLineSeparator();

	{
		// !!! Vola sa TEMPLATE CLASS SPECIALIZATION.
		CFullTemplateSpecializationClassMembersOutside<CString>	Object;

		Object.PrintTemplateSpecializationOutside(L"Timmy");
	}

	PrintLineSeparator();

	{
		// !!! Vola sa TEMPLATE CLASS SPECIALIZATION.
		CFullTemplateSpecializationClassMembersOutside<CString>::CFullTemplateSpecializationClassMembersInside<double>	Object;

		Object.PrintTemplateSpecializationInside(123.456);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateClassFullSpecializationsAndInstantination(void)
{
	PrintLineSeparator();

	{
		TemplateClassFullSpecializationsAndInstantinationTest();
	}

	PrintLineSeparator();

	{
		// !!!!! Pouzije sa TEMPLATE SPECIALIZATION.
		CTemplateClassFullSpecializationsAndInstantination<double>	Object(123.456);

		Object.PrintPrimaryTemplate();
	}

	PrintLineSeparator();

	{
		TestTemplateClassFullSpecializationsAndInstantinationUnits1();
	}

	PrintLineSeparator();

	{
		TestTemplateClassFullSpecializationsAndInstantinationUnits2();
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! PRIMARY TEMPLATE FUNCTION.
template<typename TType>
void TemplateFunctionFullSpecializations(TType Value)
{
	wcout << L"PRIMARY TEMPLATE FUNCTION 1 - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
// !!! PRIMARY TEMPLATE FUNCTION.
template<typename TType>
void TemplateFunctionFullSpecializations(TType* Value)
{
	wcout << L"PRIMARY TEMPLATE FUNCTION 2 - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
// !!! TEMPLATE SPECIALIZATION TEMPLATE FUNCTION [void TemplateFunctionFullSpecializations1(TType Value)]. TEMPLATE PARAMETERS NIE su urcene EXPLICITNE, pretoze su DEDUCED.
template<>
void TemplateFunctionFullSpecializations(int Value)
{
	wcout << L"TEMPLATE FUNCTION SPECIALIZATION 1 <int> - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
// !!! TEMPLATE SPECIALIZATION TEMPLATE FUNCTION [void TemplateFunctionFullSpecializations1(TType* Value)]. TEMPLATE PARAMETERS NIE su urcene EXPLICITNE, pretoze su DEDUCED.
template<>
void TemplateFunctionFullSpecializations(int* Value)
{
	wcout << L"TEMPLATE FUNCTION SPECIALIZATION 2 <int> - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
// !!! TEMPLATE SPECIALIZATION TEMPLATE FUNCTION [void TemplateFunctionFullSpecializations1(TType Value)]. TEMPLATE PARAMETERS su urcene EXPLICITNE.
template<>
void TemplateFunctionFullSpecializations<double>(double Value)
{
	wcout << L"TEMPLATE FUNCTION SPECIALIZATION 1 <double> - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
// !!! TEMPLATE SPECIALIZATION TEMPLATE FUNCTION [void TemplateFunctionFullSpecializations1(TType* Value)]. TEMPLATE PARAMETERS su urcene EXPLICITNE.
template<>
void TemplateFunctionFullSpecializations<double>(double* Value)
{
	wcout << L"TEMPLATE FUNCTION SPECIALIZATION 2 <double> - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
// !!! PRIMARY TEMPLATE FUNCTION.
template<typename TType>
void TemplateFunctionFullSpecializationsDefaultArgument(TType Value1, TType Value2=999)
{
	wcout << L"PRIMARY TEMPLATE FUNCTION 2 - TYPE 1 [" << GetTypeInfoName<decltype(Value1)>() << L"] VALUE 1 [" << Value1 << L"] TYPE 2 [" << GetTypeInfoName<decltype(Value2)>() << L"] VALUE 2 [" << Value2 << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
// !!! TEMPLATE FUNCTION SPECIALIZATION.
template<>
void TemplateFunctionFullSpecializationsDefaultArgument<long>(long Value1, long Value2)
{
	wcout << L"TEMPLATE FUNCTION SPECIALIZATION 2 <long> - TYPE 1 [" << GetTypeInfoName<decltype(Value1)>() << L"] VALUE 1 [" << Value1 << L"] TYPE 2 [" << GetTypeInfoName<decltype(Value2)>() << L"] VALUE 2 [" << Value2 << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
/*
// !!! TEMPLATE FUNCTION SPECIALIZATION.
// !!!!! COMPILER hodi ERROR, pretoze v TEMPLATE FUNCTION SPECIALIZATIONS NIE JE mozne definvat DEFAULT ARGUMENTS.
template<>
void TemplateFunctionFullSpecializationsDefaultArgument<double>(double Value1, double Value2=999.999)
{
	wcout << L"TEMPLATE FUNCTION SPECIALIZATION 2 <long> - TYPE 1 [" << GetTypeInfoName<decltype(Value1)>() << L"] VALUE 1 [" << Value1 << L"] TYPE 2 [" << GetTypeInfoName<decltype(Value2)>() << L"] VALUE 2 [" << Value2 << L"]." << endl;
}
*/
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateFunctionFullSpecializations(void)
{
	PrintLineSeparator();

	{
		CString													Value=L"Timmy";

		TemplateFunctionFullSpecializations(Value);
	}

	PrintLineSeparator();

	{
		CString													Value=L"Timmy";
		CString*												Pointer=&Value;

		TemplateFunctionFullSpecializations(Pointer);
	}

	PrintLineSeparator();

	{
		int														Value=100;

		TemplateFunctionFullSpecializations(Value);
	}

	PrintLineSeparator();

	{
		int														Value=100;
		int*													Pointer=&Value;

		TemplateFunctionFullSpecializations(Pointer);
	}

	PrintLineSeparator();

	{
		double													Value=100;

		TemplateFunctionFullSpecializations(Value);
	}

	PrintLineSeparator();

	{
		double													Value=100;
		double*													Pointer=&Value;

		TemplateFunctionFullSpecializations(Pointer);
	}

	PrintLineSeparator();

	{
		int														Value1=100;
		int														Value2=200;

		TemplateFunctionFullSpecializationsDefaultArgument(Value1,Value2);
	}

	PrintLineSeparator();

	{
		int														Value=100;

		// !!!!! Pouzije sa DEFAULT ARGUMENT PRIMARY TEMPLATE FUNCTION.
		TemplateFunctionFullSpecializationsDefaultArgument(Value);
	}

	PrintLineSeparator();

	{
		long													Value1=100L;
		long													Value2=200L;

		TemplateFunctionFullSpecializationsDefaultArgument(Value1,Value2);
	}

	PrintLineSeparator();

	{
		long													Value=100L;

		// !!!!! V TEMPLATE FUNCTION SPECIALIZATION sa pouzije DEFAULT ARGUMENT PRIMARY TEMPLATE FUNCTION.
		TemplateFunctionFullSpecializationsDefaultArgument(Value);
	}

	PrintLineSeparator();

	{
		int														Value=100;

		// !!! Vola sa PRIMARY TEMPLATE FUNCTION.
		TemplateFunctionFullSpecializationODR(Value);
	}

	PrintLineSeparator();

	{
		double													Value=100;

		// !!! Vola sa TEMPLATE FUNCTION SPECIALIZATION.
		TemplateFunctionFullSpecializationODR(Value);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! PRIMARY TEMPLATE VARIABLE.
template<typename TType>
TType															TemplateVariableFullSpecializations1=TType();
//----------------------------------------------------------------------------------------------------------------------
// !!! TEMPLATE VARIABLE SPECIALIZATION.
template<>
double															TemplateVariableFullSpecializations1<double> =123.456;
//----------------------------------------------------------------------------------------------------------------------
// !!! TEMPLATE VARIABLE SPECIALIZATION.
// !!!!! VARIABLE TYPE NEMUSI byt idenficka ako PARAMETER TYPE.
template<>
double															TemplateVariableFullSpecializations1<CString> =1234.56;
//----------------------------------------------------------------------------------------------------------------------
// !!! PRIMARY TEMPLATE VARIABLE.
template<typename TType>
constexpr size_t												TemplateVariableFullSpecializations2=sizeof(TType);
//----------------------------------------------------------------------------------------------------------------------
// !!! TEMPLATE VARIABLE SPECIALIZATION.
template<>
constexpr size_t												TemplateVariableFullSpecializations2<void> =0;
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateVariableFullSpecializations(void)
{
	PrintLineSeparator();

	{
		wcout << L"PRIMARY TEMPLATE VARIABLE 1 - TYPE [" << GetTypeInfoName<decltype(TemplateVariableFullSpecializations1<int>)>() << L"] VALUE [" << TemplateVariableFullSpecializations1<int> << L"]." << endl;
		wcout << L"TEMPLATE VARIABLE SPECIALIZATION 1 <double> - TYPE [" << GetTypeInfoName<decltype(TemplateVariableFullSpecializations1<double>)>() << L"] VALUE [" << TemplateVariableFullSpecializations1<double> << L"]." << endl;
		wcout << L"TEMPLATE VARIABLE SPECIALIZATION 1 <CString> - TYPE [" << GetTypeInfoName<decltype(TemplateVariableFullSpecializations1<CString>)>() << L"] VALUE [" << TemplateVariableFullSpecializations1<CString> << L"]." << endl;

		TemplateVariableFullSpecializations1<int>++;
		TemplateVariableFullSpecializations1<double>++;
		TemplateVariableFullSpecializations1<CString>++;

		wcout << L"PRIMARY TEMPLATE VARIABLE 1 - TYPE [" << GetTypeInfoName<decltype(TemplateVariableFullSpecializations1<int>)>() << L"] VALUE [" << TemplateVariableFullSpecializations1<int> << L"]." << endl;
		wcout << L"TEMPLATE VARIABLE SPECIALIZATION 1 <double> - TYPE [" << GetTypeInfoName<decltype(TemplateVariableFullSpecializations1<double>)>() << L"] VALUE [" << TemplateVariableFullSpecializations1<double> << L"]." << endl;
		wcout << L"TEMPLATE VARIABLE SPECIALIZATION 1 <CString> - TYPE [" << GetTypeInfoName<decltype(TemplateVariableFullSpecializations1<CString>)>() << L"] VALUE [" << TemplateVariableFullSpecializations1<CString> << L"]." << endl;
	}

	PrintLineSeparator();

	{
		wcout << L"PRIMARY TEMPLATE VARIABLE 2 - TYPE [" << GetTypeInfoName<decltype(TemplateVariableFullSpecializations2<int>)>() << L"] VALUE [" << TemplateVariableFullSpecializations2<int> << L"]." << endl;
		wcout << L"PRIMARY TEMPLATE VARIABLE 2 - TYPE [" << GetTypeInfoName<decltype(TemplateVariableFullSpecializations2<long double>)>() << L"] VALUE [" << TemplateVariableFullSpecializations2<long double> << L"]." << endl;
		wcout << L"TEMPLATE VARIABLE SPECIALIZATION 2 <void> - TYPE [" << GetTypeInfoName<decltype(TemplateVariableFullSpecializations2<void>)>() << L"] VALUE [" << TemplateVariableFullSpecializations2<void> << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateClassNonTemplateMethodFullSpecializations(void)
{
	PrintLineSeparator();

	{
		CFullTemplateSpecializationNonTemplateMethods<int>		Object(100);

		// !!!!! Volaju sa PRIMARY TEMPLATE METHODS.
		Object.Print1();
		Object.Print2();
		Object.Print3(200);
	}

	PrintLineSeparator();

	{
		CFullTemplateSpecializationNonTemplateMethods<double>	Object(100.111);

		// !!!!! Vola sa PRIMARY TEMPLATE METHOD, pretoze tato METHOD NEMA SPECIALIZATION.
		Object.Print1();

		// !!!!! Volaju sa TEMPLATE METHODS SPECIALIZATIONS.
		Object.Print2();
		Object.Print3(200.222);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateClassSpecializedMembers(void)
{
	PrintLineSeparator();

	{
		CFullTemplateSpecializationSpecializedMembers<int>		Object(100);

		// !!!!! Vola sa PRIMARY TEMPLATE METHOD.
		Object.MyMethod(200);
	}

	PrintLineSeparator();

	{
		CFullTemplateSpecializationSpecializedMembers<double>	Object(100.111);

		// !!!!! Vola sa TEMPLATE METHOD SPECIALIZATION.
		Object.MyMethod(200.222);
	}

	PrintLineSeparator();

	{
		CFullTemplateSpecializationSpecializedMembers<long>		Object;

		// !!!!! Vola sa TEMPLATE CLASS SPECIALIZATION METHOD.
		Object.MyMethod(1000L);
	}

	PrintLineSeparator();

	{
		CFullTemplateSpecializationSpecializedMembers<int>		Object1(100);
		CFullTemplateSpecializationSpecializedMembers<double>	Object2(100.111);
		CFullTemplateSpecializationSpecializedMembers<long>		Object3;

		wcout << L"PRIMARY TEMPLATE STATIC FIELD - TYPE [" << GetTypeInfoName<decltype(Object1.MMyStaticField)>() << L"] STATIC FIELD [" << Object1.MMyStaticField << L"]." << endl;
		wcout << L"TEMPLATE STATIC FIELD SPECIALIZATION <double> - TYPE [" << GetTypeInfoName<decltype(Object2.MMyStaticField)>() << L"] STATIC FIELD [" << Object2.MMyStaticField << L"]." << endl;
		wcout << L"TEMPLATE CLASS SPECIALIZATION STATIC FIELD <long> - TYPE [" << GetTypeInfoName<decltype(Object3.MMyStaticField)>() << L"] STATIC FIELD [" << Object3.MMyStaticField << L"]." << endl;

		wcout << endl;

		Object1.MMyStaticField+=5;
		Object2.MMyStaticField+=5.5;
		Object3.MMyStaticField+=5L;

		wcout << L"PRIMARY TEMPLATE STATIC FIELD - TYPE [" << GetTypeInfoName<decltype(Object1.MMyStaticField)>() << L"] STATIC FIELD [" << Object1.MMyStaticField << L"]." << endl;
		wcout << L"TEMPLATE STATIC FIELD SPECIALIZATION <double> - TYPE [" << GetTypeInfoName<decltype(Object2.MMyStaticField)>() << L"] STATIC FIELD [" << Object2.MMyStaticField << L"]." << endl;
		wcout << L"TEMPLATE CLASS SPECIALIZATION STATIC FIELD <long> - TYPE [" << GetTypeInfoName<decltype(Object3.MMyStaticField)>() << L"] STATIC FIELD [" << Object3.MMyStaticField << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CFullTemplateSpecializationSpecializedMembers<int>::CFullTemplateSpecializationSpecializedMembersInner<long>	Object;

		// !!!! Vola sa PRIMARY TEMPLATE INNER CLASS METHOD.
		Object.MyInnerMethod(12345L);
	}

	PrintLineSeparator();

	{
		CFullTemplateSpecializationSpecializedMembers<short>::CFullTemplateSpecializationSpecializedMembersInner<double>	Object;

		// !!!!! Vola sa TEMPLATE CLASS INNER CLASS METHOD SPECIALIZATION.
		Object.MyInnerMethod(123.456);
	}

	PrintLineSeparator();

	{
		CFullTemplateSpecializationSpecializedMembers<int>::CFullTemplateSpecializationSpecializedMembersInner<long>	Object1;
		CFullTemplateSpecializationSpecializedMembers<short>::CFullTemplateSpecializationSpecializedMembersInner<double>	Object2;

		wcout << L"PRIMARY TEMPLATE INNER CLASS STATIC FIELD - TYPE [" << GetTypeInfoName<decltype(Object1.MMyInnerStaticField)>() << L"] STATIC FIELD [" << Object1.MMyInnerStaticField << L"]." << endl;
		wcout << L"TEMPLATE CLASS INNER CLASS STATIC FIELD SPECIALIZATION <short>::<double> - TYPE [" << GetTypeInfoName<decltype(Object2.MMyInnerStaticField)>() << L"] STATIC FIELD [" << Object2.MMyInnerStaticField << L"]." << endl;

		wcout << endl;

		Object1.MMyInnerStaticField+=5;
		Object2.MMyInnerStaticField+=5.5;

		wcout << L"PRIMARY TEMPLATE INNER CLASS STATIC FIELD - TYPE [" << GetTypeInfoName<decltype(Object1.MMyInnerStaticField)>() << L"] STATIC FIELD [" << Object1.MMyInnerStaticField << L"]." << endl;
		wcout << L"TEMPLATE CLASS INNER CLASS STATIC FIELD SPECIALIZATION <short>::<double> - TYPE [" << GetTypeInfoName<decltype(Object2.MMyInnerStaticField)>() << L"] STATIC FIELD [" << Object2.MMyInnerStaticField << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateClassSpecializedFieldsDeclarationDefinition(void)
{
	PrintLineSeparator();

	{
		TemplateClassSpecializedFieldsTest();
	}

	PrintLineSeparator();

	{
		wcout << L"TEMPLATE CLASS STATIC FIELD SPECIALIZATION <STemplateClassSpecializedFields> - TYPE [" << GetTypeInfoName<decltype(CTemplateClassSpecializedFields<STemplateClassSpecializedFields>::MStaticField)>() << L"] STATIC FIELD [" << CTemplateClassSpecializedFields<STemplateClassSpecializedFields>::MStaticField << L"]." << endl;

		wcout << endl;

		CTemplateClassSpecializedFields<STemplateClassSpecializedFields>::MStaticField.SetField(1000);
		
		wcout << L"TEMPLATE CLASS STATIC FIELD SPECIALIZATION <STemplateClassSpecializedFields> - TYPE [" << GetTypeInfoName<decltype(CTemplateClassSpecializedFields<STemplateClassSpecializedFields>::MStaticField)>() << L"] STATIC FIELD [" << CTemplateClassSpecializedFields<STemplateClassSpecializedFields>::MStaticField << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateClassInnerClassSpecialization(void)
{
	PrintLineSeparator();

	{
		CFullTemplateSpecializationClassNestedClassesOuter<int>::CFullTemplateSpecializationClassNestedClassesInner<int>	Object;

		Object.Print(100);
	}

	PrintLineSeparator();

	{
		CFullTemplateSpecializationClassNestedClassesOuter<long>::CFullTemplateSpecializationClassNestedClassesInner<int>	Object;

		Object.Print(200);
	}

	PrintLineSeparator();

	{
		CFullTemplateSpecializationClassNestedClassesOuter<wchar_t>::CFullTemplateSpecializationClassNestedClassesInner<int>	Object;

		Object.Print(300);
	}

	PrintLineSeparator();

	{
		CFullTemplateSpecializationClassNestedClassesOuter<bool>::CFullTemplateSpecializationClassNestedClassesInner<double>	Object;

		Object.Print(444.444);
	}

	PrintLineSeparator();

	{
		CFullTemplateSpecializationClassNestedClassesOuter<long>::CFullTemplateSpecializationClassNestedClassesInner<short>	Object;

		Object.Print(500);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateClassPartialSpecializationSyntax(void)
{
	PrintLineSeparator();

	{
		// !!!!! Vytvara sa instancia PRIMARY TEMPLATE CLASS.
		CPartialTemplateSpecializationSyntax<int>				Object(100);

		Object.Print();
	}

	PrintLineSeparator();

	{
		int														Value=200;

		// !!!!! Vytvara sa instancia TEMPLATE CLASS PARTIAL SPECIALIZATION.
		CPartialTemplateSpecializationSyntax<int*>				Object(&Value);

		Object.PrintPartialSpecialization();
	}

	PrintLineSeparator();

	{
		double													Value=333.333;

		// !!!!! Vytvara sa instancia TEMPLATE CLASS FULL SPECIALIZATION.
		CPartialTemplateSpecializationSyntax<double*>			Object(&Value);

		Object.PrintFullSpecialization();
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateClassPartialSpecializationLimits(void)
{
	PrintLineSeparator();

	{
		// !!!!! Vola sa PRIMARY TEMPLATE CLASS.
		CPartialSpecializationTemplateClassLimits<CString,10>	Object;

		Object.Print();
	}

	PrintLineSeparator();

	{
		// !!!!! Vola sa TEMPLATE CLASS SPECIALIZATION [<TType,5>], lebo je MORE SPECIALIZED ako PRIMARY TEMPLATE CLASS aj ostatne TEMPLATE CLASS SPECIALIZATIONS.
		CPartialSpecializationTemplateClassLimits<CString,5>	Object;

		Object.Print();
	}

	PrintLineSeparator();

	{
		// !!!!! Vola sa TEMPLATE CLASS SPECIALIZATION [<double,VALUE>], lebo je MORE SPECIALIZED ako PRIMARY TEMPLATE CLASS aj ostatne TEMPLATE CLASS SPECIALIZATIONS.
		CPartialSpecializationTemplateClassLimits<double,7>		Object;

		Object.Print();
	}

	/*
	PrintLineSeparator();

	{
		// !!!!! COMPILER hodi ERROR pretoze TEMPLATE CLASS SPECIALIZATION [<TType,5>] a TEMPLATE CLASS SPECIALIZATION [<double,VALUE>] su ROVNAKO SPECIALIZED a dochadza k AMBIGUITY.
		CPartialSpecializationTemplateClassLimits<double,5>		Object;

		Object.Print();
	}
	*/

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	{
		// !!!!! Vola sa PRIMARY TEMPLATE CLASS.
		CPartialSpecializationTemplateClassLimitsVariadic<>		Object;

		Object.Print();
	}

	PrintLineSeparator();

	{
		// !!!!! Vola sa TEMPLATE CLASS SPECIALIZATION [<TTail,TTypes...>], lebo je MORE SPECIALIZED ako PRIMARY TEMPLATE CLASS.
		CPartialSpecializationTemplateClassLimitsVariadic<CString,int>	Object;

		Object.Print();
	}

	PrintLineSeparator();

	{
		// !!!!! Vola sa TEMPLATE CLASS SPECIALIZATION [<CPartialSpecializationTemplateClassLimitsVariadic<TTypes...>,TTail>], lebo je MORE SPECIALIZED ako PRIMARY TEMPLATE CLASS aj TEMPLATE CLASS SPECIALIZATION [<TTail,TTypes...>].
		CPartialSpecializationTemplateClassLimitsVariadic<CPartialSpecializationTemplateClassLimitsVariadic<CString,int>,double>	Object;

		Object.Print();
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateClassPartialSpecializationNumberOfParameters(void)
{
	PrintLineSeparator();

	{
		// !!!!! Vytvara sa instancia PRIMARY TEMPLATE CLASS.
		CPartialTemplateSpecializationNumberOfParameters		Object(CString(L"Timmy"),12);

		Object.Print();
	}

	PrintLineSeparator();

	{
		int														Value=12;

		// !!!!! Vytvara sa instancia PRIMARY TEMPLATE CLASS.
		CPartialTemplateSpecializationNumberOfParameters		Object(100,&Value);

		Object.Print();
	}

	PrintLineSeparator();

	{
		CPartialTemplateSpecializationNumberOfParametersTest	Test(100);

		// !!!!! Vytvara sa instancia PRIMARY TEMPLATE CLASS.
		CPartialTemplateSpecializationNumberOfParameters<CString(CPartialTemplateSpecializationNumberOfParametersTest::*)(int) const,CString(CPartialTemplateSpecializationNumberOfParametersTest::*)(double) const>	Object(Test,&CPartialTemplateSpecializationNumberOfParametersTest::ToString1,&CPartialTemplateSpecializationNumberOfParametersTest::ToString2);

		Object.Print(200,333.333);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateClassPartialSpecializationPriority(void)
{
	PrintLineSeparator();

	{
		// !!!!! Vytvara sa instancia PRIMARY TEMPLATE CLASS.
		CPartialTemplateSpecializationPriority<int>				Object(100);

		Object.Print();
	}

	PrintLineSeparator();

	{
		// !!!!! Vytvara sa instancia TEMPLATE CLASS SPECIALIZATION [void(TClassName::*)(void) const].
		CPartialTemplateSpecializationPriorityTest				Test(100);
		CPartialTemplateSpecializationPriority<void(CPartialTemplateSpecializationPriorityTest::*)(void) const>	Object(Test,&CPartialTemplateSpecializationPriorityTest::Print1);

		Object.Print();
	}

	PrintLineSeparator();

	{
		// !!!!! Vytvara sa instancia TEMPLATE CLASS SPECIALIZATION [void(TClassName::*)(void) const].
		CPartialTemplateSpecializationPriorityTest				Test(200);
		CPartialTemplateSpecializationPriority<void(CPartialTemplateSpecializationPriorityTest::*)(void) const>	Object(Test,&CPartialTemplateSpecializationPriorityTest::Print2);

		Object.Print();
	}

	PrintLineSeparator();

	{
		// !!!!! Vytvara sa instancia TEMPLATE CLASS SPECIALIZATION [TReturnType(TClassName::*)(void) const].
		CPartialTemplateSpecializationPriorityTest				Test(100);
		CPartialTemplateSpecializationPriority<CString(CPartialTemplateSpecializationPriorityTest::*)(void) const>	Object(Test,&CPartialTemplateSpecializationPriorityTest::ToString1);

		Object.Print();
	}

	PrintLineSeparator();

	{
		// !!!!! Vytvara sa instancia TEMPLATE CLASS SPECIALIZATION [TReturnType(TClassName::*)(void) const].
		CPartialTemplateSpecializationPriorityTest				Test(200);
		CPartialTemplateSpecializationPriority<CString(CPartialTemplateSpecializationPriorityTest::*)(void) const>	Object(Test,&CPartialTemplateSpecializationPriorityTest::ToString2);

		Object.Print();
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateClassPartialSpecializationVariadic(void)
{
	PrintLineSeparator();

	{
		CPartialTemplateSpecializationVariadic<CString>			Object(L"Timmy");

		wcout << Object.Print(L"1 PARAMETER");
	}

	PrintLineSeparator();

	{
		CPartialTemplateSpecializationVariadic<CString,int>		Object(L"Timmy",12);

		wcout << Object.Print(L"2 PARAMETERS");
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateClassPartialSpecializationDefaultAgruments(void)
{
	PrintLineSeparator();

	{
		// !!!!! Vytvara sa instancia PRIMARY TEMPLATE CLASS.
		CPartialTemplateSpecializationDefaultArguments			Object(CString(L"Timmy"),12);

		Object.Print();
	}

	PrintLineSeparator();

	{
		int														Value=100;

		// !!!!! Vytvara sa instancia TEMPLATE CLASS SPECIALIZATION.
		CPartialTemplateSpecializationDefaultArguments<int*>	Object(&Value);

		wcout << L"TEMPLATE CLASS PARTIAL SPECIALIZATION <TType*> - OBJECT TYPE [" << GetTypeInfoName<decltype(Object)>() << L"]." << endl;

		wcout << endl;

		Object.Print();
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! PRIMARY TEMPLATE VARIABLE.
template<typename TType>
TType															TemplateVariablePartialSpecializations1=TType();
//----------------------------------------------------------------------------------------------------------------------
// !!! TEMPLATE VARIABLE SPECIALIZATION.
template<typename TType>
TType*															TemplateVariablePartialSpecializations1<TType*> =nullptr;
//----------------------------------------------------------------------------------------------------------------------
// !!! TEMPLATE VARIABLE SPECIALIZATION.
// !!!!! VARIABLE TYPE NEMUSI byt idenficka ako PARAMETER TYPE.
template<typename TType>
double															TemplateVariablePartialSpecializations1<CTuple<TType>> =1234.56;
//----------------------------------------------------------------------------------------------------------------------
// !!! PRIMARY TEMPLATE VARIABLE.
template<typename TType>
constexpr size_t												TemplateVariablePartialSpecializations2=sizeof(TType);
//----------------------------------------------------------------------------------------------------------------------
// !!! TEMPLATE VARIABLE SPECIALIZATION.
template<typename TType>
constexpr size_t												TemplateVariablePartialSpecializations2<TType*> =sizeof(TType*);
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateVariablePartialSpecializations(void)
{
	PrintLineSeparator();

	{
		int														Value=100;

		wcout << L"PRIMARY TEMPLATE VARIABLE 1 - TYPE [" << GetTypeInfoName<decltype(TemplateVariablePartialSpecializations1<int>)>() << L"] VALUE [" << TemplateVariablePartialSpecializations1<int> << L"]." << endl;
		wcout << L"TEMPLATE VARIABLE SPECIALIZATION 1 <int*> - TYPE [" << GetTypeInfoName<decltype(TemplateVariablePartialSpecializations1<double>)>() << L"] VALUE [" << TemplateVariablePartialSpecializations1<int*> << L"]." << endl;
		wcout << L"TEMPLATE VARIABLE SPECIALIZATION 1 <CString> - TYPE [" << GetTypeInfoName<decltype(TemplateVariablePartialSpecializations1<CTuple<CString>>)>() << L"] VALUE [" << TemplateVariablePartialSpecializations1<CTuple<CString>> << L"]." << endl;

		wcout << endl;

		TemplateVariablePartialSpecializations1<int>++;
		TemplateVariablePartialSpecializations1<int*> =&Value;
		TemplateVariablePartialSpecializations1<CTuple<CString>>+=10;

		wcout << L"PRIMARY TEMPLATE VARIABLE 1 - TYPE [" << GetTypeInfoName<decltype(TemplateVariablePartialSpecializations1<int>)>() << L"] VALUE [" << TemplateVariablePartialSpecializations1<int> << L"]." << endl;
		wcout << L"TEMPLATE VARIABLE SPECIALIZATION 1 <int*> - TYPE [" << GetTypeInfoName<decltype(TemplateVariablePartialSpecializations1<double>)>() << L"] VALUE [" << TemplateVariablePartialSpecializations1<int*> << L"]." << endl;
		wcout << L"TEMPLATE VARIABLE SPECIALIZATION 1 <CString> - TYPE [" << GetTypeInfoName<decltype(TemplateVariablePartialSpecializations1<CTuple<CString>>)>() << L"] VALUE [" << TemplateVariablePartialSpecializations1<CTuple<CString>> << L"]." << endl;
	}

	PrintLineSeparator();

	{
		wcout << L"PRIMARY TEMPLATE VARIABLE 2 - TYPE [" << GetTypeInfoName<decltype(TemplateVariablePartialSpecializations2<int>)>() << L"] VALUE [" << TemplateVariablePartialSpecializations2<int> << L"]." << endl;
		wcout << L"TEMPLATE VARIABLE SPECIALIZATION 2 <short*> - TYPE [" << GetTypeInfoName<decltype(TemplateVariablePartialSpecializations2<short*>)>() << L"] VALUE [" << TemplateVariablePartialSpecializations2<short*> << L"]." << endl;
		wcout << L"TEMPLATE VARIABLE SPECIALIZATION 2 <long double*> - TYPE [" << GetTypeInfoName<decltype(TemplateVariablePartialSpecializations2<long double*>)>() << L"] VALUE [" << TemplateVariablePartialSpecializations2<long double*> << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestTransparentCustomization();
	//TestTemplateFunctionOverloading();
	//TestTemplateFunctionOverloadingSignatures();
	//TestTemplateFunctionOverloadingPartialOrdering();
	//TestTemplateAndNonTemplateFunctionOverloading();
	//TestTemplateFunctionOverloadingPartialOrderingVariadic();
	//TestTemplateClassFullSpecializationsSyntax();
	//TestTemplateClassFullSpecializationsParameters();
	//TestTemplateClassFullSpecializationsMembers();
	//TestTemplateClassFullSpecializationsAndInstantination();
	//TestTemplateFunctionFullSpecializations();
	//TestTemplateVariableFullSpecializations();
	//TestTemplateClassNonTemplateMethodFullSpecializations();
	//TestTemplateClassSpecializedMembers();
	//TestTemplateClassSpecializedFieldsDeclarationDefinition();
	//TestTemplateClassInnerClassSpecialization();
	//TestTemplateClassPartialSpecializationSyntax();
	//TestTemplateClassPartialSpecializationLimits();
	//TestTemplateClassPartialSpecializationNumberOfParameters();
	//TestTemplateClassPartialSpecializationPriority();
	//TestTemplateClassPartialSpecializationVariadic();
	//TestTemplateClassPartialSpecializationDefaultAgruments();
	TestTemplateVariablePartialSpecializations();

	ShowExitLine();

	return(0);
}
//----------------------------------------------------------------------------------------------------------------------