using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingEFCore2
{
//----------------------------------------------------------------------------------------------------------------------
    public class Program
    {
//----------------------------------------------------------------------------------------------------------------------
		private static readonly object							MLock=new object();
//----------------------------------------------------------------------------------------------------------------------
		private static string									MSharedVariable;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public static void WriteLineSeparator()
		{
			string												Text="".PadRight(Console.WindowWidth-1,'-');

			Console.WriteLine(Text);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! METHOD simuluje CALLBACK FUNCTION, ktora sa spusti, ked WIN32 API skonci ASYNCHRONOU IO OPERATION.
		private static void CallbackFunction(object TaskToExecute)
		{
			// !!!!! Simuluje sa, ze IO OPERATION nejaky cas trva.
			Thread.Sleep(5000);

			Console.WriteLine("CALLBACK FUNCTION STARTED.");

			Task<string>										TypedTaskToExecute=(Task<string>) TaskToExecute;

			// !!!!! Simuluje sa nacitanie RESULTS a ich ulozenie do SHARED VARIABLE z ktorej TASK vytiahne tieto RESULTS.
			lock(MLock)
			{
				MSharedVariable="HELLO WORLD !";
			}

			// !!!! Spusti sa TASK, ktory bol vrateny z ASYNCHRONOUS IO OPERATION.
			TypedTaskToExecute.Start();

			Console.WriteLine("CALLBACK FUNCTION FINISHED.");

			Console.WriteLine("IO OPERATION FINISHED.");
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! TASK METHOD, ktora vrati DATA, ktore boli nacitane pomocou ASYNCHRONOUS IO OPERATION.
		private static string GetResults()
		{
			// !!!!! Simuluje sa, ze TASK sa spusti neskor, az ked THREAD POOL zacne spracovavat tento TASK.
			Thread.Sleep(1000);

			string												Result;

			// !!!!! Simuluje sa nacitanie RESULTS zo SHARED VARIABLE kam ich ulozila CALLBACK FUNCTION.
			lock(MLock)
			{
				Result=MSharedVariable;
			}

			// !!!!! RESULTS sa vratia ako RETURN VALUE.
			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! SIMULUJE SPUSTENIE ASYNCHRONOUS IO OPERATION.
		private static Task<string> AsynchronousIOOperation()
		{
			// !!!!! Vytvori sa TASK vracajuci RESULTS IO OPERATION, ktory sa vsak NESPUSTI. Spusteny bude az v CALLBACK FUNCTION po skonceni IO OPERATION, ked su RESULTS ASYNCHRONOUS IO OPERATION k dispozicii.
			Task<string>										Task=new Task<string>(GetResults);

			// !!!!! Simuluje sa spustenie IO OPERATION cez WIN32 API FUNCTION.
			Console.WriteLine("IO OPERATION SENT to WIN32 API waiting for CALLBACK FUNCTION to CALL.");

			// !!!!! Simuluje sa vyvolanie CALLBACK METHOD, ktora by normalne bola spustena ked ASYNCRHONOU IO OPERATION SKONCI a spusti sa zaregistrovana CALLBACK FUNCTION.
			// !!!!! Ak PARAMETER sa da TASK, ktory ma vrati RESULTS ASYNCHRONOUS IO OPERATION.
			ThreadPool.QueueUserWorkItem(CallbackFunction,Task);

			// !!!!! TASK sa vracia NESPUSTENY.
			return(Task);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void ProcessResults(Task<string> IOTask)
		{
			// !!! Nacita sa RESULT s IO TASK, ktory uz je COMPLETED.
			string												Result=IOTask.Result;

			Console.WriteLine($"IO OPERATION RESULT is [{Result}].");
		}
//----------------------------------------------------------------------------------------------------------------------
		public static void ExecuteAsynchronousIOOperation()
		{
			WriteLineSeparator();

			// !!!!! TASK je SPUSTENY v CALLBACK FUNCTION, az ked sa IO OPERATION SKONCI a su k dispozii RESULTS.
			Task<string>										IOWait=AsynchronousIOOperation();

			// !!! Simuluje sa naviazanie dalsieho TASK, ktory spracuje RESULTS.
			Task												TaskToWait=IOWait.ContinueWith(ProcessResults);

			// !!! Caka sa na skoncenie TASK, ktory spracoval RESULT.
			TaskToWait.Wait();

			WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
        static void Main(string[] args)
        {
			ExecuteAsynchronousIOOperation();

			Console.WriteLine("Press ENTER to EXIT !");
			Console.ReadLine();
        }
//----------------------------------------------------------------------------------------------------------------------
    }
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------