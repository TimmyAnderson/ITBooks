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
	internal sealed class COneWaySessionReceiver : ISomeContractOneWaySession
	{
//-------------------------------------------------------------------------------------------------------
		private string											MSessionData;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		internal COneWaySessionReceiver()
		{
			CGlobals.Log.Write(CDebugHelper.GetConstructorCallString());
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void SomeOperation(string Input)
		{
			CGlobals.Log.Write(CDebugHelper.GetMethodCallString());

			MSessionData=Input;

			CGlobals.Log.Write(CDebugHelper.GetMethodCallString(),string.Format("SessionData - SET: {0}",MSessionData));
		}
//-------------------------------------------------------------------------------------------------------
		public void SomeOtherOperation(string Input)
		{
			CGlobals.Log.Write(CDebugHelper.GetMethodCallString());

			CGlobals.Log.Write(CDebugHelper.GetMethodCallString(),string.Format("SessionData - GET: {0}",MSessionData));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------