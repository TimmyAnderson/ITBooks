using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace DCDelegatesSharedLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract]
	public interface ITestService
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract]
		void ConnectionTest();
		[OperationContract]
		DMyDelegate ReceiveEmptyDelegate();
		[OperationContract]
		DMyDelegate ReceiveDelegateToStaticMethod();
		[OperationContract]
		DMyDelegate ReceiveDelegateToInstanceMethod();
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------