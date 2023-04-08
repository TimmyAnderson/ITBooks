using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.Threading;
using System.Transactions;
using System.ServiceModel.Description;
using LCChannel;
using Log;
//-------------------------------------------------------------------------------------------------------
namespace ComplexTest
{
//-------------------------------------------------------------------------------------------------------
	[ServiceBehavior(ConcurrencyMode=ConcurrencyMode.Reentrant)]
	internal class CDuplexSessionReceiver : ISomeContractDuplexSession
	{
//-------------------------------------------------------------------------------------------------------
		private string											MSessionData;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CDuplexSessionReceiver()
		{
			CGlobals.Log.Write(CDebugHelper.GetConstructorCallString());
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// ISomeContract implementation.
		public void SomeOperation(string Input)
		{
			CGlobals.Log.Write(CDebugHelper.GetMethodCallString());

			char[]						Chars=Input.ToCharArray();

			Array.Reverse(Chars);

			string						Retval=new string(Chars);

			MSessionData=Input;

			CGlobals.Log.Write(CDebugHelper.GetMethodCallString(),string.Format("SessionData - SET: {0}",MSessionData));

			// Use the callback channel to return a reversed String.
			ICallbackContract			Callback=OperationContext.Current.GetCallbackChannel<ICallbackContract>();

			Callback.SomeCallbackOperation(Retval);
		}
//-------------------------------------------------------------------------------------------------------
		// ISomeContract implementation.
		public void SomeOtherOperation(string Input)
		{
			CGlobals.Log.Write(CDebugHelper.GetMethodCallString());

			char[]						Chars=Input.ToCharArray();

			Array.Reverse(Chars);

			CGlobals.Log.Write(CDebugHelper.GetMethodCallString(),string.Format("SessionData - GET: {0}",MSessionData));

			string						Retval=new string(Chars);

			// Use the callback channel to return a reversed String.
			ICallbackContract			Callback=OperationContext.Current.GetCallbackChannel<ICallbackContract>();

			Callback.SomeCallbackOperation(Retval);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------