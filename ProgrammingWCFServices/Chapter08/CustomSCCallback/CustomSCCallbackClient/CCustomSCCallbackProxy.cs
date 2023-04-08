using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using CustomSCCallbackLibrary;
//-------------------------------------------------------------------------------------------------------
namespace CustomSCCallbackClient
{
//-------------------------------------------------------------------------------------------------------
	public class CCustomSCCallbackProxy : DuplexClientBase<ICustomSCCallbackContract>, ICustomSCCallbackContract
	{
//-------------------------------------------------------------------------------------------------------
		public CCustomSCCallbackProxy(ICustomSCCallbackCallback Callback, Binding ProxyBinding, string EndpointAddress)
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
		public void CallCallback(string Message)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.CallCallback(Message);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------