//-----------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <cstdarg>
#include <iomanip>
#include <climits>
#include "MyDebug.h"
#include "UserDefinedLiterals.h"
//-----------------------------------------------------------------------------
#ifdef _MSC_VER
#pragma warning( disable : 6287 )
#pragma warning( disable : 4244 )
#pragma warning( disable : 26800 )
#undef min
#undef max
#endif
//-----------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestBooleanType(void)
{
	PrintLineSeparator();

	bool														ValueTrue=true;
	bool														ValueFalse=false;

	if (ValueTrue==ValueFalse)
	{
		wcout << L"VALUE [" << ValueTrue << L"] and VALUE [" << ValueFalse << L"] are EQUAL !" << endl;
	}
	else
	{
		wcout << L"VALUE [" << ValueTrue << L"] and VALUE [" << ValueFalse << L"] are NOT EQUAL !" << endl;
	}

	PrintLineSeparator();

	// !!! IMPLICIT CONVERSION hodi WARNING, pretoze dochadza k NARROWING.
	bool														ConvertedFromInt1=static_cast<bool>(7);
	bool														ConvertedFromInt2=static_cast<bool>(0);

	wcout << L"VARIABLE [" << MACRO_TO_STRING(ConvertedFromInt1) << L"] has VALUE [" << ConvertedFromInt1 << L"] !" << endl;
	wcout << L"VARIABLE [" << MACRO_TO_STRING(ConvertedFromInt2) << L"] has VALUE [" << ConvertedFromInt2 << L"] !" << endl;

	/*
	// !!! COMPILER hodi ERROR, pretoze INITIALIZER [{}] NEUMOZNUJE NARROWING.
	bool														ConvertedFromInt3={7};

	wcout << L"VARIABLE [" << MACRO_TO_STRING(ConvertedFromInt3) << L"] has VALUE [" << ConvertedFromInt3 << L"] !" << endl;
	*/

	PrintLineSeparator();

	int															ConvertedFromBool1=true;
	int															ConvertedFromBool2=false;

	wcout << L"VARIABLE [" << MACRO_TO_STRING(ConvertedFromBool1) << L"] has VALUE [" << ConvertedFromBool1 << L"] !" << endl;
	wcout << L"VARIABLE [" << MACRO_TO_STRING(ConvertedFromBool2) << L"] has VALUE [" << ConvertedFromBool2 << L"] !" << endl;

	// !!! CONVERSION PREBEHNE, lebo nedochadza k NARROWING.
	int															ConvertedFromBool3={false};

	wcout << L"VARIABLE [" << MACRO_TO_STRING(ConvertedFromBool3) << L"] has VALUE [" << ConvertedFromBool3 << L"] !" << endl;

	PrintLineSeparator();

	int															Expression1=(ValueTrue+ValueTrue);
	int															Expression2=(ValueTrue-ValueTrue);
	int															Expression3=(ValueTrue||ValueTrue);

	wcout << L"VARIABLE [" << MACRO_TO_STRING(Expression1) << L"] has VALUE [" << Expression1 << L"] !" << endl;
	wcout << L"VARIABLE [" << MACRO_TO_STRING(Expression2) << L"] has VALUE [" << Expression2 << L"] !" << endl;
	wcout << L"VARIABLE [" << MACRO_TO_STRING(Expression3) << L"] has VALUE [" << Expression3 << L"] !" << endl;

	PrintLineSeparator();

	int															Value=100;
	int*														Pointer1=&Value;
	int*														Pointer2=nullptr;

	// !!! IMPLICIT CONVERSION POINTER na TYPE [bool].
	bool														ConvertedFromPointer1=Pointer1;
	bool														ConvertedFromPointer2=Pointer2;

	wcout << L"VARIABLE [" << MACRO_TO_STRING(ConvertedFromPointer1) << L"] has VALUE [" << ConvertedFromPointer1 << L"] !" << endl;
	wcout << L"VARIABLE [" << MACRO_TO_STRING(ConvertedFromPointer2) << L"] has VALUE [" << ConvertedFromPointer2 << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestCharacterTypes(void)
{
	PrintLineSeparator();

	wchar_t														Value=L'X';

	wcout << L"VARIABLE [" << MACRO_TO_STRING(Value) << L"] has VALUE [" << Value << L"] !" << endl;

	PrintLineSeparator();

	wchar_t														Value1='Z';
	wchar_t														Value2='A';

	// !!! CHARACTER TYPES maju INTEGER REPRESENTATION a je nad nimi mozne robit ARITHMETIC OPERATIONS.
	wchar_t														Result1=(Value1+Value2);
	wchar_t														Result2=(Value1-Value2);

	wcout << L"VARIABLE [" << MACRO_TO_STRING(Result1) << L"] has VALUE [" << Result1 << L"] and INTEGER VALUE [" << static_cast<int>(Result1) << L"] !" << endl;
	wcout << L"VARIABLE [" << MACRO_TO_STRING(Result2) << L"] has VALUE [" << Result2 << L"] and INTEGER VALUE [" << static_cast<int>(Result2) << L"] !" << endl;

	PrintLineSeparator();

	signed char													SingedChar=-100;
	unsigned char												UnsingedChar=100;

	wcout << L"VARIABLE [" << MACRO_TO_STRING(SingedChar) << L"] has INTEGER VALUE [" << static_cast<int>(SingedChar) << L"] !" << endl;
	wcout << L"VARIABLE [" << MACRO_TO_STRING(UnsingedChar) << L"] has INTEGER VALUE [" << static_cast<int>(UnsingedChar) << L"] !" << endl;

	PrintLineSeparator();

	char														Literal1='A';
	wchar_t														Literal2=L'A';
	char16_t													Literal3=u'\u0041';
	char32_t													Literal4=U'\U00000041';

	wcout << L"VARIABLE [" << MACRO_TO_STRING(Literal1) << L"] has INTEGER VALUE [" << static_cast<int>(Literal1) << L"] !" << endl;
	wcout << L"VARIABLE [" << MACRO_TO_STRING(Literal2) << L"] has INTEGER VALUE [" << static_cast<int>(Literal2) << L"] !" << endl;
	wcout << L"VARIABLE [" << MACRO_TO_STRING(Literal3) << L"] has INTEGER VALUE [" << static_cast<int>(Literal3) << L"] !" << endl;
	wcout << L"VARIABLE [" << MACRO_TO_STRING(Literal4) << L"] has INTEGER VALUE [" << static_cast<int>(Literal4) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestIntegerTypes(void)
{
	PrintLineSeparator();

	short int													ValueShort=100;
	signed short int											ValueSignedShort=-100;
	unsigned short int											ValueUnsignedShort=100;
	int															ValueInt=1000000;
	signed int													ValueSignedInt=-1000000;
	unsigned int												ValueUnsignedInt=1000000;
	long int													ValueLong=1000000000L;
	signed long int												ValueSignedLong=-1000000000L;
	unsigned long int											ValueUnsignedLong=1000000000UL;
	long long int												ValueLongLong=1000000000000LL;
	signed long long int										ValueSignedLongLong=-1000000000000LL;
	unsigned long long int										ValueUnsignedLongLong=1000000000000ULL;

	wcout << L"VARIABLE [" << MACRO_TO_STRING(ValueShort) << L"] has VALUE [" << ValueShort << L"] !" << endl;
	wcout << L"VARIABLE [" << MACRO_TO_STRING(ValueSignedShort) << L"] has VALUE [" << ValueSignedShort << L"] !" << endl;
	wcout << L"VARIABLE [" << MACRO_TO_STRING(ValueUnsignedShort) << L"] has VALUE [" << ValueUnsignedShort << L"] !" << endl;
	wcout << L"VARIABLE [" << MACRO_TO_STRING(ValueInt) << L"] has VALUE [" << ValueInt << L"] !" << endl;
	wcout << L"VARIABLE [" << MACRO_TO_STRING(ValueSignedInt) << L"] has VALUE [" << ValueSignedInt << L"] !" << endl;
	wcout << L"VARIABLE [" << MACRO_TO_STRING(ValueUnsignedInt) << L"] has VALUE [" << ValueUnsignedInt << L"] !" << endl;
	wcout << L"VARIABLE [" << MACRO_TO_STRING(ValueLong) << L"] has VALUE [" << ValueLong << L"] !" << endl;
	wcout << L"VARIABLE [" << MACRO_TO_STRING(ValueSignedLong) << L"] has VALUE [" << ValueSignedLong << L"] !" << endl;
	wcout << L"VARIABLE [" << MACRO_TO_STRING(ValueUnsignedLong) << L"] has VALUE [" << ValueUnsignedLong << L"] !" << endl;
	wcout << L"VARIABLE [" << MACRO_TO_STRING(ValueLongLong) << L"] has VALUE [" << ValueLongLong << L"] !" << endl;
	wcout << L"VARIABLE [" << MACRO_TO_STRING(ValueSignedLongLong) << L"] has VALUE [" << ValueSignedLongLong << L"] !" << endl;
	wcout << L"VARIABLE [" << MACRO_TO_STRING(ValueUnsignedLongLong) << L"] has VALUE [" << ValueUnsignedLongLong << L"] !" << endl;

	PrintLineSeparator();

	int															ValueDecimal=100;
	int															ValueOctal=0100;
	int															ValueHexadecimal=0x100;

	wcout << L"VARIABLE [" << MACRO_TO_STRING(ValueDecimal) << L"] has VALUE [" << ValueDecimal << L"] !" << endl;
	wcout << L"VARIABLE [" << MACRO_TO_STRING(ValueOctal) << L"] has VALUE [" << ValueOctal << L"] !" << endl;
	wcout << L"VARIABLE [" << MACRO_TO_STRING(ValueHexadecimal) << L"] has VALUE [" << ValueHexadecimal << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestFloatingPointTypes(void)
{
	PrintLineSeparator();

	float														ValueFloat=123.456F;
	double														ValueDouble=123.456789123;
	long double													ValueLongDouble=123.456e157L;

	streamsize													Precision=wcout.precision();

	wcout << setprecision(numeric_limits<double>::digits10);

	wcout << L"VARIABLE [" << MACRO_TO_STRING(ValueFloat) << L"] has VALUE [" << ValueFloat << L"] !" << endl;
	wcout << L"VARIABLE [" << MACRO_TO_STRING(ValueDouble) << L"] has VALUE [" << ValueDouble << L"] !" << endl;
	wcout << L"VARIABLE [" << MACRO_TO_STRING(ValueLongDouble) << L"] has VALUE [" << ValueLongDouble << L"] !" << endl;

	wcout << setprecision(Precision);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestStringTypes(void)
{
	PrintLineSeparator();

	char														StringNoPrefix[]="Timmy Anderson !!!";
	wchar_t														StringPrefix_L[]=L"Timmy Anderson !!!";
	char8_t														StringPrefix_u8[]=u8"Timmy Anderson !!!";
	char16_t													StringPrefix_u[]=u"Timmy Anderson !!!";
	char32_t													StringPrefix_U[]=U"Timmy Anderson !!!";
	char32_t													StringPrefix_RU[]=U"Timmy Anderson !!!";

	wcout << L"VARIABLE [" << MACRO_TO_STRING(StringNoPrefix) << L"] has LENGTH [" << sizeof(StringNoPrefix) << L"] BYTES !" << endl;
	wcout << L"VARIABLE [" << MACRO_TO_STRING(StringPrefix_L) << L"] has LENGTH [" << sizeof(StringPrefix_L) << L"] BYTES !" << endl;
	wcout << L"VARIABLE [" << MACRO_TO_STRING(StringPrefix_u8) << L"] has LENGTH [" << sizeof(StringPrefix_u8) << L"] BYTES !" << endl;
	wcout << L"VARIABLE [" << MACRO_TO_STRING(StringPrefix_u) << L"] has LENGTH [" << sizeof(StringPrefix_u) << L"] BYTES !" << endl;
	wcout << L"VARIABLE [" << MACRO_TO_STRING(StringPrefix_U) << L"] has LENGTH [" << sizeof(StringPrefix_U) << L"] BYTES !" << endl;
	wcout << L"VARIABLE [" << MACRO_TO_STRING(StringPrefix_RU) << L"] has LENGTH [" << sizeof(StringPrefix_RU) << L"] BYTES !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUserDefinedLiteralOperators(void)
{
	PrintLineSeparator();

	wcout << "OPERATOR [_I1] - VALUE [" << 100_I1 << L"] !" << endl;

	PrintLineSeparator();

	wcout << "OPERATOR [_I2] - VALUE [" << 100_I2 << L"] !" << endl;

	PrintLineSeparator();

	wcout << "OPERATOR [_I3] - VALUE [" << 4567_I3 << L"] !" << endl;

	PrintLineSeparator();

	wcout << "OPERATOR [_i4] - VALUE [" << 4567_i4 << L"] !" << endl;

	PrintLineSeparator();

	wcout << "OPERATOR [_F] - VALUE [" << 123.45_F << L"] !" << endl;

	PrintLineSeparator();

	wcout << "OPERATOR [_C] - VALUE [" << L'Z'_C << L"] !" << endl;

	PrintLineSeparator();

	wcout << "OPERATOR [_S] - VALUE [" << L"Timmy Anderson"_S << L"] !" << endl;

	PrintLineSeparator();

	wcout << "OPERATOR [_i] - VALUE [" << 100_i << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestVoidType(void)
{
	PrintLineSeparator();

	void*														VoidPointer=const_cast<wchar_t*>(L"Timmy Anderson !!!");
	const wchar_t*												TypedPointer=static_cast<const wchar_t*>(VoidPointer);

	wcout << L"VARIABLE [" << MACRO_TO_STRING(TypedPointer) << L"] has VALUE [" << TypedPointer << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSizes(void)
{
	PrintLineSeparator();

	wcout << L"SIZEOF TYPE [" << MACRO_TO_STRING(bool) << L"] is [" << sizeof(bool) << L"] BYTES !" << endl;

	PrintLineSeparator();

	wcout << L"SIZEOF TYPE [" << MACRO_TO_STRING(char) << L"] is [" << sizeof(char) << L"] BYTES !" << endl;
	wcout << L"SIZEOF TYPE [" << MACRO_TO_STRING(wchar_t) << L"] is [" << sizeof(wchar_t) << L"] BYTES !" << endl;
	wcout << L"SIZEOF TYPE [" << MACRO_TO_STRING(char16_t) << L"] is [" << sizeof(char16_t) << L"] BYTES !" << endl;
	wcout << L"SIZEOF TYPE [" << MACRO_TO_STRING(char32_t) << L"] is [" << sizeof(char32_t) << L"] BYTES !" << endl;

	PrintLineSeparator();

	wcout << L"SIZEOF TYPE [" << MACRO_TO_STRING(short int) << L"] is [" << sizeof(short int) << L"] BYTES !" << endl;
	wcout << L"SIZEOF TYPE [" << MACRO_TO_STRING(signed short int) << L"] is [" << sizeof(signed short int) << L"] BYTES !" << endl;
	wcout << L"SIZEOF TYPE [" << MACRO_TO_STRING(unsigned short int) << L"] is [" << sizeof(unsigned short int) << L"] BYTES !" << endl;
	wcout << L"SIZEOF TYPE [" << MACRO_TO_STRING(int) << L"] is [" << sizeof(int) << L"] BYTES !" << endl;
	wcout << L"SIZEOF TYPE [" << MACRO_TO_STRING(signed int) << L"] is [" << sizeof(signed int) << L"] BYTES !" << endl;
	wcout << L"SIZEOF TYPE [" << MACRO_TO_STRING(unsigned int) << L"] is [" << sizeof(unsigned int) << L"] BYTES !" << endl;
	wcout << L"SIZEOF TYPE [" << MACRO_TO_STRING(long int) << L"] is [" << sizeof(long int) << L"] BYTES !" << endl;
	wcout << L"SIZEOF TYPE [" << MACRO_TO_STRING(signed long int) << L"] is [" << sizeof(signed long int) << L"] BYTES !" << endl;
	wcout << L"SIZEOF TYPE [" << MACRO_TO_STRING(unsigned long int) << L"] is [" << sizeof(unsigned long int) << L"] BYTES !" << endl;
	wcout << L"SIZEOF TYPE [" << MACRO_TO_STRING(long long int) << L"] is [" << sizeof(long long int) << L"] BYTES !" << endl;
	wcout << L"SIZEOF TYPE [" << MACRO_TO_STRING(signed long long int) << L"] is [" << sizeof(signed long long int) << L"] BYTES !" << endl;
	wcout << L"SIZEOF TYPE [" << MACRO_TO_STRING(unsigned long long int) << L"] is [" << sizeof(unsigned long long int) << L"] BYTES !" << endl;

	PrintLineSeparator();

	wcout << L"SIZEOF TYPE [" << MACRO_TO_STRING(float) << L"] is [" << sizeof(float) << L"] BYTES !" << endl;
	wcout << L"SIZEOF TYPE [" << MACRO_TO_STRING(double) << L"] is [" << sizeof(double) << L"] BYTES !" << endl;
	wcout << L"SIZEOF TYPE [" << MACRO_TO_STRING(long double) << L"] is [" << sizeof(long double) << L"] BYTES !" << endl;

	PrintLineSeparator();

	wcout << L"BYTE has [" << CHAR_BIT << L"] BITS !" << endl;

	PrintLineSeparator();

	wcout << L"TYPE [" << MACRO_TO_STRING(int) << L"] has MINIMUM VALUE [" << numeric_limits<int>::min() << L"] !" << endl;
	wcout << L"TYPE [" << MACRO_TO_STRING(int) << L"] has MAXIMUM VALUE [" << numeric_limits<int>::max() << L"] !" << endl;

	PrintLineSeparator();

	vector<int>													Vector;

	Vector.push_back(10);
	Vector.push_back(20);
	Vector.push_back(30);

	// !!! TYPE [size_t] UNSIGNED INTEGER TYPE, ktory sa pouziva na ulozene vysledku OPERATOR [sizeof] ako aj na ulozenie poctu ITEMS v COLLECTION.
	size_t														VectorSize=Vector.size();

	wcout << L"VARIABLE [" << MACRO_TO_STRING(VectorSize) << L"] has VALUE [" << VectorSize << L"] !" << endl;

	PrintLineSeparator();

	int															Value1=100;
	int*														Pointer1=&Value1;
	int															Value2=200;
	int*														Pointer2=&Value2;

	// TYPE [ptrdiff_t] je SIGNED INTEGER TYPE, ktory sa pouziva na ukladanie vysledku rozdielu 2 POINTERS.
	// VALUE je v jednotkach [sizeof(int)], pretoze POINTERS su TYPE [int].
	ptrdiff_t													PointerDifferent=(Pointer2-Pointer1);

	wcout << L"VARIABLE [" << MACRO_TO_STRING(Pointer1) << L"] has VALUE [" << Pointer1 << L"] !" << endl;
	wcout << L"VARIABLE [" << MACRO_TO_STRING(Pointer2) << L"] has VALUE [" << Pointer2 << L"] !" << endl;
	wcout << L"VARIABLE [" << MACRO_TO_STRING(PointerDifferent) << L"] has VALUE [" << PointerDifferent << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestAlignment(void)
{
	PrintLineSeparator();

	wcout << L"ALIGNOF TYPE [" << MACRO_TO_STRING(bool) << L"] is [" << alignof(bool) << L"] BYTES !" << endl;

	PrintLineSeparator();

	wcout << L"ALIGNOF TYPE [" << MACRO_TO_STRING(char) << L"] is [" << alignof(char) << L"] BYTES !" << endl;
	wcout << L"ALIGNOF TYPE [" << MACRO_TO_STRING(wchar_t) << L"] is [" << alignof(wchar_t) << L"] BYTES !" << endl;
	wcout << L"ALIGNOF TYPE [" << MACRO_TO_STRING(char16_t) << L"] is [" << alignof(char16_t) << L"] BYTES !" << endl;
	wcout << L"ALIGNOF TYPE [" << MACRO_TO_STRING(char32_t) << L"] is [" << alignof(char32_t) << L"] BYTES !" << endl;

	PrintLineSeparator();

	wcout << L"ALIGNOF TYPE [" << MACRO_TO_STRING(short int) << L"] is [" << alignof(short int) << L"] BYTES !" << endl;
	wcout << L"ALIGNOF TYPE [" << MACRO_TO_STRING(signed short int) << L"] is [" << alignof(signed short int) << L"] BYTES !" << endl;
	wcout << L"ALIGNOF TYPE [" << MACRO_TO_STRING(unsigned short int) << L"] is [" << alignof(unsigned short int) << L"] BYTES !" << endl;
	wcout << L"ALIGNOF TYPE [" << MACRO_TO_STRING(int) << L"] is [" << alignof(int) << L"] BYTES !" << endl;
	wcout << L"ALIGNOF TYPE [" << MACRO_TO_STRING(signed int) << L"] is [" << alignof(signed int) << L"] BYTES !" << endl;
	wcout << L"ALIGNOF TYPE [" << MACRO_TO_STRING(unsigned int) << L"] is [" << alignof(unsigned int) << L"] BYTES !" << endl;
	wcout << L"ALIGNOF TYPE [" << MACRO_TO_STRING(long int) << L"] is [" << alignof(long int) << L"] BYTES !" << endl;
	wcout << L"ALIGNOF TYPE [" << MACRO_TO_STRING(signed long int) << L"] is [" << alignof(signed long int) << L"] BYTES !" << endl;
	wcout << L"ALIGNOF TYPE [" << MACRO_TO_STRING(unsigned long int) << L"] is [" << alignof(unsigned long int) << L"] BYTES !" << endl;
	wcout << L"ALIGNOF TYPE [" << MACRO_TO_STRING(long long int) << L"] is [" << alignof(long long int) << L"] BYTES !" << endl;
	wcout << L"ALIGNOF TYPE [" << MACRO_TO_STRING(signed long long int) << L"] is [" << alignof(signed long long int) << L"] BYTES !" << endl;
	wcout << L"ALIGNOF TYPE [" << MACRO_TO_STRING(unsigned long long int) << L"] is [" << alignof(unsigned long long int) << L"] BYTES !" << endl;

	PrintLineSeparator();

	wcout << L"ALIGNOF TYPE [" << MACRO_TO_STRING(float) << L"] is [" << alignof(float) << L"] BYTES !" << endl;
	wcout << L"ALIGNOF TYPE [" << MACRO_TO_STRING(double) << L"] is [" << alignof(double) << L"] BYTES !" << endl;
	wcout << L"ALIGNOF TYPE [" << MACRO_TO_STRING(long double) << L"] is [" << alignof(long double) << L"] BYTES !" << endl;

	PrintLineSeparator();

	// !!! ALIGMENT je na 128 BYTES.
	alignas(128) int											Variable1=100;
	alignas(long double) int									Variable2=200;
	alignas(128) int											Variable3=300;
	ptrdiff_t													PointerDifference1=(&Variable2-&Variable1);
	ptrdiff_t													PointerDifference2=(&Variable3-&Variable1);

	wcout << L"VARIABLE [" << MACRO_TO_STRING(Variable1) << L"] has VALUE [" << &Variable1 << L"] !" << endl;
	wcout << L"VARIABLE [" << MACRO_TO_STRING(Variable2) << L"] has VALUE [" << &Variable2 << L"] !" << endl;
	wcout << L"VARIABLE [" << MACRO_TO_STRING(Variable3) << L"] has VALUE [" << &Variable3 << L"] !" << endl;

	// !!! Rozdiel je v [sizeof(int)].
	wcout << L"VARIABLE [" << MACRO_TO_STRING(PointerDifference1) << L"] has VALUE [" << PointerDifference1 << L"] !" << endl;
	wcout << L"VARIABLE [" << MACRO_TO_STRING(PointerDifference2) << L"] has VALUE [" << PointerDifference2 << L"] !" << endl;

	// !!! ALIGMENT je na 128 BYTES.
	alignas(128) char											Variable4='A';
	alignas(long double) char									Variable5='B';
	alignas(128) char											Variable6='C';
	ptrdiff_t													PointerDifference3=(&Variable5-&Variable4);
	ptrdiff_t													PointerDifference4=(&Variable6-&Variable4);

	wcout << L"VARIABLE [" << MACRO_TO_STRING(Variable4) << L"] has VALUE [" << static_cast<void*>(&Variable4) << L"] !" << endl;
	wcout << L"VARIABLE [" << MACRO_TO_STRING(Variable5) << L"] has VALUE [" << static_cast<void*>(&Variable5) << L"] !" << endl;
	wcout << L"VARIABLE [" << MACRO_TO_STRING(Variable6) << L"] has VALUE [" << static_cast<void*>(&Variable6) << L"] !" << endl;

	// !!! Rozdiel je v [sizeof(char)].
	wcout << L"VARIABLE [" << MACRO_TO_STRING(PointerDifference3) << L"] has VALUE [" << PointerDifference3 << L"] !" << endl;
	wcout << L"VARIABLE [" << MACRO_TO_STRING(PointerDifference4) << L"] has VALUE [" << PointerDifference4 << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// VARIABLE DECLARATION.
extern int ExternVariable; 
//-----------------------------------------------------------------------------
// FUNCTION DECLARATION.
int ReturnSomeValue(void);
//-----------------------------------------------------------------------------
// STRUCTURE DECLARATION.
struct SMyStruct;
//-----------------------------------------------------------------------------
void TestDeclarationsDefinitions(void)
{
	PrintLineSeparator();

	wcout << L"VARIABLE [" << MACRO_TO_STRING(ExternVariable) << L"] has VALUE [" << ExternVariable << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"FUNCTION [" << MACRO_TO_STRING(ReturnSomeValue) << L"()] returns VALUE [" << ReturnSomeValue() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"STRUCTURE DECLARATION has NAME [" << MACRO_TO_STRING(SMyStruct) << L"] !" << endl;

	PrintLineSeparator();

	// !!! Kedze OPERATORS su aplikovane OSOBITNE na KAZDY NAME, VARIABLE 'Pointer' je POINTER, kym VARIABLE 'NonPointer' je NON-POINTER.
	int															*Pointer, NonPointer=100;

	Pointer=&NonPointer;

	wcout << L"VARIABLE [" << MACRO_TO_STRING(NonPointer) << L"] has VALUE [" << NonPointer << L"] !" << endl;
	wcout << L"VARIABLE [" << MACRO_TO_STRING(Pointer) << L"] has VALUE [" << *Pointer << L"] !" << endl;


	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
// VARIABLE DEFINITION.
int ExternVariable=100;
//-----------------------------------------------------------------------------
// FUNCTION DEFINITION.
int ReturnSomeValue(void)
{
	return(200);
}
//-----------------------------------------------------------------------------
struct SMyStruct
{
//-----------------------------------------------------------------------------
	public:
		int														MField1;
		int														MField2;
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
wstring															Variable=L"GLOBAL";
//-----------------------------------------------------------------------------
void TestScopes(void)
{
	PrintLineSeparator();

	// !!! Pristupi sa ku VARIABLE na GLOBAL SCOPE.
	wcout << L"1. VARIABLE [" << MACRO_TO_STRING(Variable) << L"] has VALUE [" << Variable << L"] !" << endl;

	wstring														Variable=L"LOCAL 1";

	// !!! Pristupi sa ku VARIABLE na LOCAL SCOPE 1.
	wcout << L"2. VARIABLE [" << MACRO_TO_STRING(Variable) << L"] has VALUE [" << Variable << L"] !" << endl;

	{
		// !!! Pristupi sa ku VARIABLE na LOCAL SCOPE 1.
		wcout << L"3. VARIABLE [" << MACRO_TO_STRING(Variable) << L"] has VALUE [" << Variable << L"] !" << endl;

		wstring													Variable=L"LOCAL 2";

		// !!! Pristupi sa ku VARIABLE na LOCAL SCOPE 2.
		wcout << L"4. VARIABLE [" << MACRO_TO_STRING(Variable) << L"] has VALUE [" << Variable << L"] !" << endl;
	}

	// !!! Pristupi sa ku VARIABLE na LOCAL SCOPE 1.
	wcout << L"5. VARIABLE [" << MACRO_TO_STRING(Variable) << L"] has VALUE [" << Variable << L"] !" << endl;

	// !!! Pristupi sa ku VARIABLE na GLOBAL SCOPE pomocou OPERATOR [::].
	wcout << L"6. VARIABLE [" << MACRO_TO_STRING(Variable) << L"] has VALUE [" << ::Variable << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!! GLOBAL VARIABLES su INITIALIZED na DEFAULT VALUES.
int																GlobalVariable;
//-----------------------------------------------------------------------------
struct SSomeStruct
{
	public:
		int														MField1;
		int														MField2;
};
//-----------------------------------------------------------------------------
void TestInitializations(void)
{
	PrintLineSeparator();
	
	// !!! Rozlicne SYNTAXES pre INITIALIZATIONS.
	int															Variable1=100;
	int															Variable2={200};
	int															Variable3(300);
	int															Variable4{400};

	wcout << L"VARIABLE [" << MACRO_TO_STRING(Variable1) << L"] has VALUE [" << Variable1 << L"] !" << endl;
	wcout << L"VARIABLE [" << MACRO_TO_STRING(Variable2) << L"] has VALUE [" << Variable2 << L"] !" << endl;
	wcout << L"VARIABLE [" << MACRO_TO_STRING(Variable3) << L"] has VALUE [" << Variable3 << L"] !" << endl;
	wcout << L"VARIABLE [" << MACRO_TO_STRING(Variable4) << L"] has VALUE [" << Variable4 << L"] !" << endl;

	PrintLineSeparator();

	/*
	// !!! SYNTAX [TYPE VARIABLE{VALUE}] NEUMOZNUJE NARROWING. COMPILER hodi ERROR.
	int															NarrowingERROR{123.456};

	wcout << L"VARIABLE [" << MACRO_TO_STRING(NarrowingERROR) << L"] has VALUE [" << NarrowingERROR << L"] !" << endl;
	*/

	// !!! OSTATNE INITIALIZATION SYNTAXE UMOZNUJU NARROWING. COMPILER HODI WARNING.
	int															NarrowingOK=123.456;

	wcout << L"VARIABLE [" << MACRO_TO_STRING(NarrowingOK) << L"] has VALUE [" << NarrowingOK << L"] !" << endl;

	PrintLineSeparator();

	constexpr int												ARRAY_SIZE=5;

	// !!! VARIABLES su INITIALIZED na DEFAULT VALUES.
	int															DefaultInitialization1{};
	double														DefaultInitialization2{};
	// !!!!! Vsetky ITEMS ARRAY su INITIALIZED na DEFAULT VALUES.
	int															DefaultInitialization3[ARRAY_SIZE]{};

	wcout << L"VARIABLE [" << MACRO_TO_STRING(DefaultInitialization1) << L"] has VALUE [" << DefaultInitialization1 << L"] !" << endl;
	wcout << L"VARIABLE [" << MACRO_TO_STRING(DefaultInitialization2) << L"] has VALUE [" << DefaultInitialization2 << L"] !" << endl;

	for(int Index=0;Index<ARRAY_SIZE;Index++)
	{
		wcout << L"VARIABLE [" << MACRO_TO_STRING(DefaultInitialization3) << L"[" << Index << L"]] has VALUE [" << DefaultInitialization3[Index] << L"] !" << endl;
	}

	PrintLineSeparator();

	// !!! STATIC VARIABLES su INITIALIZED na DEFAULT VALUES.
	static int													StaticVariable;

	wcout << L"VARIABLE [" << MACRO_TO_STRING(GlobalVariable) << L"] has VALUE [" << GlobalVariable << L"] !" << endl;
	wcout << L"VARIABLE [" << MACRO_TO_STRING(StaticVariable) << L"] has VALUE [" << StaticVariable << L"] !" << endl;

	PrintLineSeparator();

	// !!! ITEMS ARRAY su INITIALIZED na VALUES.
	int															Initialization[ARRAY_SIZE]{100,200,300,400,500};

	for(int Index=0;Index<ARRAY_SIZE;Index++)
	{
		wcout << L"VARIABLE [" << MACRO_TO_STRING(Initialization) << L"[" << Index << L"]] has VALUE [" << Initialization[Index] << L"] !" << endl;
	}

	PrintLineSeparator();

	// !!! INITIALIZATION STRUCTURE FIELDS.
	SSomeStruct													SomeStruct{100,200};

	wcout << L"VARIABLE [" << MACRO_TO_STRING(SomeStruct.MField1) << L"] has VALUE [" << SomeStruct.MField1 << L"] !" << endl;
	wcout << L"VARIABLE [" << MACRO_TO_STRING(SomeStruct.MField2) << L"] has VALUE [" << SomeStruct.MField2 << L"] !" << endl;

	PrintLineSeparator();

	// !!! C++ vytvori TYPE [initializer_list<int>].
	auto														List={100,200,300};
	auto														ListIterator=List.begin();

	for(size_t Index=0;Index<List.size();Index++)
	{
		wcout << L"VARIABLE [" << MACRO_TO_STRING(List) << L"[" << Index << L"]] has VALUE [" << *ListIterator << L"] !" << endl;

		ListIterator++;
	}

	PrintLineSeparator();

	wcout << L"TYPE of VARIABLE [" << MACRO_TO_STRING(List) << L"] is [" << ConvertStringToWideString(typeid(List).name()) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestKeywordAuto(void)
{
	PrintLineSeparator();

	auto														Variable1=100;
	auto														Variable2=123.456;
	auto														Variable3={100,200,300};
	auto&														Variable4=Variable1;
	auto*														Variable5=&Variable1;
	const auto*													Variable6=&Variable1;

	wcout << L"TYPE of VARIABLE [" << MACRO_TO_STRING(Variable1) << L"] is [" << ConvertStringToWideString(typeid(Variable1).name()) << L"] !" << endl;
	wcout << L"TYPE of VARIABLE [" << MACRO_TO_STRING(Variable2) << L"] is [" << ConvertStringToWideString(typeid(Variable2).name()) << L"] !" << endl;
	wcout << L"TYPE of VARIABLE [" << MACRO_TO_STRING(Variable3) << L"] is [" << ConvertStringToWideString(typeid(Variable3).name()) << L"] !" << endl;
	wcout << L"TYPE of VARIABLE [" << MACRO_TO_STRING(Variable4) << L"] is [" << ConvertStringToWideString(typeid(Variable4).name()) << L"] !" << endl;
	wcout << L"TYPE of VARIABLE [" << MACRO_TO_STRING(Variable5) << L"] is [" << ConvertStringToWideString(typeid(Variable5).name()) << L"] !" << endl;
	wcout << L"TYPE of VARIABLE [" << MACRO_TO_STRING(Variable6) << L"] is [" << ConvertStringToWideString(typeid(Variable6).name()) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int ReturnInt(void)
{
	return(100);
}
//-----------------------------------------------------------------------------
template<typename TType>
TType Add(const TType& Value1, const TType& Value2)
{
	TType														Result=(Value1+Value2);

	return(100);
}
//-----------------------------------------------------------------------------
// !!! RETURN VALUE TYPE je urceny vykonanim EXPRESSION v KEYWORD [decltype(EXPRESSION)].
auto ReturnValue1(void) -> decltype(ReturnInt())
{
	return(200);
}
//-----------------------------------------------------------------------------
// !!! RETURN VALUE TYPE je urceny vykonanim EXPRESSION v KEYWORD [decltype(EXPRESSION)].
auto ReturnValue2(void) -> decltype(Add(3.5L,4.6L))
{
	return(5.7L);
}
//-----------------------------------------------------------------------------
void TestKeywordDeclType(void)
{
	PrintLineSeparator();

	// !!! TYPE je urceny na zaklade RETURN VALUE FUNCTION.
	decltype(ReturnInt())										Variable1=100;
	decltype(Add(1.2,3.4))										Variable2=100;
	auto														Variable3=ReturnValue1();
	auto														Variable4=ReturnValue2();

	wcout << L"TYPE of VARIABLE [" << MACRO_TO_STRING(Variable1) << L"] is [" << ConvertStringToWideString(typeid(Variable1).name()) << L"] !" << endl;
	wcout << L"TYPE of VARIABLE [" << MACRO_TO_STRING(Variable2) << L"] is [" << ConvertStringToWideString(typeid(Variable2).name()) << L"] !" << endl;
	wcout << L"TYPE of VARIABLE [" << MACRO_TO_STRING(Variable3) << L"] is [" << ConvertStringToWideString(typeid(Variable3).name()) << L"] !" << endl;
	wcout << L"TYPE of VARIABLE [" << MACRO_TO_STRING(Variable4) << L"] is [" << ConvertStringToWideString(typeid(Variable4).name()) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestLValueRValue(void)
{
	PrintLineSeparator();

	// !!! VALUE [Variable1] je LVALUE.
	// !!! VALUE [100] je RVALUE. Zaroven je aj PRVALUE lebo NEMA IDENTIFIER.
	int															Variable1=100;

	// !!! VALUE [Variable2] je LVALUE.
	// !!! VALUE [L"Timmy Anderson"] je RVALUE. Zaroven je aj PRVALUE lebo NEMA IDENTIFIER.
	wstring														Variable2=L"Timmy Anderson";

	// !!! VALUE [Variable3] je LVALUE.
	// !!! VALUE [L"Timmy Anderson"] je RVALUE. Zaroven je aj PRVALUE lebo NEMA IDENTIFIER.
	wstring														Variable3=L"Timmy Anderson";

	// !!! VALUE [Variable4] je LVALUE.
	// !!!!! VALUE [Variable4] je RVALUE vdaka pouzitiu FUNCTION [move()].
	wstring														Variable4=move(Variable3);

	wcout << L"VARIABLE [" << MACRO_TO_STRING(Variable1) << L"] has VALUE [" << Variable1 << L"] !" << endl;
	wcout << L"VARIABLE [" << MACRO_TO_STRING(Variable2) << L"] has VALUE [" << Variable2 << L"] !" << endl;
	wcout << L"VARIABLE [" << MACRO_TO_STRING(Variable3) << L"] has VALUE [" << Variable3 << L"] !" << endl;
	wcout << L"VARIABLE [" << MACRO_TO_STRING(Variable4) << L"] has VALUE [" << Variable4 << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<typename TType>
using															Vector=vector<TType>;
//-----------------------------------------------------------------------------
void TestAliases(void)
{
	PrintLineSeparator();

	using														Int32=int32_t;

	Int32														Variable1=100;

	wcout << L"VARIABLE [" << MACRO_TO_STRING(Variable1) << L"] has VALUE [" << Variable1 << L"] !" << endl;

	PrintLineSeparator();

	Vector<int>													Variable2{100,200,300};

	for(size_t Index=0;Index<Variable2.size();Index++)
	{
		wcout << L"VARIABLE [" << MACRO_TO_STRING(Variable2) << L"[" << Index << L"]] has VALUE [" << Variable2[Index] << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestBooleanType();
	//TestCharacterTypes();
	//TestIntegerTypes();
	//TestFloatingPointTypes();
	//TestStringTypes();
	//TestUserDefinedLiteralOperators();
	//TestVoidType();
	//TestSizes();
	//TestAlignment();
	//TestDeclarationsDefinitions();
	//TestScopes();
	//TestInitializations();
	//TestKeywordAuto();
	//TestKeywordDeclType();
	//TestLValueRValue();
	TestAliases();

	ShowExitLine();

	return(0);
}
//-----------------------------------------------------------------------------