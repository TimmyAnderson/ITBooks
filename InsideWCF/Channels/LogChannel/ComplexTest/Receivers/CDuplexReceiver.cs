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
	internal sealed class CDuplexReceiver : ISomeContractDuplex
	{
//-------------------------------------------------------------------------------------------------------
		public CDuplexReceiver()
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

			// Use the callback channel to return a reversed String.
			ICallbackContract			Callback=OperationContext.Current.GetCallbackChannel<ICallbackContract>();

			Callback.SomeCallbackOperation(Retval);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------