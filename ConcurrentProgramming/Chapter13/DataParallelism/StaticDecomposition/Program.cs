using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
//------------------------------------------------------------------------------
namespace StaticDecomposition
{
//------------------------------------------------------------------------------
	class Program
	{
//------------------------------------------------------------------------------
		static void ParallelForContinous(int Lo, int Hi, Action<int,int> Body, int P)
		{
			int				Chunk=(Hi-Lo)/P;

			for (int i=0;i<P;i++)
			{
				ThreadPool.QueueUserWorkItem(delegate(object Obj)
				{
					int		PID=(int) Obj;
					int		Start=Lo+PID*Chunk;
					int		End=(PID==(P-1)) ? Hi:(Start+Chunk);

					for (int j=Start;j<End;j++)
					{
						Body(j,PID);
					}

					Console.WriteLine(string.Format("Signal that THREAD: {0} finished !",PID));
				}, i);
			}

			Console.WriteLine("Task scheduled !");
			Console.ReadLine();
		}
//------------------------------------------------------------------------------
		static void ParallelForStriped(int Lo, int Hi, Action<int,int> Body, int P)
		{
			const int		Chunk=1;

			for (int i=0;i<P;i++)
			{
				ThreadPool.QueueUserWorkItem(delegate(object PID)
				{
					int		Start=Lo+(int)PID*Chunk;

					//for (int j=Start;j<Hi;j+=Chunk*(P-1))
					for (int j=Start;j<Hi;j+=Chunk*(P-0))
					{
						for (int k=0;k<Chunk && (j+k)<Hi;k++)
						{
							Body((j+k),(int) PID);
						}
					}

					Console.WriteLine(string.Format("Signal that THREAD: {0} finished !",PID));
				}, i);
			}

			Console.WriteLine("Task scheduled !");
			Console.ReadLine();
		}
//------------------------------------------------------------------------------
		private static void Task1(int TaskID, int ThreadID)
		{
			Thread.Sleep(1000);
			Console.WriteLine(string.Format("TASK: {0} finished by THREAD: {1} !",TaskID,ThreadID));
		}
//------------------------------------------------------------------------------
		private static void Task2(int TaskID, int ThreadID)
		{
			Thread.Sleep(300*TaskID);
			Console.WriteLine(string.Format("TASK: {0} finished by THREAD: {1} !",TaskID,ThreadID));
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		private static void TestContinousIterations()
		{
			ParallelForContinous(1,16,Task1,3);
		}
//------------------------------------------------------------------------------
		private static void TestContinousStriped()
		{
			ParallelForStriped(1,17,Task2,3);
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			//TestContinousIterations();
			TestContinousStriped();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------