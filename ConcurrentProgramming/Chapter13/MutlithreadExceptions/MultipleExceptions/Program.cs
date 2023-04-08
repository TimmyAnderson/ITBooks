using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
//------------------------------------------------------------------------------
namespace MultipleExceptions
{
//------------------------------------------------------------------------------
	class Program
	{
//------------------------------------------------------------------------------
		private static AutoResetEvent[] CoBegin(List<Exception> Exceptions, params Action<object>[] Actions)
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
					catch(Exception E)
					{
					   lock(Exceptions)
					   {
						   // Agreguje Exceptions.
						   Exceptions.Add(E);
					   }
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
			List<Exception>		Exceptions=new List<Exception>();
			AutoResetEvent[]	Latches=CoBegin(Exceptions,Actions);

			WaitHandle.WaitAll(Latches);

			// Hodim agregovanu Exception.
			if (Exceptions.Count>0)
				throw(new CAggregateException(Exceptions));
		}
//------------------------------------------------------------------------------
		private static void TaskException1(object Param)
		{
			Thread.Sleep(3000);

			throw(new InvalidOperationException(string.Format("Some STUPID EXCEPTION thrown from THREAD [{0}] !",Param)));
		}
//------------------------------------------------------------------------------
		private static void TaskException2(object Param)
		{
			Thread.Sleep(3000);

			throw(new ArgumentException(string.Format("Some ABSOLUTELY NORMAL EXCEPTION thrown from THREAD [{0}] !",Param)));
		}
//------------------------------------------------------------------------------
		private static void Test()
		{
			try
			{
				DoAll(new Action<object>[]{TaskException1,TaskException2});
			}
			catch(CAggregateException E)
			{
				Console.WriteLine(string.Format("!!! AGREGATE EXCEPTION: [{0}] !",E.Message));

				for (int i=0;i<E.InnerExceptions.Length;i++)
					Console.WriteLine(string.Format("\tParallel EXCEPTION {0}: [{1}] !",i+1,E.InnerExceptions[i].Message));
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