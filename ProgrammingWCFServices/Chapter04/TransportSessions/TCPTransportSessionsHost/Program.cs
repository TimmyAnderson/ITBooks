using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace TCPTransportSessionsHost
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void DoTest(Type T)
		{
			using(ServiceHost SH=new ServiceHost(T))
			{
				SH.Open();

				Console.WriteLine("Press any key to STOP !");
				Console.ReadLine();
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="SERVER";

			try
			{
				// !!! IBA JEDEN TEST MOZE BYT NARAZ SPUSTENY.

				DoTest(typeof(CDefaultConfiguration));

				// Service NEDJE SPUSTIT, pretoze to WCF zamedzuje v danej konfiguracii.
				//DoTest(typeof(CTSNotAllowedButBindingAllowsIt));

				//DoTest(typeof(CTSRequiredAndBindingIsDefault));

				//DoTest(typeof(CTSRequiredAndBindingEnablesTS));

				// Service NEDJE SPUSTIT, pretoze to WCF zamedzuje v danej konfiguracii.
				//DoTest(typeof(CTSNotAllowedAndDoNotAllowIt));
			}
			catch(Exception E)
			{
				Console.WriteLine("EXCEPTION: {0} !",E.Message);
			}

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------