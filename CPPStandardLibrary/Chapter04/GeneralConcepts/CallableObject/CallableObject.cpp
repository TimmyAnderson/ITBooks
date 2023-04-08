//-----------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <functional> 
#include <iostream>
#include "MyDebug.h"
#include "CMemberFunction.h"
#include "CFunctionObject.h"
//-----------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------
void SimpleFunction(wstring Param1, wstring Param2)
{
	wcout << L"SimpleFunction() - PARAM 1 [" << Param1 << L"], PARAM 2 [" << Param2 << L"] !" << endl;
}
//-----------------------------------------------------------------------------
void TestFunctionPointer(void)
{
	PrintLineSeparator();

	SimpleFunction(L"Timmy",L"Anderson");

	function<void(wstring,wstring)>								CallableObject1(SimpleFunction);

	CallableObject1(L"Timmy",L"Anderson");

	function<void()>											CallableObject2=bind(SimpleFunction,L"Timmy",L"Anderson");

	CallableObject2();

	PrintLineSeparator();

	// !!! RETURN VALUE FUNCTION bind() je IMPLEMENTATION DEPENDENT.
	auto														Value=bind(SimpleFunction,L"Timmy",L"Anderson");
	const char*													ValueType=typeid(Value).name();

	wcout << "TYPE [" << ConvertStringToWideString(ValueType) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMemberFunctionPointer(void)
{
	PrintLineSeparator();

	CMemberFunction												MemberFunction;

	MemberFunction.SimpleMethod(L"Timmy",L"Anderson");

	typedef void (CMemberFunction::*PointerToMethod)(wstring, wstring);

	PointerToMethod												Pointer=&CMemberFunction::SimpleMethod;

	(MemberFunction.*Pointer)(L"Timmy",L"Anderson");

	function<void()>											CallableObject=bind(&CMemberFunction::SimpleMethod,MemberFunction,L"Timmy",L"Anderson");

	CallableObject();

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestFunctionObject(void)
{
	PrintLineSeparator();

	CFunctionObject												FunctionObject;

	FunctionObject(L"Timmy",L"Anderson");

	function<void(wstring,wstring)>								CallableObject1(FunctionObject);

	CallableObject1(L"Timmy",L"Anderson");

	function<void()>											CallableObject2=bind(FunctionObject,L"Timmy",L"Anderson");

	CallableObject2();

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestLambdaFunction(void)
{
	PrintLineSeparator();

	function<void(wstring,wstring)>								LambdaFunction=[] (wstring Param1, wstring Param2)
	{
		wcout << L"LambdaFunction() - PARAM 1 [" << Param1 << L"], PARAM 2 [" << Param2 << L"] !" << endl;
	};

	LambdaFunction(L"Timmy",L"Anderson");

	function<void(wstring,wstring)>								CallableObject1(LambdaFunction);

	CallableObject1(L"Timmy",L"Anderson");

	function<void()>											CallableObject2=bind(LambdaFunction,L"Timmy",L"Anderson");

	CallableObject2();

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	TestFunctionPointer();
	//TestMemberFunctionPointer();
	//TestFunctionObject();
	//TestLambdaFunction();

	ShowExitLine();

	return(0);
}
//-----------------------------------------------------------------------------