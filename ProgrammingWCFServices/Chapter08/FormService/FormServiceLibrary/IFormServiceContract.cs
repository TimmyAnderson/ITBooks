using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
//--------------------------------------------------------------------------------------------------------------------------------
namespace FormServiceLibrary
{
//--------------------------------------------------------------------------------------------------------------------------------
	[ServiceContract(SessionMode=SessionMode.Required)]
	public interface IFormServiceContract
	{
//--------------------------------------------------------------------------------------------------------------------------------
		[OperationContract]
		void IncrementLabel();
		[OperationContract]
		void DecrementLabel();
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------