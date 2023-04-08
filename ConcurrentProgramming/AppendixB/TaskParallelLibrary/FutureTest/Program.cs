using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
//------------------------------------------------------------------------------
namespace FutureTest
{
//------------------------------------------------------------------------------
	class Program
	{
//------------------------------------------------------------------------------
		private static void ThreadSetFuture(object Param)
		{
			Future<string>		F=(Future<string>) Param;
			string				Value="Timmy";

			Thread.Sleep(2000);

			Console.WriteLine(string.Format("Thread is setting value to [{0}] !",Value));

			F.Value=Value;
		}
//------------------------------------------------------------------------------
		private static string SimpleFuture()
		{
			int				FutureID=Future<string>.Current.Id;
			string			Param="Timmy";

			Console.WriteLine(string.Format("Future [{0}] with data [{1}] STARTED !",FutureID,Param));

			Thread.Sleep(1000);

			Console.WriteLine(string.Format("Future [{0}] with data [{1}] FINISHED !",FutureID,Param));

			return(Param.ToString().ToUpper());
		}
//------------------------------------------------------------------------------
		// Je to zretazeny Fututre<T>, ktory ma ako parameter Future<T>.
		private static string ContinuationFuture(Future<string> Param)
		{
			int						FutureID=Future<string>.Current.Id;

			Console.WriteLine(string.Format("Future [{0}] with data [{1}] STARTED !",FutureID,Param.Value));

			Thread.Sleep(1000);

			Console.WriteLine(string.Format("Future [{0}] with data [{1}] FINISHED !",FutureID,Param.Value));

			return((Param.Value.ToString() + " Anderson").ToUpper());
		}
//------------------------------------------------------------------------------
		private static string ExceptionFuture()
		{
			int				FutureID=Future<string>.Current.Id;
			string			Param="Timmy";

			Console.WriteLine(string.Format("Future [{0}] with data [{1}] STARTED !",FutureID,Param));

			Thread.Sleep(1000);

			Console.WriteLine(string.Format("Future [{0}] with data [{1}] FINISHED !",FutureID,Param));

			throw(new ArgumentException("Future EXCEPTION !!!"));
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		private static void Test1()
		{
			Future<string>		Ret=Future<string>.Create(SimpleFuture);

			Ret.Wait();

			string				Value=Ret.Value;

			Console.WriteLine(string.Format("Future returned: [{0}] !",Value));
		}
//------------------------------------------------------------------------------
		private static void Test2()
		{
			Future<string>		Ret=Future<string>.Create(ExceptionFuture);

			try
			{
				Ret.Wait();

				string			Value=Ret.Value;

				Console.WriteLine(string.Format("Future returned: [{0}] !",Value));
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("TASK EXCEPTION: [{0}]",E));
			}
		}
//------------------------------------------------------------------------------
		private static void Test3()
		{
			Future<string>		Future=Future<string>.Create(SimpleFuture);

			// !!! Zretazim Futures.
			Future<string>		Ret=Future.ContinueWith<string>(ContinuationFuture);

			try
			{
				Ret.Wait();

				string			Value=Ret.Value;

				Console.WriteLine(string.Format("Future returned: [{0}] !",Value));
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("TASK EXCEPTION: [{0}]",E));
			}
		}
//------------------------------------------------------------------------------
		private static void Test4()
		{
			// Vytvorim Future<T> BEZ PARAMETROV. Pre tuto Future musim EXPLICITNE NASTAVIT hodnotu Value.
			Future<string>		Future=Future<string>.Create();
			Thread				T=new Thread(ThreadSetFuture);

			T.Start(Future);

			try
			{
				Console.WriteLine("Waiting for future Value !");

				Future.Wait();

				string			Value=Future.Value;

				Console.WriteLine(string.Format("Future returned: [{0}] !",Value));
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("TASK EXCEPTION: [{0}]",E));
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