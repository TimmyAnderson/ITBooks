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
#include "CTemplatesOnNamespaceScope.h"
#include "CTemplatesOnClassScopeInClass.h"
#include "CTemplatesOnClassScopeOutOfClass.h"
#include "UTemplateUnion.h"
#include "CNoDefaultConstructor.h"
#include "CNonTemplateMembers.h"
#include "CVirtualTemplateMembers.h"
#include "CPrimaryVsNonPrimaryTemplates.h"
#include "CTemplateLinkage.h"
#include "CTemplateLinkage1.h"
#include "CTemplateLinkage2.h"
#include "EEnum.h"
#include "CValue.h"
#include "CNonTypeTemplateClassAuto.h"
#include "CTemplateClass1.h"
#include "CTemplateClass2.h"
#include "CTemplateClassTwoParameters1.h"
#include "CTemplateClassTwoParameters2.h"
#include "CTemplateClassTwoParameters3.h"
#include "CTemplateClassPackTemplateTypeParameters.h"
#include "CTemplateClassPackTemplateNonTypeParameters.h"
#include "CTemplateClassPackTemplateTemplateParameters.h"
#include "CString.h"
#include "CVariadicTemplate.h"
#include "CVariadicTemplate1.h"
#include "CVariadicTemplate2.h"
#include "CMultipleTemplateParameterPacksSpecialization.h"
#include "CTemplateClassDefaultArguments1.h"
#include "CTemplateClassDefaultArguments2.h"
#include "CTemplateClassDefaultArgumentsSpecializations.h"
#include "CTemplateClassDefaultArgumentsOutOfClass.h"
#include "CTemplateClassDefaultArgumentsFriends.h"
#include "CTemplateParametersSubstitutions.h"
#include "CNonTypeTemplateParameters.h"
#include "CClassBase.h"
#include "CClassDerived.h"
#include "CTemplateTemplateParameters1.h"
#include "CTemplateTemplateParameters2.h"
#include "CTemplateTemplateParameters3.h"
#include "CTemplateTemplateArguments1.h"
#include "CTemplateTemplateArguments2.h"
#include "CTemplateTemplateArguments3.h"
#include "CTemplateMethodsNonEquivalence1.h"
#include "CTemplateMethodsNonEquivalence2.h"
#include "CTemplateMethodsNonEquivalence3.h"
#include "CTemplateArgumentEquivalence.h"
#include "CVariadicTemplateClass.h"
#include "CVariadicTemplateClassPackExpansion.h"
#include "CVariadicClassBase1.h"
#include "CVariadicClassBase2.h"
#include "CVariadicClassDerived.h"
#include "CVariadicClassOuter.h"
#include "CNestedParameterPacksExpansionInner1.h"
#include "CNestedParameterPacksExpansionInner2.h"
#include "CNestedParameterPacksExpansionOuter.h"
#include "SNode.h"
#include "CFriendClassClassMakingFriends1.h"
#include "CFriendClassClassMakingFriends2.h"
#include "CFriendClassFriendClassNonTemplate1.h"
#include "CFriendClassFriendClassNonTemplate2.h"
#include "CFriendClassFriendClassTemplate.h"
#include "CFriendFunctionsNonTemplateClass1.h"
#include "CFriendFunctionsNonTemplateClass2.h"
#include "CFriendFunctionsNonTemplateClass3.h"
#include "CFriendFunctionsTemplateClass.h"
#include "CFriendFunctionsTemplateClassMakingFriend.h"
#include "CFriendTemplatesClass1.h"
#include "CFriendTemplatesClass2.h"
#include "CFriendTemplatesClassMakingFriend.h"
#include "CFriendTemplatesTemplateClass.h"
//----------------------------------------------------------------------------------------------------------------------
#ifdef _MSC_VER
#pragma warning( disable : 6287 )
#pragma warning( disable : 4244 )
#pragma warning( disable : 26478 )
#pragma warning( disable : 26800 )
#undef min
#undef max
#endif
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTemplatesOnNamespaceScope(void)
{
	PrintLineSeparator();

	{
		CTemplateOnNamespaceScope<int>							Object(100);

		wcout << L"FIELD [" << Object.GetField() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		TemplateFunctionOnNamespaceScope(100);
	}

	PrintLineSeparator();

	{
		wcout << L"TEMPLATE VARIABLE 1 ON NAMESPACE SCOPE [" << TemplateVariableOnNamespaceScope1<int> << L"]." << endl;
		
		wcout << L"TEMPLATE VARIABLE 2 ON NAMESPACE SCOPE [" << TemplateVariableOnNamespaceScope2<int> << L"]." << endl;
	}

	PrintLineSeparator();

	{
		wcout << L"TEMPLATE TYPE ALIAS ON NAMESPACE SCOPE [" << GetTypeInfoName<TemplateTypeAliasOnNamespaceScope<int>>() << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTemplatesOnClassScopeInClass(void)
{
	PrintLineSeparator();

	{
		CTemplatesOnClassScopeInClassOuter<int>::CTemplatesOnClassScopeInClassInner<int>	ObjectInner(200);
		CTemplatesOnClassScopeInClassOuter<int>					ObjectOuter(100,ObjectInner);

		wcout << L"FIELD 1 [" << ObjectOuter.GetField1() << L"]." << endl;
		wcout << L"FIELD 2 [" << ObjectOuter.GetField2().GetField() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CTemplatesOnClassScopeInClassOuter<int>::CTemplatesOnClassScopeInClassInner<int>	ObjectInner(200);
		CTemplatesOnClassScopeInClassOuter<int>					ObjectOuter(100,ObjectInner);

		ObjectOuter.TemplateMetodOnClassScopeInClass(300,123.456);
	}

	PrintLineSeparator();

	{
		wcout << L"TEMPLATE STATIC FIELD ON CLASS SCOPE [" << CTemplatesOnClassScopeInClassOuter<int>::MTemplateStaticFieldOnClassScopeInClass<double> << L"]." << endl;

		CTemplatesOnClassScopeInClassOuter<int>::MTemplateStaticFieldOnClassScopeInClass<double> =123.456;

		wcout << L"TEMPLATE STATIC FIELD ON CLASS SCOPE [" << CTemplatesOnClassScopeInClassOuter<int>::MTemplateStaticFieldOnClassScopeInClass<double> << L"]." << endl;
	}

	PrintLineSeparator();

	{
		wcout << L"TEMPLATE TYPE ALIAS ON CLASS SCOPE [" << GetTypeInfoName<CTemplatesOnClassScopeInClassOuter<int>::TemplateTypeAliasOnClassScopeInClass<double>>() << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTemplatesOnClassScopeOutOfClass(void)
{
	PrintLineSeparator();

	{
		CTemplatesOnClassScopeOutOfClassOuter<int>::CTemplatesOnClassScopeOutOfClassInner<int>	ObjectInner(200);
		CTemplatesOnClassScopeOutOfClassOuter<int>				ObjectOuter(100,ObjectInner);

		wcout << L"FIELD 1 [" << ObjectOuter.GetField1() << L"]." << endl;
		wcout << L"FIELD 2 [" << ObjectOuter.GetField2().GetField() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CTemplatesOnClassScopeOutOfClassOuter<int>::CTemplatesOnClassScopeOutOfClassInner<int>	ObjectInner(200);
		CTemplatesOnClassScopeOutOfClassOuter<int>				ObjectOuter(100,ObjectInner);

		ObjectOuter.TemplateMetodOnClassScopeOutOfClass(300,123.456);
	}

	PrintLineSeparator();

	{
		wcout << L"TEMPLATE STATIC FIELD ON CLASS SCOPE OUT OF CLASS [" << CTemplatesOnClassScopeOutOfClassOuter<int>::MTemplateStaticFieldOnClassScopeOutOfClass<double> << L"]." << endl;

		CTemplatesOnClassScopeOutOfClassOuter<int>::MTemplateStaticFieldOnClassScopeOutOfClass<double> =123.456;

		wcout << L"TEMPLATE STATIC FIELD ON CLASS SCOPE OUT OF CLASS [" << CTemplatesOnClassScopeOutOfClassOuter<int>::MTemplateStaticFieldOnClassScopeOutOfClass<double> << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateUnion(void)
{
	PrintLineSeparator();

	{
		UTemplateUnion<int,double>								Union(100);

		wcout << "UNION FIELD 1 [" << Union.GetField1() << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		UTemplateUnion<int,double>								Union(123.456);

		wcout << "UNION FIELD 2 [" << Union.GetField2() << L"] !" << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void TemplateTemplateDefaultParameters1(TType Value=100)
{
	wcout << "FUNCTION 1 - VALUE [" << Value << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void TemplateTemplateDefaultParameters2(TType Value=TType())
{
	wcout << "FUNCTION 2 - VALUE [" << Value << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void TemplateTemplateDefaultParameters3(TType Value=TType{})
{
	wcout << "FUNCTION 3 - VALUE [" << Value << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateDefaultParameters(void)
{
	PrintLineSeparator();

	{
		TemplateTemplateDefaultParameters1<int>();

		TemplateTemplateDefaultParameters1(999);
	}

	PrintLineSeparator();

	{
		TemplateTemplateDefaultParameters2<int>();

		TemplateTemplateDefaultParameters2(999);
	}

	PrintLineSeparator();

	{
		TemplateTemplateDefaultParameters3<int>();

		TemplateTemplateDefaultParameters3(999);
	}

	PrintLineSeparator();


	{
		// !!!!! COMPILER hodi ERROR, pretoze TYPE [CNoDefaultConstructor] NEMA DEFUALT CONSTRUCTOR.
		//TemplateTemplateDefaultParameters3<CNoDefaultConstructor>();

		TemplateTemplateDefaultParameters3(CNoDefaultConstructor(333));
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestNonTemplateMembers(void)
{
	PrintLineSeparator();

	{
		CNonTemplateMembersClassOuter<int>::CNonTemplateMembersClassInner	ObjectInner(200);
		CNonTemplateMembersClassOuter<int>						ObjectOuter(100,ObjectInner);

		wcout << L"FIELD 1 [" << ObjectOuter.GetField1() << L"]." << endl;
		wcout << L"FIELD 2 [" << ObjectOuter.GetField2().GetField() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		wcout << L"NON-TEMPLATE STATIC FIELD ON CLASS SCOPE OUT OF CLASS [" << CNonTemplateMembersClassOuter<int>::MNonTemplateStaticFieldOnClassScopeOutOfClass << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestVirtualTemplateMembers(void)
{
	PrintLineSeparator();

	{
		CVirtualTemplateMembers<double>							Object(123.456);

		wcout << L"FIELD [" << Object.GetField() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CVirtualTemplateMembers<double>							Object(123.456);

		wcout << L"FIELD [" << Object.GetField() << L"]." << endl;

		int														ConvertedValue=Object.ConvertToNonVirtual<int>();

		wcout << L"CONVERTED VALUE [" << ConvertedValue << L"]." << endl;
	}

	/*
	PrintLineSeparator();

	// !!! COMPILER hodi ERROR, pretoze TEMPLATE METHOD NESMIE byt VIRTUAL.
	{
		CVirtualTemplateMembers<double>							Object(123.456);

		wcout << L"FIELD [" << Object.GetField() << L"]." << endl;

		int														ConvertedValue=Object.ConvertToVirtual<int>();

		wcout << L"CONVERTED VALUE [" << ConvertedValue << L"]." << endl;
	}
	*/

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateLinkage(void)
{
	PrintLineSeparator();

	{
		wcout << L"SHARED NAME [" << TemplateLinkageSharedName << L"]." << endl;
		wcout << L"SHARED NAME CLASS [" << GetTypeInfoName<class TemplateLinkageSharedName>() << L"]." << endl;

		/*
		wcout << L"SHARED NAME ERROR [" << TemplateLinkageSharedNameError << L"]." << endl;
		wcout << L"SHARED NAME ERROR CLASS [" << GetTypeInfoName<class TemplateLinkageSharedNameError<int>>() << L"]." << endl;
		*/
	}

	PrintLineSeparator();

	{
		UseCPPLinkage(100);
	}

	/*
	PrintLineSeparator();

	// !!! Pre TEMPLATE FUNCTIONS je C LINKAGE ZAKAZANY a COMPILER hodi ERROR.
	{
		UseCLinkage(100);
	}
	*/

	PrintLineSeparator();

	{
		// !!! FUNCTION vola TEMPLATE FUNCTION [void TemplateLinkageExternalLinage(TType Value)] definovanu vo FILE [CTemplateLinkage1.cpp].
		TestExternalLinage1();

		// !!! FUNCTION vola TEMPLATE FUNCTION [void TemplateLinkageExternalLinage(TType Value)] definovanu vo FILE [CTemplateLinkage2.cpp].
		// !!!!! V skutocnosti vsak C++ zavola TEMPLATE FUNCTION definovanu vo FILE [CTemplateLinkage1.cpp], pretoze TEMPLATE FUNCTION [void TemplateLinkageExternalLinage(TType Value)] definovanu vo FILE [CTemplateLinkage2.cpp] povazuje za REDECLARATION a IGNORUJE JU. Nevygeneruje pre nu CODE.
		TestExternalLinage2();
	}

	PrintLineSeparator();

	{
		// !!! FUNCTION vola TEMPLATE FUNCTION [void TemplateLinkageInternalLinage(TType Value)] definovanu vo FILE [CTemplateLinkage1.cpp].
		TestInternalLinage1();

		// !!! FUNCTION vola TEMPLATE FUNCTION [void TemplateLinkageInternalLinage(TType Value)] definovanu vo FILE [CTemplateLinkage2.cpp].
		TestInternalLinage2();
	}

	PrintLineSeparator();

	{
		// !!! FUNCTION vola TEMPLATE FUNCTION [void TemplateLinkageNamespaceLinage(TType Value)] definovanu vo FILE [CTemplateLinkage1.cpp].
		TestNamespaceLinage1();

		// !!! FUNCTION vola TEMPLATE FUNCTION [void TemplateLinkageNamespaceLinage(TType Value)] definovanu vo FILE [CTemplateLinkage2.cpp].
		TestNamespaceLinage2();
	}

	PrintLineSeparator();

	{
		// !!! FUNCTION vola TEMPLATE FUNCTION [void TemplateLinkageAnonymousVariable1.TemplateLinkageNamespaceLinage(TType Value)] definovanu vo FILE [CTemplateLinkage1.cpp].
		TestNoLinage1();

		// !!! FUNCTION vola TEMPLATE FUNCTION [void TemplateLinkageAnonymousVariable2.TemplateLinkageNamespaceLinage(TType Value)] definovanu vo FILE [CTemplateLinkage2.cpp].
		TestNoLinage2();
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestPrimaryVsNonPrimaryTemplates(void)
{
	PrintLineSeparator();

	{
		// !!! Vytvara sa instancia PRIMARY TEMPLATE.
		CPrimaryVsNonPrimaryTemplates<int,long>					Object(true,100,200L);

		wcout << L"FIELD 1 [" << Object.GetField1() << L"] FIELD 2 [" << Object.GetField2() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vytvara sa instancia NON-PRIMARY TEMPLATE.
		CPrimaryVsNonPrimaryTemplates<int,double>				Object(true,100,123.456);

		wcout << L"FIELD 1 [" << Object.GetField1() << L"] FIELD 2 [" << Object.GetField2() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		wcout << L"PRIMARY TEMPLATE VARIABLE - FIELD 1 [" << PrimaryVsNonPrimaryTemplatesVariable<int,long>.GetField1() << L"] FIELD 2 [" << PrimaryVsNonPrimaryTemplatesVariable<int,long>.GetField2() << L"]." << endl;
		wcout << L"NON-PRIMARY TEMPLATE VARIABLE - FIELD 1 [" << PrimaryVsNonPrimaryTemplatesVariable<int,double>.GetField1() << L"] FIELD 2 [" << PrimaryVsNonPrimaryTemplatesVariable<int,double>.GetField2() << L"]." << endl;

		PrintLineSeparator();

		PrimaryVsNonPrimaryTemplatesVariable<int,long>.SetField1(100);
		PrimaryVsNonPrimaryTemplatesVariable<int,long>.SetField2(200L);

		PrimaryVsNonPrimaryTemplatesVariable<int,double>.SetField1(300);
		PrimaryVsNonPrimaryTemplatesVariable<int,double>.SetField2(444.444);

		wcout << L"PRIMARY TEMPLATE VARIABLE - FIELD 1 [" << PrimaryVsNonPrimaryTemplatesVariable<int,long>.GetField1() << L"] FIELD 2 [" << PrimaryVsNonPrimaryTemplatesVariable<int,long>.GetField2() << L"]." << endl;
		wcout << L"NON-PRIMARY TEMPLATE VARIABLE - FIELD 1 [" << PrimaryVsNonPrimaryTemplatesVariable<int,double>.GetField1() << L"] FIELD 2 [" << PrimaryVsNonPrimaryTemplatesVariable<int,double>.GetField2() << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! TEMPLATE FUNCTION ma 3 TEMPLATE PARAMETERS.
// !!! TEMPLATE PARAMETER NAME 'TType' moze byt pouzity az po svojej definicii v KEYWORD [template<>].
// !!! NON-TYPE TEMPLATE PARAMETER ma definovanu DEFAULT VALUE.
// !!! Posledny TYPE TEMPLATE PARAMETER NEMA NAME, ale ma definovanu DEFAULT VALUE.
template<typename TType, TType VALUE=999, typename=int>
void TemplateTemplateParameters(TType Parameter)
{
	wcout << L"TEMPLATE - PARAMETER [" << Parameter << L"]." << endl;
	wcout << L"TEMPLATE - VALUE [" << VALUE << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateParameters(void)
{
	PrintLineSeparator();

	{
		TemplateTemplateParameters(100);
	}

	PrintLineSeparator();

	{
		TemplateTemplateParameters<int,200>(100);
	}

	PrintLineSeparator();

	{
		TemplateTemplateParameters<int,200,char>(100);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void TemplateTemplateTypeParameters(TType Parameter)
{
	wcout << L"TEMPLATE - PARAMETER [" << Parameter << L"]." << endl;

	TType														LocalValue=Parameter;

	wcout << L"TEMPLATE - LOCAL VALUE [" << LocalValue << L"]." << endl;

	/*
	// !!!!! ELABORATED TYPE SPECIFIER [class] NESMIE byt aplikovany na TEMPLATE TYPE PARAMETERS.
	class TType													LocalValueError=Parameter;

	wcout << L"TEMPLATE - LOCAL VALUE ERROR [" << LocalValueError << L"]." << endl;
	*/
}
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateTypeParameters(void)
{
	PrintLineSeparator();

	{
		TemplateTemplateTypeParameters(100);
	}

	PrintLineSeparator();

	{
		TemplateTemplateTypeParameters(wstring(L"Timmy"));
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<int VALUE>
void TemplateNonTypeTemplateParametersTypesInt(void)
{
	wcout << L"INT - VALUE [" << VALUE << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<EEnum VALUE>
void TemplateNonTypeTemplateParametersTypesEnum(void)
{
	wcout << L"ENUM - VALUE [" << static_cast<int>(VALUE) << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<int* VALUE>
void TemplateNonTypeTemplateParametersTypesPointerToValue(void)
{
	wcout << L"POINTER TO VALUE - VALUE [" << *VALUE << L"] !" << endl;

	*VALUE=111;

	wcout << L"POINTER TO VALUE - VALUE [" << *VALUE << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<int& VALUE>
void TemplateNonTypeTemplateParametersTypesReferenceToValue(void)
{
	wcout << L"REFERENCE TO VALUE - VALUE [" << VALUE << L"] !" << endl;

	VALUE=111;

	wcout << L"REFERENCE TO VALUE - VALUE [" << VALUE << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<const wchar_t* VALUE>
void TemplateNonTypeTemplateParametersTypesPointerToWChar(void)
{
	wcout << L"POINTER TO WCHAR - VALUE [" << VALUE << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, int TType::*VALUE>
void TemplateNonTypeTemplateParametersTypesPointerToMemberField(TType Object)
{
	wcout << L"POINTER TO MEMBER FIELD - VALUE [" << Object.*VALUE << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, int (CValue::*VALUE)(void) const noexcept>
void TemplateNonTypeTemplateParametersTypesPointerToMemberMethod(TType Object)
{
	wcout << L"POINTER TO MEMBER METHOD - VALUE [" << (Object.*VALUE)() << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestNonTypeTemplateParametersTypes(void)
{
	PrintLineSeparator();

	{
		TemplateNonTypeTemplateParametersTypesInt<10>();
	}

	PrintLineSeparator();

	{
		TemplateNonTypeTemplateParametersTypesEnum<EEnum::E_VALUE>();
	}

	PrintLineSeparator();

	{
		// !!!!! VAIRABALE MUSI byt STATIC.
		static int												Value=100;

		wcout << L"STATIC VALUE [" << Value << L"] !" << endl;

		TemplateNonTypeTemplateParametersTypesPointerToValue<&Value>();

		wcout << L"STATIC VALUE [" << Value << L"] !" << endl;
	}

	/*
	PrintLineSeparator();

	{
		int												Value=100;

		wcout << L"STATIC VALUE [" << Value << L"] !" << endl;

		// !!!!! COMPILER hodi ERROR, pretoze VARIABLE 'Value' nie je STATIC.
		TemplateNonTypeTemplateParametersTypesPointerToValue<&Value>();

		wcout << L"STATIC VALUE [" << Value << L"] !" << endl;
	}
	*/

	PrintLineSeparator();

	{
		// !!!!! VAIRABALE MUSI byt STATIC.
		static int												Value=100;

		wcout << L"STATIC VALUE [" << Value << L"] !" << endl;

		TemplateNonTypeTemplateParametersTypesReferenceToValue<Value>();

		wcout << L"STATIC VALUE [" << Value << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		// !!!!! VAIRABALE MUSI byt STATIC.
		static const wchar_t									Value[]=L"Timmy";

		TemplateNonTypeTemplateParametersTypesPointerToWChar<Value>();
	}

	PrintLineSeparator();

	{
		CValue													Object(100);

		TemplateNonTypeTemplateParametersTypesPointerToMemberField<CValue,&CValue::MField>(Object);
	}

	PrintLineSeparator();

	{
		CValue													Object(100);

		TemplateNonTypeTemplateParametersTypesPointerToMemberMethod<CValue,&CValue::GetValue>(Object);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateClassNonTypeTemplateParametersAuto(void)
{
	PrintLineSeparator();

	CNonTypeTemplateClassAuto<int,5U>							Template;

	for(size_t Index=0;Index<Template.VALUES_SIZE;Index++)
	{
		int														Value=static_cast<int>((Index+1)*10);

		Template.SetValue(Index,Value);
	}

	for(size_t Index=0;Index<Template.VALUES_SIZE;Index++)
	{
		int														Value=Template.GetValue(Index);

		wcout << L"VALUES[" << Index << L"] [" << Value << L"] !" << endl;
	}

	wcout << L"TEMPLATE - TYPE [" << GetTypeInfoName<decltype(Template)>() << L"] !" << endl;
	wcout << L"TEMPLATE - TYPE.VALUES_SIZE [" << GetTypeInfoName<decltype(Template.VALUES_SIZE)>() << L"] !" << endl;

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! Pre definiciu NON-TYPE TEMPLATE PARAMETER je mozne pouzit aj KEYWORD [auto].
template<auto SIZE>
void TemplateFunctionNonTypeTemplateParametersAuto(void)
{
	using														SIZE_TYPE=decltype(SIZE);

	wcout << L"SIZE [" << SIZE << L"] !" << endl;

	wcout << L"SIZE TYPE [" << GetTypeInfoName<decltype(SIZE)>() << L"] !" << endl;
	wcout << L"SIZE_TYPE [" << GetTypeInfoName<SIZE_TYPE>() << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateFunctionNonTypeTemplateParametersAuto(void)
{
	PrintLineSeparator();

	TemplateFunctionNonTypeTemplateParametersAuto<10U>();

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! Pre definiciu NON-TYPE TEMPLATE PARAMETER je mozne pouzit aj KEYWORD [decltype(auto)].
template<decltype(auto) SIZE>
void TemplateFunctionNonTypeTemplateParametersDecltypeAuto(void)
{
	using														SIZE_TYPE=decltype(SIZE);

	wcout << L"SIZE [" << SIZE << L"] !" << endl;

	wcout << L"SIZE TYPE [" << GetTypeInfoName<decltype(SIZE)>() << L"] !" << endl;
	wcout << L"SIZE_TYPE [" << GetTypeInfoName<SIZE_TYPE>() << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateFunctionNonTypeTemplateParametersDecltypeAuto(void)
{
	PrintLineSeparator();

	{
		TemplateFunctionNonTypeTemplateParametersDecltypeAuto<10U>();
	}

	PrintLineSeparator();

	{
		static int												Variable=100;

		// !!!!!  TEMPLATE ARGUMENTS musia byt uzatvorene v ZATVORKACH [()].
		TemplateFunctionNonTypeTemplateParametersDecltypeAuto<(Variable)>();
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! REALNY TYPE NON-TYPE TEMPLATE PARAMETER je TYPE [int], a NIE TYPE [const int].
template<const int VALUE>
void TemplateTemplateFunctionNonTypeTemplateParametersTypeDecayConst(void)
{
	wcout << L"CONST INT VALUE [" << VALUE << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
/*
// !!!!! COMPILER hodi ERROR, pretoze C++ pre NON-TYPE TEMPLATE PARAMETERS IGNORUJE MODIFIER [const] a MODIFIER [volatile].
template<int VALUE>
void TemplateTemplateFunctionNonTypeTemplateParametersTypeDecayConst(void)
{
	wcout << L"INT VALUE [" << VALUE << L"] !" << endl;
}
*/
//----------------------------------------------------------------------------------------------------------------------
// !!!!! REALNY TYPE NON-TYPE TEMPLATE PARAMETER je TYPE [int*], a NIE TYPE [int[5]].
template<int VALUE[3]>
void TemplateTemplateFunctionNonTypeTemplateParametersTypeDecayArray(size_t Size)
{
	for(size_t Index=0;Index<Size;Index++)
	{
		int														Value=VALUE[Index];

		wcout << L"ARRAY - ARRAY [" << Index << L"] - VALUE [" << Value << L"] !" << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
/*
// !!!!! COMPILER hodi ERROR, pretoze C++ pre NON-TYPE TEMPLATE PARAMETERS TYPE ARRAYS sa robi DECAY na POINTER a takato TEMPLATE FUNCTION uz bola definovana.
template<int* VALUE>
void TemplateTemplateFunctionNonTypeTemplateParametersTypeDecayArray(size_t Size)
{
	for(size_t Index=0;Index<Size;Index++)
	{
		int														Value=VALUE[Index];

		wcout << L"POINTER - ARRAY [" << Index << L"] - VALUE [" << Value << L"] !" << endl;
	}
}
*/
//----------------------------------------------------------------------------------------------------------------------
// !!!!! REALNY TYPE NON-TYPE TEMPLATE PARAMETER je TYPE [int(*)(void)], a NIE TYPE [int(void)].
template<int FUNCTION(void)>
void TemplateTemplateFunctionNonTypeTemplateParametersTypeDecayFunctionPointer(void)
{
	wcout << L"FUNCTION TYPE [" << FUNCTION() << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
/*
// !!!!! COMPILER hodi ERROR, pretoze C++ pre NON-TYPE TEMPLATE PARAMETERS TYPE FUNCTION TYPES sa robi DECAY na POINTER na FUNCTION a takato TEMPLATE FUNCTION uz bola definovana.
template<int (*FUNCTION)(void)>
void TemplateTemplateFunctionNonTypeTemplateParametersTypeDecayFunctionPointer(void)
{
	wcout << L"POINTER TO FUNCTION TYPE [" << FUNCTION() << L"] !" << endl;
}
*/
//----------------------------------------------------------------------------------------------------------------------
int FunctionFunctionNonTypeTemplateParametersTypeDecay(void)
{
	return(300);
}
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateFunctionNonTypeTemplateParametersTypeDecay(void)
{
	PrintLineSeparator();

	{
		TemplateTemplateFunctionNonTypeTemplateParametersTypeDecayConst<100>();
	}

	PrintLineSeparator();

	{
		// !!!!! ARRAY MUSI byt STATIC.
		static int												Array[3]{10,20,30};

		TemplateTemplateFunctionNonTypeTemplateParametersTypeDecayArray<Array>(3);
	}

	PrintLineSeparator();

	{
		// !!!!! ARRAY MUSI byt STATIC.
		static int												Array[5]{10,20,30,40,50};

		// !!!!! Hoci NON-TYPE TEMPLATE PARAMETER ma deklarovany TYPE [int[3]], ten je DECAYED na TYPE [int*] a tym padom je mozne pouzit ako NON-TYPE TEMPLATE ARGUMENT aj TYPE [int[5]].
		TemplateTemplateFunctionNonTypeTemplateParametersTypeDecayArray<Array>(5);
	}

	PrintLineSeparator();

	{
		TemplateTemplateFunctionNonTypeTemplateParametersTypeDecayFunctionPointer<FunctionFunctionNonTypeTemplateParametersTypeDecay>();
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! TEMPLATE FUNCTION ma ako TEMPLATE PARAMETER TEMPLATE TEMPLATE PARAMETER.
template<template<typename,typename> typename TType>
void TemplateTemplateTemplateParameters1(TType<int,double> Object)
{
	wcout << L"TEMPLATE TEMPLATE PARAMETER 1 - TYPE [" << GetTypeInfoName<decltype(Object)>() << L"] - FIELD 1 [" << Object.GetValue1() << L"] - FIELD 2 [" << Object.GetValue2() << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
// !!! TEMPLATE FUNCTION ma ako TEMPLATE PARAMETER TEMPLATE TEMPLATE PARAMETER.
template<typename TType1, typename TType2, template<typename,typename> typename TType>
void TemplateTemplateTemplateParameters2(TType<TType1,TType2> Object)
{
	wcout << L"TEMPLATE TEMPLATE PARAMETER 2 - TYPE [" << GetTypeInfoName<decltype(Object)>() << L"] - FIELD 1 [" << Object.GetValue1() << L"] - FIELD 2 [" << Object.GetValue2() << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
// !!! TEMPLATE FUNCTION ma ako TEMPLATE PARAMETER TEMPLATE TEMPLATE PARAMETER.
// !!! Aj TEMPLATE PARAMETERS TEMPLATE TEMPLATE PARAMETER maju svoje NAMES.
// !!!!! TEMPLATE TEMPLATE PARAMETER NAME 'TType' reprezentuje iba nazov samotnej TEMPLATE, ale NIE TEMPLATE aj s TEMPLATE PARAMETERS. TEMPLATE PARAMETERS je NUTNE EXPLICITNE DOPLNIT ako napriklad je to v CODE [TType<TType1,TType2,VALUE_1,VALUE_2>].
template<typename TType1, typename TType2, TType1 VALUE_1, TType2 VALUE_2, template<typename TLocalType1,typename TLocalType2,TLocalType1,TLocalType2> typename TType>
void TemplateTemplateTemplateParameters3(TType<TType1,TType2,VALUE_1,VALUE_2> Object)
{
	wcout << L"TEMPLATE TEMPLATE PARAMETER 3 - TYPE [" << GetTypeInfoName<decltype(Object)>() << L"] - FIELD 1 [" << Object.GetValue1() << L"] - FIELD 2 [" << Object.GetValue2() << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateTemplateParameters(void)
{
	PrintLineSeparator();

	{
		CTemplateClass1<int,double>								Object(100,123.456);

		TemplateTemplateTemplateParameters1(Object);
	}

	PrintLineSeparator();

	{
		CTemplateClass1<long,float>								Object(100L,123.456F);

		TemplateTemplateTemplateParameters2(Object);
	}

	PrintLineSeparator();

	{
		CTemplateClass2<int,long,100,200L>						Object(1000,2000L);

		TemplateTemplateTemplateParameters3(Object);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateParameterPackTypes(void)
{
	PrintLineSeparator();

	{
		CTemplateClassPackTemplateTypeParameters<int,double,CString>	Object(100,222.222,L"Timmy");

		Object.Print();
	}

	PrintLineSeparator();

	{
		CTemplateClassPackTemplateNonTypeParameters<100,200,300>	Object;

		Object.Print();
	}

	PrintLineSeparator();

	{
		CTemplateClassTwoParameters1<CString,int>				Object1(L"Timmy",12);
		CTemplateClassTwoParameters2<CString,int>				Object2(L"Jenny",13);
		CTemplateClassTwoParameters3<CString,int>				Object3(L"Josh",12);
		CTemplateClassPackTemplateTemplateParameters<CString,int,CTemplateClassTwoParameters1,CTemplateClassTwoParameters2,CTemplateClassTwoParameters3>	Object(Object1,Object2,Object3);

		Object.Print();
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! VARIADIC TEMPLATE VARIABLE.
template<typename... TTypes>
CVariadicTemplate<TTypes...>									TemplateVariadicTemplateTypesVariable;
//----------------------------------------------------------------------------------------------------------------------
// !!! VARIADIC TEMPLATE FUNCTION.
template<typename TType, typename... TTypes>
void InernalTemplateVariadicTemplateTypes(size_t Index, TType Value, TTypes... Values)
{
	std::wcout << L"TEMPLATE FUNCTION - PARAMETER [" << Index << L"] - TYPE [" << GetTypeInfoName<TType>() << L"] - VALUE [" << Value << L"]." << std::endl;

	if constexpr (sizeof...(TTypes)>0)
	{
		InernalTemplateVariadicTemplateTypes(Index+1,Values...);
	}
}
//----------------------------------------------------------------------------------------------------------------------
// !!! VARIADIC TEMPLATE FUNCTION.
template<typename... TTypes>
void TemplateVariadicTemplateTypes(TTypes... Values)
{
	InernalTemplateVariadicTemplateTypes(1,Values...);
}
//----------------------------------------------------------------------------------------------------------------------
void TestVariadicTemplateTypes(void)
{
	PrintLineSeparator();

	{
		// !!! VARIADIC TEMPLATE VARIABLE.
		TemplateVariadicTemplateTypesVariable<CString,int> =CVariadicTemplate<CString,int>(L"Timmy",12);

		TemplateVariadicTemplateTypesVariable<CString,int>.Print(L"TEMPLATE VARIABLE");
	}

	PrintLineSeparator();

	{
		// !!! VARIADIC TEMPLATE FUNCTION.
		TemplateVariadicTemplateTypes(100,123.456,CString(L"Timmy"));
	}

	PrintLineSeparator();

	{
		// !!! VARIADIC TEMPLATE CLASS.
		CVariadicTemplate<CString,int>							Object(L"Timmy",12);

		Object.Print(L"TEMPLATE CLASS");
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! TEMPLATE VARIABLE.
template<typename TType1, typename TType2>
CVariadicTemplate<TType1,TType2>								TemplateMultipleTemplateParameterPacksVariable;
//----------------------------------------------------------------------------------------------------------------------
// !!! TEMPLATE VARIABLE SPECIALIZATION, ktora ma viacero TEMPLATE PARAMETERS PACKS.
template<typename... TTypes1, typename... TTypes2>
CMultipleTemplateParameterPacksSpecialization<CVariadicTemplate1<TTypes1...>,CVariadicTemplate2<TTypes2...>>	TemplateMultipleTemplateParameterPacksVariable<CVariadicTemplate1<TTypes1...>,CVariadicTemplate2<TTypes2...>>;
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE FUNCTIONS MOZU mat za TEMPLATE PARAMETERS PACKS aj dalsie TEMPLATE PARAMETER, ak su tie identifikovatelne pomocou TEMPLATE PARAMETER DEDUCTION
template<typename... TTypes, typename TType>
void TemplateMultipleTemplateParameterPacks1(CVariadicTemplate<TTypes...> Parameter1, TType Parameter2)
{
	wcout << L"TEMPLATE FUNCTION 1 - PARAMETER 1 - TYPE [" << GetTypeInfoName<decltype(Parameter1)>() << L"]." << endl;

	Parameter1.Print(L"TEMPLATE FUNCTION 1 - PARAMETER 1");

	PrintLineSeparator();

	wcout << L"TEMPLATE FUNCTION 1 - PARAMETER 2 - TYPE [" << GetTypeInfoName<decltype(Parameter2)>() << L"] - VALUE [" << Parameter2 << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE FUNCTIONS MOZU mat viacero TEMPLATE PARAMETERS PACKS ak TEMPLATE PARAMETERS vo viacerych TEMPLATE PARAMETERS PACKS mozu byt jednoznacne identifikovane pomocou TEMPLATE PARAMETER DEDUCTION.
template<typename... TTypes1, typename... TTypes2>
void TemplateMultipleTemplateParameterPacks2(CVariadicTemplate1<TTypes1...> Parameter1, CVariadicTemplate2<TTypes2...> Parameter2)
{
	wcout << L"TEMPLATE FUNCTION 2 - PARAMETER 1 - TYPE [" << GetTypeInfoName<decltype(Parameter1)>() << L"]." << endl;

	Parameter1.Print(L"TEMPLATE FUNCTION 2 - PARAMETER 1");

	PrintLineSeparator();

	wcout << L"TEMPLATE FUNCTION 2 - PARAMETER 2 - TYPE [" << GetTypeInfoName<decltype(Parameter2)>() << L"]." << endl;

	Parameter2.Print(L"TEMPLATE FUNCTION 2 - PARAMETER 2");
}
//----------------------------------------------------------------------------------------------------------------------
void TestMultipleTemplateParameterPacks(void)
{
	PrintLineSeparator();

	{
		// !!! Pouzije sa TEMPLATE VARIABLE.
		TemplateMultipleTemplateParameterPacksVariable<CString,int> =CVariadicTemplate<CString,int>(L"Timmy",12);

		TemplateMultipleTemplateParameterPacksVariable<CString,int>.Print(L"TEMPLATE VARIABLE");

		PrintLineSeparator();

		TemplateMultipleTemplateParameterPacksVariable<CVariadicTemplate1<CString,int>,CVariadicTemplate2<CString,int,double>> =CMultipleTemplateParameterPacksSpecialization<CVariadicTemplate1<CString,int>,CVariadicTemplate2<CString,int,double>>(CVariadicTemplate1<CString,int>(L"Timmy",12),CVariadicTemplate2<CString,int,double>(L"Jenny",12,123.456));

		TemplateMultipleTemplateParameterPacksVariable<CVariadicTemplate1<CString,int>,CVariadicTemplate2<CString,int,double>>.Print(L"TEMPLATE VARIABLE SPECIALIZATION");
	}

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	{
		CVariadicTemplate<CString,int>							Object1(L"Timmy",12);
		int														Object2=100;

		TemplateMultipleTemplateParameterPacks1(Object1,Object2);
	}

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	{
		CVariadicTemplate1<CString,int>							Object1(L"Timmy",12);
		CVariadicTemplate2<CString,int,double>					Object2(L"Jenny",13,123.456);

		TemplateMultipleTemplateParameterPacks2(Object1,Object2);
	}

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	{
		CVariadicTemplate1<CString,int>							Object1(L"Timmy",12);
		CVariadicTemplate2<CString,int,double>					Object2(L"Jenny",13,123.456);
		CMultipleTemplateParameterPacksSpecialization<CVariadicTemplate1<CString,int>,CVariadicTemplate2<CString,int,double>>	Object(Object1,Object2);

		Object.Print(L"TEMPLATE CLASS");
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE FUNCTION moze mat definovany DEFAULT TEMPLATE ARGUMENT aj pre TEMPLATE PARAMETER hoci za nim nasleduju dalsie TEMPLATE PARAMETERS, ktore DEFAULT TEMPLATE ARGUMENTS vtedy, ak tieto pre TEMPLATE PARAMETERS mozu byt ich ARGUMENTS DEDUCED.
template<typename TReturnValue=double, typename TType1, typename TType2>
TReturnValue TemplateFunctionDefaultArguments(TType1 Parameter1, TType2 Parameter2)
{
	wcout << MACRO_FUNCTION_PROTOTYPE << endl;

	TReturnValue												ReturnValue=(Parameter1+Parameter2);

	return(ReturnValue);
}
//----------------------------------------------------------------------------------------------------------------------
// !!! VARIADIC TEMPLATE FUNCTION.
// !!!!! COMPILER hodi ERROR, pretoze pre TEMPLATE PARAMETER PACK NIE JE mozne definovat DEFAULT TEMPLATE ARGUMENTS.
//template<typename TType, typename... TTypes=int>
template<typename TType, typename... TTypes>
void TemplateVariadicTemplateDefaultArguments(TType Value, TTypes... Values)
{
	std::wcout << L"TEMPLATE FUNCTION - TYPE [" << GetTypeInfoName<TType>() << L"] - VALUE [" << Value << L"]." << std::endl;

	if constexpr (sizeof...(TTypes)>0)
	{
		TemplateVariadicTemplateDefaultArguments(Values...);
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateDefaultArguments(void)
{
	PrintLineSeparator();

	{
		// !!! POUZIJE sa DEFAULT TEMPLATE ARGUMENT.
		CTemplateClassDefaultArguments1<CString>				Object(L"Timmy",12);

		wcout << L"OBJECT - TYPE [" << GetTypeInfoName<decltype(Object)>() << L"] - FIELD 1 [" << Object.GetField1() << L"] FIELD 2 [" << Object.GetField2() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! NEPOUZIJE sa DEFAULT TEMPLATE ARGUMENT.
		CTemplateClassDefaultArguments1<CString,double>			Object(L"Timmy",12.12);

		wcout << L"OBJECT - TYPE [" << GetTypeInfoName<decltype(Object)>() << L"] - FIELD 1 [" << Object.GetField1() << L"] FIELD 2 [" << Object.GetField2() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! POUZIJU sa DEFAULT TEMPLATE ARGUMENTS.
		CTemplateClassDefaultArguments2<CString,int>			Object(L"Timmy",12,13.13,14.14f,L'X',true);

		wcout << L"OBJECT - TYPE [" << GetTypeInfoName<decltype(Object)>() << L"] - FIELD 1 [" << Object.GetField1() << L"] FIELD 2 [" << Object.GetField2() << L"] FIELD 3 [" << Object.GetField3() << L"] FIELD 4 [" << Object.GetField4() << L"] FIELD 5 [" << Object.GetField5() << L"] FIELD 6 [" << Object.GetField6() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		double													ReturnValue=TemplateFunctionDefaultArguments(10,20L);

		wcout << L"RETURN VALUE [" << ReturnValue << L"]." << endl;
	}

	PrintLineSeparator();

	{
		long													ReturnValue=TemplateFunctionDefaultArguments<long>(10,20L);

		wcout << L"RETURN VALUE [" << ReturnValue << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Pouzije sa PRIMARY TEMPLATE CLASS.
		CTemplateClassDefaultArgumentsSpecializations<CString,CString>	Object(L"Timmy",L"Anderson");

		Object.Print();
	}

	PrintLineSeparator();

	{
		// !!! Pouzije sa TEMPLATE CLASS SPECIALIZATION.
		CTemplateClassDefaultArgumentsSpecializations<CString,int>	Object(L"Timmy",12);

		Object.Print();
	}

	PrintLineSeparator();

	{
		TemplateVariadicTemplateDefaultArguments(CString(L"Timmy"),12);
	}

	PrintLineSeparator();

	{
		CTemplateClassDefaultArgumentsOutOfClass<CString,int>	Object(L"Timmy",12);

		wcout << L"OBJECT - TYPE [" << GetTypeInfoName<decltype(Object)>() << L"] - FIELD 1 [" << Object.GetField1() << L"] FIELD 2 [" << Object.GetField2() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CTemplateClassDefaultArgumentsFriends<CString,int>		Object1(L"Timmy",12);
		CTemplateClassDefaultArgumentsFriendsFriend<CString,int>	Object2(Object1);

		Object2.Print();
	}

	PrintLineSeparator();

	{
		CTemplateClassDefaultArgumentsFriends<CString,int>		Object(L"Timmy",12);

		FriendPrint1(Object);
	}

	PrintLineSeparator();

	{
		CTemplateClassDefaultArgumentsFriends<CString,int>		Object(L"Timmy",12);

		FriendPrint2<CString>(Object);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void TemplateTemplateParametersSubstitutions1(TType Value)
{
	wcout << L"FUNCTION 1 - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] - VALUE [" << Value << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
// !!! TEMPLATE PARAMETER ma definovany DEFAULT TEMPLATE ARGUMENT.
template<typename TReturnValue=int, typename TType>
TReturnValue TemplateTemplateParametersSubstitutions2(TType Value)
{
	wcout << L"FUNCTION 2 - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] RETURN TYPE [" << GetTypeInfoName<TReturnValue>() << L"] - VALUE [" << Value << L"]." << endl;

	TReturnValue												ReturnValue=static_cast<TReturnValue>(Value);

	return(ReturnValue);
}
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateParametersSubstitutions(void)
{
	PrintLineSeparator();

	{
		// !!! TEMPLATE ARGUMENT je definovany EXPLICITNE.
		TemplateTemplateParametersSubstitutions1<int>(100);
	}

	PrintLineSeparator();

	{
		// !!! TEMPLATE ARGUMENT je DEDUCED.
		TemplateTemplateParametersSubstitutions1(123.456);
	}

	PrintLineSeparator();

	{
		// !!! Ako TEMPLATE ARGUMENT je pouzity DEFAULT TEMPLATE ARGUMENT.
		int														ReturnValue=TemplateTemplateParametersSubstitutions2(123.456);

		wcout << L"RETURN VALUE [" << ReturnValue << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! TEMPLATE ARGUMENT je definovany EXPLICITNE.
		double													ReturnValue=TemplateTemplateParametersSubstitutions2<double>(123.456);

		wcout << L"RETURN VALUE [" << ReturnValue << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CTemplateParametersSubstitutions<CString,int>			Object(L"Timmy",12);

		wcout << L"OBJECT - FIELD 1 [" << Object.GetValue1() << L"] FIELD 2 [" << Object.GetValue2() << L"]." << endl;

		const CTemplateParametersSubstitutions<CString,int>*	PointerToObject=Object.GetThis();

		wcout << L"POINTER TO OBJECT - FIELD 1 [" << PointerToObject->GetValue1() << L"] FIELD 2 [" << PointerToObject->GetValue2() << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TConvertedType=int, typename TType>
void TemplateTemplateFunctionParametersSubstitutions1(TType Value)
{
	TConvertedType												ConvertedValue=static_cast<TConvertedType>(Value);

	wcout << L"FUNCTION 1 - VALUE [" << Value << L"] CONVERTED VALUE [" << ConvertedValue << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
// !!! TEMPLATE PARAMETERS, ktore NEMOZU byt DEDUCED by mali byt vzdy na ZACIATKU TEMPLATE PARAMETER LIST, lebo musia byt definovane EXPLICITNE. Tie ktore mozu byt DEDUCED by sa mali nachadzat az neskor, aby mohli byt DEDUCED.
template<typename TConvertedType, typename TType>
void TemplateTemplateFunctionParametersSubstitutions2(TType Value)
{
	TConvertedType												ConvertedValue=static_cast<TConvertedType>(Value);

	wcout << L"FUNCTION 2 - VALUE [" << Value << L"] CONVERTED VALUE [" << ConvertedValue << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void TemplateTemplateFunctionParametersSubstitutions3A(TType Value)
{
	wcout << L"FUNCTION 3A - BY VALUE - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] - VALUE [" << Value << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void TemplateTemplateFunctionParametersSubstitutions3B(TType Value)
{
	wcout << L"FUNCTION 3B - BY VALUE - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] - VALUE [" << Value << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void TemplateTemplateFunctionParametersSubstitutions3B(TType* Value)
{
	wcout << L"FUNCTION 3B - BY POINTER - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] - VALUE [" << (*Value) << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TFunction, typename TType>
void UseTemplateTemplateFunctionParametersSubstitutions(TFunction Function, TType Value)
{
	Function(Value);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void TemplateTemplateFunctionParametersSubstitutions4(typename TType::SomeType Value)
{
	wcout << L"FUNCTION 4 - VALUE [" << Value << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void TemplateTemplateFunctionParametersSubstitutions4(...)
{
	wcout << L"FUNCTION 4 - VALUE [...]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateFunctionParametersSubstitutions(void)
{
	PrintLineSeparator();

	{
		// !!! TEMPLATE PARAMETERS su definovane EXPLICITNE.
		TemplateTemplateFunctionParametersSubstitutions1<double,double>(123.456);
	}

	PrintLineSeparator();

	{
		// !!! 1. TEMPLATE PARAMETER je urceny na zaklade DEFAULT VALUE a 2. TEMPLATE PARAMETER je DEDUCED.
		TemplateTemplateFunctionParametersSubstitutions1(123.456);
	}

	PrintLineSeparator();

	{
		// !!! 1. TEMPLATE PARAMETER MUSI byt urceny EXPLICITNE, lebo NEMOZE byt DEDUCED a 2. TEMPLATE PARAMETER je DEDUCED.
		TemplateTemplateFunctionParametersSubstitutions2<int>(123.456);
	}

	PrintLineSeparator();

	{
		int														Value=100;
		int*													PointerToValue=&Value;

		// !!! C++ spravi spravny RESOLUTION.
		TemplateTemplateFunctionParametersSubstitutions3A<int>(Value);

		// !!! C++ spravi spravny RESOLUTION.
		TemplateTemplateFunctionParametersSubstitutions3B<int>(Value);

		// !!! C++ spravi spravny RESOLUTION.
		TemplateTemplateFunctionParametersSubstitutions3B<int>(PointerToValue);

		// !!! C++ vyberie FUNCTION, kedze NIE JE OVERLOADED.
		UseTemplateTemplateFunctionParametersSubstitutions(&TemplateTemplateFunctionParametersSubstitutions3A<int>,200);

		/*
		// !!!!! C++ hodi COMPILATION ERROR, pretoze nevie vybrat z 2 OVERLOADED VERZII danej FUNCTION.
		UseTemplateTemplateFunctionParametersSubstitutions(&TemplateTemplateFunctionParametersSubstitutions3B<int>,300);
		*/
	}

	PrintLineSeparator();

	{
		// !!!!!! Pretoze FUNCTION je OVERLOADED, C++ musi spravit RESOLUTION medzi FUNCTIONS.
		// 1. FUNCTION [void TemplateTemplateFunctionParametersSubstitutions4(typename TType::SomeType Value)].
		// 2. FUNCTION [void TemplateTemplateFunctionParametersSubstitutions4(...)].
		// !!!!! Kedze TYPE [int] NEMA TYPE [SomeType], tak vyber 1. FUNCTION sposobi COMPILERATION ERROR, ktory je vsak vdaka principu SFINAE IGNOROVANY.
		// !!! C++ vyberie 2. FUNCTION, pretoze ta vyhovuje zadanemu ARGUMENT.
		TemplateTemplateFunctionParametersSubstitutions4<int>(100);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void NonTypeTemplateParametersTypesSubstitutions1(int Value)
{
	wcout << L"FUNCTION 1 - VALUE [" << Value << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void NonTypeTemplateParametersTypesSubstitutions2(TType Value)
{
	wcout << L"FUNCTION 2 - VALUE [" << Value << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void NonTypeTemplateParametersTypesSubstitutions3(int Value)
{
	wcout << L"FUNCTION 3 - VALUE [" << Value << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, int TType::*VALUE>
void NonTypeTemplateParametersTypesSubstitutionsPointerToMemberField(TType Object)
{
	wcout << L"POINTER TO MEMBER FIELD - VALUE [" << Object.*VALUE << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, int (CValue::*VALUE)(void) const noexcept>
void NonTypeTemplateParametersTypesSubstitutionsPointerToMemberMethod(TType Object)
{
	wcout << L"POINTER TO MEMBER METHOD - VALUE [" << (Object.*VALUE)() << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestNonTypeTemplateParametersTypesSubstitutions(void)
{
	PrintLineSeparator();

	{
		// !!! Substitucia za INTEGER TYPE.
		CNonTypeTemplateParameters<int,100>						Object;

		wcout << L"TYPE [" << GetTypeInfoName<decltype(Object)>() << L"] - VALUE [" << Object.GetVALUE() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		static int												Variable=100;

		// !!!!! Ako TEMPLATE NON-TYPE ARGUMENT NEMOZE byt pouzita ADDRESS LOCAL VARIABLE, pretoze ta je znama az v RUNTIME. Ale moze byt pouzita ADDRESS na STATIC VARIABLE, lebo tak je znama uz v COMPILE (LINKING) TIME.
		CNonTypeTemplateParameters<int*,&Variable>				Object;

		wcout << L"TYPE [" << GetTypeInfoName<decltype(Object)>() << L"] - VALUE [" << *(Object.GetVALUE()) << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!!!! Ako TEMPLATE NON-TYPE ARGUMENT je pouzity POINTER na FUNCTION.
		CNonTypeTemplateParameters<void(*)(int),&NonTypeTemplateParametersTypesSubstitutions1>	Object;

		wcout << L"TYPE [" << GetTypeInfoName<decltype(Object)>() << L"]." << endl;

		Object.GetVALUE()(100);
	}

	PrintLineSeparator();

	{
		// !!!!! Ako TEMPLATE NON-TYPE ARGUMENT je pouzity POINTER na TEMPLATE FUNCTION.
		CNonTypeTemplateParameters<void(*)(int),&NonTypeTemplateParametersTypesSubstitutions2<int>>	Object;

		wcout << L"TYPE [" << GetTypeInfoName<decltype(Object)>() << L"]." << endl;

		Object.GetVALUE()(100);
	}

	PrintLineSeparator();

	{
		// !!!!! Ako TEMPLATE NON-TYPE ARGUMENT je pouzity REFERENCE na FUNCTION.
		CNonTypeTemplateParameters<void(&)(int),NonTypeTemplateParametersTypesSubstitutions3>	Object;

		wcout << L"TYPE [" << GetTypeInfoName<decltype(Object)>() << L"]." << endl;

		Object.GetVALUE()(100);
	}

	PrintLineSeparator();

	{
		// !!!!! Ako TEMPLATE NON-TYPE ARGUMENT je pouzity REFERENCE na STATIC FIELD.
		CNonTypeTemplateParameters<int&,CNonTypeTemplateParameters<int,100>::MStaticField>	Object;

		wcout << L"TYPE [" << GetTypeInfoName<decltype(Object)>() << L"] - VALUE [" << Object.GetVALUE() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!!!! Ako TEMPLATE NON-TYPE ARGUMENT je pouzita VALUE vratena CONSTEXPR CONVERSION OPERERATOR [operator int()].
		CNonTypeTemplateParameters<int,CNonTypeTemplateParameters<int,100>{}>	Object;

		wcout << L"TYPE [" << GetTypeInfoName<decltype(Object)>() << L"] - VALUE [" << Object.GetVALUE() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CValue													Object(100);

		TemplateNonTypeTemplateParametersTypesPointerToMemberField<CValue,&CValue::MField>(Object);
	}

	PrintLineSeparator();

	{
		CValue													Object(100);

		TemplateNonTypeTemplateParametersTypesPointerToMemberMethod<CValue,&CValue::GetValue>(Object);
	}

	PrintLineSeparator();

	{
		static wchar_t											Array[]{L"Timmy"};

		// !!!!! Ako TEMPLATE NON-TYPE ARGUMENT je pouzity STATIC pouzita VARIABLE vracajuca STRING.
		CNonTypeTemplateParameters<wchar_t*,Array>				Object;

		wcout << L"TYPE [" << GetTypeInfoName<decltype(Object)>() << L"] - VALUE [" << Object.GetVALUE() << L"]." << endl;
	}

	/*
	PrintLineSeparator();

	// !!!!! COMPILER hodi ERROR, pretoze STRING LITERALS NIE JE mozne pouzit ako ARGUMENTS pre TEMPLATE NON-TYPE PARAMETERS.
	{
		// !!!!! Ako TEMPLATE NON-TYPE ARGUMENT je pouzity STATIC VARIABLE na STRING LITERAL.
		CNonTypeTemplateParameters<const wchar_t*,L"Timmy">		Object;

		wcout << L"TYPE [" << GetTypeInfoName<decltype(Object)>() << L"] - VALUE [" << Object.GetVALUE() << L"]." << endl;
	}
	*/

	PrintLineSeparator();

	{
		static CClassBase										StaticObject(L"BASE");

		// !!!!! Ako TEMPLATE NON-TYPE ARGUMENT je pouzity POINTER na STATIC VARIABLE TYPE BASE CLASS.
		CNonTypeTemplateParameters<CClassBase*,&StaticObject>	Object;

		wcout << L"TYPE [" << GetTypeInfoName<decltype(Object)>() << L"] - VALUE [" << Object.GetVALUE()->GetField() << L"]." << endl;
	}

	/*
	PrintLineSeparator();

	// !!!!! COMPILER hodi ERROR, pretoze neakceptuje POINTER na DERIVED CLASS ako TEMPLATE NON-TYPE ARGUMENT, ktory ma TYPE POINTER na BASE CLASS.
	{
		static CClassDerived									StaticObject(L"DERIVED");

		// !!!!! Ako TEMPLATE NON-TYPE ARGUMENT je pouzity POINTER na STATIC VARIABLE TYPE DERIVED CLASS.
		CNonTypeTemplateParameters<CClassBase*,&StaticObject>	Object;

		wcout << L"TYPE [" << GetTypeInfoName<decltype(Object)>() << L"] - VALUE [" << Object.GetVALUE()->GetField() << L"]." << endl;
	}
	*/

	PrintLineSeparator();

	{
		static CClassBase										StaticObject(L"BASE");

		// !!!!! Ako TEMPLATE NON-TYPE ARGUMENT je pouzity REFERENCE na CLASS FIELD.
		CNonTypeTemplateParameters<CString&,StaticObject.MField>	Object;

		wcout << L"TYPE [" << GetTypeInfoName<decltype(Object)>() << L"] - VALUE [" << Object.GetVALUE() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		static int												StaticObject[]{10,20,30};

		// !!!!! Ako TEMPLATE NON-TYPE ARGUMENT je pouzity POINTER na STATIC VARIABLE TYPE DERIVED CLASS.
		CNonTypeTemplateParameters<int*,&StaticObject[1]>		Object;

		wcout << L"TYPE [" << GetTypeInfoName<decltype(Object)>() << L"] - VALUE [" << *(Object.GetVALUE()) << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateTemplateParametersTypesSubstitutions(void)
{
	PrintLineSeparator();

	{
		// !!! TEMPLATE ma TEMPLATE TYPE PARAMETER.
		CTemplateTemplateArguments1<CString>				Argument(L"Jenny");

		// !!! TEMPLATE TEMPLATE ARGUMENT [CTemplateTemplateArguments1<CString>] ma 1 TEMPLATE TYPE PARAMETER co splna poziadavky TEMPLATE TEMPLATE PARAMETER, ktory vyzaduje TEMPLATE, ktora ma 1 TEMPLATE TYPE PARAMETER.
		CTemplateTemplateParameters1<CString,int,CTemplateTemplateArguments1>	Object(L"Timmy",12,Argument);

		wcout << Object.ToString() << endl;
	}

	PrintLineSeparator();

	{
		// !!! TEMPLATE ma 1. TEMPLATE TYPE PARAMETER a 2. TEMPLATE TYPE PARAMETER s DEFAULT TEMPLATE TYPE ARGUMENT.
		CTemplateTemplateArguments2<CString>				Argument(L"Jenny",13);

		// !!! TEMPLATE TEMPLATE ARGUMENT [CTemplateTemplateArguments2<CString>] ma 2 TEMPLATE TYPE PARAMETERS, avsak 2. TEMPLATE PARAMETER ma DEFAULT TEMPLATE TYPE ARGUMENT. Preto tento TYPE splna poziadavky TEMPLATE TEMPLATE PARAMETER, ktory vyzaduje TEMPLATE, ktora ma 1 TEMPLATE TYPE PARAMETER.
		CTemplateTemplateParameters1<CString,int,CTemplateTemplateArguments2>	Object(L"Timmy",12,Argument);

		wcout << Object.ToString() << endl;
	}

	PrintLineSeparator();

	{
		// !!! TEMPLATE ma 1. TEMPLATE TYPE PARAMETER a 2. TEMPLATE NON-TYPE PARAMETER.
		CTemplateTemplateArguments3<CString,200>				Argument(L"Jenny");

		// !!! TEMPLATE TEMPLATE ARGUMENT [CTemplateTemplateArguments3<CString,200>] ma 1. TEMPLATE TYPE PARAMETERS a 2. TEMPLATE NON-TYPE PARAMETER. Preto tento TYPE splna poziadavky TEMPLATE TEMPLATE PARAMETER, ktory vyzaduje TEMPLATE, ktora ma 1. TEMPLATE TYPE PARAMETER a 2. TEMPLATE NON-TYPE PARAMETER.
		CTemplateTemplateParameters2<CString,int,CTemplateTemplateArguments3>	Object(L"Timmy",12,Argument);

		wcout << Object.ToString() << endl;
	}

	/*
	PrintLineSeparator();

	{
		// !!! TEMPLATE ma 1. TEMPLATE TYPE PARAMETER a 2. TEMPLATE NON-TYPE PARAMETER.
		CTemplateTemplateArguments3<CString,200>				Argument(L"Jenny");

		// !!!!! COMPILER hodi ERROR, pretoze TEMPLATE ocakava TEMPLATE TEMPLATE ARGUMENT, ktory ma 2 TEMPLATE TYPE PARAMETERS, ale je mu poskytnuta TEMPLATE, ktora ma ako 1. TEMPLATE TYPE PARAMETER a ako 1. TEMPLATE NON-TYPE PARAMETER.
		CTemplateTemplateParameters1<CString,int,CTemplateTemplateArguments3>	Object(L"Timmy",12,Argument);

		wcout << Object.ToString() << endl;
	}
	*/

	PrintLineSeparator();

	{
		// !!! TEMPLATE ma 1. TEMPLATE TYPE PARAMETER a 2. TEMPLATE TYPE PARAMETER.
		CTemplateTemplateArguments2<CString,int>				Argument(L"Jenny",13);

		// !!!!! TEMPLATE prijma TEMPLATE TEMPLATE PARAMETER, ktory musi mat ako TEMPLATE TEMPLATE ARGUMENT TEMPLATE, ktora ma LUBOVOLNY pocet TEMPLATE PARAMETERS.
		// !!!!! Avsak CONSTRUCTOR ocakava ako posledny PARAMETER TEMPLATE TEMPLATE PARAMETER, ktory musi mat ako TEMPLATE TEMPLATE ARGUMENT TEMPLATE, ktora ma 2 TEMPLATE TYPE PARAMETERS.
		CTemplateTemplateParameters3<CString,int,CTemplateTemplateArguments2>	Object(L"Timmy",12,Argument);

		wcout << Object.ToString() << endl;
	}

	/*
	PrintLineSeparator();

	{
		// !!! TEMPLATE ma 1. TEMPLATE TYPE PARAMETER a 2. TEMPLATE TYPE PARAMETER.
		CTemplateTemplateArguments1<CString>				Argument(L"Jenny");

		// !!!!! TEMPLATE prijma TEMPLATE TEMPLATE PARAMETER, ktory musi mat ako TEMPLATE TEMPLATE ARGUMENT TEMPLATE, ktora ma LUBOVOLNY pocet TEMPLATE PARAMETERS.
		// !!!!! COMPILER hodi ERROR, pretoze CONSTRUCTOR ocakava ako posledny PARAMETER TEMPLATE TEMPLATE PARAMETER, ktory musi mat ako TEMPLATE TEMPLATE ARGUMENT TEMPLATE, ktora ma 2 TEMPLATE TYPE PARAMETERS. Avsak poskytnuty TEMPLATE TEMPLATE ARGUMENT ma iba 1 TEMPLATE TYPE PARAMETER.
		CTemplateTemplateParameters3<CString,int,CTemplateTemplateArguments1>	Object(L"Timmy",12,Argument);

		wcout << Object.ToString() << endl;
	}
	*/

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
/**/
// !!!!! DECLARATION TEMPLATE FUNCTION.
// !!!!! FUNCTION ma PROTOTYPE [void TemplateTemplateArgumentsEquivalence(CTemplateArgumentEquivalence<int, (VALUE_1 + VALUE_2)>) [with int VALUE_1 = 30; int VALUE_2 = 70]].
template<int VALUE_1, int VALUE_2>
void TemplateTemplateArgumentsEquivalence(CTemplateArgumentEquivalence<int,VALUE_1+VALUE_2> Value);
//----------------------------------------------------------------------------------------------------------------------
// !!!!! DECLARATION TEMPLATE FUNCTION, ktora je EKVIVALENTNA s predoslou DECLARATION.
// !!!!! FUNCTION ma PROTOTYPE [void TemplateTemplateArgumentsEquivalence(CTemplateArgumentEquivalence<int, (VALUE_1 + VALUE_2)>) [with int VALUE_1 = 30; int VALUE_2 = 70]].
template<int VALUE_2, int VALUE_1>
void TemplateTemplateArgumentsEquivalence(CTemplateArgumentEquivalence<int,VALUE_2+VALUE_1> Value);
/**/
//----------------------------------------------------------------------------------------------------------------------
/*
// !!!!! DECLARATION TEMPLATE FUNCTION, ktora NIE JE EKVIVALENTNA s predoslou DECLARATION.
// !!!!! FUNCTION ma PROTOTYPE [void TemplateTemplateArgumentsEquivalence(CTemplateArgumentEquivalence<int, (VALUE_2 + VALUE_1)>) [with int VALUE_1 = 30; int VALUE_2 = 70]].
// !!!!! Aj ked tento CODE by mal sposobit COMPILATION ERROR, nie kazdy C++ COMPILER ju dokaze odhalit.
template<int VALUE_1, int VALUE_2>
void TemplateTemplateArgumentsEquivalence(CTemplateArgumentEquivalence<int,VALUE_2+VALUE_1> Value);
*/
//----------------------------------------------------------------------------------------------------------------------
/**/
// !!!!! DEFINITION TEMPLATE FUNCTION.
// !!!!! FUNCTION ma PROTOTYPE [void TemplateTemplateArgumentsEquivalence(CTemplateArgumentEquivalence<int, (VALUE_1 + VALUE_2)>) [with int VALUE_1 = 30; int VALUE_2 = 70]].
template<int VALUE_1, int VALUE_2>
void TemplateTemplateArgumentsEquivalence(CTemplateArgumentEquivalence<int,VALUE_1+VALUE_2> Value)
{
	wcout << MACRO_FUNCTION_PROTOTYPE << endl;

	wcout << "FUNCTION 1 - " << Value.ToString() << endl;
}
/**/
//----------------------------------------------------------------------------------------------------------------------
/*
// !!!!! DEFINITION TEMPLATE FUNCTION.
template<int VALUE_1, int VALUE_2>
// !!!!! FUNCTION ma PROTOTYPE [void TemplateTemplateArgumentsEquivalence(CTemplateArgumentEquivalence<int, (VALUE_2 + VALUE_1)>) [with int VALUE_1 = 30; int VALUE_2 = 70]].
void TemplateTemplateArgumentsEquivalence(CTemplateArgumentEquivalence<int,VALUE_2+VALUE_1> Value)
{
	wcout << MACRO_FUNCTION_PROTOTYPE << endl;

	wcout << "FUNCTION 2 - " << Value.ToString() << endl;
}
*/
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateArgumentsEquivalence(void)
{
	PrintLineSeparator();

	{
		CTemplateArgumentEquivalence<int,3*3>					Object1(100);
		CTemplateArgumentEquivalence<int,4+5>					Object2(200);

		wcout << Object1.ToString() << endl;
		wcout << Object2.ToString() << endl;

		// !!!!! Oba OBJECT su EKVIVALENTNE.
		Object1=Object2;

		wcout << Object1.ToString() << endl;
		wcout << Object2.ToString() << endl;
	}

	PrintLineSeparator();

	{
		CTemplateArgumentEquivalence<int,100>					Object(200);

		TemplateTemplateArgumentsEquivalence<30,70>(Object);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateMethodsNonEquivalence(void)
{
	PrintLineSeparator();

	{
		CTemplateMethodsNonEquivalence1							Object(L"Timmy");

		wcout << "OBJECT [" << Object.GetValue() << L"] !" << endl;

		// !!!!! NEVOLA sa TEMPLATE COPY CONSTRUCTOR, pretoze TEMPLATE COPY/MOVE CONSTRUCTORS a TEMPLATE OPERATOR [COPY/MOVE OPERATOR=] su C++ IGNOROVANE, a namiesto nich su volane DEFAULT COPY/MOVE CONSTRUCTORS a DEFAULT OPERATOR [COPY/MOVE OPERATOR=], ktore generuje COMPILER.
		CTemplateMethodsNonEquivalence1							CopyObject(Object);

		wcout << "COPY OBJECT [" << CopyObject.GetValue() << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		CTemplateMethodsNonEquivalence2							Object(L"Timmy");

		wcout << "OBJECT [" << Object.GetValue() << L"] !" << endl;

		// !!!!! Vdaka pouzitiu DELETE COPY CONSTRUCTOR, ktory ma aplikovany aj KEYWORD [volatile] je mozne prinutit C++, aby volal pri COPY SEMANTICS TEMPLATE CONSTRUCTOR.
		CTemplateMethodsNonEquivalence2							CopyObject(Object);

		wcout << "COPY OBJECT [" << CopyObject.GetValue() << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		CTemplateMethodsNonEquivalence3							Object(wstring(L"Timmy"));

		wcout << "OBJECT [" << Object.GetValue() << L"] !" << endl;

		// !!!!! Vdaka pouzitiu DELETE COPY CONSTRUCTOR, ktory ma aplikovany aj KEYWORD [volatile] je mozne prinutit C++, aby volal pri COPY SEMANTICS TEMPLATE CONSTRUCTOR.
		CTemplateMethodsNonEquivalence3							CopyObject(Object);

		wcout << "COPY OBJECT [" << CopyObject.GetValue() << L"] !" << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestVariadicTemplates(void)
{
	PrintLineSeparator();

	{
		CVariadicTemplateClass<CString,int>						Object(L"Timmy",12);

		Object.Print(L"CLASS 1");

		wcout << "NUMBER OF TEMPLATE PARAMETERS [" << CVariadicTemplateClass<CString,int>::SIZE << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		CVariadicTemplateClass<CString,CString,int>				Object(L"Timmy",L"Anderson",12);

		Object.Print(L"CLASS 2");

		wcout << "NUMBER OF TEMPLATE PARAMETERS [" << CVariadicTemplateClass<CString,CString,int>::SIZE << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		CString													Parameter1(L"Timmy");
		double													Parameter2=12.12;
		int														Parameter3=12;
		CVariadicTemplateClassPackExpansion<CString,double,int>	Object(&Parameter1,&Parameter2,&Parameter3);

		Object.Print(L"CLASS EXPANSION PACK 1");

		wcout << "NUMBER OF TEMPLATE PARAMETERS [" << CVariadicTemplateClassPackExpansion<CString,double,int>::SIZE << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		CString													Parameter1(L"Timmy");
		CString													Parameter2(L"Anderson");
		int														Parameter3=12;
		CVariadicTemplateClassPackExpansion<CString,CString,int>	Object(&Parameter1,&Parameter2,&Parameter3);

		Object.Print(L"CLASS EXPANSION PACK 2");

		wcout << "NUMBER OF TEMPLATE PARAMETERS [" << CVariadicTemplateClassPackExpansion<CString,CString,int>::SIZE << L"] !" << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestExpansionPack(void)
{
	PrintLineSeparator();

	{
		CVariadicClassBase1										Base1(L"BASE 1");
		CVariadicClassBase2										Base2(L"BASE 2");
		CVariadicClassDerived<CVariadicClassBase1,CVariadicClassBase2>	Derived(L"DERIVED",Base1,Base2);

		wcout << Derived.CVariadicClassBase1::ToString() << endl;
		wcout << Derived.CVariadicClassBase2::ToString() << endl;
		wcout << Derived.ToString() << endl;
	}

	PrintLineSeparator();

	{
		CVariadicClassOuter<int,long,bool>::CVariadicClassInner<100,200L,true>	Object;

		Object.Print();
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! FUNCTION ma FUNCTION PARAMETER PACK.
template<typename TType, typename... TTypes>
void PrintTemplateFunctionParameterPack(size_t Index, TType Parameter, TTypes... Parameters)
{
	wcout << "INDEX [" << Index << L"] PARAMETER [" << Parameter << L"] !" << endl;

	if constexpr (sizeof...(Parameters)>0)
	{
		PrintTemplateFunctionParameterPack((Index+1),Parameters...);
	}
}
//----------------------------------------------------------------------------------------------------------------------
// !!! FUNCTION ma FUNCTION PARAMETER PACK.
template<typename... TTypes>
void TemplateFunctionParameterPack(TTypes... Parameters)
{
	if constexpr (sizeof...(Parameters)>0)
	{
		PrintTemplateFunctionParameterPack(1,Parameters...);
	}
	else
	{
		wcout << "NO PARAMETERS." << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestFunctionParameterPack(void)
{
	PrintLineSeparator();

	{
		TemplateFunctionParameterPack(CString(L"Timmy"),CString(L"Anderson"),12);
	}

	PrintLineSeparator();

	{
		TemplateFunctionParameterPack();
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename... TTypes>
void InternalTemplateMultipleParameterPacksExpansion(size_t Index, TType Parameter, TTypes... Parameters)
{
	wcout << "INDEX [" << Index << L"] PARAMETER [" << Parameter << L"] !" << endl;

	if constexpr (sizeof...(Parameters)>0)
	{
		InternalTemplateMultipleParameterPacksExpansion((Index+1),Parameters...);
	}
}
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTypes>
void TemplateMultipleParameterPacksExpansion(TTypes... Values)
{
	if constexpr (sizeof...(Values)>0)
	{
		// !!!!! EXPANSION PACK sa vykonava nad 2 PARAMETER PACKS.
		// 1. PARAMETER PACK je PACK [TTypes], ktory vykonava CONVERSION jednotlivych PARAMETERS v EXPANSION PACK.
		// 2. PARAMETER PACK je PACK [Values], ktory obsahuje VALUES zaslane do TEMPLATE FUNCTION.
		InternalTemplateMultipleParameterPacksExpansion(1,TTypes(Values)...);
	}
	else
	{
		wcout << "NO PARAMETERS." << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestMultipleParameterPacksExpansion(void)
{
	PrintLineSeparator();

	{
		TemplateMultipleParameterPacksExpansion(CString(L"Timmy"),CString(L"Anderson"),12);
	}

	PrintLineSeparator();

	{
		TemplateMultipleParameterPacksExpansion();
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestNestedParameterPacksExpansion(void)
{
	PrintLineSeparator();

	CNestedParameterPacksExpansionOuter<CNestedParameterPacksExpansionInner1<CString,CString,int>,CNestedParameterPacksExpansionInner2<CString,CString,int>>	Object;

	Object.Print(CString(L"Timmy"),CString(L"Anderson"),12);

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestZeroLengthPackExpansion(void)
{
	PrintLineSeparator();

	{
		CVariadicClassBase1										Base1(L"BASE 1");
		CVariadicClassBase2										Base2(L"BASE 2");
		CVariadicClassDerived<CVariadicClassBase1,CVariadicClassBase2>	Derived(L"DERIVED",Base1,Base2);

		wcout << Derived.CVariadicClassBase1::ToString() << endl;
		wcout << Derived.CVariadicClassBase2::ToString() << endl;
		wcout << Derived.ToString() << endl;
	}

	PrintLineSeparator();

	{
		// !!!!! COMPILER NEHODI ERROR, ani ked TEMPLATE PARAMETER PACK je prazdny, pretoze PACK EXPANSION [...] nie je SYNTACTIC, ale SEMANTIC zalezitost.
		CVariadicClassDerived<>									Derived(L"DERIVED");

		wcout << Derived.ToString() << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
TType TemplateOperatorFoldExpressions1Add5(TType Value)
{
	return(Value+5);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTypes>
common_type_t<TTypes...> TemplateOperatorFoldExpressions1UnaryLeftFold(TTypes... Values)
{
	// !!!!! Pouziva sa UNARY LEFT FOLD OPERATOR.
	common_type_t<TTypes...>									Result=(... + Values);

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTypes>
common_type_t<TTypes...> TemplateOperatorFoldExpressions1UnaryRightFold(TTypes... Values)
{
	// !!!!! Pouziva sa UNARY RIGHT FOLD OPERATOR.
	common_type_t<TTypes...>									Result=(Values + ...);

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename... TTypes>
common_type_t<TType,TTypes...> TemplateOperatorFoldExpressions1BinaryLeftFold(TType InitValue, TTypes... Values)
{
	// !!!!! Pouziva sa BINARY LEFT FOLD OPERATOR.
	common_type_t<TType,TTypes...>								Result=(InitValue + ... + Values);

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename... TTypes>
common_type_t<TType,TTypes...> TemplateOperatorFoldExpressions1BinaryRightFold(TType InitValue, TTypes... Values)
{
	// !!!!! Pouziva sa BINARY RIGHT FOLD OPERATOR.
	common_type_t<TType,TTypes...>								Result=(Values + ... + InitValue);

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename... TTypes>
common_type_t<TType,TTypes...> TemplateOperatorFoldExpressions1ComplexExpression(TType InitValue, TTypes... Values)
{
	// !!!!! Vo FOLD EXPRESSIONS je mozne pouzivat SUBEXPRESSIONS, ktore vsak musia byt uzatvorene v zatvorkach [()].
	common_type_t<TType,TTypes...>								Result=((Values+2) + ... + (InitValue+1));

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename... TTypes>
common_type_t<TType,TTypes...> TemplateOperatorFoldExpressions1UnaryFoldEmptyParameterPack(TType Value, TTypes... Values)
{
	// !!!!! UNARY FOLD OPERATOR NIE je mozne pouzit, aj ked je TEMPLATE PARAMETER PACK PRAZDNY. COMPILER hodi ERROR
	common_type_t<TType,TTypes...>								Result=(... + Values);

	Result+=Value;

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename... TTypes>
common_type_t<TType,TTypes...> TemplateOperatorFoldExpressions1BinaryFoldEmptyParameterPack(TType Value, TTypes... Values)
{
	// !!!!! BINARY FOLD OPERATOR je mozne pouzit, aj ked je TEMPLATE PARAMETER PACK PRAZDNY.
	common_type_t<TType,TTypes...>								Result=(Value + ... + Values);

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename... TTypes>
common_type_t<TType,TTypes...> TemplateOperatorFoldExpressions1CallFunction(TType Value, TTypes... Values)
{
	// !!!!! Pre kazdy TEMPLATE PARAMETER sa vola FUNCTION [TType TemplateOperatorFoldExpressions1Add5(TType Value)].
	common_type_t<TType,TTypes...>								Result=(Value + ... + TemplateOperatorFoldExpressions1Add5(Values));

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
void TestFoldExpressions1(void)
{
	PrintLineSeparator();

	{
		int														Result=TemplateOperatorFoldExpressions1UnaryLeftFold(10,20,30);

		wcout << L"UNARY LEFT FOLD [" << Result << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		int														Result=TemplateOperatorFoldExpressions1UnaryRightFold(10,20,30);

		wcout << L"UNARY RIGHT FOLD [" << Result << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		int														Result=TemplateOperatorFoldExpressions1BinaryLeftFold(100,10,20,30);

		wcout << L"BINARY LEFT FOLD [" << Result << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		int														Result=TemplateOperatorFoldExpressions1BinaryRightFold(100,10,20,30);

		wcout << L"BINARY RIGHT FOLD [" << Result << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		int														Result=TemplateOperatorFoldExpressions1ComplexExpression(100,10,20,30);

		wcout << L"RESULT [" << Result << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		int														Result=TemplateOperatorFoldExpressions1UnaryFoldEmptyParameterPack(100,10,20,30);

		wcout << L"RESULT [" << Result << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		int														Result=TemplateOperatorFoldExpressions1BinaryFoldEmptyParameterPack(100,10,20,30);

		wcout << L"RESULT [" << Result << L"] !" << endl;
	}

	/*
	PrintLineSeparator();

	// !!!!! COMPILER hodi ERROR, pretoze UNARY FOLD OPERATOR NEMOZE byt volany, ak je VARIADIC TEMPLATE PACK je PRAZDNY.
	{
		int														Result=TemplateOperatorFoldExpressions1UnaryFoldEmptyParameterPack(100);

		wcout << L"UNARY FOLD RESULT [" << Result << L"] !" << endl;
	}
	*/

	PrintLineSeparator();

	// !!!!! CODE zbehne OK, pretoze BINARY FOLD OPERATOR MOZE byt volany, ak je VARIADIC TEMPLATE PACK je PRAZDNY.
	{
		int														Result=TemplateOperatorFoldExpressions1BinaryFoldEmptyParameterPack(100);

		wcout << L"BINARY FOLD RESULT [" << Result << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		int														Result=TemplateOperatorFoldExpressions1CallFunction(100,10,20,30);

		wcout << L"CALL FUNCTION RESULT [" << Result << L"] !" << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TNode, typename TRootNode, typename... TNodes>
TNode* TemplateFoldExpressions2OperatorPointerToMember(TRootNode RootNode, TNodes... Nodes)
{
	// !!!!! Pouziva sa OPERATOR->* pre pristup k MEMBERS.
	TNode*														Result=(RootNode ->* ... ->* Nodes);

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
void TestFoldExpressions2(void)
{
	PrintLineSeparator();

	{
		SNode													Node1(10);
		SNode													Node2(20);
		SNode													Node3(30);

		Node1.SetRightNode(&Node2);
		Node2.SetLeftNode(&Node1);
		Node2.SetRightNode(&Node3);
		Node3.SetLeftNode(&Node2);

		// !!! Ziskaju sa POINTERS na MEMBERS.
		SNode*													SNode::*Left=&SNode::MLeftNode;
		SNode*													SNode::*Right=&SNode::MRightNode;

		// !!!!! Ako PATH sa pouzivaju POINTERS na MEMBERS.
		SNode*													Result=TemplateFoldExpressions2OperatorPointerToMember<SNode>(&Node1,Right,Left,Right,Right);

		wcout << L"NODE RESULT [" << Result->GetValue() << L"] !" << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TValue>
wstring TemplateFoldExpressions3Format(TValue Value, size_t& Index, size_t Count)
{
	wstringstream												Stream;

	if (Index>1)
	{
		Stream << L" ";
	}

	Stream << L"[" << Value << L"]";

	if (Index==Count)
	{
		Stream << L" !";
	}

	Index++;

	return(Stream.str());
}
//----------------------------------------------------------------------------------------------------------------------
template<typename... TValues>
wstringstream TemplateFoldExpressions3(TValues... Values)
{
	wstringstream												Stream;
	size_t														Index=1;

	Stream << L"VALUES ";

	// !!!!! Pouziva sa OPERATOR<< pre vypis ITEMS.
	(Stream << ... << TemplateFoldExpressions3Format(Values,Index,sizeof...(Values)));

	Stream << endl;

	return(Stream);
}
//----------------------------------------------------------------------------------------------------------------------
void TestFoldExpressions3(void)
{
	PrintLineSeparator();

	wstringstream												Stream=TemplateFoldExpressions3(L"Timmy",L"Anderson",12);

	wcout << Stream.str();

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename... TValues>
bool TemplateUnaryFoldExpressionAnd(TValues... Values)
{
	// !!!!! UNARY FOLD EXPRESSION pre OPERATOR&& moze mat aj 0 TEMPLATE PARAMETERS. V takom pripade je RESULT VALUE [true].
	bool														Result=(... && Values);

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename... TValues>
bool TemplateUnaryFoldExpressionOr(TValues... Values)
{
	// !!!!! UNARY FOLD EXPRESSION pre OPERATOR|| moze mat aj 0 TEMPLATE PARAMETERS. V takom pripade je RESULT VALUE [false].
	bool														Result=(... || Values);

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
void TestFoldExpressionsUnaryFoldExpressions(void)
{
	PrintLineSeparator();

	{
		bool													Result=TemplateUnaryFoldExpressionAnd(true,true,true);

		wcout << L"RESULT [" << Result << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		bool													Result=TemplateUnaryFoldExpressionAnd(true,false,true);

		wcout << L"RESULT [" << Result << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		// !!!!! UNARY FOLD EXPRESSION pre OPERATOR&& moze mat aj 0 TEMPLATE PARAMETERS. V takom pripade je RESULT VALUE [true].
		bool													Result=TemplateUnaryFoldExpressionAnd();

		wcout << L"RESULT [" << Result << L"] !" << endl;
	}

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	{
		bool													Result=TemplateUnaryFoldExpressionOr(true,true,true);

		wcout << L"RESULT [" << Result << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		bool													Result=TemplateUnaryFoldExpressionOr(false,false,false);

		wcout << L"RESULT [" << Result << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		// !!!!! UNARY FOLD EXPRESSION pre OPERATOR|| moze mat aj 0 TEMPLATE PARAMETERS. V takom pripade je RESULT VALUE [false].
		bool													Result=TemplateUnaryFoldExpressionOr();

		wcout << L"RESULT [" << Result << L"] !" << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename... TValues>
void TemplateFoldExpressionsOperatorComma(vector<TType>& Vector, TValues... Values)
{
	// !!!!! Pomocou FOLD EXPRESSION a OPERATOR, sa pridaju ITEMS do VECTOR.
	// !!!!! UNARY FOLD EXPRESSION pre OPERATOR, moze mat aj 0 TEMPLATE PARAMETERS. V takom pripade je RESULT VALUE [void()].
    (Vector.push_back(Values) , ...);
}
//----------------------------------------------------------------------------------------------------------------------
void TestFoldExpressionsOperatorComma(void)
{
	PrintLineSeparator();

	{
		vector<int>												Values;

		TemplateFoldExpressionsOperatorComma(Values,10,20,30);

		if (Values.size()>0)
		{
			for(int Value : Values)
			{
				wcout << L"VALUE [" << Value << L"] !" << endl;
			}
		}
		else
		{
			wcout << L"VECTOR is EMPTY !" << endl;
		}
	}

	PrintLineSeparator();

	{
		vector<int>												Values;

		// !!!!! UNARY FOLD EXPRESSION pre OPERATOR, moze mat aj 0 TEMPLATE PARAMETERS. V takom pripade je RESULT VALUE [void()].
		TemplateFoldExpressionsOperatorComma(Values);

		if (Values.size()>0)
		{
			for(int Value : Values)
			{
				wcout << L"VALUE [" << Value << L"] !" << endl;
			}
		}
		else
		{
			wcout << L"VECTOR is EMPTY !" << endl;
		}
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestFriendTemplateClasses(void)
{
	PrintLineSeparator();

	{
		CFriendClassClassMakingFriends1<CString>				FriendObject(L"Timmy");
		CFriendClassFriendClassNonTemplate1						Object(FriendObject);

		Object.Print();
	}

	PrintLineSeparator();

	{
		CFriendClassClassMakingFriends1<CString>				FriendObject(L"Timmy");
		CFriendClassFriendClassTemplate<CFriendClassClassMakingFriends1<CString>>	Object(FriendObject);

		Object.Print();
	}

	PrintLineSeparator();

	{
		CFriendClassClassMakingFriends1<double>					FriendObject1(123.456);
		CFriendClassClassMakingFriends1<int>					FriendObject2(100);

		// !!! Vola sa TEMPLATE METHOD, ktora ako TEMPLATE PARAMETER pouziva TYPE [int]
		FriendObject1.PrintForDifferentTemplateParameter(FriendObject2);
	}

	PrintLineSeparator();

	{
		// !!!!! CLASS [CFriendClassClassMakingFriends2<CFriendClassFriendClassNonTemplate2>] robi FRIEND z TEMPLATE PARAMETER [CFriendClassFriendClassNonTemplate2].
		CFriendClassClassMakingFriends2<CFriendClassFriendClassNonTemplate2>	FriendObject;
		CFriendClassFriendClassNonTemplate2						Object(FriendObject);

		Object.Print();
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestFriendFunctionsInNonTemplateClasses1(void)
{
	PrintLineSeparator();

	{
		FriendFunctions1(100,123.456);
	}

	PrintLineSeparator();

	{
		FriendFunctions1(true,123.456);
	}

	PrintLineSeparator();

	{
		FriendFunctions1(CString(L"TEXT"),123.456);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestFriendFunctionsInNonTemplateClasses2(void)
{
	PrintLineSeparator();

	{
		FriendFunctions2Function1(100,123.456);
	}

	/*
	PrintLineSeparator();

	{
		// !!!!! COMPILER hodi ERROR, pretoze TEMPLATE FUNCTION [void FriendFunctions2Function1(TType1 Value1, TType2 Value2)] nebola deklarovana ako FRIEND.
		FriendFunctions2Function1(CString(L"TEXT"),100);
	}
	*/

	PrintLineSeparator();

	{
		// !!!!! COMPILER hodi ERROR, pretoze COMPILER vola TEMPLATE FUNCTION [void FriendFunctions2Function2(TType1 Value1, TType2 Value2)] nebola deklarovana ako FRIEND.
		CFriendFunctionsNonTemplateClass2::CallFriendFunctions2Function2(100,123.456);
	}

	/*
	PrintLineSeparator();

	{
		// !!!!! COMPILER hodi ERROR, pretoze COMPILER vola TEMPLATE FUNCTION [void FriendFunctions2Function2(TType1 Value1, TType2 Value2)] nebola deklarovana ako FRIEND.
		// !!!!! COMPILER NEVOLA FUNCTION [void FriendFunctions2Function2(int Value1, double Value2)], lebo je VISIBLE iba v ramci CLASS [CFriendFunctionsNonTemplateClass2].
		FriendFunctions2Function2(100,123.456);
	}
	*/

	/*
	PrintLineSeparator();

	{
		// !!!!! COMPILER hodi ERROR, pretoze TEMPLATE FUNCTION [void FriendFunctions2Function2(TType1 Value1, TType2 Value2)] nebola deklarovana ako FRIEND.
		FriendFunctions2Function2(CString(L"TEXT"),100);
	}
	*/

	PrintLineSeparator();

	{
		FriendFunctions2Function3(100,123.456);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestFriendFunctionsInNonTemplateClasses3(void)
{
	PrintLineSeparator();

	{
		FriendFunctions3Function1(100,123.456);
	}

	PrintLineSeparator();

	{
		FriendFunctions3Function1(true,123.456);
	}

	PrintLineSeparator();

	{
		FriendFunctions3Function2(100,123.456);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestFriendFunctionsInTemplateClasses(void)
{
	PrintLineSeparator();

	{
		CFriendFunctionsTemplateClassMakingFriend<CString>		FriendObject(L"Timmy");
		CFriendFunctionsTemplateClass<CString>					Object;

		Object.Print(FriendObject);
	}

	PrintLineSeparator();

	{
		CFriendFunctionsTemplateClassMakingFriend<CString>		Object(L"Timmy");

		// !!!!! Vola sa FUNCTION, ktore je deklarovana ako FRIEND.
		FriendFunctionNotMethod(Object);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestFriendTemplates(void)
{
	PrintLineSeparator();

	{
		CFriendTemplatesTemplateClass<int>						Object(12);

		Object.Print();
	}

	PrintLineSeparator();

	{
		CFriendTemplatesClassMakingFriend						FriendObject(L"Jenny");
		CFriendTemplatesClass<CString>							Object1(L"Timmy");

		// !!!!! METHOD pristupuje k PRIVATE FIELD CLASS [CFriendTemplatesClassMakingFriend]. Kedze vsak je FRIEND, tak CODE zbehne.
		Object1.Print1(FriendObject);

		// !!!!! METHOD pristupuje k PRIVATE FIELD CLASS [CFriendTemplatesClassMakingFriend]. Kedze vsak je FRIEND, tak CODE zbehne.
		Object1.Print2();

		CFriendTemplatesClass<int>								Object2(100);

		Object2.Print2();
	}

	PrintLineSeparator();

	{
		// !!!!! Vola sa FRIEND TEMPLATE FUNCTION.
		FriendTemplateFunction(100);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestTemplatesOnNamespaceScope();
	//TestTemplatesOnClassScopeInClass();
	//TestTemplatesOnClassScopeOutOfClass();
	//TestTemplateUnion();
	//TestTemplateDefaultParameters();
	//TestNonTemplateMembers();
	//TestVirtualTemplateMembers();
	//TestTemplateLinkage();
	//TestPrimaryVsNonPrimaryTemplates();
	//TestTemplateParameters();
	//TestTemplateTypeParameters();
	//TestNonTypeTemplateParametersTypes();
	//TestTemplateClassNonTypeTemplateParametersAuto();
	//TestTemplateFunctionNonTypeTemplateParametersAuto();
	//TestTemplateFunctionNonTypeTemplateParametersDecltypeAuto();
	//TestTemplateFunctionNonTypeTemplateParametersTypeDecay();
	//TestTemplateTemplateParameters();
	//TestTemplateParameterPackTypes();
	//TestVariadicTemplateTypes();
	//TestMultipleTemplateParameterPacks();
	//TestTemplateDefaultArguments();
	//TestTemplateParametersSubstitutions();
	//TestTemplateFunctionParametersSubstitutions();
	//TestNonTypeTemplateParametersTypesSubstitutions();
	//TestTemplateTemplateParametersTypesSubstitutions();
	//TestTemplateArgumentsEquivalence();
	//TestTemplateMethodsNonEquivalence();
	//TestVariadicTemplates();
	//TestExpansionPack();
	//TestFunctionParameterPack();
	//TestMultipleParameterPacksExpansion();
	//TestNestedParameterPacksExpansion();
	//TestZeroLengthPackExpansion();
	//TestFoldExpressions1();
	//TestFoldExpressions2();
	//TestFoldExpressions3();
	//TestFoldExpressionsUnaryFoldExpressions();
	//TestFoldExpressionsOperatorComma();
	//TestFriendTemplateClasses();
	//TestFriendFunctionsInNonTemplateClasses1();
	//TestFriendFunctionsInNonTemplateClasses2();
	//TestFriendFunctionsInNonTemplateClasses3();
	//TestFriendFunctionsInTemplateClasses();
	TestFriendTemplates();

	ShowExitLine();

	return(0);
}
//----------------------------------------------------------------------------------------------------------------------