using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.ServiceModel;
using System.ServiceModel.Channels;
using CustomSCCallbackLibrary;
//-------------------------------------------------------------------------------------------------------
namespace CustomSCCallbackClient
{
//-------------------------------------------------------------------------------------------------------
	[CallbackBehavior(ConcurrencyMode=ConcurrencyMode.Multiple, UseSynchronizationContext=true)]
	class CCustomSCCallbackCatcher : ICustomSCCallbackCallback
	{
//-------------------------------------------------------------------------------------------------------
		public void OnCallback(string Message)
		{
			Console.WriteLine(string.Format("{0}: {1}, TID: {2} !",CDebugHelper.GetMethodCallString(1),Message,Thread.CurrentThread.ManagedThreadId));

			Console.WriteLine(string.Format("FROM SERVER: {0} !",Message));
			Thread.Sleep(5*1000);

			Console.WriteLine(string.Format("{0}: {1}, TID: {2} !",CDebugHelper.GetMethodCallString(2),Message,Thread.CurrentThread.ManagedThreadId));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------