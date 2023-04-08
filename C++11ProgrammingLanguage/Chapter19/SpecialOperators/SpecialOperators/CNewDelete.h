//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
#include <string>
//-----------------------------------------------------------------------------
class CNewDelete
{
//-----------------------------------------------------------------------------
	protected:
		int														MDummyA;
		int														MDummyB;
		int														MDummyC;
		int														MDummyD;

	public:
		void* operator new(size_t Size)
		{
			int8_t*												Buffer=::new int8_t[Size];

			std::wcout << L"void* CNewDelete::OPERATOR NEW(size_t Size) CALLED ! SIZE [" << Size << L"] BUFFER [" << Buffer << L"] !" << std::endl;

			return(Buffer);
		}

		void operator delete(void* Object)
		{
			std::wcout << L"void CNewDelete::OPERATOR DELETE(void* Object) CALLED ! OBJECT [" << Object << L"] !" << std::endl;

			if (Object!=nullptr)
			{
				::delete[]((int8_t*)Object);
			}
		}

		void operator delete(void* Object, size_t BufferSize)
		{
			std::wcout << L"void CNewDelete::OPERATOR DELETE(void* Object, size_t BufferSize) CALLED ! OBJECT [" << Object << L"] BUFFER SIZE [" << BufferSize << L"] !" << std::endl;

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
			std::wcout << L"void CNewDelete::OPERATOR DELETE(void* Object, wstring String) CALLED ! OBJECT [" << Object << L"] STRING [" << String << L"] !" << std::endl;

			if (Object!=nullptr)
			{
				::delete[]((int8_t*)Object);
			}
		}

		void operator delete(void* Object, size_t BufferSize, std::wstring& String)
		{
			std::wcout << L"void CNewDelete::OPERATOR DELETE(void* Object, size_t BufferSize, wstring String) CALLED ! OBJECT [" << Object << L"] BUFFER SIZE [" << BufferSize << L"] STRING [" << String << L"] !" << std::endl;

			if (Object!=nullptr)
			{
				::delete[]((int8_t*)Object);
			}
		}

		void* operator new(size_t Size, std::wstring& String1, std::wstring& String2)
		{
			int8_t*												Buffer=::new int8_t[Size];

			std::wcout << L"void* CNewDelete::OPERATOR NEW(size_t Size, wstring String1, wstring String2) CALLED ! SIZE [" << Size << L"] STRING 1 [" << String1 << L"] STRING 2 [" << String2 << L"] BUFFER [" << Buffer << L"] !" << std::endl;

			return(Buffer);
		}

		void operator delete(void* Object, std::wstring& String1, std::wstring& String2)
		{
			std::wcout << L"void CNewDelete::OPERATOR DELETE(void* Object, wstring String1, wstring String2) CALLED ! OBJECT [" << Object << L"] STRING 1 [" << String1 << L"] STRING 2 [" << String2 << L"] !" << std::endl;

			if (Object!=nullptr)
			{
				::delete[]((int8_t*)Object);
			}
		}

		void operator delete(void* Object, size_t BufferSize, std::wstring& String1, std::wstring& String2)
		{
			std::wcout << L"void CNewDelete::OPERATOR DELETE(void* Object, size_t BufferSize, wstring String1, wstring String2) CALLED ! OBJECT [" << Object << L"] BUFFER SIZE [" << BufferSize << L"] STRING 1 [" << String1 << L"] STRING 2 [" << String2 << L"] !" << std::endl;

			if (Object!=nullptr)
			{
				::delete[]((int8_t*)Object);
			}
		}

