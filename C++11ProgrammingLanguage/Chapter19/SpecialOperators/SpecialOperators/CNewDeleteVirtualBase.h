//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CNewDeleteVirtualBase
{
//-----------------------------------------------------------------------------
	protected:
		int														MDummyA;

	public:
		void* operator new(size_t Size)
		{
			int8_t*												Buffer=::new int8_t[Size];

			std::wcout << L"void* CNewDeleteVirtualBase::OPERATOR NEW(size_t Size) CALLED ! SIZE [" << Size << L"] BUFFER [" << Buffer << L"] !" << std::endl;

			return(Buffer);
		}

		void operator delete(void* Object, size_t BufferSize)
		{
			std::wcout << L"void CNewDeleteVirtualBase::OPERATOR DELETE(void* Object, size_t BufferSize) CALLED ! OBJECT [" << Object << L"] BUFFER SIZE [" << BufferSize << L"] !" << std::endl;

			if (Object!=nullptr)
			{
				::delete[]((int8_t*)Object);
			}
		}

		// !!!!! Tento CODE NIE JE PLATFORM INDEPENDENT, pretoze C++ NEDEFINUJE, ze do OPERATOR NEW[] sa MUSI ako SIZE zaslat VALUE [SIZEOF(size_t)+SIZEOF(CNewDeleteVirtualBase)*N]. VALUE [SIZEOF(size_t)] sluziaca na ulozene poctu ITEMS je IMPLEMENTATION DEPENDENT.
		void* operator new[](size_t Size)
		{
			int8_t*												Buffer=::new int8_t[Size];
			size_t												NumberOfItemsPlaceholderSize=sizeof(size_t);

			// !!!!! MEMORY pre SIZE PLACEHOLDER sa MUSI VYMAZAT, pretoze C++ v skutocnosti pouziva iba SIZEOF(int) BYTES a ostatne necha NENAINICIALIZOVANE.
			for (size_t Index=0;Index<NumberOfItemsPlaceholderSize;Index++)
			{
				Buffer[Index]=0;
			}

			size_t												ItemSize=sizeof(CNewDeleteVirtualBase);
			// !!! PARAMETER 'Size' je rovny [sizeof(size_t)+N*sizeof(CNewDeleteVirtualBase)], kde v sizeof(size_t) je ulozena hodnota N rovnajuca sa POCTU ITEMS v ARRAY.
			size_t												NumberOfItems=(Size-NumberOfItemsPlaceholderSize)/sizeof(CNewDeleteVirtualBase);
			CNewDeleteVirtualBase*								FirstItem=(CNewDeleteVirtualBase*) (Buffer+NumberOfItemsPlaceholderSize);

			// !!!!! CONSTRUCTORS pre ITEMS sa NESMU VOLAT, pretoze to C++ robi AUTOMATICKY pri navrate z OPERATOR NEW[].

			std::wcout << L"void* CNewDeleteVirtualBase::OPERATOR NEW[](size_t Size) CALLED ! SIZE [" << Size << L"] ITEM SIZE [" << ItemSize << L"] ALLOCATED MEMORY [" << Buffer << L"] NUMBER OF ITEMS [" << NumberOfItems << L"] FIRST ITEM [" << FirstItem << L"] !" << std::endl;

			// !!!!! OPERATOR[] vracia POINTER na BUFFER a NIE POINTER na 1. ITEM. Az C++ COMPILER AUTOMATICKY posuva tento POINTER o SIZEOF(size_t) BYTES na 1. ITEM alokovaneho ARRAY.
			return(Buffer);
		}

		// !!!!! Tento CODE NIE JE PLATFORM INDEPENDENT, pretoze C++ NEDEFINUJE, ze do OPERATOR NEW[] sa MUSI ako SIZE zaslat VALUE [SIZEOF(size_t)+SIZEOF(CNewDeleteVirtualBase)*N]. VALUE [SIZEOF(size_t)] sluziaca na ulozene poctu ITEMS je IMPLEMENTATION DEPENDENT.
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
				CNewDeleteVirtualBase*							FirstItem=(CNewDeleteVirtualBase*) (Buffer+NumberOfItemsPlaceholderSize);

				std::wcout << L"void CNewDeleteVirtualBase::OPERATOR DELETE[](void* Object, size_t BufferSize) CALLED ! OBJECT [" << Object << L"] BUFFER SIZE [" << BufferSize << L"] NUMBER OF ITEMS [" << NumberOfItems << L"] FIRST ITEM [" << FirstItem << L"] !" << std::endl;

				// !!!!! DESTRUCTORS pre ITEMS sa NESMU VOLAT, pretoze to C++ robi AUTOMATICKY PRED VOLANIM OPERATOR DELETE[].

				::delete[]((int8_t*)Object);
			}
			else
			{
				std::wcout << L"void CNewDeleteVirtualBase::OPERATOR DELETE[](void* Object, size_t BufferSize) CALLED ! OBJECT [" << Object << L"] BUFFER SIZE [" << BufferSize << L"] !" << std::endl;
			}
		}

	public:
		CNewDeleteVirtualBase(void)
		{
			std::wcout << L"CONSTRUCTOR CNewDeleteVirtualBase CALLED !" << std::endl;
		}

		virtual ~CNewDeleteVirtualBase(void)
		{
			std::wcout << L"!!!!! DESTRUCTOR CNewDeleteVirtualBase CALLED !" << std::endl;
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------