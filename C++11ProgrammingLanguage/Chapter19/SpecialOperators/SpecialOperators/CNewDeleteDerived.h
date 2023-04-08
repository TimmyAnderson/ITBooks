//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
#include <string>
#include "CNewDeleteBase1.h"
#include "CNewDeleteBase2.h"
//-------------------------------------------------------------------------------------------------------
class CNewDeleteDerived : public CNewDeleteBase1, public CNewDeleteBase2
{
//-----------------------------------------------------------------------------
	protected:
		int														MDummyDerivedA;
		int														MDummyDerivedB;
		int														MDummyDerivedC;
		int														MDummyDerivedD;

	public:
		void* operator new(size_t Size)
		{
			int8_t*												Buffer=::new int8_t[Size];

			std::wcout << L"void* CNewDeleteDerived::OPERATOR NEW(size_t Size) CALLED ! SIZE [" << Size << L"] BUFFER [" << Buffer << L"] !" << std::endl;

			return(Buffer);
		}

		void operator delete(void* Object)
		{
			std::wcout << L"void CNewDeleteDerived::OPERATOR DELETE(void* Object) CALLED ! OBJECT [" << Object << L"] !" << std::endl;

			if (Object!=nullptr)
			{
				::delete[]((int8_t*)Object);
			}
		}

		void operator delete(void* Object, size_t BufferSize)
		{
			std::wcout << L"void CNewDeleteDerived::OPERATOR DELETE(void* Object, size_t BufferSize) CALLED ! OBJECT [" << Object << L"] BUFFER SIZE [" << BufferSize << L"] !" << std::endl;

			if (Object!=nullptr)
			{
				::delete[]((int8_t*)Object);
			}
		}

		void* operator new(size_t Size, std::wstring& String)
		{
			int8_t*												Buffer=::new int8_t[Size];

			std::wcout << L"void* CNewDeleteDerived::OPERATOR NEW(size_t Size, wstring String) CALLED ! SIZE [" << Size << L"] STRING [" << String << L"] BUFFER [" << Buffer << L"] !" << std::endl;

			return(Buffer);
		}

		void operator delete(void* Object, std::wstring& String)
		{
			std::wcout << L"void CNewDeleteDerived::OPERATOR DELETE(void* Object, wstring String) CALLED ! OBJECT [" << Object << L"] STRING [" << String << L"] !" << std::endl;

			if (Object!=nullptr)
			{
				::delete[]((int8_t*)Object);
			}
		}

		void operator delete(void* Object, size_t BufferSize, std::wstring& String)
		{
			std::wcout << L"void CNewDeleteDerived::OPERATOR DELETE(void* Object, size_t BufferSize, wstring String) CALLED ! OBJECT [" << Object << L"] BUFFER SIZE [" << BufferSize << L"] STRING [" << String << L"] !" << std::endl;

			if (Object!=nullptr)
			{
				::delete[]((int8_t*)Object);
			}
		}

		void* operator new(size_t Size, std::wstring& String1, std::wstring& String2)
		{
			int8_t*												Buffer=::new int8_t[Size];

			std::wcout << L"void* CNewDeleteDerived::OPERATOR NEW(size_t Size, wstring String1, wstring String2) CALLED ! SIZE [" << Size << L"] STRING 1 [" << String1 << L"] STRING 2 [" << String2 << L"] BUFFER [" << Buffer << L"] !" << std::endl;

			return(Buffer);
		}

		void operator delete(void* Object, std::wstring& String1, std::wstring& String2)
		{
			std::wcout << L"void CNewDeleteDerived::OPERATOR DELETE(void* Object, wstring String1, wstring String2) CALLED ! OBJECT [" << Object << L"] STRING 1 [" << String1 << L"] STRING 2 [" << String2 << L"] !" << std::endl;

			if (Object!=nullptr)
			{
				::delete[]((int8_t*)Object);
			}
		}

		void operator delete(void* Object, size_t BufferSize, std::wstring& String1, std::wstring& String2)
		{
			std::wcout << L"void CNewDeleteDerived::OPERATOR DELETE(void* Object, size_t BufferSize, wstring String1, wstring String2) CALLED ! OBJECT [" << Object << L"] BUFFER SIZE [" << BufferSize << L"] STRING 1 [" << String1 << L"] STRING 2 [" << String2 << L"] !" << std::endl;

			if (Object!=nullptr)
			{
				::delete[]((int8_t*)Object);
			}
		}

