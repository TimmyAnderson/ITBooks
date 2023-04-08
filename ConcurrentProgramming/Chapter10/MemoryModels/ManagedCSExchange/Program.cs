using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
//------------------------------------------------------------------------------
namespace ManagedCSExchange
{
//------------------------------------------------------------------------------
	class Program
	{
//------------------------------------------------------------------------------
		private static SExchange			MLock=new SExchange();
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		private static void ThreadMethod(object Obj)
		{
			string							Param=(string) Obj;

			Console.WriteLine(string.Format("{0} STARTED !",Param));

			MLock.EnterCS();

			Console.WriteLine(string.Format("{0} ENTERED CS !",Param));

			Thread.Sleep(1000);

			Console.WriteLine(string.Format("{0} LEFT CS !",Param));

			MLock.ExitCS();

			Console.WriteLine(string.Format("{0} FINISHED !",Param));
		}
//------------------------------------------------------------------------------
		private static void TestSExchange()
		{
			Thread							T1=new Thread(new ParameterizedThreadStart(ThreadMethod));
			Thread							T2=new Thread(new ParameterizedThreadStart(ThreadMethod));

			T1.Start("111");
			T2.Start("222");

			T1.Join();
			T2.Join();
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			TestSExchange();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------