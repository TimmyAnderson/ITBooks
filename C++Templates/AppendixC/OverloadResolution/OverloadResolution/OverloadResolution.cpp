//----------------------------------------------------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <concepts>
#include <cstdint>
#include <vector>
#include <complex>
#include "MyDebug.h"
#include "CClassWithConversionConstructor.h"
#include "CValue.h"
#include "COverloadResolutionForThis.h"
#include "CLValueRValueThisMethods.h"
#include "CConversionSequenceBase.h"
#include "CConversionSequenceDerived.h"
#include "CClassHierarchy1.h"
#include "CClassHierarchy2.h"
#include "CClassHierarchy3.h"
#include "CAggregateClass.h"
#include "CInitializerListConstructors.h"
#include "CFunctionObjectAndSurrogate.h"
#include "COverloadResolutionInDifferentContexts.h"
//----------------------------------------------------------------------------------------------------------------------
#ifdef _MSC_VER
#pragma warning( disable : 6287 )
#pragma warning( disable : 4244 )
#pragma warning( disable : 26800 )
#undef min
#undef max
#endif
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void OverloadResolution1(int Value)
{
	wcout << L"FUNCTION 1 - INT [" << Value << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void OverloadResolution1(double Value)
{
	wcout << L"FUNCTION 1 - DOUBLE [" << Value << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void OverloadResolution2(int Value)
{
	wcout << L"FUNCTION 2 - INT [" << Value << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void OverloadResolution2(char Value)
{
	wcout << L"FUNCTION 2 - CHAR [" << ConvertCharToWideChar(Value) << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void OverloadResolution3(CValue Value)
{
	wcout << L"FUNCTION 3 - INT [" << Value.GetValue() << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
// !!! FUNCTION ma lubovolny pocet PARAMETERS.
void OverloadResolution3(...)
{
	wcout << L"FUNCTION 3 - ELLIPSIS !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void OverloadResolution4(int Value1, double Value2)
{
	wcout << L"FUNCTION 4 - INT [" << Value1 << L"] DOUBLE [" << Value2 << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void OverloadResolution4(long Value1, int Value2)
{
	wcout << L"FUNCTION 4 - LONG [" << Value1 << L"] INT [" << Value2 << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestOverloadResolution(void)
{
	PrintLineSeparator();

	{
		// !!! Zavola sa FUNCTION s PARAMETER TYPE [int].
		// !!! Dochadza k PERFECT MATCH.
		OverloadResolution1(10);

		// !!! Zavola sa FUNCTION s PARAMETER TYPE [double].
		// !!! Dochadza k PERFECT MATCH.
		OverloadResolution1(22.22);
	}

	PrintLineSeparator();

	{
		// !!!!! Zavola sa FUNCTION s PARAMETER TYPE [int], pretoze volanie FUNCTION s PARAMETER TYPE [int] vyzaduje iba TYPE PROMOTION z TYPE [bool] na TYPE [int], kym volanie FUNCTION s PARAMETER TYPE [char] vyzaduje az aplikaciu STANDARD CONVERSION.
		OverloadResolution2(true);

		// !!! Zavola sa FUNCTION s PARAMETER TYPE [char].
		// !!! Jedna sa o PERFECT MATCH.
		OverloadResolution2('X');
	}

	PrintLineSeparator();

	{
		// !!!!! Zavola sa FUNCTION s PARAMETER TYPE [CValue], pretoze volanie FUNCTION s PARAMETER TYPE [CValue] vyzaduje iba STANDARD CONVERSION z TYPE [int] na TYPE [CValue], kym volanie FUNCTION s PARAMETER TYPE [...] vyzaduje az pouzitie ELLIPSIS.
		OverloadResolution3(100);
	}

	PrintLineSeparator();

	{
		// !!!!! Zavola sa FUNCTION s PARAMETER TYPE [...], pretoze TYPE [const wchar_t[15]] nemoze byt CONVERTED na TYPE [CValue].
		OverloadResolution3(L"Timmy Anderson");
	}

	PrintLineSeparator();

	{
		// !!! Zavola sa FUNCTION s PARAMETER TYPE [int] a PARAMETER TYPE [double].
		// !!! Dochadza k PERFECT MATCH.
		OverloadResolution4(10,11.22);

		// !!! Zavola sa FUNCTION s PARAMETER TYPE [long] a PARAMETER TYPE [int].
		// !!! Dochadza k PERFECT MATCH.
		OverloadResolution4(10L,20);

		// !!!!! COMPILER hodi AMBIGUITY ERROR. Je to preto, lebo FUNCTION [void OverloadResolution4(int,double)] ma BEST MATCH pre 1. PARAMETER a FUNCTION [void OverloadResolution4(long,int)] ma BEST MATCH pre 2. PARAMETER. Kedze plati zasada, ze najlepsia kandidatska FUNCTION NESMIE mat HORSI MATCH pre ziaden zo svojich PARAMETERS ako alternativne FUNCTIONS, tak COMPILER hodi AMBIGUITY ERROR.
		//OverloadResolution4(10,20);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CClassWithConversionConstructor<TType> TemplateOverloadResolutionAfterTemplateArgumentsDeduction(const CClassWithConversionConstructor<TType>& Value1, int Value2)
{
	wcout << L"TEMPLATE VALUE 1 [" << Value1.GetValue() << L"] VALUE 2 [" << Value2 << L"] !" << endl;

	return(Value1);
}
//----------------------------------------------------------------------------------------------------------------------
void TestOverloadResolutionAfterTemplateArgumentsDeduction(void)
{
	PrintLineSeparator();

	// !!!!! CODE zbehne OK, pretoze TEMPLATE PARAMETER je EXPLICITNE definovany, a NEROBI sa TEMPLATE ARGUMENTS DEDUCTION.
	// !!!!! V takom pripade je TEMPLATE FUNCTION zaradena do OVERLOAD RESOLUTION a kedze ARGUMENTS vyhovuju PARAMETERS (PERFECT MATCH), tak je FUNCTION vybrana.
	{
		CClassWithConversionConstructor<wchar_t>				Result=TemplateOverloadResolutionAfterTemplateArgumentsDeduction<wchar_t>(L"Timmy Anderson",12);

		wcout << L"RESULT [" << Result.GetValue() << L"] !" << endl;
	}

	/*
	PrintLineSeparator();

	// !!!!! COMPILER hodi ERROR, pretoze TEMPLATE PARAMETER NIE je EXPLICITNE DEFINOVANY a tym padom sa robi TEMPLATE ARGUMENTS DEDUCTION.
	// !!!!! Kedze TEMPLATE ARGUMENT je TYPE [const wchar_t[15]], kym TEMPLATE PARAMETER je TYPE [const CClassWithConversionConstructor<TType>&], NEDOCHADZA k PERFECT MATCH.
	// !!!!! TEMPLATE ARGUMENT TYPE [const wchar_t[15]] vsak JE CONVERTIBLE na TEMPLATE PARAMETER TYPE [const CClassWithConversionConstructor<TType>&], pretoze CLASS 'CClassWithConversionConstructor' obsahuje CONVERSION CONSTRUCTOR s PARAMETER TYPE [const wchar_t*], ktory by sa mohol pouzit na vytvorenie instancie CLASS 'CClassWithConversionConstructor'.
	// !!!!! COMPILER vsak hodi ERROR preto, lebo pri TEMPLATE ARGUMENTS DEDUCTION sa NEAPLIKUJU CONVERSION CONSTRUCTORS ci CONVERSION OPERATORS a TEMPLATE ARGUMENTS DEDUCTION sa vykonava PRED OVERLOAD RESOLUTION. To znamena, ze TEMPLATE ARGUMENTS DEDUCTION za TEMPLATE PARAMETER dosadi TYPE [const wchar_t[15]], lenze ocakavany RETURN VALUE TYPE je TYPE [CClassWithConversionConstructor<wchar_t>] a TYPE [const wchar_t[15]] nemoze byt konvertovany na TYPE [wchar_t]. C++ teda tuto FUNCTION vyradi z INITIAL OVERLOAD SET, pretoze nesedia TYPES a VOBEC ju NEZARADI do procesu OVERLOAD RESOLUTION.
	{
		CClassWithConversionConstructor<wchar_t>				Result=TemplateOverloadResolutionAfterTemplateArgumentsDeduction(L"Timmy Anderson",12);

		wcout << L"RESULT [" << Result.GetValue() << L"] !" << endl;
	}
	*/

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void TemplateTemplateArgumentsDeduction1(TType&& Value1, TType&& Value2)
{
	wcout << L"TEMPLATE VALUE 1 [" << Value1 << L"] VALUE 2 [" << Value2 << L"] !" << endl;

	wcout << L"TEMPLATE - TYPE [" << GetTypeInfoName<TType>() << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void TemplateTemplateArgumentsDeduction2(TType&& Value1, double&& Value2)
{
	wcout << L"TEMPLATE VALUE 1 [" << Value1 << L"] VALUE 2 [" << Value2 << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateArgumentsDeduction(void)
{
	PrintLineSeparator();

	// !!! CODE zbehne OK a DEDUCED TYPE je TYPE [double].
	// !!! Je to preto, lebo OBE PARAMETERS su RVALUES.
	{
		TemplateTemplateArgumentsDeduction1(1.2,3.4);
	}

	PrintLineSeparator();

	// !!! CODE zbehne OK a DEDUCED TYPE je TYPE [double].
	// !!! Je to preto, lebo OBE PARAMETERS su LVALUES a TEMPLATES, ktore maju TEMPLATE PARAMETER REFERENCE na RVALUE akceptuju ako TEMPLATE ARGUMENT LVALUES.
	{
		double													Value1=1.2;
		double													Value2=3.4;

		TemplateTemplateArgumentsDeduction1(Value1,Value2);
	}

	/*
	PrintLineSeparator();

	// !!!!! COMPILER hodi ERROR, pretoze 1. TEMPLATE ARGUMENT je LVAULE a 2. TEMPLATE PARAMETER je RVALUE a na zaklade toho spravi C++ TEMPLATE ARGUMENTS DEDUCTION. Avsak TEMPLATE FUNCTION ocakava, ze OBE TEMPLATE ARGUMENTS maju ROVNAKY TYPE.
	{
		double													Value=1.2;

		TemplateTemplateArgumentsDeduction1(Value,3.4);
	}
	*/

	/*
	PrintLineSeparator();

	// !!!!! COMPILER hodi ERROR, pretoze 2. TEMPLATE ARGUMENT je LVALUE [double] co nezodpoveda 2. NON-TEMPLATE PARAMETER, ktory je RVALUE [double&&]. A kedze 2. PARAMETER je NON-TEMPLATE PARAMETER, tak sa neaplikuje konverzia z LVALUE ARGUMENTS na RVALUE PARAMETERS, ako sa to robi pri TEMPLATE PARAMETERS.
	{
		double													Value1=1.2;
		double													Value2=3.4;

		TemplateTemplateArgumentsDeduction2(Value1,Value2);
	}
	*/

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestOverloadResolutionForThisParameter(void)
{
	PrintLineSeparator();

	{
		COverloadResolutionForThis								Value(L"Timmy Anderson");

		wcout << L"VALUE [" << Value.GetValue() << L"] !" << endl;
 
		// !!! CODE zbehne OK, pretoze PARAMETER je TYPE [size_t] a tym padom existuje PERFECT MATCH pre volanie OPERATOR [wchar_t& operator[](size_t Index)].
		{
			size_t												Index1=5;

			Value[Index1]=L'1'; 

			wcout << L"VALUE [" << Value.GetValue() << L"] !" << endl;
		}

		// !!!!! COMPILER v niektorych implementaciach C++ moze hodit AMBIGUITY ERROR.
		// !!!!! Je to dosledok toho, ze ARGUMENT 'Index' je TYPE [int], ktory OPERATOR [wchar_t& operator[](size_t Index)] ocakava PARAMETER TYPE [size_t]. Ci COMPILER hodi ERROR zavisi od toho ako je definovany TYPE [size_t].
		// !!!!! V pripade VC++ aj G++ ak su COMPILED pre X64 ku COMPILATION ERROR NEODJDE. Je to preto, lebo COMPILER vybera z nasledujucich moznosti.
		// !!!!! 1. Zavolat OPERATOR [wchar_t& operator[](std::size_t Index)].
		// !!!!! 2. Zavolat OPERATOR [operator wchar_t*(void)] a NASLEDNE volat BUILD-IN OPERATOR [OPERATOR[]] pre POINTERS.
		// !!!!! Pri posudzovani moznosti 1 volat OPERATOR [wchar_t& operator[](std::size_t Index)] sa musi vykonat CONVERSION ARGUMENT TYPE [int] na PARAMETER TYPE [size_t], ktory ma realny TYPE [unsigned int64_t]. To vedie k aplikacii OVERLOAD RESOLUTION RULE 'MATCH WITH STANDARD CONVERSIONS ONLY'.
		// !!!!! Pri posudzovani moznosti 2 volat OPERATOR [operator wchar_t*(void)] a NASLEDNE volat BUILD-IN OPERATOR [OPERATOR[]] pre POINTERS je nutne vykonat CONVERSION ARGUMENT TYPE [int] na BUILD-IN OPERATOR [OPERATOR[]] PARAMETER TYPE [ptrdiff_t], ktory ma realny TYPE [int64_t]. CONVERSION TYPE [int] na TYPE [int64_t] sice vyzaduje aplikaciu RULE 'MATCH WITH PROMOTION', avsak pouzitie OPERATOR [operator wchar_t*(void)] vyzaduje aplikaciu RULE 'MATCH WITH USER DEFINED CONVERSIONS'.
		// !!!!! No a kedze OVERLOAD RESOLUTION RULE 'MATCH WITH STANDARD CONVERSIONS ONLY' ma VYSSIU PRIORITU ako OVERLOAD RESOLUTION RULE 'MATCH WITH USER DEFINED CONVERSIONS', tak sa pouzije [wchar_t& operator[](std::size_t Index)].
		{
			int													Index2=5;

			Value[Index2]=L'2'; 

			wcout << L"VALUE [" << Value.GetValue() << L"] !" << endl;
		}

		// !!!!! COMPILER VC++ a G++ ak je CODE COMPILED ako X64 hodi AMBIGUITY ERROR.
		// !!!!! Je to dosledok toho, ze ARGUMENT 'Index' je TYPE [int64_t], ktory OPERATOR [wchar_t& operator[](size_t Index)] ocakava PARAMETER TYPE [size_t], ktory ma realny TYPE [unsigned int64_t]. To znamena, ze OPERATOR [wchar_t& operator[](size_t Index)] NIE JE PERFECT MATCH.
		// !!!!! Ak je CODE COMPILED por X64, COMPILER vybera z nasledujucich moznosti.
		// !!!!! 1. Zavolat OPERATOR [wchar_t& operator[](std::size_t Index)].
		// !!!!! 2. Zavolat OPERATOR [operator wchar_t*(void)] a NASLEDNE volat BUILD-IN OPERATOR [OPERATOR[]] pre POINTERS.
		// !!!!! Pouzitie moznosti 1 znamena, ze na volanie OPERATOR [wchar_t& operator[](std::size_t Index)] je nutne vykonat CONVERSION AGRUMENT TYPE [int64_t] na PARAMETER TYPE [size_t], ktory ma realny TYPE [unsigned int64_t]. To znamena, ze je treba aplikovat OVERLOAD RESOLUTION RULE 'MATCH WITH STANDARD CONVERSIONS ONLY'.
		// !!!!! Pouzitie moznosti 2 znamena, ze na volanie OPERATOR [operator wchar_t*(void)] a NASLEDNE volanie BUILD-IN OPERATOR [OPERATOR[]] pre POINTERS NIE je nutne vykonat CONVERSION AGRUMENT TYPE [int64_t] na PARAMETER TYPE [ptrdiff_t], ktory ma realny TYPE [int64_t]. To vedie k PERFECT MATCH. Avsak pouzitie OPERATOR [operator wchar_t*(void)] vyzaduje aplikaciu OVERLOAD RESOLUTION RULE 'MATCH WITH USER DEFINED CONVERSIONS'.
		// !!!!! COMPILER hodi COMPILATION ERROR, pretoze sa nevie rozhodnut medzi aplikaciou OVERLOAD RESOLUTION RULE 'MATCH WITH STANDARD CONVERSIONS ONLY' a aplikaciou OVERLOAD RESOLUTION RULE 'MATCH WITH USER DEFINED CONVERSIONS'.
		/*
		{
			int64_t												Index3=5;

			Value[Index3]=L'3'; 

			wcout << L"VALUE [" << Value.GetValue() << L"] !" << endl;
		}
		*/
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestLValueRValueThisMethods(void)
{
	PrintLineSeparator();

	// !!! CODE zbehne OK, pretoze OBJECT 'Object' je LVALUE a ten moze volat METHOD, ktora pouziva DEFAULT CONVENTION pre IMPLICITNY PARAMETER [*this].
	{
		CLValueRValueThisMethods								Object;

		Object.OldStyleThisParameter();
	}

	PrintLineSeparator();

	// !!! CODE zbehne OK, pretoze OBJECT 'Object' je LVALUE a ten moze volat METHOD, ktora je oznacena, ze jej IMPLICITNY PARAMETER [*this] bude LVALUE.
	{
		CLValueRValueThisMethods								Object;

		Object.LValueReferenceThisParameter();
	}

	/*
	PrintLineSeparator();

	// !!!!! COMPILER hodi ERROR, pretoze OBJECT 'Object' je LVALUE a ten nemoze volat METHOD, ktora je oznacena, ze jej IMPLICITNY PARAMETER [*this] bude RVALUE.
	{
		CLValueRValueThisMethods								Object;

		Object.RValueReferenceThisParameter();
	}
	*/

	PrintLineSeparator();

	// !!! CODE zbehne OK, pretoze OBJECT je RVALUE a ten moze volat METHOD, ktora pouziva DEFAULT CONVENTION pre IMPLICITNY PARAMETER [*this].
	{
		CLValueRValueThisMethods().OldStyleThisParameter();
	}

	/*
	PrintLineSeparator();

	// !!!!! COMPILER hodi ERROR, pretoze OBJECT je RVALUE a ten nemoze volat METHOD, ktora je oznacena, ze jej IMPLICITNY PARAMETER [*this] bude LVALUE.
	{
		CLValueRValueThisMethods().LValueReferenceThisParameter();
	}
	*/

	PrintLineSeparator();

	// !!! CODE zbehne OK, pretoze OBJECT je RVALUE a ten moze volat METHOD, ktora je oznacena, ze jej IMPLICITNY PARAMETER [*this] bude RVALUE.
	{
		CLValueRValueThisMethods().RValueReferenceThisParameter();
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void PerfectMatch1(int& Value)
{
	wcout << L"FUNCTION [void PerfectMatch1(int& Value)] VALUE [" << Value << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void PerfectMatch1(const int& Value)
{
	wcout << L"FUNCTION [void PerfectMatch1(const int& Value)] VALUE [" << Value << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void PerfectMatch2(const CValue& Value)
{
	wcout << L"FUNCTION [void PerfectMatch2(const CValue& Value)] VALUE [" << Value.GetValue() << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void PerfectMatch2(CValue&& Value)
{
	wcout << L"FUNCTION [void PerfectMatch2(CValue&& Value)] VALUE [" << Value.GetValue() << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void PerfectMatch3(int Value)
{
	wcout << L"FUNCTION [void PerfectMatch3(int Value)] VALUE [" << Value << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void PerfectMatch3(int& Value)
{
	wcout << L"FUNCTION [void PerfectMatch3(int& Value)] VALUE [" << Value << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void PerfectMatch3(const int& Value)
{
	wcout << L"FUNCTION [void PerfectMatch3(const int& Value)] VALUE [" << Value << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestPerfectMatch(void)
{
	PrintLineSeparator();

	{
		int														Value=100;

		// !!! Zavola sa FUNCTION s TYPE [int&], pretoze EXPRESSION 'Value' je LVALUE.
		PerfectMatch1(Value);

		// !!! Zavola sa FUNCTION s TYPE [const int&], pretoze EXPRESSION '200' je RVALUE.
		PerfectMatch1(200);
	}

	PrintLineSeparator();

	{
		CValue													Value=100;
		CValue&&												ReferenceValue=move(Value);

		// !!! Zavola sa FUNCTION s TYPE [const CValue&], pretoze EXPRESSION 'ReferenceValue' je LVALUE, hoci ma TYPE [CValue&&].
		PerfectMatch2(ReferenceValue);

		// !!! Zavola sa FUNCTION s TYPE [CValue&&], pretoze EXPRESSION 'CValue(200)' je RVALUE.
		PerfectMatch2(CValue(200));

		// !!! Zavola sa FUNCTION s TYPE [CValue&&], pretoze EXPRESSION 'move(ReferenceValue)' je RVALUE.
		PerfectMatch2(move(ReferenceValue));
	}

	PrintLineSeparator();

	{
		CValue													Value=100;

		// !!! Vola sa NO-CONST verzia METHOD.
		Value.ConstAndNoConst();

		// !!! Vola sa CONST verzia METHOD, kedze NO-CONST verzia neexistuje.
		Value.ConstOnly();
	}

	/*
	PrintLineSeparator();

	{
		int														Value=100;

		// !!!!! COMPILER hodi ERROR, pretoze FUNCTION moze byt volana pre TYPE [int], TYPE [int&] a TYPE [const int&].
		PerfectMatch3(Value);

		// !!!!! COMPILER hodi ERROR, pretoze FUNCTION moze byt volana pre TYPE [int] a TYPE [const int&].
		PerfectMatch3(200);
	}
	*/

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TThis>
void TemplateOverloadResolutionTemplates1(TThis This)
{
	wcout << L"TEMPLATE FUNCTION [void TemplateOverloadResolutionTemplates2(TThis This)] CALLED ! VALUE [" << This << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
// !!! NON-TEMPLATE FUNCTION.
void TemplateOverloadResolutionTemplates1(int This)
{
	wcout << L"TEMPLATE FUNCTION [void TemplateOverloadResolutionTemplates1(int This)] CALLED ! VALUE [" << This << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TThis>
void TemplateOverloadResolutionTemplates2(TThis This)
{
	wcout << L"TEMPLATE FUNCTION [void TemplateOverloadResolutionTemplates2(TThis This)] CALLED ! VALUE [" << This << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
// !!! TEMPLATE SPECIALIZATION.
template<>
void TemplateOverloadResolutionTemplates2<int>(int This)
{
	wcout << L"TEMPLATE FUNCTION [void TemplateOverloadResolutionTemplates2<int>(int This)] CALLED ! VALUE [" << This << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TThis>
void TemplateOverloadResolutionTemplates3(TThis This)
{
	wcout << L"TEMPLATE FUNCTION [void TemplateOverloadResolutionTemplates3(TThis This)] CALLED ! VALUE [" << This << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! METHOD pouzivana pre RECURSION CASES.
template<typename TThis, typename... TTypes>
void TemplateOverloadResolutionTemplates3(TThis This, TTypes... Others)
{
	wcout << L"TEMPLATE FUNCTION [void TemplateOverloadResolutionTemplates3(TThis This, TTypes... Others)] CALLED ! VALUE [" << This << L"] !" << endl;

	TemplateOverloadResolutionTemplates3(Others...);
}
//----------------------------------------------------------------------------------------------------------------------
void TestOverloadResolutionTemplates(void)
{
	PrintLineSeparator();

	{
		// !!!!! Vola sa NON-TEMPLATE FUNCTION, pretoze ta ma prioritu pred TEMPLATE FUNCTION.
		TemplateOverloadResolutionTemplates1(100);

		// !!! Vola sa TEMPLATE FUNCTION.
		TemplateOverloadResolutionTemplates1(100.222);
	}

	PrintLineSeparator();

	{
		// !!!!! Vola sa TEMPLATE FUNCTION SPECIALIZATION, pretoze ta ma prioritu pred TEMPLATE FUNCTION.
		TemplateOverloadResolutionTemplates2(100);

		// !!! Vola sa TEMPLATE FUNCTION.
		TemplateOverloadResolutionTemplates2(100.222);
	}

	PrintLineSeparator();

	{
		// !!!!! Vola sa TEMPLATE FUNCTION BEZ TEMPLATE PARAMETER PACK, pretoze ta je vzdy preferovana pred volanim TEMPLATE FUNCTION s TEMPLATE PARAMETER PACK.
		TemplateOverloadResolutionTemplates3(100);
	}

	PrintLineSeparator();

	{
		TemplateOverloadResolutionTemplates3(L"Timmy",L"Anderson",12);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void ConversionSequence1(int Value)
{
	wcout << L"TEMPLATE FUNCTION [void ConversionSequence1(int Value)] CALLED ! VALUE [" << Value << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void ConversionSequence2(short Value)
{
	wcout << L"TEMPLATE FUNCTION [void ConversionSequence2(short Value)] CALLED ! VALUE [" << Value << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void ConversionSequence2(int Value)
{
	wcout << L"TEMPLATE FUNCTION [void ConversionSequence2(int Value)] CALLED ! VALUE [" << Value << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestConversionSequence(void)
{
	PrintLineSeparator();

	{
		CConversionSequenceDerived								Object(100);

		// !!! Pri IMPLICIT CONVERSION TYPE [CConversionSequenceDerived] na TYPE [int] sa vykonava nasledujuce CONVERSION SEQUENCE.
		// !!! 1. Vykona sa STANDARD CONVERSION z TYPE [CConversionSequenceDerived] na TYPE [CConversionSequenceBase], ktora ma definovany CONVERSION OPERATOR.
		// !!! 2. Vykona sa USER DEFINED CONVERSION z TYPE [CConversionSequenceBase] na TYPE [short].
		// !!! 3. Vykona sa STANDARD CONVERSION z TYPE [short] na TYPE [int].
		ConversionSequence1(Object);
	}

	PrintLineSeparator();

	{
		CConversionSequenceDerived								Object(100);

		// !!! Zavola sa FUNCTION s PARAMETER TYPE [short].
		// !!! Pri IMPLICIT CONVERSION TYPE [CConversionSequenceDerived] na TYPE [short] sa vykonava nasledujuce CONVERSION SEQUENCE.
		// !!! 1. Vykona sa STANDARD CONVERSION z TYPE [CConversionSequenceDerived] na TYPE [CConversionSequenceBase], ktora ma definovany CONVERSION OPERATOR.
		// !!! 2. Vykona sa USER DEFINED CONVERSION z TYPE [CConversionSequenceBase] na TYPE [short].
		ConversionSequence2(Object);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void PointerConversionsConversionPriorities1(bool Value)
{
	wcout << L"FUNCTION [void PointerConversionsConversionPriorities1(bool Value)] CALLED with VALUE [" << Value << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void PointerConversionsConversionPriorities2(bool Value)
{
	wcout << L"FUNCTION [void PointerConversionsConversionPriorities2(bool Value)] CALLED with VALUE [" << Value << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void PointerConversionsConversionPriorities2(void* RawPointer)
{
	CClassHierarchy1*											Pointer=(CClassHierarchy1*) RawPointer;

	wcout << L"FUNCTION [void PointerConversionsConversionPriorities2(void* RawPointer)] CALLED with VALUE [" << Pointer->GetValue() << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void PointerConversionsConversionPriorities3(bool Value)
{
	wcout << L"FUNCTION [void PointerConversionsConversionPriorities3(bool Value)] CALLED with VALUE [" << Value << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void PointerConversionsConversionPriorities3(void* RawPointer)
{
	CClassHierarchy1*											Pointer=(CClassHierarchy1*) RawPointer;

	wcout << L"FUNCTION [void PointerConversionsConversionPriorities3(void* RawPointer)] CALLED with VALUE [" << Pointer->GetValue() << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void PointerConversionsConversionPriorities3(CClassHierarchy1* Pointer)
{
	wcout << L"FUNCTION [void PointerConversionsConversionPriorities3(CClassHierarchy1* Pointer)] CALLED with VALUE [" << Pointer->GetValue() << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void PointerConversionsHierarchyConversions(CClassHierarchy1* Pointer)
{
	wcout << L"FUNCTION [void PointerConversionsHierarchyConversions(CClassHierarchy1* Pointer)] CALLED with VALUE [" << Pointer->GetValue() << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void PointerConversionsHierarchyConversions(CClassHierarchy2* Pointer)
{
	wcout << L"FUNCTION [void PointerConversionsHierarchyConversions(CClassHierarchy2* Pointer)] CALLED with VALUE [" << Pointer->GetValue() << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestPointerConversions(void)
{
	PrintLineSeparator();

	{
		CClassHierarchy3										Object(L"HIERARCHY 3");
		CClassHierarchy3*										PointerToObject=&Object;

		// !!! VOLA sa FUNCTION s PARAMETER TYPE [bool], pretoze CONVERSION POINTERS na TYPE [bool] je mozny.
		PointerConversionsConversionPriorities1(PointerToObject);
	}

	PrintLineSeparator();

	{
		CClassHierarchy3										Object(L"HIERARCHY 3");

		// !!!!! Vola sa FUNCTION s PARAMETER TYPE [void*], pretoze volanie FUNCTION s PARAMETER TYPE [void*] ma vyssiu prioritu ako volanie FUNCTION s PARAMETER TYPE [bool].
		PointerConversionsConversionPriorities2(&Object);
	}

	PrintLineSeparator();

	{
		CClassHierarchy3										Object(L"HIERARCHY 3");

		// !!!!! Vola sa FUNCTION s PARAMETER TYPE [CClassHierarchy1*], pretoze volanie FUNCTION s PARAMETER TYPE POINTER na BASE CLASS ma vyssiu prioritu ako volanie FUNCTION s PARAMETER TYPE [void*] aj FUNCTION s PARAMETER TYPE [bool].
		PointerConversionsConversionPriorities3(&Object);
	}

	PrintLineSeparator();

	{
		CClassHierarchy3										Object(L"HIERARCHY 3");

		// !!!!! Vola sa FUNCTION s PARAMETER TYPE [CClassHierarchy2*], pretoze pri volani FUNCTION s PARAMETER TYPE POINTER na BASE CLASS a FUNCTION s PARAMETER TYPE POINTER na DERIVED CLASS, C++ vyberie FUNCTION s PARAMETER TYPE POINTER na DERIVED CLASS.
		PointerConversionsHierarchyConversions(&Object);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void PointerToMemberConversionsConversionPriorities1(bool Value)
{
	wcout << L"FUNCTION [void PointerToMemberConversionsConversionPriorities1(bool Value)] CALLED with VALUE [" << Value << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void PointerToMemberConversionsConversionPriorities2(bool Value)
{
	wcout << L"FUNCTION [void PointerToMemberConversionsConversionPriorities2(bool Value)] CALLED with VALUE [" << Value << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void PointerToMemberConversionsConversionPriorities2(void(CClassHierarchy2::*PointerToMember)(const wstring&))
{
	CClassHierarchy2											Object(L"HIERARCHY 2");

	wcout << L"FUNCTION [void PointerToMemberConversionsConversionPriorities2(void(CClassHierarchy2::*PointerToMember)(const wstring&))] CALLED !" << endl;
	(Object.*PointerToMember)(L"222");
}
//----------------------------------------------------------------------------------------------------------------------
void PointerToMemberConversionsHierarchyConversions(void(CClassHierarchy2::*PointerToMember)(const wstring&))
{
	CClassHierarchy2											Object(L"HIERARCHY 2");

	wcout << L"FUNCTION [void PointerToMemberConversionsHierarchyConversions(void(CClassHierarchy2::*PointerToMember)(const wstring&))] CALLED !" << endl;
	(Object.*PointerToMember)(L"222");
}
//----------------------------------------------------------------------------------------------------------------------
void PointerToMemberConversionsHierarchyConversions(void(CClassHierarchy3::*PointerToMember)(const wstring&))
{
	CClassHierarchy3											Object(L"HIERARCHY 3");

	wcout << L"FUNCTION [void PointerToMemberConversionsHierarchyConversions(void(CClassHierarchy3::*PointerToMember)(const wstring&))] CALLED !" << endl;
	(Object.*PointerToMember)(L"333");
}
//----------------------------------------------------------------------------------------------------------------------
void TestPointerToMemberConversions(void)
{
	PrintLineSeparator();

	{
		void (CClassHierarchy1::*PointerToMember1)(const wstring&);
		void (CClassHierarchy1::*PointerToMember2)(const wstring&);

		PointerToMember1=&CClassHierarchy1::MyFunction;
		PointerToMember2=nullptr;

		// !!! VOLA sa FUNCTION s PARAMETER TYPE [bool], pretoze CONVERSION POINTERS na MEMBERS na TYPE [bool] je mozny.
		PointerToMemberConversionsConversionPriorities1(PointerToMember1);

		// !!! VOLA sa FUNCTION s PARAMETER TYPE [bool], pretoze CONVERSION POINTERS na MEMBERS na TYPE [bool] je mozny.
		PointerToMemberConversionsConversionPriorities1(PointerToMember2);
	}

	PrintLineSeparator();

	{
		void (CClassHierarchy1::*PointerToMember)(const wstring&);

		PointerToMember=&CClassHierarchy1::MyFunction;

		// !!! VOLA sa FUNCTION s PARAMETER TYPE [void(CClassHierarchy2::*PointerToMember)(const wstring&)], pretoze CONVERSION POINTERS na MEMBERS na BASE CLASS na POINTERS na MEMBERS na DERIVED CLASS ma VYSSIU PRIORITU ako CONVERSION na TYPE [bool].
		PointerToMemberConversionsConversionPriorities2(PointerToMember);
	}
	PrintLineSeparator();

	{
		void (CClassHierarchy1::*PointerToMember)(const wstring&);

		PointerToMember=&CClassHierarchy1::MyFunction;

		// !!!!! Zavola sa FUNCTION s PARAMETER TYPE [void(CClassHierarchy2::*PointerToMember)(const wstring&)]. Je to preto, lebo ked C++ ma vybrat medzi OVERLOADED FUNCTIONS, ktore maju ako PARAMETERS POINTERS TO MEMBERS, tak v pripade, ze nedochadza k PERFECT MATCH (FUNCTION s PARAMETER TYPE [void(CClassHierarchy1::*PointerToMember)(const wstring&)]), tak vyberie tu, ktora je MENEJ DERIVED. Kedze TYPE [void(CClassHierarchy2::*PointerToMember)(const wstring&)] je MENEJ DERIVED ako TYPE [void(CClassHierarchy3::*PointerToMember)(const wstring&)], vola sa FUNCTION s PARAMETER TYPE [void(CClassHierarchy2::*PointerToMember)(const wstring&)].
		PointerToMemberConversionsHierarchyConversions(PointerToMember);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void InitializerListConversions1(initializer_list<int> Values)
{
	wstringstream												Stream;
	int															Count=0;

	for(int Value : Values)
	{
		if (Count++>0)
		{
			Stream << L',';
		}

		Stream << Value;
	}

	wcout << L"FUNCTION [void InitializerListConversions1(initializer_list<int> Values)] CALLED with VALUES [" << Stream.str() << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void InitializerListConversions1(initializer_list<wstring> Values)
{
	wstringstream												Stream;
	int															Count=0;

	for(const wstring& Value : Values)
	{
		if (Count++>0)
		{
			Stream << L',';
		}

		Stream << Value;
	}

	wcout << L"FUNCTION [void InitializerListConversions1(initializer_list<wstring> Values)] CALLED with VALUES [" << Stream.str() << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void InitializerListConversions2(vector<int> const& Values)
{
	wstringstream												Stream;

	for(size_t Index=0;Index<Values.size();Index++)
	{
		if (Index>0)
		{
			Stream << L',';
		}

		int														Value=Values[Index];

		Stream << Value;
	}

	wcout << L"FUNCTION [void InitializerListConversions2(vector<int> const& Values)] CALLED with VALUES [" << Stream.str() << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void InitializerListConversions3(const complex<double>& Value)
{
	wcout << L"FUNCTION [void InitializerListConversions3(const complex<double>& Value)] CALLED with REAL VALUE [" << Value.real() << L"] and IMAGINARY VALUE [" << Value.imag() << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void InitializerListConversions4(const CAggregateClass& Value)
{
	wcout << L"FUNCTION [void InitializerListConversions4(const CAggregateClass& Value)] CALLED with VALUE [" << Value.GetValue1() << L"] and VALUE [" << Value.GetValue2() << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void InitializerListConversions5(initializer_list<char> Values)
{
	wstringstream												Stream;
	int															Count=0;

	for(char Value : Values)
	{
		if (Count++>0)
		{
			Stream << L',';
		}

		Stream << ConvertCharToWideChar(Value);
	}

	wcout << L"FUNCTION [void InitializerListConversions5(initializer_list<char> Values)] CALLED with VALUES [" << Stream.str() << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void InitializerListConversions5(initializer_list<int> Values)
{
	wstringstream												Stream;
	int															Count=0;

	for(int Value : Values)
	{
		if (Count++>0)
		{
			Stream << L',';
		}

		Stream << Value;
	}

	wcout << L"FUNCTION [void InitializerListConversions5(initializer_list<int> Values)] CALLED with VALUES [" << Stream.str() << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestInitializerListConversions(void)
{
	PrintLineSeparator();

	{
		// !!! Vola sa FUNCTION s TYPE [initializer_list<int>].
		InitializerListConversions1({10,20,30,40});
	}

	PrintLineSeparator();

	{
		// !!! Vola sa FUNCTION s TYPE [initializer_list<wstring>].
		InitializerListConversions1({L"Timmy",L"Jenny",L"Josh"});
	}

	PrintLineSeparator();

	{
		// !!! INITIALIZER LIST je CONVERTED na TYPE [vector<int>].
		InitializerListConversions2({10,20,30,40});
	}

	PrintLineSeparator();

	{
		// !!! INITIALIZER LIST je CONVERTED na TYPE [complex<double>].
		InitializerListConversions3({10,20});
	}

	PrintLineSeparator();

	{
		// !!! CLASS 'CAggregateClass' je AGGREGATE CLASS, ktory je mozne inicializovat pomocou INITIALIZER LIST.
		InitializerListConversions4({10,20});
	}

	PrintLineSeparator();

	{
		// !!! Zavola sa FUNCTION s PARAMETER TYPE [initializer_list<char> Values].
		// !!! C++ musi vykonat OVERLOAD RESOLUTION pre nasledujuce FUNCTIONS.
		// !!! 1. FUNCTION s PARAMETER TYPE [initializer_list<char>].
		// !!! 2. FUNCTION s PARAMETER TYPE [initializer_list<int>].
		// !!!!! C++ sa rozhodne pre FUNCTION s PARAMETER TYPE [initializer_list<char>]. Je to preto, lebo vsetky ITEMS INITIALIZER LIST maju TYPE [char] tak ako TYPE PARAMETER CLASS [initializer_list<char>]. To znamena, ze dochadza k PERFECT MATCH. C++ NEVYBERIE FUNCTION s PARAMETER TYPE [initializer_list<int>], pretoze tu je pre vsetky ITEMS INITIALIZER LIST potrebne aplikovat OVERLOAD RESOLUTION RULE 'MATCH WITH PROMOTION' a tym padom sa jedna o HORSI MATCH.
		InitializerListConversions5({'T','i','m','m','y','\0'});
	}

	PrintLineSeparator();

	{
		// !!! Zavola sa FUNCTION s PARAMETER TYPE [initializer_list<int> Values].
		// !!! C++ musi vykonat OVERLOAD RESOLUTION pre nasledujuce FUNCTIONS.
		// !!! 1. FUNCTION s PARAMETER TYPE [initializer_list<char>].
		// !!! 2. FUNCTION s PARAMETER TYPE [initializer_list<int>].
		// !!!!! C++ sa rozhodne pre FUNCTION s PARAMETER TYPE [initializer_list<int>]. Je to preto, lebo pri FUNCTION s PARAMETER TYPE [initializer_list<char>] je treba pre posledny ITEM INITIALIZER LIST '0' aplikovat OVERLOAD RESOLUTION RULE 'MATCH WITH STANDARD CONVERSIONS ONLY'. Kedze C++ aplikuje NAJHORSI mozny OVERLOAD RESOLUTION RULE na celu FUNCTION, tak FUNCTION ma OVERLOAD RESOLUTION RULE 'MATCH WITH STANDARD CONVERSIONS ONLY'. Naopak, pri posudzivani FUNCTION s PARAMETER TYPE [initializer_list<int>] pre prvych 5 ITEMS je treba aplikovat OVERLOAD RESOLUTION RULE 'MATCH WITH PROMOTION' a posledny ITEM je TYPE [int], takze je to PERFECT MATCH. Tym padom pre celu FUNCTION s PARAMETER TYPE [initializer_list<int>] je potrebne aplikovat OVERLOAD RESOLUTION RULE 'MATCH WITH PROMOTION' a to je lepsi OVERLOAD RESOLUTION RULE ako OVERLOAD RESOLUTION RULE 'MATCH WITH STANDARD CONVERSIONS ONLY'. Preto je vybrata FUNCTION s PARAMETER TYPE [initializer_list<int>].
		InitializerListConversions5({'T','i','m','m','y',0});
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void InitializerListConstructors1(CInitializerListConstructors<int> Value)
{
	wstringstream												Stream;
	const vector<int>											List=Value.GetList();

	for(size_t Index=0;Index<List.size();Index++)
	{
		if (Index>0)
		{
			Stream << L',';
		}

		int														ListValue=List[Index];

		Stream << ListValue;
	}

	wcout << L"FUNCTION [void InitializerListConstructors1(CInitializerListConstructors<int> Value)] CALLED with LIST [" << Stream.str() << L"] VALUE 1 [" << Value.GetValue1() << L"] VALUE 2 [" << Value.GetValue2() << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void InitializerListConstructors2(CInitializerListConstructors<wstring> Value)
{
	wstringstream												Stream;
	const vector<wstring>										List=Value.GetList();

	for(size_t Index=0;Index<List.size();Index++)
	{
		if (Index>0)
		{
			Stream << L',';
		}

		wstring													ListValue=List[Index];

		Stream << ListValue;
	}

	wcout << L"FUNCTION [void InitializerListConstructors2(CInitializerListConstructors<wstring> Value)] CALLED with LIST [" << Stream.str() << L"] VALUE 1 [" << Value.GetValue1() << L"] VALUE 2 [" << Value.GetValue2() << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestInitializerListConstructors(void)
{
	PrintLineSeparator();

	{
		// !!! Vola sa CONTRUCTOR s PARAMETER TYPE [initializer_list<TType> Values].
		InitializerListConstructors1({1,2,3,4,5});
	}

	PrintLineSeparator();

	{
		// !!! Vola sa CONTRUCTOR s PARAMETER TYPE [initializer_list<TType> Values].
		InitializerListConstructors1({1,2});
	}

	PrintLineSeparator();

	{
		// !!! Vola sa CONTRUCTOR s PARAMETER TYPE [initializer_list<TType> Values].
		InitializerListConstructors1({1u,2});
	}

	PrintLineSeparator();

	{
		// !!! Vola sa CONTRUCTOR s PARAMETER TYPE [initializer_list<TType> Values].
		InitializerListConstructors2({L"Timmy",L"Jenny",L"Josh"});
	}

	PrintLineSeparator();

	{
		// !!! Vola sa CONTRUCTOR s PARAMETER TYPE [unsigned int] a PARAMETER TYPE [const TType&].
		InitializerListConstructors2({10,L"Timmy"});
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestFunctionObjectAndSurrogate(void)
{
	PrintLineSeparator();

	{
		CFunctionObjectAndSurrogate								Object;

		// !!! Zavola sa OPERATOR [OPERATOR()].
		Object(10.1,20.2);
	}

	PrintLineSeparator();

	{
		CFunctionObjectAndSurrogate								Object;

		// !!! Zavola sa OPERATOR [operator MyFunctionType1*(void) const].
		Object(10.1,20,30);
	}

	PrintLineSeparator();

	{
		CFunctionObjectAndSurrogate								Object;

		// !!! Zavola sa OPERATOR [operator MyFunctionType2&(void) const].
		Object(10.1,20,L"Timmy Anderson");
	}

	/*
	PrintLineSeparator();

	{
		CFunctionObjectAndSurrogate								Object;

		// !!! COMPILER hodi ERROR. Nevie sa rozhodnut medzi nasledujucimi OPERATORS.
		// !!! 1. Volanim OPERATOR [void operator()(double Value1, double Value2) const].
		// !!! 2. Volanim OPERATOR [operator MyFunctionType3*(void) const], kde TYPE 'MyFunctionType3' je FUNCTION s PROTOTYPE [void(double Value1, int Value2)].
		// !!!!! C++ vyhladava METHOD na zaklade ARGUMENTS [Object,10.1,20]. Kandidatmi je FUNCTION [void operator()(const CFunctionObjectAndSurrogate&, double, double) const] a SURROGATE FUNCTION s PARAMETERS [MyFunctionType3*,double,int]. SURROGATE FUNCTION potrebuje pre IMPLICIT PARAMETER TYPE [MyFunctionType3*] pouzitie OVERLOAD RESOLUTION RULE 'MATCH WITH USER DEFINED CONVERSIONS' co je horsi OVERLOAD RESOLUTION RULE aky je potrebny pre vsetky PARAMETERS OPERATOR [void operator()(double Value1, double Value2) const]. Avsak pre POSLEDNY PARAMETER SURROGATE FUNCTION je TYPE [int] PERFECT MATCH. Kedze v C++ plati, ze ZIADNA FUNCTION z VIABLE FUNCTION CANDIDATES SET nesmie mat pre ZIADNY PARAMETER LEPSI MATCH ako prisluny PARAMETER vo vybranej FUNCTION, dojde k FUNCTION CALL AMBIGUITY.
		Object(10.1,20);
	}
	*/

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void FunctionOverloadResolutionInDifferentContexts(int Value)
{
	wcout << L"FUNCTION [void FunctionOverloadResolutionInDifferentContexts(int Value)] CALLED with VALUE [" << Value << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void FunctionOverloadResolutionInDifferentContexts(double Value)
{
	wcout << L"FUNCTION [void FunctionOverloadResolutionInDifferentContexts(double Value)] CALLED with VALUE [" << Value << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestOverloadResolutionInDifferentContexts(void)
{
	PrintLineSeparator();

	{
		// !!! Vykonava sa OVERLOAD RESOLUTION. Do POINTER na FUNCTION sa priradi FUNCTION s PARAMETER TYPE [int].
		void													(*PointerToFunction)(int)=FunctionOverloadResolutionInDifferentContexts;

		(*PointerToFunction)(100);
	}

	PrintLineSeparator();

	{
		// !!! Vykonava sa OVERLOAD RESOLUTION. Do REFERENCE na FUNCTION sa priradi FUNCTION s PARAMETER TYPE [double].
		void													(&ReferenceToFunction)(double)=FunctionOverloadResolutionInDifferentContexts;

		ReferenceToFunction(111.222);
	}

	PrintLineSeparator();

	{
		// !!! Zavola sa CONSTRUCTOR s PARAMETER TYPE [long].
		COverloadResolutionInDifferentContexts					Object(100L);

		wcout << L"VALUE [" << Object.GetValue1() << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		// !!! Zavola sa CONSTRUCTOR s PARAMETER TYPE [double].
		COverloadResolutionInDifferentContexts					Object(100.123);

		wcout << L"VALUE [" << Object.GetValue2() << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		// !!! Zavola sa CONSTRUCTOR s PARAMETER TYPE [const wstring&].
		COverloadResolutionInDifferentContexts					Object(L"Timmy Anderson");

		wcout << L"VALUE [" << Object.GetValue3() << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		COverloadResolutionInDifferentContexts					Object(100L);

		// !!! Zavola sa OPERATOR [OPERATOR long].
		long													Value=Object;

		wcout << L"VALUE [" << Value << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		COverloadResolutionInDifferentContexts					Object(100.123);

		// !!! Zavola sa OPERATOR [OPERATOR double].
		double													Value=Object;

		wcout << L"VALUE [" << Value << L"] !" << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestOverloadResolution();
	//TestOverloadResolutionAfterTemplateArgumentsDeduction();
	//TestTemplateArgumentsDeduction();
	//TestOverloadResolutionForThisParameter();
	//TestLValueRValueThisMethods();
	//TestPerfectMatch();
	//TestOverloadResolutionTemplates();
	//TestConversionSequence();
	//TestPointerConversions();
	//TestPointerToMemberConversions();
	//TestInitializerListConversions();
	//TestInitializerListConstructors();
	//TestFunctionObjectAndSurrogate();
	TestOverloadResolutionInDifferentContexts();

	ShowExitLine();

	return(0);
}
//----------------------------------------------------------------------------------------------------------------------