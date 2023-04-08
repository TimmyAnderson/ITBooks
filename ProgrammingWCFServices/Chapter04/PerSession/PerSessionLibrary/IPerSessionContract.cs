using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace PerSessionLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract(SessionMode=SessionMode.Allowed)]
	public interface IPerSessionContract
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract]
		CState GetState();
		[OperationContract]
		void SetState(CState State);
		[OperationContract]
		void PrintActualState();
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------