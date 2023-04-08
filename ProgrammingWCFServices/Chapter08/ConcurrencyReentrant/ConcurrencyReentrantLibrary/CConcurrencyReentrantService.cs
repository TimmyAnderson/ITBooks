using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Runtime.Serialization;
using System.ServiceModel;
using ClientHelper;
//-------------------------------------------------------------------------------------------------------
namespace ConcurrencyReentrantLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceBehavior(InstanceContextMode=InstanceContextMode.PerSession,ConcurrencyMode=ConcurrencyMode.Reentrant)]
	public class CConcurrencyReentrantService : IConcurrencyReentrantContract, IDisposable
	{
//-------------------------------------------------------------------------------------------------------
		private static CClientList<IConcurrencyReentrantCallback>	MClientList=new CClientList<IConcurrencyReentrantCallback>();
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CConcurrencyReentrantService()
		{
			Console.WriteLine(CDebugHelper.GetConstructorCallString());
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void Connect(string ClientName)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			MClientList.Add(new CClientListItem<IConcurrencyReentrantCallback>(OperationContext.Current.GetCallbackChannel<IConcurrencyReentrantCallback>(), ClientName));
		}
//-------------------------------------------------------------------------------------------------------
        public void Disconnect()
        {
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			MClientList.Remove(OperationContext.Current.GetCallbackChannel<IConcurrencyReentrantCallback>());
        }
//-------------------------------------------------------------------------------------------------------
        public void SlowMethod(string Message)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString(1));

			Console.WriteLine(string.Format("{0}: {1} !",CDebugHelper.GetMethodCallString(),Message));
			Thread.Sleep(5*1000);

			Console.WriteLine(CDebugHelper.GetMethodCallString(2));
		}
//-------------------------------------------------------------------------------------------------------
        public void DoCallback(string Message)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString(1));

			IConcurrencyReentrantCallback		Callback=OperationContext.Current.GetCallbackChannel<IConcurrencyReentrantCallback>();
			string								ServerMessage=string.Format("SERVER: {0}",Message);

			Thread.Sleep(5*1000);

			try
			{
				Callback.OnCallback1(ServerMessage);
			}
			catch(Exception E)
			{
				Console.WriteLine(CDebugHelper.GetExceptionString(E));
			}

			Console.WriteLine(CDebugHelper.GetMethodCallString(2));
		}
//-------------------------------------------------------------------------------------------------------
        public void DoSlowCallback(string Message)
		{
			Console.WriteLine(string.Format("DoSlowCallback() with MESSAGE [{0}] STARTED !",Message));

			IConcurrencyReentrantCallback		Callback=OperationContext.Current.GetCallbackChannel<IConcurrencyReentrantCallback>();
			string								ServerMessage=string.Format("FROM SERVER: {0}",Message);

			Console.WriteLine(string.Format("DoSlowCallback() with MESSAGE [{0}] is going to WAIT !",Message));

			Thread.Sleep(2000);

			Console.WriteLine(string.Format("DoSlowCallback() with MESSAGE [{0}] is finished WAITING !",Message));

			try
			{
				Console.WriteLine(string.Format("DoSlowCallback() with MESSAGE [{0}] is CALLING CALLBACK !",Message));

				// !!! Pocas realizacie CALLBACK sa UVOLNI LOCK a k objektu je mozne PRISTUPIT, kedze NEMA UVALENY LOCK.
				Callback.OnCallback2(ServerMessage);

				Console.WriteLine(string.Format("DoSlowCallback() with MESSAGE [{0}] is CALLED CALLBACK !",Message));
			}
			catch(Exception E)
			{
				Console.WriteLine(CDebugHelper.GetExceptionString(E));
			}

			Console.WriteLine(string.Format("DoSlowCallback() with MESSAGE [{0}] FINISHED !",Message));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void Dispose()
		{
			Console.WriteLine(CDebugHelper.GetDestructorCallString());
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------