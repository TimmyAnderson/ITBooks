using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
//------------------------------------------------------------------------------
namespace MarshalingExceptions
{
//------------------------------------------------------------------------------
	class Program
	{
//------------------------------------------------------------------------------
		private static int CalculateValue()
		{
			Thread.Sleep(3000);

			throw(new InvalidOperationException("Some STUPID EXCEPTION from SECONDARY THREAD !"));
		}
//------------------------------------------------------------------------------
		private static void Test()
		{
			CFuture<int>		MyFuture=new CFuture<int>(CalculateValue);
			
			Console.WriteLine("Getting FUTURE value !");

			try
			{
				int					Value=MyFuture.Value;

				Console.WriteLine(string.Format("FUTURE VALUE: [{0}] !",Value));
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("!!! FUTURE EXCEPTION: [{0}] !",E));
			}
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