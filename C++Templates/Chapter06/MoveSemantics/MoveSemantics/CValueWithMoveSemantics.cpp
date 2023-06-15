//----------------------------------------------------------------------------------------------------------------------
#include "CValueWithMoveSemantics.h"
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CValueWithMoveSemantics::CValueWithMoveSemantics(const wchar_t* Buffer)
	: MBuffer(nullptr)
{
	if (Buffer!=nullptr)
	{
		size_t													Length=GetLength(Buffer);
		wchar_t*												LocalBuffer=new wchar_t[Length+1];

		CopyData(LocalBuffer,Buffer);

		MBuffer=LocalBuffer;
	}

	wcout << L"CONSTRUCTOR CALLED !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
CValueWithMoveSemantics::CValueWithMoveSemantics(const CValueWithMoveSemantics& Other)
	: MBuffer(nullptr)
{
	if (Other.MBuffer!=nullptr)
	{
		size_t													Length=GetLength(Other.MBuffer);
		wchar_t*												Buffer=new wchar_t[Length+1];

		CopyData(Buffer,Other.MBuffer);

		MBuffer=Buffer;
	}

	wcout << L"COPY CONSTRUCTOR CALLED !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
CValueWithMoveSemantics::CValueWithMoveSemantics(CValueWithMoveSemantics&& Other) noexcept
	: MBuffer(nullptr)
{
	MBuffer=Other.MBuffer;

	Other.MBuffer=nullptr;

	wcout << L"MOVE CONSTRUCTOR CALLED !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
CValueWithMoveSemantics::~CValueWithMoveSemantics(void) noexcept
{
	if (MBuffer!=nullptr)
	{
		delete[](MBuffer);
		MBuffer=nullptr;
	}

	wcout << L"DESTRUCTOR CALLED !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CValueWithMoveSemantics& CValueWithMoveSemantics::operator=(const CValueWithMoveSemantics& Other)
{
	if (MBuffer!=nullptr)
	{
		delete[](MBuffer);
		MBuffer=nullptr;
	}

	if (Other.MBuffer!=nullptr)
	{
		size_t													Length=GetLength(Other.MBuffer);
		wchar_t*												Buffer=new wchar_t[Length+1];

		CopyData(Buffer,Other.MBuffer);

		MBuffer=Buffer;
	}

	wcout << L"OPERATOR [COPY OPERATOR=] CALLED !" << endl;

	return(*this);
}
//----------------------------------------------------------------------------------------------------------------------
CValueWithMoveSemantics& CValueWithMoveSemantics::operator=(CValueWithMoveSemantics&& Other) noexcept
{
	if (MBuffer!=nullptr)
	{
		delete[](MBuffer);
		MBuffer=nullptr;
	}

	MBuffer=Other.MBuffer;

	Other.MBuffer=nullptr;

	wcout << L"OPERATOR [MOVE OPERATOR=] CALLED !" << endl;

	return(*this);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
size_t CValueWithMoveSemantics::GetLength(const wchar_t* Buffer)
{
	size_t														Length=0;

	if (Buffer!=nullptr)
	{
		while(Buffer[Length]!=L'\0')
		{
			Length++;
		}
	}

	return(Length);
}
//----------------------------------------------------------------------------------------------------------------------
void CValueWithMoveSemantics::CopyData(wchar_t* Destination, const wchar_t* Source)
{
	if (Source!=nullptr)
	{
		size_t													Position=0;

		while(Source[Position]!=L'\0')
		{
			wchar_t												Char=Source[Position];

			Destination[Position]=Char;
			Position++;
		}

		Destination[Position]=L'\0';
	}
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
const wchar_t* CValueWithMoveSemantics::GetBuffer(void) const noexcept
{
	return(MBuffer);
}
//----------------------------------------------------------------------------------------------------------------------