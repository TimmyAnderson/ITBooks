using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
//------------------------------------------------------------------------------
namespace ManagedTPWorkItems
{
//------------------------------------------------------------------------------
	class Program
	{
//------------------------------------------------------------------------------
		static void ThreadMethod(object State)
		{
			string				Param=(string) State;

			Console.WriteLine(string.Format("{0} BEGIN THREAD: [{1}] !",DateTime.Now.ToString("HH:mm:ss:fff"),Param));

			Thread.Sleep(10*1000);

			Console.WriteLine(string.Format("{0} END THREAD: [{1}] !",DateTime.Now.ToString("HH:mm:ss:fff"),Param));
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		static void Test()
		{
			// !!!!! Program demonstruje i fakt, ze NOVE THREADS sa vytvaraju s MINIMALNYM INTERVALOM 500ms, AK NEZVYSIM default Min Trhread Count z 0 na vyssie cislo.
			//ThreadPool.SetMinThreads(20,20);

			for (int i=0;i<20;i++)
			{
				string			Text=string.Format("XXX {0}",i+1);

				ThreadPool.QueueUserWorkItem(ThreadMethod,Text);
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