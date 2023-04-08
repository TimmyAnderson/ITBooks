using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace ConcurrencyMultipleLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract(SessionMode=SessionMode.Required)]
	public interface IConcurrencyMultipleContract
	{
//-------------------------------------------------------------------------------------------------------
        [OperationContract]
		void SlowMethod(string Message);
        [OperationContract]
		void MethodImplTest(string Message);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------