using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
//-------------------------------------------------------------------------------------------------------
namespace MySynchronizationContext
{
//-------------------------------------------------------------------------------------------------------
	internal class CWorkItem : IDisposable
	{
//-------------------------------------------------------------------------------------------------------
		private SendOrPostCallback								MMethod;
		private object											MMethodParams;
		// Pouziva sa na indikaciu, ze vykonavanie instrukcie sa skoncilo. Je to pre implementaciu Send().
		private ManualResetEvent								MAsynchroWaitHandle;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		internal CWorkItem(SendOrPostCallback Method, object MethodParams)
		{
			MMethod=Method;
			MMethodParams=MethodParams;
			MAsynchroWaitHandle=new ManualResetEvent(false);
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		internal ManualResetEvent								AsynchroWaitHandle
		{
			get
			{
				return(MAsynchroWaitHandle);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		internal void DoCall()
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString(Thread.CurrentThread.ManagedThreadId));

			MMethod(MMethodParams);
			MAsynchroWaitHandle.Set();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void Dispose()
		{
			if (MAsynchroWaitHandle!=null)
			{
				MAsynchroWaitHandle.Close();
				MAsynchroWaitHandle=null;
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------