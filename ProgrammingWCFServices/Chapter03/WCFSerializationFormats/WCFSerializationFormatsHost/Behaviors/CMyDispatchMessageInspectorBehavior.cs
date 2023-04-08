using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.ServiceModel.Description;
using System.ServiceModel.Dispatcher;
//-------------------------------------------------------------------------------------------------------
namespace WCFSerializationFormatsHost
{
//-------------------------------------------------------------------------------------------------------
	public class CMyDispatchMessageInspectorBehavior : IContractBehavior
	{
//-------------------------------------------------------------------------------------------------------
		public void AddBindingParameters(ContractDescription ContractDescription, ServiceEndpoint Endpoint, BindingParameterCollection BindingParameters)
		{
		}
//-------------------------------------------------------------------------------------------------------
		public void ApplyClientBehavior(ContractDescription ContractDescription, ServiceEndpoint Endpoint, ClientRuntime ClientRuntime)
		{
		}
//-------------------------------------------------------------------------------------------------------
		public void ApplyDispatchBehavior(ContractDescription ContractDescription, ServiceEndpoint Endpoint, DispatchRuntime DispatchRuntime)
		{
			DispatchRuntime.MessageInspectors.Add(new CMyDispatchMessageInspector());

			Console.WriteLine("CMyDispatchMessageInspector ATTACHED !");
		}
//-------------------------------------------------------------------------------------------------------
		public void Validate(ContractDescription ContractDescription, ServiceEndpoint Endpoint)
		{
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------