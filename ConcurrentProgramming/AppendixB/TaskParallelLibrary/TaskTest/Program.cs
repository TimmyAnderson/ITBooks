using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
//------------------------------------------------------------------------------
namespace TaskTest
{
//------------------------------------------------------------------------------
	class Program
	{
//------------------------------------------------------------------------------
		private static void SimpleTask(object Param)
		{
			int				TaskID=Task.Current.Id;

			Console.WriteLine(string.Format("Task [{0}] with data [{1}] STARTED !",TaskID,Param));

			Thread.Sleep(1000);

			Console.WriteLine(string.Format("Task [{0}] with data [{1}] FINISHED !",TaskID,Param));
		}
//------------------------------------------------------------------------------
		private static void ThrowException1(object Param)
		{
			int				TaskID=Task.Current.Id;

			Console.WriteLine(string.Format("Task [{0}] with data [{1}] !",TaskID,Param));

			Thread.Sleep(1000);

			throw(new ArgumentException("INVALID ARGUMENT !!!"));
		}
//------------------------------------------------------------------------------
		private static void ThrowException2(object Param)
		{
			int				TaskID=Task.Current.Id;

			Console.WriteLine(string.Format("Task [{0}] with data [{1}] !",TaskID,Param));

			Thread.Sleep(1000);

			throw(new InvalidCastException("INVALID CAST !!!"));
		}
//------------------------------------------------------------------------------
		private static void ParentTask1(object Param)
		{
			int				TaskID=Task.Current.Id;

			Console.WriteLine(string.Format("Task [{0}] with data [{1}] STARTED !",TaskID,Param));

			Task.Create(ChildTask1,Param);

			Thread.Sleep(1000);

			Console.WriteLine(string.Format("Task [{0}] with data [{1}] FINISHED !",TaskID,Param));
		}
//------------------------------------------------------------------------------
		private static void ParentTask2(object Param)
		{
			int				TaskID=Task.Current.Id;

			Console.WriteLine(string.Format("Task [{0}] with data [{1}] STARTED !",TaskID,Param));

			Task.Create(ChildTask2,Param);

			Thread.Sleep(1000);

			Console.WriteLine(string.Format("Task [{0}] with data [{1}] FINISHED !",TaskID,Param));
		}
//------------------------------------------------------------------------------
		private static void ParentTask3(object Param)
		{
			int				TaskID=Task.Current.Id;

			Console.WriteLine(string.Format("Task [{0}] with data [{1}] STARTED !",TaskID,Param));

			Task.Create(ChildTask3,Param);

			Thread.Sleep(3000);

			Console.WriteLine(string.Format("Task [{0}] with data [{1}] FINISHED !",TaskID,Param));
		}
//------------------------------------------------------------------------------
		private static void ParentTask4(object Param)
		{
			int				TaskID=Task.Current.Id;

			Console.WriteLine(string.Format("Task [{0}] with data [{1}] STARTED !",TaskID,Param));

			// Vytvorim DETACHED CHILD.
			Task.Create(ChildTask4,Param,new TaskManager(),TaskCreationOptions.Detached);

			Thread.Sleep(3000);

			Console.WriteLine(string.Format("Task [{0}] with data [{1}] FINISHED !",TaskID,Param));
		}
//------------------------------------------------------------------------------
		private static void ChildTask1(object Param)
		{
			int				TaskID=Task.Current.Id;
			int				PTaskID=Task.Current.Parent.Id;

			Console.WriteLine(string.Format("Task [{0}] - Parent [{1}] with data [{2}] STARTED !",TaskID,PTaskID,Param));

			Thread.Sleep(3000);

			Console.WriteLine(string.Format("Task [{0}] - Parent [{1}] with data [{2}] FINISHED !",TaskID,PTaskID,Param));
		}
//------------------------------------------------------------------------------
		private static void ChildTask2(object Param)
		{
			int				TaskID=Task.Current.Id;
			int				PTaskID=Task.Current.Parent.Id;

			Console.WriteLine(string.Format("Task [{0}] - Parent [{1}] with data [{2}] !",TaskID,PTaskID,Param));

			Thread.Sleep(1000);

			throw(new ArgumentException("INVALID ARGUMENT !!!"));
		}
//------------------------------------------------------------------------------
		private static void ChildTask3(object Param)
		{
			int				TaskID=Task.Current.Id;
			int				PTaskID=Task.Current.Parent.Id;

			Console.WriteLine(string.Format("Task [{0}] - Parent [{1}] with data [{2}] STARTED !",TaskID,PTaskID,Param));

			// Cakam kratko, aby Parent skoncil SKOR.
			Thread.Sleep(1000);

			Console.WriteLine(string.Format("Task [{0}] - Parent [{1}] with data [{2}] FINISHED !",TaskID,PTaskID,Param));
		}
//------------------------------------------------------------------------------
		private static void ChildTask4(object Param)
		{
			int				TaskID=Task.Current.Id;
			string			PTaskID=(Task.Current.Parent!=null) ? Task.Current.Parent.Id.ToString() : "DETACHED - NO PARENT";

			Console.WriteLine(string.Format("Task [{0}] - Parent [{1}] with data [{2}] STARTED !",TaskID,PTaskID,Param));

			// Cakam kratko, aby Parent skoncil SKOR.
			Thread.Sleep(1000);

			Console.WriteLine(string.Format("Task [{0}] - Parent [{1}] with data [{2}] FINISHED !",TaskID,PTaskID,Param));
		}
//------------------------------------------------------------------------------
		private static void CancelTask(object Param)
		{
			int				TaskID=Task.Current.Id;

			Console.WriteLine(string.Format("Task [{0}] with data [{1}] STARTED !",TaskID,Param));

			Thread.Sleep(5000);

			Console.WriteLine(string.Format("Task [{0}] with data [{1}] FINISHED - CANCELLED: [{2}] !",TaskID,Param,Task.Current.IsCanceled.ToString().ToUpper()));
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		private static void Test1()
		{
			Task			Task1=Task.Create(SimpleTask,1);
			Task			Task2=Task.Create(SimpleTask,2);
			Task			Task3=Task.Create(SimpleTask,3);
			Task			Task4=Task.Create(SimpleTask,4);
			Task[]			Tasks=new Task[]{Task1,Task2,Task3,Task4};

			Console.WriteLine("All tasks are started now !");

			Task.WaitAll(Tasks);

			Console.WriteLine("All tasks are FINISHED !");
		}
//------------------------------------------------------------------------------
		private static void Test2()
		{
			Task			Task1=Task.Create(ThrowException1,1);
			Task			Task2=Task.Create(ThrowException2,2);

			Console.WriteLine("All tasks are started now !");

			try
			{
				Task1.Wait();
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("TASK 1 EXCEPTION: [{0}]",E));
			}

			try
			{
				Task2.Wait();
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("TASK 2 EXCEPTION: [{0}]",E));
			}