	public:
		// !!!!! Tento CODE NIE JE PLATFORM INDEPENDENT, pretoze C++ NEDEFINUJE, ze do OPERATOR NEW[] sa MUSI ako SIZE zaslat VALUE [SIZEOF(size_t)+SIZEOF(CNewDeleteDerived)*N]. VALUE [SIZEOF(size_t)] sluziaca na ulozene poctu ITEMS je IMPLEMENTATION DEPENDENT.
		void* operator new[](size_t Size)
		{
			int8_t*												Buffer=::new int8_t[Size];
			size_t												NumberOfItemsPlaceholderSize=sizeof(size_t);

			// !!!!! MEMORY pre SIZE PLACEHOLDER sa MUSI VYMAZAT, pretoze C++ v skutocnosti pouziva iba SIZEOF(int) BYTES a ostatne necha NENAINICIALIZOVANE.
			for (size_t Index=0;Index<NumberOfItemsPlaceholderSize;Index++)
			{
				Buffer[Index]=0;
			}

			size_t												ItemSize=sizeof(CNewDeleteDerived);
			// !!! PARAMETER 'Size' je rovny [sizeof(size_t)+N*sizeof(CNewDeleteDerived)], kde v sizeof(size_t) je ulozena hodnota N rovnajuca sa POCTU ITEMS v ARRAY.
			size_t												NumberOfItems=(Size-NumberOfItemsPlaceholderSize)/sizeof(CNewDeleteDerived);
			CNewDeleteDerived*									FirstItem=(CNewDeleteDerived*) (Buffer+NumberOfItemsPlaceholderSize);

			// !!!!! CONSTRUCTORS pre ITEMS sa NESMU VOLAT, pretoze to C++ robi AUTOMATICKY pri navrate z OPERATOR NEW[].

			std::wcout << L"void* CNewDeleteDerived::OPERATOR NEW[](size_t Size) CALLED ! SIZE [" << Size << L"] ITEM SIZE [" << ItemSize << L"] ALLOCATED MEMORY [" << Buffer << L"] NUMBER OF ITEMS [" << NumberOfItems << L"] FIRST ITEM [" << FirstItem << L"] !" << std::endl;

			// !!!!! OPERATOR[] vracia POINTER na BUFFER a NIE POINTER na 1. ITEM. Az C++ COMPILER AUTOMATICKY posuva tento POINTER o SIZEOF(size_t) BYTES na 1. ITEM alokovaneho ARRAY.
			return(Buffer);
		}

		// !!!!! Tento CODE NIE JE PLATFORM INDEPENDENT, pretoze C++ NEDEFINUJE, ze do OPERATOR NEW[] sa MUSI ako SIZE zaslat VALUE [SIZEOF(size_t)+SIZEOF(CNewDeleteDerived)*N]. VALUE [SIZEOF(size_t)] sluziaca na ulozene poctu ITEMS je IMPLEMENTATION DEPENDENT.
		// !!!!! 1. PARAMETER NEUKAZUJE na 1. ITEM v ARRAY, ale na ZACIATOK alokovaneho BUFFER, ktory je dlhsi o SIZEOF(size_t) BYTES, pretoze na zaciatku je ulozeny pocet ITEMS v ARRAY.
		// !!!!! 2. PARAMETER je POCET BYTES, ktore BUFFER OBSAHUJE.
		void operator delete[](void* Object, size_t BufferSize)
		{
			if (Object!=nullptr)
			{
				// !!! PARAMETER Object sa odkazuje na BUFFER, ktora bol alokovany v NEW[].
				int8_t*											Buffer=(int8_t*) Object;
				size_t*											PointerToNumberOfItemsPlaceholder=(size_t*) Buffer;
				size_t											NumberOfItems=*PointerToNumberOfItemsPlaceholder;
				size_t											NumberOfItemsPlaceholderSize=sizeof(size_t);
				// !!! PRVY ITEM sa nachadza az sizeof(size_t) BYTES NESKOR, pretoze prvych sizeof(size_t) BYTES obsahuje POCET alokovanych ITEMS.
				CNewDeleteDerived*								FirstItem=(CNewDeleteDerived*) (Buffer+NumberOfItemsPlaceholderSize);

				std::wcout << L"void CNewDeleteDerived::OPERATOR DELETE[](void* Object, size_t BufferSize) CALLED ! OBJECT [" << Object << L"] BUFFER SIZE [" << BufferSize << L"] NUMBER OF ITEMS [" << NumberOfItems << L"] FIRST ITEM [" << FirstItem << L"] !" << std::endl;

				// !!!!! DESTRUCTORS pre ITEMS sa NESMU VOLAT, pretoze to C++ robi AUTOMATICKY PRED VOLANIM OPERATOR DELETE[].

				::delete[]((int8_t*)Object);
			}
			else
			{
				std::wcout << L"void CNewDeleteDerived::OPERATOR DELETE[](void* Object, size_t BufferSize) CALLED ! OBJECT [" << Object << L"] BUFFER SIZE [" << BufferSize << L"] !" << std::endl;
			}
		}

