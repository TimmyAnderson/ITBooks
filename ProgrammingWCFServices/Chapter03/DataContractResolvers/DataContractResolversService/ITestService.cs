using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
using SharedLibrary1;
//-------------------------------------------------------------------------------------------------------
namespace DataContractResolversService
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract]
	public interface ITestService
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract]
		void ConnectionTest();
		[OperationContract]
		CNameBase ReceiveName(int Version);
		[OperationContract]
		CNameBaseGenerics<string> ReceiveGenericsName(int Version);
		[OperationContract]
		void SendName(CNameBase Name);
		[OperationContract]
		void SendGenericsName(CNameBaseGenerics<string> Name);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------