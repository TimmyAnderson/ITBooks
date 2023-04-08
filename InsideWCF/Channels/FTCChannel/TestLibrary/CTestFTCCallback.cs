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
	public class CTestFTCCallback : ITestFTCCallback
	{
//-------------------------------------------------------------------------------------------------------
		public CTestFTCCallback()
		{
			CSettings.Log.Write(CDebugHelper.GetConstructorCallString(),ELogRecordType.E_LRT_METHOD_CALL);
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public string SomeCallbackOperation(string Input)
		{
			CSettings.Log.Write(CDebugHelper.GetMethodCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			string			In=string.Format("--------------------- CALLBACK CALLED - Parameter Input: {0} !",Input);

			CSettings.Log.Write(In,ELogRecordType.E_LRT_SERVICE_CLIENT);

			string			Out=string.Format("HI {0} ! HERE IS CALLBACK !",Input);

			return(Out);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------