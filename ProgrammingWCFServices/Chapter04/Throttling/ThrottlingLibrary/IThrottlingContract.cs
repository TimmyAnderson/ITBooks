using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace ThrottlingLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract(SessionMode=SessionMode.Required)]
	public interface IThrottlingContract
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract]
		void StartInstance();
		[OperationContract]
		void DropInstance();
		[OperationContract]
		void SlowMethod(int Timeout);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------