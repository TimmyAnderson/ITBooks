using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
//------------------------------------------------------------------------------
namespace CountdownEventTest
{
//------------------------------------------------------------------------------
	class Program
	{
//------------------------------------------------------------------------------
		private static string Create()
		{
			Console.WriteLine("Instance CREATED !");

			return("Timmy");
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		private static void Test()
		{
			LazyInit<string>			LI=new LazyInit<string>(Create);

			Console.WriteLine("BEFORE 1. access !");

			Console.WriteLine(string.Format("1. access [{0}] !",LI.Value));
			Console.WriteLine(string.Format("2. access [{0}] !",LI.Value));
			Console.WriteLine(string.Format("3. access [{0}] !",LI.Value));
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Test();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------