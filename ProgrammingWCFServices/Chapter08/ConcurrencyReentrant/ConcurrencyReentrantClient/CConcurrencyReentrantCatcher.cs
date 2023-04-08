using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.Threading;
using ConcurrencyReentrantLibrary;
//-------------------------------------------------------------------------------------------------------
namespace ConcurrencyReentrantClient
{
//-------------------------------------------------------------------------------------------------------
	[CallbackBehavior(ConcurrencyMode=ConcurrencyMode.Reentrant)]
	public class CConcurrencyReentrantCatcher : IConcurrencyReentrantCallback
	{
//-------------------------------------------------------------------------------------------------------
		private string											MClientName;
		private CConcurrencyReentrantProxy						MConcurrencyReentrantProxy;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CConcurrencyReentrantCatcher(string ClientName)
		{
			MClientName=ClientName;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public  CConcurrencyReentrantProxy						ConcurrencyReentrantProxy
		{
			set
			{
				MConcurrencyReentrantProxy=value;
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void OnCallback1(string Message)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString(1));

			Console.WriteLine(string.Format("PROXY: {0} FROM SERVER: {1} !",MClientName,Message));

			string					ClientMessage=string.Format("CLIENT: {0} !",MClientName,Message);

			try
			{
				MConcurrencyReentrantProxy.SlowMethod(Message);
			}
			catch(Exception E)
			{
				Console.WriteLine(CDebugHelper.GetExceptionString(E));
			}

			Console.WriteLine(CDebugHelper.GetMethodCallString(2));
		}
//-------------------------------------------------------------------------------------------------------
		public void OnCallback2(string Message)
		{
			Console.WriteLine(string.Format("CALLBACK - OnCallback2() with MESSAGE [{0}] is going to WAIT !",Message));

			Thread.Sleep(2000);

			Console.WriteLine(string.Format("CALLBACK - OnCallback2() with MESSAGE [{0}] is finished WAITING !",Message));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------