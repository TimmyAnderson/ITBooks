//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <windows.h>
#include <conio.h>
#include <crtdbg.h>
#include <strsafe.h>
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
//----------------------------------------------------------------------------------------------------------------------
#ifndef _MSC_VER
#define wprintf_s wprintf
#define printf_s printf
#endif
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
std::wstring GetTypeInfoName(const std::type_info& Value);
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