using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using SimpleCallbackLibrary;
//-------------------------------------------------------------------------------------------------------
namespace SimpleCallbackClient
{
//-------------------------------------------------------------------------------------------------------
	public class CSimpleCallbackProxy : DuplexClientBase<ISimpleCallbackContract>, ISimpleCallbackContract
	{
//-------------------------------------------------------------------------------------------------------
		public CSimpleCallbackProxy(ISimpleCallbackCallback Callback, Binding ProxyBinding, string EndpointAddress)
			: base(new InstanceContext(Callback),ProxyBinding, new EndpointAddress(EndpointAddress))
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void Connect(string ClientName)
		{
			Console.WriteLine("CSimpleCallbackClientProxy.Connect() !");
			Channel.Connect(ClientName);
		}
//-------------------------------------------------------------------------------------------------------
		public void Disconnect()
		{
			Console.WriteLine("CSimpleCallbackClientProxy.Disconnect() !");
			Channel.Disconnect();
		}
//-------------------------------------------------------------------------------------------------------
		public void DoSomething(string ClientName, string Message, int Timeout)
		{
			Console.WriteLine("COneWayProxy.DoSomething() !");
			Channel.DoSomething(ClientName,Message,Timeout);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------