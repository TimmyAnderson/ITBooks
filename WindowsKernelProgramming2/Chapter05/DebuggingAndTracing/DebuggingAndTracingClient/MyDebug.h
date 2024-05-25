//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <windows.h>
#include <conio.h>
#include <crtdbg.h>
#include <strsafe.h>
#include <type_traits>
#else
#include <cxxabi.h>
#endif
#include <cstdint>
#include <wchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <typeinfo>
#include <type_traits>
#include <string>
//----------------------------------------------------------------------------------------------------------------------
#define MACRO_TO_STRING( Variable ) ConvertStringToWideString(#Variable)
#define MACRO_INTERNAL_STRINGIFY_TO_WIDE_STRING(Parameter) #Parameter
#define MACRO_STRINGIFY_TO_WIDE_STRING(Parameter) ConvertStringToWideString(MACRO_INTERNAL_STRINGIFY_TO_WIDE_STRING(Parameter))
//----------------------------------------------------------------------------------------------------------------------
#ifndef _MSC_VER
#define wprintf_s wprintf
#define printf_s printf
#endif
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
enum class ERefrenceType
{
//----------------------------------------------------------------------------------------------------------------------
	E_NO_REFERENCE=1,
	E_LVALUE_REFERENCE=2,
	E_RVALUE_REFERENCE=3,
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void SafeMain(void);
void PrintLineSeparator(bool UseWideChar=true);
void ShowExitLine(void);
char ConvertWideCharToChar(wchar_t WideChar);
wchar_t ConvertCharToWideChar(char Char);
std::wstring ConvertStringToWideString(const std::string& Value);
std::string ConvertWideStringToString(const std::wstring& Value);
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
std::wstring GetTypeInfoName(void)
{
	std::wstring GetTypeInfoName(const std::type_info& Value, bool IsArray, ERefrenceType ReferenceType, bool IsConst, bool IsVolatile, bool IsReferenceToConst, bool IsReferenceToVolatile);

	const std::type_info&										Value=typeid(TType);
	bool														IsArray=std::is_array<TType>::value;
	bool														IsConst=std::is_const<TType>::value;
	bool														IsVolatile=std::is_volatile<TType>::value;
	bool														IsReferenceToConst;
	bool														IsReferenceToVolatile;
	ERefrenceType												ReferenceType;

	if (std::is_lvalue_reference<TType>::value==true)
	{
		ReferenceType=ERefrenceType::E_LVALUE_REFERENCE;

		using													NO_REFERENCE_TYPE=typename std::remove_reference<TType>::type;

		IsReferenceToConst=std::is_const<NO_REFERENCE_TYPE>::value;
		IsReferenceToVolatile=std::is_volatile<NO_REFERENCE_TYPE>::value;
	}
	else if (std::is_rvalue_reference<TType>::value==true)
	{
		ReferenceType=ERefrenceType::E_RVALUE_REFERENCE;

		using													NO_REFERENCE_TYPE=typename std::remove_reference<TType>::type;

		IsReferenceToConst=std::is_const<NO_REFERENCE_TYPE>::value;
		IsReferenceToVolatile=std::is_volatile<NO_REFERENCE_TYPE>::value;
	}
	else
	{
		ReferenceType=ERefrenceType::E_NO_REFERENCE;
		IsReferenceToConst=false;
		IsReferenceToVolatile=false;
	}

	std::wstring												TypeInfoName=GetTypeInfoName(Value,IsArray,ReferenceType,IsConst,IsVolatile,IsReferenceToConst,IsReferenceToVolatile);

	return(TypeInfoName);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType,size_t N>
size_t CountOf(TType (&)[N])
{
    return(std::extent<TType[N]>::value);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! NASLEDUJUCE TEMPLATES sluzia na urcenie VALUE CATEGORY.
template<typename TType>
constexpr const wchar_t*										VALUE_CATEGORY=L"PRVALUE TType";
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
constexpr const wchar_t*										VALUE_CATEGORY<TType&> =L"LVALUE TType&";
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
constexpr const wchar_t*										VALUE_CATEGORY<TType&&> =L"XVALUE TType&&";
//----------------------------------------------------------------------------------------------------------------------
// !!!!! NASLEDUJUCE MACRO sluzi na vypis VALUE CATEGORY. Dvojite ZATVORKY [()] su NUTNE, aby sa vratila okrem TYPE aj VALUE CATEGORY.
#define SHOW_VALUE_CATEGORY(EXPRESSION) wcout << L"EXPRESSION [" << #EXPRESSION << L"] has VALUE CATEGORY [" << VALUE_CATEGORY<decltype((EXPRESSION))> << L"] !" << endl
//----------------------------------------------------------------------------------------------------------------------
#ifdef _MSC_VER 
#define MACRO_FUNCTION_PROTOTYPE ConvertStringToWideString(__FUNCSIG__)
#else
#define MACRO_FUNCTION_PROTOTYPE ConvertStringToWideString(__PRETTY_FUNCTION__)
#endif
//----------------------------------------------------------------------------------------------------------------------