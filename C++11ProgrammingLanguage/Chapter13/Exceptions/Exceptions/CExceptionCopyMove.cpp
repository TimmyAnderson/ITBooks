//-----------------------------------------------------------------------------
#include "CExceptionCopyMove.h"
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
CExceptionCopyMove::CExceptionCopyMove(const wstring& Value)
	: MValue(Value)
{
	wcout << L"CONSTRUCTOR [" << __func__ << L"()] CALLED !" << endl;
}
//-----------------------------------------------------------------------------
CExceptionCopyMove::CExceptionCopyMove(const CExceptionCopyMove& Value)
	: MValue(Value.MValue)
{
	wcout << L"!!!!! COPY CONSTRUCTOR [" << __func__ << L"()] CALLED !" << endl;
}
//-----------------------------------------------------------------------------
CExceptionCopyMove::CExceptionCopyMove(CExceptionCopyMove&& Value) noexcept
	: MValue(std::move(Value.MValue))
{
	wcout << L"!!!!! MOVE CONSTRUCTOR [" << __func__ << L"()] CALLED !" << endl;
}
//-----------------------------------------------------------------------------
CExceptionCopyMove::~CExceptionCopyMove(void)
{
	wcout << L"DESTRUCTOR [" << __func__ << L"()] CALLED !" << endl;
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
CExceptionCopyMove& CExceptionCopyMove::operator=(const CExceptionCopyMove& Value)
{
	wcout << L"!!!!! COPY OPERATOR= [" << __func__ << L"()] CALLED !" << endl;

	MValue=Value.MValue;

	return(*this);
}
//-----------------------------------------------------------------------------
CExceptionCopyMove& CExceptionCopyMove::operator=(CExceptionCopyMove&& Value) noexcept
{
	wcout << L"!!!!! MOVE OPERATOR= [" << __func__ << L"()] CALLED !" << endl;

	MValue=move(Value.MValue);

	return(*this);
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
const wstring& CExceptionCopyMove::GetValue(void) const noexcept
{
	return(MValue);
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
wstring CExceptionCopyMove::GetTextMessage(void) const noexcept
{
	wstring														Message;

	Message.append(L"EXCEPTION [CExceptionCopyMove] - VALUE [");
	Message.append(MValue);
	Message.append(L"] !");

	return(Message);
}
//-----------------------------------------------------------------------------