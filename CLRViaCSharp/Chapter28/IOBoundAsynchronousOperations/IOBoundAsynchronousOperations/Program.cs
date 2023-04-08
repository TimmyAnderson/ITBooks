using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.IO;
using System.Net;
using System.Threading.Tasks;
using System.ComponentModel;
//-------------------------------------------------------------------------------------------------------
namespace IOBoundAsynchronousOperations
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void UnhandledExceptionHandler(object Sender, UnhandledExceptionEventArgs E)
		{
			Console.WriteLine(string.Format("UNHANDLED EXCEPTION [{0}] THROWN !",E.ExceptionObject));

			Console.WriteLine("\nPress any key to CONTINUE !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private static string LoadTestAction(object Param)
		{
			int													Counter=(int) Param;

			Thread.Sleep(1000);

			Console.WriteLine(string.Format("ACTION [{0}] was PROCESSED !",Counter));

			return(Counter.ToString());
		}
//-------------------------------------------------------------------------------------------------------
		private static async void LoadTest()
		{
			Console.WriteLine("!!!!! LOAD TEST STARTED !");

			List<Task<string>>									Tasks=new List<Task<string>>();

			// Spusti sa 1000 TASKS.
			for(int Index=0;Index<1000;Index++)
			{
				Task<string>									NewTask=new Task<string>(LoadTestAction,Index+1);

				Tasks.Add(NewTask);

				NewTask.Start();
			}

			// !!! Emulacia spracovania vysledkov.
			while(true)
			{
				if (Tasks.Count==0)
				{
					break;
				}

				// !!! Vytvori novy TASK, ktory sa spusti, ak niektory z TASKS bol ukonceny.
				Task<Task<string>>								CompletionTask=Task.WhenAny(Tasks);

				// !!!!! OPERATOR AWAIT caka na skoncenie TASK, ktory sa spusti, ak niektory z TASKS bol ukonceny.
				Task<string>									CompletedTask=await CompletionTask;

				Console.WriteLine(string.Format("RESULTS from ACTION [{0}] was PROCESSED !",CompletedTask.Result));

				// !!! TASK sa odstrani z COLLECTION.
				Tasks.Remove(CompletedTask);
			}

			Console.WriteLine("!!!!! LOAD TEST FINISHED !");
		}
//-------------------------------------------------------------------------------------------------------
		private static async Task TestException1()
		{
			Console.WriteLine("TestException1() EXECUTING !");

			Task												SomeTask=new Task(ExceptionAction);

			SomeTask.Start();

			// !!! Sposobi hodenie EXCEPTION.
			await SomeTask;

			// !!! Tu sa uz program NIKDY NEDOSTANE.
			Console.WriteLine("TestException1() FINISHED !");
		}
//-------------------------------------------------------------------------------------------------------
		private static async Task TestException2()
		{
			Console.WriteLine("TestException2() EXECUTING !");

			Task												SomeTask=new Task(ExceptionAction);

			SomeTask.Start();

			try
			{
				// !!! Sposobi hodenie EXCEPTION.
				await SomeTask;
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION [{0}] OCCURED while AWAITING !",E.Message));
			}

			Console.WriteLine("TestException2() FINISHED !");
		}
//-------------------------------------------------------------------------------------------------------
		// !!! ASYNCHRONOUS FUNCTION, ktora NEMA RETURN VALUE.
		// !!!!! Kedze ASYNCHRONOUS FUNCTION NEMA RETURN VALUE, ani SYNCHRONIZATION CONTEXT, tak EXCEPTION je RETHROWN v TASKU, co sposobi PAD PROGRAMU.
		private static async void TestException3()
		{
			Console.WriteLine("TestException3() EXECUTING !");

			Task												SomeTask=new Task(ExceptionAction);

			SomeTask.Start();

			// !!! Sposobi hodenie EXCEPTION.
			await SomeTask;

			// !!! Tu sa uz program NIKDY NEDOSTANE.
			Console.WriteLine("TestException3() FINISHED !");
		}
//-------------------------------------------------------------------------------------------------------
		private static void ExceptionAction()
		{
			Console.WriteLine("ExceptionAction() EXECUTING !");

			Thread.Sleep(2000);

			Console.WriteLine("ExceptionAction() will THROW EXCEPTION !");

			throw(new Exception("This is SOME EXCEPTION !"));
		}
//-------------------------------------------------------------------------------------------------------
		private static async Task<string> ReadFileWithAsynchronousFunction1()
		{
			// !!!!! Kedze som zadal FileOptions.Asynchronous, tak CLR vykonavat VSETKY OPERACIE ASYNCHRONNE OPERACIE.
			using(FileStream FS=new FileStream(@"Files\SomeFile.txt",FileMode.Open,FileAccess.Read,FileShare.Read,1024,FileOptions.Asynchronous))
			{
				byte[]											Buffer=new byte[FS.Length];

				Console.WriteLine(string.Format("THREAD: [{0}] - BEFORE OPERATION STARTED !",Thread.CurrentThread.ManagedThreadId));

				// !!!!! Kedze FileStream.BeginRead() ma aj INE PARAMETERS ako AsyncCallback a Object, tak BeginRead() MUSIM volat MANUALNE.
				IAsyncResult									AR=FS.BeginRead(Buffer,0,Buffer.Length,null,null);

				Func<IAsyncResult,int>							EndMethod=FS.EndRead;

				await Task.Factory.FromAsync(AR,EndMethod,TaskCreationOptions.None);

				Console.WriteLine(string.Format("THREAD: [{0}] - AFTER OPERATION COMPLETED !",Thread.CurrentThread.ManagedThreadId));

				string											Result=Encoding.UTF8.GetString(Buffer);

				return(Result);
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static async Task<string> ReadFileWithAsynchronousFunction2()
		{
			// !!!!! Kedze som zadal FileOptions.Asynchronous, tak CLR vykonavat VSETKY OPERACIE ASYNCHRONNE OPERACIE.
			using(FileStream FS=new FileStream(@"Files\SomeFile.txt",FileMode.Open,FileAccess.Read,FileShare.Read,1024,FileOptions.Asynchronous))
			{
				byte[]											Buffer=new byte[FS.Length];

				Console.WriteLine(string.Format("THREAD: [{0}] - BEFORE OPERATION STARTED !",Thread.CurrentThread.ManagedThreadId));

				// !!!!! Alternativne pouzitie GENERICS verzie Task.Factory.FromAsync().
				// Prve 3 GENERICS PARAMETERS udavaju PARAMETERS FileStream.BeginRead().
				// Posledny 4. GENERICS PARAMETER udava RETURN VALUE FileStream.EndRead().
				await Task.Factory.FromAsync<byte[],int,int,int>(FS.BeginRead,FS.EndRead,Buffer,0,Buffer.Length,null);

				Console.WriteLine(string.Format("THREAD: [{0}] - AFTER OPERATION COMPLETED !",Thread.CurrentThread.ManagedThreadId));

				string											Result=Encoding.UTF8.GetString(Buffer);

				return(Result);
			}
		}
//-------------------------------------------------------------------------------------------------------
		// !!! ASYNCHRONOUS FUNCTION, ktora NEMA RETURN VALUE.
		// !!!!! Kedze FUNCTION nevracia TASK ako RETURN VALUE, tak na zistenie ukoncenia ASYNCHROUNOUS FUNCTION sa pouziva PARAMETER typu ManualResetEvent.
		private static async void VoidReturnAsynchronousFunction(ManualResetEvent Event)
		{
			Console.WriteLine(string.Format("THREAD: [{0}] - MAIN - BEFORE 'AWAIT' OPERATOR CALLED !",Thread.CurrentThread.ManagedThreadId));

			Task												AsynchronousTask=new Task(SomeAction);
			
			AsynchronousTask.Start();

			await AsynchronousTask;

			Console.WriteLine(string.Format("THREAD: [{0}] - MAIN - AFTER 'AWAIT' OPERATOR CALLED !",Thread.CurrentThread.ManagedThreadId));

			// !!! Signalizuje sa ukoncenie ASYNCHRONOUS FUNCTION.
			Event.Set();
		}
//-------------------------------------------------------------------------------------------------------
		private static Task TestMultiTask()
		{
			Task												Task1=new Task(Action1);
			Task												Task2=new Task(Action2);

			Task1.Start();
			Task2.Start();

			// !!! Tento TASK sa zavola, ak skoncia obe TASKS.
			Task												CallWhenBothTaskFinished=Task.WhenAll(Task1,Task2);

			return(CallWhenBothTaskFinished);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Action1()
		{
			Console.WriteLine(string.Format("THREAD: [{0}] - Action1() STARTED !",Thread.CurrentThread.ManagedThreadId));

			Thread.Sleep(1000);

			Console.WriteLine(string.Format("THREAD: [{0}] - Action1() FINISHED !",Thread.CurrentThread.ManagedThreadId));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Action2()
		{
			Console.WriteLine(string.Format("THREAD: [{0}] - Action2() STARTED !",Thread.CurrentThread.ManagedThreadId));

			Thread.Sleep(1000);

			Console.WriteLine(string.Format("THREAD: [{0}] - Action2() FINISHED !",Thread.CurrentThread.ManagedThreadId));
		}
//-------------------------------------------------------------------------------------------------------
		// !!! ASYNCHRONOUS FUNCTION MUSI vraciat Task<RETURN_VALUE>, kde RETURN_VALUE je TYPE RETURN VALUE, ktoru ASYNCHRONOUS FUNCTION vracia.
		private static Task RunAction1()
		{
			Task												NewTask=new Task(Action1);

			// !!! Vrateny TASK MUSI byt NASTARTOVANY. METHOD GetAwaiter() ho automaticky NESPUSTA.
			NewTask.Start();

			return(NewTask);
		}
//-------------------------------------------------------------------------------------------------------
		// !!! ASYNCHRONOUS FUNCTION MUSI vraciat Task<RETURN_VALUE>, kde RETURN_VALUE je TYPE RETURN VALUE, ktoru ASYNCHRONOUS FUNCTION vracia.
		private static Task RunAction2()
		{
			Task												NewTask=new Task(Action2);

			// !!! Vrateny TASK MUSI byt NASTARTOVANY. METHOD GetAwaiter() ho automaticky NESPUSTA.
			NewTask.Start();

			return(NewTask);
		}
//-------------------------------------------------------------------------------------------------------
		private static int RunActionReturnsInt()
		{
			Console.WriteLine(string.Format("THREAD: [{0}] - RunActionReturnsInt() EXECUTED !",Thread.CurrentThread.ManagedThreadId));

			return(100);
		}
//-------------------------------------------------------------------------------------------------------
		private static void RunActionReturnsVoid()
		{
			Console.WriteLine(string.Format("THREAD: [{0}] - RunActionReturnsVoid() EXECUTED !",Thread.CurrentThread.ManagedThreadId));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// !!! ASYNCHRONOUS FUNCTION MUSI vraciat Task<RETURN_VALUE>, kde RETURN_VALUE je TYPE RETURN VALUE, ktoru ASYNCHRONOUS FUNCTION vracia.
		private async static Task<string> CustomAsynchronousFunction1()
		{
			Console.WriteLine(string.Format("THREAD: [{0}] - CustomAsynchronousFunction1() STARTED !",Thread.CurrentThread.ManagedThreadId));

			// !!!!! Kedze Task implementuje GetAwaiter() je ho mozne pouzit ako OPERAND OPERATORA 'await'.
			await RunAction1();

			Console.WriteLine(string.Format("THREAD: [{0}] - CustomAsynchronousFunction1() BETWEEN AWAITS !",Thread.CurrentThread.ManagedThreadId));

			// !!!!! Kedze Task implementuje GetAwaiter() je ho mozne pouzit ako OPERAND OPERATORA 'await'.
			await RunAction2();

			Console.WriteLine(string.Format("THREAD: [{0}] - CustomAsynchronousFunction1() FINISHED !",Thread.CurrentThread.ManagedThreadId));

			return("My name is TIMMY !!!");
		}
//-------------------------------------------------------------------------------------------------------
		// !!! ASYNCHRONOUS FUNCTION MUSI vraciat Task<RETURN_VALUE>, kde RETURN_VALUE je TYPE RETURN VALUE, ktoru ASYNCHRONOUS FUNCTION vracia.
		private async static Task<string> CustomAsynchronousFunction2()
		{
			Console.WriteLine(string.Format("THREAD: [{0}] - CustomAsynchronousFunction3() STARTED !",Thread.CurrentThread.ManagedThreadId));

			Task												Task1=new Task(Action1);

			// !!! Vrateny TASK MUSI byt NASTARTOVANY. METHOD GetAwaiter() ho automaticky NESPUSTA.
			Task1.Start();

			// !!!!! Kedze Task implementuje GetAwaiter() je ho mozne pouzit ako OPERAND OPERATORA 'await'.
			await Task1;

			Console.WriteLine(string.Format("THREAD: [{0}] - CustomAsynchronousFunction3() BETWEEN AWAITS !",Thread.CurrentThread.ManagedThreadId));

			Task												Task2=new Task(Action2);

			// !!! Vrateny TASK MUSI byt NASTARTOVANY. METHOD GetAwaiter() ho automaticky NESPUSTA.
			Task2.Start();

			// !!!!! Kedze Task implementuje GetAwaiter() je ho mozne pouzit ako OPERAND OPERATORA 'await'.
			await Task2;

			Console.WriteLine(string.Format("THREAD: [{0}] - CustomAsynchronousFunction3() FINISHED !",Thread.CurrentThread.ManagedThreadId));

			return("My name is TIMMY !!!");
		}
//-------------------------------------------------------------------------------------------------------
		/*
		// !!! ASYNCHRONOUS FUNCTION MUSI vraciat Task<RETURN_VALUE>, kde RETURN_VALUE je TYPE RETURN VALUE, ktoru ASYNCHRONOUS FUNCTION vracia.
		private async static Task<string> CustomAsynchronousFunction3()
		{
			Console.WriteLine(string.Format("THREAD: [{0}] - CustomAsynchronousFunction2() STARTED !",Thread.CurrentThread.ManagedThreadId));

			// !!!!! Kedze METHOD vracia INT pre ktory NIE JE MOZNE volat GetAwaiter(), COMPILER hodi ERROR.
			await RunActionReturnsInt();

			Console.WriteLine(string.Format("THREAD: [{0}] - CustomAsynchronousFunction2() BETWEEN AWAITS !",Thread.CurrentThread.ManagedThreadId));

			// !!!!! Kedze METHOD vracia VOID pre ktory NIE JE MOZNE volat GetAwaiter(), COMPILER hodi ERROR.
			await RunActionReturnsVoid();

			Console.WriteLine(string.Format("THREAD: [{0}] - CustomAsynchronousFunction2() FINISHED !",Thread.CurrentThread.ManagedThreadId));

			return("My name is TIMMY !!!");
		}
		*/
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// !!! ASYNCHRONOUS FUNCTION MUSI vraciat Task<RETURN_VALUE>, kde RETURN_VALUE je TYPE RETURN VALUE, ktoru ASYNCHRONOUS FUNCTION vracia.
		private async static Task<string> MyAsynchronousFunction()
		{
			string												Result="";

			// !!!!! CODE sa vykonava v THREADE, ktory ZAVOLAL MyAsynchronousFunction().
			Console.WriteLine(string.Format("THREAD: [{0}] - MyAsynchronousFunction() STARTED !",Thread.CurrentThread.ManagedThreadId));

			using(FileStream FS=new FileStream(@"Files\SomeFile.txt",FileMode.Open))
			{
				int												Length=(int) FS.Length;
				byte[]											Buffer=new byte[Length];

				Console.WriteLine(string.Format("THREAD: [{0}] - BEFORE FIRST READ !",Thread.CurrentThread.ManagedThreadId));

				// !!! Nacita prvych 10 BYTES.
				// !!!!! Kedze sa pouzil KEYWORD 'await', tak sa IO OPERATION vykona ASYNCHRONNE.
				await FS.ReadAsync(Buffer,0,10);

				// !!!!! CODE sa vykona v NOVOM TASKU.
				Console.WriteLine(string.Format("THREAD: [{0}] - AFTER FIRST READ !",Thread.CurrentThread.ManagedThreadId));

				Thread.Sleep(1000);
				
				// !!! Nacita prvych 10 BYTES.
				// !!!!! Kedze sa pouzil KEYWORD 'await', tak sa IO OPERATION vykona ASYNCHRONNE.
				Console.WriteLine(string.Format("THREAD: [{0}] - BEFORE SECOND READ !",Thread.CurrentThread.ManagedThreadId));

				await FS.ReadAsync(Buffer,10,Length-10);

				// !!!!! CODE sa vykona v NOVOM TASKU.
				Console.WriteLine(string.Format("THREAD: [{0}] - AFTER SECOND READ !",Thread.CurrentThread.ManagedThreadId));

				Result=Encoding.UTF8.GetString(Buffer);
			}

			Console.WriteLine(string.Format("THREAD: [{0}] - MyAsynchronousFunction() FINISHED !",Thread.CurrentThread.ManagedThreadId));

			return(Result);
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private static void BW_DoWork(object Sender, DoWorkEventArgs E)
		{
			Console.WriteLine(string.Format("THREAD: [{0}] - BW_DoWork() CALLED 1 !",Thread.CurrentThread.ManagedThreadId));

			Thread.Sleep(1000);

			// Nastavim RESULT.
			E.Result="Timmy Anderson";

			Console.WriteLine(string.Format("THREAD: [{0}] - BW_DoWork() CALLED 2 !",Thread.CurrentThread.ManagedThreadId));
		}
//-------------------------------------------------------------------------------------------------------
		private static void BW_RunWorkerCompleted(object Sender, RunWorkerCompletedEventArgs E)
		{
			Console.WriteLine(string.Format("THREAD: [{0}] - BW_RunWorkerCompleted(), Result: [{1}], Error: [{2}], Cancelled: [{3}] !",Thread.CurrentThread.ManagedThreadId,E.Result,E.Error,E.Cancelled));
		}
//-------------------------------------------------------------------------------------------------------
		private static void SomeAction()
		{
			Console.WriteLine(string.Format("THREAD: [{0}] - SomeAction() CALLED 1 !",Thread.CurrentThread.ManagedThreadId));

			Thread.Sleep(1000);

			Console.WriteLine(string.Format("THREAD: [{0}] - SomeAction() CALLED 2 !",Thread.CurrentThread.ManagedThreadId));
		}
//-------------------------------------------------------------------------------------------------------
		private static void CallbackForSomeAction(object Param)
		{
			Console.WriteLine(string.Format("THREAD: [{0}] - CallbackForSomeAction() CALLED 1 !",Thread.CurrentThread.ManagedThreadId));

			Thread.Sleep(1000);

			Console.WriteLine(string.Format("THREAD: [{0}] - CallbackForSomeAction() CALLED 2 !",Thread.CurrentThread.ManagedThreadId));
		}
//-------------------------------------------------------------------------------------------------------
		private static void FileReadCallback1(IAsyncResult AR)
		{
			Console.WriteLine(string.Format("THREAD: [{0}] - STARTED !",Thread.CurrentThread.ManagedThreadId));

			CFileStreamCallbackParams							CallbackParams=(CFileStreamCallbackParams) AR.AsyncState;

			Thread.Sleep(1000);

			// !!!!! Kedze v MAIN THREAD bol FileStream DISPOSED, no IO OPERATION este STALE BEZALA, tak sa DISPOSE ODLOZI az do chvile kym sa NEZAVOLA EndRead().
			// !!!!! CLASS FileStream je pri volani EndRead() DISPOSED.
			CallbackParams.FileStream.EndRead(AR);

			string												DataFromFile=Encoding.UTF8.GetString(CallbackParams.Buffer);

			Console.WriteLine(string.Format("THREAD: [{0}] - FINISHED - DataFromFile: [{1}] !",Thread.CurrentThread.ManagedThreadId,DataFromFile));
		}
//-------------------------------------------------------------------------------------------------------
		private static void FileReadCallback2(IAsyncResult AR)
		{
			Console.WriteLine(string.Format("THREAD: [{0}] - STARTED !",Thread.CurrentThread.ManagedThreadId));

			CFileStreamCallbackParams							CallbackParams=(CFileStreamCallbackParams) AR.AsyncState;

			Thread.Sleep(1000);

			// !!!!! Kedze v MAIN THREAD bol FileStream DISPOSED, no IO OPERATION este STALE BEZALA, tak sa DISPOSE ODLOZI az do chvile kym sa NEZAVOLA EndRead().
			// !!!!! CLASS FileStream je pri volani EndRead() DISPOSED.
			CallbackParams.FileStream.EndRead(AR);

			try
			{
				// !!!!! Pri pokuse o pristup k MEMBER FILE STREAM, ktory pristupuje na FILE dojde k EXCEPTION, pretoze FileStream uz bol DISPOSED.
				long											Length=CallbackParams.FileStream.Length;

				Console.WriteLine(string.Format("THREAD: [{0}] - LENGTH: [{1}] !",Thread.CurrentThread.ManagedThreadId,Length));
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("THREAD: [{0}] - EXCEPTION: [{1}] !",Thread.CurrentThread.ManagedThreadId,E.Message));
			}

			string												DataFromFile=Encoding.UTF8.GetString(CallbackParams.Buffer);

			Console.WriteLine(string.Format("THREAD: [{0}] - FINISHED - DataFromFile: [{1}] !",Thread.CurrentThread.ManagedThreadId,DataFromFile));
		}
//-------------------------------------------------------------------------------------------------------
		private static void FileReadCallback3(IAsyncResult AR)
		{
			Console.WriteLine(string.Format("THREAD: [{0}] - STARTED !",Thread.CurrentThread.ManagedThreadId));

			CFileStreamCallbackParams							CallbackParams=(CFileStreamCallbackParams) AR.AsyncState;

			Thread.Sleep(1000);

			// !!!!! EndRead() sa NESMIE VOLAT, pretoze to AUTOMATICKY spravi TASK.
			//CallbackParams.FileStream.EndRead(AR);

			string												DataFromFile=Encoding.UTF8.GetString(CallbackParams.Buffer);

			Console.WriteLine(string.Format("THREAD: [{0}] - FINISHED - DataFromFile: [{1}] !",Thread.CurrentThread.ManagedThreadId,DataFromFile));
		}
//-------------------------------------------------------------------------------------------------------
		private static void ProcessExceptionWebResponse(IAsyncResult Result)
		{
			WebRequest											WR=(WebRequest) Result.AsyncState;
			WebResponse											WebResponse=null;

			Console.WriteLine(string.Format("ProcessExceptionWebResponse() - STARTED !"));

			try
			{
				WebResponse=WR.EndGetResponse(Result);
				Console.WriteLine(string.Format("ProcessExceptionWebResponse() - Content length: [{0}] !",WebResponse.ContentLength));
			}
			catch(WebException E)
			{
				Console.WriteLine(string.Format("ProcessExceptionWebResponse() - EXCEPTION: [{0}] !",E));
			}
			finally
			{
				if (WebResponse!=null)
				{
					WebResponse.Close();
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private static void Test1()
		{
			// !!!!! Kedze som nezadal FileOptions.Asynchronous, tak CLR bude IBA EMULOVAT ASYNCHRONNE OPERACIE nad FILE, ale v skutocnosti VSETKY IO OPERACIE BUDU SYNCHRONNE.
			using(FileStream FS=new FileStream(@"Files\SomeFile.txt",FileMode.Open))
			{
				CFileStreamCallbackParams						CallbackParams=new CFileStreamCallbackParams(FS);

				Console.WriteLine(string.Format("THREAD: [{0}] - BEFORE IO OPERATION START !",Thread.CurrentThread.ManagedThreadId));

				// !!!!! Aj ked sa v skutocnosti vykonava SYNCHRONNE, tak THREAD NEBUDE BLOCKED.
				IAsyncResult									AR=FS.BeginRead(CallbackParams.Buffer,0,CallbackParams.Buffer.Length,FileReadCallback1,CallbackParams);

				Console.WriteLine(string.Format("THREAD: [{0}] - BEFORE WAITING !",Thread.CurrentThread.ManagedThreadId));

				// !!!!! Je SIGNALIZOVANY este PRED VYKONANIM CALLBACK METHOD.
				AR.AsyncWaitHandle.WaitOne();

				Console.WriteLine(string.Format("THREAD: [{0}] - AFTER WAITING !",Thread.CurrentThread.ManagedThreadId));

				// !!!!! Pozdrzi sa vykonanie Dispose(), az kym sa NESKONCI IO OPERATION.
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test2()
		{
			// Explicitne poziadam o vykonanie ASYNCHRONNEJ OPEACIE nad THREADOM.
			// !!!!! Kedze som zadal FileOptions.Asynchronous, tak CLR vykonavat VSETKY OPERACIE ASYNCHRONNE OPERACIE.
			using(FileStream FS=new FileStream(@"Files\SomeFile.txt",FileMode.Open,FileAccess.Read,FileShare.Read,1024,FileOptions.Asynchronous))
			{
				CFileStreamCallbackParams						CallbackParams=new CFileStreamCallbackParams(FS);

				Console.WriteLine(string.Format("THREAD: [{0}] - BEFORE IO OPERATION START !",Thread.CurrentThread.ManagedThreadId));

				// !!! NAOZAJ sa vykona ASYNCHRONNE.
				IAsyncResult									AR=FS.BeginRead(CallbackParams.Buffer,0,CallbackParams.Buffer.Length,FileReadCallback1,CallbackParams);

				Console.WriteLine(string.Format("THREAD: [{0}] - BEFORE WAITING !",Thread.CurrentThread.ManagedThreadId));

				// !!!!! Je SIGNALIZOVANY este PRED VYKONANIM CALLBACK METHOD.
				AR.AsyncWaitHandle.WaitOne();

				Console.WriteLine(string.Format("THREAD: [{0}] - AFTER WAITING !",Thread.CurrentThread.ManagedThreadId));

				// !!!!! Pozdrzi sa vykonanie Dispose(), az kym sa NESKONCI IO OPERATION.
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test3()
		{
			// Explicitne poziadam o vykonanie ASYNCHRONNEJ OPEACIE nad THREADOM.
			// !!!!! Kedze som zadal FileOptions.Asynchronous, tak CLR vykonavat VSETKY OPERACIE ASYNCHRONNE OPERACIE.
			using(FileStream FS=new FileStream(@"Files\SomeFile.txt",FileMode.Open,FileAccess.Read,FileShare.Read,1024,FileOptions.Asynchronous))
			{
				CFileStreamCallbackParams						CallbackParams=new CFileStreamCallbackParams(FS);

				Console.WriteLine(string.Format("THREAD: [{0}] - BEFORE IO OPERATION START !",Thread.CurrentThread.ManagedThreadId));

				// !!! NAOZAJ sa vykona ASYNCHRONNE.
				// !!! CALLBACK sa POKUSI o pristup k FileStream, co sposobi EXCEPTION, pretoze FileStream je po zavolani EndRead() v CALLBACK METHOD okamzite DISPOSED.
				IAsyncResult									AR=FS.BeginRead(CallbackParams.Buffer,0,CallbackParams.Buffer.Length,FileReadCallback2,CallbackParams);

				Console.WriteLine(string.Format("THREAD: [{0}] - BEFORE WAITING !",Thread.CurrentThread.ManagedThreadId));

				// !!!!! Je SIGNALIZOVANY este PRED VYKONANIM CALLBACK METHOD.
				AR.AsyncWaitHandle.WaitOne();

				Console.WriteLine(string.Format("THREAD: [{0}] - AFTER WAITING !",Thread.CurrentThread.ManagedThreadId));

				// !!!!! Pozdrzi sa vykonanie Dispose(), az kym sa NESKONCI IO OPERATION.
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test4()
		{
			// Generujem REQUEST na NEEXISTUJUCU ADRESU - co sposobi EXCEPTION.
			WebRequest											WR=WebRequest.Create("http://0.0.0.0/");
			IAsyncResult										AR=WR.BeginGetResponse(ProcessExceptionWebResponse,WR);

			// !!! Je signalizovany ESTE PRED VOLANIM CALLBACK METODY.
			AR.AsyncWaitHandle.WaitOne();

			Console.WriteLine(string.Format("THREAD: [{0}] - WEB CALL FINISHED !",Thread.CurrentThread.ManagedThreadId));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test5()
		{
			Console.WriteLine(string.Format("THREAD: [{0}] - MAIN THREAD !",Thread.CurrentThread.ManagedThreadId));

			Action												A=new Action(SomeAction);

			A.BeginInvoke(CallbackForSomeAction,A);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test6()
		{
			Console.WriteLine(string.Format("THREAD: [{0}] - MAIN THREAD !",Thread.CurrentThread.ManagedThreadId));

			Action												A=new Action(SomeAction);
			IAsyncResult										AR=A.BeginInvoke(CallbackForSomeAction,A);

			// !!! Je signalizovany ESTE PRED VOLANIM CALLBACK METODY.
			AR.AsyncWaitHandle.WaitOne();
			
			A.EndInvoke(AR);

			Console.WriteLine(string.Format("THREAD: [{0}] - EndInvoke() FINISHED, CompletedSynchronously: [{1}] !",Thread.CurrentThread.ManagedThreadId,AR.CompletedSynchronously));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test7()
		{
			// !!!!! Kedze som zadal FileOptions.Asynchronous, tak CLR vykonavat VSETKY OPERACIE ASYNCHRONNE OPERACIE.
			using(FileStream FS=new FileStream(@"Files\SomeFile.txt",FileMode.Open,FileAccess.Read,FileShare.Read,1024,FileOptions.Asynchronous))
			{
				CFileStreamCallbackParams						CallbackParams=new CFileStreamCallbackParams(FS);
				IAsyncResult									AR=FS.BeginRead(CallbackParams.Buffer,0,CallbackParams.Buffer.Length,FileReadCallback3,CallbackParams);

				// !!! V podstate konvertuje IAsyncResult na IO TASK na skoncenie ktoreho je mozne zavesit iny TASK.
				Task<int>										APMTask=Task.Factory.FromAsync<int>(AR,FS.EndRead);

				// TASK je AUTOMATICKY SPUSTENY a NESMIE sa VOLAT Start().
				// APMTask.Start();

				// !!! Pri skonceni IO TASK sa vykona NOVY TASK, ktory spracuje vysledky IO TASKU.
				Task											ProcessTask=APMTask.ContinueWith(P => Console.WriteLine(string.Format("Read [{0}] bytes !",P.Result)));

				ProcessTask.Wait();
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Demonstracia EAP.
		private static void Test8()
		{
			BackgroundWorker									BW=new BackgroundWorker();

			// !!! Zaregistrujem CALLBACK volany pri SKONCENI ASYNCHRONNEJ OPERACIE.
			BW.RunWorkerCompleted+=new RunWorkerCompletedEventHandler(BW_RunWorkerCompleted);

			// Zaregistrujem CALLBACK na kod, ktory sa vykona v BackgroundWorker.
			BW.DoWork+=new DoWorkEventHandler(BW_DoWork);

			// Spustim asynchronnu operaciu.
			BW.RunWorkerAsync();
		}
//-------------------------------------------------------------------------------------------------------
		// Demonstracia konverzie EAP na Task.
		private static void Test9()
		{
			// !!! Vytvorim TaskCompletionSource<> na konverziu EAP na TASK.
			TaskCompletionSource<string>						TCS=new System.Threading.Tasks.TaskCompletionSource<string>();
			BackgroundWorker									BW=new BackgroundWorker();

			// Zaregistrujem CALLBACK na kod, ktory sa vykona v BackgroundWorker.
			BW.DoWork+=new DoWorkEventHandler(BW_DoWork);

			// !!! Zaregistrujem CALLBACK volany pri SKONCENI ASYNCHRONNEJ OPERACIE.
			BW.RunWorkerCompleted+=(Sender,E) =>
			{
				Console.WriteLine(string.Format("THREAD: [{0}] - RUN WORKER COMPLETED, Result: [{1}], Error: [{2}], Cancelled: [{3}] !",Thread.CurrentThread.ManagedThreadId,E.Result,E.Error,E.Cancelled));

				// Ak doslo ku CANCELLATION volam SetCanceled().
				if (E.Cancelled==true)
				{
					TCS.SetCanceled();
				}
				// Ak doslo k EXCEPTION volam SetException().
				else if (E.Error!=null)
				{
					TCS.SetException(E.Error);
				}
				// Ak vsetko prebehlo OK volam SetException().
				else if (E.Result!=null)
				{
					TCS.SetResult((string) E.Result);
				}
			};

			// !!! Na konci TASKU, ktory bol konvertovany z EAP zavolam dalsi, ktory iba zobrazi vysledky.
			TCS.Task.ContinueWith(P => Console.WriteLine(string.Format("TASK RESULT: [{0}] !",P.Result)));

			// !!! Spustim ASYNCHRONNU OPERACIU cez EAP.
			BW.RunWorkerAsync();
		}
//-------------------------------------------------------------------------------------------------------
		// Demonstracia jednoduchej ASYNCHRONOUS FUNCTION.
		private static void Test10()
		{
			Console.WriteLine(string.Format("THREAD: [{0}] - MAIN - BEFORE MyAsynchronousFunction() CALLED !",Thread.CurrentThread.ManagedThreadId));

			Task<string>										AsynchronousFunctionTask=MyAsynchronousFunction();

			Console.WriteLine(string.Format("THREAD: [{0}] - MAIN - AFTER MyAsynchronousFunction() FINISHED !",Thread.CurrentThread.ManagedThreadId));

			AsynchronousFunctionTask.Wait();

			Console.WriteLine(string.Format("THREAD: [{0}] - MAIN - AFTER ASYNCHRONOUS FUNCTION TASK FINISHED, Result: [{1}] !",Thread.CurrentThread.ManagedThreadId,AsynchronousFunctionTask.Result));
		}
//-------------------------------------------------------------------------------------------------------
		// Demonstracia jednoduchej ASYNCHRONOUS FUNCTION v NON-STATIC METHOD.
		private static void Test11()
		{
			Console.WriteLine(string.Format("THREAD: [{0}] - MAIN - BEFORE MyAsynchronousFunction() CALLED !",Thread.CurrentThread.ManagedThreadId));

			CClassWithAsynchronousFunction						ClassWithAsynchronousFunction=new CClassWithAsynchronousFunction();

			Task<string>										AsynchronousFunctionTask=ClassWithAsynchronousFunction.MyAsynchronousFunction();

			Console.WriteLine(string.Format("THREAD: [{0}] - MAIN - AFTER MyAsynchronousFunction() FINISHED !",Thread.CurrentThread.ManagedThreadId));

			AsynchronousFunctionTask.Wait();

			Console.WriteLine(string.Format("THREAD: [{0}] - MAIN - AFTER ASYNCHRONOUS FUNCTION TASK FINISHED, Result: [{1}] !",Thread.CurrentThread.ManagedThreadId,AsynchronousFunctionTask.Result));
		}
//-------------------------------------------------------------------------------------------------------
		// Demonstracia CUSTOM ASYNCHRONOUS FUNCTION.
		private static void Test12()
		{
			Console.WriteLine(string.Format("THREAD: [{0}] - MAIN - BEFORE CustomAsynchronousFunction1() CALLED !",Thread.CurrentThread.ManagedThreadId));

			Task<string>										AsynchronousFunctionTask=CustomAsynchronousFunction1();

			Console.WriteLine(string.Format("THREAD: [{0}] - MAIN - AFTER CustomAsynchronousFunction1() FINISHED !",Thread.CurrentThread.ManagedThreadId));

			AsynchronousFunctionTask.Wait();

			Console.WriteLine(string.Format("THREAD: [{0}] - MAIN - AFTER ASYNCHRONOUS FUNCTION TASK FINISHED, Result: [{1}] !",Thread.CurrentThread.ManagedThreadId,AsynchronousFunctionTask.Result));
		}
//-------------------------------------------------------------------------------------------------------
		// Demonstracia CUSTOM ASYNCHRONOUS FUNCTION.
		private static void Test13()
		{
			Console.WriteLine(string.Format("THREAD: [{0}] - MAIN - BEFORE CustomAsynchronousFunction2() CALLED !",Thread.CurrentThread.ManagedThreadId));

			Task<string>										AsynchronousFunctionTask=CustomAsynchronousFunction2();

			Console.WriteLine(string.Format("THREAD: [{0}] - MAIN - AFTER CustomAsynchronousFunction2() FINISHED !",Thread.CurrentThread.ManagedThreadId));

			AsynchronousFunctionTask.Wait();

			Console.WriteLine(string.Format("THREAD: [{0}] - MAIN - AFTER ASYNCHRONOUS FUNCTION TASK FINISHED, Result: [{1}] !",Thread.CurrentThread.ManagedThreadId,AsynchronousFunctionTask.Result));
		}
//-------------------------------------------------------------------------------------------------------
		// Demonstracia CUSTOM ASYNCHRONOUS FUNCTION a CUSTOM AWAITER.
		private static void Test14()
		{
			Console.WriteLine(string.Format("THREAD: [{0}] - MAIN - BEFORE CustomAwaitor.Test() CALLED !",Thread.CurrentThread.ManagedThreadId));

			CCustomAwaiter										CustomAwaitor=new CCustomAwaiter();

			Task<string>										AsynchronousFunctionTask=CustomAwaitor.Test();

			Console.WriteLine(string.Format("THREAD: [{0}] - MAIN - AFTER CustomAwaitor.Test() FINISHED !",Thread.CurrentThread.ManagedThreadId));

			AsynchronousFunctionTask.Wait();

			Console.WriteLine(string.Format("THREAD: [{0}] - MAIN - AFTER ASYNCHRONOUS FUNCTION TASK FINISHED, Result: [{1}] !",Thread.CurrentThread.ManagedThreadId,AsynchronousFunctionTask.Result));
		}
//-------------------------------------------------------------------------------------------------------
		// Demonstracia CUSTOM ASYNCHRONOUS FUNCTION a CUSTOM AWAITER.
		private static void Test15()
		{
			Console.WriteLine(string.Format("THREAD: [{0}] - MAIN - BEFORE CustomAwaiterWithCustomTaskAwaiter.Test() CALLED !",Thread.CurrentThread.ManagedThreadId));

			CCustomAwaiterWithCustomTaskAwaiter					CustomAwaiterWithCustomTaskAwaiter=new CCustomAwaiterWithCustomTaskAwaiter();

			Task<string>										AsynchronousFunctionTask=CustomAwaiterWithCustomTaskAwaiter.Test();

			Console.WriteLine(string.Format("THREAD: [{0}] - MAIN - AFTER CustomAwaiterWithCustomTaskAwaiter.Test() FINISHED !",Thread.CurrentThread.ManagedThreadId));

			AsynchronousFunctionTask.Wait();

			Console.WriteLine(string.Format("THREAD: [{0}] - MAIN - AFTER ASYNCHRONOUS FUNCTION TASK FINISHED, Result: [{1}] !",Thread.CurrentThread.ManagedThreadId,AsynchronousFunctionTask.Result));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test16()
		{
			Console.WriteLine(string.Format("THREAD: [{0}] - MAIN - BEFORE TestMultiTask() CALLED !",Thread.CurrentThread.ManagedThreadId));

			Task												AsynchronousFunctionTask=TestMultiTask();

			Console.WriteLine(string.Format("THREAD: [{0}] - MAIN - AFTER TestMultiTask() FINISHED !",Thread.CurrentThread.ManagedThreadId));

			AsynchronousFunctionTask.Wait();

			Console.WriteLine(string.Format("THREAD: [{0}] - MAIN - AFTER ASYNCHRONOUS FUNCTION TASK FINISHED !",Thread.CurrentThread.ManagedThreadId));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test17()
		{
			Console.WriteLine(string.Format("THREAD: [{0}] - MAIN - BEFORE VoidReturnAsynchronousFunction() CALLED !",Thread.CurrentThread.ManagedThreadId));

			ManualResetEvent									Event=new ManualResetEvent(false);

			// !!! ASYNCHRONOUS FUNCTION, ktora NEMA RETURN VALUE.
			// !!!!! Kedze FUNCTION nevracia TASK ako RETURN VALUE, tak na zistenie ukoncenia ASYNCHROUNOUS FUNCTION sa pouziva PARAMETER typu ManualResetEvent.
			VoidReturnAsynchronousFunction(Event);

			Console.WriteLine(string.Format("THREAD: [{0}] - MAIN - AFTER VoidReturnAsynchronousFunction() FINISHED !",Thread.CurrentThread.ManagedThreadId));

			Event.WaitOne();

			Console.WriteLine(string.Format("THREAD: [{0}] - MAIN - AFTER ASYNCHRONOUS FUNCTION TASK FINISHED !",Thread.CurrentThread.ManagedThreadId));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test18()
		{
			Console.WriteLine(string.Format("THREAD: [{0}] - MAIN - BEFORE ReadFileWithAsynchronousFunction1() CALLED !",Thread.CurrentThread.ManagedThreadId));

			Task<string>										AsynchronousFunctionTask=ReadFileWithAsynchronousFunction1();

			Console.WriteLine(string.Format("THREAD: [{0}] - MAIN - AFTER ReadFileWithAsynchronousFunction1() FINISHED !",Thread.CurrentThread.ManagedThreadId));

			AsynchronousFunctionTask.Wait();

			Console.WriteLine(string.Format("THREAD: [{0}] - MAIN - AFTER ASYNCHRONOUS FUNCTION TASK FINISHED, RESULT [{1}] !",Thread.CurrentThread.ManagedThreadId,AsynchronousFunctionTask.Result));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test19()
		{
			Console.WriteLine(string.Format("THREAD: [{0}] - MAIN - BEFORE ReadFileWithAsynchronousFunction2() CALLED !",Thread.CurrentThread.ManagedThreadId));

			Task<string>										AsynchronousFunctionTask=ReadFileWithAsynchronousFunction2();

			Console.WriteLine(string.Format("THREAD: [{0}] - MAIN - AFTER ReadFileWithAsynchronousFunction2() FINISHED !",Thread.CurrentThread.ManagedThreadId));

			AsynchronousFunctionTask.Wait();

			Console.WriteLine(string.Format("THREAD: [{0}] - MAIN - AFTER ASYNCHRONOUS FUNCTION TASK FINISHED, RESULT [{1}] !",Thread.CurrentThread.ManagedThreadId,AsynchronousFunctionTask.Result));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test20()
		{
			Console.WriteLine(string.Format("THREAD: [{0}] - MAIN - BEFORE TestException1() CALLED !",Thread.CurrentThread.ManagedThreadId));

			Task												AsynchronousFunctionTask=TestException1();

			Console.WriteLine(string.Format("THREAD: [{0}] - MAIN - AFTER TestException1() FINISHED !",Thread.CurrentThread.ManagedThreadId));

			try
			{
				AsynchronousFunctionTask.Wait();

				Console.WriteLine(string.Format("THREAD: [{0}] - MAIN - AFTER ASYNCHRONOUS FUNCTION TASK FINISHED !",Thread.CurrentThread.ManagedThreadId));
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("THREAD: [{0}] - MAIN - EXCEPTION [{1}] OCCURED while processing ASYNCHRONOUS FUNCTION !",Thread.CurrentThread.ManagedThreadId,E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test21()
		{
			Console.WriteLine(string.Format("THREAD: [{0}] - MAIN - BEFORE TestException2() CALLED !",Thread.CurrentThread.ManagedThreadId));

			Task												AsynchronousFunctionTask=TestException2();

			Console.WriteLine(string.Format("THREAD: [{0}] - MAIN - AFTER TestException2() FINISHED !",Thread.CurrentThread.ManagedThreadId));

			try
			{
				AsynchronousFunctionTask.Wait();

				Console.WriteLine(string.Format("THREAD: [{0}] - MAIN - AFTER ASYNCHRONOUS FUNCTION TASK FINISHED !",Thread.CurrentThread.ManagedThreadId));
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("THREAD: [{0}] - MAIN - EXCEPTION [{1}] OCCURED while processing ASYNCHRONOUS FUNCTION !",Thread.CurrentThread.ManagedThreadId,E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test22()
		{
			AppDomain.CurrentDomain.UnhandledException += UnhandledExceptionHandler;

			Console.WriteLine(string.Format("THREAD: [{0}] - MAIN - BEFORE TestException3() CALLED !",Thread.CurrentThread.ManagedThreadId));

			TestException3();

			Console.WriteLine(string.Format("THREAD: [{0}] - MAIN - AFTER TestException3() FINISHED !",Thread.CurrentThread.ManagedThreadId));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test23()
		{
			Console.WriteLine(string.Format("THREAD: [{0}] - MAIN - BEFORE LAMBDA EXPRESSION CREATED !",Thread.CurrentThread.ManagedThreadId));

			// !!! Demonstruje LAMBDA EXPRESSION ako ASYNCHRONOUS FUNCTION.
			Func<Task<string>>									LambdaExpression=(async () =>
			{
				Task											AwaitebleAction=new Task(SomeAction);

				AwaitebleAction.Start();

				Console.WriteLine(string.Format("THREAD: [{0}] - BEFORE AWAIT !",Thread.CurrentThread.ManagedThreadId));

				await AwaitebleAction;

				Console.WriteLine(string.Format("THREAD: [{0}] - AFTER AWAIT !",Thread.CurrentThread.ManagedThreadId));

				return("Timmy Anderson");
			});

			// !!! Vytvorim NOVY TASK pre LAMBDA EXPRESSION a tento TASK sa OKAMZITE SPUSTI.
			Task<string>										AsynchronousFunctionTask=Task.Run(LambdaExpression);

			Console.WriteLine(string.Format("THREAD: [{0}] - MAIN - AFTER LAMBDA EXPRESSION CREATED !",Thread.CurrentThread.ManagedThreadId));

			AsynchronousFunctionTask.Wait();

			Console.WriteLine(string.Format("THREAD: [{0}] - MAIN - AFTER ASYNCHRONOUS FUNCTION TASK FINISHED, RESULT [{1}] !",Thread.CurrentThread.ManagedThreadId,AsynchronousFunctionTask.Result));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test24()
		{
			LoadTest();
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
			Test24();

			Console.WriteLine("\nPress any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------