	public:
		// !!!!! Tento CODE NIE JE PLATFORM INDEPENDENT, pretoze C++ NEDEFINUJE, ze do OPERATOR NEW[] sa MUSI ako SIZE zaslat VALUE [SIZEOF(size_t)+SIZEOF(CNewDelete)*N]. VALUE [SIZEOF(size_t)] sluziaca na ulozene poctu ITEMS je IMPLEMENTATION DEPENDENT.
		void* operator new[](size_t Size)
		{
			int8_t*												Buffer=::new int8_t[Size];
			size_t												NumberOfItemsPlaceholderSize=sizeof(size_t);

			// !!!!! MEMORY pre SIZE PLACEHOLDER sa MUSI VYMAZAT, pretoze C++ v skutocnosti pouziva iba SIZEOF(int) BYTES a ostatne necha NENAINICIALIZOVANE.
			for (size_t Index=0;Index<NumberOfItemsPlaceholderSize;Index++)
			{
				Buffer[Index]=0;
			}

			size_t												ItemSize=sizeof(CNewDelete);
			// !!! PARAMETER 'Size' je rovny [sizeof(size_t)+N*sizeof(CNewDelete)], kde v sizeof(size_t) je ulozena hodnota N rovnajuca sa POCTU ITEMS v ARRAY.
			size_t												NumberOfItems=(Size-NumberOfItemsPlaceholderSize)/sizeof(CNewDelete);
			CNewDelete*											FirstItem=(CNewDelete*) (Buffer+NumberOfItemsPlaceholderSize);

			// !!!!! CONSTRUCTORS pre ITEMS sa NESMU VOLAT, pretoze to C++ robi AUTOMATICKY pri navrate z OPERATOR NEW[].

			std::wcout << L"void* CNewDeleteDerived::OPERATOR NEW[](size_t Size) CALLED ! SIZE [" << Size << L"] ITEM SIZE [" << ItemSize << L"] ALLOCATED MEMORY [" << Buffer << L"] NUMBER OF ITEMS [" << NumberOfItems << L"] FIRST ITEM [" << FirstItem << L"] !" << std::endl;

			// !!!!! OPERATOR[] vracia POINTER na BUFFER a NIE POINTER na 1. ITEM. Az C++ COMPILER AUTOMATICKY posuva tento POINTER o SIZEOF(size_t) BYTES na 1. ITEM alokovaneho ARRAY.
			return(Buffer);
		}

		// !!!!! Tento CODE NIE JE PLATFORM INDEPENDENT, pretoze C++ NEDEFINUJE, ze do OPERATOR NEW[] sa MUSI ako SIZE zaslat VALUE [SIZEOF(size_t)+SIZEOF(CNewDelete)*N]. VALUE [SIZEOF(size_t)] sluziaca na ulozene poctu ITEMS je IMPLEMENTATION DEPENDENT.
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
				CNewDelete*										FirstItem=(CNewDelete*) (Buffer+NumberOfItemsPlaceholderSize);

				std::wcout << L"void CNewDelete::OPERATOR DELETE[](void* Object, size_t BufferSize) CALLED ! OBJECT [" << Object << L"] BUFFER SIZE [" << BufferSize << L"] NUMBER OF ITEMS [" << NumberOfItems << L"] FIRST ITEM [" << FirstItem << L"] !" << std::endl;

				// !!!!! DESTRUCTORS pre ITEMS sa NESMU VOLAT, pretoze to C++ robi AUTOMATICKY PRED VOLANIM OPERATOR DELETE[].

