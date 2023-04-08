//-----------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <iostream>
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
	wcout << L"IS POLYMORPHIC <int> [" << is_polymorphic<int>::value << L"] !" << endl;
	wcout << L"IS POLYMORPHIC <wstring> [" << is_polymorphic<wstring>::value << L"] !" << endl;
	wcout << L"IS POLYMORPHIC <CNonPolymorphicType> [" << is_polymorphic<CNonPolymorphicType>::value << L"] !" << endl;
	wcout << L"IS POLYMORPHIC <CPolymorphicType> [" << is_polymorphic<CPolymorphicType>::value << L"] !" << endl;

	// !!! STRUCTURE [underlying_type<T>] je TYPE FUNCTION.
	wcout << "UNDERLYING TYPE <EEnum1> [" << ConvertStringToWideString(typeid(underlying_type<EEnum1>::type).name()) << L"] !" << endl;
	wcout << "UNDERLYING TYPE <EEnum2> [" << ConvertStringToWideString(typeid(underlying_type<EEnum2>::type).name()) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSimpleTypeFunction(void)
{
	PrintLineSeparator();

	wcout << "CArrayTypeFunction<double,10>::Type [" << ConvertStringToWideString(typeid(CArrayTypeFunction<double,10>::Type).name()) << L"] !" << endl;
	wcout << L"CArrayTypeFunction<double,10>::Size [" << CArrayTypeFunction<double,10>::Size << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSimpleConditionalTypeFunction(void)
{
	PrintLineSeparator();

	wcout << "CBiggerTypeTypeFunction<int,int>::Type [" << ConvertStringToWideString(typeid(CBiggerTypeTypeFunction<int,int>::BiggerType).name()) << L"] !" << endl;
	wcout << "CBiggerTypeTypeFunction<int,double>::Type [" << ConvertStringToWideString(typeid(CBiggerTypeTypeFunction<int,double>::BiggerType).name()) << L"] !" << endl;
	wcout << "CBiggerTypeTypeFunction<int,char>::Type [" << ConvertStringToWideString(typeid(CBiggerTypeTypeFunction<int,char>::BiggerType).name()) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestAliases(void)
{
	PrintLineSeparator();

	wcout << "IsBigger<int,double>::Type [" << ConvertStringToWideString(typeid(IsBigger<int,double>).name()) << L"] !" << endl;
	wcout << "IsBiggerAsInt<double>::Type [" << ConvertStringToWideString(typeid(IsBiggerAsInt<double>).name()) << L"] !" << endl;

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
	wcout << L"HasOperatorPlus(IntValue1,IntValue2) [" << ((HasOperatorPlus(IntValue1,IntValue2)==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	// Vracia TRUE.
	wcout << L"HasOperatorPlus(IntValue1,DoubleValue1) [" << ((HasOperatorPlus(IntValue1,DoubleValue1)==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	// Vracia TRUE.
	wcout << L"HasOperatorPlus(DoubleValue1,DoubleValue2) [" << ((HasOperatorPlus(DoubleValue1,DoubleValue2)==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	// Vracia FALSE.
	wcout << L"HasOperatorPlus(StringValue1,IntValue1) [" << ((HasOperatorPlus(StringValue1,IntValue1)==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	// Vracia TRUE.
	wcout << L"HasOperatorPlus(StringValue1,StringValue2) [" << ((HasOperatorPlus(StringValue1,StringValue2)==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	// Vracia TRUE.
	wcout << L"HasOperatorPlus(ClassWithCustomOperators1,ClassWithCustomOperators2) [" << ((HasOperatorPlus(ClassWithCustomOperators1,ClassWithCustomOperators2)==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	// Vracia TRUE.
	wcout << L"HasOperatorPlus(ClassWithCustomOperators1,IntValue1) [" << ((HasOperatorPlus(ClassWithCustomOperators1,IntValue1)==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	// !!! Vracia FALSE, pretoze je pretazeny iba OPERATOR (CClassWithCustomOperators+INT) a NIE (INT+CClassWithCustomOperators).
	wcout << L"HasOperatorPlus(IntValue1,ClassWithCustomOperators1) [" << ((HasOperatorPlus(IntValue1,ClassWithCustomOperators1)==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	// !!!!! Vracia TRUE, pretoze C++ AUTOMATICKY KONVERTUJE DOUBLE na INT, aj ked pri pouziti hodi COMPILER WARNING.
	wcout << L"HasOperatorPlus(ClassWithCustomOperators1,DoubleValue1) [" << ((HasOperatorPlus(ClassWithCustomOperators1,DoubleValue1)==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	PrintLineSeparator();

	// Vracia TRUE.
	wcout << L"HasOperatorDivide(IntValue1,IntValue2) [" << ((HasOperatorDivide(IntValue1,IntValue2)==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	// Vracia TRUE.
	wcout << L"HasOperatorDivide(IntValue1,DoubleValue1) [" << ((HasOperatorDivide(IntValue1,DoubleValue1)==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	// Vracia TRUE.
	wcout << L"HasOperatorDivide(DoubleValue1,DoubleValue2) [" << ((HasOperatorDivide(DoubleValue1,DoubleValue2)==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	// Vracia FALSE.
	wcout << L"HasOperatorDivide(StringValue1,IntValue1) [" << ((HasOperatorDivide(StringValue1,IntValue1)==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	// Vracia FALSE.
	wcout << L"HasOperatorDivide(StringValue1,StringValue2) [" << ((HasOperatorDivide(StringValue1,StringValue2)==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	// Vracia FALSE.
	wcout << L"HasOperatorDivide(ClassWithCustomOperators1,ClassWithCustomOperators2) [" << ((HasOperatorDivide(ClassWithCustomOperators1,ClassWithCustomOperators2)==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	// Vracia FALSE.
	wcout << L"HasOperatorDivide(ClassWithCustomOperators1,IntValue1) [" << ((HasOperatorDivide(ClassWithCustomOperators1,IntValue1)==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	// Vracia FALSE.
	wcout << L"HasOperatorDivide(IntValue1,ClassWithCustomOperators1) [" << ((HasOperatorDivide(IntValue1,ClassWithCustomOperators1)==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	// Vracia FALSE.
	wcout << L"HasOperatorDivide(ClassWithCustomOperators1,DoubleValue1) [" << ((HasOperatorDivide(ClassWithCustomOperators1,DoubleValue1)==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

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
	wcout << L"HasOperatorPlus(int,int) [" << ((CHasOperators<int,int>::IsOperatorPlusDefined==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	// Vracia TRUE.
	wcout << L"HasOperatorPlus(int,double) [" << ((CHasOperators<int,double>::IsOperatorPlusDefined==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	// Vracia TRUE.
	wcout << L"HasOperatorPlus(double,double) [" << ((CHasOperators<double,double>::IsOperatorPlusDefined==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	// Vracia FALSE.
	wcout << L"HasOperatorPlus(string,int) [" << ((CHasOperators<string,int>::IsOperatorPlusDefined==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	// Vracia TRUE.
	wcout << L"HasOperatorPlus(string,string) [" << ((CHasOperators<string,string>::IsOperatorPlusDefined==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	// Vracia TRUE.
	wcout << L"HasOperatorPlus(CClassWithCustomOperators,CClassWithCustomOperators) [" << ((CHasOperators<CClassWithCustomOperators,CClassWithCustomOperators>::IsOperatorPlusDefined==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	// Vracia TRUE.
	wcout << L"HasOperatorPlus(CClassWithCustomOperators,int) [" << ((CHasOperators<CClassWithCustomOperators,int>::IsOperatorPlusDefined==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	// !!! Vracia FALSE, pretoze je pretazeny iba OPERATOR (CClassWithCustomOperators+INT) a NIE (INT+CClassWithCustomOperators).
	wcout << L"HasOperatorPlus(int,CClassWithCustomOperators) [" << ((CHasOperators<int,CClassWithCustomOperators>::IsOperatorPlusDefined==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	// !!!!! Vracia TRUE, pretoze C++ AUTOMATICKY KONVERTUJE DOUBLE na INT, aj ked pri pouziti hodi COMPILER WARNING.
	wcout << L"HasOperatorPlus(CClassWithCustomOperators,double) [" << ((CHasOperators<CClassWithCustomOperators,double>::IsOperatorPlusDefined==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	PrintLineSeparator();

	// Vracia TRUE.
	wcout << L"HasOperatorDivide(int,int) [" << ((CHasOperators<int,int>::IsOperatorDivideDefined==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	// Vracia TRUE.
	wcout << L"HasOperatorDivide(int,double) [" << ((CHasOperators<int,double>::IsOperatorDivideDefined==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	// Vracia TRUE.
	wcout << L"HasOperatorDivide(double,double) [" << ((CHasOperators<double,double>::IsOperatorDivideDefined==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	// Vracia FALSE.
	wcout << L"HasOperatorDivide(string,int) [" << ((CHasOperators<string,int>::IsOperatorDivideDefined==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	// Vracia FALSE.
	wcout << L"HasOperatorDivide(string,string) [" << ((CHasOperators<string,string>::IsOperatorDivideDefined==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	// Vracia FALSE.
	wcout << L"HasOperatorDivide(CClassWithCustomOperators,CClassWithCustomOperators) [" << ((CHasOperators<CClassWithCustomOperators,CClassWithCustomOperators>::IsOperatorDivideDefined==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	// Vracia FALSE.
	wcout << L"HasOperatorDivide(CClassWithCustomOperators,int) [" << ((CHasOperators<CClassWithCustomOperators,int>::IsOperatorDivideDefined==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	// Vracia FALSE.
	wcout << L"HasOperatorDivide(int,CClassWithCustomOperators) [" << ((CHasOperators<int,CClassWithCustomOperators>::IsOperatorDivideDefined==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	// Vracia FALSE.
	wcout << L"HasOperatorDivide(CClassWithCustomOperators,double) [" << ((CHasOperators<CClassWithCustomOperators,double>::IsOperatorDivideDefined==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestHasFieldXXX(void)
{
	PrintLineSeparator();

	wcout << L"CLASS [SStructureWithFieldXXX] has FIELD 'XXX' defined [" << ((CHasFieldXXX<SStructureWithFieldXXX>::IfFieldDefined==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	
	wcout << L"CLASS [SStructureWithoutFieldXXX] has FIELD 'XXX' defined [" << ((CHasFieldXXX<SStructureWithoutFieldXXX>::IfFieldDefined==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

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

	wcout << L"Result1 [" << Result1 << L"] !" << endl;
	wcout << L"Result2 [" << Result2 << L"] !" << endl;
	wcout << L"Result3 [" << Result3 << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestTypeTraits(void)
{
	PrintLineSeparator();

	wcout << "CMyTypeTraits<CMyTypeWithTraits1>::Value [" << ConvertStringToWideString(typeid(CMyTypeTraits<CMyTypeWithTraits1>::Value).name()) << L"] !" << endl;
	wcout << "CMyTypeTraits<CMyTypeWithTraits1>::Pointer [" << ConvertStringToWideString(typeid(CMyTypeTraits<CMyTypeWithTraits1>::Pointer).name()) << L"] !" << endl;
	wcout << "CMyTypeTraits<CMyTypeWithTraits1>::Reference [" << ConvertStringToWideString(typeid(CMyTypeTraits<CMyTypeWithTraits1>::Reference).name()) << L"] !" << endl;

	PrintLineSeparator();

	wcout << "CMyTypeTraits<CMyTypeWithTraits2>::Value [" << ConvertStringToWideString(typeid(CMyTypeTraits<CMyTypeWithTraits2>::Value).name()) << L"] !" << endl;
	wcout << "CMyTypeTraits<CMyTypeWithTraits2>::Pointer [" << ConvertStringToWideString(typeid(CMyTypeTraits<CMyTypeWithTraits2>::Pointer).name()) << L"] !" << endl;
	wcout << "CMyTypeTraits<CMyTypeWithTraits2>::Reference [" << ConvertStringToWideString(typeid(CMyTypeTraits<CMyTypeWithTraits2>::Reference).name()) << L"] !" << endl;

	PrintLineSeparator();

	vector<int>													Vector{1,2,3};

	// Pouzitie TYPE TRAITS.
	wcout << "iterator_traits<vector<int>::iterator>::difference_type [" << ConvertStringToWideString(typeid(iterator_traits<vector<int>::iterator>::difference_type).name()) << L"] !" << endl;

	PrintLineSeparator();

	// !!! Namiesto TYPE TRAITS je mozne pouzit KEYWORD [decltype()].
	wcout << "decltype(Vector.end()-Vector.begin()) [" << ConvertStringToWideString(typeid(decltype(Vector.end()-Vector.begin())).name()) << L"] !" << endl;

	PrintLineSeparator();

	// !!! Takisto je mozne namiesto TYPE TRAITS pouzit KEYWORD [auto].
	auto														IteratorDifference=Vector.end()-Vector.begin();

	wcout << "IteratorDifference [" << ConvertStringToWideString(typeid(IteratorDifference).name()) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestConditionalTypeFunction(void)
{
	PrintLineSeparator();

	wcout << "CConditional<true,int,double>::TYPE [" << ConvertStringToWideString(typeid(CConditional<true,int,double>::TYPE).name()) << L"] !" << endl;
	wcout << "CConditional<false,int,double>::TYPE [" << ConvertStringToWideString(typeid(CConditional<false,int,double>::TYPE).name()) << L"] !" << endl;

	PrintLineSeparator();

	wcout << "conditional<true,int,double>::type [" << ConvertStringToWideString(typeid(conditional<true,int,double>::type).name()) << L"] !" << endl;
	wcout << "conditional<false,int,double>::type [" << ConvertStringToWideString(typeid(conditional<false,int,double>::type).name()) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSelectTypeFunction(void)
{
	PrintLineSeparator();

	wcout << "CSelect<1,bool,int,double,wstring> [" << ConvertStringToWideString(typeid(CSelect<1,bool,int,double,wstring>::TYPE).name()) << L"] !" << endl;
	wcout << "CSelect<2,bool,int,double,wstring> [" << ConvertStringToWideString(typeid(CSelect<2,bool,int,double,wstring>::TYPE).name()) << L"] !" << endl;
	wcout << "CSelect<3,bool,int,double,wstring> [" << ConvertStringToWideString(typeid(CSelect<3,bool,int,double,wstring>::TYPE).name()) << L"] !" << endl;
	wcout << "CSelect<4,bool,int,double,wstring> [" << ConvertStringToWideString(typeid(CSelect<4,bool,int,double,wstring>::TYPE).name()) << L"] !" << endl;

	// !!! INDEX je MIMO hranic <1,4>. Kedze do TEMPLATE bol pridany STATIC ASSERT, tak COMPILER hodi ERROR.
	//wcout << "CSelect<100,bool,int,double,wstring> [" << ConvertStringToWideString(typeid(CSelect<100,bool,int,double,wstring>::TYPE).name()) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSelectVariadicTypeFunction(void)
{
	PrintLineSeparator();

	wcout << "CSelectVariadic<0,bool,int,double,wstring> [" << ConvertStringToWideString(typeid(CSelectVariadic<0,bool,int,double,wstring>::TYPE).name()) << L"] !" << endl;
	wcout << "CSelectVariadic<1,bool,int,double,wstring> [" << ConvertStringToWideString(typeid(CSelectVariadic<1,bool,int,double,wstring>::TYPE).name()) << L"] !" << endl;
	wcout << "CSelectVariadic<2,bool,int,double,wstring> [" << ConvertStringToWideString(typeid(CSelectVariadic<2,bool,int,double,wstring>::TYPE).name()) << L"] !" << endl;
	wcout << "CSelectVariadic<3,bool,int,double,wstring> [" << ConvertStringToWideString(typeid(CSelectVariadic<3,bool,int,double,wstring>::TYPE).name()) << L"] !" << endl;

	// !!! INDEX je MIMO hranic definovanych poctom PARAMETERS a preto COMPILER hodi COMPILATION ERROR.
	//wcout << "CSelectVariadic<100,bool,int,double,wstring> [" << ConvertStringToWideString(typeid(CSelectVariadic<100,bool,int,double,wstring>::TYPE).name()) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestTemplateClassRecursion(void)
{
	PrintLineSeparator();

	int															Value1=CTemplateClassRecursion<10>::VALUE;

	wcout << L"Value1 [" << Value1 << L"] !" << endl;

	int															Value2=CTemplateClassRecursion<5>::VALUE;

	wcout << L"Value2 [" << Value2 << L"] !" << endl;

	/*
	// !!! Sposobi nekonecnu RECURSION a tym padom aj COMPILATION ERROR.
	int															Value3=CTemplateClassRecursion<-1>::VALUE;

	wcout << L"Value3 [" << Value3 << L"] !" << endl;
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

	wcout << L"Value1 [" << Value1 << L"] !" << endl;

	int															Value2=TemplateFunctionRecursion<5>();

	wcout << L"Value2 [" << Value2 << L"] !" << endl;

	/*
	// !!! Sposobi nekonecnu RECURSION a tym padom aj COMPILATION ERROR.
	int															Value3=TemplateFunctionRecursion<-1>();

	wcout << L"Value3 [" << Value3 << L"] !" << endl;
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

	wcout << L"ReturnString1 [" << ReturnString1 << L"] !" << endl;

	/*
	// !!! Hodi COMPILATION ERROR, pretoze INT NIE JE CLASS.
	int															ReturnInt1=Class.EnableIfInReturnValue(12);

	wcout << L"ReturnInt1 [" << ReturnInt1 << L"] !" << endl;
	*/

	wstring														ReturnString2=Class.EnableIfInParameter<wstring>(ClassType2);

	wcout << L"ReturnString2 [" << ReturnString2 << L"] !" << endl;

	/*
	// !!! Hodi COMPILATION ERROR, pretoze INT NIE JE CLASS.
	int															ReturnInt2=Class.EnableIfInParameter<int>(12);

	wcout << L"ReturnInt2 [" << ReturnInt2 << L"] !" << endl;
	*/

	wstring														ReturnString3=Class.EnableIfInTypeParameter(ClassType3);

	wcout << L"ReturnString3 [" << ReturnString3 << L"] !" << endl;

	/*
	// !!! Hodi COMPILATION ERROR, pretoze INT NIE JE CLASS.
	int															ReturnInt3=Class.EnableIfInTypeParameter(12);

	wcout << L"ReturnInt3 [" << ReturnInt3 << L"] !" << endl;
	*/

	PrintLineSeparator();

	wstring														ReturnString4=EnableIfInReturnValue(ClassType4);

	wcout << L"ReturnString4 [" << ReturnString4 << L"] !" << endl;

	/*
	// !!! Hodi COMPILATION ERROR, pretoze INT NIE JE CLASS.
	int															ReturnInt4=EnableIfInReturnValue(42);

	wcout << L"ReturnInt4 [" << ReturnInt4 << L"] !" << endl;
	*/

	wstring														ReturnString5=EnableIfInParameter<wstring>(ClassType5);

	wcout << L"ReturnString5 [" << ReturnString5 << L"] !" << endl;

	/*
	// !!! Hodi COMPILATION ERROR, pretoze INT NIE JE CLASS.
	int															ReturnInt5=EnableIfInParameter<int>(15);

	wcout << L"ReturnInt5 [" << ReturnInt5 << L"] !" << endl;
	*/

	wstring														ReturnString6=EnableIfInTypeParameter(ClassType6);

	wcout << L"ReturnString6 [" << ReturnString6 << L"] !" << endl;

	/*
	// !!! Hodi COMPILATION ERROR, pretoze INT NIE JE CLASS.
	int															ReturnInt6=EnableIfInTypeParameter(12);

	wcout << L"ReturnInt6 [" << ReturnInt6 << L"] !" << endl;
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

	wcout << L"ReturnString1 [" << ReturnString1 << L"] !" << endl;

	/*
	// !!! Hodi COMPILATION ERROR, pretoze INT NIE JE CLASS.
	int															ReturnInt1=Class.EnableIfInReturnValue(12);

	wcout << L"ReturnInt1 [" << ReturnInt1 << L"] !" << endl;
	*/

	wstring														ReturnString2=Class.EnableIfInParameter<wstring>(ClassType2);

	wcout << L"ReturnString2 [" << ReturnString2 << L"] !" << endl;

	/*
	// !!! Hodi COMPILATION ERROR, pretoze INT NIE JE CLASS.
	int															ReturnInt2=Class.EnableIfInParameter<int>(12);

	wcout << L"ReturnInt2 [" << ReturnInt2 << L"] !" << endl;
	*/

	wstring														ReturnString3=Class.EnableIfInTypeParameter(ClassType3);

	wcout << L"ReturnString3 [" << ReturnString3 << L"] !" << endl;

	/*
	// !!! Hodi COMPILATION ERROR, pretoze INT NIE JE CLASS.
	int															ReturnInt3=Class.EnableIfInTypeParameter(12);

	wcout << L"ReturnInt3 [" << ReturnInt3 << L"] !" << endl;
	*/

	PrintLineSeparator();

	wstring														ReturnString4=CustomEnableIfInReturnValue(ClassType4);

	wcout << L"ReturnString4 [" << ReturnString4 << L"] !" << endl;

	/*
	// !!! Hodi COMPILATION ERROR, pretoze INT NIE JE CLASS.
	int															ReturnInt4=CustomEnableIfInReturnValue(42);

	wcout << L"ReturnInt4 [" << ReturnInt4 << L"] !" << endl;
	*/

	wstring														ReturnString5=CustomEnableIfInParameter<wstring>(ClassType5);

	wcout << L"ReturnString5 [" << ReturnString5 << L"] !" << endl;

	/*
	// !!! Hodi COMPILATION ERROR, pretoze INT NIE JE CLASS.
	int															ReturnInt5=CustomEnableIfInParameter<int>(15);

	wcout << L"ReturnInt5 [" << ReturnInt5 << L"] !" << endl;
	*/

	wstring														ReturnString6=CustomEnableIfInTypeParameter(ClassType6);

	wcout << L"ReturnString6 [" << ReturnString6 << L"] !" << endl;

	/*
	// !!! Hodi COMPILATION ERROR, pretoze INT NIE JE CLASS.
	int															ReturnInt6=CustomEnableIfInTypeParameter(12);

	wcout << L"ReturnInt6 [" << ReturnInt6 << L"] !" << endl;
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

	wcout << L"HasMethodXXX(IntValue) [" << ((HasMethodXXX(IntValue)==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	wcout << L"HasMethodXXX(StringValue) [" << ((HasMethodXXX(StringValue)==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	wcout << L"HasMethodXXX(TypeWithMethodXXXValue) [" << ((HasMethodXXX(TypeWithMethodXXXValue)==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"SCheckFunctionXXX<int>::RESULT [" << ((SCheckFunctionXXX<int>::RESULT==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	wcout << L"SCheckFunctionXXX<wstring>::RESULT [" << ((SCheckFunctionXXX<wstring>::RESULT==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	wcout << L"SCheckFunctionXXX<CTypeWithMethodXXX>::RESULT [" << ((SCheckFunctionXXX<CTypeWithMethodXXX>::RESULT==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestHasFunctionXXXFromBook(void)
{
	PrintLineSeparator();

	wcout << L"SHasFunctionXXX<int>::value [" << ((SHasFunctionXXX<int>::value==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	wcout << L"SHasFunctionXXX<wstring>::value [" << ((SHasFunctionXXX<wstring>::value==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	wcout << L"SHasFunctionXXX<CTypeWithMethodXXX>::value [" << ((SHasFunctionXXX<CTypeWithMethodXXX>::value==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"SFunctionXXXCheck<int>::RESULT [" << ((SFunctionXXXCheck<int>::RESULT==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	wcout << L"SFunctionXXXCheck<wstring>::RESULT [" << ((SFunctionXXXCheck<wstring>::RESULT==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	wcout << L"SFunctionXXXCheck<CTypeWithMethodXXX>::RESULT [" << ((SFunctionXXXCheck<CTypeWithMethodXXX>::RESULT==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

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

	wcout << L"Tuple1 [" << Tuple1.MValue << L"] [" << Tuple1.GetBase()->MValue << L"] [" << Tuple1.GetBase()->GetBase()->MValue << L"] [" << Tuple1.GetBase()->GetBase()->GetBase()->MValue << L"] !" << endl;

	Tuple1.Print(L"Tuple1 ",L" !\n");

	bool														Item1=STupleItem<bool,0>::GetItem(Tuple1);
	int															Item2=STupleItem<int,1>::GetItem(Tuple1);
	double														Item3=STupleItem<double,2>::GetItem(Tuple1);
	wstring														Item4=STupleItem<wstring,3>::GetItem(Tuple1);

	wcout << L"Tuple1 [" << Item1 << L"] [" << Item2 << L"] [" << Item3 << L"] [" << Item4 << L"] !" << endl;

	bool														ConstItem1=STupleItem<bool,0>::GetItem(Tuple2);
	int															ConstItem2=STupleItem<int,1>::GetItem(Tuple2);
	double														ConstItem3=STupleItem<double,2>::GetItem(Tuple2);
	wstring														ConstItem4=STupleItem<wstring,3>::GetItem(Tuple2);

	wcout << L"Tuple2 [" << ConstItem1 << L"] [" << ConstItem2 << L"] [" << ConstItem3 << L"] [" << ConstItem4 << L"] !" << endl;

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

	wcout << L"VARIADIC TEMPLATE [" << FirstName1 << L" " << LastName1 << L"] AGE [" << Age1 << L"] !" << endl;

	PrintLineSeparator();

	const CString&												FirstName2=VariadicTemplateWithCString.GetItem<0>();
	const CString&												LastName2=VariadicTemplateWithCString.GetItem<1>();
	const int&													Age2=VariadicTemplateWithCString.GetItem<2>();
	
	wcout << L"VARIADIC TEMPLATE with CString [" << FirstName2.GetValue() << L" " << LastName2.GetValue() << L"] AGE [" << Age2 << L"] !" << endl;

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

	wcout << L"NumberOfTypeParameters [" << NumberOfTypeParameters << L"] !" << endl;
}
//-----------------------------------------------------------------------------
template<typename... TTypes>
void FinishProcessing(TTypes...)
{
	wcout << L"FinishProcessing() - PROCESSING FINISHED !" << endl;
}
//-----------------------------------------------------------------------------
template<typename TType>
TType ProcessItem(TType TypeParameter)
{
	wcout << L"ProcessItem() - PARAMETER [" << TypeParameter << L"] !" << endl;

	return(TypeParameter);
}
//-----------------------------------------------------------------------------
template<typename... TTypes>
void UnpackTypeParameterPack(TTypes... TypeParameters)
{
	wcout << L"UnpackTypeParameterPack() - PROCESSING STARTED !" << endl;

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
		wcout << L"\nEXCEPTION [" << Exception.GetMessage().c_str() << L"] !" << endl;
	}

	PrintLineSeparator();

	try
	{
		// Chyba posledny PARAMETER.
		PrintfByIndex(L"NAME [!% !%] AGE [!%] !!\n",wstring(L"Timmy"),wstring(L"Anderson"));
	}
	catch(const CException& Exception)
	{
		wcout << L"\nEXCEPTION [" << Exception.GetMessage().c_str() << L"] !" << endl;
	}

	PrintLineSeparator();

	try
	{
		// Jeden PARAMETER je navyse.
		PrintfByIndex(L"NAME [!% !%] AGE [!%] !!\n",wstring(L"Timmy"),wstring(L"Anderson"),12,12);
	}
	catch(const CException& Exception)
	{
		wcout << L"\nEXCEPTION [" << Exception.GetMessage().c_str() << L"] !" << endl;
	}

	PrintLineSeparator();

	try
	{
		// Chybny format.
		PrintfByIndex(L" !");
	}
	catch(const CException& Exception)
	{
		wcout << L"\nEXCEPTION [" << Exception.GetMessage().c_str() << L"] !" << endl;
	}

	PrintLineSeparator();

	try
	{
		PrintfByIterator(L"NAME [!% !%] AGE [!%] !!\n",wstring(L"Timmy"),wstring(L"Anderson"),12);
	}
	catch(const CException& Exception)
	{
		wcout << L"\nEXCEPTION [" << Exception.GetMessage().c_str() << L"] !" << endl;
	}

	PrintLineSeparator();

	try
	{
		// Chyba posledny PARAMETER.
		PrintfByIterator(L"NAME [!% !%] AGE [!%] !!\n",wstring(L"Timmy"),wstring(L"Anderson"));
	}
	catch(const CException& Exception)
	{
		wcout << L"\nEXCEPTION [" << Exception.GetMessage().c_str() << L"] !" << endl;
	}

	PrintLineSeparator();

	try
	{
		// Jeden PARAMETER je navyse.
		PrintfByIterator(L"NAME [!% !%] AGE [!%] !!\n",wstring(L"Timmy"),wstring(L"Anderson"),12,12);
	}
	catch(const CException& Exception)
	{
		wcout << L"\nEXCEPTION [" << Exception.GetMessage().c_str() << L"] !" << endl;
	}

	PrintLineSeparator();

	try
	{
		// Chybny format.
		PrintfByIterator(L" !");
	}
	catch(const CException& Exception)
	{
		wcout << L"\nEXCEPTION [" << Exception.GetMessage().c_str() << L"] !" << endl;
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

	wcout << L"ComplexClass [" << ComplexClass.GetFirstItem().c_str() << L"] [" << ComplexClass.GetBase()->GetFirstItem().c_str() << L"] [" << ComplexClass.GetBase()->GetBase()->GetFirstItem() << L"] !" << endl;

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
	// !!! G++ hodi WARNING.
#ifdef _MSC_VER
	PrintVariadicTemplateFunction(&Prefix,&Postfix,(TypeParameters+(++Addition))...);
#endif
}
//-----------------------------------------------------------------------------
template<typename TType>
TType AddValues(TType Value1, TType Value2)
{
	TType														Result=Value1+Value2;

	wcout << L"[" << Value1 << L"] + [" << Value2 << "] = [" << Result << "] !" << endl;

	return(Result);
}
//-----------------------------------------------------------------------------
#ifdef _MSC_VER
template<typename TType, typename... TTypes>
void VariadicTemplatesAddValues(TType Value, TTypes... Values)
{
	wstring														Prefix=L"EXPRESSIONS ADDITION TEST";
	wstring														Postfix=L" !\n";

	// !!!!! C++ pre hodnoty (10,100,200,300) generuje CODE [PrintVariadicTemplateFunction(&Prefix,&Postfix,AddValues<int>(10,100),AddValues<int>(10,200),AddValues<int>(10,300))].
	// !!! G++ hodi WARNING.
	PrintVariadicTemplateFunction(&Prefix,&Postfix,(AddValues<TType>(Value,Values))...);
}
#endif
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
		wcout << L"RESULT [TRUE] !" << endl;
	}
	else
	{
		wcout << L"RESULT [FALSE] !" << endl;
	}

	// Inicializacia VECTOR.
	vector<bool>												Vector{GetFirst(Parameters)...};

	for(bool Value : Vector)
	{
		wcout << L"VALUE [" << Value << L"] !" << endl;
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

#ifdef _MSC_VER
	VariadicTemplatesAddValues(10,100,200,300);
#endif

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

	wcout << L"NAME [" << Reference1.GetValue() << L"] AGE [" << Reference2.GetValue() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void PrintName(const wstring& FirstName, const wstring& LastName, int Age)
{
	wcout << L"NAME [" << FirstName << L" " << LastName << L"] AGE [" << Age << L"] !" << endl;
}
//-----------------------------------------------------------------------------
void PrintNameClass(const CName& Name)
{
	wcout << L"NAME [" << Name.GetFirstName() << L" " << Name.GetLastName() << L"] AGE [" << Name.GetAge() << L"] !" << endl;
}
//-----------------------------------------------------------------------------
template<typename TFunctionToCall, typename... TTypes>
void CallerFunction(TFunctionToCall&& FunctionToCall, TTypes&&... TypeParameters)
{
	wcout << L"CallerFunction() CALLED !" << endl;

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

	wcout << L"TUPLE [" << Tuple.GetValue() << L" " << Tuple.GetBase().GetValue() << L"] AGE [" << Tuple.GetBase().GetBase().GetValue() << L"] !" << endl;
	
	Tuple.Print(L"TUPLE");

	wstring														FirstName1=CTuple<wstring,wstring,int>::StaticGetItem<0>(Tuple);
	wstring														LastName1=CTuple<wstring,wstring,int>::StaticGetItem<1>(Tuple);
	int															Age1=CTuple<wstring,wstring,int>::StaticGetItem<2>(Tuple);

	wcout << L"TUPLE [" << FirstName1 << L" " << LastName1 << L"] AGE [" << Age1 << L"] !" << endl;

	const wstring&												FirstName2=Tuple.GetItem<0>();
	const wstring&												LastName2=Tuple.GetItem<1>();
	const int&													Age2=Tuple.GetItem<2>();

	wcout << L"TUPLE [" << FirstName2 << L" " << LastName2 << L"] AGE [" << Age2 << L"] !" << endl;

	PrintLineSeparator();

	const CString&												FirstName3=TupleWithCString.GetItem<0>();
	const CString&												LastName3=TupleWithCString.GetItem<1>();
	const int&													Age3=TupleWithCString.GetItem<2>();
	
	wcout << L"TUPLE with CString [" << FirstName3.GetValue() << L" " << LastName3.GetValue() << L"] AGE [" << Age3 << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestStandardTuple(void)
{
	PrintLineSeparator();

	tuple<wstring,wstring,int>									Tuple(L"Timmy",L"Anderson",12);

	wcout << L"TUPLE [" << get<0>(Tuple) << L" " << get<1>(Tuple) << L"] AGE [" << get<2>(Tuple) << L"] !" << endl;

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
	//TestHasOperators2();
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
	TestVariadicTemplateFunction();
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