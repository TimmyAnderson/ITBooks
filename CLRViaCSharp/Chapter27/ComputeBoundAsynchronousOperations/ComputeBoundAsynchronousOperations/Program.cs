using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Runtime.Remoting.Messaging;
using System.Security.Principal;
//-------------------------------------------------------------------------------------------------------
namespace ComputeBoundAsynchronousOperations
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static int										MTaskCounter=0;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private static void Wait1Second()
		{
			int													TaskCounter=Interlocked.Increment(ref MTaskCounter);

			Console.WriteLine(string.Format("TASK: [{0}] STARTED !",TaskCounter));

			Thread.Sleep(1000);

			Console.WriteLine(string.Format("TASK: [{0}] FINISHED !",TaskCounter));
		}
//-------------------------------------------------------------------------------------------------------
		private static int[] SumParentTask(object Param)
		{
			Console.WriteLine(string.Format("!!!!!!!!!! THREAD: [{0}] - PARENT TASK STARTED !",Thread.CurrentThread.ManagedThreadId));

			int[]												Results=new int[3];

			// !!! Pouzijem KLAUZURY na prenos RESULTS.
			Task<int>											ChildTask1=new Task<int>(() => Results[0]=SumChildTask(200),TaskCreationOptions.AttachedToParent);
			Task<int>											ChildTask2=new Task<int>(() => Results[1]=SumChildTask(300),TaskCreationOptions.AttachedToParent);
			Task<int>											ChildTask3=new Task<int>(() => Results[2]=SumChildTask(400),TaskCreationOptions.AttachedToParent);

			// Tento PARENT TASK spusti dalsie 3 CHILDREN TASKS.
			ChildTask1.Start();
			ChildTask2.Start();
			ChildTask3.Start();

			Console.WriteLine(string.Format("!!!!!!!!!! THREAD: [{0}] - PARENT TASK FINISHED !",Thread.CurrentThread.ManagedThreadId));

			// !!!!! Kedze PARENT TASK SKONCI OKAMZITE zatial pole Results je PRAZDNE a NAPLNI SA AZ PO VYKONANI VSETKYCH TASKS.
			return(Results);
		}
//-------------------------------------------------------------------------------------------------------
		private static int[] SumParentTaskDeny(object Param)
		{
			Console.WriteLine(string.Format("!!!!!!!!!! THREAD: [{0}] - PARENT TASK STARTED !",Thread.CurrentThread.ManagedThreadId));

			int[]												Results=new int[3];

			// !!! Pouzijem KLAUZURY na prenos RESULTS.
			Task<int>											ChildTask1=new Task<int>(() => Results[0]=SumChildTask(200),TaskCreationOptions.AttachedToParent);
			Task<int>											ChildTask2=new Task<int>(() => Results[1]=SumChildTask(300),TaskCreationOptions.AttachedToParent);
			Task<int>											ChildTask3=new Task<int>(() => Results[2]=SumChildTask(400),TaskCreationOptions.AttachedToParent);

			// Tento PARENT TASK spusti dalsie 3 CHILDREN TASKS.
			ChildTask1.Start();
			ChildTask2.Start();
			ChildTask3.Start();

			Console.WriteLine(string.Format("!!!!!!!!!! THREAD: [{0}] - PARENT TASK FINISHED !",Thread.CurrentThread.ManagedThreadId));

			// !!!!! Kedze PARENT TASK ma ZABLOKOVANU moznost vytvarania CHILD TASKS, CHILD TASKS budu spustene ako NON-CHILD TASKS a VAZBA medzi PARENT a CHILD NEBUDE EXISTOVAT.
			return(Results);
		}
//-------------------------------------------------------------------------------------------------------
		private static int SumChildTask(object Param)
		{
			int													To=(int) Param;

			Console.WriteLine(string.Format("THREAD: [{0}] - CHILD TASK STARTED CALCULATION !",Thread.CurrentThread.ManagedThreadId));

			int													Ret=0;
			
			for (int Index=0;Index<To;Index++)
			{
				Thread.Sleep(10);

				Ret++;
			}

			Console.WriteLine(string.Format("THREAD: [{0}] - CHILD TASK FINISHED CALCULATION !",Thread.CurrentThread.ManagedThreadId));

			return(Ret);
		}