		// !!!!! Tento CODE NIE JE PLATFORM INDEPENDENT, pretoze C++ NEDEFINUJE, ze do OPERATOR NEW[] sa MUSI ako SIZE zaslat VALUE [SIZEOF(size_t)+SIZEOF(CNewDeleteDerived)*N]. VALUE [SIZEOF(size_t)] sluziaca na ulozene poctu ITEMS je IMPLEMENTATION DEPENDENT.
		void* operator new[](size_t Size, size_t ItemSize, std::wstring& String1, std::wstring& String2)
		{
			int8_t*												Buffer=::new int8_t[Size];
			size_t												NumberOfItemsPlaceholderSize=sizeof(size_t);

			// !!!!! MEMORY pre SIZE PLACEHOLDER sa MUSI VYMAZAT, pretoze C++ v skutocnosti pouziva iba SIZEOF(int) BYTES a ostatne necha NENAINICIALIZOVANE.
			for (size_t Index=0;Index<NumberOfItemsPlaceholderSize;Index++)
			{
				Buffer[Index]=0;
			}

			// !!! PARAMETER 'Size' je rovny [sizeof(size_t)+N*sizeof(CNewDeleteDerived)], kde v sizeof(size_t) je ulozena hodnota N rovnajuca sa POCTU ITEMS v ARRAY.
			size_t												NumberOfItems=(Size-NumberOfItemsPlaceholderSize)/sizeof(CNewDeleteDerived);
			CNewDeleteDerived*									FirstItem=(CNewDeleteDerived*) (Buffer+NumberOfItemsPlaceholderSize);

			// !!!!! CONSTRUCTORS pre ITEMS sa NESMU VOLAT, pretoze to C++ robi AUTOMATICKY pri navrate z OPERATOR NEW[].

			std::wcout << L"void* CNewDeleteDerived::OPERATOR NEW[](size_t Size, size_t ItemSize, wstring& String1, wstring& String2) CALLED ! SIZE [" << Size << L"] ITEM SIZE [" << ItemSize << L"] STRING 1 [" << String1 << L"] STRING 2 [" << String2 << L"] ALLOCATED MEMORY [" << Buffer << L"] NUMBER OF ITEMS [" << NumberOfItems << L"] ITEM [" << FirstItem << L"] !" << std::endl;

			// !!!!! OPERATOR[] vracia POINTER na BUFFER a NIE POINTER na 1. ITEM. Az C++ COMPILER AUTOMATICKY posuva tento POINTER o SIZEOF(size_t) BYTES na 1. ITEM alokovaneho ARRAY.
			return(Buffer);
		}

		// !!!!! Tento CODE NIE JE PLATFORM INDEPENDENT, pretoze C++ NEDEFINUJE, ze do OPERATOR NEW[] sa MUSI ako SIZE zaslat VALUE [SIZEOF(size_t)+SIZEOF(CNewDeleteDerived)*N]. VALUE [SIZEOF(size_t)] sluziaca na ulozene poctu ITEMS je IMPLEMENTATION DEPENDENT.
		// !!!!! 1. PARAMETER NEUKAZUJE na 1. ITEM v ARRAY, ale na ZACIATOK alokovaneho BUFFER, ktory je dlhsi o SIZEOF(size_t) BYTES, pretoze na zaciatku je ulozeny pocet ITEMS v ARRAY.
		// !!!!! 2. PARAMETER je POCET BYTES, ktore BUFFER OBSAHUJE.
		void operator delete[](void* Object, size_t BufferSize, std::wstring& String1, std::wstring& String2)
		{
			if (Object!=nullptr)
			{
				// !!! PARAMETER Object sa odkazuje na BUFFER, ktora bol alokovany v NEW[].
				int8_t*											Buffer=(int8_t*) Object;
				size_t*											PointerToNumberOfItemsPlaceholder=(size_t*) Buffer;
				size_t											NumberOfItems=*PointerToNumberOfItemsPlaceholder;
				size_t											NumberOfItemsPlaceholderSize=sizeof(size_t);
				// !!! PRVY ITEM sa nachadza az SIZEOF(size_t) BYTES NESKOR, pretoze prvych sizeof(size_t) BYTES obsahuje POCET alokovanych ITEMS.
				CNewDeleteDerived*								FirstItem=(CNewDeleteDerived*) (Buffer+NumberOfItemsPlaceholderSize);

				std::wcout << L"void CNewDeleteDerived::OPERATOR DELETE[](void* Object, size_t BufferSize, wstring& String1, wstring& String2) CALLED ! OBJECT [" << Object << L"] BUFFER SIZE [" << BufferSize << L"] STRING 1 [" << String1 << L"] STRING 2 [" << String2 << L"] NUMBER OF ITEMS [" << NumberOfItems << L"] FIRST ITEM [" << FirstItem << L"] !" << std::endl;

				::delete[]((int8_t*)Object);
			}
			else
			{
				std::wcout << L"void CNewDeleteDerived::OPERATOR DELETE[](void* Object, size_t BufferSize, wstring& String1, wstring& String2) CALLED ! OBJECT [" << Object << L"] BUFFER SIZE [" << BufferSize << L"] STRING 1 [" << String1 << L"] STRING 2 [" << String2 << L"] !" << std::endl;
			}
		}

