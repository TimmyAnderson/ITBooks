using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.ServiceModel;
using System.ServiceModel.Channels;
using ConcurrencyCallbackLibrary;
//-------------------------------------------------------------------------------------------------------
namespace ConcurrencyCallbackClient
{
//-------------------------------------------------------------------------------------------------------
	[CallbackBehavior(ConcurrencyMode=ConcurrencyMode.Single)]
	public class CConcurrencyCallbackCatcher : IConcurrencyCallbackCallback
	{
//-------------------------------------------------------------------------------------------------------
		public void OnCallback(string Message)
		{
			Console.WriteLine(string.Format("{0}: {1} !",CDebugHelper.GetMethodCallString(1),Message));

			Console.WriteLine(string.Format("FROM SERVER: {0} !",Message));
			Thread.Sleep(5*1000);

			Console.WriteLine(string.Format("{0}: {1} !",CDebugHelper.GetMethodCallString(2),Message));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------