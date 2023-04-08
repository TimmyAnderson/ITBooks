//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <string>
#include <exception>
//-------------------------------------------------------------------------------------------------------
// !!! CUSTOM EXCEPTION, ktora dedi z CLASS [exception].
class CException : public std::exception
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
		virtual const char* what(void) const noexcept
		{
			return(MMessage.c_str());
		}

	public:
		const std::string& GetMessage(void) const
		{
			return(MMessage);
		}

	public:
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
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------