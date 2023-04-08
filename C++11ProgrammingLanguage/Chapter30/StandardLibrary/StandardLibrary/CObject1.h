//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <string>
#include <exception>
#include <iostream>
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
class CObject1
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
		CObject1(const std::string& Message)
			: MMessage(Message)
		{
		}

		virtual ~CObject1(void)
		{
#ifdef _MSC_VER
			bool												IsUncaughtException=uncaught_exception();
			int													NumberOfUncaughtExceptions=uncaught_exceptions();

			cout << "OBJECT 1 - IsUncaughtException [" << IsUncaughtException << "], NumberOfUncaughtExceptions [" << NumberOfUncaughtExceptions << "] !\n";
#else
			bool												IsUncaughtException=uncaught_exception();

			cout << "OBJECT 1 - IsUncaughtException [" << IsUncaughtException << "] !\n";
#endif
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------