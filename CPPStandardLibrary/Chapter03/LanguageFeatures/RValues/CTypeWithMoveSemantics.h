//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <string>
//-------------------------------------------------------------------------------------------------------
class CTypeWithMoveSemantics
{
//-------------------------------------------------------------------------------------------------------
	private:
		std::wstring											MMessage;

	public:
		CTypeWithMoveSemantics& operator=(const CTypeWithMoveSemantics& Other)
		{
			std::wcout << L"COPY OPERATOR= CALLED !" << std::endl;

			MMessage=Other.MMessage;

			return(*this);
		}

		CTypeWithMoveSemantics& operator=(CTypeWithMoveSemantics&& Other)
		{
			std::wcout << L"MOVE OPERATOR= CALLED !" << std::endl;

			MMessage=std::move(Other.MMessage);

			return(*this);
		}

		CTypeWithMoveSemantics& operator=(const CTypeWithMoveSemantics&& Other)
		{
			std::wcout << L"CONSTANT MOVE OPERATOR= CALLED !" << std::endl;

			MMessage=std::move(Other.MMessage);

			return(*this);
		}

	public:
		const std::wstring& GetMessage(void) const
		{
			return(MMessage);
		}

	public:
		CTypeWithMoveSemantics(const std::wstring& Message)
			: MMessage(Message)
		{
			std::wcout << L"DEFAULT CONSTRUCTOR CALLED !" << std::endl;
		}

		CTypeWithMoveSemantics(const CTypeWithMoveSemantics& Other)
			: MMessage(Other.MMessage)
		{
			std::wcout << L"COPY CONSTRUCTOR CALLED !" << std::endl;
		}

		CTypeWithMoveSemantics(CTypeWithMoveSemantics&& Other)
			: MMessage(std::move(Other.MMessage))
		{
			std::wcout << L"MOVE CONSTRUCTOR CALLED !" << std::endl;
		}

		CTypeWithMoveSemantics(const CTypeWithMoveSemantics&& Other)
			: MMessage(std::move(Other.MMessage))
		{
			std::wcout << L"CONSTANT MOVE CONSTRUCTOR CALLED !" << std::endl;
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------