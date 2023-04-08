using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
//------------------------------------------------------------------------------
namespace AlogrithmsTest
{
//------------------------------------------------------------------------------
	class Program
	{
//------------------------------------------------------------------------------
		private static void PrintIteration(int Iteration)
		{
			Thread.Sleep(1000);

			Console.WriteLine(string.Format("Iteration nubmer: [{0}] !",Iteration));
		}
//------------------------------------------------------------------------------
		private static void PrintIterationException(int Iteration)
		{
			Thread.Sleep(1000);

			Console.WriteLine(string.Format("Iteration nubmer: [{0}] !",Iteration));

			if (Iteration==5)
				throw(new Exception("You have reached 5 !!!"));
		}
//------------------------------------------------------------------------------
		private static void PrintIterationStop(int Iteration, ParallelState PS)
		{
			Console.WriteLine(string.Format("START - Iteration nubmer: [{0}] !",Iteration));

			Thread.Sleep(Iteration*500);

			Console.WriteLine(string.Format("STOP - Iteration nubmer: [{0}] !",Iteration));

			if (Iteration==5)
				PS.Stop();
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		private static void Test1()
		{
			Parallel.For(0,10,PrintIteration);
		}
//------------------------------------------------------------------------------
		private static void Test2()
		{
			int[]			Array=new int[]{1,3,5,7,9,11,13};

			Parallel.ForEach(Array,PrintIteration);
		}
//------------------------------------------------------------------------------
		private static void Test3()
		{
			try
			{
				Parallel.For(0,10,PrintIterationException);
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}]",E));
			}
		}
//------------------------------------------------------------------------------
		private static void Test4()
		{
			try
			{
				Parallel.For(0,15,PrintIterationStop);
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}]",E));
			}
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			//Test1();
			//Test2();
			//Test3();
			Test4();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------