//-------------------------------------------------------------------------------------------------------
#include "NewDelete.h"
#include <stdio.h>
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
CNewDelete::CNewDelete(void)
{
	wprintf_s(L"CONSTRUCTOR CALLED !\n");

	MDummyA=1;
	MDummyB=2;
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

	if (Object!=NULL)
	{
		::delete[](Object);
	}
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

	if (Object!=NULL)
	{
		::delete[](Object);
	}
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

	if (Object!=NULL)
	{
		::delete[](Object);
	}
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void* CNewDelete::operator new[](size_t Size)
{
	__int8*														Buffer=::new __int8[Size];
	size_t														NumberOfItemsPlaceholderSize=sizeof(size_t);

	// !!!!! MEMORY pre SIZE PLACEHOLDER sa MUSI VYMAZAT, pretoze C++ v skutocnosti pouziva iba SIZEOF(int) BYTES a ostatne necha NENAINICIALIZOVANE.
	for (size_t Index=0;Index<NumberOfItemsPlaceholderSize;Index++)
	{
		Buffer[Index]=0;
	}

	size_t														ItemSize=sizeof(CNewDelete);
	// !!! PARAMETER Size je rovny [sizeof(size_t)+N*sizeof(CNewDelete)], kde v sizeof(size_t) bude ulozena hodnota N.
	size_t														NumberOfItems=(Size-NumberOfItemsPlaceholderSize)/sizeof(CNewDelete);
	CNewDelete*											Item=(CNewDelete*) (Buffer+NumberOfItemsPlaceholderSize);

	// !!!!! CONSTRUCTORS pre ITEMS sa NESMU VOLAT, pretoze to C++ robi AUTOMATICKY pri navrate z OPERATOR NEW[].

	wprintf_s(L"void* CNewDelete::operator new[](size_t Size) CALLED and ALLOCATED MEMORY [%p], ITEM SIZE [%d], NUMBER OF ITEMS [%d] !\n",Buffer,ItemSize,NumberOfItems);

	return(Buffer);
}
//-------------------------------------------------------------------------------------------------------
// !!!!! 2. PARAMETER je IMPLICITNY PARAMETER, ktory zasiela COMPILER pri volani delete[]() a udava dlzku jedneho ITEM, ktore NEW[] ALOKUJE.
void CNewDelete::operator delete[](void* Object, size_t ItemSize)
{
	wprintf_s(L"void CNewDelete::operator delete[](void* Object, size_t ItemSize) CALLED with ITEM SIZE [%d] for ALLOCATED MEMORY [%p] !\n",ItemSize,Object);

	if (Object!=NULL)
	{
		// !!! PARAMETER Object sa odkazuje na BUFFER, ktora bol alokovany v NEW[].
		__int8*													Buffer=(__int8*) Object;
		size_t*													PointerToNumberOfItemsPlaceholder=(size_t*) Buffer;
		size_t													NumberOfItems=*PointerToNumberOfItemsPlaceholder;
		size_t													NumberOfItemsPlaceholderSize=sizeof(size_t);
		// !!! PRVY ITEM sa nachadza az sizeof(size_t) BYTES NESKOR, pretoze prvych sizeof(size_t) BYTES obsahuje POCET alokovanychITEMS.
		CNewDelete*												Item=(CNewDelete*) (Buffer+NumberOfItemsPlaceholderSize);

		// !!!!! DESTRUCTORS pre ITEMS sa NESMU VOLAT, pretoze to C++ robi AUTOMATICKY pri navrate z OPERATOR NEW[].

		::delete[](Object);
	}
}
//-------------------------------------------------------------------------------------------------------
void* CNewDelete::operator new[](size_t Size, size_t ItemSize, wstring& String1, wstring& String2)
{
	__int8*														Buffer=::new __int8[Size];
	size_t														NumberOfItemsPlaceholderSize=sizeof(size_t);

	// !!!!! MEMORY pre SIZE PLACEHOLDER sa MUSI VYMAZAT, pretoze C++ v skutocnosti pouziva iba SIZEOF(int) BYTES a ostatne necha NENAINICIALIZOVANE.
	for (size_t Index=0;Index<NumberOfItemsPlaceholderSize;Index++)
	{
		Buffer[Index]=0;
	}

	// !!! PARAMETER Size je rovny [sizeof(size_t)+N*sizeof(CNewDelete)], kde v sizeof(size_t) bude ulozena hodnota N.
	size_t														NumberOfItems=(Size-NumberOfItemsPlaceholderSize)/sizeof(CNewDelete);
	CNewDelete*											Item=(CNewDelete*) (Buffer+NumberOfItemsPlaceholderSize);

	// !!!!! CONSTRUCTORS pre ITEMS sa NESMU VOLAT, pretoze to C++ robi AUTOMATICKY pri navrate z OPERATOR NEW[].

	wprintf_s(L"void* CNewDelete::operator new[](void* Object, size_t ItemSize, wstring& String1, wstring& String2) CALLED with PARAMS [%s,%s], ITEM SIZE [%d] and ALLOCATED MEMORY [%p] !\n",String1.c_str(),String2.c_str(),ItemSize,Buffer);

	return(Buffer);
}
//-------------------------------------------------------------------------------------------------------
void CNewDelete::operator delete[](void* Object, size_t ItemSize, wstring& String1, wstring& String2)
{
	wprintf_s(L"void CNewDelete::operator delete[](void* Object, size_t ItemSize, wstring& String1, wstring& String2) CALLED with PARAMS [%s,%s], ITEM SIZE [%d] and ALLOCATED MEMORY [%p] !\n",String1.c_str(),String2.c_str(),ItemSize,Object);

	if (Object!=NULL)
	{
		// !!! PARAMETER Object sa odkazuje na BUFFER, ktora bol alokovany v NEW[].
		__int8*													Buffer=(__int8*) Object;
		size_t*													PointerToNumberOfItemsPlaceholder=(size_t*) Buffer;
		size_t													NumberOfItems=*PointerToNumberOfItemsPlaceholder;
		size_t													NumberOfItemsPlaceholderSize=sizeof(size_t);
		// !!! PRVY ITEM sa nachadza az sizeof(size_t) BYTES NESKOR, pretoze prvych sizeof(size_t) BYTES obsahuje POCET alokovanychITEMS.
		CNewDelete*										Item=(CNewDelete*) (Buffer+NumberOfItemsPlaceholderSize);

		// !!! Zavola sa DESTRUCTOR pre KAZDY ITEM, pretoze DELETE[] je volana ako FUNCTION a vtedy C++ NEVOLA AUTOMATICKY DESTRUCTORS.
		// !!!!! V skutocnosti by volanie DESTRUCTORS NEMALO byt priamo v DELETE[], ale v CALLING CODE. Tu je to mozne volat iba preto, ze DELETE[] s VIACERYMI PARAMETERS NIE JE MOZNE VOLAT INAK ako pomocou FUNCTION SYNTAX.
		for (size_t Index=0;Index<NumberOfItems;Index++)
		{
			// !!! EXPLICITNE sa zavola DESTRUCTOR.
			Item->~CNewDelete();

			Item++;
		}

		::delete[](Object);
	}
}
//-------------------------------------------------------------------------------------------------------