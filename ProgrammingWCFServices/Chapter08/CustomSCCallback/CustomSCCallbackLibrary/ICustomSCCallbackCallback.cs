using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace CustomSCCallbackLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract]
	public interface ICustomSCCallbackCallback
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract]
		void OnCallback(string Message);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------