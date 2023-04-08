using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
//-------------------------------------------------------------------------------------------------------
namespace MySynchronizationContext
{
//-------------------------------------------------------------------------------------------------------
	public class CMySynchronizationContext : SynchronizationContext, IDisposable
	{
//-------------------------------------------------------------------------------------------------------
		private CWorkerThread									MWorkerThread;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CMySynchronizationContext()
		{
			MWorkerThread=new CWorkerThread(this);
			MWorkerThread.Start();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override void Post(SendOrPostCallback Method, object MethodParams)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString(Thread.CurrentThread.ManagedThreadId));

			CWorkItem			WorkItem = new CWorkItem(Method,MethodParams);

			MWorkerThread.Push(WorkItem);
		}
//-------------------------------------------------------------------------------------------------------
		public override void Send(SendOrPostCallback Method, object MethodParams)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString(Thread.CurrentThread.ManagedThreadId));

			// If already on the correct context, must invoke now to avoid deadlock.
			if (SynchronizationContext.Current==this)
			{
				Method(MethodParams);
				return;
			}

			CWorkItem				WorkItem=new CWorkItem(Method,MethodParams);

			MWorkerThread.Push(WorkItem);
			WorkItem.AsynchroWaitHandle.WaitOne();
		}
//-------------------------------------------------------------------------------------------------------
		public void Dispose()
		{
			MWorkerThread.Dispose();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------