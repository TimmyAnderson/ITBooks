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
	internal class CRequestReplySessionReceiver : ISomeContractRequestReplySession
	{
//-------------------------------------------------------------------------------------------------------
		private string											MSessionData;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CRequestReplySessionReceiver()
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

			MSessionData=Input;

			CGlobals.Log.Write(CDebugHelper.GetMethodCallString(),string.Format("SessionData - SET: {0}",MSessionData));

			return(new string(Chars));
		}
//-------------------------------------------------------------------------------------------------------
		public string SomeOtherOperation(string Input)
		{
			CGlobals.Log.Write(CDebugHelper.GetMethodCallString());
	        
			Char[]			Chars=Input.ToCharArray();

			Array.Reverse(Chars);

			CGlobals.Log.Write(CDebugHelper.GetMethodCallString(),string.Format("SessionData - GET: {0}",MSessionData));

			return(new string(Chars));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------