//-------------------------------------------------------------------------------------------------------
#include "stdafx.h"
#include <conio.h>
#include <string>
#include <vector>
#include "SimpleTemplate.h"
// !!!!! Musim vlozit i CPP, aby LINKER zahrnul i IMPLEMENTACIE TEMPLATE METOD.
#include "SimpleTemplate.cpp"
#include "BufferTemplate.h"
// !!!!! Musim vlozit i CPP, aby LINKER zahrnul i IMPLEMENTACIE TEMPLATE METOD.
#include "BufferTemplate.cpp"
#include "SimpleTemplateWithInt.h"
// !!!!! Musim vlozit i CPP, aby LINKER zahrnul i IMPLEMENTACIE TEMPLATE METOD.
#include "SimpleTemplateWithInt.cpp"
#include "Comparer.h"
#include "SimpleTemplateWithDefault.h"
// !!!!! Musim vlozit i CPP, aby LINKER zahrnul i IMPLEMENTACIE TEMPLATE METOD.
#include "SimpleTemplateWithDefault.cpp"
#include "Store.h"
#include "StorePointer.h"
#include "StoreVoidPointer.h"
#include "StoreDouble.h"
#include "ArrayTemplate.h"
#include "Base.h"
#include "Derived.h"
#include "VirtualTemplateDerived.h"
#include "Operators.h"
// !!!!! Musim vlozit i CPP, aby LINKER zahrnul i IMPLEMENTACIE TEMPLATE METOD.
#include "Operators.cpp"
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
wstring															DEFAULT_VALUE=L"EMPTY";
//-------------------------------------------------------------------------------------------------------
void PrintFunction(const wstring& Param)
{
	wprintf_s(L"Value: [%s] !\n",Param.c_str());
}
//-------------------------------------------------------------------------------------------------------
template <typename TType>
void Swap(TType& Param1, TType& Param2)
{
	wprintf_s(L"TEMPLATE FUNCTION is CALLED !\n");

	// !!! TEMPLATE predpoklada, ze CLASS ma pretazeny OPERATOR= a robi DEEP COPY.
	TType														Temp=Param1;

	Param1=Param2;
	Param2=Temp;
}
//-------------------------------------------------------------------------------------------------------
// !!!!! Pretazene SWAP pre DOUBLE hodnoty.
void Swap(double& Param1, double& Param2)
{
	wprintf_s(L"CLASSIC FUNCTION is CALLED !\n");

	double														Temp=Param1;

	Param1=Param2;
	Param2=Temp;
}
//-------------------------------------------------------------------------------------------------------
// !!! Trieda TComparer MUSI obsahovat STATICKU metodu Compare().
template <typename TType, typename TComparer>
void PrintCompareResult(TType& Param1, TType& Param2)
{
	int															Result=TComparer::Compare(Param1,Param2);

	if (Result==0)
	{
		wprintf_s(L"VALUES are SAME !\n");
	}
	else if (Result>0)
	{
		wprintf_s(L"VALUE1 is BIGGER than VALUE2 !\n");
	}
	else
	{
		wprintf_s(L"VALUE1 is SMALLER than VALUE2 !\n");
	}
}
//-------------------------------------------------------------------------------------------------------
/*
// !!!!! Toto Visual C++ NESKOMPILUJE (aj ked je to v sulade s C++ standardom), lebo DEFAULT PARAMETRE je mozne vo Visual C++ pouzivat IBA pre CLASS TEMPLATES.
template <typename TType, typename TComparer=CCompare>
void PrintCompareResultWithDefault(TType& Param1, TType& Param2)
{
	int															Result=TComparer::Compare(Param1,Param2);

	if (Result==0)
	{
		wprintf_s(L"VALUES are SAME !\n");
	}
	else if (Result>0)
	{
		wprintf_s(L"VALUE1 is BIGGER than VALUE2 !\n");
	}
	else
	{
		wprintf_s(L"VALUE1 is SMALLER than VALUE2 !\n");
	}
}
*/
//-------------------------------------------------------------------------------------------------------
template<class TType>
TType Bigger(TType Value1, TType Value2)
{
	wprintf_s(L"TType Bigger(TType Value1, TType Value2) CALLED !\n");

	if (Value1>Value2)
	{
		return(Value1);
	}
	else
	{
		return(Value2);
	}
}
//-------------------------------------------------------------------------------------------------------
// !!! Toto je SPECIALIZED verzia TEMPLATE FUNCTION.
template<>
const wchar_t* Bigger(const wchar_t* Value1, const wchar_t* Value2)
{
	wprintf_s(L"const wchar_t* Bigger(const wchar_t* Value1, const wchar_t* Value2) CALLED !\n");

	if (wcscmp(Value1,Value2)>0)
	{
		return(Value1);
	}
	else
	{
		return(Value2);
	}
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void Test1(void)
{
	CSimpleTemplate<int>										SimpleVariable(10);

	int															Value=SimpleVariable.GetVariable();

	wprintf_s(L"Value: [%d] !\n",Value);
}
//-------------------------------------------------------------------------------------------------------
void Test2(void)
{
	CSimpleTemplate<wstring>									SimpleVariable(L"Timmy Anderson");

	wstring														Value=SimpleVariable.GetVariable();

	wprintf_s(L"Value: [%s] !\n",Value.c_str());
}
//-------------------------------------------------------------------------------------------------------
void Test3(void)
{
	int															Value1=10;
	int															Value2=4;

	wprintf_s(L"Value1: [%d], Value2: [%d] !\n",Value1,Value2);

	Swap(Value1,Value2);

	wprintf_s(L"Value1: [%d], Value2: [%d] !\n",Value1,Value2);
}
//-------------------------------------------------------------------------------------------------------
void Test4(void)
{
	wstring														Value1=L"Timmy";
	wstring														Value2=L"Jenny";

	wprintf_s(L"Value1: [%s], Value2: [%s] !\n",Value1.c_str(),Value2.c_str());

	Swap(Value1,Value2);

	wprintf_s(L"Value1: [%s], Value2: [%s] !\n",Value1.c_str(),Value2.c_str());
}
//-------------------------------------------------------------------------------------------------------
void Test5(void)
{
	// !!! TYPEDEF sa da s vyhodou pouzit na SKRATENIE mena TEMPLATE CLASS.
	typedef CSimpleTemplate<wstring>							CStringSimpleTemplate;
	
	CStringSimpleTemplate										SimpleVariable(L"Timmy Anderson");

	wstring														Value=SimpleVariable.GetVariable();

	wprintf_s(L"Value: [%s] !\n",Value.c_str());
}
//-------------------------------------------------------------------------------------------------------
void Test6(void)
{
	// TEMPLATE pouziva i TEMPALTE PARAMETRE a INT PARAMETRE.
	// !!!!! CLASS PARAMETRE ako TEMPLATE PARAMETRE C++ NEAKCEPTUJE.
	//CBufferTemplate<wstring,DEFAULT_VALUE,3>					Buffer;

	// !!!!! Alternativou je pouzitie POINTERS.
	CBufferTemplate<wstring*,&DEFAULT_VALUE,3>					Buffer;

	wstring														Name1=L"Timmy";
	wstring														Name2=L"Atreyu";
	wstring														Name3=L"Jenny";

	Buffer.SetValue(0,&Name1);
	Buffer.SetValue(1,&Name2);
	Buffer.SetValue(2,&Name3);

	wprintf_s(L"Name1: [%s] !\n",Buffer.GetValue(0)->c_str());
	wprintf_s(L"Name2: [%s] !\n",Buffer.GetValue(1)->c_str());
	wprintf_s(L"Name3: [%s] !\n",Buffer.GetValue(2)->c_str());
}
//-------------------------------------------------------------------------------------------------------
void Test7(void)
{
	CSimpleTemplateWithInt<wstring,99>							SimpleVariableWithInt1(L"Timmy Anderson");
	// !!! Su to IDENTICKE TYPY.
	CSimpleTemplateWithInt<wstring,100-1>						SimpleVariableWithInt2(L"Jenny Thompson");

	wstring														Value1=SimpleVariableWithInt1.GetVariable();
	wstring														Value2=SimpleVariableWithInt2.GetVariable();

	wprintf_s(L"Value: [%s] !\n",Value1.c_str());
	wprintf_s(L"Value: [%s] !\n",Value2.c_str());

	// !!! Dokaz, ze typy su IDENTICKE - pretoze ich mozem priradzovat.
	SimpleVariableWithInt2=SimpleVariableWithInt1;

	wstring														Value3=SimpleVariableWithInt1.GetVariable();
	wstring														Value4=SimpleVariableWithInt2.GetVariable();

	wprintf_s(L"Value: [%s] !\n",Value3.c_str());
	wprintf_s(L"Value: [%s] !\n",Value4.c_str());

	SimpleVariableWithInt1.PrintINTParameter();
	SimpleVariableWithInt2.PrintINTParameter();
}
//-------------------------------------------------------------------------------------------------------
void Test8(void)
{
	int															Value1=10;
	int															Value2=4;

	wprintf_s(L"Value1: [%d], Value2: [%d] !\n",Value1,Value2);

	// !!! IMPLICITNE DEDUKOVANE TEMPLATE PARAMETRE.
	Swap(Value1,Value2);

	wprintf_s(L"Value1: [%d], Value2: [%d] !\n",Value1,Value2);

	// !!! EXPLICITNE definovane TEMPLATE PARAMETRE.
	Swap<int>(Value1,Value2);

	wprintf_s(L"Value1: [%d], Value2: [%d] !\n",Value1,Value2);
}
//-------------------------------------------------------------------------------------------------------
void Test9(void)
{
	int															Value1=10;
	int															Value2=4;

	wprintf_s(L"Value1: [%d], Value2: [%d] !\n",Value1,Value2);

	// Kedze parametre su typu INT vola sa TEMPLATE FUNCTION.
	Swap(Value1,Value2);

	wprintf_s(L"Value1: [%d], Value2: [%d] !\n",Value1,Value2);

	double														DValue1=10.0;
	double														DValue2=4.0;

	wprintf_s(L"DValue1: [%f], DValue2: [%f] !\n",DValue1,DValue2);

	// !!! Kedze parametre su typu DOUBLE, C++ preferuje KLASICKU FUNCTION pred TEMPLATE FUNCTION.
	Swap(DValue1,DValue2);

	wprintf_s(L"DValue1: [%f], DValue2: [%f] !\n",DValue1,DValue2);
}
//-------------------------------------------------------------------------------------------------------
void Test10(void)
{
	int															Value1=3;
	int															Value2=6;

	PrintCompareResult<int,CComparer>(Value1,Value2);

	// !!!!! Toto C++ NESKOMPILUJE, lebo DEFAULT PARAMETRE je mozne pouzivat IBA pre CLASS TEMPLATES.
	//PrintCompareResultWithDefault<int>(Value1,Value2);
}
//-------------------------------------------------------------------------------------------------------
void Test11(void)
{
	CSimpleTemplateWithDefault<wstring>							SimpleVariable1(L"Timmy Anderson");

	wstring														Value1=SimpleVariable1.GetVariable();

	wprintf_s(L"Value: [%s] !\n",Value1.c_str());

	// !!! Pouzije sa DEFAULT PARAMETER, ktory je typu DOUBLE.
	CSimpleTemplateWithDefault<>								SimpleVariable2(3.2);

	double														Value2=SimpleVariable2.GetVariable();

	wprintf_s(L"Value: [%f] !\n",Value2);
}
//-------------------------------------------------------------------------------------------------------
void Test12(void)
{
	CStore<int>													Value1(10);

	// !!! Pouzije sa TEMPLATE VERZIA.
	int															OutValue1=Value1.GetValue();

	wprintf_s(L"OutValue1: [%d] !\n",OutValue1);

	int															Temp1=20;

	CStore<int*>												Value2(&Temp1);

	// !!! Pouzije sa SPECIALIZED VERZIA pre POINTER.
	int*														OutValue2=Value2.GetValue();

	wprintf_s(L"OutValue2: [%d] !\n",*OutValue2);

	int															Temp2=30;

	CStore<void*>												Value3((void*) &Temp2);

	// !!! Pouzije sa SPECIALIZED VERZIA pre VOID*.
	void*														OutValue3=Value3.GetValue();

	wprintf_s(L"OutValue3: [%d] !\n",*((int*) OutValue3));

	CStore<double>												Value4(40.0);

	// !!! Pouzije sa SPECIALIZED VERZIA pre DOUBLE.
	double														OutValue4=Value4.GetValue();

	wprintf_s(L"OutValue4: [%f] !\n",OutValue4);
}
//-------------------------------------------------------------------------------------------------------
void Test13(void)
{
	// !!! Pouzije sa TEMPLATE FUNCTION.
	int															Result1=Bigger(10,4);

	wprintf_s(L"Result1: [%d] !\n",Result1);

	// !!! Pouzije sa SPECIALIZED TEMPLATE FUNCTION.
	const wchar_t*												Result2=Bigger(L"Jenny",L"Timmy");

	wprintf_s(L"Result2: [%s] !\n",Result2);
}
//-------------------------------------------------------------------------------------------------------
void Test14(void)
{
	CArrayTemplate<wstring>										Array(3);

	Array.SetValue(0,L"Timmy");
	Array.SetValue(1,L"Atreyu");
	Array.SetValue(2,L"Jenny");

	Array.ExecuteAllItems(&PrintFunction);
}
//-------------------------------------------------------------------------------------------------------
void Test15(void)
{
	CDerived													Derived(6);
	
	wprintf_s(L"Derived.GetValue(): [%d] !\n",Derived.GetValue());

	// Do CBase* je mozne priradit CDerived*.
	CBase*														Base=&Derived;

	wprintf_s(L"Base->GetValue(): [%d] !\n",Base->GetValue());

	vector<CDerived*>											DerivedVetor;
	CDerived													Value1(1);
	CDerived													Value2(2);
	CDerived													Value3(3);

	DerivedVetor.push_back(&Value1);
	DerivedVetor.push_back(&Value2);
	DerivedVetor.push_back(&Value3);

	wprintf_s(L"DerivedVetor.size(): [%d] !\n",DerivedVetor.size());

	/*
	// !!! Do vector<CBase*> NIE JE mozne priradit vector<CDerived*>.
	vector<CBase*>												BaseVector=&DerivedVetor;

	wprintf_s(L"BaseVector.size(): [%d] !\n",BaseVector.size());
	*/
}
//-------------------------------------------------------------------------------------------------------
void Test16(void)
{
	CVirtualTemplateDerived<int>								Derived;

	Derived.DummyNonVirtualFunction(1);

	Derived.DummyVirtualFunction(2);

	Derived.DummyAbstractFunction(3);

	Derived.DummyNonVirtualTemplateFunction<double>(4.4);
}
//-------------------------------------------------------------------------------------------------------
void Test17(void)
{
	COperators<int>												IntOperators(4);
	COperators<double>											DoubleOperators(6);

	wprintf_s(L"IntOperators: [%d] !\n",IntOperators.GetValue());
	wprintf_s(L"DoubleOperators: [%f] !\n",DoubleOperators.GetValue());

	// !!! Pouzije sa KONVERZNY OPERATOR.
	DoubleOperators=(COperators<double>) IntOperators;

	wprintf_s(L"DoubleOperators: [%f] !\n",DoubleOperators.GetValue());
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	//Test1();
	//Test2();
	//Test3();
	//Test4();
	//Test5();
	//Test6();
	//Test7();
	//Test8();
	//Test9();
	//Test10();
	//Test11();
	//Test12();
	//Test13();
	//Test14();
	//Test15();
	//Test16();
	Test17();

	wprintf_s(L"Press any key to EXIT !\n");
	_getch();

	return(0);
}
//-------------------------------------------------------------------------------------------------------