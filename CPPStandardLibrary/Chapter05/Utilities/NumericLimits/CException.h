//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <string>
//-------------------------------------------------------------------------------------------------------
class CException
{
//-------------------------------------------------------------------------------------------------------
	private:
		std::wstring											MMessage;

	public:
		CException& operator=(const CException& Other)
		{
			MMessage=Other.MMessage;

			return(*this);
		}

		CException& operator=(CException&& Other)
		{
			MMessage=std::move(Other.MMessage);

			return(*this);
		}

		CException& operator=(const CException&& Other)
		{
			MMessage=std::move(Other.MMessage);

			return(*this);
		}

	public:
		const std::wstring& GetMessage(void) const
		{
			return(MMessage);
		}

	public:
		CException(const std::wstring& Message)
			: MMessage(Message)
		{
		}

		CException(const CException& Other)
			: MMessage(Other.MMessage)
		{
		}

		CException(CException&& Other)
			: MMessage(std::move(Other.MMessage))
		{
		}

		CException(const CException&& Other)
			: MMessage(std::move(Other.MMessage))
		{
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------