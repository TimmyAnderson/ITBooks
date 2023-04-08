using System;
using System.Collections.Generic;
using System.Threading;
using System.Threading.Tasks;
//----------------------------------------------------------------------------------------------------------------------
namespace TestAsynchronousEnumerable
{
//----------------------------------------------------------------------------------------------------------------------
	class Program
	{
//----------------------------------------------------------------------------------------------------------------------
		private static string CreateTime()
		{
			DateTime											Time=DateTime.Now;
			string												TextTime=$"{Time.Hour.ToString("00")}:{Time.Minute.ToString("00")}:{Time.Second.ToString("00")}.{Time.Millisecond.ToString("000")}";

			return(TextTime);
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! Vytvori sa RESULT, ktory moze byt spracovavany ASYNCHRONNE.
		private static async IAsyncEnumerable<int> CreateResults()
		{
			for(int Index=0;Index<5;Index++)
			{
				int												Value=(Index+1);

				Console.WriteLine($"RECORD [{Value}] is PRODUCING at TIME [{CreateTime()}] in THREAD [{Thread.CurrentThread.ManagedThreadId}] !");

				await Task.Delay(1000);

				Console.WriteLine($"RECORD [{Value}] is PRODUCED at TIME [{CreateTime()}] in THREAD [{Thread.CurrentThread.ManagedThreadId}] !");

				yield return(Value);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static async Task ProcessResults()
		{
			IAsyncEnumerable<int>								Results=CreateResults();

			await foreach(int Value in Results)
			{
				Console.WriteLine($"RECORD [{Value}] is CONSUMED at TIME [{CreateTime()}] in THREAD [{Thread.CurrentThread.ManagedThreadId}] !");
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.WriteLine("".PadRight(Console.WindowWidth-1,'-'));

			Task												Results=ProcessResults();

			Results.Wait();

			Console.WriteLine("".PadRight(Console.WindowWidth-1,'-'));

			Console.WriteLine("Press ANY KEY to EXIT !");
			Console.ReadKey();
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------