			Console.WriteLine("All tasks are FINISHED !");
		}
//------------------------------------------------------------------------------
		private static void Test3()
		{
			Task			Task=Task.Create(ThrowException1,"AAA");

			Console.WriteLine("All tasks are started now !");

			try
			{
				Task.Wait();
			}
			catch(AggregateException E)
			{
				Console.WriteLine(string.Format("TASK EXCEPTION: [{0}]",E));

				// Spracujem vsetky Exceptions.
				E.Handle(P => true);
			}

			Console.WriteLine("All tasks are FINISHED !");
		}
//------------------------------------------------------------------------------
		private static void Test4()
		{
			Task			Task=Task.Create(ThrowException1,"AAA");

			Console.WriteLine("All tasks are started now !");

			try
			{
				Task.Wait();
			}
			catch(AggregateException E)
			{
				Console.WriteLine(string.Format("TASK EXCEPTION: [{0}]",E.Message));

				try
				{
					// NESPRACUJUEM ZIADNU EXCEPTION.
					// !!! Handle() OKAMZITE VRATI NEPSRACOVANE EXCEPTION V NOVEJ EXCEPTION.
					E.Handle(P => false);
				}
				catch(AggregateException Ex)
				{
					Console.WriteLine(string.Format("SECOND TASK EXCEPTION: [{0}]",Ex.Message));
				}
			}

			Console.WriteLine("All tasks are FINISHED !");
		}
//------------------------------------------------------------------------------
		private static void Test5()
		{
			// UPLNE IGNORUJEM EXCEPTION.
			Task.Create(ThrowException1,"AAA");
		}
//------------------------------------------------------------------------------
		private static void Test6()
		{
			Task			Task=Task.Create(ParentTask1,1);

			Console.WriteLine("All tasks are started now !");

			try
			{
				Task.Wait();
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("TASK EXCEPTION: [{0}]",E));
			}

			Console.WriteLine("All tasks are FINISHED !");
		}
//------------------------------------------------------------------------------
		private static void Test7()
		{
			Task			Task=Task.Create(ParentTask2,1);

			Console.WriteLine("All tasks are started now !");

			try
			{
				Task.Wait();
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("TASK EXCEPTION: [{0}]",E));
			}

			Console.WriteLine("All tasks are FINISHED !");
		}
//------------------------------------------------------------------------------
		private static void Test8()
		{
			Task			Task=Task.Create(ParentTask3,1);

			Console.WriteLine("All tasks are started now !");

			try
			{
				// Child skonci skor ako Parent.
				Task.Wait();
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("TASK EXCEPTION: [{0}]",E));
			}

			Console.WriteLine("All tasks are FINISHED !");
		}
//------------------------------------------------------------------------------
		private static void Test9()
		{
			Task			Task=Task.Create(ParentTask4,1);

			Console.WriteLine("All tasks are started now !");

			try
			{
				// Child skonci skor ako Parent.
				Task.Wait();
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("TASK EXCEPTION: [{0}]",E));
			}

			Console.WriteLine("All tasks are FINISHED !");
		}
//------------------------------------------------------------------------------
		private static void Test10()
		{
			Task			Task=Task.Create(CancelTask,"AAA");

			Console.WriteLine("All tasks are started now !");

			try
			{
				Thread.Sleep(1000);

				// Dam Cancel.
				Task.CancelAndWait();
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("TASK EXCEPTION: [{0}]",E));
			}

			Console.WriteLine(string.Format("TASK Canceled: [{0}]",Task.IsCanceled.ToString().ToUpper()));

			Console.WriteLine("All tasks are FINISHED !");
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			//Test1();
			//Test2();
			//Test3();
			//Test4();
			//Test5();
			//Test6();
			//Test7();
			//Test8();
			//Test9();
			Test10();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------