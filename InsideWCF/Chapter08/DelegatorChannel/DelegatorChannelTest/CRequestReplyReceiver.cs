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
	internal sealed class CRequestReplyReceiver : ISomeContractRequestReply
	{
//-------------------------------------------------------------------------------------------------------
		public CRequestReplyReceiver()
		{
			CPrintHelper.Print("RECEIVER OBJECT: RequestReplyReceiver !", "ctor");
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// ISomeContract implementation.
		public String SomeOperation(string Input)
		{
			CPrintHelper.Print("RECEIVER OBJECT: RequestReplyReceiver !", String.Format("SomeOperation: {0}", Input));
	        
			Char[]			Chars=Input.ToCharArray();

			Array.Reverse(Chars);

			return(new string(Chars));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------