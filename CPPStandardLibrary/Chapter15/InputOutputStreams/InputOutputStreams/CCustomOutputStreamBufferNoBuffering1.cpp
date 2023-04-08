//-----------------------------------------------------------------------------
#include "CCustomOutputStreamBufferNoBuffering1.h"
#include <iostream>
//-----------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
CCustomOutputStreamBufferNoBuffering1::int_type CCustomOutputStreamBufferNoBuffering1::overflow(int_type Character)
{
	wcout << L"METHOD overflow() CALLED with PARAMETER [" << Character << L"] !" << endl;

	if (traits_type::eq_int_type(Character,wstreambuf::traits_type::eof())==false)
	{
		MDataStore+=Character;
	}

	return(Character);
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
const wstring& CCustomOutputStreamBufferNoBuffering1::GetDataStore(void) const noexcept
{
	return(MDataStore);
}
//-----------------------------------------------------------------------------