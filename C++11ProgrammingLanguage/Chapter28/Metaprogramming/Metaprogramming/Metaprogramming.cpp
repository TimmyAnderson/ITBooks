//-----------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <stdio.h>
#include <string>
#include <vector>
#include <utility>
#include <tuple>
#include "MyDebug.h"
#include "CNonPolymorphicType.h"
#include "CPolymorphicType.h"
#include "EEnum1.h"
#include "EEnum2.h"
#include "CArrayTypeFunction.h"
#include "CBiggerTypeTypeFunction.h"
#include "CSelect.h"
#include "HasOperators.h"
#include "CHasOperators.h"
#include "CIsIntegralFunctor.h"
#include "CMyTypeTraits.h"
#include "CMyTypeWithTraits1.h"
#include "CMyTypeWithTraits2.h"
#include "CConditional.h"
#include "CSelectVariadic.h"
#include "CTemplateClassRecursion.h"
#include "CStandardEnableIf.h"
#include "CEnableIf.h"
#include "CCustomEnableIf.h"
#include "CTypeWithMethodXXX.h"
#include "HasMethodXXX1.h"
#include "HasMethodXXX2.h"
#include "HasMethodXXX3.h"
#include "SHasFunctionXXX.h"
#include "STuple.h"
#include "CVariadicTemplateMethods.h"
#include "CSimpleVariadicClassTemplate.h"
#include "CComplexVariadicClassTemplate.h"
#include "Printf.h"
#include "CClass1.h"
#include "CClass2.h"
#include "CDerivedVariadicTemplate.h"
#include "CName.h"
#include "CTuple.h"
#include "CString.h"
#include "CVariadicTemplate.h"
#include "CException.h"
#include "CClassWithCustomOperators.h"
#include "CHasFieldXXX.h"
#include "SStructureWithFieldXXX.h"
#include "SStructureWithoutFieldXXX.h"
//-----------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------
// TYPE ALIAS.
template<typename TType1,typename TType2>
using IsBigger=typename CBiggerTypeTypeFunction<int,int>::BiggerType;
//-----------------------------------------------------------------------------
// TYPE ALIAS.
template<typename TType>
using IsBiggerAsInt=typename CBiggerTypeTypeFunction<int,TType>::BiggerType;
//-----------------------------------------------------------------------------
void TestStandardTypeFunctions(void)
{
	PrintLineSeparator();

	// !!! STRUCTURE [is_polymorphic<T>] je TYPE FUNCTION.
	wprintf_s(L"IS POLYMORPHIC <int> [%d] !\n",is_polymorphic<int>::value);
	wprintf_s(L"IS POLYMORPHIC <wstring> [%d] !\n",is_polymorphic<wstring>::value);
	wprintf_s(L"IS POLYMORPHIC <CNonPolymorphicType> [%d] !\n",is_polymorphic<CNonPolymorphicType>::value);
	wprintf_s(L"IS POLYMORPHIC <CPolymorphicType> [%d] !\n",is_polymorphic<CPolymorphicType>::value);

	// !!! STRUCTURE [underlying_type<T>] je TYPE FUNCTION.
	printf_s("UNDERLYING TYPE <EEnum1> [%s] !\n",typeid(underlying_type<EEnum1>::type).name());
	printf_s("UNDERLYING TYPE <EEnum2> [%s] !\n",typeid(underlying_type<EEnum2>::type).name());

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSimpleTypeFunction(void)
{
	PrintLineSeparator();

	printf_s("CArrayTypeFunction<double,10>::Type [%s] !\n",typeid(CArrayTypeFunction<double,10>::Type).name());
	wprintf_s(L"CArrayTypeFunction<double,10>::Size [%d] !\n",CArrayTypeFunction<double,10>::Size);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSimpleConditionalTypeFunction(void)
{
	PrintLineSeparator();

	printf_s("CBiggerTypeTypeFunction<int,int>::Type [%s] !\n",typeid(CBiggerTypeTypeFunction<int,int>::BiggerType).name());
	printf_s("CBiggerTypeTypeFunction<int,double>::Type [%s] !\n",typeid(CBiggerTypeTypeFunction<int,double>::BiggerType).name());
	printf_s("CBiggerTypeTypeFunction<int,char>::Type [%s] !\n",typeid(CBiggerTypeTypeFunction<int,char>::BiggerType).name());

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestAliases(void)
{
	PrintLineSeparator();

	printf_s("IsBigger<int,double>::Type [%s] !\n",typeid(IsBigger<int,double>).name());
	printf_s("IsBiggerAsInt<double>::Type [%s] !\n",typeid(IsBiggerAsInt<double>).name());

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestHasOperators1(void)
{
	PrintLineSeparator();

	int															IntValue1=111;
	int															IntValue2=222;
	double														DoubleValue1=111.11;
	double														DoubleValue2=222.22;
	string														StringValue1="A";
	string														StringValue2="B";
	CClassWithCustomOperators									ClassWithCustomOperators1=100;
	CClassWithCustomOperators									ClassWithCustomOperators2=200;

	// Vracia TRUE.
	wprintf_s(L"HasOperatorPlus(IntValue1,IntValue2) [%ls] !\n",(HasOperatorPlus(IntValue1,IntValue2)==true) ? L"TRUE" : L"FALSE");

	// Vracia TRUE.
	wprintf_s(L"HasOperatorPlus(IntValue1,DoubleValue1) [%ls] !\n",(HasOperatorPlus(IntValue1,DoubleValue1)==true) ? L"TRUE" : L"FALSE");

	// Vracia TRUE.
	wprintf_s(L"HasOperatorPlus(DoubleValue1,DoubleValue2) [%ls] !\n",(HasOperatorPlus(DoubleValue1,DoubleValue2)==true) ? L"TRUE" : L"FALSE");

	// Vracia FALSE.
	wprintf_s(L"HasOperatorPlus(StringValue1,IntValue1) [%ls] !\n",(HasOperatorPlus(StringValue1,IntValue1)==true) ? L"TRUE" : L"FALSE");

	// Vracia TRUE.
	wprintf_s(L"HasOperatorPlus(StringValue1,StringValue2) [%ls] !\n",(HasOperatorPlus(StringValue1,StringValue2)==true) ? L"TRUE" : L"FALSE");

	// Vracia TRUE.
	wprintf_s(L"HasOperatorPlus(ClassWithCustomOperators1,ClassWithCustomOperators2) [%ls] !\n",(HasOperatorPlus(ClassWithCustomOperators1,ClassWithCustomOperators2)==true) ? L"TRUE" : L"FALSE");

	// Vracia TRUE.
	wprintf_s(L"HasOperatorPlus(ClassWithCustomOperators1,IntValue1) [%ls] !\n",(HasOperatorPlus(ClassWithCustomOperators1,IntValue1)==true) ? L"TRUE" : L"FALSE");

	// !!! Vracia FALSE, pretoze je pretazeny iba OPERATOR (CClassWithCustomOperators+INT) a NIE (INT+CClassWithCustomOperators).
	wprintf_s(L"HasOperatorPlus(IntValue1,ClassWithCustomOperators1) [%ls] !\n",(HasOperatorPlus(IntValue1,ClassWithCustomOperators1)==true) ? L"TRUE" : L"FALSE");

	// !!!!! Vracia TRUE, pretoze C++ AUTOMATICKY KONVERTUJE DOUBLE na INT, aj ked pri pouziti hodi COMPILER WARNING.
	wprintf_s(L"HasOperatorPlus(ClassWithCustomOperators1,DoubleValue1) [%ls] !\n",(HasOperatorPlus(ClassWithCustomOperators1,DoubleValue1)==true) ? L"TRUE" : L"FALSE");

	PrintLineSeparator();

	// Vracia TRUE.
	wprintf_s(L"HasOperatorDivide(IntValue1,IntValue2) [%ls] !\n",(HasOperatorDivide(IntValue1,IntValue2)==true) ? L"TRUE" : L"FALSE");

	// Vracia TRUE.
	wprintf_s(L"HasOperatorDivide(IntValue1,DoubleValue1) [%ls] !\n",(HasOperatorDivide(IntValue1,DoubleValue1)==true) ? L"TRUE" : L"FALSE");

	// Vracia TRUE.
	wprintf_s(L"HasOperatorDivide(DoubleValue1,DoubleValue2) [%ls] !\n",(HasOperatorDivide(DoubleValue1,DoubleValue2)==true) ? L"TRUE" : L"FALSE");

	// Vracia FALSE.
	wprintf_s(L"HasOperatorDivide(StringValue1,IntValue1) [%ls] !\n",(HasOperatorDivide(StringValue1,IntValue1)==true) ? L"TRUE" : L"FALSE");

	// Vracia FALSE.
	wprintf_s(L"HasOperatorDivide(StringValue1,StringValue2) [%ls] !\n",(HasOperatorDivide(StringValue1,StringValue2)==true) ? L"TRUE" : L"FALSE");

	// Vracia FALSE.
	wprintf_s(L"HasOperatorDivide(ClassWithCustomOperators1,ClassWithCustomOperators2) [%ls] !\n",(HasOperatorDivide(ClassWithCustomOperators1,ClassWithCustomOperators2)==true) ? L"TRUE" : L"FALSE");

	// Vracia FALSE.
	wprintf_s(L"HasOperatorDivide(ClassWithCustomOperators1,IntValue1) [%ls] !\n",(HasOperatorDivide(ClassWithCustomOperators1,IntValue1)==true) ? L"TRUE" : L"FALSE");

	// Vracia FALSE.
	wprintf_s(L"HasOperatorDivide(IntValue1,ClassWithCustomOperators1) [%ls] !\n",(HasOperatorDivide(IntValue1,ClassWithCustomOperators1)==true) ? L"TRUE" : L"FALSE");

	// Vracia FALSE.
	wprintf_s(L"HasOperatorDivide(ClassWithCustomOperators1,DoubleValue1) [%ls] !\n",(HasOperatorDivide(ClassWithCustomOperators1,DoubleValue1)==true) ? L"TRUE" : L"FALSE");

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestHasOperators2(void)
{
	PrintLineSeparator();

	string														StringValue1="A";
	string														StringValue2="B";
	CClassWithCustomOperators									ClassWithCustomOperators1=100;
	CClassWithCustomOperators									ClassWithCustomOperators2=200;

	// Vracia TRUE.
	wprintf_s(L"HasOperatorPlus(int,int) [%ls] !\n",(CHasOperators<int,int>::IsOperatorPlusDefined==true) ? L"TRUE" : L"FALSE");

	// Vracia TRUE.
	wprintf_s(L"HasOperatorPlus(int,double) [%ls] !\n",(CHasOperators<int,double>::IsOperatorPlusDefined==true) ? L"TRUE" : L"FALSE");

	// Vracia TRUE.
	wprintf_s(L"HasOperatorPlus(double,double) [%ls] !\n",(CHasOperators<double,double>::IsOperatorPlusDefined==true) ? L"TRUE" : L"FALSE");

	// Vracia FALSE.
	wprintf_s(L"HasOperatorPlus(string,int) [%ls] !\n",(CHasOperators<string,int>::IsOperatorPlusDefined==true) ? L"TRUE" : L"FALSE");

	// Vracia TRUE.
	wprintf_s(L"HasOperatorPlus(string,string) [%ls] !\n",(CHasOperators<string,string>::IsOperatorPlusDefined==true) ? L"TRUE" : L"FALSE");

	// Vracia TRUE.
	wprintf_s(L"HasOperatorPlus(CClassWithCustomOperators,CClassWithCustomOperators) [%ls] !\n",(CHasOperators<CClassWithCustomOperators,CClassWithCustomOperators>::IsOperatorPlusDefined==true) ? L"TRUE" : L"FALSE");

	// Vracia TRUE.
	wprintf_s(L"HasOperatorPlus(CClassWithCustomOperators,int) [%ls] !\n",(CHasOperators<CClassWithCustomOperators,int>::IsOperatorPlusDefined==true) ? L"TRUE" : L"FALSE");

	// !!! Vracia FALSE, pretoze je pretazeny iba OPERATOR (CClassWithCustomOperators+INT) a NIE (INT+CClassWithCustomOperators).
	wprintf_s(L"HasOperatorPlus(int,CClassWithCustomOperators) [%ls] !\n",(CHasOperators<int,CClassWithCustomOperators>::IsOperatorPlusDefined==true) ? L"TRUE" : L"FALSE");

	// !!!!! Vracia TRUE, pretoze C++ AUTOMATICKY KONVERTUJE DOUBLE na INT, aj ked pri pouziti hodi COMPILER WARNING.
	wprintf_s(L"HasOperatorPlus(CClassWithCustomOperators,double) [%ls] !\n",(CHasOperators<CClassWithCustomOperators,double>::IsOperatorPlusDefined==true) ? L"TRUE" : L"FALSE");

	PrintLineSeparator();

	// Vracia TRUE.
	wprintf_s(L"HasOperatorDivide(int,int) [%ls] !\n",(CHasOperators<int,int>::IsOperatorDivideDefined==true) ? L"TRUE" : L"FALSE");

	// Vracia TRUE.
	wprintf_s(L"HasOperatorDivide(int,double) [%ls] !\n",(CHasOperators<int,double>::IsOperatorDivideDefined==true) ? L"TRUE" : L"FALSE");

	// Vracia TRUE.
	wprintf_s(L"HasOperatorDivide(double,double) [%ls] !\n",(CHasOperators<double,double>::IsOperatorDivideDefined==true) ? L"TRUE" : L"FALSE");

	// Vracia FALSE.
	wprintf_s(L"HasOperatorDivide(string,int) [%ls] !\n",(CHasOperators<string,int>::IsOperatorDivideDefined==true) ? L"TRUE" : L"FALSE");

	// Vracia FALSE.
	wprintf_s(L"HasOperatorDivide(string,string) [%ls] !\n",(CHasOperators<string,string>::IsOperatorDivideDefined==true) ? L"TRUE" : L"FALSE");

	// Vracia FALSE.
	wprintf_s(L"HasOperatorDivide(CClassWithCustomOperators,CClassWithCustomOperators) [%ls] !\n",(CHasOperators<CClassWithCustomOperators,CClassWithCustomOperators>::IsOperatorDivideDefined==true) ? L"TRUE" : L"FALSE");

	// Vracia FALSE.
	wprintf_s(L"HasOperatorDivide(CClassWithCustomOperators,int) [%ls] !\n",(CHasOperators<CClassWithCustomOperators,int>::IsOperatorDivideDefined==true) ? L"TRUE" : L"FALSE");

	// Vracia FALSE.
	wprintf_s(L"HasOperatorDivide(int,CClassWithCustomOperators) [%ls] !\n",(CHasOperators<int,CClassWithCustomOperators>::IsOperatorDivideDefined==true) ? L"TRUE" : L"FALSE");

	// Vracia FALSE.
	wprintf_s(L"HasOperatorDivide(CClassWithCustomOperators,double) [%ls] !\n",(CHasOperators<CClassWithCustomOperators,double>::IsOperatorDivideDefined==true) ? L"TRUE" : L"FALSE");

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestHasFieldXXX(void)
{
	PrintLineSeparator();

	wprintf_s(L"CLASS [SStructureWithFieldXXX] has FIELD 'XXX' defined [%ls] !\n",(CHasFieldXXX<SStructureWithFieldXXX>::IfFieldDefined==true) ? L"TRUE" : L"FALSE");
	
	wprintf_s(L"CLASS [SStructureWithoutFieldXXX] has FIELD 'XXX' defined [%ls] !\n",(CHasFieldXXX<SStructureWithoutFieldXXX>::IfFieldDefined==true) ? L"TRUE" : L"FALSE");

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestTypeFunctionWithFunctor(void)
{
	PrintLineSeparator();

	CIsIntegralFunctor<int>										Functor1;
	CIsIntegralFunctor<wstring>									Functor2;

	bool														Result1=Functor1();
	bool														Result2=Functor2();
	// !!! DOUBLE NIE JE INTEGRAL TYPE.
	bool														Result3=CIsIntegralFunctor<double>{}();

	wprintf_s(L"Result1 [%d] !\n",Result1);
	wprintf_s(L"Result2 [%d] !\n",Result2);
	wprintf_s(L"Result3 [%d] !\n",Result3);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestTypeTraits(void)
{
	PrintLineSeparator();

	printf_s("CMyTypeTraits<CMyTypeWithTraits1>::Value [%s] !\n",typeid(CMyTypeTraits<CMyTypeWithTraits1>::Value).name());
	printf_s("CMyTypeTraits<CMyTypeWithTraits1>::Pointer [%s] !\n",typeid(CMyTypeTraits<CMyTypeWithTraits1>::Pointer).name());
	printf_s("CMyTypeTraits<CMyTypeWithTraits1>::Reference [%s] !\n",typeid(CMyTypeTraits<CMyTypeWithTraits1>::Reference).name());

	PrintLineSeparator();

	printf_s("CMyTypeTraits<CMyTypeWithTraits2>::Value [%s] !\n",typeid(CMyTypeTraits<CMyTypeWithTraits2>::Value).name());
	printf_s("CMyTypeTraits<CMyTypeWithTraits2>::Pointer [%s] !\n",typeid(CMyTypeTraits<CMyTypeWithTraits2>::Pointer).name());
	printf_s("CMyTypeTraits<CMyTypeWithTraits2>::Reference [%s] !\n",typeid(CMyTypeTraits<CMyTypeWithTraits2>::Reference).name());

	PrintLineSeparator();

	vector<int>													Vector{1,2,3};

	// Pouzitie TYPE TRAITS.
	printf_s("iterator_traits<vector<int>::iterator>::difference_type [%s] !\n",typeid(iterator_traits<vector<int>::iterator>::difference_type).name());

	PrintLineSeparator();

	// !!! Namiesto TYPE TRAITS je mozne pouzit KEYWORD [decltype()].
	printf_s("decltype(Vector.end()-Vector.begin()) [%s] !\n",typeid(decltype(Vector.end()-Vector.begin())).name());

	PrintLineSeparator();

	// !!! Takisto je mozne namiesto TYPE TRAITS pouzit KEYWORD [auto].
	auto														IteratorDifference=Vector.end()-Vector.begin();

	printf_s("IteratorDifference [%s] !\n",typeid(IteratorDifference).name());

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestConditionalTypeFunction(void)
{
	PrintLineSeparator();

	printf_s("CConditional<true,int,double>::TYPE [%s] !\n",typeid(CConditional<true,int,double>::TYPE).name());
	printf_s("CConditional<false,int,double>::TYPE [%s] !\n",typeid(CConditional<false,int,double>::TYPE).name());

	PrintLineSeparator();

	printf_s("conditional<true,int,double>::type [%s] !\n",typeid(conditional<true,int,double>::type).name());
	printf_s("conditional<false,int,double>::type [%s] !\n",typeid(conditional<false,int,double>::type).name());

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSelectTypeFunction(void)
{
	PrintLineSeparator();

	printf_s("CSelect<1,bool,int,double,wstring> [%s] !\n",typeid(CSelect<1,bool,int,double,wstring>::TYPE).name());
	printf_s("CSelect<2,bool,int,double,wstring> [%s] !\n",typeid(CSelect<2,bool,int,double,wstring>::TYPE).name());
	printf_s("CSelect<3,bool,int,double,wstring> [%s] !\n",typeid(CSelect<3,bool,int,double,wstring>::TYPE).name());
	printf_s("CSelect<4,bool,int,double,wstring> [%s] !\n",typeid(CSelect<4,bool,int,double,wstring>::TYPE).name());

	// !!! INDEX je MIMO hranic <1,4>. Kedze do TEMPLATE bol pridany STATIC ASSERT, tak COMPILER hodi ERROR.
	//printf_s("CSelect<100,bool,int,double,wstring> [%s] !\n",typeid(CSelect<100,bool,int,double,wstring>::TYPE).name());

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSelectVariadicTypeFunction(void)
{
	PrintLineSeparator();

	printf_s("CSelectVariadic<0,bool,int,double,wstring> [%s] !\n",typeid(CSelectVariadic<0,bool,int,double,wstring>::TYPE).name());
	printf_s("CSelectVariadic<1,bool,int,double,wstring> [%s] !\n",typeid(CSelectVariadic<1,bool,int,double,wstring>::TYPE).name());
	printf_s("CSelectVariadic<2,bool,int,double,wstring> [%s] !\n",typeid(CSelectVariadic<2,bool,int,double,wstring>::TYPE).name());
	printf_s("CSelectVariadic<3,bool,int,double,wstring> [%s] !\n",typeid(CSelectVariadic<3,bool,int,double,wstring>::TYPE).name());

	// !!! INDEX je MIMO hranic definovanych poctom PARAMETERS a preto COMPILER hodi COMPILATION ERROR.
	//printf_s("CSelectVariadic<100,bool,int,double,wstring> [%s] !\n",typeid(CSelectVariadic<100,bool,int,double,wstring>::TYPE).name());

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestTemplateClassRecursion(void)
{
	PrintLineSeparator();

	int															Value1=CTemplateClassRecursion<10>::VALUE;

	wprintf_s(L"Value1 [%d] !\n",Value1);

	int															Value2=CTemplateClassRecursion<5>::VALUE;

	wprintf_s(L"Value2 [%d] !\n",Value2);

	/*
	// !!! Sposobi nekonecnu RECURSION a tym padom aj COMPILATION ERROR.
	int															Value3=CTemplateClassRecursion<-1>::VALUE;

	wprintf_s(L"Value3 [%d] !\n",Value3);
	*/

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!! Toto je ITERATION STEP TEMPLATE ITERATION.
template<int IterationStep>
int TemplateFunctionRecursion(void)
{
	// !!! Tu sa vykonava COMPILE TIME RECURSION, pretoze sa vola TEMPLATE s (IterationStep-1).
	int															Value=IterationStep+TemplateFunctionRecursion<IterationStep-1>();

	return(Value);
}
//-----------------------------------------------------------------------------
// !!! Toto je TERMINAL STEP TEMPLATE ITERATION.
// !!! Jedna sa o TEMPLATE SPECIALIZATION.
template<>
int TemplateFunctionRecursion<1>(void)
{
	return(1);
}
//-----------------------------------------------------------------------------
void TestTemplateFunctionRecursion(void)
{
	PrintLineSeparator();

	int															Value1=TemplateFunctionRecursion<10>();

	wprintf_s(L"Value1 [%d] !\n",Value1);

	int															Value2=TemplateFunctionRecursion<5>();

	wprintf_s(L"Value2 [%d] !\n",Value2);

	/*
	// !!! Sposobi nekonecnu RECURSION a tym padom aj COMPILATION ERROR.
	int															Value3=TemplateFunctionRecursion<-1>();

	wprintf_s(L"Value3 [%d] !\n",Value3);
	*/

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!! TEMPLATE METHOD je definovana IBA pre CLASS TYPES.
template<typename TType>
typename enable_if<is_class<TType>::value,TType>::type EnableIfInReturnValue(TType Value)
{
	typename enable_if<is_class<TType>::value,TType>::type		JustOneMoreCopy=Value;

	return(JustOneMoreCopy);
}
//-----------------------------------------------------------------------------
// !!! TEMPLATE METHOD je definovana IBA pre CLASS TYPES.
template<typename TType>
TType EnableIfInParameter(typename enable_if<is_class<TType>::value,TType>::type Value)
{
	typename enable_if<is_class<TType>::value,TType>::type		JustOneMoreCopy=Value;

	return(JustOneMoreCopy);
}
//-----------------------------------------------------------------------------
// !!! TEMPLATE METHOD je definovana IBA pre CLASS TYPES.
// !!! 2. PARAMETER je ANONYMOUS. Pouziva sa iba na testovanie ci [TType] je CLASS.
template<typename TType, typename =typename enable_if<is_class<TType>::value,TType>::type>
TType EnableIfInTypeParameter(TType Value)
{
	typename enable_if<is_class<TType>::value,TType>::type		JustOneMoreCopy=Value;

	return(JustOneMoreCopy);
}
//-----------------------------------------------------------------------------
void TestStandardEnableIf(void)
{
	PrintLineSeparator();

	CStandardEnableIf											Class;
	wstring														ClassType1=L"Timmy";
	wstring														ClassType2=L"Atreyu";
	wstring														ClassType3=L"Jenny";
	wstring														ClassType4=L"Timmy";
	wstring														ClassType5=L"Atreyu";
	wstring														ClassType6=L"Jenny";

	wstring														ReturnString1=Class.EnableIfInReturnValue(ClassType1);

	wprintf_s(L"ReturnString1 [%ls] !\n",ReturnString1.c_str());

	/*
	// !!! Hodi COMPILATION ERROR, pretoze INT NIE JE CLASS.
	int															ReturnInt1=Class.EnableIfInReturnValue(12);

	wprintf_s(L"ReturnInt1 [%d] !\n",ReturnInt1);
	*/

	wstring														ReturnString2=Class.EnableIfInParameter<wstring>(ClassType2);

	wprintf_s(L"ReturnString2 [%ls] !\n",ReturnString2.c_str());

	/*
	// !!! Hodi COMPILATION ERROR, pretoze INT NIE JE CLASS.
	int															ReturnInt2=Class.EnableIfInParameter<int>(12);

	wprintf_s(L"ReturnInt2 [%d] !\n",ReturnInt2);
	*/

	wstring														ReturnString3=Class.EnableIfInTypeParameter(ClassType3);

	wprintf_s(L"ReturnString3 [%ls] !\n",ReturnString3.c_str());

	/*
	// !!! Hodi COMPILATION ERROR, pretoze INT NIE JE CLASS.
	int															ReturnInt3=Class.EnableIfInTypeParameter(12);

	wprintf_s(L"ReturnInt3 [%d] !\n",ReturnInt3);
	*/

	PrintLineSeparator();

	wstring														ReturnString4=EnableIfInReturnValue(ClassType4);

	wprintf_s(L"ReturnString4 [%ls] !\n",ReturnString4.c_str());

	/*
	// !!! Hodi COMPILATION ERROR, pretoze INT NIE JE CLASS.
	int															ReturnInt4=EnableIfInReturnValue(42);

	wprintf_s(L"ReturnInt4 [%d] !\n",ReturnInt4);
	*/

	wstring														ReturnString5=EnableIfInParameter<wstring>(ClassType5);

	wprintf_s(L"ReturnString5 [%ls] !\n",ReturnString5.c_str());

	/*
	// !!! Hodi COMPILATION ERROR, pretoze INT NIE JE CLASS.
	int															ReturnInt5=EnableIfInParameter<int>(15);

	wprintf_s(L"ReturnInt5 [%d] !\n",ReturnInt5);
	*/

	wstring														ReturnString6=EnableIfInTypeParameter(ClassType6);

	wprintf_s(L"ReturnString6 [%ls] !\n",ReturnString6.c_str());

	/*
	// !!! Hodi COMPILATION ERROR, pretoze INT NIE JE CLASS.
	int															ReturnInt6=EnableIfInTypeParameter(12);

	wprintf_s(L"ReturnInt6 [%d] !\n",ReturnInt6);
	*/

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!! TEMPLATE METHOD je definovana IBA pre CLASS TYPES.
template<typename TType>
typename CEnableIf<is_class<TType>::value,TType>::TYPE CustomEnableIfInReturnValue(TType Value)
{
	typename CEnableIf<is_class<TType>::value,TType>::TYPE		JustOneMoreCopy=Value;

	return(JustOneMoreCopy);
}
//-----------------------------------------------------------------------------
// !!! TEMPLATE METHOD je definovana IBA pre CLASS TYPES.
template<typename TType>
TType CustomEnableIfInParameter(typename CEnableIf<is_class<TType>::value,TType>::TYPE Value)
{
	typename CEnableIf<is_class<TType>::value,TType>::TYPE		JustOneMoreCopy=Value;

	return(JustOneMoreCopy);
}
//-----------------------------------------------------------------------------
// !!! TEMPLATE METHOD je definovana IBA pre CLASS TYPES.
// !!! 2. PARAMETER je ANONYMOUS. Pouziva sa iba na testovanie ci [TType] je CLASS.
template<typename TType, typename =typename CEnableIf<is_class<TType>::value,TType>::TYPE>
TType CustomEnableIfInTypeParameter(TType Value)
{
	typename CEnableIf<is_class<TType>::value,TType>::TYPE		JustOneMoreCopy=Value;

	return(JustOneMoreCopy);
}
//-----------------------------------------------------------------------------
void TestCustomEnableIf(void)
{
	PrintLineSeparator();

	CCustomEnableIf												Class;
	wstring														ClassType1=L"Timmy";
	wstring														ClassType2=L"Atreyu";
	wstring														ClassType3=L"Jenny";
	wstring														ClassType4=L"Timmy";
	wstring														ClassType5=L"Atreyu";
	wstring														ClassType6=L"Jenny";

	wstring														ReturnString1=Class.EnableIfInReturnValue(ClassType1);

	wprintf_s(L"ReturnString1 [%ls] !\n",ReturnString1.c_str());

	/*
	// !!! Hodi COMPILATION ERROR, pretoze INT NIE JE CLASS.
	int															ReturnInt1=Class.EnableIfInReturnValue(12);

	wprintf_s(L"ReturnInt1 [%d] !\n",ReturnInt1);
	*/

	wstring														ReturnString2=Class.EnableIfInParameter<wstring>(ClassType2);

	wprintf_s(L"ReturnString2 [%ls] !\n",ReturnString2.c_str());

	/*
	// !!! Hodi COMPILATION ERROR, pretoze INT NIE JE CLASS.
	int															ReturnInt2=Class.EnableIfInParameter<int>(12);

	wprintf_s(L"ReturnInt2 [%d] !\n",ReturnInt2);
	*/

	wstring														ReturnString3=Class.EnableIfInTypeParameter(ClassType3);

	wprintf_s(L"ReturnString3 [%ls] !\n",ReturnString3.c_str());

	/*
	// !!! Hodi COMPILATION ERROR, pretoze INT NIE JE CLASS.
	int															ReturnInt3=Class.EnableIfInTypeParameter(12);

	wprintf_s(L"ReturnInt3 [%d] !\n",ReturnInt3);
	*/

	PrintLineSeparator();

	wstring														ReturnString4=CustomEnableIfInReturnValue(ClassType4);

	wprintf_s(L"ReturnString4 [%ls] !\n",ReturnString4.c_str());

	/*
	// !!! Hodi COMPILATION ERROR, pretoze INT NIE JE CLASS.
	int															ReturnInt4=CustomEnableIfInReturnValue(42);

	wprintf_s(L"ReturnInt4 [%d] !\n",ReturnInt4);
	*/

	wstring														ReturnString5=CustomEnableIfInParameter<wstring>(ClassType5);

	wprintf_s(L"ReturnString5 [%ls] !\n",ReturnString5.c_str());

	/*
	// !!! Hodi COMPILATION ERROR, pretoze INT NIE JE CLASS.
	int															ReturnInt5=CustomEnableIfInParameter<int>(15);

	wprintf_s(L"ReturnInt5 [%d] !\n",ReturnInt5);
	*/

	wstring														ReturnString6=CustomEnableIfInTypeParameter(ClassType6);

	wprintf_s(L"ReturnString6 [%ls] !\n",ReturnString6.c_str());

	/*
	// !!! Hodi COMPILATION ERROR, pretoze INT NIE JE CLASS.
	int															ReturnInt6=CustomEnableIfInTypeParameter(12);

	wprintf_s(L"ReturnInt6 [%d] !\n",ReturnInt6);
	*/

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestHasFunctionXXX(void)
{
	PrintLineSeparator();

	int															IntValue=100;
	string														StringValue="AAA";
	CTypeWithMethodXXX											TypeWithMethodXXXValue;

	wprintf_s(L"HasMethodXXX(IntValue) [%ls] !\n",(HasMethodXXX(IntValue)==true) ? L"TRUE" : L"FALSE");

	wprintf_s(L"HasMethodXXX(StringValue) [%ls] !\n",(HasMethodXXX(StringValue)==true) ? L"TRUE" : L"FALSE");

	wprintf_s(L"HasMethodXXX(TypeWithMethodXXXValue) [%ls] !\n",(HasMethodXXX(TypeWithMethodXXXValue)==true) ? L"TRUE" : L"FALSE");

	PrintLineSeparator();

	wprintf_s(L"SCheckFunctionXXX<int>::RESULT [%ls] !\n",(SCheckFunctionXXX<int>::RESULT==true) ? L"TRUE" : L"FALSE");

	// !!! Toto uz FUNGUJE aj v G++.
	wprintf_s(L"SCheckFunctionXXX<wstring>::RESULT [%ls] !\n",(SCheckFunctionXXX<wstring>::RESULT==true) ? L"TRUE" : L"FALSE");

	wprintf_s(L"SCheckFunctionXXX<CTypeWithMethodXXX>::RESULT [%ls] !\n",(SCheckFunctionXXX<CTypeWithMethodXXX>::RESULT==true) ? L"TRUE" : L"FALSE");

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestHasFunctionXXXFromBook(void)
{
	PrintLineSeparator();

	wprintf_s(L"SHasFunctionXXX<int>::value [%ls] !\n",(SHasFunctionXXX<int>::value==true) ? L"TRUE" : L"FALSE");

	wprintf_s(L"SHasFunctionXXX<wstring>::value [%ls] !\n",(SHasFunctionXXX<wstring>::value==true) ? L"TRUE" : L"FALSE");

	wprintf_s(L"SHasFunctionXXX<CTypeWithMethodXXX>::value [%ls] !\n",(SHasFunctionXXX<CTypeWithMethodXXX>::value==true) ? L"TRUE" : L"FALSE");

	PrintLineSeparator();

	wprintf_s(L"SFunctionXXXCheck<int>::RESULT [%ls] !\n",(SFunctionXXXCheck<int>::RESULT==true) ? L"TRUE" : L"FALSE");

	// !!! Toto uz FUNGUJE aj v G++.
	wprintf_s(L"SFunctionXXXCheck<wstring>::RESULT [%ls] !\n",(SFunctionXXXCheck<wstring>::RESULT==true) ? L"TRUE" : L"FALSE");

	wprintf_s(L"SFunctionXXXCheck<CTypeWithMethodXXX>::RESULT [%ls] !\n",(SFunctionXXXCheck<CTypeWithMethodXXX>::RESULT==true) ? L"TRUE" : L"FALSE");

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<typename T1, typename T2, typename T3, typename T4>
STuple<T1,T2,T3,T4> MakeTuple(const T1& Value1, const T2& Value2, const T3& Value3, const T4& Value4)
{
	return(STuple<T1,T2,T3,T4>(Value1,Value2,Value3,Value4));
}
//-----------------------------------------------------------------------------
void TestTuple(void)
{
	PrintLineSeparator();

	STuple<bool,int,double,wstring>								Tuple1{true,10,2.3,L"ABC"};
	const STuple<bool,int,double,wstring>						Tuple2{false,12,4.8,L"XYZ"};
	STuple<bool,int,double,wstring>								Tuple3=MakeTuple(true,10,2.3,wstring(L"ABC"));

	wprintf_s(L"Tuple1 [%d] [%d] [%f] [%ls]!\n",Tuple1.MValue,Tuple1.GetBase()->MValue,Tuple1.GetBase()->GetBase()->MValue,Tuple1.GetBase()->GetBase()->GetBase()->MValue.c_str());

	Tuple1.Print(L"Tuple1 ",L" !\n");

	bool														Item1=STupleItem<bool,0>::GetItem(Tuple1);
	int															Item2=STupleItem<int,1>::GetItem(Tuple1);
	double														Item3=STupleItem<double,2>::GetItem(Tuple1);
	wstring														Item4=STupleItem<wstring,3>::GetItem(Tuple1);

	wprintf_s(L"Tuple1 [%d] [%d] [%f] [%ls]!\n",Item1,Item2,Item3,Item4.c_str());

	bool														ConstItem1=STupleItem<bool,0>::GetItem(Tuple2);
	int															ConstItem2=STupleItem<int,1>::GetItem(Tuple2);
	double														ConstItem3=STupleItem<double,2>::GetItem(Tuple2);
	wstring														ConstItem4=STupleItem<wstring,3>::GetItem(Tuple2);

	wprintf_s(L"Tuple2 [%d] [%d] [%f] [%ls]!\n",ConstItem1,ConstItem2,ConstItem3,ConstItem4.c_str());

	Tuple3.Print(L"Tuple3 ",L" !\n");

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestVariadicTemplate(void)
{
	PrintLineSeparator();

	CVariadicTemplate<wstring,wstring,int>						VariadicTemplate(L"Timmy",L"Anderson",12);
	CVariadicTemplate<CString,CString,int>						VariadicTemplateWithCString(CString(L"Timmy"),CString(L"Anderson"),12);

	PrintLineSeparator();

	const wstring&												FirstName1=VariadicTemplate.GetItem<0>();
	const wstring&												LastName1=VariadicTemplate.GetItem<1>();
	const int&													Age1=VariadicTemplate.GetItem<2>();

	wprintf_s(L"VARIADIC TEMPLATE [%ls %ls] AGE [%d] !\n",FirstName1.c_str(),LastName1.c_str(),Age1);

	PrintLineSeparator();

	const CString&												FirstName2=VariadicTemplateWithCString.GetItem<0>();
	const CString&												LastName2=VariadicTemplateWithCString.GetItem<1>();
	const int&													Age2=VariadicTemplateWithCString.GetItem<2>();
	
	wprintf_s(L"VARIADIC TEMPLATE with CString [%ls %ls] AGE [%d] !\n",FirstName2.GetValue().c_str(),LastName2.GetValue().c_str(),Age2);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!!!! NON-TEMPLATE FUNCTION, ktora reprezentuje KONIEC REKURZIE.
void SimpleVariadicTemplateFunction(wstring* Prefix, wstring* Postfix)
{
	if (Prefix!=nullptr)
	{
		wcout << *Prefix;
	}

	if (Postfix!=nullptr)
	{
		wcout << *Postfix;
	}
}
//-----------------------------------------------------------------------------
// !!! Definicia VARIADIC TEMPLATES. PARAMETER [FirstTypeParameter] reprezentuje 1. TYPE PARAMETER. PARAMETER [OtherTypeParameters] reprezentuje 2. az N. PARAMETERS.
// !!!!! TYPE PARAMETER [TTypes] sa nazyva TEMPLATE PARAMETER PACK.
template<typename TType, typename... TTypes>
// !!!!! SYNTAX [TTypes...] rozbali vsetky ostatne TYPE PARAMETERS.
void SimpleVariadicTemplateFunction(wstring* Prefix, wstring* Postfix, TType FirstTypeParameter, TTypes... OtherTypeParameters)
{
	if (Prefix!=nullptr)
	{
		wcout << *Prefix;
	}

	wcout << L" [" << FirstTypeParameter << L"]";

	// !!! Rekurzivne sa vola VARIADIC TEMPLATE SimpleVariadicTemplateFunction().
	// !!!!! SYNTAX [OtherTypeParameters...] rozbali vsetky ostatne TYPE PARAMETERS.
	SimpleVariadicTemplateFunction(nullptr,Postfix,OtherTypeParameters...);
}
//-----------------------------------------------------------------------------
template<typename... TTypes>
size_t CountTypeParamaterInVariadicTemplateFunction(TTypes...)
{
	size_t														NumberOfTypeParameters=sizeof...(TTypes);

	return(NumberOfTypeParameters);
}
//-----------------------------------------------------------------------------
template<typename... TTypes>
void PassTypeParamaterVariadicTemplateFunction(TTypes... TypeParameters)
{
	// !!!!! TEMPLATE PARAMETER PACKS ako [TypeParameters] je mozne prenasat ako normalne PARAMETERS.
	// !!! Pri prenose TEMPLATE PARAMETER PACKS je nutne vykonat PARAMETER PACK EXPANSION.
	size_t														NumberOfTypeParameters=CountTypeParamaterInVariadicTemplateFunction(TypeParameters...);

	wcout << L"NumberOfTypeParameters [" << NumberOfTypeParameters << L"] !\n";
}
//-----------------------------------------------------------------------------
template<typename... TTypes>
void FinishProcessing(TTypes...)
{
	wprintf_s(L"FinishProcessing() - PROCESSING FINISHED !\n");
}
//-----------------------------------------------------------------------------
template<typename TType>
TType ProcessItem(TType TypeParameter)
{
	wcout << L"ProcessItem() - PARAMETER [" << TypeParameter << L"] !\n";

	return(TypeParameter);
}
//-----------------------------------------------------------------------------
template<typename... TTypes>
void UnpackTypeParameterPack(TTypes... TypeParameters)
{
	wprintf_s(L"UnpackTypeParameterPack() - PROCESSING STARTED !\n");

	// !!!!! C++ pretavi toto volanie na CODE [ProcessItem(TYPE_PARAMETER_1),ProcessItem(TYPE_PARAMETER_2),...,ProcessItem(TYPE_PARAMETER_N)]. To znaci, ze sa zoberu RETURN VALUES z volanie TEMPLATE FUNCTION PrintItem() a tie sa rozbalia, aby mohli sluzit ako PARAMETERS do VARIADIC TEMPLATE FUNCTION FinishProcessing().
	// !!!!! TYPE PARAMETER PACK je mozne pouzit pri vykonavani CASTS ci specifikacii TYPE PARAMETER TEMPLATES.
	// !!!!! CODE sa transformuje na CODE [FinishProcessing(ProcessItem<TYPE_1>((TYPE_1)TypeParameter_1),ProcessItem<TYPE_2>((TYPE_2)TypeParameter_2),...,ProcessItem<TYPE_N>((TYPE_N)TypeParameter_N))].
	FinishProcessing(ProcessItem<TTypes>((TTypes)TypeParameters)...);
}
//-----------------------------------------------------------------------------
void TestVariadicTemplateFunction(void)
{
	PrintLineSeparator();

	wstring														Prefix1=wstring(L"0 PARAMETERS");
	wstring														Prefix2=wstring(L"1 PARAMETERS");
	wstring														Prefix3=wstring(L"2 PARAMETERS");
	wstring														Prefix4=wstring(L"3 PARAMETERS");
	wstring														Postfix=wstring(L" !\n");

	SimpleVariadicTemplateFunction(&Prefix1,&Postfix);
	SimpleVariadicTemplateFunction(&Prefix2,&Postfix,L"Timmy");
	SimpleVariadicTemplateFunction(&Prefix3,&Postfix,L"Timmy",L"Anderson");
	SimpleVariadicTemplateFunction(&Prefix4,&Postfix,L"Timmy",L"Anderson",12);

	PrintLineSeparator();

	PassTypeParamaterVariadicTemplateFunction("5",4,3.2,2.4F,false);

	PrintLineSeparator();

	UnpackTypeParameterPack(true,100,12.4,L"ABC");

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestVariadicFunctionPrintf(void)
{
	PrintLineSeparator();

	try
	{
		PrintfByIndex(L"NAME [!% !%] AGE [!%] !!\n",wstring(L"Timmy"),wstring(L"Anderson"),12);
	}
	catch(const CException& Exception)
	{
		wprintf_s(L"\nEXCEPTION [%ls] !\n",Exception.GetMessage().c_str());
	}

	PrintLineSeparator();

	try
	{
		// Chyba posledny PARAMETER.
		PrintfByIndex(L"NAME [!% !%] AGE [!%] !!\n",wstring(L"Timmy"),wstring(L"Anderson"));
	}
	catch(const CException& Exception)
	{
		wprintf_s(L"\nEXCEPTION [%ls] !\n",Exception.GetMessage().c_str());
	}

	PrintLineSeparator();

	try
	{
		// Jeden PARAMETER je navyse.
		PrintfByIndex(L"NAME [!% !%] AGE [!%] !!\n",wstring(L"Timmy"),wstring(L"Anderson"),12,12);
	}
	catch(const CException& Exception)
	{
		wprintf_s(L"\nEXCEPTION [%ls] !\n",Exception.GetMessage().c_str());
	}

	PrintLineSeparator();

	try
	{
		// Chybny format.
		PrintfByIndex(L"!");
	}
	catch(const CException& Exception)
	{
		wprintf_s(L"\nEXCEPTION [%ls] !\n",Exception.GetMessage().c_str());
	}

	PrintLineSeparator();

	try
	{
		PrintfByIterator(L"NAME [!% !%] AGE [!%] !!\n",wstring(L"Timmy"),wstring(L"Anderson"),12);
	}
	catch(const CException& Exception)
	{
		wprintf_s(L"\nEXCEPTION [%ls] !\n",Exception.GetMessage().c_str());
	}

	PrintLineSeparator();

	try
	{
		// Chyba posledny PARAMETER.
		PrintfByIterator(L"NAME [!% !%] AGE [!%] !!\n",wstring(L"Timmy"),wstring(L"Anderson"));
	}
	catch(const CException& Exception)
	{
		wprintf_s(L"\nEXCEPTION [%ls] !\n",Exception.GetMessage().c_str());
	}

	PrintLineSeparator();

	try
	{
		// Jeden PARAMETER je navyse.
		PrintfByIterator(L"NAME [!% !%] AGE [!%] !!\n",wstring(L"Timmy"),wstring(L"Anderson"),12,12);
	}
	catch(const CException& Exception)
	{
		wprintf_s(L"\nEXCEPTION [%ls] !\n",Exception.GetMessage().c_str());
	}

	PrintLineSeparator();

	try
	{
		// Chybny format.
		PrintfByIterator(L"!");
	}
	catch(const CException& Exception)
	{
		wprintf_s(L"\nEXCEPTION [%ls] !\n",Exception.GetMessage().c_str());
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestVariadicTemplateMethod(void)
{
	PrintLineSeparator();

	wstring														Prefix1=wstring(L"0 PARAMETERS");
	wstring														Prefix2=wstring(L"1 PARAMETERS");
	wstring														Prefix3=wstring(L"2 PARAMETERS");
	wstring														Prefix4=wstring(L"3 PARAMETERS");
	wstring														Postfix=wstring(L" !\n");

	CVariadicTemplateMethods									VariadicTemplateMethods;

	VariadicTemplateMethods.SimpleVariadicTemplateMethod(&Prefix1,&Postfix);
	VariadicTemplateMethods.SimpleVariadicTemplateMethod(&Prefix2,&Postfix,L"Timmy");
	VariadicTemplateMethods.SimpleVariadicTemplateMethod(&Prefix3,&Postfix,L"Timmy",L"Anderson");
	VariadicTemplateMethods.SimpleVariadicTemplateMethod(&Prefix4,&Postfix,L"Timmy",L"Anderson",12);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestVariadicTemplateClass(void)
{
	PrintLineSeparator();

	CSimpleVariadicClassTemplate<wstring,wstring,int>			SimpleClass(wstring(L"Timmy"),wstring(L"Anderson"),12);

	SimpleClass.PrintBuffer();

	PrintLineSeparator();

	CComplexVariadicClassTemplate<wstring,wstring,int>			ComplexClass(wstring(L"Timmy"),wstring(L"Anderson"),12);

	wprintf_s(L"ComplexClass [%ls] [%ls] [%d] !\n",ComplexClass.GetFirstItem().c_str(),ComplexClass.GetBase()->GetFirstItem().c_str(),ComplexClass.GetBase()->GetBase()->GetFirstItem());

	PrintLineSeparator();

	ComplexClass.DoRecursion();

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void PrintVariadicTemplateFunction(wstring* Prefix, wstring* Postfix)
{
	if (Prefix!=nullptr)
	{
		wcout << *Prefix;
	}

	if (Postfix!=nullptr)
	{
		wcout << *Postfix;
	}
}
//-----------------------------------------------------------------------------
template<typename TType, typename... TTypes>
void PrintVariadicTemplateFunction(wstring* Prefix, wstring* Postfix, TType FirstTypeParameter, TTypes... OtherTypeParameters)
{
	if (Prefix!=nullptr)
	{
		wcout << *Prefix;
	}

	wcout << L" [" << FirstTypeParameter << L"]";

	PrintVariadicTemplateFunction(nullptr,Postfix,OtherTypeParameters...);
}
//-----------------------------------------------------------------------------
template<typename... TTypes>
void IncrementTest(TTypes... TypeParameters)
{
	wstring														Prefix=L"INCREMENT TEST";
	wstring														Postfix=L" !\n";

	// !!! Volanie sa konvertuje na [SimpleVariadicTemplateFunction(&Prefix,&Postfix,++10,++20,++30)].
	PrintVariadicTemplateFunction(&Prefix,&Postfix,++TypeParameters...);
}
//-----------------------------------------------------------------------------
template<typename... TTypes>
void AdditionTest(int Addition, TTypes... TypeParameters)
{
	wstring														Prefix=L"ADDITION TEST";
	wstring														Postfix=L" !\n";

	// !!! Volanie sa konvertuje na [PrintVariadicTemplateFunction(&Prefix,&Postfix,10+100,10+200,10+300)].
	PrintVariadicTemplateFunction(&Prefix,&Postfix,Addition+TypeParameters...);

	// !!! Volanie sa konvertuje na [PrintVariadicTemplateFunction(&Prefix,&Postfix,10+100,10+200,10+300)].
	PrintVariadicTemplateFunction(&Prefix,&Postfix,(TypeParameters+Addition)...);

	// !!! Volanie sa konvertuje na [PrintVariadicTemplateFunction(&Prefix,&Postfix,13+100,13+200,13+300)] a NIE [SimpleVariadicTemplateFunction(&Prefix,&Postfix,11+100,12+200,13+300)].
	// !!!!! POZOR. Vysledok je (113,213,313) a NIE (111,212,313). Z toho vyplyva, ze C++ EXPRESSION vykonava ESTE PRED substituciou ARGUMENTS danej FUNCTION.
	// V G++ hodi COMPILER WARNING.
#ifdef _MSC_VER
	PrintVariadicTemplateFunction(&Prefix,&Postfix,(TypeParameters+(++Addition))...);
#endif
}
//-----------------------------------------------------------------------------
template<typename TType>
TType AddValues(TType Value1, TType Value2)
{
	TType														Result=Value1+Value2;

	wcout << L"[" << Value1 << L"] + [" << Value2 << "] = [" << Result << "] !\n";

	return(Result);
}
//-----------------------------------------------------------------------------
template<typename TType, typename... TTypes>
void VariadicTemplatesAddValues(TType Value, TTypes... Values)
{
	wstring														Prefix=L"EXPRESSIONS ADDITION TEST";
	wstring														Postfix=L" !\n";

	// !!!!! C++ pre hodnoty (10,100,200,300) generuje CODE [PrintVariadicTemplateFunction(&Prefix,&Postfix,AddValues<int>(10,100),AddValues<int>(10,200),AddValues<int>(10,300))].
	PrintVariadicTemplateFunction(&Prefix,&Postfix,(AddValues<TType>(Value,Values))...);
}
//-----------------------------------------------------------------------------
bool CheckCondition(void)
{
	return(true);
}
//-----------------------------------------------------------------------------
template<typename... TTypes>
bool CheckCondition(bool Value, TTypes... Values)
{
	return(Value==true && CheckCondition(Values...)==true);
}
//-----------------------------------------------------------------------------
bool GetFirst(bool First)
{
	return(First);
}
//-----------------------------------------------------------------------------
template<typename ...TTypes>
void BoolTemplate(TTypes... Parameters)
{
	bool														Result=CheckCondition(Parameters...);

	if (Result==true)
	{
		wprintf_s(L"RESULT [TRUE] !\n");
	}
	else
	{
		wprintf_s(L"RESULT [FALSE] !\n");
	}

	// Inicializacia VECTOR.
	vector<bool>												Vector{GetFirst(Parameters)...};

	for(bool Value : Vector)
	{
		wprintf_s(L"VALUE [%d] !\n",Value);
	}
}
//-----------------------------------------------------------------------------
void TestVariadicTemplateFunctionExpressions(void)
{
	PrintLineSeparator();

	IncrementTest(10,20,30);

	PrintLineSeparator();

	AdditionTest(10,100,200,300);

	PrintLineSeparator();

	VariadicTemplatesAddValues(10,100,200,300);

	PrintLineSeparator();

	BoolTemplate(true,false,true);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestDerivedVariadicTemplate(void)
{
	PrintLineSeparator();

	CClass1														Class1(L"Timmy Anderson");
	CClass2														Class2(12);
	CDerivedVariadicTemplate<CClass1,CClass2>					VariadicTemplate(Class1,Class2);

	// !!! Kedze VARIADIC CLASS CDerivedVariadicTemplate<CClass1,CClass2> je DERIVED z CLASSES CClass1 a CClass2, je mozne spravit CASTING na ich REFERENCES.
	CClass1&													Reference1=VariadicTemplate;
	CClass2&													Reference2=VariadicTemplate;

	wprintf_s(L"NAME [%ls] AGE [%d] !\n",Reference1.GetValue().c_str(),Reference2.GetValue());

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void PrintName(const wstring& FirstName, const wstring& LastName, int Age)
{
	wprintf_s(L"NAME [%ls %ls] AGE [%d] !\n",FirstName.c_str(),LastName.c_str(),Age);
}
//-----------------------------------------------------------------------------
void PrintNameClass(const CName& Name)
{
	wprintf_s(L"NAME [%ls %ls] AGE [%d] !\n",Name.GetFirstName().c_str(),Name.GetLastName().c_str(),Name.GetAge());
}
//-----------------------------------------------------------------------------
template<typename TFunctionToCall, typename... TTypes>
void CallerFunction(TFunctionToCall&& FunctionToCall, TTypes&&... TypeParameters)
{
	wprintf_s(L"CallerFunction() CALLED !\n");

	// !!! Vola sa FUNCTION FunctionToCall() s PARAMETERS [TypeParameters].
	// !!!!! Pouzitie FUNCTION forward<TType>() umoznuje vyuzit MOVE SEMANTICS.
	FunctionToCall(forward<TTypes>(TypeParameters)...);
}
//-----------------------------------------------------------------------------
CName CreateNameAsRVALUE(const wstring& FirstName, const wstring& LastName, int Age)
{
	return(CName(FirstName,LastName,Age));
}
//-----------------------------------------------------------------------------
void TestCallAnotherFunction(void)
{
	PrintLineSeparator();

	CallerFunction(PrintName,wstring(L"Timmy"),wstring(L"Anderson"),12);

	PrintLineSeparator();

	CName														Name(wstring(L"Timmy"),wstring(L"Anderson"),12);

	CallerFunction(PrintNameClass,Name);

	PrintLineSeparator();

	CallerFunction(PrintNameClass,CName(wstring(L"Timmy"),wstring(L"Anderson"),12));

	PrintLineSeparator();

	CallerFunction(PrintNameClass,CreateNameAsRVALUE(wstring(L"Timmy"),wstring(L"Anderson"),12));

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMyTuple(void)
{
	PrintLineSeparator();

	CTuple<wstring,wstring,int>									Tuple(L"Timmy",L"Anderson",12);
	CTuple<CString,CString,int>									TupleWithCString(CString(L"Timmy"),CString(L"Anderson"),12);

	PrintLineSeparator();

	wprintf_s(L"TUPLE [%ls %ls] AGE [%d] !\n",Tuple.GetValue().c_str(),Tuple.GetBase().GetValue().c_str(),Tuple.GetBase().GetBase().GetValue());
	
	Tuple.Print(L"TUPLE");

	wstring														FirstName1=CTuple<wstring,wstring,int>::StaticGetItem<0>(Tuple);
	wstring														LastName1=CTuple<wstring,wstring,int>::StaticGetItem<1>(Tuple);
	int															Age1=CTuple<wstring,wstring,int>::StaticGetItem<2>(Tuple);

	wprintf_s(L"TUPLE [%ls %ls] AGE [%d] !\n",FirstName1.c_str(),LastName1.c_str(),Age1);

	const wstring&												FirstName2=Tuple.GetItem<0>();
	const wstring&												LastName2=Tuple.GetItem<1>();
	const int&													Age2=Tuple.GetItem<2>();

	wprintf_s(L"TUPLE [%ls %ls] AGE [%d] !\n",FirstName2.c_str(),LastName2.c_str(),Age2);

	PrintLineSeparator();

	const CString&												FirstName3=TupleWithCString.GetItem<0>();
	const CString&												LastName3=TupleWithCString.GetItem<1>();
	const int&													Age3=TupleWithCString.GetItem<2>();
	
	wprintf_s(L"TUPLE with CString [%ls %ls] AGE [%d] !\n",FirstName3.GetValue().c_str(),LastName3.GetValue().c_str(),Age3);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestStandardTuple(void)
{
	PrintLineSeparator();

	tuple<wstring,wstring,int>									Tuple(L"Timmy",L"Anderson",12);

	wprintf_s(L"TUPLE [%ls %ls] AGE [%d] !\n",get<0>(Tuple).c_str(),get<1>(Tuple).c_str(),get<2>(Tuple));

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestStandardTypeFunctions();
	//TestSimpleTypeFunction();
	//TestSimpleConditionalTypeFunction();
	//TestAliases();
	//TestHasOperators1();
	TestHasOperators2();
	//TestHasFieldXXX();
	//TestTypeFunctionWithFunctor();
	//TestTypeTraits();
	//TestConditionalTypeFunction();
	//TestSelectTypeFunction();
	//TestSelectVariadicTypeFunction();
	//TestTemplateClassRecursion();
	//TestTemplateFunctionRecursion();
	//TestStandardEnableIf();
	//TestCustomEnableIf();
	//TestHasFunctionXXX();
	//TestHasFunctionXXXFromBook();
	//TestTuple();
	//TestVariadicTemplate();
	//TestVariadicTemplateFunction();
	//TestVariadicFunctionPrintf();
	//TestVariadicTemplateMethod();
	//TestVariadicTemplateClass();
	//TestVariadicTemplateFunctionExpressions();
	//TestDerivedVariadicTemplate();
	//TestCallAnotherFunction();
	//TestMyTuple();
	//TestStandardTuple();

	ShowExitLine();

	return(0);
}
//-----------------------------------------------------------------------------