	public:
		int GetDummyBase1A(void) const noexcept
		{
			return(MDummyBase1A);
		}

		void SetDummyBase1A(int Value)
		{
			MDummyBase1A=Value;
		}

		int GetDummyBase1B(void) const noexcept
		{
			return(MDummyBase1B);
		}

		void SetDummyBase1B(int Value)
		{
			MDummyBase1B=Value;
		}

		int GetDummyBase2A(void) const noexcept
		{
			return(MDummyBase2A);
		}

		void SetDummyBase2A(int Value)
		{
			MDummyBase2A=Value;
		}

		int GetDummyBase2B(void) const noexcept
		{
			return(MDummyBase2B);
		}

		void SetDummyBase2B(int Value)
		{
			MDummyBase2B=Value;
		}

		int GetDummyDerivedA(void) const noexcept
		{
			return(MDummyDerivedA);
		}

		void SetDummyDerivedA(int Value)
		{
			MDummyDerivedA=Value;
		}

		int GetDummyDerivedB(void) const noexcept
		{
			return(MDummyDerivedB);
		}

		void SetDummyDerivedB(int Value)
		{
			MDummyDerivedB=Value;
		}

		int GetDummyDerivedC(void) const noexcept
		{
			return(MDummyDerivedC);
		}

		void SetDummyDerivedC(int Value)
		{
			MDummyDerivedC=Value;
		}

		int GetDummyDerivedD(void) const noexcept
		{
			return(MDummyDerivedD);
		}

		void SetDummyDerivedD(int Value)
		{
			MDummyDerivedD=Value;
		}

	public:
		CNewDeleteDerived(void)
		{
			std::wcout << L"CONSTRUCTOR CNewDeleteDerived CALLED !" << std::endl;

			MDummyBase1A=1;
			MDummyBase1B=2;
			MDummyBase2A=3;
			MDummyBase2B=4;
			MDummyDerivedA=5;
			MDummyDerivedB=6;
			MDummyDerivedC=7;
			MDummyDerivedD=8;
		}

	public:
		CNewDeleteDerived(bool ThrowException)
		{
			std::wcout << L"CONSTRUCTOR CNewDeleteDerived CALLED !" << std::endl;

			MDummyBase1A=1;
			MDummyBase1B=2;
			MDummyBase2A=3;
			MDummyBase2B=4;
			MDummyDerivedA=5;
			MDummyDerivedB=6;
			MDummyDerivedC=7;
			MDummyDerivedD=8;

			if (ThrowException==true)
			{
				throw(std::wstring(L"EXCEPTION THROWN !"));
			}
		}

		// !!!!! Ak sa pretazuje OPERATOR NEW a OPERATOR DELETE pre CLASS a tato CLASS moze byt v DEDICSKEJ HIERARCHII, tak BASE CLASS MUSI MAT VIRTUAL DESTRUCTOR, inak PRETAZENY OPERATOR NEW a OPERATOR DELETE NEBUDU FUNGOVAT SPRAVNE.
		virtual ~CNewDeleteDerived(void) override
		{
			std::wcout << L"!!!!! DESTRUCTOR CNewDeleteDerived CALLED ! DUMMY BASE 1A [" << MDummyBase1A << L"] DUMMY BASE 1B [" << MDummyBase1B << L"] DUMMY BASE 2A [" << MDummyBase2A << L"] DUMMY BASE 2B [" << MDummyBase2B << L"] DUMMY DERIVED A [" << MDummyDerivedA << L"] DUMMY DERIVED B [" << MDummyDerivedB << L"] DUMMY DERIVED C [" << MDummyDerivedC << L"] DUMMY DERIVED D [" << MDummyDerivedD << L"] !" << std::endl;
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------