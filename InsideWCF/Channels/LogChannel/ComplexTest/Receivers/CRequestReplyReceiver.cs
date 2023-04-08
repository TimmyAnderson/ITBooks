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
	internal sealed class CRequestReplyReceiver : ISomeContractRequestReply
	{
//-------------------------------------------------------------------------------------------------------
		public CRequestReplyReceiver()
		{
			CGlobals.Log.Write(CDebugHelper.GetConstructorCallString());
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// ISomeContract implementation.
		public string SomeOperation(string Input)
		{
			CGlobals.Log.Write(CDebugHelper.GetMethodCallString());
	        
			Char[]			Chars=Input.ToCharArray();

			Array.Reverse(Chars);

			return(new string(Chars));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------