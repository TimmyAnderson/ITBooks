using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using TransportSessionsSharedLibrary;
using WSHTTPTransportSessionsHost;
//-------------------------------------------------------------------------------------------------------
namespace WSHTTPTransportSessionsClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="CLIENT";

			Console.WriteLine("Press any key to START !");
			Console.ReadLine();

			//CTestHelper.SimpleTest<IDefaultConfiguration>("DefaultConfiguration");

			//CTestHelper.SimpleTest<ITSNotAllowedButBindingAllowsIt>("TSNotAllowedButBindingAllowsIt");

			//CTestHelper.SimpleTest<ITSRequiredAndBindingIsDefault>("TSRequiredAndBindingIsDefault");

			//CTestHelper.SimpleTest<ITSRequiredAndBindingEnablesTS>("TSRequiredAndBindingEnablesTS");

			//CTestHelper.SimpleTest<ITSNotAllowedAndDoNotAllowItNoSecurity>("TSNotAllowedAndDoNotAllowItNoSecurity");

			CTestHelper.SimpleTest<ITSDisabledButSecurityUsed>("TSDisabledButSecurityUsed");

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------