using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Runtime.CompilerServices;
//-------------------------------------------------------------------------------------------------------
namespace IOBoundAsynchronousOperations
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CCustomAwaiterWithCustomTaskAwaiter
	{
//-------------------------------------------------------------------------------------------------------
		private CCustomTaskAwaiter								MCurrentAwaiter;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private void SomeAction()
		{
			Console.WriteLine(string.Format("THREAD: [{0}] - SomeAction() STARTED !",Thread.CurrentThread.ManagedThreadId));

			Thread.Sleep(1000);
			
			Console.WriteLine(string.Format("THREAD: [{0}] - SomeAction() FINISHED !",Thread.CurrentThread.ManagedThreadId));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// !!!!! CUSTOM implementacia GetAwaiter().
		public CCustomTaskAwaiter GetAwaiter()
		{
			Console.WriteLine(string.Format("THREAD: [{0}] - GetAwaiter() EXECUTED !",Thread.CurrentThread.ManagedThreadId));

			// !!!!! Vracia CUSTOM implementaciu TaskAwaiter.
			return(MCurrentAwaiter);
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// !!! ASYNCHRONOUS FUNCTION MUSI vracat Task<RETURN_VALUE>, kde RETURN_VALUE je TYPE RETURN VALUE, ktoru ASYNCHRONOUS FUNCTION vracia.
		public async Task<string> Test()
		{
			Console.WriteLine(string.Format("THREAD: [{0}] - Test() STARTED !",Thread.CurrentThread.ManagedThreadId));

			// !!!!! Vytvorim novy TASK, ktory pouzije CUSTOM AWAITER.
			Task												Task1=new Task(SomeAction);

			// Vytvorim AWAITER okolo CURRENT TASK.
			MCurrentAwaiter=new CCustomTaskAwaiter(Task1);

			// !!! TASK musi by SPUSTENY.
			Task1.Start();

			// !!!!! Kedze CLASS CCustomAwaiter implementuje GetAwaiter() je ho mozne pouzit ako OPERAND OPERATORA 'await'.
			await this;

			Console.WriteLine(string.Format("THREAD: [{0}] - Test() BETWEEN AWAITER !",Thread.CurrentThread.ManagedThreadId));

			// !!!!! Vytvorim novy TASK, ktory pouzije CUSTOM AWAITER.
			Task												Task2=new Task(SomeAction);

			// Vytvorim AWAITER okolo CURRENT TASK.
			MCurrentAwaiter=new CCustomTaskAwaiter(Task2);

			// !!! TASK musi by SPUSTENY.
			Task2.Start();

			// !!!!! Kedze CLASS CCustomAwaiter implementuje GetAwaiter() je ho mozne pouzit ako OPERAND OPERATORA 'await'.
			await this;

			Console.WriteLine(string.Format("THREAD: [{0}] - Test() FINISHED !",Thread.CurrentThread.ManagedThreadId));

			return("My name is TIMMY !!!");
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------