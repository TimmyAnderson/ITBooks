using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using BagAssembly1;
using BagAssembly2;
//------------------------------------------------------------------------------------------------------
namespace BagExecutable
{
//------------------------------------------------------------------------------------------------------
	public static class Program
	{
//------------------------------------------------------------------------------------------------------
		private static void PrintText()
		{
			Console.WriteLine(string.Format("---------->>> Program.PrintText() CALLED in APP DOMAIN [{0}] !",AppDomain.CurrentDomain.FriendlyName));
		}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			try
			{
				PrintText();
				CClassBagAssembly1.PrintText();
				CClassBagAssembly2.PrintText();
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION [{0}] !",E.Message));
			}

			//Console.WriteLine("Press any KEY to EXIT !");
			//Console.ReadLine();
		}
//------------------------------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------------------------------