				::delete[]((int8_t*)Object);
			}
			else
			{
				std::wcout << L"void CNewDelete::OPERATOR DELETE[](void* Object, size_t BufferSize) CALLED ! OBJECT [" << Object << L"] BUFFER SIZE [" << BufferSize << L"] !" << std::endl;
			}
		}

		// !!!!! Tento CODE NIE JE PLATFORM INDEPENDENT, pretoze C++ NEDEFINUJE, ze do OPERATOR NEW[] sa MUSI ako SIZE zaslat VALUE [SIZEOF(size_t)+SIZEOF(CNewDelete)*N]. VALUE [SIZEOF(size_t)] sluziaca na ulozene poctu ITEMS je IMPLEMENTATION DEPENDENT.
		void* operator new[](size_t Size, size_t ItemSize, std::wstring& String1, std::wstring& String2)
		{
			int8_t*												Buffer=::new int8_t[Size];
			size_t												NumberOfItemsPlaceholderSize=sizeof(size_t);

			// !!!!! MEMORY pre SIZE PLACEHOLDER sa MUSI VYMAZAT, pretoze C++ v skutocnosti pouziva iba SIZEOF(int) BYTES a ostatne necha NENAINICIALIZOVANE.
			for (size_t Index=0;Index<NumberOfItemsPlaceholderSize;Index++)
			{
				Buffer[Index]=0;
			}

			// !!! PARAMETER 'Size' je rovny [sizeof(size_t)+N*sizeof(CNewDelete)], kde v sizeof(size_t) je ulozena hodnota N rovnajuca sa POCTU ITEMS v ARRAY.
			size_t												NumberOfItems=(Size-NumberOfItemsPlaceholderSize)/sizeof(CNewDelete);
			CNewDelete*											FirstItem=(CNewDelete*) (Buffer+NumberOfItemsPlaceholderSize);

			// !!!!! CONSTRUCTORS pre ITEMS sa NESMU VOLAT, pretoze to C++ robi AUTOMATICKY pri navrate z OPERATOR NEW[].

			std::wcout << L"void* CNewDelete::OPERATOR NEW[](size_t Size, size_t ItemSize, wstring& String1, wstring& String2) CALLED ! SIZE [" << Size << L"] ITEM SIZE [" << ItemSize << L"] STRING 1 [" << String1 << L"] STRING 2 [" << String2 << L"] ALLOCATED MEMORY [" << Buffer << L"] NUMBER OF ITEMS [" << NumberOfItems << L"] FIRST ITEM [" << FirstItem << L"] !" << std::endl;

			// !!!!! OPERATOR[] vracia POINTER na BUFFER a NIE POINTER na 1. ITEM. Az C++ COMPILER AUTOMATICKY posuva tento POINTER o SIZEOF(size_t) BYTES na 1. ITEM alokovaneho ARRAY.
			return(Buffer);
		}

		// !!!!! Tento CODE NIE JE PLATFORM INDEPENDENT, pretoze C++ NEDEFINUJE, ze do OPERATOR NEW[] sa MUSI ako SIZE zaslat VALUE [SIZEOF(size_t)+SIZEOF(CNewDelete)*N]. VALUE [SIZEOF(size_t)] sluziaca na ulozene poctu ITEMS je IMPLEMENTATION DEPENDENT.
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
				// !!! PRVY ITEM sa nachadza az sizeof(size_t) BYTES NESKOR, pretoze prvych sizeof(size_t) BYTES obsahuje POCET alokovanych ITEMS.
				CNewDelete*										FirstItem=(CNewDelete*) (Buffer+NumberOfItemsPlaceholderSize);

				std::wcout << L"void CNewDelete::OPERATOR DELETE[](void* Object, size_t BufferSize, wstring& String1, wstring& String2) CALLED ! OBJECT [" << Object << L"] BUFFER SIZE [" << BufferSize << L"] STRING 1 [" << String1 << L"] STRING 2 [" << String2 << L"] NUMBER OF ITEMS [" << NumberOfItems << L"] FIRST ITEM [" << FirstItem << L"] !" << std::endl;

				// !!!!! DESTRUCTORS pre jednotlive ITEMS by sa NEMALI volat tu, ale v CALLING CODE.

				::delete[]((int8_t*)Object);
			}
			else
			{
				std::wcout << L"void CNewDelete::OPERATOR DELETE[](void* Object, size_t BufferSize, wstring& String1, wstring& String2) CALLED ! OBJECT [" << Object << L"] BUFFER SIZE [" << BufferSize << L"] STRING 1 [" << String1 << L"] STRING 2 [" << String2 << L"] !" << std::endl;
			}
		}

	public:
		int GetDummyA(void) const noexcept
		{
			return(MDummyA);
		}

		void SetDummyA(int Value)
		{
			MDummyA=Value;
		}

		int GetDummyB(void) const noexcept
		{
			return(MDummyB);
		}

		void SetDummyB(int Value)
		{
			MDummyB=Value;
		}

		int GetDummyC(void) const noexcept
		{
			return(MDummyC);
		}

		void SetDummyC(int Value)
		{
			MDummyC=Value;
		}

		int GetDummyD(void) const noexcept
		{
			return(MDummyD);
		}

		void SetDummyD(int Value)
		{
			MDummyD=Value;
		}

	public:
		CNewDelete(void)
		{
			std::wcout << L"CONSTRUCTOR CNewDelete CALLED !" << std::endl;

			MDummyA=1;
			MDummyB=2;
			MDummyC=3;
			MDummyD=4;
		}

		// !!!!! Ak sa pretazuje OPERATOR NEW a OPERATOR DELETE pre CLASS a tato CLASS moze byt v DEDICSKEJ HIERARCHII, tak BASE CLASS MUSI MAT VIRTUAL DESTRUCTOR, inak PRETAZENY OPERATOR NEW a OPERATOR DELETE NEBUDU FUNGOVAT SPRAVNE.
		virtual ~CNewDelete(void)
		{
			std::wcout << L"!!!!! DESTRUCTOR CNewDelete CALLED ! DUMMY A [" << MDummyA << L"] DUMMY B [" << MDummyB << L"] DUMMY C [" << MDummyC << L"] DUMMY D [" << MDummyD << L"] !" << std::endl;
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------