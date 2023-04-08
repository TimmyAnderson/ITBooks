//-----------------------------------------------------------------------------
#include "CCustomInputStreamBuffer.h"
#include <iostream>
#include <sstream>
#include <cstring>
//-----------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
CCustomInputStreamBuffer::CCustomInputStreamBuffer(const std::wstring& DataStore)
	: MDataStore(DataStore), MDataStoreOffset(0)
{
	// !!! Nastavia sa POINTERS EBACK, GPTR a EGPTR. Ukazuju na TU ISTU POSITION, pretoze doteraz nebol ZIADEN CHARACTER nacitany z DATA STORE.
	// !!!!! POINTERS ukazuju az ZA PUTBACK BUFFER na poziciu, kde sa nachadza interny BUFFER daneho STREAM BUFFER.
	setg(MBuffer+PUTBACK_BUFFER_SIZE,MBuffer+PUTBACK_BUFFER_SIZE,MBuffer+PUTBACK_BUFFER_SIZE);

	for(size_t Index=0;Index<(PUTBACK_BUFFER_SIZE+BUFFER_SIZE);Index++)
	{
		// Vlozi sa DUMMY CHARACTER.
		MBuffer[Index]=L'-';
	}
}
//-----------------------------------------------------------------------------
CCustomInputStreamBuffer::~CCustomInputStreamBuffer(void)
{
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
bool CCustomInputStreamBuffer::FillBuffer(void)
{
	// !!! Vypocita sa pocet CHARACTERS, ktore PROGRAM nacital z interneho BUFFER. Tieto CHARACTERS su presunute do PUTBACK BUFFER, aby mohla STREAM BUFFER podporoval PUTBACK OPERATIONS.
	ptrdiff_t													NumberOfCharactersToBeMovedToPutbackBuffer=(gptr()-eback());

	// Maximalna dlzka PUTBACK BUFFER je 'PUTBACK_BUFFER_SIZE'.
	if (NumberOfCharactersToBeMovedToPutbackBuffer>PUTBACK_BUFFER_SIZE)
	{
		NumberOfCharactersToBeMovedToPutbackBuffer=PUTBACK_BUFFER_SIZE;
	}

	// !!! Posledne CHARACTERS, ktore boli PROGRAMOM nacitane z interneho BUFFER daneho STREAM BUFFER su prekopirovane do PUTBACK BUFFER, aby STREAM BUFFER podporoval PUTBACK OPERATIONS.
	memmove(MBuffer+(PUTBACK_BUFFER_SIZE-NumberOfCharactersToBeMovedToPutbackBuffer),gptr()-NumberOfCharactersToBeMovedToPutbackBuffer,NumberOfCharactersToBeMovedToPutbackBuffer*sizeof(char_type));

	if (MDataStoreOffset<MDataStore.size())
	{
		ptrdiff_t												NumberOfCharactersReadFromDataStore=0;

		// !!! Nacitaju sa nove CHARACTERS z DATA STORE.
		for(ptrdiff_t Index=0;Index<BUFFER_SIZE && MDataStoreOffset<MDataStore.size();Index++,MDataStoreOffset++,NumberOfCharactersReadFromDataStore++)
		{
			MBuffer[Index+PUTBACK_BUFFER_SIZE]=MDataStore[MDataStoreOffset];
		}

		// !!! POINTER EBACK ukazuje na ZACIATOK PUTBACK BUFFER.
		setg(MBuffer+(PUTBACK_BUFFER_SIZE-NumberOfCharactersToBeMovedToPutbackBuffer),MBuffer+PUTBACK_BUFFER_SIZE,MBuffer+PUTBACK_BUFFER_SIZE+NumberOfCharactersReadFromDataStore);

		return(true);
	}
	else
	{
		return(false);
	}
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
CCustomInputStreamBuffer::int_type CCustomInputStreamBuffer::underflow(void)
{
	// !!! Interny BUFFER daneho STREAM BUFFER este obsahuje CHARACTERS, ktore PROGRAMOM NEBOLI NACITANE, a preto mozne vratit CHARACTER na ktory ukazuje POINTER GPTR.
	if (gptr()<egptr())
	{
		int_type												Character=traits_type::to_int_type(*gptr());

		wcout << L"METHOD underflow() CALLED returning CHARACTER [" << Character << L"] !" << endl;

		return(Character);
	}
	// !!! Interny BUFFER daneho STREAM BUFFER je uz PRAZDY, a preto je potrebne nacitat CHARACTERS z DATA STORE.
	else
	{
		bool													BufferHasData=FillBuffer();

		if (BufferHasData==true)
		{
			int_type											Character=traits_type::to_int_type(*gptr());

			wcout << L"METHOD underflow() CALLED returning CHARACTER [" << Character << L"] ! METHOD has READ DATA STORE !" << endl;

			return(Character);
		}
		else
		{
			int_type											Character=traits_type::eof();

			wcout << L"METHOD underflow() CALLED returning EOF CHARACTER [" << Character << L"] !" << endl;

			return(Character);
		}
	}
}
//-----------------------------------------------------------------------------
streamsize CCustomInputStreamBuffer::xsgetn(char_type* String, streamsize Count)
{
	for(streamsize Index=0;Index<Count;Index++)
	{
		int_type												Character;

		// !!! Interny BUFFER daneho STREAM BUFFER este obsahuje CHARACTERS, ktore PROGRAMOM NEBOLI NACITANE, a preto mozne vratit CHARACTER na ktory ukazuje POINTER GPTR.
		if (gptr()<egptr())
		{
			Character=traits_type::to_int_type(*gptr());

			gbump(1);
		}
		// !!! Interny BUFFER daneho STREAM BUFFER je uz PRAZDY, a preto je potrebne nacitat CHARACTERS z DATA STORE.
		else
		{
			bool													BufferHasData=FillBuffer();

			if (BufferHasData==true)
			{
				Character=traits_type::to_int_type(*gptr());

				gbump(1);
			}
			else
			{
				Character=traits_type::eof();
			}
		}

		if (traits_type::eq_int_type(Character,traits_type::eof())==false)
		{
			String[Index]=Character;
		}
		else
		{
			wstring												TemporaryString(String,Index);

			wcout << L"METHOD xsgetn() CALLED with PARAMETER [" << TemporaryString << L"] !" << endl;

			return(Index);
		}
	}

	wstring														TemporaryString(String,Count);

	wcout << L"METHOD xsgetn() CALLED with PARAMETER [" << TemporaryString << L"] !" << endl;

	return(Count);
}
//-----------------------------------------------------------------------------
CCustomInputStreamBuffer::int_type CCustomInputStreamBuffer::pbackfail(int_type Character)
{
	wcout << L"METHOD pbackfail() CALLED returning CHARACTER [" << Character << L"] !" << endl;

	return(Character);
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
const wstring& CCustomInputStreamBuffer::GetDataStore(void) const noexcept
{
	return(MDataStore);
}
//-----------------------------------------------------------------------------
wstring CCustomInputStreamBuffer::GetPointers(void) const
{
	wstringstream												Stream;

	Stream << L"EBACK [" << static_cast<void*>(eback()) << L"] GPTR [" << static_cast<void*>(gptr()) << L"] EGPTR [" << static_cast<void*>(egptr()) << L"]";

	return(Stream.str());
}
//-----------------------------------------------------------------------------
wstring CCustomInputStreamBuffer::GetBufferContent(void) const
{
	wstring														String(MBuffer,PUTBACK_BUFFER_SIZE+BUFFER_SIZE);

	return(String);
}
//-----------------------------------------------------------------------------