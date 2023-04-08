using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace UseSynchronizationContextLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract(SessionMode=SessionMode.Required)]
	public interface IUseSynchronizationContextContract
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract]
		void IncrementLabel();
		[OperationContract]
		void DecrementLabel();
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------