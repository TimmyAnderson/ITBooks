//-----------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <utility>
#include <memory>
#include <numeric>
#include <functional>
#include <iterator>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include "MyDebug.h"
#include "CSimpleFunctionObject.h"
#include "CPerson.h"
#include "CPersonSortingCriteriaFunctionObject.h"
#include "CIncrementFunctionObject.h"
#include "CForEachStateFunctionObject.h"
#include "CWrongStatefulPredicate.h"
#include "CSimpleObject.h"
#include "CSumFunctionObject.h"
//-----------------------------------------------------------------------------
using namespace std;
using namespace std::placeholders;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<typename TCollection>
void PrintCollection(const wstring& Prefix, const TCollection& Collection)
{
	wcout << Prefix;
	wcout << L" [";

	bool														PrintSeparator=false;

	for(const auto& Item : Collection)
	{
		if (PrintSeparator==true)
		{
			wcout << L" ";
		}
		else
		{
			PrintSeparator=true;
		}

		wcout << Item;
	}

	wcout << L"] !" << endl;
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<typename TKey, typename TValue, typename TCompare>
void PrintMap(const wstring& Prefix, const map<TKey,TValue,TCompare>& Collection)
{
	wcout << Prefix;
	wcout << L" [";

	bool														PrintSeparator=false;

	for(const typename map<TKey,TValue,TCompare>::value_type& Item : Collection)
	{
		if (PrintSeparator==true)
		{
			wcout << L" ";
		}
		else
		{
			PrintSeparator=true;
		}

		wcout << L"[" << Item.first << "]=[" << Item.second << "]";
	}

	wcout << L"] !" << endl;
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSimpleFunctionObject(void)
{
	PrintLineSeparator();

	vector<wstring>												Vector({L"Timmy",L"Atreyu",L"Jenny"});

	wcout << L"VECTOR [";

	// !!! Pouzije sa FUNCTION OBJECT na vypis ITEMS.
	for_each(Vector.cbegin(),Vector.cend(),CSimpleFunctionObject());

	wcout << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSortingCriteriaFunctionObject(void)
{
	PrintLineSeparator();

	set<CPerson,CPersonSortingCriteriaFunctionObject>			Set;

	Set.insert(CPerson(L"Timmy",12));
	Set.insert(CPerson(L"Jenny",13));
	Set.insert(CPerson(L"Atreyu",12));

	// ITEMS su SORTED podla SORTING CRITERIAS implementovanymi FUNCTION OBJECT - podla ABECEDY.
	PrintCollection(L"SET",Set);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestFunctionObjectsByValue(void)
{
	PrintLineSeparator();

	CIncrementFunctionObject									FunctionObject(10);

	vector<int>													Vector1;

	// !!! Kedze FUNCTION OBJECTS sa prenasaju BY-VALUE, interny STATE sa NEUCHOVAVA.
	generate_n(back_inserter(Vector1),5,FunctionObject);

	PrintCollection(L"VECTOR 1",Vector1);
	
	wcout << L"FUNCTION OBJECT VALUE [" << FunctionObject.GetValue() << L"] !" << endl;

	PrintLineSeparator();

	vector<int>													Vector2;

	// !!! Kedze FUNCTION OBJECTS sa prenasaju BY-VALUE, interny STATE sa NEUCHOVAVA.
	generate_n(back_inserter(Vector2),5,FunctionObject);

	PrintCollection(L"VECTOR 2",Vector2);
	
	wcout << L"FUNCTION OBJECT VALUE [" << FunctionObject.GetValue() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestFunctionObjectsByReference(void)
{
	PrintLineSeparator();

	CIncrementFunctionObject									FunctionObject(10);

	vector<int>													Vector1;

	// !!! Kedze FUNCTION OBJECTS sa prenasaju BY-REFERENCE, interny STATE sa ZACHOVAVA.
	generate_n<back_insert_iterator<vector<int>>,int,CIncrementFunctionObject&>(back_inserter(Vector1),5,FunctionObject);

	PrintCollection(L"VECTOR 1",Vector1);
	
	wcout << L"FUNCTION OBJECT VALUE [" << FunctionObject.GetValue() << L"] !" << endl;

	PrintLineSeparator();

	vector<int>													Vector2;

	// !!! Kedze FUNCTION OBJECTS sa prenasaju BY-REFERENCE, interny STATE sa ZACHOVAVA.
	generate_n<back_insert_iterator<vector<int>>,int,CIncrementFunctionObject&>(back_inserter(Vector2),5,FunctionObject);

	PrintCollection(L"VECTOR 2",Vector2);
	
	wcout << L"FUNCTION OBJECT VALUE [" << FunctionObject.GetValue() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestForEachStateFunctionObject(void)
{
	PrintLineSeparator();

	vector<int>													Vector({5,6,7,50});

	PrintCollection(L"VECTOR",Vector);

	PrintLineSeparator();

	// !!! FUNCTION for_each() vracia FUNCTION OBJECT, ktory je mozne pouzit na ziskanie STATE z FUNCTION OBJECT.
	CForEachStateFunctionObject									FunctionObject=for_each(Vector.cbegin(),Vector.cend(),CForEachStateFunctionObject());

	wcout << L"FUNCTION OBJECT - NUMBER of ITEMS [" << FunctionObject.GetNumberOfItems() << L"] !" << endl;
	wcout << L"FUNCTION OBJECT - SUM of VALUES [" << FunctionObject.GetSumOfValues() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestErrorStatefulPredicate(void)
{
	PrintLineSeparator();

	vector<int>													Vector({1,2,3,4,5,6,7,8,9,10});

	PrintCollection(L"VECTOR",Vector);

	PrintLineSeparator();

	// !!!!! Tento CODE moze v zavislosti od IMPLEMENTATION vratit nezmyselne vysledky. Castokrat IMPLEMENTATION vytovi KOPIU FUNCTION OBJECT 'CWrongStatefulPredicate', ktora si ulozi svoj INTERNAL STATE a tym padom ALGORITHM moze vymazat viacero ITEMS, ako iba ocakavany 1 ITEM.
	// !!!!! Chybou v CODE je v tom, ze PREDICATE je STATEFUL, pricom PREDICATES by mali byt STATELESS.
	// !!!!! Vo VC 2015 CODE fungoval sprave, ale v GCC 6.0. fungoval NESPRAVNE a odstranil (presunom na koniec) 2 ITEMS namiesto jedneho.
	remove_if(Vector.begin(),Vector.end(),CWrongStatefulPredicate(3));

	PrintCollection(L"VECTOR",Vector);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestPredefinedFunctionObjects(void)
{
	PrintLineSeparator();

	wcout << L"FUNCTION OBJECT - NEGATE(10) [" << negate<int>()(10) << L"] !" << endl;
	wcout << L"FUNCTION OBJECT - PLUS(10,5) [" << plus<int>()(10,5) << L"] !" << endl;
	wcout << L"FUNCTION OBJECT - MINUS(10,5) [" << minus<int>()(10,5) << L"] !" << endl;
	wcout << L"FUNCTION OBJECT - MULTIPLES(10,5) [" << multiplies<int>()(10,5) << L"] !" << endl;
	wcout << L"FUNCTION OBJECT - DIVIDES(10,5) [" << divides<int>()(10,5) << L"] !" << endl;
	wcout << L"FUNCTION OBJECT - MODULUS(10,6) [" << modulus<int>()(10,6) << L"] !" << endl;
	wcout << L"FUNCTION OBJECT - EQUAL_TO(10,5) [" << equal_to<int>()(10,5) << L"] !" << endl;
	wcout << L"FUNCTION OBJECT - NOT_EQUAL_TO(10,5) [" << not_equal_to<int>()(10,5) << L"] !" << endl;
	wcout << L"FUNCTION OBJECT - LESS(10,5) [" << less<int>()(10,5) << L"] !" << endl;
	wcout << L"FUNCTION OBJECT - GREATER(10,5) [" << greater<int>()(10,5) << L"] !" << endl;
	wcout << L"FUNCTION OBJECT - LESS_EQUAL(10,5) [" << less_equal<int>()(10,5) << L"] !" << endl;
	wcout << L"FUNCTION OBJECT - GREATER_EQUAL(10,5) [" << greater_equal<int>()(10,5) << L"] !" << endl;
	wcout << L"FUNCTION OBJECT - LOGICAL_NOT(10) [" << logical_not<int>()(10) << L"] !" << endl;
	wcout << L"FUNCTION OBJECT - LOGICAL_AND(0,6) [" << logical_and<int>()(0,6) << L"] !" << endl;
	wcout << L"FUNCTION OBJECT - LOGICAL_OR(15,0) [" << logical_or<int>()(15,0) << L"] !" << endl;
	wcout << L"FUNCTION OBJECT - BIT_NOT(13) [" << bit_not<int>()(13) << L"] !" << endl;
	wcout << L"FUNCTION OBJECT - BIT_AND(13,6) [" << bit_and<int>()(13,6) << L"] !" << endl;
	wcout << L"FUNCTION OBJECT - BIT_OR(13,6) [" << bit_or<int>()(13,6) << L"] !" << endl;
	wcout << L"FUNCTION OBJECT - BIT_XOR(13,6) [" << bit_xor<int>()(13,6) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestFunction(int Parameter1, int Parameter2, int Parameter3, int Parameter4)
{
	wcout << L"PARAMETER_1 [" << Parameter1 << "], PARAMETER_2 [" << Parameter2 << "], PARAMETER_3 [" << Parameter3 << "], PARAMETER_4 [" << Parameter4 << "] !" << endl;
}
//-----------------------------------------------------------------------------
void FunctionWithMultipleParameters(int Parameter1, int Parameter2, int Parameter3, int Parameter4, int Parameter5)
{
	wcout << L"PARAMETER_1 [" << Parameter1 << "], PARAMETER_2 [" << Parameter2 << "], PARAMETER_3 [" << Parameter3 << "], PARAMETER_4 [" << Parameter4 << "], PARAMETER_5 [" << Parameter5 << "] !" << endl;
}
//-----------------------------------------------------------------------------
void TestBind1(void)
{
	PrintLineSeparator();

	// Nasledujuci CODE vytvori NOVY CALLABLE OBJECT, ktory bude mat 2 PARAMETERS. PARAMETERS FUNCTION bind() maju nasledujuci vyznam.
	// A. PARAMETER 'TestFunction' reprezentuje CALLABLE OBJECT, ktory ma novovytvoreny CALLABLE OBJECT obalovat.
	// B. PARAMETER '100' reprezentuje 1. PARAMETER FUNCTION TestFunction(). Pri volani CALLABLE OBJECT 'CallableObject' bude 1. PARAMETER FUNCTION TestFunction() VZDY subsitutovany hodnotou 100.
	// C. PARAMETER '_1' reprezentuje 2. PARAMETER FUNCTION TestFunction(). Kedze sa pouzil PLACEHOLDER [_1], tak pri volani CALLABLE OBJECT 'CallableObject' bude tento PLACEHOLDER nahradeny 1. PARAMETER pouzitym pri volani CALLABLE OBJECT 'CallableObject'.
	// D. PARAMETER '_2' reprezentuje 3. PARAMETER FUNCTION TestFunction(). Kedze sa pouzil PLACEHOLDER [_2], tak pri volani CALLABLE OBJECT 'CallableObject' bude tento PLACEHOLDER nahradeny 2. PARAMETER pouzitym pri volani CALLABLE OBJECT 'CallableObject'.
	// E. PARAMETER '200' reprezentuje 4. PARAMETER FUNCTION TestFunction(). Pri volani CALLABLE OBJECT 'CallableObject' bude 4. PARAMETER FUNCTION TestFunction() VZDY subsitutovany hodnotou 200.
	auto														CallableObject1=bind(TestFunction,100,_1,_2,200);

	// !!!!! Nasledujuce CODE sa intepretuje ako volanie FUNCTION [TestFunction(100,77,888,200)].
	CallableObject1(777,888);

	PrintLineSeparator();

	FunctionWithMultipleParameters(10,20,30,40,50);

	PrintLineSeparator();

	// !!!!! FUNCTION bind() vytvori sa CALLABLE OBJECT, ktory definuje 3 ARGUMENTS a 2 ARGUMENTS (1. a 3.) nahradi PLACEHOLDERS, ktore budu reprezentovat PARAMETERS vrateneho CALLABLE OBJECT.
	// !!!!! Vysledny CALLABLE OBJECT bude mat namiest 5 iba 2 PARAMETERS.
	auto														CallableObject2=bind(FunctionWithMultipleParameters,_2,111,_1,666,888);

	// !!! Hodnota '11' bude nahradi 1. PLACEHOLDER, ktory reprezentuje 3. PARAMETER FUNCTION FunctionWithMultipleParameters().
	// !!! Hodnota '22' bude nahradi 2. PLACEHOLDER, ktory reprezentuje 1. PARAMETER FUNCTION FunctionWithMultipleParameters().
	CallableObject2(11,22);

	PrintLineSeparator();

	// !!! Kedze sa pouzili PLACEHOLDERS [_3] a [_4], tak vrateny CALLABLE OBJECT MUSI mat 4 PARAMETERS.
	auto														CallableObject3=bind(FunctionWithMultipleParameters,_3,111,_4,666,888);

	// !!!!! CALLABLE OBJECT ma 4 PARAMETERS, alebo  1. a 2. PARAMETER sa NEPOUZIJU, pretoze nemaju svoje PLACEHOLDERS.
	CallableObject3(11,22,33,44);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestBind2(void)
{
	PrintLineSeparator();

	// !!!!! FUNCTION bind() z BINARY OPERATOR spravi CALLABLE OBJECT, ktory ma 1 PARAMETER a chova sa ako UNARY OPERATOR.
	// !!!!! Hodnota 10 sa namapuje ako 1. PARAMETER povodneho FUNCTION OBJECT [plus<int>]. 2. PARAMETER bude substituovanym PARAMETER, ktory sa zada pri volani novovytvoreneho CALLABLE OBJECT.
	auto														CallableObject1=bind(plus<int>(),10,_1);
	// Explicitne zavolanie CALLABLE OBJECT vrateneho FUNCTION bind().
	auto														Result1=CallableObject1(7);

	wcout << L"RESULT 1 [" <<  Result1 << L"] !" << endl;

	const type_info&											TypeInfo1=typeid(Result1);

	if (TypeInfo1==typeid(int))
	{
		wcout << L"RESULT 1 TYPE [int] !" << endl;
	}
	else
	{
		wcout << L"RESULT 1 TYPE [UNEXPECTED] !" << endl;
	}

	PrintLineSeparator();

	// !!! Pouziva sa verzia FUNCTION bind(), ktora umoznuje definovat RETURN VALUE TYPE.
	auto														CallableObject2=bind<double>(plus<int>(),_1,10);
	// Explicitne zavolanie CALLABLE OBJECT vrateneho FUNCTION bind().
	auto														Result2=CallableObject2(7);

	wcout << L"RESULT 2 [" << Result2 << L"] !" << endl;

	const type_info&											TypeInfo2=typeid(Result2);
	
	// !!! Kontrola ci RETURN TYPE je naozaj [double].
	if (TypeInfo2==typeid(double))
	{
		wcout << L"RESULT 2 TYPE [double] !" << endl;
	}
	else
	{
		wcout << L"RESULT 2 TYPE [UNEXPECTED] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestBind3(void)
{
	PrintLineSeparator();

	vector<CSimpleObject>										Object;

	Object.push_back(CSimpleObject(10));
	Object.push_back(CSimpleObject(20));
	Object.push_back(CSimpleObject(30));
	Object.push_back(CSimpleObject(40));
	Object.push_back(CSimpleObject(50));

	// !!! PLACEHOLDER [_1] reprezentuje THIS POINTER.
	auto														CallableObject1=bind(&CSimpleObject::PrintValue,_1);

	// !!! Vrateny CALLABLE OBJECT ma 1 PARAMETER, ktory sa substituuje za THIS POINTER.
	for_each(Object.begin(),Object.end(),CallableObject1);

	PrintLineSeparator();

	// !!! PLACEHOLDER [_1] reprezentuje THIS POINTER.
	// !!! PLACEHOLDER [_2] reprezentuje CUSTOM PARAMETER.
	// !!! Kedze sa pouzili 2 PLACEHOLDERS, tak vrateny CALLABLE OBJECT ma 2 PARAMETERS.
	auto														TempCallableObject=bind(&CSimpleObject::AddAndPrintValue,_1,_2);

	// !!! Kedze CALLABLE OBJECT 'TempCallableObject' ma 2 PARAMETERS a ALGORITHM for_each() vyzaduje CALLABLE OBJECT s 1 PARAMETER, je nutne vytvorit CALLABLE OBJECT s 1 PARAMETER.
	auto														CallableObject2=bind(TempCallableObject,_1,6);

	// !!! Vrateny CALLABLE OBJECT ma 1 PARAMETER, ktory sa substituuje za THIS POINTER.
	for_each(Object.begin(),Object.end(),CallableObject2);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestBind4(void)
{
	PrintLineSeparator();

	vector<CSimpleObject*>										Objects;

	Objects.push_back(new CSimpleObject(10));
	Objects.push_back(new CSimpleObject(20));
	Objects.push_back(new CSimpleObject(30));
	Objects.push_back(new CSimpleObject(40));
	Objects.push_back(new CSimpleObject(50));

	// !!! PLACEHOLDER [_1] reprezentuje THIS POINTER.
	auto														CallableObject=bind(&CSimpleObject::PrintValue,_1);

	// !!! Vrateny CALLABLE OBJECT ma 1 PARAMETER, ktory sa substituuje za THIS POINTER.
	// !!! FUNCTION je volana pre POINTERS.
	for_each(Objects.begin(),Objects.end(),CallableObject);

	for(CSimpleObject* Object : Objects)
	{
		delete(Object);
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestBind5(void)
{
	PrintLineSeparator();

	vector<shared_ptr<CSimpleObject>>							Objects;

	Objects.push_back(shared_ptr<CSimpleObject>(new CSimpleObject(10)));
	Objects.push_back(shared_ptr<CSimpleObject>(new CSimpleObject(20)));
	Objects.push_back(shared_ptr<CSimpleObject>(new CSimpleObject(30)));
	Objects.push_back(shared_ptr<CSimpleObject>(new CSimpleObject(40)));
	Objects.push_back(shared_ptr<CSimpleObject>(new CSimpleObject(50)));

	// !!! PLACEHOLDER [_1] reprezentuje THIS POINTER.
	auto														CallableObject=bind(&CSimpleObject::PrintValue,_1);

	// !!! Vrateny CALLABLE OBJECT ma 1 PARAMETER, ktory sa substituuje za THIS POINTER.
	// !!! FUNCTION je volana pre SHARED POINTERS.
	for_each(Objects.begin(),Objects.end(),CallableObject);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestBind6(void)
{
	PrintLineSeparator();

	CSumFunctionObject											FunctionObject;

	// !!! FUNCTION bind() sa pouzije na CUSTOM FUNCTION OBJECT.
	auto														CallableObject=bind(FunctionObject,10,_1);

	wcout << L"RESULT [" << CallableObject(2) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestBindMemberFunction(void)
{
	PrintLineSeparator();

	auto														CallableMethod1=mem_fn(&CSimpleObject::PrintValue);

	CallableMethod1(CSimpleObject(10));

	PrintLineSeparator();

	auto														CallableMethod2=mem_fn(&CSimpleObject::PrintValuePrefixPostfix);

	CallableMethod2(CSimpleObject(20),L"<<<",L">>>");

	PrintLineSeparator();

	vector<CSimpleObject>										Objects;

	Objects.push_back(CSimpleObject(10));
	Objects.push_back(CSimpleObject(20));
	Objects.push_back(CSimpleObject(30));
	Objects.push_back(CSimpleObject(40));
	Objects.push_back(CSimpleObject(50));

	auto														CallableMethod3=mem_fn(&CSimpleObject::PrintValuePrefixPostfix);

	for_each(Objects.begin(),Objects.end(),bind(CallableMethod3,_1,L"<",L">"));

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestBindField(void)
{
	PrintLineSeparator();

	map<wstring,int>											Map;

	Map[L"1"]=11;
	Map[L"2"]=22;
	Map[L"3"]=33;

	PrintMap(L"MAP",Map);

	PrintLineSeparator();

	plus<int>													Plus;

	// Pouziva sa FIELD 'map<wstring,int>::value_type::second'.
	// !!! PLACEHOLDER '_1' reprezentuje kumulativnu VALUE a je typu 'int'.
	// !!! PLACEHOLDER '_2' reprezentuje ITEM danej MAP a je typu 'pair<const wstring,int>'.
	// !!!!! CODE [bind(&map<wstring,int>::value_type::second,_2)] vola FIELD 'map<wstring,int>::value_type::second' pre PLACEHOLDER, ktory reprezentuje ITEM danej MAP. Vysledkom je ziskanie VALUE pre kazdy KEY danej MAP.
	auto														Bind=bind(Plus,_1,bind(&map<wstring,int>::value_type::second,_2));

	int															Sum=accumulate(Map.begin(),Map.end(),0,Bind);

	wcout << L"MAP SUM [" << Sum << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestLambdaFunction(void)
{
	PrintLineSeparator();

	vector<int>													Vector({10,20,30,40,50});

	PrintCollection(L"VECTOR",Vector);

	PrintLineSeparator();

	wcout << L"VECTOR [";

	bool														IsFirst=false;

	auto														Callback=[&IsFirst](int& Value)->void{if (IsFirst==false){IsFirst=true;}else{std::wcout << L" ";} Value*=2; std::wcout << Value;};

	// !!! ALGORITHM zaroven MODIFIKUJE VALUES daneho VECTOR.
	for_each(Vector.begin(),Vector.end(),Callback);

	wcout << L"] !" << endl;

	PrintLineSeparator();

	PrintCollection(L"VECTOR",Vector);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestLambdaFunctionCallingMethods(void)
{
	PrintLineSeparator();

	vector<CPerson>												Vector;

	Vector.push_back(CPerson(L"Timmy",12));
	Vector.push_back(CPerson(L"Jenny",13));
	Vector.push_back(CPerson(L"Atreyu",12));

	PrintCollection(L"VECTOR",Vector);

	PrintLineSeparator();

	wcout << L"VECTOR [";

	bool														IsFirst=false;

	// !!! LAMBDA FUNCTIONS mozu volat METHODS.
	auto														Callback=[&IsFirst](const CPerson& Value)->void{if (IsFirst==false){IsFirst=true;}else{std::wcout << L" ";} wcout << Value.ToString();};

	for_each(Vector.cbegin(),Vector.cend(),Callback);

	wcout << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestLambdaFunctionSortingCriteria(void)
{
	PrintLineSeparator();

	// Implementuje funkcnost OPERATOR<.
	auto														Comparer=[](const CPerson& Value1, const CPerson& Value2)->bool{return(Value1.GetName()<Value2.GetName());};

	// COMPARER TYPE je vhodne zadavat pomocou KEYWORD [decltype].
	set<CPerson,decltype(Comparer)>								Set(Comparer);

	Set.insert(CPerson(L"Timmy",12));
	Set.insert(CPerson(L"Jenny",13));
	Set.insert(CPerson(L"Atreyu",12));

	// ITEMS su SORTED podla SORTING CRITERIAS implementovanymi FUNCTION OBJECT - podla ABECEDY.
	PrintCollection(L"SET",Set);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestSimpleFunctionObject();
	//TestSortingCriteriaFunctionObject();
	//TestFunctionObjectsByValue();
	//TestFunctionObjectsByReference();
	//TestForEachStateFunctionObject();
	//TestErrorStatefulPredicate();
	//TestPredefinedFunctionObjects();
	//TestBind1();
	//TestBind2();
	//TestBind3();
	//TestBind4();
	//TestBind5();
	//TestBind6();
	//TestBindMemberFunction();
	//TestBindField();
	//TestLambdaFunction();
	//TestLambdaFunctionCallingMethods();
	TestLambdaFunctionSortingCriteria();

	ShowExitLine();

	return(0);
}
//-----------------------------------------------------------------------------