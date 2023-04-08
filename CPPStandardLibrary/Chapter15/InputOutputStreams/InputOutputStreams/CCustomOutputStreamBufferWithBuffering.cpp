//-----------------------------------------------------------------------------
#include "CCustomOutputStreamBufferWithBuffering.h"
#include <iostream>
//-----------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
CCustomOutputStreamBufferWithBuffering::CCustomOutputStreamBufferWithBuffering(void)
{
	// !!! Nastavia sa POINTERS PBASE, PPTR a EPPTR.
	// !!!!! POINTER EPPTR musi ukazovat 1 POSITION ZA KONIEC CUSTOM BUFFER.
	setp(MBuffer,MBuffer+BUFFER_SIZE);
}
//-----------------------------------------------------------------------------
CCustomOutputStreamBufferWithBuffering::~CCustomOutputStreamBufferWithBuffering(void)
{
	// !!! Urobi sa FLUSH CUSTOM BUFFER do DATA STORE.
	sync();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void CCustomOutputStreamBufferWithBuffering::FlushCustomBufferToDataStore(void)
{
	ptrdiff_t													NumberOfCharactersInCustomBuffer=(pptr()-pbase());

	for(ptrdiff_t Index=0;Index<NumberOfCharactersInCustomBuffer;Index++)
	{
		// CHARACTERS z CUSTOM BUFFER sa zapisu do DATA STORE.
		MDataStore+=*(pbase()+Index);
	}

	// !!! Zmeni sa pozicia PPTR.
	pbump(static_cast<int>(-NumberOfCharactersInCustomBuffer));
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
CCustomOutputStreamBufferWithBuffering::int_type CCustomOutputStreamBufferWithBuffering::overflow(int_type Character)
{
	wcout << L"METHOD overflow() CALLED with PARAMETER [" << wchar_t(Character) << L"] !" << endl;

	if (traits_type::eq_int_type(Character,wstreambuf::traits_type::eof())==false)
	{
		if (pptr()==epptr())
		{
			// !!! CUSTOM BUFFER je PLNY, a preto jeho obsah je nutne presunut do DATA STORE.
			FlushCustomBufferToDataStore();
		}

		// !!! Novy CHARACTER sa zapise do CUSTOM BUFFER.
		*(pptr())=Character;

		// PPTR sa posunie o 1 CHARACTER.
		pbump(1);
	}

	return(Character);
}
//-----------------------------------------------------------------------------
streamsize CCustomOutputStreamBufferWithBuffering::xsputn(const char_type* String, streamsize Size)
{
	wstring														TemporaryString(String,Size);

	wcout << L"METHOD xsputn() CALLED with PARAMETER [" << TemporaryString << L"] !" << endl;

	// !!! Tu by sa dal pouzit aj efektivnejsi sposob zapisu do CUSTOM BUFFER, alebo priamo do DATA STORE.
	for(streamsize Index=0;Index<Size;Index++)
	{
		if (pptr()==epptr())
		{
			// !!! CUSTOM BUFFER je PLNY, a preto jeho obsah je nutne presunut do DATA STORE.
			FlushCustomBufferToDataStore();
		}

		// !!! Novy CHARACTER sa zapise do CUSTOM BUFFER.
		*(pptr())=TemporaryString[Index];

		// PPTR sa posunie o 1 CHARACTER.
		pbump(1);
	}

	return(Size);
}
//-----------------------------------------------------------------------------
int CCustomOutputStreamBufferWithBuffering::sync(void)
{
	wcout << L"METHOD sync() CALLED !" << endl;

	// !!! Presunie CHARACTERS z CUSTOM BUFFER do DATA STORE.
	FlushCustomBufferToDataStore();

	return(0);
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
const wstring& CCustomOutputStreamBufferWithBuffering::GetDataStore(void) const noexcept
{
	return(MDataStore);
}
//-----------------------------------------------------------------------------