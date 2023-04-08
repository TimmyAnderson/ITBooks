using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;
using System.Diagnostics;
//-------------------------------------------------------------------------------------------------------
namespace MyCustomAssembly
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CCustomAssembly
	{
//-------------------------------------------------------------------------------------------------------
		public static void PrintText()
		{
			Console.WriteLine("!!!!!!!!!! CCustomAssembly.PrintText() - APP DOMAIN [{0} - {1}] !",AppDomain.CurrentDomain.Id,AppDomain.CurrentDomain.FriendlyName);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------