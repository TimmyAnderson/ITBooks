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
	// !!!!! CUSTOM TASK AWAITER musi IMPLEMENTOVAT INTERFACES ICriticalNotifyCompletion a INotifyCompletion, PROPERTY IsCompleted a METHOD GetResult().
	public sealed class CCustomTaskAwaiter : ICriticalNotifyCompletion, INotifyCompletion
	{
//-------------------------------------------------------------------------------------------------------
		private Task											MAwaiterTask;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CCustomTaskAwaiter(Task AwaiterTask)
		{
			MAwaiterTask=AwaiterTask;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public bool												IsCompleted
		{
			get
			{
				Console.WriteLine(string.Format("THREAD: [{0}] - IsCompleted EXECUTED IsCompleted: [{1}] !",Thread.CurrentThread.ManagedThreadId,MAwaiterTask.IsCompleted));

				return(MAwaiterTask.IsCompleted);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void OnCompleted(Action Continuation)
		{
			Console.WriteLine(string.Format("THREAD: [{0}] - OnCompleted() EXECUTED !",Thread.CurrentThread.ManagedThreadId));

			// !!!!! Ak CURRENT TASK SKONCI, tak sa zavola METHOD Continuation(), ktora interne vola IAsyncStateMachine.MoveNext(), cim posunie STATE vo vygenerovanej STATE MACHINE.
			MAwaiterTask.ContinueWith(P => Continuation());
		}
//-------------------------------------------------------------------------------------------------------
		public void UnsafeOnCompleted(Action Continuation)
		{
			Console.WriteLine(string.Format("THREAD: [{0}] - UnsafeOnCompleted() EXECUTED !",Thread.CurrentThread.ManagedThreadId));

			// !!!!! Ak CURRENT TASK SKONCI, tak sa zavola METHOD Continuation(), ktora interne vola IAsyncStateMachine.MoveNext(), cim posunie STATE vo vygenerovanej STATE MACHINE.
			MAwaiterTask.ContinueWith(P => Continuation());
		}
//-------------------------------------------------------------------------------------------------------
		// !!!!! Ak by sa pouzil Task<TType>, tak by GetResult() vracal TType ako RETURN VALUE.
		public void GetResult()
		{
			// !!! METHOD by mala hodit EXCEPTION, ak doslo pri vykonavani ASYNCHRONOUS FUNCTION k EXCEPTION.
			Console.WriteLine(string.Format("THREAD: [{0}] - GetResult() EXECUTED !",Thread.CurrentThread.ManagedThreadId));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------