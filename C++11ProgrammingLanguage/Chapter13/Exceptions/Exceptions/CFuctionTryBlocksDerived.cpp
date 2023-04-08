//-----------------------------------------------------------------------------
#include "CFuctionTryBlocksDerived.h"
#include "CException.h"
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
CFuctionTryBlocksDerived::CFuctionTryBlocksDerived(const wstring& Value)
// !!! FUNCTION TRY BLOCKS zachyti EXCEPTION z BASE CLASS CONSTRUCTORS.
try
	: CFuctionTryBlocksBase(Value)
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
CFuctionTryBlocksDerived::~CFuctionTryBlocksDerived(void)
{
	wcout << L"DESTRUCTOR [" << __func__ << L"()] CALLED !" << endl;
}
//-----------------------------------------------------------------------------