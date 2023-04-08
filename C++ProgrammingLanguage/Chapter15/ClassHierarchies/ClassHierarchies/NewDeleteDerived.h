//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <string>
//-------------------------------------------------------------------------------------------------------
class CNewDeleteBase1
{
	protected:
		int														MDummyBase1A;
		int														MDummyBase1B;

	public:
		virtual ~CNewDeleteBase1(void)
		{
		}
};
//-------------------------------------------------------------------------------------------------------
class CNewDeleteBase2
{
	protected:
		int														MDummyBase2A;
		int														MDummyBase2B;

	public:
		virtual ~CNewDeleteBase2(void)
		{
		}
};
//-------------------------------------------------------------------------------------------------------
class CNewDeleteDerived : public CNewDeleteBase1, public CNewDeleteBase2
{
	protected:
		int														MDummyDerivedA;
		int														MDummyDerivedB;

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
		CNewDeleteDerived(void);
		// !!!!! Ak pretazujem NEW a DELETE OPERATORS pre CLASS a tato CLASSS moze byt v DEDICSKEJ HIERARCHII, tak BASE CLASS MUSI MAT VIRTUAL DESTRUCTOR, inak PRETAZENE NEW a DELETE NEBUDU FUNGOVAT SPRAVNE.
		virtual ~CNewDeleteDerived(void);
};
//-------------------------------------------------------------------------------------------------------