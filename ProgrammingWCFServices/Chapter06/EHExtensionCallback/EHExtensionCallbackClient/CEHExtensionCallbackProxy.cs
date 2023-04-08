using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using EHExtensionCallbackLibrary;
//-------------------------------------------------------------------------------------------------------
namespace EHExtensionCallbackClient
{
//-------------------------------------------------------------------------------------------------------
	public class CEHExtensionCallbackProxy : DuplexClientBase<IEHExtensionCallbackContract>, IEHExtensionCallbackContract
	{
//-------------------------------------------------------------------------------------------------------
		public CEHExtensionCallbackProxy(IEHExtensionCallbackCallback Callback, Binding ProxyBinding, string EndpointAddress)
			: base(new InstanceContext(Callback),ProxyBinding, new EndpointAddress(EndpointAddress))
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void Connect(string ClientName)
		{
			Console.WriteLine("CEHExtensionCallbackProxy.Connect() !");
			Channel.Connect(ClientName);
		}
//-------------------------------------------------------------------------------------------------------
		public void Disconnect()
		{
			Console.WriteLine("CEHExtensionCallbackProxy.Disconnect() !");
			Channel.Disconnect();
		}
//-------------------------------------------------------------------------------------------------------
		public void DoCallback(string Message)
		{
			Console.WriteLine("CEHExtensionCallbackProxy.DoCallback() !");
			Channel.DoCallback(Message);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------