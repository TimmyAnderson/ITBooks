//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <string>
//-------------------------------------------------------------------------------------------------------
class CException
{
//-------------------------------------------------------------------------------------------------------
	private:
		std::string												MMessage;

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
		const std::string& GetMessage(void) const
		{
			return(MMessage);
		}

	public:
		CException(void)
			: MMessage()
		{
		}

		CException(const std::string& Message)
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

		virtual ~CException(void)
		{
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------