using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace InstanceDeactivationLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract(SessionMode=SessionMode.Required)]
	public interface IInstanceDeactivationContract
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract]
		void StartSession(int Value);
		[OperationContract]
		void BeforeCall(int Value);
		[OperationContract]
		void AfterCall(int Value);
		[OperationContract]
		void BeforeAndAfterCall(int Value);
		[OperationContract]
		void ManualRelease(int Value);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------