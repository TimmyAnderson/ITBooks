//-----------------------------------------------------------------------------
#include "CFuctionTryBlocks.h"
#include "CException.h"
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
CFuctionTryBlocks::CFuctionTryBlocks(const wstring& Value)
// !!! FUNCTION TRY BLOCKS zachyti EXCEPTION z MEMBER CONSTRUCTORS.
try
	: MValue(Value)
{
	wcout << L"CONSTRUCTOR [" << __func__ << L"()] CALLED !" << endl;
}
catch(const CException& E)
{
	wcout << L"In CONSTRUCTOR [" << __func__ << L"()] TRY BLOCK FAILED with EXCEPTION [" << E.GetTextMessage() << L"] !" << endl;

	// !!!!! EXCEPTION sa NEDA kompletne spracovat a preto je NUTNE spravit RETHROW.
	throw;
}
//-----------------------------------------------------------------------------
CFuctionTryBlocks::~CFuctionTryBlocks(void)
{
	wcout << L"DESTRUCTOR [" << __func__ << L"()] CALLED !" << endl;
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
const CFuctionTryBlocksMember& CFuctionTryBlocks::GetValue(void) const noexcept
{
	return(MValue);
}
//-----------------------------------------------------------------------------