//-------------------------------------------------------------------------------------------------------
#include "NewDelete.h"
#include <stdio.h>
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
CNewDelete::CNewDelete(void)
{
	wprintf_s(L"CONSTRUCTOR CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------
CNewDelete::~CNewDelete(void)
{
	wprintf_s(L"DESTRUCTOR CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void* CNewDelete::operator new(size_t Size)
{
	wprintf_s(L"void* CNewDelete::operator new(size_t Size) CALLED !\n");

	__int8*														Buffer=::new __int8[Size];

	return(Buffer);
}
//-------------------------------------------------------------------------------------------------------
void CNewDelete::operator delete(void* Object)
{
	wprintf_s(L"void CNewDelete::operator delete(void* Object) CALLED !\n");

	::delete[](Object);
}
//-------------------------------------------------------------------------------------------------------
void* CNewDelete::operator new(size_t Size, std::wstring& String)
{
	wprintf_s(L"void* CNewDelete::operator new(size_t Size, wstring String) with PARAM [%s] CALLED !\n",String.c_str());

	__int8*														Buffer=::new __int8[Size];

	return(Buffer);
}
//-------------------------------------------------------------------------------------------------------
void CNewDelete::operator delete(void* Object, wstring& String)
{
	wprintf_s(L"void* CNewDelete::operator delete(size_t Size, wstring String) with PARAM [%s] CALLED !\n",String.c_str());

	::delete[](Object);
}
//-------------------------------------------------------------------------------------------------------
void* CNewDelete::operator new(size_t Size, wstring& String1, wstring& String2)
{
	wprintf_s(L"void* CNewDelete::operator new(size_t Size, wstring String1, wstring String2) with PARAMS [%s,%s] CALLED !\n",String1.c_str(),String2.c_str());

	__int8*														Buffer=::new __int8[Size];

	return(Buffer);
}
//-------------------------------------------------------------------------------------------------------
void CNewDelete::operator delete(void* Object, wstring& String1, wstring& String2)
{
	wprintf_s(L"void* CNewDelete::operator delete(size_t Size, wstring String1, wstring String2) with PARAMS [%s,%s] CALLED !\n",String1.c_str(),String2.c_str());

	::delete[](Object);
}
//-------------------------------------------------------------------------------------------------------