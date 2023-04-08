using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
//------------------------------------------------------------------------------
namespace ForkJoinParallelism
{
//------------------------------------------------------------------------------
	class Program
	{
//------------------------------------------------------------------------------
		private static Random					MRND=new Random();
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		private static AutoResetEvent[] CoBegin(params Action<object>[] Actions)
		{
			AutoResetEvent[]	Latches=new AutoResetEvent[Actions.Length];

			for (int i=0;i<Actions.Length;i++)
			{
				Latches[i]=new AutoResetEvent(false);

				ThreadPool.QueueUserWorkItem(delegate(object Obj)
				{
					int			Index=(int) Obj;

					try
					{
						Actions[Index](Index+1);
					}
					finally
					{
						Latches[Index].Set();
					}
				}, i);
			}

			return(Latches);
		}
//------------------------------------------------------------------------------
		private static void DoAll(params Action<object>[] Actions)
		{
			Action<object>[]	ParallelActions=new Action<object>[Actions.Length-1];

			Array.Copy(Actions,ParallelActions,Actions.Length-1);

			AutoResetEvent[]	Latches=CoBegin(ParallelActions);

			try
			{
				// !!! Posledny task vykonam priamo v CALLER THREADE.
				Actions[Actions.Length-1](Actions.Length);
			}
			finally
			{
				WaitHandle.WaitAll(Latches);
			}

			Console.WriteLine("TASKS FINISHED !");
			Console.ReadLine();
		}
//------------------------------------------------------------------------------
		private static void Task(object Param)
		{
			int					TaskID=(int) Param;

			Thread.Sleep(MRND.Next(1000,3000));
			Console.WriteLine(string.Format("TASK: {0} finished !",TaskID));
		}
//------------------------------------------------------------------------------
		private static void Test()
		{
			// Vlozim 10 tasks.
			DoAll(Task,Task,Task,Task,Task,Task,Task,Task,Task,Task);
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