//-------------------------------------------------------------------------------------------------------
		private static void PrintAggregateException(AggregateException AE)
		{
			Console.WriteLine("AGGREGATE EXCEPTION:");

			foreach (Exception E in AE.InnerExceptions)
			{
				if ((E is TaskCanceledException)==true)
				{
					TaskCanceledException						TypedException=(TaskCanceledException) E;
					Task										Task=TypedException.Task;
					
					Console.WriteLine(string.Format("\t[{0}]: [{1}], TASK [{2}] !",E.GetType(),E.Message,Task));
				}
				else
				{
					Console.WriteLine(string.Format("\t[{0}]: [{1}] !",E.GetType(),E.Message));
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void PrintResultOnCompletedTask(Task<int> PreviousTask)
		{
			Console.WriteLine(string.Format("!!!!!!!!!! THREAD: [{0}] - TASK COMPLETED SUCCESSFULLY - RESULT: [{1}] !",Thread.CurrentThread.ManagedThreadId,PreviousTask.Result));
		}
//-------------------------------------------------------------------------------------------------------
		private static void PrintResultOnCancellationTask(Task<int> PreviousTask)
		{
			Console.WriteLine(string.Format("!!!!!!!!!! THREAD: [{0}] - TASK CANCELLED !",Thread.CurrentThread.ManagedThreadId));
		}
//-------------------------------------------------------------------------------------------------------
		private static void PrintResultOnFailedTask(Task<int> PreviousTask)
		{
			Console.WriteLine(string.Format("!!!!!!!!!! THREAD: [{0}] - TASK FAILED - EXCEPTION: [{1}] !",Thread.CurrentThread.ManagedThreadId,PreviousTask.Exception.Message));
		}
//-------------------------------------------------------------------------------------------------------
		private static void WaitTask(object Param)
		{
			int													Timeout=(int) Param;

			Console.WriteLine(string.Format("THREAD: [{0}] - WaitTask() - STARTED !",Thread.CurrentThread.ManagedThreadId));
			Thread.Sleep(Timeout);
			Console.WriteLine(string.Format("THREAD: [{0}] - WaitTask() - FINISHED !",Thread.CurrentThread.ManagedThreadId));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Print1ResultTask(Task<int> PreviousTask)
		{
			Console.WriteLine(string.Format("THREAD: [{0}] - Print1ResultTask() - STARTED !",Thread.CurrentThread.ManagedThreadId));
			Thread.Sleep(1000);
			Console.WriteLine(string.Format("THREAD: [{0}] - Print1ResultTask() - RESULT: [{1}] !",Thread.CurrentThread.ManagedThreadId,PreviousTask.Result));
			Console.WriteLine(string.Format("THREAD: [{0}] - Print1ResultTask() - FINISHED !",Thread.CurrentThread.ManagedThreadId));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Print2ResultTask(Task<int> PreviousTask)
		{
			Console.WriteLine(string.Format("THREAD: [{0}] - Print2ResultTask() - STARTED !",Thread.CurrentThread.ManagedThreadId));
			Thread.Sleep(1000);
			Console.WriteLine(string.Format("THREAD: [{0}] - Print2ResultTask() - RESULT: [{1}] !",Thread.CurrentThread.ManagedThreadId,PreviousTask.Result));
			Console.WriteLine(string.Format("THREAD: [{0}] - Print2ResultTask() - FINISHED !",Thread.CurrentThread.ManagedThreadId));
		}
//-------------------------------------------------------------------------------------------------------
		private static int RunSumTask()
		{
			Console.WriteLine(string.Format("THREAD: [{0}] - TASK STARTED CALCULATION !",Thread.CurrentThread.ManagedThreadId));

			int													Ret=0;
			
			for (int Index=0;Index<300;Index++)
			{
				Thread.Sleep(10);

				Ret++;
			}

			Console.WriteLine(string.Format("THREAD: [{0}] - TASK FINISHED CALCULATION !",Thread.CurrentThread.ManagedThreadId));

			return(Ret);
		}
//-------------------------------------------------------------------------------------------------------
		private static int SumTask(object Param)
		{
			Console.WriteLine(string.Format("THREAD: [{0}] - TASK STARTED CALCULATION !",Thread.CurrentThread.ManagedThreadId));

			int													Ret=0;
			
			for (int Index=0;Index<300;Index++)
			{
				Thread.Sleep(10);

				Ret++;
			}

			Console.WriteLine(string.Format("THREAD: [{0}] - TASK FINISHED CALCULATION !",Thread.CurrentThread.ManagedThreadId));

			return(Ret);
		}
//-------------------------------------------------------------------------------------------------------
		private static int SumTaskWithException(object Param)
		{
			Console.WriteLine(string.Format("THREAD: [{0}] - TASK STARTED CALCULATION !",Thread.CurrentThread.ManagedThreadId));

			int													Ret=0;
			
			for (int Index=0;Index<300;Index++)
			{
				Thread.Sleep(10);

				Ret++;
			}

			Console.WriteLine(string.Format("THREAD: [{0}] - TASK FINISHED CALCULATION and is going to THROW EXCEPTION !",Thread.CurrentThread.ManagedThreadId));
			
			// Hodim EXCEPTION.
			throw(new Exception("Some EXCEPTION HAPPENED !"));
		}
//-------------------------------------------------------------------------------------------------------
		private static int SumTaskWithCancellation(object Param)
		{
			Console.WriteLine(string.Format("THREAD: [{0}] - TASK STARTED CALCULATION !",Thread.CurrentThread.ManagedThreadId));

			CancellationToken									CT=(CancellationToken) Param;
			int													Ret=0;
			
			for (int Index=0;Index<300;Index++)
			{
				if (CT.WaitHandle.WaitOne(10)==true)
				{
					// !!! Vykonanie CANCELLATION oznamujem vratenim OperationCanceledException.
					throw(new OperationCanceledException("Operation WAS CANCELLED !",CT));
				}

				Ret++;
			}
			
			Console.WriteLine(string.Format("THREAD: [{0}] - TASK FINISHED CALCULATION !",Thread.CurrentThread.ManagedThreadId));

			return(Ret);
		}
//-------------------------------------------------------------------------------------------------------
		private static void TaskScheduler_UnobservedTaskException(object Sender, UnobservedTaskExceptionEventArgs E)
		{
			Console.WriteLine(string.Format("UNOBSERVED EXCEPTION : [{0}] !",E.Exception));
			
			// Zachytim UNOBSERVED EXCEPTION.
			E.SetObserved();
		}
//-------------------------------------------------------------------------------------------------------
		private static bool HandleException(Exception E)
		{
			Console.WriteLine(string.Format("EXCEPTION HANDLING: [{0}] !",E.Message));

			return(false);
		}
//-------------------------------------------------------------------------------------------------------
		private static void CanBeCancelledThread1(object Param)
		{
			CancellationToken									CT=(CancellationToken) Param;

			for (int Index=0;Index<100;Index++)
			{
				// Kontrolujem ci nedoslo k poziadavke na CANCELLATION.
				if (CT.WaitHandle.WaitOne(200)==true)
				{
					Console.WriteLine(string.Format("THREAD: [{0}] - THREAD WILL BE CANCELLED !",Thread.CurrentThread.ManagedThreadId));
					break;
				}

				Console.WriteLine(string.Format("THREAD: [{0}] - Waiting for CANCELLATION, IsCancellationRequested: [{1}] !",Thread.CurrentThread.ManagedThreadId,CT.IsCancellationRequested));
			}

			Console.WriteLine(string.Format("THREAD: [{0}] - THREAD FINISHED !",Thread.CurrentThread.ManagedThreadId));
		}
//-------------------------------------------------------------------------------------------------------
		private static void CanBeCancelledThread2(object Param)
		{
			CancellationToken									CT=(CancellationToken) Param;

			for (int Index=0;Index<100;Index++)
			{
				Thread.Sleep(200);

				// Kontrolujem ci nedoslo k poziadavke na CANCELLATION.
				if (CT.IsCancellationRequested==true)
				{
					Console.WriteLine(string.Format("THREAD: [{0}] - THREAD WILL BE CANCELLED !",Thread.CurrentThread.ManagedThreadId));
					break;
				}

				Console.WriteLine(string.Format("THREAD: [{0}] - Waiting for CANCELLATION, IsCancellationRequested: [{1}] !",Thread.CurrentThread.ManagedThreadId,CT.IsCancellationRequested));
			}

			Console.WriteLine(string.Format("THREAD: [{0}] - THREAD FINISHED !",Thread.CurrentThread.ManagedThreadId));
		}
//-------------------------------------------------------------------------------------------------------
		private static void CanBeCancelledThread3(object Param)
		{
			CancellationToken									CT=(CancellationToken) Param;

			for (int Index=0;Index<100;Index++)
			{
				Thread.Sleep(200);

				try
				{
					// Kontrolujem ci nedoslo k poziadavke na CANCELLATION.
					CT.ThrowIfCancellationRequested();
				}
				catch(OperationCanceledException)
				{
					Console.WriteLine(string.Format("THREAD: [{0}] - THREAD WILL BE CANCELLED !",Thread.CurrentThread.ManagedThreadId));
					break;
				}

				Console.WriteLine(string.Format("THREAD: [{0}] - Waiting for CANCELLATION, IsCancellationRequested: [{1}] !",Thread.CurrentThread.ManagedThreadId,CT.IsCancellationRequested));
			}

			Console.WriteLine(string.Format("THREAD: [{0}] - THREAD FINISHED !",Thread.CurrentThread.ManagedThreadId));
		}
//-------------------------------------------------------------------------------------------------------
		private static void CancellationMethod1(object Param)
		{
			Console.WriteLine(string.Format("THREAD: [{0}] - CANCELLATION METHOD 1 CALLED !",Thread.CurrentThread.ManagedThreadId));
		}
//-------------------------------------------------------------------------------------------------------
		private static void CancellationMethod2(object Param)
		{
			Console.WriteLine(string.Format("THREAD: [{0}] - CANCELLATION METHOD 2 CALLED !",Thread.CurrentThread.ManagedThreadId));
		}
//-------------------------------------------------------------------------------------------------------
		private static void CancellationMethod3(object Param)
		{
			Console.WriteLine(string.Format("THREAD: [{0}] - CANCELLATION METHOD 3 CALLED !",Thread.CurrentThread.ManagedThreadId));
		}
//-------------------------------------------------------------------------------------------------------
		private static void CancellationMethodSource1(object Param)
		{
			Console.WriteLine(string.Format("THREAD: [{0}] - CANCELLATION METHOD for SOURCE 1 CALLED !",Thread.CurrentThread.ManagedThreadId));
		}
//-------------------------------------------------------------------------------------------------------
		private static void CancellationMethodSource2(object Param)
		{
			Console.WriteLine(string.Format("THREAD: [{0}] - CANCELLATION METHOD for SOURCE 2 CALLED !",Thread.CurrentThread.ManagedThreadId));
		}
//-------------------------------------------------------------------------------------------------------
		private static void CancellationMethodCombinedSource(object Param)
		{
			Console.WriteLine(string.Format("THREAD: [{0}] - CANCELLATION METHOD for COMBINED SOURCE CALLED !",Thread.CurrentThread.ManagedThreadId));
		}
//-------------------------------------------------------------------------------------------------------
		private static void CancellationMethodWithException1(object Param)
		{
			Console.WriteLine(string.Format("THREAD: [{0}] - CANCELLATION METHOD 1 CALLED !",Thread.CurrentThread.ManagedThreadId));
			throw(new Exception("EXCEPTION 1 !"));
		}
//-------------------------------------------------------------------------------------------------------
		private static void CancellationMethodWithException2(object Param)
		{
			Console.WriteLine(string.Format("THREAD: [{0}] - CANCELLATION METHOD 2 CALLED !",Thread.CurrentThread.ManagedThreadId));
			throw(new Exception("EXCEPTION 2 !"));
		}
//-------------------------------------------------------------------------------------------------------
		private static void CancellationMethodWithException3(object Param)
		{
			Console.WriteLine(string.Format("THREAD: [{0}] - CANCELLATION METHOD 3 CALLED !",Thread.CurrentThread.ManagedThreadId));
			throw(new Exception("EXCEPTION 3 !"));
		}
//-------------------------------------------------------------------------------------------------------
		private static void PrintSomething(object Param)
		{
			for (int Index=0;Index<100;Index++)
			{
				Console.WriteLine(string.Format("THREAD [{0}] - iteration [{1}] !",Param,Index+1));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void PrintExecutionContext(object Param)
		{
			CName												Name=(CName) CallContext.LogicalGetData("Name");

			Console.WriteLine(string.Format("THREAD [{0}] - Name from EXECUTION CONTEXT: [{1}], Identity: [{2}] !",Thread.CurrentThread.Name,Name,Thread.CurrentPrincipal.Identity.Name));
		}
//-------------------------------------------------------------------------------------------------------
		private static void ThreadPoolPrintExecutionContext(object Param)
		{
			CName												Name=(CName) CallContext.LogicalGetData("Name");

			Console.WriteLine(string.Format("THREAD [{0}] - Name from EXECUTION CONTEXT: [{1}], Identity: [{2}] !",Param,Name,Thread.CurrentPrincipal.Identity.Name));
		}
//-------------------------------------------------------------------------------------------------------
		private static void UnhandledException(object Param)
		{
			throw(new Exception("EXCEPTION in TP !"));
		}
//-------------------------------------------------------------------------------------------------------
		private static void CurrentDomain_UnhandledException(object Sender, UnhandledExceptionEventArgs E)
		{
			Console.WriteLine(string.Format("UNHANDLED EXCEPTION, IsTerminating: [{0}], EXCEPTION: [{1}] !",E.IsTerminating,E.ExceptionObject));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private static void Test1()
		{
			ThreadPool.QueueUserWorkItem(PrintSomething,1);
			ThreadPool.QueueUserWorkItem(PrintSomething,2);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test2()
		{
			AppDomain.CurrentDomain.UnhandledException+=new UnhandledExceptionEventHandler(CurrentDomain_UnhandledException);

			ThreadPool.QueueUserWorkItem(UnhandledException,null);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test3()
		{
			CName												Name=new CName("Timmy","Anderson",12);
			Thread												T;

			// Nastavim PRINCIPAL.
			Thread.CurrentPrincipal=new GenericPrincipal(new GenericIdentity("Timmy"),new string[0]);

			// Zapisem nejake data do EXECUTION CONTEXT CURRENT THREAD.
			CallContext.LogicalSetData("Name",Name);

			// Vytvorim novy THREAD pri POVOLENOM PRENOSE EXECUTION CONTEXT.
			T=new Thread(PrintExecutionContext);
			T.Name="DEFAULT FLOW";

			T.Start();
			T.Join();

			// Zablokujem prenos EXECUTION CONTEXT.
			ExecutionContext.SuppressFlow();

			// Vytvorim novy THREAD pri ZAKAZANOM PRENOSE EXECUTION CONTEXT.
			T=new Thread(PrintExecutionContext);
			T.Name="FLOW SUPPRESSED";

			T.Start();
			T.Join();

			// Povolim prenos EXECUTION CONTEXT.
			ExecutionContext.RestoreFlow();

			// Vytvorim novy THREAD pri ZNOVA POVOLENOM PRENOSE EXECUTION CONTEXT.
			T=new Thread(PrintExecutionContext);
			T.Name="FLOW RESTORED";

			T.Start();
			T.Join();
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test4()
		{
			CName												Name=new CName("Timmy","Anderson",12);

			// Nastavim PRINCIPAL.
			Thread.CurrentPrincipal=new GenericPrincipal(new GenericIdentity("Timmy"),new string[0]);

			// Zapisem nejake data do EXECUTION CONTEXT CURRENT THREAD.
			CallContext.LogicalSetData("Name",Name);

			// Vytvorim WORK ITEM pri POVOLENOM PRENOSE EXECUTION CONTEXT.
			ThreadPool.QueueUserWorkItem(ThreadPoolPrintExecutionContext,"DEFAULT FLOW");

			// Zablokujem prenos EXECUTION CONTEXT.
			ExecutionContext.SuppressFlow();

			// Vytvorim WORK ITEM pri ZAKAZANOM PRENOSE EXECUTION CONTEXT.
			ThreadPool.QueueUserWorkItem(ThreadPoolPrintExecutionContext,"FLOW SUPPRESSED");

			// Povolim prenos EXECUTION CONTEXT.
			ExecutionContext.RestoreFlow();

			// Vytvorim novy THREAD pri ZNOVA POVOLENOM PRENOSE EXECUTION CONTEXT.
			ThreadPool.QueueUserWorkItem(ThreadPoolPrintExecutionContext,"FLOW RESTORED");
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test5()
		{
			// Vytvorim TOKEN, ktorym budem riadit CANCELLATION.
			CancellationTokenSource								CTS=new CancellationTokenSource();
			Thread												T=new Thread(CanBeCancelledThread1);

			// Ako parameter do THREAD zaslem CancellationToken.
			T.Start(CTS.Token);

			Thread.Sleep(3000);

			Console.WriteLine("\nTHREAD will be CANCELLED !");

			CTS.Cancel();
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test6()
		{
			// Vytvorim TOKEN, ktorym budem riadit CANCELLATION.
			CancellationTokenSource								CTS=new CancellationTokenSource();
			Thread												T=new Thread(CanBeCancelledThread2);

			// Ako parameter do THREAD zaslem CancellationToken.
			T.Start(CTS.Token);

			Thread.Sleep(3000);

			Console.WriteLine("\nTHREAD will be CANCELLED !");

			CTS.Cancel();
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test7()
		{
			// Vytvorim TOKEN, ktorym budem riadit CANCELLATION.
			CancellationTokenSource								CTS=new CancellationTokenSource();
			Thread												T=new Thread(CanBeCancelledThread3);

			// Ako parameter do THREAD zaslem CancellationToken.
			T.Start(CTS.Token);

			Thread.Sleep(3000);

			Console.WriteLine("\nTHREAD will be CANCELLED !");

			CTS.Cancel();
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test8()
		{
			CancellationTokenSource								CTS=new CancellationTokenSource();
			Thread												T=new Thread(CanBeCancelledThread1);

			// !!! Ako parameter do THREAD zaslem CancellationToken typu NONE, ktory NEMOZE BYT NIKDY CANCELLED, a preto THREAD NEBUDE CANCELLED.
			T.Start(CancellationToken.None);

			Thread.Sleep(3000);

			Console.WriteLine("\nTHREAD will be CANCELLED !");

			// !!! NESPOSOBI CANCELLATION daneho THREAD.
			CTS.Cancel();
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test9()
		{
			// Vytvorim TOKEN, ktorym budem riadit CANCELLATION.
			// !!! TOKEN AUTOMATICKY po 3 SEKUNDACH sposobi CANCELLATION.
			CancellationTokenSource								CTS=new CancellationTokenSource(3000);
			Thread												T=new Thread(CanBeCancelledThread1);

			// Ako parameter do THREAD zaslem CancellationToken.
			T.Start(CTS.Token);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test10()
		{
			// Vytvorim TOKEN, ktorym budem riadit CANCELLATION.
			CancellationTokenSource								CTS=new CancellationTokenSource();
			Thread												T=new Thread(CanBeCancelledThread1);

			// Ako parameter do THREAD zaslem CancellationToken.
			T.Start(CTS.Token);

			// !!! CANCELLATION sa AUTOMATICKY vykona po 3 SEKUNDACH.
			CTS.CancelAfter(3000);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test11()
		{
			// Vytvorim TOKEN, ktorym budem riadit CANCELLATION.
			CancellationTokenSource								CTS=new CancellationTokenSource();
			Thread												T=new Thread(CanBeCancelledThread1);

			// Zaregistrujem si CALLBACK metodu, ktoru budem volat pri CANCELLATION.
			CancellationTokenRegistration						CTR1=CTS.Token.Register(CancellationMethod1,null);
			CancellationTokenRegistration						CTR2=CTS.Token.Register(CancellationMethod2,null);
			CancellationTokenRegistration						CTR3=CTS.Token.Register(CancellationMethod3,null);

			// Ako parameter do THREAD zaslem CancellationToken.
			T.Start(CTS.Token);

			Thread.Sleep(1000);

			// !!! Volanim Dispose() sa zrusi volanie CALLBACK METODY.
			CTR1.Dispose();

			Thread.Sleep(2000);

			Console.WriteLine("\nTHREAD will be CANCELLED !");

			CTS.Cancel();
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test12()
		{
			// Vytvorim TOKEN, ktorym budem riadit CANCELLATION.
			CancellationTokenSource								CTS=new CancellationTokenSource();
			Thread												T=new Thread(CanBeCancelledThread1);

			// Zaregistrujem si CALLBACK metodu, ktoru budem volat pri CANCELLATION.
			CancellationTokenRegistration						CTR1=CTS.Token.Register(CancellationMethodWithException1,null);
			CancellationTokenRegistration						CTR2=CTS.Token.Register(CancellationMethodWithException2,null);
			CancellationTokenRegistration						CTR3=CTS.Token.Register(CancellationMethodWithException3,null);

			// Ako parameter do THREAD zaslem CancellationToken.
			T.Start(CTS.Token);

			Thread.Sleep(3000);

			Console.WriteLine("\nTHREAD will be CANCELLED !");

			try
			{
				// !!!!! Aj ked CALLBACK METHODS hodili UNHANDLED EXCEPTIONS, tak budu vyvolane vsetky 3.
				CTS.Cancel();
			}
			// !!! Ak VIACERO CALLBACK METHODS hodilo EXCEPTIONS, tak je generovana AggregateException.
			catch(AggregateException E)
			{
				Console.WriteLine("AggregateException OCCURED with INNER EXCEPTIONS:");

				foreach(Exception InnerException in E.InnerExceptions)
				{
					Console.WriteLine(string.Format("INNER EXCEPTION [{0}] !",InnerException.Message));
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("Exception OCCURED [{0}] !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test13()
		{
			// Vytvorim TOKEN, ktorym budem riadit CANCELLATION.
			CancellationTokenSource								CTS=new CancellationTokenSource();
			Thread												T=new Thread(CanBeCancelledThread1);

			// Zaregistrujem si CALLBACK metodu, ktoru budem volat pri CANCELLATION.
			CancellationTokenRegistration						CTR1=CTS.Token.Register(CancellationMethodWithException1,null);
			CancellationTokenRegistration						CTR2=CTS.Token.Register(CancellationMethodWithException2,null);
			CancellationTokenRegistration						CTR3=CTS.Token.Register(CancellationMethodWithException3,null);

			// Ako parameter do THREAD zaslem CancellationToken.
			T.Start(CTS.Token);

			Thread.Sleep(3000);

			Console.WriteLine("\nTHREAD will be CANCELLED !");

			try
			{
				// !!!!! Ak niektora z CALLBACK METHODS, tak ostatne sa NEZAVOLAJU.
				CTS.Cancel(true);
			}
			// !!! Ak VIACERO CALLBACK METHODS hodilo EXCEPTIONS, tak je generovana AggregateException.
			// !!!!! Tu sa to vsak NESTANE, lebo Cancel() bola volana s PARAMETROM TRUE.
			catch(AggregateException E)
			{
				Console.WriteLine("AggregateException OCCURED with INNER EXCEPTIONS:");

				foreach(Exception InnerException in E.InnerExceptions)
				{
					Console.WriteLine(string.Format("INNER EXCEPTION [{0}] !",InnerException.Message));
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("Exception OCCURED [{0}] !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test14()
		{
			CancellationTokenSource								CTS1=new CancellationTokenSource();
			CancellationTokenSource								CTS2=new CancellationTokenSource();

			CancellationToken									Token1=CTS1.Token;
			CancellationToken									Token2=CTS2.Token;

			// !!! Vytvori COMBINED CANCELLATION TOKEN SOURCE.
			CancellationTokenSource								CTSCombined=CancellationTokenSource.CreateLinkedTokenSource(Token1,Token2);

			CancellationToken									CombinedToken=CTSCombined.Token;

			Thread												T=new Thread(CanBeCancelledThread1);

			CancellationTokenRegistration						CTR1=CTS1.Token.Register(CancellationMethodSource1,null);
			CancellationTokenRegistration						CTR2=CTS2.Token.Register(CancellationMethodSource2,null);
			CancellationTokenRegistration						CTR3=CTSCombined.Token.Register(CancellationMethodCombinedSource,null);

			// Ako parameter do THREAD zaslem CancellationToken.
			T.Start(CombinedToken);

			Thread.Sleep(3000);

			Console.WriteLine("\nTHREAD will be CANCELLED !");

			// !!!!! Ak NIEKTORY z TOKEN Token1, alebo Token2 je CANCELLED, tak je aj COMBINED CANCELLATION TOKEN CANCELLED.
			// !!! REGISTRED METHODS sa vyvolaju pre Token2 a COMBINED TOKEN, ale NIE pre Token1.
			CTS2.Cancel(true);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test15()
		{
			Func<int>											TaskFunction=new Func<int>(RunSumTask);

			// Vytvori TASK a hned ho aj spusti.
			Task<int>											SomeTask=Task.Run<int>(TaskFunction);

			Console.WriteLine(string.Format("THREAD: [{0}] - New TASK CREATED and STARTED and now WAITING for FINISH !",Thread.CurrentThread.ManagedThreadId));

			// Pockam kym TASK NESKONCI.
			SomeTask.Wait();

			int													Result=SomeTask.Result;

			Console.WriteLine(string.Format("THREAD: [{0}] - TASK FINISHED with RESULT: [{1}] !",Thread.CurrentThread.ManagedThreadId,Result));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test16()
		{
			Task<int>											SomeTask=new Task<int>(SumTask,null);

			Console.WriteLine(string.Format("THREAD: [{0}] - New TASK CREATED !",Thread.CurrentThread.ManagedThreadId));

			SomeTask.Start();

			Console.WriteLine(string.Format("THREAD: [{0}] - New TASK STARTED and WAITING for FINISH !",Thread.CurrentThread.ManagedThreadId));

			// Pockam kym TASK NESKONCI.
			SomeTask.Wait();

			int													Result=SomeTask.Result;

			Console.WriteLine(string.Format("THREAD: [{0}] - TASK FINISHED with RESULT: [{1}] !",Thread.CurrentThread.ManagedThreadId,Result));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test17()
		{
			Task<int>											SomeTask=new Task<int>(SumTask,null);
			
			Console.WriteLine(string.Format("THREAD: [{0}] - New TASK CREATED !",Thread.CurrentThread.ManagedThreadId));

			SomeTask.Start();

			Console.WriteLine(string.Format("THREAD: [{0}] - New TASK STARTED and WAITING for FINISH !",Thread.CurrentThread.ManagedThreadId));

			// !!! Pockam kym TASK NESKONCI. Property Result urobi WAIT, ak este TASK neskoncil.
			int													Result=SomeTask.Result;

			Console.WriteLine(string.Format("THREAD: [{0}] - TASK FINISHED with RESULT: [{1}] !",Thread.CurrentThread.ManagedThreadId,Result));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test18()
		{
			Task<int>											SomeTask=new Task<int>(SumTask,null);
		
			Console.WriteLine(string.Format("THREAD: [{0}] - New TASK CREATED !",Thread.CurrentThread.ManagedThreadId));

			SomeTask.Start();

			Console.WriteLine(string.Format("THREAD: [{0}] - New TASK STARTED and WAITING for FINISH !",Thread.CurrentThread.ManagedThreadId));

			// !!! Pockam kym TASK NESKONCI. PROPERTY Exception urobi WAIT, ak este TASK neskoncil.
			Exception											E=SomeTask.Exception;
			int													Result=SomeTask.Result;

			Console.WriteLine(string.Format("THREAD: [{0}] - TASK FINISHED with RESULT: [{1}], EXCEPTION: [{2}] !",Thread.CurrentThread.ManagedThreadId,Result,E));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test19()
		{
			Task<int>											SomeTask=new Task<int>(SumTaskWithException,null);
		
			Console.WriteLine(string.Format("THREAD: [{0}] - New TASK CREATED !",Thread.CurrentThread.ManagedThreadId));

			SomeTask.Start();

			Console.WriteLine(string.Format("THREAD: [{0}] - New TASK STARTED and WAITING for FINISH !",Thread.CurrentThread.ManagedThreadId));

			try
			{
				// Pockam kym TASK NESKONCI.
				SomeTask.Wait();

				int												Result=SomeTask.Result;

				Console.WriteLine(string.Format("THREAD: [{0}] - TASK FINISHED with RESULT: [{1}] !",Thread.CurrentThread.ManagedThreadId,Result));
			}
			catch(AggregateException AE)
			{
				// !!! Pockam kym TASK NESKONCI. Property Exception urobi WAIT, ak este TASK neskoncil.
				Exception										E=SomeTask.Exception;

				Console.WriteLine(string.Format("THREAD: [{0}] - TASK FINISHED with EXCEPTION: [{1}] !",Thread.CurrentThread.ManagedThreadId,AE));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test20()
		{
			Task<int>											SomeTask=new Task<int>(SumTaskWithException,null);
		
			Console.WriteLine(string.Format("THREAD: [{0}] - New TASK CREATED !",Thread.CurrentThread.ManagedThreadId));

			SomeTask.Start();

			Console.WriteLine(string.Format("THREAD: [{0}] - New TASK STARTED and WAITING for FINISH !",Thread.CurrentThread.ManagedThreadId));

			try
			{
				// Pockam kym TASK NESKONCI.
				int												Result=SomeTask.Result;

				Console.WriteLine(string.Format("THREAD: [{0}] - TASK FINISHED with RESULT: [{1}] !",Thread.CurrentThread.ManagedThreadId,Result));
			}
			catch(AggregateException AE1)
			{
				Console.WriteLine(string.Format("THREAD: [{0}] - TASK FINISHED with EXCEPTION: [{1}] !",Thread.CurrentThread.ManagedThreadId,AE1));

				try
				{
					// !!!!! Ak METHOD HandleException() aspon pre 1 EXCEPTION z AE1.InnerExceptions vratila FALSE, tak je generovana AggregateException obsahujuca v PROPERTY InnerExceptions VSETKY tie EXCEPTIONS, pre ktore METHOD HandleException() vratila FALSE.
					AE1.Handle(HandleException);
				}
				catch(AggregateException AE2)
				{
					Console.WriteLine(string.Format("THREAD: [{0}] - NOT ALL EXCEPTIONS in AggregateExcption were HANDLED ! EXCEPTION: [{1}] !",Thread.CurrentThread.ManagedThreadId,AE2));
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test21()
		{
			try
			{
				NullReferenceException							Exception1=new NullReferenceException("Some NULL !");
				ArgumentException								Exception2=new ArgumentException("Some ARGUMENT !");
				NullReferenceException							ExceptionAggregate1=new NullReferenceException("Some NULL in AGGREGATE EXCEPTION !");
				ArgumentException								ExceptionAggregate2=new ArgumentException("Some ARGUMENT in AGGREGATE EXCEPTION !");
				AggregateException								Exception3=new AggregateException(ExceptionAggregate1,ExceptionAggregate2);
				AggregateException								Exception=new AggregateException(Exception1,Exception2,Exception3);

				throw(Exception);
			}
			catch(AggregateException AE)
			{
				foreach(Exception E in AE.InnerExceptions)
				{
					Console.WriteLine(string.Format("THREAD: [{0}] - NOT FLATTENED EXCEPTION: [{1}] !",Thread.CurrentThread.ManagedThreadId,E.Message));
				}

				AggregateException								FlattenedException=AE.Flatten();

				foreach(Exception E in FlattenedException.InnerExceptions)
				{
					Console.WriteLine(string.Format("THREAD: [{0}] - FLATTENED EXCEPTION: [{1}] !",Thread.CurrentThread.ManagedThreadId,E.Message));
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test22()
		{
			TaskScheduler.UnobservedTaskException+=new EventHandler<UnobservedTaskExceptionEventArgs>(TaskScheduler_UnobservedTaskException);

			Task<int>											SomeTask=new Task<int>(SumTaskWithException,null);
		
			Console.WriteLine(string.Format("THREAD: [{0}] - New TASK CREATED !",Thread.CurrentThread.ManagedThreadId));

			SomeTask.Start();

			Console.WriteLine(string.Format("THREAD: [{0}] - New TASK STARTED and PRESS ANY KEY to CONTINUE !",Thread.CurrentThread.ManagedThreadId));
			Console.ReadLine();

			SomeTask=null;

			// !!! Umyselne spustim GC.Collect(), aby sa zavolal FINALIZER, ktory bude generovat UNHANDLED EXCEPTION.
			GC.Collect();

			// Pockam na zavolanie Finalize().
			GC.WaitForPendingFinalizers();
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test23()
		{
			Task												Task1=new Task(WaitTask,3000);
			Task												Task2=new Task(WaitTask,2000);
		
			Task1.Start();
			Task2.Start();

			Console.WriteLine(string.Format("THREAD: [{0}] - WaitAny() CALLED !",Thread.CurrentThread.ManagedThreadId));

			int													Index=Task.WaitAny(Task1,Task2);

			Console.WriteLine(string.Format("THREAD: [{0}] - WaitAny() FINISHED with RESULT [{1}] !",Thread.CurrentThread.ManagedThreadId,Index));
	
			Console.WriteLine(string.Format("THREAD: [{0}] - WaitAll() CALLED !",Thread.CurrentThread.ManagedThreadId));

			bool												Finished=Task.WaitAll(new Task[]{Task1,Task2},5000);

			Console.WriteLine(string.Format("THREAD: [{0}] - WaitAll() FINISHED with RESULT [{1}] !",Thread.CurrentThread.ManagedThreadId,Finished));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test24()
		{
			Task												Task1=new Task(WaitTask,3000);
			Task												Task2=new Task(WaitTask,2000);
		
			Task1.Start();
			Task2.Start();

			Console.WriteLine(string.Format("THREAD: [{0}] - WaitAny() CALLED !",Thread.CurrentThread.ManagedThreadId));

			int													Index=Task.WaitAny(new Task[]{Task1,Task2},1000);

			Console.WriteLine(string.Format("THREAD: [{0}] - WaitAny() FINISHED with RESULT [{1}] !",Thread.CurrentThread.ManagedThreadId,Index));
	
			Console.WriteLine(string.Format("THREAD: [{0}] - WaitAll() CALLED !",Thread.CurrentThread.ManagedThreadId));

			bool												Finished=Task.WaitAll(new Task[]{Task1,Task2},5000);

			Console.WriteLine(string.Format("THREAD: [{0}] - WaitAll() FINISHED with RESULT [{1}] !",Thread.CurrentThread.ManagedThreadId,Finished));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test25()
		{
			// Po 2 SEKUNDACH bude automaticky CANCELLED.
			CancellationTokenSource								CTS=new CancellationTokenSource(2000);
			Task<int>											Task1=new Task<int>(SumTaskWithCancellation,CTS.Token);
			Task												Task2=new Task(WaitTask,1000);
		
			Task1.Start();
			Task2.Start();

			Console.WriteLine(string.Format("THREAD: [{0}] - WaitAny() CALLED !",Thread.CurrentThread.ManagedThreadId));

			try
			{
				int												Index=Task.WaitAny(new Task[]{Task1,Task2},1000);

				Console.WriteLine(string.Format("THREAD: [{0}] - WaitAny() FINISHED with RESULT [{1}] !",Thread.CurrentThread.ManagedThreadId,Index));
			}
			catch(AggregateException E)
			{
				Console.WriteLine(string.Format("THREAD: [{0}] - WaitAny() CANCELLED with EXCEPTION [{1}] !",Thread.CurrentThread.ManagedThreadId,E));
			}

			Console.WriteLine(string.Format("THREAD: [{0}] - WaitAll() CALLED !",Thread.CurrentThread.ManagedThreadId));

			try
			{
				Task.WaitAll(new Task[]{Task1,Task2});

				Console.WriteLine(string.Format("THREAD: [{0}] - WaitAll() FINISHED !",Thread.CurrentThread.ManagedThreadId));
			}
			catch(AggregateException E)
			{
				Console.WriteLine(string.Format("THREAD: [{0}] - WaitAny() CANCELLED with EXCEPTION [{1}] !",Thread.CurrentThread.ManagedThreadId,E));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test26()
		{
			// Po 2 SEKUNDACH bude automaticky CANCELLED.
			CancellationTokenSource								CTS=new CancellationTokenSource(1000);
			Task												Task1=new Task(WaitTask,2000);
			Task												Task2=new Task(WaitTask,3000);
		
			Task1.Start();
			Task2.Start();

			Console.WriteLine(string.Format("THREAD: [{0}] - WaitAny() CALLED !",Thread.CurrentThread.ManagedThreadId));

			try
			{
				int												Index=Task.WaitAny(new Task[]{Task1,Task2},1000,CTS.Token);

				Console.WriteLine(string.Format("THREAD: [{0}] - WaitAny() FINISHED with RESULT [{1}] !",Thread.CurrentThread.ManagedThreadId,Index));
			}
			catch(OperationCanceledException E)
			{
				Console.WriteLine(string.Format("THREAD: [{0}] - WaitAny() CANCELLED with EXCEPTION [{1}] !",Thread.CurrentThread.ManagedThreadId,E));
			}

			Console.WriteLine(string.Format("THREAD: [{0}] - WaitAll() CALLED !",Thread.CurrentThread.ManagedThreadId));

			try
			{
				Task.WaitAll(new Task[]{Task1,Task2},CTS.Token);

				Console.WriteLine(string.Format("THREAD: [{0}] - WaitAll() FINISHED !",Thread.CurrentThread.ManagedThreadId));
			}
			catch(OperationCanceledException E)
			{
				Console.WriteLine(string.Format("THREAD: [{0}] - WaitAny() CANCELLED with EXCEPTION [{1}] !",Thread.CurrentThread.ManagedThreadId,E));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test27()
		{
			// Vytvorim CancellationTokenSource, aby som mohol TASK CANCELED.
			CancellationTokenSource								CTS=new CancellationTokenSource();

			// Do TASK predam CancellationTokenSource.
			Task<int>											SomeTask=new Task<int>(SumTaskWithCancellation,CTS.Token,CTS.Token);

			Console.WriteLine(string.Format("THREAD: [{0}] - New TASK CREATED !",Thread.CurrentThread.ManagedThreadId));

			SomeTask.Start();

			Console.WriteLine(string.Format("THREAD: [{0}] - New TASK STARTED and WAITING for CANCELLATION !",Thread.CurrentThread.ManagedThreadId));

			Thread.Sleep(1000);

			// Poziadam o vykonanie CANCEL.
			CTS.Cancel();
			Console.WriteLine(string.Format("THREAD: [{0}] - TASK STARTED was CANCELED !",Thread.CurrentThread.ManagedThreadId));

			try
			{
				// Pockam kym TASK NESKONCI.
				SomeTask.Wait();
			}
			catch(AggregateException AE1)
			{
				try
				{
					// !!! Skontrolujem ci TASK bol CANCELLED, alebo hodil EXCEPPTION.
					// !!!!! TASK skoncil v CANCELLED STATE, ak AggregateException obsahuje IBA EXCEPTIONS typu OperationCanceledException.
					AE1.Handle(P => (P is OperationCanceledException)==true);

					Console.WriteLine(string.Format("THREAD: [{0}] - TASK was CANCELLED - EXCEPTION: [{1}] !",Thread.CurrentThread.ManagedThreadId,AE1.InnerExceptions[0].Message));
				}
				catch(AggregateException AE2)
				{
					Console.WriteLine(string.Format("THREAD: [{0}] - TASK finished with EXCEPTION: [{1}] !",Thread.CurrentThread.ManagedThreadId,AE2));
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test28()
		{
			Task<int>											Task1=new Task<int>(SumTask,null);

			Console.WriteLine(string.Format("THREAD: [{0}] - New TASK CREATED !",Thread.CurrentThread.ManagedThreadId));

			// Vytvorim dalsie 2 TASKS, ktore sa PARALELNE SPUSTIA, ked skonci Task1.
			Task												Task2=Task1.ContinueWith(Print1ResultTask);
			Task												Task3=Task1.ContinueWith(Print2ResultTask);

			Console.WriteLine(string.Format("THREAD: [{0}] - New TASK STARTED !",Thread.CurrentThread.ManagedThreadId));

			Task1.Start();

			// Pockam kym vsetky TASKS skoncia.
			Task.WaitAll(Task1,Task2,Task3);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test29()
		{
			Task<int>											Task1=new Task<int>(SumTask,null);

			Console.WriteLine(string.Format("THREAD: [{0}] - New TASK CREATED !",Thread.CurrentThread.ManagedThreadId));

			// Vytvorim dalsie 2 TASKS, ktore sa PARALELNE SPUSTIA, ked skonci Task1.
			Task												Task2=Task1.ContinueWith(Print1ResultTask,TaskContinuationOptions.AttachedToParent);
			Task												Task3=Task1.ContinueWith(Print2ResultTask,TaskContinuationOptions.AttachedToParent);

			Console.WriteLine(string.Format("THREAD: [{0}] - New TASK STARTED !",Thread.CurrentThread.ManagedThreadId));

			Task1.Start();

			// Pockam kym vsetky TASKS skoncia.
			Task.WaitAll(Task1,Task2,Task3);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test30()
		{
			Task<int>											Task1=new Task<int>(SumTask,null);

			Console.WriteLine(string.Format("THREAD: [{0}] - New TASK CREATED !",Thread.CurrentThread.ManagedThreadId));

			// Tento task sa spusti iba ak operacia prebehne korektne.
			Task												Task2=Task1.ContinueWith(PrintResultOnCompletedTask,TaskContinuationOptions.OnlyOnRanToCompletion);
			// Tento task sa spusti iba ak operacia hodi EXCEPTION.
			Task												Task3=Task1.ContinueWith(PrintResultOnFailedTask,TaskContinuationOptions.OnlyOnFaulted);
			// Tento task sa spusti iba ak operacia bude CANCELED.
			Task												Task4=Task1.ContinueWith(PrintResultOnCancellationTask,TaskContinuationOptions.OnlyOnCanceled);

			Console.WriteLine(string.Format("THREAD: [{0}] - New TASK STARTED !",Thread.CurrentThread.ManagedThreadId));

			// TASK skonci KOREKTNE.
			Task1.Start();

			try
			{
				// Pockam kym vsetky TASKS skoncia.
				// !!!!! CONTINUATION TASKS (OnlyOnFaulted, OnlyOnCanceled), ktore NEBOLI VYKONANE SU AUTOMATICKY CANCELED cez HODENIE EXCEPTION OperationCanceledException.
				// !!!!! Preto i volanie tejto metody skonci hodenim AggregateException obsahujuce 2 OperationCanceledException.
				Task.WaitAll(Task1,Task2,Task3,Task4);
			}
			catch(AggregateException AE)
			{
				PrintAggregateException(AE);
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test31()
		{
			// Vytvorim CancellationTokenSource, aby som mohol TASK CANCELED.
			CancellationTokenSource								CTS=new CancellationTokenSource();

			Task<int>											Task1=new Task<int>(SumTaskWithCancellation,CTS.Token,CTS.Token);

			Console.WriteLine(string.Format("THREAD: [{0}] - New TASK CREATED !",Thread.CurrentThread.ManagedThreadId));

			// Tento task sa spusti iba ak operacia prebehne korektne.
			Task												Task2=Task1.ContinueWith(PrintResultOnCompletedTask,TaskContinuationOptions.OnlyOnRanToCompletion);
			// Tento task sa spusti iba ak operacia hodi EXCEPTION.
			Task												Task3=Task1.ContinueWith(PrintResultOnFailedTask,TaskContinuationOptions.OnlyOnFaulted);
			// Tento task sa spusti iba ak operacia bude CANCELED.
			Task												Task4=Task1.ContinueWith(PrintResultOnCancellationTask,TaskContinuationOptions.OnlyOnCanceled);

			Console.WriteLine(string.Format("THREAD: [{0}] - New TASK STARTED !",Thread.CurrentThread.ManagedThreadId));

			// TASK skonci cez CANCELLATION.
			Task1.Start();

			Thread.Sleep(1000);

			// Poziadam o vykonanie CANCEL.
			CTS.Cancel();
			Console.WriteLine(string.Format("THREAD: [{0}] - TASK was CANCELED !",Thread.CurrentThread.ManagedThreadId));

			try
			{
				// Pockam kym vsetky TASKS skoncia.
				// !!!!! CONTINUATION TASKS (OnlyOnRanToCompletion, OnlyOnFaulted), ktore NEBOLI VYKONANE SU AUTOMATICKY CANCELED cez HODENIE EXCEPTION OperationCanceledException.
				// !!! EXCEPTION hodi aj Task1, ktory bol CANCELLED.
				// !!!!! Preto i volanie tejto metody skonci hodenim AggregateException obsahujuce 3 OperationCanceledException.
				Task.WaitAll(Task1,Task2,Task3,Task4);
			}
			catch(AggregateException AE)
			{
				PrintAggregateException(AE);
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test32()
		{
			Task<int>											Task1=new Task<int>(SumTaskWithException,null);

			Console.WriteLine(string.Format("THREAD: [{0}] - New TASK CREATED !",Thread.CurrentThread.ManagedThreadId));

			// Tento task sa spusti iba ak operacia prebehne korektne.
			Task												Task2=Task1.ContinueWith(PrintResultOnCompletedTask,TaskContinuationOptions.OnlyOnRanToCompletion);
			// Tento task sa spusti iba ak operacia hodi EXCEPTION.
			Task												Task3=Task1.ContinueWith(PrintResultOnFailedTask,TaskContinuationOptions.OnlyOnFaulted);
			// Tento task sa spusti iba ak operacia bude CANCELED.
			Task												Task4=Task1.ContinueWith(PrintResultOnCancellationTask,TaskContinuationOptions.OnlyOnCanceled);

			Console.WriteLine(string.Format("THREAD: [{0}] - New TASK STARTED !",Thread.CurrentThread.ManagedThreadId));

			// TASK skonci HODENIM EXCEPTION.
			Task1.Start();

			try
			{
				// Pockam kym vsetky TASKS skoncia.
				// !!!!! CONTINUATION TASKS (OnlyOnRanToCompletion, OnlyOnCanceled), ktore NEBOLI VYKONANE SU AUTOMATICKY CANCELED cez HODENIE EXCEPTION OperationCanceledException.
				// !!! EXCEPTION hodi aj Task1, ktory skoncil EXCEPTION.
				// !!!!! Preto i volanie tejto metody skonci hodenim AggregateException obsahujuce 2 OperationCanceledException a jednej EXCEPTION, ktora bola hodena v Task1.
				Task.WaitAll(Task1,Task2,Task3,Task4);
			}
			catch(AggregateException AE)
			{
				PrintAggregateException(AE);
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test33()
		{
			CancellationTokenSource								CTS=new CancellationTokenSource();
		
			try
			{
				// !!!!! NEPLATI. V knihe sa pise, ze bez zavolania Task.Start() sa vykona CANCELLATION. Toto vsak NEPLATI a TASK sa KOREKTNE SPUSTI.
				CTS.Cancel();

				Console.WriteLine(string.Format("THREAD: [{0}] - TASK was CANCELLED !",Thread.CurrentThread.ManagedThreadId));

				Task<int>										Task=new Task<int>(SumTaskWithCancellation,CTS.Token);

				Console.WriteLine(string.Format("THREAD: [{0}] - TASK CREATED !",Thread.CurrentThread.ManagedThreadId));

				Task.Start();

				Console.WriteLine(string.Format("THREAD: [{0}] - TASK was STARTED !",Thread.CurrentThread.ManagedThreadId));

				Task.Wait();

				Console.WriteLine(string.Format("THREAD: [{0}] - TASK FINISHED !",Thread.CurrentThread.ManagedThreadId));
			}
			catch(AggregateException E)
			{
				Console.WriteLine(string.Format("THREAD: [{0}] - EXCEPTION [{1}] !",Thread.CurrentThread.ManagedThreadId,E));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test34()
		{
			// Vytvorim PARENT TASK, ktory SPUSTI 3 CHILD TASKS.
			Task<int[]>											ParentTask=new Task<int[]>(SumParentTask,null);

			Console.WriteLine(string.Format("THREAD: [{0}] - PARENT TASK CREATED !",Thread.CurrentThread.ManagedThreadId));

			ParentTask.Start();

			Console.WriteLine(string.Format("THREAD: [{0}] - PARENT TASK STARTED !",Thread.CurrentThread.ManagedThreadId));

			// !!!!! PARENT TASK skonci az ked skoncia VSETKY CHILD TASKS.
			ParentTask.Wait();

			int[]												Results=ParentTask.Result;

			Console.WriteLine(string.Format("THREAD: [{0}] - CHILD TASK 1 RESULT: [{1}] !",Thread.CurrentThread.ManagedThreadId,Results[0]));
			Console.WriteLine(string.Format("THREAD: [{0}] - CHILD TASK 2 RESULT: [{1}] !",Thread.CurrentThread.ManagedThreadId,Results[1]));
			Console.WriteLine(string.Format("THREAD: [{0}] - CHILD TASK 3 RESULT: [{1}] !",Thread.CurrentThread.ManagedThreadId,Results[2]));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test35()
		{
			// !!!!! UMYSELNE ZABRANIM VYTVARANIU CHILD TASKS.
			Task<int[]>											ParentTask=new Task<int[]>(SumParentTaskDeny,null,TaskCreationOptions.DenyChildAttach);

			Console.WriteLine(string.Format("THREAD: [{0}] - PARENT TASK CREATED !",Thread.CurrentThread.ManagedThreadId));

			ParentTask.Start();

			Console.WriteLine(string.Format("THREAD: [{0}] - PARENT TASK STARTED !",Thread.CurrentThread.ManagedThreadId));

			// !!!!! Kedze PARENT TASK ma ZABLOKOVANU moznost vytvarania CHILD TASKS, CHILD TASKS budu spustene ako NON-CHILD TASKS a VAZBA medzi PARENT a CHILD NEBUDE EXISTOVAT. To znaci, ze 'PARENT' a 'CHILD' TASKS budu NEZAVISLE a ParentTask.Wait() skonci OKAMZITE po skonceni PARENT TASK, NECAKAJUC na skoncenie CHILD TASKS.
			ParentTask.Wait();

			int[]												Results=ParentTask.Result;

			Console.WriteLine(string.Format("THREAD: [{0}] - CHILD TASK 1 RESULT: [{1}] !",Thread.CurrentThread.ManagedThreadId,Results[0]));
			Console.WriteLine(string.Format("THREAD: [{0}] - CHILD TASK 2 RESULT: [{1}] !",Thread.CurrentThread.ManagedThreadId,Results[1]));
			Console.WriteLine(string.Format("THREAD: [{0}] - CHILD TASK 3 RESULT: [{1}] !",Thread.CurrentThread.ManagedThreadId,Results[2]));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test36()
		{
			Task												Task1=new Task(() => {Console.WriteLine(string.Format("TASK [{0}] !",Task.CurrentId));});
			Task												Task2=new Task(() => {Console.WriteLine(string.Format("TASK [{0}] !",Task.CurrentId));});
			Task												Task3=new Task(() => {Console.WriteLine(string.Format("TASK [{0}] !",Task.CurrentId));});

			// !!! ID sa vytvara AZ pri PRVOM pristupe a tak jeho HODNOTA ZAVISI od PORADIA, ktore ID som ako prve ZOBRAZIL.
			// ID je implementovane ako COUNTER.
			Console.WriteLine(string.Format("Task2.Id: [{0}] !",Task2.Id));
			Console.WriteLine(string.Format("Task3.Id: [{0}] !",Task3.Id));
			Console.WriteLine(string.Format("Task1.Id: [{0}] !",Task1.Id));

			Task1.Start();
			Task2.Start();
			Task3.Start();

			Task.WaitAll(Task1,Task2,Task3);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test37()
		{
			Task<int>											SomeTask=new Task<int>(SumTask,null);

			Console.WriteLine(string.Format("THREAD: [{0}] - New TASK CREATED, Status: [{1}] !",Thread.CurrentThread.ManagedThreadId,SomeTask.Status));

			SomeTask.Start();

			Console.WriteLine(string.Format("THREAD: [{0}] - New TASK STARTED and WAITING for FINISH, Status: [{1}] !",Thread.CurrentThread.ManagedThreadId,SomeTask.Status));

			// Pockam kym TASK NESKONCI.
			SomeTask.Wait();

			int													Result=SomeTask.Result;
			
			Console.WriteLine(string.Format("THREAD: [{0}] - TASK FINISHED with RESULT: [{1}], Status: [{2}] !",Thread.CurrentThread.ManagedThreadId,Result,SomeTask.Status));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test38()
		{
			// EMULUJEM TASK.
			TaskCompletionSource<string>						TCS=new TaskCompletionSource<string>();

			// Nastavim vysledok TASKU.
			TCS.SetResult("Timmy Anderson");

			Task<string>										EmulatedTask=TCS.Task;

			Action<Task<string>>								ContinuationTaskAction=(CompletedTask) =>
			{
				Console.WriteLine(string.Format("SIMULATED TASK - RESULT: [{0}] !",CompletedTask.Result));
			};
			
			EmulatedTask.ContinueWith(ContinuationTaskAction);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test39()
		{
			// EMULUJEM TASK.
			TaskCompletionSource<string>						TCS=new TaskCompletionSource<string>();

			// !!! Emulujem, ze TASK skoncil EXCEPTION.
			TCS.SetException(new Exception("Some SERIOUS BUG !!!"));

			Task<string>										EmulatedTask=TCS.Task;

			Action<Task<string>>								ContinuationTaskAction=(CompletedTask) =>
			{
				try
				{
					Console.WriteLine(string.Format("TASK RESULT: [{0}] !",CompletedTask.Result));
				}
				catch(Exception E)
				{
					Console.WriteLine(string.Format("SIMULATED TASK - EXCEPTION: [{0}] !",E));
				}
			};
			
			EmulatedTask.ContinueWith(ContinuationTaskAction);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test40()
		{
			// Vytvorim CancellationTokenSource, aby som mohol TASK CANCELED.
			CancellationTokenSource								CTS=new CancellationTokenSource();

			// !!! Vytvorim TaskFactory s DEFAULT TASK SCHEDULER.
			TaskFactory<int>									TF=new TaskFactory<int>(CTS.Token,TaskCreationOptions.PreferFairness,TaskContinuationOptions.None,TaskScheduler.Default);

			// Vytvorim niekolko TASKS.
			Task<int>											Task1=TF.StartNew(SumTaskWithCancellation,CTS.Token,CTS.Token);
			Task<int>											Task2=TF.StartNew(SumTaskWithCancellation,CTS.Token,CTS.Token);
			Task<int>											Task3=TF.StartNew(SumTaskWithCancellation,CTS.Token,CTS.Token);

			Console.WriteLine(string.Format("THREAD: [{0}] - TASKS CREATED AND STARTED !",Thread.CurrentThread.ManagedThreadId));

			Task<int>											SumTask=TF.ContinueWhenAll(new Task<int>[]{Task1,Task2,Task3},P => P.Select(R => R.Result).Sum());

			SumTask.Wait();

			Console.WriteLine(string.Format("THREAD: [{0}] - SumTask.Result: [{1}] !",Thread.CurrentThread.ManagedThreadId,SumTask.Result));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test41()
		{
			int													WorkerThreads;
			int													CompletionPortThreads;
			int													MinWorkerThreads;
			int													MinCompletionPortThreads;
			int													MaxWorkerThreads;
			int													MaxCompletionPortThreads;

			ThreadPool.GetAvailableThreads(out WorkerThreads, out CompletionPortThreads);
			ThreadPool.GetMinThreads(out MinWorkerThreads, out MinCompletionPortThreads);
			ThreadPool.GetMaxThreads(out MaxWorkerThreads, out MaxCompletionPortThreads);
			
			Console.WriteLine(string.Format("WorkerThreads: [{0}] !",WorkerThreads));
			Console.WriteLine(string.Format("CompletionPortThreads: [{0}] !",CompletionPortThreads));
			Console.WriteLine(string.Format("MinWorkerThreads: [{0}] !",MinWorkerThreads));
			Console.WriteLine(string.Format("MinCompletionPortThreads: [{0}] !",MinCompletionPortThreads));
			Console.WriteLine(string.Format("MaxWorkerThreads: [{0}] !",MaxWorkerThreads));
			Console.WriteLine(string.Format("MaxCompletionPortThreads: [{0}] !",MaxCompletionPortThreads));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test42()
		{
			DateTime											StartTime=DateTime.Now;
			Task[]												Tasks=new Task[1000];

			for(int Index=0;Index<Tasks.Length;Index++)
			{
				Tasks[Index]=new Task(Wait1Second);
				Tasks[Index].Start();
			}

			Task.WaitAll(Tasks);

			TimeSpan											TimeDifference=DateTime.Now-StartTime;

			// Spracovanie trvalo 50-80 sekund.
			Console.WriteLine(string.Format("TIME DIFFERENCE [{0}] !",TimeDifference.TotalSeconds));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test43()
		{
			DateTime											StartTime=DateTime.Now;
			Task[]												Tasks=new Task[1000];

			// Nastavim vysoky pocet THREADS.
			ThreadPool.SetMinThreads(1000,1000);

			for(int Index=0;Index<Tasks.Length;Index++)
			{
				Tasks[Index]=new Task(Wait1Second);
				Tasks[Index].Start();
			}

			Task.WaitAll(Tasks);

			TimeSpan											TimeDifference=DateTime.Now-StartTime;

			// Spracovanie trvalo 3-4 sekundy.
			Console.WriteLine(string.Format("TIME DIFFERENCE [{0}] !",TimeDifference.TotalSeconds));
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
			//Test8();
			//Test9();
			//Test10();
			//Test11();
			//Test12();
			//Test13();
			//Test14();
			//Test15();
			//Test16();
			//Test17();
			//Test18();
			//Test19();
			//Test20();
			//Test21();
			//Test22();
			//Test23();
			//Test24();
			//Test25();
			//Test26();
			//Test27();
			//Test28();
			//Test29();
			//Test30();
			//Test31();
			//Test32();
			//Test33();
			//Test34();
			//Test35();
			//Test36();
			//Test37();
			//Test38();
			//Test39();
			//Test40();
			//Test41();
			//Test42();
			Test43();

			Console.WriteLine("\nPress any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------