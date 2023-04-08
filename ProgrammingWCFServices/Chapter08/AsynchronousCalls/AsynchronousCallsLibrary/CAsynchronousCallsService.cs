using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Runtime.Serialization;
using System.Runtime.CompilerServices;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace AsynchronousCallsLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceBehavior(InstanceContextMode=InstanceContextMode.PerSession,ConcurrencyMode=ConcurrencyMode.Multiple)]
	public class CAsynchronousCallsService : IAsynchronousCallsContract, IDisposable
	{
//-------------------------------------------------------------------------------------------------------
		private static Func<string,string>						MMyFunction=new Func<string,string>(MySlowMethod);
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CAsynchronousCallsService()
		{
			Console.WriteLine(CDebugHelper.GetConstructorCallString());
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private static string MySlowMethod(string Message)
		{
			Console.WriteLine(string.Format("MySlowMethod(): BEFORE WAIT - {0}: {1} !",CDebugHelper.GetMethodCallString(),Message));

			Thread.Sleep(5*1000);

			Console.WriteLine(string.Format("MySlowMethod(): AFTER WAIT - {0}: {1} !",CDebugHelper.GetMethodCallString(),Message));

			return(Message + "_RET");
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void IsAlive()
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
		}
//-------------------------------------------------------------------------------------------------------
        public string SlowMethod(string Message, ref string RefMessage, out string OutMessage)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString(1));

			Console.WriteLine(string.Format("{0}: {1} !",CDebugHelper.GetMethodCallString(),Message));
			Thread.Sleep(5*1000);

			RefMessage=Message + "_REF";
			OutMessage=Message + "_OUT";

			Console.WriteLine(CDebugHelper.GetMethodCallString(2));

			return(Message + "_RET");
		}
//-------------------------------------------------------------------------------------------------------
		public void SlowMethodWithException(string Message)
		{
			Console.WriteLine(string.Format("{0}: {1} !",CDebugHelper.GetMethodCallString(),Message));
			
			Exception					E=new Exception("SOME INVALID OPERATION");
			FaultException<Exception>	FE=new FaultException<Exception>(E,"BUG !!!");

			throw(FE);
		}
//-------------------------------------------------------------------------------------------------------
		public void SlowMethodWithUnexpectedException(string Message)
		{
			Console.WriteLine(string.Format("{0}: {1} !",CDebugHelper.GetMethodCallString(),Message));
			
			Exception					E=new Exception("SOME INVALID OPERATION");

			throw(E);
		}
//-------------------------------------------------------------------------------------------------------
		public IAsyncResult BeginServerAsynchroSlowMethod(string Message, AsyncCallback CB, object AS)
		{
			Console.WriteLine(string.Format("BeginServerAsynchroSlowMethod() CALLED !"));

			IAsyncResult				AR=MMyFunction.BeginInvoke(Message,CB,AS);

			return(AR);
		}
//-------------------------------------------------------------------------------------------------------
		public string EndServerAsynchroSlowMethod(IAsyncResult AR)
		{
			string						Ret=MMyFunction.EndInvoke(AR);

			Console.WriteLine(string.Format("EndServerAsynchroSlowMethod() CALLED !"));

			return(Ret);
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