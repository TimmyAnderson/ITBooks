using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using CallbackContractHierarchyLibrary;
//-------------------------------------------------------------------------------------------------------
namespace CallbackContractHierarchyClient
{
//-------------------------------------------------------------------------------------------------------
	public class CCallbackContractHierarchyProxy : DuplexClientBase<ICallbackContractHierarchyContract2>, ICallbackContractHierarchyContract2
	{
//-------------------------------------------------------------------------------------------------------
		public CCallbackContractHierarchyProxy(ICallbackContractHierarchyCallback2 Callback, Binding ProxyBinding, string EndpointAddress)
			: base(new InstanceContext(Callback),ProxyBinding, new EndpointAddress(EndpointAddress))
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void Connect(string ClientName)
		{
			Console.WriteLine("CCallbackContractHierarchyProxy.Connect() !");
			Channel.Connect(ClientName);
		}
//-------------------------------------------------------------------------------------------------------
		public void Disconnect()
		{
			Console.WriteLine("CCallbackContractHierarchyProxy.Disconnect() !");
			Channel.Disconnect();
		}
//-------------------------------------------------------------------------------------------------------
		public void CallCallback1(string Message, int Timeout)
		{
			Console.WriteLine("CCallbackContractHierarchyProxy.CallCallback1() !");
			Channel.CallCallback1(Message,Timeout);
		}
//-------------------------------------------------------------------------------------------------------
		public void CallCallback2(string MessagePart1, string MessagePart2, int Timeout)
		{
			Console.WriteLine("CCallbackContractHierarchyProxy.CallCallback2() !");
			Channel.CallCallback2(MessagePart1,MessagePart2,Timeout);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------