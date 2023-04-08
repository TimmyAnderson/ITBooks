using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime;
//-------------------------------------------------------------------------------------------------------
namespace DefaultCLRHostChangedDefaults
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.WriteLine(string.Format("IsServerGC: [{0}], LatencyMode: [{1}] !",GCSettings.IsServerGC,GCSettings.LatencyMode));
			Console.WriteLine(string.Format("Version: [{0}] !",Environment.Version));
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------