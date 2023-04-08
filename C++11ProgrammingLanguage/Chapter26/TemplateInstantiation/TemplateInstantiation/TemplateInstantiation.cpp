//-----------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <stdio.h>
#include <string>
#include <vector>
#include <complex>
#include "MyDebug.h"
#include "CTemplateClass.h"
#include "CAlias.h"
#include "CTemplateMethod.h"
#include "CClassInNamespace.h"
#include "CTemplateDerivationNonDependentBase.h"
#include "CTemplateDerivationNonDependentDerived.h"
#include "CTemplateDerivationDependentBase.h"
#include "CTemplateDerivationDependentDerived.h"
//-----------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------
// EXPLICITNA TEMPLATE INSTANCE. C++ OKAMZITE generuje CODE pre VSETKY METHODS.
template class CTemplateClass<double>;
//-----------------------------------------------------------------------------
// !!!!! Hodi COMPILATION ERROR. Pri EXPLICIT INSTANCE C++ OKAMZITE generuje CODE pre VSETKY METHODS, no kedze TYPE [vector] NEMA OPERATOR++, ktory vyuziva METHOD IncrementValue(), C++ generuje COMPILATION ERROR.
//template class CTemplateClass<vector<int>>;
//-----------------------------------------------------------------------------
// !!! EXTERN TEMPLATES MUSIA mat EXPLICITNU deklaraciu svojej INSTANCE v INOM CPP FILE.
extern template class std::complex<double>;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestImplicitSpecialization(void)
{
	PrintLineSeparator();

	// !!! Pri IMPLICIT TEMPLATE INSTANTIATION C++ generuje CODE IBA TYCH METHODS, ktore sa REALNE v CODE POUZIVAJU.
	// !!!!! Preto je mozne pouzit TEMPLATE CLASS [CTemplateClass] aj pre TYPE [wstring], ktory NEMA OPERATOR++, pretoze METHOD IncrementValue(), ktora OPERATOR++ pouziva sa NEZAVOLALA a tym padom pre nu C++ NEGENERUJE jej CODE.
	CTemplateClass<wstring>										Class1(L"Timmy Anderson");

	wprintf_s(L"VALUE [%ls] !\n",Class1.GetValue().c_str());

	// !!! Hodi COMPILATION ERROR, pretoze TYPE [wstring] NEMA definovany OPERATOR++, ktory FUNCTION IncrementValue() vola.
	//wprintf_s(L"VALUE [%ls] !\n",Class.IncrementValue().c_str());
	
	CTemplateClass<int>											Class2(12);

	wprintf_s(L"VALUE [%d] !\n",Class2.GetValue());

	wprintf_s(L"VALUE [%d] !\n",Class2.IncrementValue());

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestExplicitSpecialization(void)
{
	PrintLineSeparator();

	// !!! TEMPLATE INSTANCE je deklarovana EXPLICITNE VYSSIE v CODE.
	CTemplateClass<double>										Class1(12.4);

	wprintf_s(L"VALUE [%f] !\n",Class1.GetValue());

	// TEMPLATE INSTANCE je [complex<double>] EXTERNE DEKLAROVANA.
	complex<double>												Class2(complex<double>(1.1,2.2));

	wprintf_s(L"VALUE [%f,%f] !\n",Class2.real(),Class2.imag());

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void OverloadedFunction(double)
{
	wprintf_s(L"FUNCTION void OverloadedFunction(double) CALLED !\n");
}
//-----------------------------------------------------------------------------
template<typename TType>
void NonDependentNamesTemplate(void)
{
	// !!! Zavola sa FUNCTION [void OverloadedFunction(double)], pretoze aj ked FUNCTION [void OverloadedFunction(int)] lepsie splna kriteria volania OverloadedFunction(100), kedze NIE JE PRISTUPNA v case TEMPLATE DEFINITION, NEPOUZIJE sa.
	// !!!!! Vo VC++ sa vsak zavola FUNCTION [void OverloadedFunction(int)] namiesto FUNCTION [void OverloadedFunction(double)]. V G++ je to opacne, teda tak ako je to napisane v knihe.
	OverloadedFunction(100);
}
//-----------------------------------------------------------------------------
void OverloadedFunction(int)
{
	wprintf_s(L"FUNCTION void OverloadedFunction(int) CALLED !\n");
}
//-----------------------------------------------------------------------------
void TestNonDependentNames(void)
{
	PrintLineSeparator();

	NonDependentNamesTemplate<int>();

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<typename TType>
// !!! Kedze [CAlias<TType>::TypeValue] reprezentuje TYPE, je NUTNE pouzit KEYWORD [typename].
typename CAlias<TType>::TypeValue KeywordTypenameTemplate(TType Value1, TType Value2)
{
	// !!! Kedze [CAlias<TType>::TypeValue] reprezentuje TYPE, je NUTNE pouzit KEYWORD [typename].
	typename CAlias<TType>::TypeValue							Result=Value1+Value2;

	return(Result);
}
//-----------------------------------------------------------------------------
void TestKeywordTypename(void)
{
	PrintLineSeparator();

	int															Result=KeywordTypenameTemplate(10,20);

	wprintf_s(L"RESULT [%d] !\n",Result);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<typename TType1, typename TType2>
TType2 KeywordTypenameTemplate(TType1 Value)
{
	CTemplateMethod<TType1>										Class(Value);
	TType2														ReturnValue;

	// !!!!! Kedze [Convert<TType2>()] je TEMPLATE METHOD, je NUTNE pouzit KEYWORD [template].
	// !!! VC++ akceptuje CODE aj BEZ KEYWORD [template], ale G++ hodi ERROR.
	ReturnValue=Class.template Convert<TType2>();

	return(ReturnValue);
}
//-----------------------------------------------------------------------------
void TestKeywordTemplate(void)
{
	PrintLineSeparator();

	double														Result=KeywordTypenameTemplate<int,double>(6);

	wprintf_s(L"RESULT [%f] !\n",Result);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void PointOfInstantiationFunction(int Value);
//-----------------------------------------------------------------------------
template<typename TType>
void PointOfInstantiationTemplate(TType Value)
{
	PointOfInstantiationFunction(Value-1);
}
//-----------------------------------------------------------------------------
void PointOfInstantiationFunction(int Value)
{
	wprintf_s(L"VALUE [%d] !\n",Value);

	if (Value>0)
	{
		// !!! Tu sa vykonava TEMPLATE INSTANTINATION.
		PointOfInstantiationTemplate<int>(Value);
	}
}
//-----------------------------------------------------------------------------
// !!!!! C++ az na TOTO miesto prida DECLARATION FUNCTION [void PointOfInstantiationTemplate(int Value)].
//-----------------------------------------------------------------------------
void TestPointOfInstantiation(void)
{
	PrintLineSeparator();

	PointOfInstantiationFunction(3);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<typename TType>
void TemplatesInNamespaceTemplate(TType Value)
{
	// !!! Zavola sa FUNCTION PrintClassInNamespace() z NAMESPACE [SomeNamespace], pretoze ak [TType] je CLASS [CClassInNamespace], ktory je definovany v tom istom NAMESPACE, C++ teda vykonava RESOLVING aj v tomto NAMESPACE.
	PrintClassInNamespace(Value);
}
//-----------------------------------------------------------------------------
void TestTemplatesInNamespace(void)
{
	PrintLineSeparator();

	SomeNamespace::CClassInNamespace							Class(L"Timmy Anderson");

	TemplatesInNamespaceTemplate(Class);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestTemplatesBaseClasses(void)
{
	PrintLineSeparator();

	CTemplateDerivationNonDependentDerived<int>					Class1;

	Class1.Test();

	PrintLineSeparator();

	CTemplateDerivationDependentDerived<int>					Class2;

	Class2.Test();

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestImplicitSpecialization();
	//TestExplicitSpecialization();
	//TestNonDependentNames();
	//TestKeywordTypename();
	//TestKeywordTemplate();
	//TestPointOfInstantiation();
	//TestTemplatesInNamespace();
	TestTemplatesBaseClasses();

	ShowExitLine();

	return(0);
}
//-----------------------------------------------------------------------------