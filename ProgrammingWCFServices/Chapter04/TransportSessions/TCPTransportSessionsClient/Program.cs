using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using TransportSessionsSharedLibrary;
using TCPTransportSessionsHost;
//-------------------------------------------------------------------------------------------------------
namespace TCPTransportSessionsClient
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

			CTestHelper.SimpleTest<IDefaultConfiguration>("DefaultConfiguration");

			// Service je SA NEDA VYTVORIT.
			//CTestHelper.SimpleTest<ITSNotAllowedButBindingAllowsIt>("TSNotAllowedButBindingAllowsIt");

			//CTestHelper.SimpleTest<ITSRequiredAndBindingIsDefault>("TSRequiredAndBindingIsDefault");

			//CTestHelper.SimpleTest<ITSRequiredAndBindingEnablesTS>("TSRequiredAndBindingEnablesTS");

			// Service je SA NEDA VYTVORIT.
			//CTestHelper.SimpleTest<ITSNotAllowedAndDoNotAllowIt>("TSNotAllowedAndDoNotAllowIt");

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------