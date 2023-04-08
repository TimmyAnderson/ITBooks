using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using ConcurrencyCallbackLibrary;
//-------------------------------------------------------------------------------------------------------
namespace ConcurrencyCallbackClient
{
//-------------------------------------------------------------------------------------------------------
	public class CConcurrencyCallbackProxy : DuplexClientBase<IConcurrencyCallbackContract>, IConcurrencyCallbackContract
	{
//-------------------------------------------------------------------------------------------------------
		public CConcurrencyCallbackProxy(IConcurrencyCallbackCallback Callback, Binding ProxyBinding, string EndpointAddress)
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
		public void CallCallbackWithoutWait(string Message)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.CallCallbackWithoutWait(Message);
		}
//-------------------------------------------------------------------------------------------------------
		public void CallCallbackWithWait(string Message)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.CallCallbackWithWait(Message);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------