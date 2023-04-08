using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
//------------------------------------------------------------------------------
namespace Future
{
//------------------------------------------------------------------------------
	class Program
	{
//------------------------------------------------------------------------------
		private static int CalculateValue()
		{
			Thread.Sleep(3000);

			return(50);
		}
//------------------------------------------------------------------------------
		private static void Test()
		{
			CFuture<int>			MyFuture=new CFuture<int>(CalculateValue);
			
			Console.WriteLine("Getting FUTURE value !");

			int					Value=MyFuture.Value;

			Console.WriteLine(string.Format("FUTURE VALUE: [{0}] !",Value));
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