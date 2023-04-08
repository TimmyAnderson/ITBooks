using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using RawMessageSenderLibrary;
//-------------------------------------------------------------------------------------------------------
namespace RawMessageSenderClient
{
//-------------------------------------------------------------------------------------------------------
	public class CRawMessageSenderProxy : ClientBase<IRawMessageSenderContract>, IRawMessageSenderContract
	{
//-------------------------------------------------------------------------------------------------------
		public CRawMessageSenderProxy(Binding ProxyBinding, string EndpointAddress)
			: base(ProxyBinding, new EndpointAddress(EndpointAddress))
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void SubmitOrder(Message Order)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.SubmitOrder(Order);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------