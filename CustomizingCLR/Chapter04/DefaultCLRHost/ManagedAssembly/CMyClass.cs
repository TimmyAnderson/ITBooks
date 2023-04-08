using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Runtime;
//-------------------------------------------------------------------------------------------------------
namespace ManagedAssembly
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CMyClass
	{
//-------------------------------------------------------------------------------------------------------
		// Tato metoda je zavedena z NATIVE PROCESU pomocou CLR HOSTING.
		public static int MySimpleMethod(string Argument)
		{
			Console.WriteLine(string.Format("Hello [{0}] !",Argument));

			return(100);
		}
//-------------------------------------------------------------------------------------------------------
		// Tato metoda je zavedena z NATIVE PROCESU pomocou CLR HOSTING.
		public static int PrintGCType(string Argument)
		{
			Console.WriteLine(string.Format("GC - IsServer [{0}], GCSettings.LatencyMode [{1}] !",GCSettings.IsServerGC,GCSettings.LatencyMode));

			return(0);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------