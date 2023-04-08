using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.Threading;
using System.ServiceModel.Description;
using FTCSharedLibrary;
//-------------------------------------------------------------------------------------------------------
namespace TestLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceBehavior(ConcurrencyMode=ConcurrencyMode.Reentrant)]
	public class CTestFTCContract : ITestFTCContract
	{
//-------------------------------------------------------------------------------------------------------
		private string											MSessionData;
		private int												MCallCounter;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CTestFTCContract()
		{
			CSettings.Log.Write(CDebugHelper.GetConstructorCallString(),ELogRecordType.E_LRT_METHOD_CALL);
			MCallCounter=0;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public string SomeOperation_BEGIN(string Input)
		{
			CSettings.Log.Write(CDebugHelper.GetMethodCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			MCallCounter++;

			CSettings.Log.Write(string.Format("+++++++++++++ CALL COUNTER: {0} !",MCallCounter),ELogRecordType.E_LRT_SERVICE_CLIENT);

			char[]						Chars=Input.ToUpper().ToCharArray();

			Array.Reverse(Chars);

			string						Retval=new string(Chars);

			MSessionData=Input;

			CSettings.Log.Write(CDebugHelper.GetMethodCallString(),string.Format("SessionData - SET: {0}",MSessionData),ELogRecordType.E_LRT_SERVICE_CLIENT);

			// Use the callback channel to return a reversed String.
			ITestFTCCallback			Callback=OperationContext.Current.GetCallbackChannel<ITestFTCCallback>();

			string						CalRet=Callback.SomeCallbackOperation(Retval);

			CSettings.Log.Write((string.Format("$$$$$$$$$$$$$$$$$$ CALLBACK RESPONSE - SomeOperation_BEGIN(): '{0}' !",CalRet)),ELogRecordType.E_LRT_SERVICE_CLIENT);

			string						Out=string.Format("SomeOperation_BEGIN SPEAKING: {0} !",Input);

			return(Out);
		}
//-------------------------------------------------------------------------------------------------------
		public string SomeOperation_MIDDLE(string Input)
		{
			CSettings.Log.Write(CDebugHelper.GetMethodCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			MCallCounter++;

			CSettings.Log.Write(string.Format("+++++++++++++ CALL COUNTER: {0} !",MCallCounter),ELogRecordType.E_LRT_SERVICE_CLIENT);

			char[]						Chars=Input.ToCharArray();

			Array.Reverse(Chars);

			string						Retval=new string(Chars);

			MSessionData=Input;

			CSettings.Log.Write(CDebugHelper.GetMethodCallString(),string.Format("SessionData - SET: {0}",MSessionData),ELogRecordType.E_LRT_SERVICE_CLIENT);

			// Use the callback channel to return a reversed String.
			ITestFTCCallback			Callback=OperationContext.Current.GetCallbackChannel<ITestFTCCallback>();

			string						CalRet=Callback.SomeCallbackOperation(Retval);

			CSettings.Log.Write(string.Format("$$$$$$$$$$$$$$$$$$ CALLBACK RESPONSE - SomeOperation_MIDDLE(): '{0}' !",CalRet),ELogRecordType.E_LRT_SERVICE_CLIENT);

			string						Out=string.Format("SomeOperation_MIDDLE SPEAKING: {0} !",Input);

			return(Out);
		}
//-------------------------------------------------------------------------------------------------------
		public string SomeOperation_END(string Input)
		{
			CSettings.Log.Write(CDebugHelper.GetMethodCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			MCallCounter++;

			CSettings.Log.Write(string.Format("+++++++++++++ CALL COUNTER: {0} !",MCallCounter),ELogRecordType.E_LRT_SERVICE_CLIENT);

			char[]						Chars=Input.ToCharArray();

			Array.Reverse(Chars);

			string						Retval=new string(Chars);

			MSessionData=Input;

			CSettings.Log.Write(CDebugHelper.GetMethodCallString(),string.Format("SessionData - SET: {0}",MSessionData),ELogRecordType.E_LRT_SERVICE_CLIENT);

			// Use the callback channel to return a reversed String.
			ITestFTCCallback			Callback=OperationContext.Current.GetCallbackChannel<ITestFTCCallback>();

			string						CalRet=Callback.SomeCallbackOperation(Retval);

			CSettings.Log.Write(string.Format("$$$$$$$$$$$$$$$$$$ CALLBACK RESPONSE - SomeOperation_END(): '{0}' !",CalRet),ELogRecordType.E_LRT_SERVICE_CLIENT);

			string						Out=string.Format("SomeOperation_END SPEAKING: {0} !",Input);

			return(Out);
		}
//-------------------------------------------------------------------------------------------------------
		public void ThrowException(string Input)
		{
			CSettings.Log.Write(CDebugHelper.GetMethodCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			char[]						Chars=Input.ToCharArray();

			Array.Reverse(Chars);

			string						Retval=new string(Chars);

			MSessionData=Input;

			CSettings.Log.Write(CDebugHelper.GetMethodCallString(),string.Format("SessionData - SET: {0}",MSessionData),ELogRecordType.E_LRT_SERVICE_CLIENT);

			// Vytvorim Exception.
			InvalidOperationException	IO=new InvalidOperationException("SOME INVALID OPERATION FAULT EXCEPTION");

			// Vratim Exception.
			throw(new FaultException<InvalidOperationException>(IO,new FaultReason("SOME REASON !!!")));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------