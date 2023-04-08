//-----------------------------------------------------------------------------
#include "CCustomOutputStreamBufferNoBuffering2.h"
#include <iostream>
//-----------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
CCustomOutputStreamBufferNoBuffering2::int_type CCustomOutputStreamBufferNoBuffering2::overflow(int_type Character)
{
	wcout << L"METHOD overflow() CALLED with PARAMETER [" << Character << L"] !" << endl;

	if (traits_type::eq_int_type(Character,wstreambuf::traits_type::eof())==false)
	{
		MDataStore+=Character;
	}

	return(Character);
}
//-----------------------------------------------------------------------------
streamsize CCustomOutputStreamBufferNoBuffering2::xsputn(const char_type* String, streamsize Size)
{
	wstring														TemporaryString(String,Size);

	wcout << L"METHOD xsputn() CALLED with PARAMETER [" << TemporaryString << L"] !" << endl;

	MDataStore+=TemporaryString;

	return(Size);
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
const wstring& CCustomOutputStreamBufferNoBuffering2::GetDataStore(void) const noexcept
{
	return(MDataStore);
}
//-----------------------------------------------------------------------------