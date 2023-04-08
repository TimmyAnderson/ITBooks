//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
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
//-----------------------------------------------------------------------------
#define MACRO_TO_STRING( Variable ) ConvertStringToWideString(#Variable)
//-----------------------------------------------------------------------------
#ifndef _MSC_VER
#define wprintf_s wprintf
#define printf_s printf
#endif
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void SafeMain(void);
void PrintLineSeparator(bool UseWideChar=true);
void ShowExitLine(void);
std::wstring ConvertStringToWideString(const std::string& Value);
std::string ConvertWideStringToString(const std::wstring& Value);
std::string GetTypeInfoName(const std::type_info& Value);
//-----------------------------------------------------------------------------
template<typename TType,size_t N>
size_t CountOf(TType (&)[N])
{
    return(std::extent<TType[N]>::value);
}
//-----------------------------------------------------------------------------