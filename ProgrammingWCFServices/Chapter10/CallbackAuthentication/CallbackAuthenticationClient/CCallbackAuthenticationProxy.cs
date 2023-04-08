using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using CallbackAuthenticationLibrary;
//-------------------------------------------------------------------------------------------------------
namespace CallbackAuthenticationClient
{
//-------------------------------------------------------------------------------------------------------
	public class CCallbackAuthenticationProxy : DuplexClientBase<ICallbackAuthenticationContract>, ICallbackAuthenticationContract
	{
//-------------------------------------------------------------------------------------------------------
		public CCallbackAuthenticationProxy(ICallbackAuthenticationCallback Callback, Binding ProxyBinding, string EndpointAddress)
			: base(new InstanceContext(Callback),ProxyBinding, new EndpointAddress(EndpointAddress))
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void Connect(string ClientName)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.Connect(ClientName);
		}
//-------------------------------------------------------------------------------------------------------
		public void Disconnect()
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.Disconnect();
		}
//-------------------------------------------------------------------------------------------------------
		public void DoCallback()
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.DoCallback();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------