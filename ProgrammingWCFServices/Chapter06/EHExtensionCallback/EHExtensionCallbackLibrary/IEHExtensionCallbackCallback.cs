using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace EHExtensionCallbackLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract]
	public interface IEHExtensionCallbackCallback
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract]
		[FaultContract(typeof(InvalidOperationException))]
		void OnEvent(string Message);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------