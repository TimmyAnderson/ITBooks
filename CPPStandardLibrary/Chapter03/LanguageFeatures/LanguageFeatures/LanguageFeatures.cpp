//-------------------------------------------------------------------------------------------------------
#include <vector>
#include <list>
#include <typeinfo>
#include <type_traits>
#include <complex>
#include <iostream>
#include <tuple>
#include "MyDebug.h"
#include "SName.h"
#include "CName1.h"
#include "CName2.h"
#include "CName3.h"
#include "CCollection.h"
#include "CClassWithExplicitConstructor.h"
#include "CItem1.h"
#include "CItem2.h"
#include "CItem3.h"
#include "CCustomCollection1.h"
#include "CCustomCollection2.h"
#include "CCustomCollection3.h"
#include "CCustomCollection4.h"
#include "CConstExpressionMethod.h"
#include "CMyTuple.h"
#include "CClassWithTemplateMethods.h"
#include "CNestedTemplateClass.h"
#include "ENonScopedEnumeration.h"
#include "EScopedEnumeration.h"
#include "CTemplateWithType.h"
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
void TestDoubleGreaterSign(void)
{
	PrintLineSeparator();

	// Medzi znakmi '>>' nie je nutna medzera.
	vector<list<int>>											VectorList;
	list<int>													List1;
	list<int>													List2;
	
	List1.push_back(1);
	List1.push_back(2);
	List1.push_back(3);

	List2.push_back(9);
	List2.push_back(8);
	List2.push_back(7);

	VectorList.push_back(List1);
	VectorList.push_back(List2);

	for(vector<list<int>>::iterator Iterator1=VectorList.begin();Iterator1!=VectorList.end();Iterator1++)
	{
		int														Counter=0;

		for(list<int>::iterator Iterator2=Iterator1->begin();Iterator2!=Iterator1->end();Iterator2++,Counter++)
		{
			wcout << L"VectorList[" << (Iterator1-VectorList.begin()) << L"][" << (Counter) << L"]=[" << (*Iterator2) << L"] !" << endl;
		}
	}

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void NullPtrFunction1(int Value)
{
	wcout << L"NullPtrFunction1(int Value) CALLED with VALUE [" << Value << L"] !" << endl;
}
//-------------------------------------------------------------------------------------------------------
void NullPtrFunction1(void* Value)
{
	wcout << L"NullPtrFunction1(void* Value) CALLED with VALUE [" << Value << L"] !" << endl;
}
//-------------------------------------------------------------------------------------------------------
void NullPtrFunction2(void* Value)
{
	wcout << L"NullPtrFunction2(void* Value) CALLED with VALUE [" << Value << L"] !" << endl;
}
//-------------------------------------------------------------------------------------------------------
// !!! TYPE [nullptr_t] je standardny TYPE, ktory je deklarovany v HEADER [cstddef]. Tento TYPE vsak NEMA ZIADNE MEMBERS.
void NullPtrFunction2(nullptr_t Value)
{
	wcout << L"NullPtrFunction2(nullptr_t Value) CALLED with VALUE [" << (void*)(Value) << L"] !" << endl;
}
//-------------------------------------------------------------------------------------------------------
// !!! TYPE [nullptr_t] je standardny TYPE, ktory je deklarovany v HEADER [cstddef]. Tento TYPE vsak NEMA ZIADNE MEMBERS.
void NullPtrFunction3(nullptr_t Value)
{
	wcout << L"NullPtrFunction3(nullptr_t Value) CALLED with VALUE [" << (void*)(Value) << L"] !" << endl;
}
//-------------------------------------------------------------------------------------------------------
void NullPtrFunction4(int Value)
{
	wcout << L"NullPtrFunction4(int Value) CALLED with VALUE [" << Value << L"] !" << endl;
}
//-------------------------------------------------------------------------------------------------------
void TestNullPtrKeyword(void)
{
	PrintLineSeparator();

	// Vola FUNCTION [void NullPtrFunction1(int Value)].
	NullPtrFunction1(0);
	// Vola FUNCTION [void NullPtrFunction1(int Value)].
	// !!!!! G++ hodi COMPILER ERROR.
	//NullPtrFunction1(NULL);
	// Vola FUNCTION [void NullPtrFunction1(void* Value)].
	NullPtrFunction1(nullptr);

	// Vola FUNCTION [void NullPtrFunction2(nullptr_t Value)].
	NullPtrFunction2(nullptr);

	nullptr_t													Value=nullptr;

	// Vola FUNCTION [void NullPtrFunction2(nullptr_t Value)].
	NullPtrFunction2(Value);

	// Vola FUNCTION [void NullPtrFunction2(void* Value)].
	NullPtrFunction2((void*) nullptr);

	// Vola FUNCTION [void NullPtrFunction3(nullptr_t Value)].
	NullPtrFunction3(NULL);
	// Vola FUNCTION [void NullPtrFunction3(nullptr_t Value)].
	NullPtrFunction3(0);

	// !!! Hodi ERROR, pretoze KEYWORD [nullptr] NIE JE MOZNE konvertovat na TYPE [int].
	//NullPtrFunction4(nullptr);

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
float ReturnConstant(void)
{
	return(2.8f);
}
//-------------------------------------------------------------------------------------------------------
/*
// Hodi ERROR.
void FunctionWithAuto(auto Value)
{
	wcout << "TYPE [Value]=[" << << L"] !" << endl;,typeid(Value).name());
}
*/
//-------------------------------------------------------------------------------------------------------
/*
// Hodi ERROR.
void FunctionWithAuto(auto Value=4)
{
	wcout << "TYPE [Value]=[" << ConvertStringToWideString(typeid(Value).name()) << L"] !" << endl;
}
*/
//-------------------------------------------------------------------------------------------------------
void TestAutoKeyword(void)
{
	PrintLineSeparator();

	auto														Value1=100;
	auto														Value2=100.5;
	auto														Value3=ReturnConstant();

	wcout << "TYPE [Value1]=[" << ConvertStringToWideString(typeid(Value1).name()) << L"] !" << endl;
	wcout << "TYPE [Value2]=[" << ConvertStringToWideString(typeid(Value2).name()) << L"] !" << endl;
	wcout << "TYPE [Value3]=[" << ConvertStringToWideString(typeid(Value3).name()) << L"] !" << endl;

	list<int>													List;
	
	List.push_back(1);
	List.push_back(2);
	List.push_back(3);

	int															Counter=0;

	for(auto Iterator=List.begin();Iterator!=List.end();Iterator++,Counter++)
	{
		wcout << L"List[" << Counter << L"]=[" << (*Iterator) << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void InitializerListAsParameter(const initializer_list<wstring>& Values)
{
	for(initializer_list<wstring>::iterator Iterator=Values.begin();Iterator!=Values.end();Iterator++)
	{
		wcout << L"Values[" << (Iterator-Values.begin()) << L"]=[" << Iterator->c_str() << L"] !" << endl;
	}
}
//-------------------------------------------------------------------------------------------------------
void TestUniformInitialization(void)
{
	PrintLineSeparator();

	// Inicializuje sa na 0.
	int															Variable1{};
	int															Variable2{10};
	// Inicializuje sa na [nullptr].
	int*														Variable3{};
	int*														Variable4{(int*) 1000};

	wcout << L"Variable1 [" << Variable1 << L"] !" << endl;
	wcout << L"Variable2 [" << Variable2 << L"] !" << endl;
	wcout << L"Variable3 [" << Variable3 << L"] !" << endl;
	wcout << L"Variable4 [" << Variable4 << L"] !" << endl;

	// !!! COMPILATION ERROR. STRATOVA konverzia NIE JE MOZNA.
	//int														VariableError1{10.5};

	char														Variable5{65};
	// !!! COMPILATION ERROR. STRATOVA konverzia NIE JE MOZNA.
	//char														VariableError2{65000};

	wcout << L"Variable5 [" << Variable5 << L"] !" << endl;

	PrintLineSeparator();

	int															Array1[]{1,2,3};
	wstring														Array2[]{L"Aa",L"Bb",L"Cc"};
	
	for(size_t Index=0;Index<CountOf(Array1);Index++)
	{
		wcout << L"Array1[" << Index << L"]=[" << Array1[Index] << L"] !" << endl;
	}

	PrintLineSeparator();

	for(size_t Index=0;Index<CountOf(Array2);Index++)
	{
		wcout << L"Array2[" << Index << L"]=[" << Array2[Index].c_str() << L"] !" << endl;
	}

	PrintLineSeparator();

	complex<double>												Variable6{1.1,2.2};

	wcout << L"Variable6 [" << Variable6.real() << L"," << Variable6.imag() << L"] !" << endl;

	PrintLineSeparator();

	SName														Variable7{L"Timmy",L"Anderson",12};

	wcout << L"Variable7 - FirstName [" << Variable7.MFirstName << L"], LastName [" << Variable7.MLastName << L"], Age [" << Variable7.MAge << L"] !" << endl;

	PrintLineSeparator();

	// CLASS NEMA ZIADEN CONSTRUCTOR.
	CName1														Variable8{L"Jenny",L"Thompson",13};

	wcout << L"Variable8 - FirstName [" << Variable8.MFirstName << L"], LastName [" << Variable8.MLastName << L"], Age [" << Variable8.MAge << L"] !" << endl;

	PrintLineSeparator();

	// !!! CLASS MA iba DEFAULT CONSTRUCTOR, ktory sa zavola.
	CName2														Variable9{};

	wcout << L"Variable9 - FirstName [" << Variable9.MFirstName << L"], LastName [" << Variable9.MLastName << L"], Age [" << Variable9.MAge << L"] !" << endl;

	PrintLineSeparator();

	/*
	// !!! CLASS MA iba DEFAULT CONSTRUCTOR. Kedze ten nema ZIADNE PARAMTERS, tak UNIFORMNU INICIALIZACIU NIE JE MOZNE POUZIT.
	CName2														VariableError3{L"Jenny",L"Thompson",13};

	wcout << L"VariableError3 - FirstName [" << VariableError3.MFirstName << L"], LastName [" << VariableError3.MLastName << L"], Age [" << VariableError3.MAge << L"] !" << endl;
	*/

	// !!! CLASS MA iba CONSTRUCTOR s 3 PARAMETERS, ktory sa zavola.
	CName3														Variable10{L"Timmy",L"Anderson",12};

	wcout << L"Variable10 - FirstName [" << Variable10.MFirstName << L"], LastName [" << Variable10.MLastName << L"], Age [" << Variable10.MAge << L"] !" << endl;

	PrintLineSeparator();

	// !!! Kedze sa NEPOUZIVA UNIFORMNA INICIALIZACIA a CLASS CCollection ma CONSTRUCTOR s 2 INT PARAMETERS, zavola sa tento CONSTRUCTOR.
	CCollection													Collection1(10,20);

	Collection1.Print();

	PrintLineSeparator();

	// !!! Aj ked CLASS CCollection ma CONSTRUCTOR s 2 INT PARAMETERS, zavola sa CONSTRUCTOR s PARAMETROM typu [initializer_list<int> Values].
	CCollection													Collection2{10,20};

	Collection2.Print();

	PrintLineSeparator();

	// !!! Zavola sa CONSTRUCTOR s PARAMETROM typu [initializer_list<int> Values].
	CCollection													Collection3{10,20,30,40,50};

	Collection3.Print();

	PrintLineSeparator();

	// !!! Zavola sa CONSTRUCTOR s PARAMETRAMI typu [wstring] a [initializer_list<int> Values].
	CCollection													Collection4{L"AAA",{10,20,30,40,50}};

	Collection4.Print();

	PrintLineSeparator();

	// Vola sa EXPLICITNY CONSTRUCTOR.
	CClassWithExplicitConstructor								Explicit1(L"Timmy",L"Anderson",12);

	wcout << L"Explicit1 - FirstName [" << Explicit1.MFirstName << L"], LastName [" << Explicit1.MLastName << L"], Age [" << Explicit1.MAge << L"] !" << endl;

	PrintLineSeparator();

	// Vola sa EXPLICITNY CONSTRUCTOR.
	CClassWithExplicitConstructor								Explicit2{L"Timmy",L"Anderson",12};

	wcout << L"Explicit2 - FirstName [" << Explicit2.MFirstName << L"], LastName [" << Explicit2.MLastName << L"], Age [" << Explicit2.MAge << L"] !" << endl;

	PrintLineSeparator();

	/*
	// !!! COMPILER hodi ERROR, pretoze CONSTRUCTOR je EXPLICITNY. Ak by NEBOL, tak CODE by sa KOREKTNE skompiloval.
	CClassWithExplicitConstructor								VariableError4={L"Jenny",L"Thompson",13};

	wcout << L"VariableError4 - FirstName [" << VariableError4.MFirstName << L"], LastName [" << VariableError4.MLastName << L"], Age [" << VariableError4.MAge << L"] !" << endl;
	*/

	InitializerListAsParameter({L"X",L"Y",L"Z"});

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void TestForLoopsArrays(void)
{
	PrintLineSeparator();

	int															Array1[]{11,12,13};

	// C++ 11 umoznuje enumeraciu klasickymi ARRAYS.
	for(int Value : Array1)
	{
		wcout << L"Array1 [" << Value << L"] !" << endl;
	}

	PrintLineSeparator();

	wstring														Array2[]{L"XXX",L"YYY",L"ZZZ"};

	// C++ 11 umoznuje enumeraciu klasickymi ARRAYS.
	// !!! Je dolezite pouzit REFERENCIU, aby nedochadzalo ku kopirovaniu ITEMS.
	for(const wstring& Value : Array2)
	{
		wcout << L"Array2 [" << Value << L"] !" << endl;
	}

	PrintLineSeparator();

	// Inicializacia BEZ volania COPY CONSTRUCTOR.
	CItem1														Array3[]{100,200};

	for(const CItem1& Value : Array3)
	{
		wcout << L"Array3 [" << Value.MValue << L"] !" << endl;
	}

	PrintLineSeparator();

	// Kedze sa nepouzila REFERENCIA, vola sa COPY CONSTRUCTOR.
	for(CItem1 Value : Array3)
	{
		wcout << L"Array3 [" << Value.MValue << L"] !" << endl;
	}

	PrintLineSeparator();

	// Inicializacia BEZ volania COPY CONSTRUCTOR.
	// !!!!! V G++ tento CODE ZLYHA, pretoze vyzaduje volanie COPY CONSTRUCTOR, ktory je oznaceny ako EXPLICIT. Po vyhodeni KEYWORD [EXPLICIT] CODE fungoval spravne.
	CItem2														Array4[]{11,22,33};

	// !!! NEVOLA sa COPY CONSTRUCTOR.
	for(const CItem2& Value : Array4)
	{
		wcout << L"Array4 [" << Value.MValue << L"] !" << endl;
	}

	/*
	// !!! Kedze sa ITEM prenasa BY-VALUE, je NUTNE volat COPY CONSTRUCTOR, no kedze ten je EXPLICIT, tak COMPILER hodi ERROR.
	for(CItem2 Value : Array4)
	{
		wcout << L"Array4 [" << Value.MValue << L"] !" << endl;
	}
	*/

	PrintLineSeparator();

	// Inicializacia BEZ volania COPY CONSTRUCTOR.
	// !!!!! V G++ tento CODE ZLYHA, pretoze vyzaduje volanie COPY CONSTRUCTOR, ktory je oznaceny ako EXPLICIT. Po vyhodeni KEYWORD [EXPLICIT] CODE fungoval spravne.
	CItem3														Array5[]{11,22,33};

	// !!! NEVOLA sa OPERATOR=.
	for(const CItem3& Value : Array5)
	{
		wcout << L"Array5 [" << Value.MValue << L"] !" << endl;
	}

	/*
	// !!!!! Aj ked OPERATOR= je definovany, prikaz [for(TYPE NAME : COLLECTION)] ho NEPOUZIVA a tak COMPILER hodi ERROR.
	for(CItem3 Value : Array5)
	{
		wcout << L"Array5 [" << Value.MValue << L"] !" << endl;
	}
	*/

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void TestForLoopsStandardCollections(void)
{
	PrintLineSeparator();

	vector<int>													Collection1{11,12,13};

	// C++ 11 umoznuje enumeraciu standardnymi COLLECTIONS, kedze MAJU definovane METHODS begin() a end().
	for(int Value : Collection1)
	{
		wcout << L"Collection1 [" << Value << L"] !" << endl;
	}

	PrintLineSeparator();

	list<wstring>												Collection2{L"AA",L"BB",L"CC"};

	// C++ 11 umoznuje enumeraciu standardnymi COLLECTIONS, kedze MAJU definovane METHODS begin() a end().
	for(const wstring& Value : Collection2)
	{
		wcout << L"Collection2 [" << Value << L"] !" << endl;
	}

	PrintLineSeparator();

	initializer_list<int>										Collection3{11,12,13};

	// Aj CLASS initializer_list<> ma METHODS begin() a end().
	for(int Value : Collection3)
	{
		wcout << L"Collection3 [" << Value << L"] !" << endl;
	}

	PrintLineSeparator();

	// Aj CLASS initializer_list<> ma METHODS begin() a end().
	for(int Value : {11,12,13})
	{
		wcout << L"Collection4 [" << Value << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!! METHOD begin() MUSI vracat ITERATOR.
vector<int>::const_iterator begin(const CCustomCollection3& Collection)
{
	wcout << L"vector<int>::const_iterator begin(const CCustomCollection3& Collection) CALLED !" << endl;

	return(Collection.MCollection.begin());
}
//-------------------------------------------------------------------------------------------------------
// !!! METHOD end() MUSI vracat ITERATOR.
vector<int>::const_iterator end(const CCustomCollection3& Collection)
{
	wcout << L"vector<int>::const_iterator end(const CCustomCollection3& Collection) CALLED !" << endl;

	return(Collection.MCollection.end());
}
//-------------------------------------------------------------------------------------------------------
void TestForLoopsCustomCollections(void)
{
	PrintLineSeparator();

	CCustomCollection1											Collection1{11,22,33};

	/*
	// !!! ENUMERACIA NIE JE MOZNA, lebo CLASS NEDEFINUJE METHODS begin() a end() a ani NEEXISTUJU GLOBALNE FUNCTION begin() a end(), ktore by ako PARAMETER mali TYPE CCustomCollection1.
	for(int Value : Collection1)
	{
		wcout << L"Collection1 [" << Value << L"] !" << endl;
	}
	*/

	// Tato enumeracia vsak je mozna, kedze TYPE [vector<>] ma METHODS begin() a end().
	for(int Value : Collection1.MCollection)
	{
		wcout << L"Collection1.MCollection [" << Value << L"] !" << endl;
	}

	PrintLineSeparator();

	CCustomCollection2											Collection2{11,22,33};

	// !!! ENUMERACIA JE MOZNA, lebo CLASS DEFINUJE METHODS begin() a end().
	for(int Value : Collection2)
	{
		wcout << L"Collection2 [" << Value << L"] !" << endl;
	}

	PrintLineSeparator();

	CCustomCollection3											Collection3{11,22,33};

	// !!! ENUMERACIA JE MOZNA, lebo pre CLASS su definovane GLOBALNE FUNCTIONS begin() a end().
	for(int Value : Collection3)
	{
		wcout << L"Collection3 [" << Value << L"] !" << endl;
	}

	PrintLineSeparator();

	CCustomCollection4											Collection4{11,22,33};

	// !!! ENUMERACIA JE MOZNA, lebo CLASS DEFINUJE METHODS begin() a end().
	for(int Value : Collection4)
	{
		wcout << L"Collection4 [" << Value << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void TestStringLiterals(void)
{
	PrintLineSeparator();

	wstring														Text1=LR"(C:\SomeDirectory\SomeFile.txt)";

	wcout << L"Text1 [" << Text1 << L"] !" << endl;

	wstring														Text2=LR"(My name is "Timmy Anderson")";

	wcout << L"Text2 [" << Text2 << L"] !" << endl;

	// !!! STRING [XXX] sluzi ako znacka urcujuca ZACIATOK a KONIEC STRINGU. Zaciatok STRINGU sa potom oznacuje pomocou STRING [XXX(] a koniec STRING pomocou STRING [XXX)].
	wstring														Text3=LR"XXX()" ") " \ ' XXX YYY ZZZ)XXX";

	wcout << L"Text3 [" << Text3 << L"] !" << endl;

	wstring														Text4=LR"XXX(XXX)XXX";

	wcout << L"Text4 [" << Text4 << L"] !" << endl;

	char16_t													Text5[]=u"This is a UTF-16 string.";

	// !!! FUNCTION wcout << ) zobrazi iba 1. znak, pretoze TYPE [char16_t] NEPODPORUJE KOREKTNE.
	//wcout << L"Text5 [" << Text5 << L"] !" << endl;

	// !!! WCOUT vypise retazec korektne.
	wcout << L"Text5 [" << (wchar_t*) Text5 << L"] !" << endl;

	char32_t													Text6[]=U"This is a UTF-32 string.";

	// !!! FUNCTION wcout << ) zobrazi iba 1. znak, pretoze TYPE [char32_t] NEPODPORUJE KOREKTNE.
	//wcout << L"Text6 [" << Text6 << L"] !" << endl;

	// !!! WCOUT vypise iba 1. ZNAK.
	wcout << L"Text6 [" << (wchar_t*) Text6 << L"] !" << endl;

	// UNICODE CHARACTERS.
	const wchar_t												Text7[]=L"\U0002008A\U0002008B";

	// !!! Na konzole tieto CHARACTERS NIE SU zobrazene korektne.
	wcout << L"Text7 [" << Text7 << L"] !" << endl;

	// !!! WCOUT vyhodi CHYBNE ZNAKY.
	wcout << L"Text7 [" << (wchar_t*) Text7 << L"] !" << endl;

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!! KEYWORD [constexpr] je mozne aplikovat na STATIC METHODS.
constexpr static int GetSize(int Size)
{
	// !!! V C++ 11 moze FUNCTION s KEYWORD [constexpr] obsahovat IBA RETURN STATEMENT.
	return((Size>0) ? Size : 1);
}
//-------------------------------------------------------------------------------------------------------
void TestConstExpressions(void)
{
	PrintLineSeparator();

	// !!! KEYWORD [constexpr] je mozne aplikovat na VARIABLES.
	constexpr int												Length=CConstExpressionMethod::GetSizeStatic(4)*2;

	wcout << L"Length [" << Length << L"] !" << endl;

	CConstExpressionMethod										ConstExpressionMethod;

	// Aby COMPILER nehlasil WARNING, ze VARIABLE je nepouzita.
	(void)ConstExpressionMethod;

	int															Array1[ConstExpressionMethod.GetSize(0)];
	int															Array2[ConstExpressionMethod.GetSize(3)];
	int															Array3[CConstExpressionMethod::GetSizeStatic(0)];
	int															Array4[CConstExpressionMethod::GetSizeStatic(4)];
	int															Array5[GetSize(0)];
	int															Array6[GetSize(5)];

	wcout << L"SIZE Array1 [" << CountOf(Array1) << L"] !" << endl;
	wcout << L"SIZE Array2 [" << CountOf(Array2) << L"] !" << endl;
	wcout << L"SIZE Array3 [" << CountOf(Array3) << L"] !" << endl;
	wcout << L"SIZE Array4 [" << CountOf(Array4) << L"] !" << endl;
	wcout << L"SIZE Array5 [" << CountOf(Array5) << L"] !" << endl;
	wcout << L"SIZE Array6 [" << CountOf(Array6) << L"] !" << endl;

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void PrintMyTuple(const CMyTuple<wstring,wstring,int>& Name)
{
	wcout << L"Name [";
	wcout << Name.GetHead();
	wcout << L",";
	wcout << Name.GetTail().GetHead();
	wcout << L",";
	wcout << Name.GetTail().GetTail().GetHead();
	wcout << L"] !" << endl;
}
//-------------------------------------------------------------------------------------------------------
void TestVariadicTemplates(void)
{
	PrintLineSeparator();

	CMyTuple<wstring,wstring,int>								Name(L"Timmy",L"Anderson",12);

	wcout << L"Name [";
	wcout << Name.GetHead();
	wcout << L",";
	wcout << Name.GetTail().GetHead();
	wcout << L",";
	wcout << Name.GetTail().GetTail().GetHead();
	wcout << L"] !" << endl;

	PrintMyTuple(Name);

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void TestDecltype(void)
{
	PrintLineSeparator();

	// KEYWORD [decltype] vracia TYPE EXPRESSION v zatvorkach.
	decltype(10+5)												X=2;
	decltype(10-8*4)											Y=4;
	decltype(0*0)												Result=X*Y;

	wcout << L"RESULT [" << Result << L"] !" << endl;

	wcout << "TYPE [" << ConvertStringToWideString(typeid(decltype(5.4)).name()) << L"] !" << endl;

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
template<typename TType>
auto NewReturnValueSpeficication(TType Value1, TType Value2) -> decltype(Value1+Value2)
{
	return(Value1+Value2);
}
//-------------------------------------------------------------------------------------------------------
void TestReturnValue(void)
{
	PrintLineSeparator();

	int															Value1=4;
	int															Value2=2;
	auto														Result=NewReturnValueSpeficication(Value1,Value2);

	wcout << L"RESULT [" << Result << L"] !" << endl;

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void TestScopedEnumerations(void)
{
	PrintLineSeparator();

	// !!! NON-SCOPED ENUMERATION VALUES su definovane v GLOBAL NAMESPACE.
	ENonScopedEnumeration										NonScopedEnumeration=E_NSE_VALUE_1;

	wcout << L"NonScopedEnumeration [" << NonScopedEnumeration << L"] !" << endl;

	// !!! NON-SCOPED ENUMERATION VALUES su definovane v GLOBAL NAMESPACE.
	NonScopedEnumeration=E_NSE_VALUE_2;

	wcout << L"NonScopedEnumeration [" << NonScopedEnumeration << L"] !" << endl;

	// NON-SCOPED ENUMERATIONS je mozne IMPLICITNE konverovat na INTERGRAL VALUES.
	int															ConvertedValue1=NonScopedEnumeration;

	wcout << L"ConvertedValue1 [" << ConvertedValue1 << L"] !" << endl;

	PrintLineSeparator();

	// !!! SCOPED ENUMERATION VALUES su definovane v NAMESPACE daneho SCOPED ENUMERATION TYPE.
	EScopedEnumeration											ScopedEnumeration=EScopedEnumeration::E_SE_VALUE_1;

	wcout << L"ScopedEnumeration [" << int(ScopedEnumeration) << L"] !" << endl;

	// !!! SCOPED ENUMERATION VALUES su definovane v NAMESPACE daneho SCOPED ENUMERATION TYPE.
	ScopedEnumeration=EScopedEnumeration::E_SE_VALUE_2;

	wcout << L"ScopedEnumeration [" << int(ScopedEnumeration) << L"] !" << endl;

	// !!! SCOPED ENUMERATIONS NIE je mozne IMPLICITNE konverovat na INTERGRAL VALUES a je NUTNE pouzit EXPLICITNU KONVERZIU.
	int															ConvertedValue2=(int) ScopedEnumeration;

	wcout << L"ConvertedValue2 [" << ConvertedValue2 << L"] !" << endl;

	wcout << "UNDERLYING TYPE [EScopedEnumeration] [" << ConvertStringToWideString(typeid(underlying_type<EScopedEnumeration>::type).name()) << L"] !" << endl;
	wcout << "UNDERLYING TYPE [EScopedEnumerationChar] [" << ConvertStringToWideString(typeid(underlying_type<EScopedEnumerationChar>::type).name()) << L"] !" << endl;

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void TestNewTypes(void)
{
	PrintLineSeparator();

	char16_t													Value1='A';

	wcout << L"Value1 [" << Value1 << L"] !" << endl;

	char32_t													Value2='A';

	wcout << L"Value2 [" << Value2 << L"] !" << endl;

	long long													Value3=100;

	wcout << L"Value3 [" << Value3 << L"] !" << endl;

	unsigned long long											Value4=100;

	wcout << L"Value4 [" << Value4 << L"] !" << endl;

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
template<typename TType>
TType TypenameKeywordTemplate(TType Value)
{
	// !!! Je NUTNE pouzit KEYWORD [typename].
	typename CTemplateWithType<TType>::TYPE						LocalValue=Value;

	return(LocalValue);
}
//-------------------------------------------------------------------------------------------------------
void TestTypenameKeyword(void)
{
	PrintLineSeparator();

	// !!! Je NUTNE pouzit KEYWORD [typename].
	wstring														Value=TypenameKeywordTemplate(L"Timmy Anderson");

	wcout << L"VALUE [" << Value << L"] !" << endl;

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void TestTemplateMethodsAndConstructors(void)
{
	PrintLineSeparator();

	// Zavola sa NON-TEMPLATE CONSTRUCTOR.
	CClassWithTemplateMethods<int>								Class1(10);
	double														Result1=Class1.Convert<double>();

	wcout << L"RESULT 1 [" << Result1 << L"] !" << endl;

	PrintLineSeparator();

	// Zavola sa TEMPLATE CONSTRUCTOR.
	CClassWithTemplateMethods<int>								Class2(10.2);
	double														Result2=Class2.Convert<double>();

	wcout << L"RESULT 2 [" << Result2 << L"] !" << endl;

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void TestNestedTemplateClass(void)
{
	PrintLineSeparator();

	COuterClass<int>											OuterClass(10);

	wcout << L"OUTER VALUE [" << OuterClass.GetValue() << L"] !" << endl;

	COuterClass<int>::CInnerClass<double>						InnerClass(4.2);
	
	wcout << L"INNER VALUE [" << InnerClass.GetValue() << L"] !" << endl;

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
template<typename TType>
TType GetDefaultValue1(void)
{
	// Inicializuje VARIABLE [DefaultValue] na DEFAULT VALUE.
	TType														DefaultValue=TType();

	return(DefaultValue);
}
//-------------------------------------------------------------------------------------------------------
template<typename TType>
TType GetDefaultValue2(void)
{
	// Inicializuje VARIABLE [DefaultValue] na DEFAULT VALUE.
	TType														DefaultValue{};

	return(DefaultValue);
}
//-------------------------------------------------------------------------------------------------------
void TestExplicitInitialization(void)
{
	PrintLineSeparator();

	wcout << L"DEFAULT VALUE 1 [" << GetDefaultValue1<double>() << L"] !" << endl;
	wcout << L"DEFAULT VALUE 2 [" << GetDefaultValue2<double>() << L"] !" << endl;

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestDoubleGreaterSign();
	//TestNullPtrKeyword();
	//TestAutoKeyword();
	//TestUniformInitialization();
	//TestForLoopsArrays();
	//TestForLoopsStandardCollections();
	//TestForLoopsCustomCollections();
	//TestStringLiterals();
	//TestConstExpressions();
	//TestVariadicTemplates();
	//TestDecltype();
	//TestReturnValue();
	//TestScopedEnumerations();
	//TestNewTypes();
	//TestTypenameKeyword();
	//TestTemplateMethodsAndConstructors();
	//TestNestedTemplateClass();
	TestExplicitInitialization();

	ShowExitLine();

	return(0);
}
//-------------------------------------------------------------------------------------------------------