//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <string>
//-------------------------------------------------------------------------------------------------------
class CNewDelete
{
	public:
		void* operator new(size_t Size);
		void operator delete(void* Object);
		void* operator new(size_t Size, std::wstring& String);
		void operator delete(void* Object, std::wstring& String);
		void* operator new(size_t Size, std::wstring& String1, std::wstring& String2);
		void operator delete(void* Object, std::wstring& String1, std::wstring& String2);

	public:
		CNewDelete(void);
		virtual ~CNewDelete(void);
};
//-------------------------------------------------------------------------------------------------------