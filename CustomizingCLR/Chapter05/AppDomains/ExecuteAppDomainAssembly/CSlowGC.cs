using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
//-------------------------------------------------------------------------------------------------------
namespace ExecuteAppDomainAssembly
{
//-------------------------------------------------------------------------------------------------------
	// !!! Umyselne spomali FINALIZER.
	public sealed class CSlowGC
	{
//-------------------------------------------------------------------------------------------------------
		~CSlowGC()
		{
			Console.WriteLine(string.Format("START FINALIZER WAITING - EXECUTED in APP DOMAIN [{0}] !",AppDomain.CurrentDomain.FriendlyName));

			Thread.Sleep(5000);

			Console.WriteLine(string.Format("STOP FINALIZER WAITING - EXECUTED in APP DOMAIN [{0}] !",AppDomain.CurrentDomain.FriendlyName));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------