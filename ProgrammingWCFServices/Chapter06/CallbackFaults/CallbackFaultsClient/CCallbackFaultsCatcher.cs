using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using CallbackFaultsLibrary;
//-------------------------------------------------------------------------------------------------------
namespace CallbackFaultsClient
{
//-------------------------------------------------------------------------------------------------------
	class CCallbackFaultsCatcher : ICallbackFaultsCallback
	{
//-------------------------------------------------------------------------------------------------------
		public void NonFaultCallback(string Message)
		{
			Console.WriteLine(string.Format("NonFaultCallback() - FROM SERVER: {0} !",Message));

			throw(new Exception("THIS IS NON FAULT EXCEPTION"));
		}
//-------------------------------------------------------------------------------------------------------
		public void FaultCallback(string Message)
		{
			Console.WriteLine(string.Format("FaultCallback() - FROM SERVER: {0} !",Message));

			CFaultDetails			FD=new CFaultDetails("THIS IS FAULT EXCEPTION");

			throw(new FaultException<CFaultDetails>(FD));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------