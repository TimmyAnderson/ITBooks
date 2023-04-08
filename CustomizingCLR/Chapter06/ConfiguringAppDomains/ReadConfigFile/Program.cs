using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Configuration;
//------------------------------------------------------------------------------------------------------
namespace ReadConfigFile
{
//------------------------------------------------------------------------------------------------------
	class Program
	{
//------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			string												ValueFromConfigFile=ConfigurationManager.AppSettings["Name"];

			if (ValueFromConfigFile!=null)
			{
				Console.WriteLine(string.Format("VALUE from CONFIG FILE: [{0}] !",ValueFromConfigFile));
			}
			else
			{
				Console.WriteLine(string.Format("VALUE in CONFIG FILE NOT FOUND !"));
			}
		}
//------------------------------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------------------------------