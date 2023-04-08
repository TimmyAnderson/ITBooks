//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <string>
//-------------------------------------------------------------------------------------------------------
class CNewDelete
{
	protected:
		int														MDummyA;
		int														MDummyB;

	public:
		void* operator new(size_t Size);
		void operator delete(void* Object);
		void* operator new(size_t Size, std::wstring& String);
		void operator delete(void* Object, std::wstring& String);
		void* operator new(size_t Size, std::wstring& String1, std::wstring& String2);
		void operator delete(void* Object, std::wstring& String1, std::wstring& String2);

	public:
		void* operator new[](size_t Size);
		void operator delete[](void* Object, size_t ItemSize);
		void* operator new[](size_t Size, size_t ItemSize, std::wstring& String1, std::wstring& String2);
		void operator delete[](void* Object, size_t ItemSize, std::wstring& String1, std::wstring& String2);

	public:
		CNewDelete(void);
		// !!!!! Ak pretazujem NEW a DELETE OPERATORS pre CLASS a tato CLASSS moze byt v DEDICSKEJ HIERARCHII, tak BASE CLASS MUSI MAT VIRTUAL DESTRUCTOR, inak PRETAZENE NEW a DELETE NEBUDU FUNGOVAT SPRAVNE.
		virtual ~CNewDelete(void);
};
//-------------------------------------------------------------------------------------------------------