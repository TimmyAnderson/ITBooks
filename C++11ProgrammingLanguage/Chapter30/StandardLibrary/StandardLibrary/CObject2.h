//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <string>
#include <exception>
#include <iostream>
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
class CObject2
{
//-------------------------------------------------------------------------------------------------------
	private:
		std::string												MMessage;

	public:
		const std::string& GetMessage(void) const
		{
			return(MMessage);
		}

	public:
		CObject2(const std::string& Message)
			: MMessage(Message)
		{
		}

		virtual ~CObject2(void)
		{
#ifdef _MSC_VER
			bool												IsUncaughtException=uncaught_exception();
			int													NumberOfUncaughtExceptions=uncaught_exceptions();

			cout << "OBJECT 2 - IsUncaughtException [" << IsUncaughtException << "], NumberOfUncaughtExceptions [" << NumberOfUncaughtExceptions << "] !\n";
#else
			bool												IsUncaughtException=uncaught_exception();

			cout << "OBJECT 2 - IsUncaughtException [" << IsUncaughtException << "] !\n";
#endif
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------