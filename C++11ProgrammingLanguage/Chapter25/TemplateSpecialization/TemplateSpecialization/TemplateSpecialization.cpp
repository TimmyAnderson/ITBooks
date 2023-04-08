//-------------------------------------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <string>
#include <vector>
#include "MyDebug.h"
#include "CClassWithTypes.h"
#include "CSimpleTemplate.h"
#include "CBufferTemplate.h"
#include "CClassWithMembers.h"
#include "CSimpleFunctor.h"
#include "CPair.h"
#include "CDefaultParameters.h"
#include "CSpecializations.h"
#include "CSpecializationWithAssert.h"
#include "CMethodSpecializations.h"
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
wstring															GlobalValue=L"Timmy Anderson";
//-------------------------------------------------------------------------------------------------------
template<typename TType>
TType SimpleTemplateFunction(TType Value)
{
	return(Value*Value);
}
//-------------------------------------------------------------------------------------------------------
template<typename TFunctor, typename TParameter>
void CallFunctor(TFunctor Functor, TParameter Parameter)
{
	Functor(Parameter);
}
//-------------------------------------------------------------------------------------------------------
void FunctionFunctor(wstring Parameter)
{
	wprintf_s(L"FUNCTION FUNCTOR CALLED with PARAMETER [%ls] !\n",Parameter.c_str());
}
//-------------------------------------------------------------------------------------------------------
void TestTypeParameters(void)
{
	PrintLineSeparator();

	wprintf_s(L"SimpleTemplateFunction(10) [%d] !\n",SimpleTemplateFunction(10));

	printf_s("TYPE 1 [%s] !\n",typeid(CSimpleTemplate<int>).name());
	printf_s("TYPE 2 [%s] !\n",typeid(CSimpleTemplate<vector<int>>).name());
	printf_s("TYPE 3 [%s] !\n",typeid(CSimpleTemplate<CClassWithTypes::CPublicSubClass>).name());

	// !!! COMPILER hodi ERROR, lebo TYPE [CClassWithTypes::CPrivateSubClass] NIE JE ACCESSIBLE.
	//printf_s("TYPE 4 [%s] !\n",typeid(CSimpleTemplate<CClassWithTypes::CPrivateSubClass>).name());

	PrintLineSeparator();

	CSimpleFunctor												Functor;

	CallFunctor(Functor,wstring(L"Timmy Anderson"));

	auto														LambdaAsFunctor=[](wstring Parameter){wprintf_s(L"LAMBDA FUNCTOR CALLED with PARAMETER [%ls] !\n",Parameter.c_str());};

	// !!! LAMBDA EXPRESSION je mozne konvertovat na FUNCTOR.
	CallFunctor(LambdaAsFunctor,wstring(L"Timmy Anderson"));

	CallFunctor([](wstring Parameter){wprintf_s(L"INLINE LAMBDA FUNCTOR CALLED with PARAMETER [%ls] !\n",Parameter.c_str());},wstring(L"Timmy Anderson"));

	// !!! POINTER na FUNCTION je mozne konvertovat na FUNCTOR.
	CallFunctor(FunctionFunctor,wstring(L"Timmy Anderson"));

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
template<int BUFFER_SIZE>
void PrintBuffer(int Buffer[BUFFER_SIZE])
{
	for(int Index=0;Index<BUFFER_SIZE;Index++)
	{
		wprintf_s(L"BUFFER[%d]: [%d] !\n",Index,Buffer[Index]);
	}
}
//-------------------------------------------------------------------------------------------------------
void TestValueParameters1(void)
{
	PrintLineSeparator();

	const int													BUFFER_SIZE=3;
	CBufferTemplate<int,BUFFER_SIZE>							Buffer;
	int															InputBuffer[BUFFER_SIZE]{11,12,13};
	int															OutputBuffer[BUFFER_SIZE];

	Buffer.SetBuffer(InputBuffer);

	Buffer.GetBuffer(OutputBuffer);

	PrintBuffer<BUFFER_SIZE>(OutputBuffer);

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!! TEMPLATE obsahuje ako VALUE PARAMETER POINTER na OBJECT. OBJECT pri TEMPLATE INSTANCING MUSI byt GLOBAL OBJECT.
template<wstring* Text>
void PointerToObjectTemplate(void)
{
	wprintf_s(L"TEMPLATE VALUE PARAMETER [%ls] !\n",Text->c_str());
}
//-------------------------------------------------------------------------------------------------------
// !!! TEMPLATE obsahuje ako VALUE PARAMETER POINTER na FUNCTION.
template<void (*Function)(void)>
void PointerToFunctionTemplate(void)
{
	Function();
}
//-------------------------------------------------------------------------------------------------------
void PrintSomething(void)
{
	wprintf_s(L"My name is TIMMY ANDERSON !\n");
}
//-------------------------------------------------------------------------------------------------------
void TestValueParameters2(void)
{
	PrintLineSeparator();

	// !!! LOCAL VARIABLES NIE JE mozne pouzit. Pouzit je mozne IBA GLOBAL VARIABLES.
	PointerToObjectTemplate<&GlobalValue>();

	PrintLineSeparator();

	PointerToFunctionTemplate<PrintSomething>();

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!! TEMPLATE ma ako PARAMETER POINTER na MEMBER VARIABLE.
template<int CClassWithMembers::*SomeIntMemberVariable>
void PrintMemberVariable(CClassWithMembers Object)
{
	wprintf_s(L"Object->SomeIntVariable: [%d] !\n",Object.*SomeIntMemberVariable);
}
//-------------------------------------------------------------------------------------------------------
// !!! TEMPLATE ma ako PARAMETER POINTER na MEMBER METHOD.
template<void (CClassWithMembers::*SomeMemberFunction)(const wchar_t*)>
void CallMemberFunction(CClassWithMembers Object, const wchar_t* Prefix)
{
	(Object.*SomeMemberFunction)(Prefix);
}
//-------------------------------------------------------------------------------------------------------
void TestValueParameters3(void)
{
	PrintLineSeparator();

	CClassWithMembers											Value1{100};
	CClassWithMembers											Value2{200};

	PrintMemberVariable<&CClassWithMembers::MValue>(Value1);
	PrintMemberVariable<&CClassWithMembers::MValue>(Value2);

	PrintLineSeparator();

	const wchar_t*												Parameter1=wstring(L"Object1").c_str();
	const wchar_t*												Parameter2=wstring(L"Object2").c_str();

	CallMemberFunction<&CClassWithMembers::PrintValue>(Value1,Parameter1);
	CallMemberFunction<&CClassWithMembers::PrintValue>(Value2,Parameter2);

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!! 3. TYPE PARAMETER je TEMPLATE s 2 TYPE PARAMETERS.
template<typename TType1, typename TType2, template<typename,typename> class TTemplateParameter>
void TemplateWithTemplateParameter(TType1 Value1, TType2 Value2)
{
	TTemplateParameter<TType1,TType2>							TemplateParameter{Value1,Value2};
	TType1														PairValue1=TemplateParameter.GetValue1();
	TType2														PairValue2=TemplateParameter.GetValue2();

	// Len pre testovacie ucely FUNCTION wprintf_s() predpoklada, ze [TType1] je [wstring] a [TType2] je [int].
	wprintf_s(L"FUNCTION with TEMPLATE PARAMETER CALLED [%ls %d] !\n",PairValue1.c_str(),PairValue2);
}
//-------------------------------------------------------------------------------------------------------
void TestTemplateParameters(void)
{
	PrintLineSeparator();

	// !!! Meno TEMPLATE [CPair] sa uz zadava BEZ TYPE PARAMETERS.
	TemplateWithTemplateParameter<wstring,int,CPair>(wstring(L"Timmy Anderson"),12);

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
template<typename TResult=int, typename TParameter1=int, typename TParameter2=int>
TResult Add(TParameter1 Parameter1, TParameter2 Parameter2)
{
	TResult														Result=(TResult) (Parameter1+Parameter2);

	return(Result);
}
//-------------------------------------------------------------------------------------------------------
void TestDefaultParameters(void)
{
	PrintLineSeparator();

	// Nepouzivaju sa DEFAULT PARAMETERS.
	CDefaultParameters<wstring,int>								Class1(L"Timmy Anderson",12);

	wprintf_s(L"Class1<wstring,int> [%ls %d] !\n",Class1.GetValue1().c_str(),Class1.GetValue2());

	// Pouziva sa 2. DEFAULT PARAMETER.
	CDefaultParameters<wstring>									Class2(L"Timmy Anderson",12);

	wprintf_s(L"Class2<wstring> [%ls %d] !\n",Class2.GetValue1().c_str(),Class2.GetValue2());

	// Pouzivaju sa obe DEFAULT PARAMETERS.
	CDefaultParameters<>										Class3(L"Timmy Anderson",12);

	wprintf_s(L"Class3<> [%ls %d] !\n",Class3.GetValue1().c_str(),Class3.GetValue2());

	/*
	// !!! Pouzivaju sa obe DEFAULT PARAMETERS. Pri CLASS TEMPLATES su znaky [<>] NUTNE.
	CDefaultParameters											Class4(L"Timmy Anderson",12);

	wprintf_s(L"Class4 [%ls %d] !\n",Class4.GetValue1().c_str(),Class4.GetValue2());
	*/

	PrintLineSeparator();

	// Nepouzivaju sa DEFAULT PARAMETERS.
	wprintf_s(L"Add<int,int,int>(10,5) [%d] !\n",Add<int,int,int>(10,5));

	// Pouziva sa 3. DEFAULT PARAMETER.
	wprintf_s(L"Add<int,int>(10,5) [%d] !\n",Add<int,int>(10,5));

	// Pouzivaju sa 2. a 3. DEFAULT PARAMETER.
	wprintf_s(L"Add<int>(10,5) [%d] !\n",Add<int>(10,5));

	// Pouzivaju sa vsetky DEFAULT PARAMETERS.
	wprintf_s(L"Add<>(10,5) [%d] !\n",Add<>(10,5));

	// Ked sa pouziva vsetky DEFAULT PARAMETERS, je mozne vyhodit znaky [<>].
	wprintf_s(L"Add(10,5) [%d] !\n",Add(10,5));

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void TestClassSpecialization(void)
{
	PrintLineSeparator();

	// !!! Vola sa PRIMARY TEMPLATE.
	CSpecializations<int>										Class1;

	Class1.Print();

	CSpecializations<int*>										Class2;

	Class2.Print();

	CSpecializations<int&>										Class3;

	Class3.Print();

	CSpecializations<wstring>									Class4;

	Class4.Print();

	PrintLineSeparator();

	// !!! Vola sa SPECIALIZATION pre POINTERS.
	CSpecializations<wstring*>									Class5;

	Class5.Print();

	PrintLineSeparator();

	// !!! Vola sa SPECIALIZATION pre REFERENCES.
	CSpecializations<wstring&>									Class6;

	Class6.Print();

	PrintLineSeparator();

	// !!! Vola sa SPECIALIZATION pre REFERENCES.
	CSpecializations<const int&>								Class7;

	Class7.Print();

	PrintLineSeparator();

	// !!! Vola sa SPECIALIZATION pre POINTERS.
	CSpecializations<void*>										Class8;

	Class8.Print();

	PrintLineSeparator();

	// !!! Vola sa PRIMARY TEMPLATE.
	CSpecializationWithAssert<CClassWithMembers>				Class9;

	Class9.Print();

	PrintLineSeparator();

	// !!! Vola sa SPECIALIZATION pre POINTERS.
	CSpecializationWithAssert<CClassWithMembers*>				Class10;

	Class10.Print();

	/*
	PrintLineSeparator();

	// !!! STATIC ASSERT hodi COMPILATION ERROR.
	CSpecializationWithAssert<int>								Class11;

	Class11.Print();

	PrintLineSeparator();

	// !!! STATIC ASSERT hodi COMPILATION ERROR.
	CSpecializationWithAssert<int*>								Class12;

	Class12.Print();
	*/

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// PRIMARY TEMPLATE.
template<typename TType>
TType TemplateFunction(TType Value)
{
	wprintf_s(L"TEMPLATE FUNCTION [template<typename TType> TType TemplateFunction(TType Value)] CALLED !\n");

	return(Value);
}
//-------------------------------------------------------------------------------------------------------
// TEMPLATE SPECIALIZATION.
template<>
wstring TemplateFunction<wstring>(wstring Value)
{
	wprintf_s(L"TEMPLATE SPECIALIZATION [template<> wstring TemplateFunction<wstring>(wstring Value)] CALLED !\n");

	return(Value);
}
//-------------------------------------------------------------------------------------------------------
// TEMPLATE SPECIALIZATION.
// !!! SYNTAX [<int>] je mozne odstranit.
template<>
int TemplateFunction(int Value)
{
	wprintf_s(L"TEMPLATE SPECIALIZATION [template<> int TemplateFunction(int Value)] CALLED !\n");

	return(Value);
}
//-------------------------------------------------------------------------------------------------------
// !!! OVERLOADED FUNCTION. Toto NIE JE TEMPLATE SPECIALIZATION, pretoze CHYBA PREFIX [template<>].
double TemplateFunction(double Value)
{
	wprintf_s(L"OVERLOADED FUNCTION [double TemplateFunction(double Value)] CALLED !\n");

	return(Value);
}
//-------------------------------------------------------------------------------------------------------
// PRIMARY TEMPLATE.
template<typename TType>
TType OverloadedVSSpecialization(TType Value)
{
	wprintf_s(L"TEMPLATE FUNCTION [template<typename TType> TType OverloadedVSSpecialization(TType Value)] CALLED !\n");

	return(Value);
}
//-------------------------------------------------------------------------------------------------------
// TEMPLATE SPECIALIZATION.
template<>
int OverloadedVSSpecialization(int Value)
{
	wprintf_s(L"TEMPLATE SPECIALIZATION [template<> int OverloadedVSSpecialization(int Value)] CALLED !\n");

	return(Value);
}
//-------------------------------------------------------------------------------------------------------
// !!! OVERLOADED FUNCTION. Toto NIE JE TEMPLATE SPECIALIZATION, pretoze CHYBA PREFIX [template<>].
int OverloadedVSSpecialization(int Value)
{
	wprintf_s(L"OVERLOADED FUNCTION [int OverloadedVSSpecialization(int Value)] CALLED !\n");

	return(Value);
}
//-------------------------------------------------------------------------------------------------------
void TestFunctionSpecialization(void)
{
	PrintLineSeparator();

	// Vola sa TEMPLATE FUNCTION, pretoze TEMPLATE SPECIALIZATION pre CHAR* nebola definovana.
	TemplateFunction("Timmy Anderson");

	PrintLineSeparator();

	// Vola sa TEMPLATE SPECIALIZATION.
	TemplateFunction(wstring(L"Timmy Anderson"));

	PrintLineSeparator();

	// Vola sa TEMPLATE SPECIALIZATION.
	TemplateFunction(12);

	PrintLineSeparator();

	// Vola sa OVERLOADED FUNCTION.
	TemplateFunction(12.0);

	PrintLineSeparator();

	// Vola sa TEMPLATE FUNCTION, pretoze TEMPLATE SPECIALIZATION pre CHAR* nebola definovana.
	OverloadedVSSpecialization("Timmy Anderson");

	PrintLineSeparator();

	// Vola sa TEMPLATE SPECIALIZATION.
	OverloadedVSSpecialization<int>(12);

	PrintLineSeparator();

	// Vola sa TEMPLATE SPECIALIZATION.
	OverloadedVSSpecialization<>(12);

	PrintLineSeparator();

	// Vola sa OVERLOADED FUNCTION.
	OverloadedVSSpecialization(12);

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void TestMethodSpecialization(void)
{
	PrintLineSeparator();

	CMethodSpecializations										Class;

	// Vola sa TEMPLATE METHOD, pretoze TEMPLATE SPECIALIZATION pre CHAR* nebola definovana.
	Class.TemplateMethod("Timmy Anderson");

	PrintLineSeparator();

	// Vola sa TEMPLATE SPECIALIZATION.
	Class.TemplateMethod(wstring(L"Timmy Anderson"));

	PrintLineSeparator();

	// Vola sa TEMPLATE SPECIALIZATION.
	Class.TemplateMethod(12);

	PrintLineSeparator();

	// Vola sa OVERLOADED METHOD.
	Class.TemplateMethod(12.0);

	PrintLineSeparator();

	// Vola sa TEMPLATE METHOD, pretoze TEMPLATE SPECIALIZATION pre CHAR* nebola definovana.
	Class.OverloadedVSSpecialization("Timmy Anderson");

	PrintLineSeparator();

	// Vola sa TEMPLATE SPECIALIZATION.
	Class.OverloadedVSSpecialization<int>(12);

	PrintLineSeparator();

	// Vola sa TEMPLATE SPECIALIZATION.
	Class.OverloadedVSSpecialization<>(12);

	PrintLineSeparator();

	// Vola sa OVERLOADED METHOD.
	Class.OverloadedVSSpecialization(12);

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestTypeParameters();
	//TestValueParameters1();
	//TestValueParameters2();
	//TestValueParameters3();
	//TestTemplateParameters();
	//TestDefaultParameters();
	//TestClassSpecialization();
	//TestFunctionSpecialization();
	TestMethodSpecialization();

	ShowExitLine();

	return(0);
}
//-------------------------------------------------------------------------------------------------------