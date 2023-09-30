//----------------------------------------------------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <concepts>
#include "MyDebug.h"
#include "CValueWithMoveSemantics.h"
#include "CPerfectForwardingInConstructorNoTemplate.h"
#include "CPerfectForwardingInConstructorTemplate.h"
#include "CPerfectForwardingInConstructorTemplateEnableIf.h"
#include "CTemplateTemplateSpecialMethods1.h"
#include "CTemplateTemplateSpecialMethods2.h"
#include "CTemplateTemplateSpecialMethods3.h"
#include "CPerfectForwardingInConstructorTemplateConcept.h"
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
void PrintObject(wstring Name, const CValueWithMoveSemantics& Object)
{
	if (Object.GetBuffer()!=nullptr)
	{
		wcout << Name << L" [" << Object.GetBuffer() << L"] !" << endl;
	}
	else
	{
		wcout << Name << L" [NULL] !" << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestValueWithMoveSemantics(void)
{
	PrintLineSeparator();

	{
		CValueWithMoveSemantics									Object(nullptr);

		PrintObject(L"OBJECT",Object);
	}

	PrintLineSeparator();

	{
		CValueWithMoveSemantics									Object(L"Timmy");

		PrintObject(L"OBJECT",Object);
	}

	PrintLineSeparator();

	// !!! Pouzitie COPY CONSTRUCTOR.
	{
		CValueWithMoveSemantics									Object1(L"Timmy");
		CValueWithMoveSemantics									Object2(Object1);

		PrintObject(L"OBJECT 1",Object1);
		PrintObject(L"OBJECT 2",Object2);
	}

	PrintLineSeparator();

	// !!! Pouzitie COPY CONSTRUCTOR.
	{
		CValueWithMoveSemantics									Object1(nullptr);
		CValueWithMoveSemantics									Object2(Object1);

		PrintObject(L"OBJECT 1",Object1);
		PrintObject(L"OBJECT 2",Object2);
	}

	PrintLineSeparator();

	// !!! Pouzitie OPERATOR [COPY OPERATOR=].
	{
		CValueWithMoveSemantics									Object1(L"Timmy");
		CValueWithMoveSemantics									Object2(nullptr);

		PrintObject(L"OBJECT 1",Object1);
		PrintObject(L"OBJECT 2",Object2);

		Object2=Object1;

		PrintObject(L"OBJECT 1",Object1);
		PrintObject(L"OBJECT 2",Object2);
	}

	PrintLineSeparator();

	// !!! Pouzitie OPERATOR [COPY OPERATOR=].
	{
		CValueWithMoveSemantics									Object1(nullptr);
		CValueWithMoveSemantics									Object2(L"Timmy");

		PrintObject(L"OBJECT 1",Object1);
		PrintObject(L"OBJECT 2",Object2);

		Object2=Object1;

		PrintObject(L"OBJECT 1",Object1);
		PrintObject(L"OBJECT 2",Object2);
	}

	PrintLineSeparator();

	// !!! Pouzitie OPERATOR [COPY OPERATOR=].
	{
		CValueWithMoveSemantics									Object1(nullptr);
		CValueWithMoveSemantics									Object2(nullptr);

		PrintObject(L"OBJECT 1",Object1);
		PrintObject(L"OBJECT 2",Object2);

		Object2=Object1;

		PrintObject(L"OBJECT 1",Object1);
		PrintObject(L"OBJECT 2",Object2);
	}

	PrintLineSeparator();

	// !!! Pouzitie MOVE CONSTRUCTOR.
	{
		CValueWithMoveSemantics									Object1(L"Timmy");
		CValueWithMoveSemantics									Object2(move(Object1));

		PrintObject(L"OBJECT 1",Object1);
		PrintObject(L"OBJECT 2",Object2);
	}

	PrintLineSeparator();

	// !!! Pouzitie MOVE CONSTRUCTOR.
	{
		CValueWithMoveSemantics									Object1(nullptr);
		CValueWithMoveSemantics									Object2(move(Object1));

		PrintObject(L"OBJECT 1",Object1);
		PrintObject(L"OBJECT 2",Object2);
	}

	PrintLineSeparator();

	// !!! Pouzitie OPERATOR [MOVE OPERATOR=].
	{
		CValueWithMoveSemantics									Object1(L"Timmy");
		CValueWithMoveSemantics									Object2(nullptr);

		PrintObject(L"OBJECT 1",Object1);
		PrintObject(L"OBJECT 2",Object2);

		Object2=move(Object1);

		PrintObject(L"OBJECT 1",Object1);
		PrintObject(L"OBJECT 2",Object2);
	}

	PrintLineSeparator();

	// !!! Pouzitie OPERATOR [COPY OPERATOR=].
	{
		CValueWithMoveSemantics									Object1(nullptr);
		CValueWithMoveSemantics									Object2(L"Timmy");

		PrintObject(L"OBJECT 1",Object1);
		PrintObject(L"OBJECT 2",Object2);

		Object2=move(Object1);

		PrintObject(L"OBJECT 1",Object1);
		PrintObject(L"OBJECT 2",Object2);
	}

	PrintLineSeparator();

	// !!! Pouzitie OPERATOR [COPY OPERATOR=].
	{
		CValueWithMoveSemantics									Object1(nullptr);
		CValueWithMoveSemantics									Object2(nullptr);

		PrintObject(L"OBJECT 1",Object1);
		PrintObject(L"OBJECT 2",Object2);

		Object2=move(Object1);

		PrintObject(L"OBJECT 1",Object1);
		PrintObject(L"OBJECT 2",Object2);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! FUNCTION, ktora vykonava cinnost FUNCTION [move()].
template <class TType>
constexpr remove_reference_t<TType>&& MyMove(TType&& Parameter) noexcept
{
	wcout << L"FUNCTION [constexpr remove_reference_t<TType>&& MyMove(TType&& Parameter) noexcept] CALLED !" << endl;

    return(static_cast<remove_reference_t<TType>&&>(Parameter));
}
//----------------------------------------------------------------------------------------------------------------------
void RValueNotPassedFunction(CValueWithMoveSemantics&& Object)
{
	PrintObject(L"PARAMETER OBJECT in FUNCTION 1",Object);
	
	// !!! Pouzije sa MOVE CONSTRUCTOR na inicializaciu LOCAL VARIABLE.
	CValueWithMoveSemantics										LocalObject=move(Object);

	PrintObject(L"LOCAL OBJECT in FUNCTION 2",LocalObject);
	PrintObject(L"PARAMETER OBJECT in FUNCTION 2",Object);
}
//----------------------------------------------------------------------------------------------------------------------
void RValueNotPassedForwarder(CValueWithMoveSemantics&& Object)
{
	// !!!!! Aj ked VARIABLE 'Object' ma TYPE RVALUE REFERENCE, bez pouzitia FUNCTION [move()] za do CALLED FUNCTION zasiela ako LVALUE REFERENCE.
	PrintObject(L"OBJECT in FORWARDER 1",Object);

	// !!!!! COMPILER hodi ERROR, pretoze aj ked VARIABLE 'Object' ma TYPE RVALUE REFERENCE pri volanie inej FUNCTION je prenasana ako LVALUE REFERENCE, a NIE ako RVALUE REFERENCE. A preto COMPILER hodi ERROR.
	//RValueNotPassedFunction(Object);

	// !!!!! CODE zbehne OK, pretoze ak sa pouzije FUNCTION [move()], tak VARIABLE je do FUNCTION prenesena ako RVALUE REFERENCE.
	RValueNotPassedFunction(move(Object));

	PrintObject(L"OBJECT in FORWARDER 2",Object);
}
//----------------------------------------------------------------------------------------------------------------------
void RValueNotPassedForwarderMyMove(CValueWithMoveSemantics&& Object)
{
	// !!!!! Aj ked VARIABLE 'Object' ma TYPE RVALUE REFERENCE, bez pouzitia FUNCTION [move()] za do CALLED FUNCTION zasiela ako LVALUE REFERENCE.
	PrintObject(L"OBJECT in FORWARDER 1",Object);

	// !!!!! CODE zbehne OK, pretoze ak sa pouzije FUNCTION [move()], tak VARIABLE je do FUNCTION prenesena ako RVALUE REFERENCE.
	RValueNotPassedFunction(MyMove(Object));

	PrintObject(L"OBJECT in FORWARDER 2",Object);
}
//----------------------------------------------------------------------------------------------------------------------
void TestRValueNotPassed(void)
{
	PrintLineSeparator();

	{
		CValueWithMoveSemantics									Object(L"Timmy");

		RValueNotPassedForwarder(move(Object));
	}

	PrintLineSeparator();

	{
		CValueWithMoveSemantics									Object(L"Timmy");

		RValueNotPassedForwarderMyMove(move(Object));
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void PerfectForwardingNoTemplatesFunction(CValueWithMoveSemantics& Object)
{
	PrintObject(L"FUNCTION - LVALUE REFERENCE",Object);
}
//----------------------------------------------------------------------------------------------------------------------
void PerfectForwardingNoTemplatesFunction(const CValueWithMoveSemantics& Object)
{
	PrintObject(L"FUNCTION - LVALUE CONST REFERENCE",Object);
}
//----------------------------------------------------------------------------------------------------------------------
void PerfectForwardingNoTemplatesFunction(CValueWithMoveSemantics&& Object)
{
	PrintObject(L"FUNCTION - RVALUE MOVABLE REFERENCE",Object);
}
//----------------------------------------------------------------------------------------------------------------------
void PerfectForwardingNoTemplatesForwarder(CValueWithMoveSemantics& Object)
{
	PrintObject(L"FORWARDER - LVALUE REFERENCE",Object);

	PerfectForwardingNoTemplatesFunction(Object);
}
//----------------------------------------------------------------------------------------------------------------------
void PerfectForwardingNoTemplatesForwarder(const CValueWithMoveSemantics& Object)
{
	PrintObject(L"FORWARDER - LVALUE CONST REFERENCE",Object);

	PerfectForwardingNoTemplatesFunction(Object);
}
//----------------------------------------------------------------------------------------------------------------------
void PerfectForwardingNoTemplatesForwarder(CValueWithMoveSemantics&& Object)
{
	PrintObject(L"FORWARDER - RVALUE MOVABLE REFERENCE",Object);

	// !!! Kedze pri volani FUNCTION je RVALUE REFERENCE zasielana ako LVALUE REFERENCE, je NUTNE volat FUNCTION [move()], ktora vracia RVALUE REFERENCE.
	PerfectForwardingNoTemplatesFunction(move(Object));
}
//----------------------------------------------------------------------------------------------------------------------
void TestPerfectForwardingNoTemplates(void)
{
	PrintLineSeparator();

	{
		CValueWithMoveSemantics									Object(L"OBJECT");

		// !!! Vola sa FUNCTION s PARAMETER TYPE [CValueWithMoveSemantics&].
		PerfectForwardingNoTemplatesForwarder(Object);
	}

	PrintLineSeparator();

	{
		const CValueWithMoveSemantics							ConstObject(L"CONSTANT OBJECT");

		// !!! Vola sa FUNCTION s PARAMETER TYPE [const CValueWithMoveSemantics&].
		PerfectForwardingNoTemplatesForwarder(ConstObject);
	}

	PrintLineSeparator();

	{
		// !!! Vola sa FUNCTION s PARAMETER TYPE [CValueWithMoveSemantics&&], pretoze sa jedna o TEMPORARY VARIABLE, ktora je RVALUE REFERENCE.
		PerfectForwardingNoTemplatesForwarder(CValueWithMoveSemantics(L"LOCAL OBJECT"));
	}

	PrintLineSeparator();

	{
		CValueWithMoveSemantics									Object(L"OBJECT");

		// !!! Vola sa FUNCTION s PARAMETER TYPE [CValueWithMoveSemantics&&], pretoze na LVALUE REFERENCE VARIABLE sa aplikovala FUNCTION [move()], ktora z nej spravila RVALUE REFERENCE.
		PerfectForwardingNoTemplatesForwarder(move(Object));
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void PerfectForwardingTemplatesFunction(CValueWithMoveSemantics& Object)
{
	PrintObject(L"FUNCTION - LVALUE REFERENCE",Object);
}
//----------------------------------------------------------------------------------------------------------------------
void PerfectForwardingTemplatesFunction(const CValueWithMoveSemantics& Object)
{
	PrintObject(L"FUNCTION - LVALUE CONST REFERENCE",Object);
}
//----------------------------------------------------------------------------------------------------------------------
void PerfectForwardingTemplatesFunction(CValueWithMoveSemantics&& Object)
{
	PrintObject(L"FUNCTION - RVALUE MOVABLE REFERENCE",Object);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void PerfectForwardingTemplatesForwarder(TType&& Object)
{
	PrintObject(L"FORWARDER",Object);

	// !!!!! Volanim FUNCTION [forward()] sa vykonava PERFECT FORWARDING pre TYPE [TType&], TYPE [const TType&] a TYPE [TType&&].
	PerfectForwardingTemplatesFunction(forward<TType>(Object));
}
//----------------------------------------------------------------------------------------------------------------------
void TestPerfectForwardingTemplates(void)
{
	PrintLineSeparator();

	{
		CValueWithMoveSemantics									Object(L"OBJECT");

		// !!! Vola sa FUNCTION s PARAMETER TYPE [CValueWithMoveSemantics&].
		PerfectForwardingTemplatesForwarder(Object);
	}

	PrintLineSeparator();

	{
		const CValueWithMoveSemantics							ConstObject(L"CONSTANT OBJECT");

		// !!! Vola sa FUNCTION s PARAMETER TYPE [const CValueWithMoveSemantics&].
		PerfectForwardingTemplatesForwarder(ConstObject);
	}

	PrintLineSeparator();

	{
		// !!! Vola sa FUNCTION s PARAMETER TYPE [CValueWithMoveSemantics&&], pretoze sa jedna o TEMPORARY VARIABLE, ktora je RVALUE REFERENCE.
		PerfectForwardingTemplatesForwarder(CValueWithMoveSemantics(L"LOCAL OBJECT"));
	}
	
	PrintLineSeparator();

	{
		CValueWithMoveSemantics									Object(L"OBJECT");

		// !!! Vola sa FUNCTION s PARAMETER TYPE [CValueWithMoveSemantics&&], pretoze na LVALUE REFERENCE VARIABLE sa aplikovala FUNCTION [move()], ktora z nej spravila RVALUE REFERENCE.
		PerfectForwardingTemplatesForwarder(move(Object));
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void TemplateParameterPerfectForwardForwarder(TType&& Object)
{
	SHOW_VALUE_CATEGORY(forward<TType>(Object));

	// !!!!! Pre TYPE [TYPE&] a TYPE [const TYPE&] sa NEVOLA ZIADEN CONSTRUCTOR, iba sa vykonava kopia REFERENCE.
	// !!!!! Pre TYPE [TYPE&&] sa vola MOVE CONSTRUCTOR.
	TType														LocalObject=forward<TType>(Object);

	PrintObject(L"FORWARDER - OBJECT",Object);
	PrintObject(L"FORWARDER - LOCAL OBJECT",LocalObject);
}
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateParameterPerfectForward(void)
{
	PrintLineSeparator();

	{
		CValueWithMoveSemantics									Object(L"OBJECT");

		TemplateParameterPerfectForwardForwarder(Object);
	}

	PrintLineSeparator();

	{
		const CValueWithMoveSemantics							ConstObject(L"CONSTANT OBJECT");

		TemplateParameterPerfectForwardForwarder(ConstObject);
	}

	PrintLineSeparator();

	{
		TemplateParameterPerfectForwardForwarder(CValueWithMoveSemantics(L"LOCAL OBJECT"));
	}
	
	PrintLineSeparator();

	{
		CValueWithMoveSemantics									Object(L"OBJECT");

		TemplateParameterPerfectForwardForwarder(move(Object));
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestPerfectForwardingInConstructorsNoTemplate(void)
{
	PrintLineSeparator();

	{
		wstring													Text=L"OBJECT";

		// !!! Vola sa COPY CONSTRUCTOR pre TYPE [wstring].
		CPerfectForwardingInConstructorNoTemplate				Object(Text);

		wcout << L"OBJECT [" << Object.GetValue() << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vola sa MOVE CONSTRUCTOR pre TYPE [wstring].
		CPerfectForwardingInConstructorNoTemplate				Object(L"LOCAL OBJECT");

		wcout << L"OBJECT [" << Object.GetValue() << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		CPerfectForwardingInConstructorNoTemplate				SourceObject(L"SOURCE OBJECT");

		// !!! Vola sa COPY CONSTRUCTOR pre TYPE [CPerfectForwardingInConstructorNoTemplate].
		CPerfectForwardingInConstructorNoTemplate				Object(SourceObject);

		wcout << L"OBJECT [" << Object.GetValue() << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		CPerfectForwardingInConstructorNoTemplate				SourceObject(L"SOURCE OBJECT");

		// !!! Vola sa MOVE CONSTRUCTOR pre TYPE [CPerfectForwardingInConstructorNoTemplate].
		CPerfectForwardingInConstructorNoTemplate				Object(move(SourceObject));

		wcout << L"OBJECT [" << Object.GetValue() << L"] !" << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestPerfectForwardingInConstructorsTemplate(void)
{
	PrintLineSeparator();

	{
		wstring													Text=L"OBJECT";

		// !!! Vola sa COPY CONSTRUCTOR pre TYPE [wstring].
		CPerfectForwardingInConstructorTemplate					Object(Text);

		wcout << L"OBJECT [" << Object.GetValue() << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vola sa MOVE CONSTRUCTOR pre TYPE [wstring].
		CPerfectForwardingInConstructorTemplate					Object(L"LOCAL OBJECT");

		wcout << L"OBJECT [" << Object.GetValue() << L"] !" << endl;
	}

	/*
	PrintLineSeparator();

	// !!!!! COMPILER hodi ERROR pretoze namiesto volania NON-TEMPLATE COPY CONSTRUCTOR sa vola TEMPLATE FORWARD CONSTRUCTOR, ktory sa pokusi spravit FORWARD TYPE [CPerfectForwardingInConstructorTemplate] do TYPE [wstring]. Dovodom preco sa vola TEMPLATE FORWARD CONSTRUCTOR namiesto logickejsieho NON-TEMPLATE COPY CONSTRUCTOR su C++ RULES, ktore preferuju TEMPLATE FORWARD CONSTRUCTOR.
	{
		CPerfectForwardingInConstructorTemplate					SourceObject(L"SOURCE OBJECT");

		CPerfectForwardingInConstructorTemplate					Object(SourceObject);

		wcout << L"OBJECT [" << Object.GetValue() << L"] !" << endl;
	}
	*/

	PrintLineSeparator();

	{
		CPerfectForwardingInConstructorTemplate					SourceObject(L"SOURCE OBJECT");

		// !!! Vola sa MOVE CONSTRUCTOR pre TYPE [CPerfectForwardingInConstructorTemplate&&].
		CPerfectForwardingInConstructorTemplate					Object(move(SourceObject));

		wcout << L"OBJECT [" << Object.GetValue() << L"] !" << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE FUNCTION bude zaradena do CANDIDATE SET FUNCTIONS, ktore je mozne volat, iba ak TEMPLATE PARAMETER 'TType' je kratsi, alebo rovny 4 BYTES.
template<typename TType>
enable_if<(sizeof(TType)<=4),TType>::type TemplateTypeTraitEnableIf1(TType Value)
{
	wcout << L"ENABLE IF 1 - VALUE [" << Value << L"] !" << endl;

	return(Value);
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE FUNCTION bude zaradena do CANDIDATE SET FUNCTIONS, ktore je mozne volat, iba ak TEMPLATE PARAMETER 'TType' je kratsi, alebo rovny 4 BYTES.
// !!!!! TEMPLATE FUNCTION pouziva FINTU, kde namiesto pouzitie TYPE TRAIT [enable_if] v samotnej TEMPLATE FUNCTION sa definuje 2. TEMPLATE PARAMETER s DEFAULT VALUE, kde sa pouzije TYPE TRAIT [enable_if]. Ak ma CONDITION v TYPE TRAIT [enable_if] VALUE [false], tak dojde k SFINAE a TEMPLATE FUNCTION NIE JE zaradena do CANDIDATE SET FUNCTIONS, ktore je mozne volat.
template<typename TType, typename=enable_if<(sizeof(TType)<=4),TType>::type>
TType TemplateTypeTraitEnableIf2(TType Value)
{
	wcout << L"ENABLE IF 2 - VALUE [" << Value << L"] !" << endl;

	return(Value);
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Definuje sa USING, ktory pouzije TYPE TRAIT [enable_if]. Je to FINTA ako sprehladnit implementaciu TEMPLATE FUNCTION, ktora pouziva TYPE TRAIT [enable_if].
template<typename TType>
using															EnableIfSizeofIsLessOrEqual4=enable_if<(sizeof(TType)<=4),TType>::type;
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE FUNCTION bude zaradena do CANDIDATE SET FUNCTIONS, ktore je mozne volat, iba ak TEMPLATE PARAMETER 'TType' je kratsi, alebo rovny 4 BYTES.
// !!!!! TEMPLATE FUNCTION pouziva FINTU, kde namiesto pouzitie TYPE TRAIT [enable_if] v samotnej TEMPLATE FUNCTION sa definuje 2. TEMPLATE PARAMETER s DEFAULT VALUE, kde sa pouzije TYPE TRAIT [enable_if]. Ak ma CONDITION v TYPE TRAIT [enable_if] VALUE [false], tak dojde k SFINAE a TEMPLATE FUNCTION NIE JE zaradena do CANDIDATE SET FUNCTIONS, ktore je mozne volat.
template<typename TType, typename=EnableIfSizeofIsLessOrEqual4<TType>>
TType TemplateTypeTraitEnableIf3(TType Value)
{
	wcout << L"ENABLE IF 3 - VALUE [" << Value << L"] !" << endl;

	return(Value);
}
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitEnableIf(void)
{
	PrintLineSeparator();

	{
		int														ValueInt=100;
		int														Result=TemplateTypeTraitEnableIf1(ValueInt);

		wcout << L"RESULT [" << Result << L"] !" << endl;
	}

	/*
	PrintLineSeparator();

	// !!!!! COMPILER hodi ERROR, pretoze TYPE [double] ma viac ako 4 BYTES a v TYPE TRAIT [enable_if<>] ma tak CONDITION FALSE VALUE.
	{
		double													ValueDouble=123.456;
		double													Result=TemplateTypeTraitEnableIf1(ValueDouble);

		wcout << L"RESULT [" << Result << L"] !" << endl;
	}
	*/

	PrintLineSeparator();

	{
		int														ValueInt=100;
		int														Result=TemplateTypeTraitEnableIf2(ValueInt);

		wcout << L"RESULT [" << Result << L"] !" << endl;
	}

	/*
	PrintLineSeparator();

	// !!!!! COMPILER hodi ERROR, pretoze TYPE [double] ma viac ako 4 BYTES a v TYPE TRAIT [enable_if<>] ma tak CONDITION FALSE VALUE.
	{
		double													ValueDouble=123.456;
		double													Result=TemplateTypeTraitEnableIf2(ValueDouble);

		wcout << L"RESULT [" << Result << L"] !" << endl;
	}
	*/

	PrintLineSeparator();

	{
		int														ValueInt=100;
		int														Result=TemplateTypeTraitEnableIf3(ValueInt);

		wcout << L"RESULT [" << Result << L"] !" << endl;
	}

	/*
	PrintLineSeparator();

	// !!!!! COMPILER hodi ERROR, pretoze TYPE [double] ma viac ako 4 BYTES a v TYPE TRAIT [enable_if<>] ma tak CONDITION FALSE VALUE.
	{
		double													ValueDouble=123.456;
		double													Result=TemplateTypeTraitEnableIf3(ValueDouble);

		wcout << L"RESULT [" << Result << L"] !" << endl;
	}
	*/

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestPerfectForwardingInConstructorsTemplateEnableIf(void)
{
	PrintLineSeparator();

	{
		wstring													Text=L"OBJECT";

		// !!! Vola sa COPY CONSTRUCTOR pre TYPE [wstring].
		CPerfectForwardingInConstructorTemplateEnableIf			Object(Text);

		wcout << L"OBJECT [" << Object.GetValue() << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vola sa MOVE CONSTRUCTOR pre TYPE [wstring].
		CPerfectForwardingInConstructorTemplateEnableIf			Object(L"LOCAL OBJECT");

		wcout << L"OBJECT [" << Object.GetValue() << L"] !" << endl;
	}

	PrintLineSeparator();

	// !!!!! CODE zbehne OK, pretoze konfliktny TEMPLATE CONSTRCUTOR je povoleny IBA pre ARGUMENTS, ktore su konvertovatelne na TYPE [wstring].
	{
		CPerfectForwardingInConstructorTemplateEnableIf			SourceObject(L"SOURCE OBJECT");

		// !!! Vola sa MOVE CONSTRUCTOR pre TYPE [const CPerfectForwardingInConstructorTemplateEnableIf&].
		CPerfectForwardingInConstructorTemplateEnableIf			Object(SourceObject);

		wcout << L"OBJECT [" << Object.GetValue() << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		CPerfectForwardingInConstructorTemplateEnableIf			SourceObject(L"SOURCE OBJECT");

		// !!! Vola sa MOVE CONSTRUCTOR pre TYPE [CPerfectForwardingInConstructorTemplateEnableIf&&].
		CPerfectForwardingInConstructorTemplateEnableIf			Object(move(SourceObject));

		wcout << L"OBJECT [" << Object.GetValue() << L"] !" << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateSpecialMethods(void)
{
	PrintLineSeparator();

	{
		CTemplateTemplateSpecialMethods1						Object(L"Timmy");

		// !!!!! NEVOLA sa TEMPLATE COPY CONSTRUCTOR, pretoze TEMPLATE COPY/MOVE CONSTRUCTORS a TEMPLATE OPERATOR [COPY/MOVE OPERATOR=] su C++ IGNOROVANE, a namiesto nich su volane DEFAULT COPY/MOVE CONSTRUCTORS a DEFAULT OPERATOR [COPY/MOVE OPERATOR=], ktore generuje COMPILER.
		CTemplateTemplateSpecialMethods1						CopyObject(Object);

		wcout << L"OBJECT [" << Object.GetValue() << L"] !" << endl;
		wcout << L"COPY OBJECT [" << CopyObject.GetValue() << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		CTemplateTemplateSpecialMethods2						Object(L"Timmy");

		// !!!!! Vdaka pouzitiu DELETE COPY CONSTRUCTOR, ktory ma aplikovany aj KEYWORD [volatile] je mozne prinutit C++, aby volal pri COPY SEMANTICS TEMPLATE CONSTRUCTOR.
		CTemplateTemplateSpecialMethods2						CopyObject(Object);

		wcout << L"OBJECT [" << Object.GetValue() << L"] !" << endl;
		wcout << L"COPY OBJECT [" << CopyObject.GetValue() << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		CTemplateTemplateSpecialMethods3						Object(wstring(L"Timmy"));

		// !!!!! Vdaka pouzitiu DELETE COPY CONSTRUCTOR, ktory ma aplikovany aj KEYWORD [volatile] je mozne prinutit C++, aby volal pri COPY SEMANTICS TEMPLATE CONSTRUCTOR.
		CTemplateTemplateSpecialMethods3						CopyObject(Object);

		wcout << L"OBJECT [" << Object.GetValue() << L"] !" << endl;
		wcout << L"COPY OBJECT [" << CopyObject.GetValue() << L"] !" << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestPerfectForwardingInConstructorsTemplateConcept(void)
{
	PrintLineSeparator();

	{
		wstring													Text=L"OBJECT";

		// !!! Vola sa COPY CONSTRUCTOR pre TYPE [wstring].
		CPerfectForwardingInConstructorTemplateConcept			Object(Text);

		wcout << L"OBJECT [" << Object.GetValue() << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vola sa MOVE CONSTRUCTOR pre TYPE [wstring].
		CPerfectForwardingInConstructorTemplateConcept			Object(L"LOCAL OBJECT");

		wcout << L"OBJECT [" << Object.GetValue() << L"] !" << endl;
	}

	PrintLineSeparator();

	// !!!!! CODE zbehne OK, pretoze konfliktny TEMPLATE CONSTRCUTOR je povoleny IBA pre ARGUMENTS, ktore su konvertovatelne na TYPE [wstring].
	{
		CPerfectForwardingInConstructorTemplateConcept			SourceObject(L"SOURCE OBJECT");

		// !!! Vola sa MOVE CONSTRUCTOR pre TYPE [const CPerfectForwardingInConstructorTemplateConcept&].
		CPerfectForwardingInConstructorTemplateConcept			Object(SourceObject);

		wcout << L"OBJECT [" << Object.GetValue() << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		CPerfectForwardingInConstructorTemplateConcept			SourceObject(L"SOURCE OBJECT");

		// !!! Vola sa MOVE CONSTRUCTOR pre TYPE [CPerfectForwardingInConstructorTemplateConcept&&].
		CPerfectForwardingInConstructorTemplateConcept			Object(move(SourceObject));

		wcout << L"OBJECT [" << Object.GetValue() << L"] !" << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestValueWithMoveSemantics();
	//TestRValueNotPassed();
	//TestPerfectForwardingNoTemplates();
	//TestPerfectForwardingTemplates();
	//TestTemplateParameterPerfectForward();
	//TestPerfectForwardingInConstructorsNoTemplate();
	//TestPerfectForwardingInConstructorsTemplate();
	//TestTypeTraitEnableIf();
	//TestPerfectForwardingInConstructorsTemplateEnableIf();
	TestTemplateSpecialMethods();
	//TestPerfectForwardingInConstructorsTemplateConcept();

	ShowExitLine();

	return(0);
}
//----------------------------------------------------------------------------------------------------------------------