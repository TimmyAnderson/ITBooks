using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace ChannelFaultingHost
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract(SessionMode=SessionMode.Allowed)]
	public interface IFaultTestService
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract]
		void Dummy();
//-------------------------------------------------------------------------------------------------------
		[OperationContract]
		void NoFaultContractStandardException();
		[OperationContract]
		void NoFaultContractFaultException();
		[OperationContract]
		void NoFaultContractTypedFaultException();
		[OperationContract]
		[FaultContract(typeof(InvalidOperationException))]
		void WithFaultContractStandardException();
		[OperationContract]
		[FaultContract(typeof(InvalidOperationException))]
		void WithFaultContractFaultException();
		[OperationContract]
		[FaultContract(typeof(InvalidOperationException))]
		void WithFaultContractTypedFaultException();
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------