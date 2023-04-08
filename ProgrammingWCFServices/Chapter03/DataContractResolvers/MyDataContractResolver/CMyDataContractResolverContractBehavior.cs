using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel.Description;
using System.ServiceModel.Channels;
using System.ServiceModel.Dispatcher;
//-------------------------------------------------------------------------------------------------------
namespace MyDataContractResolver
{
//-------------------------------------------------------------------------------------------------------
	public class CMyDataContractResolverContractBehavior : IContractBehavior
	{
//-------------------------------------------------------------------------------------------------------
		private CMyDataContractResolver							MResolver;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CMyDataContractResolverContractBehavior(CMyDataContractResolver Resolver)
		{
			MResolver=Resolver;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void AddBindingParameters(ContractDescription ContractDescription, ServiceEndpoint Endpoint, BindingParameterCollection BindingParameters)
		{
		}
//-------------------------------------------------------------------------------------------------------
		public void Validate(ContractDescription ContractDescription, ServiceEndpoint Endpoint)
		{
		}
//-------------------------------------------------------------------------------------------------------
		public void ApplyClientBehavior(ContractDescription ContractDescription, ServiceEndpoint Endpoint, ClientRuntime ClientRuntime)
		{
			foreach(OperationDescription Operation in ContractDescription.Operations)
			{
				DataContractSerializerOperationBehavior		DCSB=Operation.Behaviors.Find<DataContractSerializerOperationBehavior>();

				DCSB.DataContractResolver=MResolver;
			}
		}
//-------------------------------------------------------------------------------------------------------
		public void ApplyDispatchBehavior(ContractDescription ContractDescription, ServiceEndpoint Endpoint, DispatchRuntime DispatchRuntime)
		{
			foreach(OperationDescription Operation in ContractDescription.Operations)
			{
				DataContractSerializerOperationBehavior		DCSB=Operation.Behaviors.Find<DataContractSerializerOperationBehavior>();

				DCSB.DataContractResolver=MResolver;
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------