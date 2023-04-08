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
	public sealed class CCustomAwaiter
	{
//-------------------------------------------------------------------------------------------------------
		private Task											MTask;
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
		public TaskAwaiter GetAwaiter()
		{
			Console.WriteLine(string.Format("THREAD: [{0}] - GetAwaiter() EXECUTED !",Thread.CurrentThread.ManagedThreadId));

			// !!!!! Vracia implementaciu TaskAwaiter v CLASS Task.
			return(MTask.GetAwaiter());
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// !!! ASYNCHRONOUS FUNCTION MUSI vracat Task<RETURN_VALUE>, kde RETURN_VALUE je TYPE RETURN VALUE, ktoru ASYNCHRONOUS FUNCTION vracia.
		public async Task<string> Test()
		{
			Console.WriteLine(string.Format("THREAD: [{0}] - Test() STARTED !",Thread.CurrentThread.ManagedThreadId));

			// !!!!! Vytvorim novy TASK, ktory pouzije CUSTOM AWAITER.
			MTask=new Task(SomeAction);

			// !!! TASK musi by SPUSTENY.
			MTask.Start();

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