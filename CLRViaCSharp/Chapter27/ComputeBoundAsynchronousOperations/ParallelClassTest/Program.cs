using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
//-------------------------------------------------------------------------------------------------------
namespace ParallelClassTest
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static string[]									MStrings=new string[]{"Timothy Anderson","Jennifer Thompson","Atreyu","Bubu","Tony Randal","Bart King","David Kong"};
		private static int										MInitCounter=0;
		private static int										MBodyCounter=0;
		private static int										MFinallyCounter=0;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private static int Init()
		{
			Interlocked.Increment(ref MInitCounter);

			return(0);
		}
//-------------------------------------------------------------------------------------------------------
		private static int Body(int Value, ParallelLoopState PLS, int ValueFromLocalInit)
		{
			Interlocked.Increment(ref MBodyCounter);

			return(0);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Finally(int ValueFromBodyOrLocalInit)
		{
			Interlocked.Increment(ref MFinallyCounter);
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private static void InvokeAction()
		{
			Console.WriteLine(string.Format("TASK: [{0}] - ACTION STARTED !",Task.CurrentId));

			Thread.Sleep(5*1000);

			Console.WriteLine(string.Format("TASK: [{0}] - ACTION FINISHED !",Task.CurrentId));
		}
//-------------------------------------------------------------------------------------------------------
		private static int SlowCalculationStringSize_For(int Index, ParallelLoopState PLS, int ValueFromLocalInit)
		{
			Console.WriteLine(string.Format("TASK: [{0}] - BODY STARTED, ValueFromLocalInit: [{1}], Index: [{2}] !",Task.CurrentId,Index,ValueFromLocalInit));

			int													Length=0;
			string												Text=MStrings[Index];

			for (int Iteration=0;Iteration<Text.Length;Iteration++)
			{
				Thread.Sleep(500);
				Length++;

				// Ak bol spraveny CANCELLATION, doslo k UNHANDLED EXCEPTION v INOM ITEM, bol volany Break(), alebo Stop(), tak UKONCIM VYKONAVANIE ITEM.
				// !!!!! Pri Break() je TRUE IBA PRE ITEMS, ktore maju INDEX VYSSI ako ITEM, ktory VOLAL Break().
				// !!!!! Pri Stop() je TRUE pre VSETKY ITEMS.
				if (PLS.ShouldExitCurrentIteration==true)
				{
					Console.WriteLine(string.Format("TASK: [{0}] - BODY DETECTED PROPERTY ShouldExitCurrentIteration SET to TRUE !",Task.CurrentId));
					throw(new OperationCanceledException("Operation WAS CANCELED, BROKEN, or STOPPED !"));
				}
			}

			Console.WriteLine(string.Format("TASK: [{0}] - BODY FINISHED !",Task.CurrentId));

			return(Length);
		}
//-------------------------------------------------------------------------------------------------------
		// Inicializujem pociatocnu hodnotu, ktora sa PRENESIE do BODY METODY.
		private static int LocalInit()
		{
			Console.WriteLine(string.Format("TASK: [{0}] - LOCAL INIT !",Task.CurrentId));

			// Prenesiem pociatocnu hodnotu do BODY METODY.
			return(-100);
		}
//-------------------------------------------------------------------------------------------------------
		private static int SlowCalculationStringSize(string Text, ParallelLoopState PLS, long Index, int ValueFromLocalInit)
		{
			Console.WriteLine(string.Format("TASK: [{0}] - BODY STARTED, ValueFromLocalInit: [{1}], Index: [{2}] !",Task.CurrentId,Index,ValueFromLocalInit));

			int													Length=0;

			for (int Iteration=0;Iteration<Text.Length;Iteration++)
			{
				Thread.Sleep(500);
				Length++;

				// Ak bol spraveny CANCELLATION, doslo k UNHANDLED EXCEPTION v INOM ITEM, bol volany Break(), alebo Stop(), tak UKONCIM VYKONAVANIE ITEM.
				// !!!!! Pri Break() je TRUE IBA PRE ITEMS, ktore maju INDEX VYSSI ako ITEM, ktory VOLAL Break().
				// !!!!! Pri Stop() je TRUE pre VSETKY ITEMS.
				if (PLS.ShouldExitCurrentIteration==true)
				{
					Console.WriteLine(string.Format("TASK: [{0}] - BODY DETECTED PROPERTY ShouldExitCurrentIteration SET to TRUE !",Task.CurrentId));
					throw(new OperationCanceledException("Operation WAS CANCELED, BROKEN, or STOPPED !"));
				}
			}

			Console.WriteLine(string.Format("TASK: [{0}] - BODY FINISHED !",Task.CurrentId));

			return(Length);
		}
//-------------------------------------------------------------------------------------------------------
		// Vykona Break().
		private static int SlowCalculationStringSize_Break(string Text, ParallelLoopState PLS, long Index, int ValueFromLocalInit)
		{
			Console.WriteLine(string.Format("TASK: [{0}] - BODY STARTED, ValueFromLocalInit: [{1}], Index: [{2}] !",Task.CurrentId,Index,ValueFromLocalInit));

			int													Length=0;

			for (int Iteration=0;Iteration<Text.Length;Iteration++)
			{
				Thread.Sleep(500);
				Length++;

				// Ak bol spraveny CANCELLATION, doslo k UNHANDLED EXCEPTION v INOM ITEM, bol volany Break(), alebo Stop(), tak UKONCIM VYKONAVANIE ITEM.
				// !!!!! Pri Break() je TRUE IBA PRE ITEMS, ktore maju INDEX VYSSI ako ITEM, ktory VOLAL Break().
				// !!!!! Pri Stop() je TRUE pre VSETKY ITEMS.
				if (PLS.ShouldExitCurrentIteration==true)
				{
					Console.WriteLine(string.Format("TASK: [{0}] - BODY DETECTED PROPERTY ShouldExitCurrentIteration SET to TRUE !",Task.CurrentId));
					return(-1000);
				}
			}

			Console.WriteLine(string.Format("TASK: [{0}] - BODY FINISHED !",Task.CurrentId));

			if (Index==2)
			{
				Console.WriteLine(string.Format("!!!!! TASK: [{0}] - BREAKING !",Task.CurrentId));
				PLS.Break();
			}

			return(Length);
		}
//-------------------------------------------------------------------------------------------------------
		// Vykona Stop().
		private static int SlowCalculationStringSize_Stop(string Text, ParallelLoopState PLS, long Index, int ValueFromLocalInit)
		{
			Console.WriteLine(string.Format("TASK: [{0}] - BODY STARTED, ValueFromLocalInit: [{1}], Index: [{2}] !",Task.CurrentId,Index,ValueFromLocalInit));

			int													Length=0;

			for (int Iteration=0;Iteration<Text.Length;Iteration++)
			{
				Thread.Sleep(500);
				Length++;

				// Ak bol spraveny CANCELLATION, doslo k UNHANDLED EXCEPTION v INOM ITEM, bol volany Break(), alebo Stop(), tak UKONCIM VYKONAVANIE ITEM.
				// !!!!! Pri Break() je TRUE IBA PRE ITEMS, ktore maju INDEX VYSSI ako ITEM, ktory VOLAL Break().
				// !!!!! Pri Stop() je TRUE pre VSETKY ITEMS.
				if (PLS.ShouldExitCurrentIteration==true)
				{
					Console.WriteLine(string.Format("TASK: [{0}] - BODY DETECTED PROPERTY ShouldExitCurrentIteration SET to TRUE !",Task.CurrentId));
					return(-1000);
				}
			}

			Console.WriteLine(string.Format("TASK: [{0}] - BODY FINISHED !",Task.CurrentId));

			if (Index==2)
			{
				Console.WriteLine(string.Format("!!!!! TASK: [{0}] - STOPPING !",Task.CurrentId));
				PLS.Stop();
			}

			return(Length);
		}
//-------------------------------------------------------------------------------------------------------
		// Hodnota ValueFromBodyOrLocalInit - je vysledkom BODY ak doslo ku korektnemu spracovanie ITEM a z LOCAL INIT ak doslo k UNHANDLED EXCEPTION.
		private static void LocalFinally(int ValueFromBodyOrLocalInit)
		{
			Console.WriteLine(string.Format("TASK: [{0}] - LOCAL FINISH, ValueFromBodyOrLocalInit: [{1}] !",Task.CurrentId,ValueFromBodyOrLocalInit));
		}
//-------------------------------------------------------------------------------------------------------
		// Hodi UNHANDLED EXCEPTION.
		private static int SlowCalculationStringSize_UnhandledException(string Text, ParallelLoopState PLS, long Index, int ValueFromLocalInit)
		{
			Console.WriteLine(string.Format("TASK: [{0}] - BODY STARTED, ValueFromLocalInit: [{1}], Index: [{2}] !",Task.CurrentId,Index,ValueFromLocalInit));

			int													Length=0;

			for (int Iteration=0;Iteration<Text.Length;Iteration++)
			{
				Thread.Sleep(500);
				Length++;

				// Ak niektory ITEM hodil EXCEPTION, tak OKAMZITE UKONCIM ITEM.
				if (PLS.IsExceptional==true)
				{
					Console.WriteLine(string.Format("!!! TASK: [{0}] - UNHANDLED EXCEPTION DETECTED !",Task.CurrentId));
					return(-1000);
				}
			}

			// Pre Index==2 HODIM EXCEPTION.
			if (Index==2)
			{
				Console.WriteLine(string.Format("!!!!! TASK: [{0}] - THROWING UNHANDLED EXCEPTION !",Task.CurrentId));
				throw(new Exception("Some UNHANDLED EXCEPTION !"));
			}

			Console.WriteLine(string.Format("TASK: [{0}] - BODY FINISHED !",Task.CurrentId));

			return(Length);
		}
//-------------------------------------------------------------------------------------------------------
		private static void CancellationTaskMethod(object Param)
		{
			CancellationTokenSource	CTS=(CancellationTokenSource) Param;

			Thread.Sleep(4*1000);

			Console.WriteLine(string.Format("!!! CANCELLING in PROGRESS !",Task.CurrentId));
			CTS.Cancel();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private static void Test1()
		{
			Console.WriteLine(string.Format("MAIN THREAD ID is: [{0}] !",Task.CurrentId));

			string[]											Strings=new string[]{"Timothy Anderson","Jennifer Thompson","Atreyu","Bubu","Tony Randal","Bart King","David Kong"};
			ParallelLoopResult									Result=Parallel.ForEach<string,int>(Strings,LocalInit,SlowCalculationStringSize,LocalFinally);
			
			// !!!!! Aj CURRENT THREAD PARTICIPUJE na VYKONAVANI ForEach().
			Console.WriteLine(string.Format("TASK: [{0}] - Parallel.ForEach() FINISHED, IsCompleted: [{1}], LowestBreakIteration: [{2}] !",Task.CurrentId,Result.IsCompleted,Result.LowestBreakIteration));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test2()
		{
			Console.WriteLine(string.Format("MAIN THREAD ID is: [{0}] !",Task.CurrentId));

			string[]											Strings=new string[]{"Timothy Anderson","Jennifer Thompson","Atreyu","Bubu","Tony Randal","Bart King","David Kong"};

			try
			{
				// Simulujem UNHANDLED EXCEPTION.
				ParallelLoopResult								Result=Parallel.ForEach<string,int>(Strings,LocalInit,SlowCalculationStringSize_UnhandledException,LocalFinally);
			
				// !!!!! Aj CURRENT THREAD PARTICIPUJE na VYKONAVANI ForEach().
				Console.WriteLine(string.Format("TASK: [{0}] - Parallel.ForEach() FINISHED, IsCompleted: [{1}], LowestBreakIteration: [{2}] !",Task.CurrentId,Result.IsCompleted,Result.LowestBreakIteration));
			}
			catch(AggregateException AE)
			{
				Console.WriteLine("AGGREGATE EXCEPTION:");

				foreach (Exception E in AE.InnerExceptions)
				{
					Console.WriteLine(string.Format("\t[{0}]: [{1}] !",E.GetType(),E.Message));
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test3()
		{
			Console.WriteLine(string.Format("MAIN THREAD ID is: [{0}] !",Task.CurrentId));

			string[]											Strings=new string[]{"Timothy Anderson","Jennifer Thompson","Atreyu","Bubu","Tony Randal","Bart King","David Kong"};
			CancellationTokenSource								CTS=new CancellationTokenSource();
			ParallelOptions										PO=new ParallelOptions();

			PO.CancellationToken=CTS.Token;

			try
			{
				// Vytvorim TASK, ktory po istom case vykona CANCELLATION.
				Task											CancellationTask=new Task(CancellationTaskMethod,CTS);

				CancellationTask.Start();

				ParallelLoopResult								Result=Parallel.ForEach<string,int>(Strings,PO,LocalInit,SlowCalculationStringSize,LocalFinally);
			
				// !!!!! Aj CURRENT THREAD PARTICIPUJE na VYKONAVANI ForEach().
				Console.WriteLine(string.Format("TASK: [{0}] - Parallel.ForEach() FINISHED, IsCompleted: [{1}], LowestBreakIteration: [{2}] !",Task.CurrentId,Result.IsCompleted,Result.LowestBreakIteration));
			}
			catch(AggregateException AE)
			{
				Console.WriteLine("AGGREGATE EXCEPTION:");

				foreach (Exception E in AE.InnerExceptions)
				{
					Console.WriteLine(string.Format("\t[{0}]: [{1}] !",E.GetType(),E.Message));
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test4()
		{
			Console.WriteLine(string.Format("MAIN THREAD ID is: [{0}] !",Task.CurrentId));

			string[]											Strings=new string[]{"Timothy Anderson","Jennifer Thompson","Atreyu","Bubu","Tony Randal","Bart King","David Kong"};
			CancellationTokenSource								CTS=new CancellationTokenSource();
			ParallelOptions										PO=new ParallelOptions();

			PO.CancellationToken=CTS.Token;

			try
			{
				// ITEM 2 vykona BREAK.
				ParallelLoopResult								Result=Parallel.ForEach<string,int>(Strings,PO,LocalInit,SlowCalculationStringSize_Break,LocalFinally);
			
				// !!!!! Aj CURRENT THREAD PARTICIPUJE na VYKONAVANI ForEach().
				Console.WriteLine(string.Format("TASK: [{0}] - Parallel.ForEach() FINISHED, IsCompleted: [{1}], LowestBreakIteration: [{2}] !",Task.CurrentId,Result.IsCompleted,Result.LowestBreakIteration));
			}
			catch(AggregateException AE)
			{
				Console.WriteLine("AGGREGATE EXCEPTION:");

				foreach (Exception E in AE.InnerExceptions)
				{
					Console.WriteLine(string.Format("\t[{0}]: [{1}] !",E.GetType(),E.Message));
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test5()
		{
			Console.WriteLine(string.Format("MAIN THREAD ID is: [{0}] !",Task.CurrentId));

			string[]											Strings=new string[]{"Timothy Anderson","Jennifer Thompson","Atreyu","Bubu","Tony Randal","Bart King","David Kong"};
			CancellationTokenSource								CTS=new CancellationTokenSource();
			ParallelOptions										PO=new ParallelOptions();

			PO.CancellationToken=CTS.Token;

			try
			{
				// ITEM 2 vykona STOP.
				ParallelLoopResult								Result=Parallel.ForEach<string,int>(Strings,PO,LocalInit,SlowCalculationStringSize_Stop,LocalFinally);
			
				// !!!!! Aj CURRENT THREAD PARTICIPUJE na VYKONAVANI ForEach().
				Console.WriteLine(string.Format("TASK: [{0}] - Parallel.ForEach() FINISHED, IsCompleted: [{1}], LowestBreakIteration: [{2}] !",Task.CurrentId,Result.IsCompleted,Result.LowestBreakIteration));
			}
			catch(AggregateException AE)
			{
				Console.WriteLine("AGGREGATE EXCEPTION:");

				foreach (Exception E in AE.InnerExceptions)
				{
					Console.WriteLine(string.Format("\t[{0}]: [{1}] !",E.GetType(),E.Message));
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test6()
		{
			Console.WriteLine(string.Format("MAIN THREAD ID is: [{0}] !",Task.CurrentId));

			ParallelLoopResult									Result=Parallel.For<int>(0,MStrings.Length,LocalInit,SlowCalculationStringSize_For,LocalFinally);
			
			// !!!!! Aj CURRENT THREAD PARTICIPUJE na VYKONAVANI ForEach().
			Console.WriteLine(string.Format("TASK: [{0}] - Parallel.For() FINISHED, IsCompleted: [{1}], LowestBreakIteration: [{2}] !",Task.CurrentId,Result.IsCompleted,Result.LowestBreakIteration));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test7()
		{
			Console.WriteLine(string.Format("MAIN THREAD ID is: [{0}] !",Task.CurrentId));

			Action												Action1=new Action(InvokeAction);
			Action												Action2=new Action(InvokeAction);
			Action												Action3=new Action(InvokeAction);

			Parallel.Invoke(Action1,Action2,Action3);
			
			// !!!!! Aj CURRENT THREAD PARTICIPUJE na VYKONAVANI ForEach().
			Console.WriteLine(string.Format("TASK: [{0}] - Parallel.Invoke() FINISHED !",Task.CurrentId));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test8()
		{
			int[]												Collection=new int[1000];

			// !!!!! Init() a Finally() sa vykona tolkokrat ako POCET TASKS (NIE ITERATIONS), ktore spracovavali Parallel.For().
			Parallel.For<int>(0,10000,Init,Body,Finally);

			Console.WriteLine(string.Format("InitCounter: [{0}], BodyCounter: [{1}], FinallyCounter: [{2}] !",MInitCounter,MBodyCounter,MFinallyCounter));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			//Test1();
			//Test2();
			//Test3();
			//Test4();
			//Test5();
			//Test6();
			//Test7();
			Test8();

			Console.WriteLine("\nPress any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------