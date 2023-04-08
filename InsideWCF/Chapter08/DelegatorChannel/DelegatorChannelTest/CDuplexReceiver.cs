using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.Threading;
using System.Transactions;
using System.ServiceModel.Description;
using DelegatorChannel;
//-------------------------------------------------------------------------------------------------------
namespace DelegatorChannelTest
{
//-------------------------------------------------------------------------------------------------------
	internal sealed class CDuplexReceiver : ISomeContractDuplex
	{
//-------------------------------------------------------------------------------------------------------
		public CDuplexReceiver()
		{
			CPrintHelper.Print("RECEIVER OBJECT: DuplexReceiver !", "ctor");
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// ISomeContract implementation.
		public void SomeOperation(string Input)
		{
			CPrintHelper.Print("RECEIVER OBJECT: DuplexReceiver !", String.Format("SomeOperation: {0}", Input));

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