using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using ConcurrencyReentrantLibrary;
//-------------------------------------------------------------------------------------------------------
namespace ConcurrencyReentrantClient
{
//-------------------------------------------------------------------------------------------------------
	public class CConcurrencyReentrantProxy : DuplexClientBase<IConcurrencyReentrantContract>, IConcurrencyReentrantContract
	{
//-------------------------------------------------------------------------------------------------------
		public CConcurrencyReentrantProxy(IConcurrencyReentrantCallback Callback, Binding ProxyBinding, string EndpointAddress)
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
		public void SlowMethod(string Message)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.SlowMethod(Message);
		}
//-------------------------------------------------------------------------------------------------------
		public void DoCallback(string Message)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.DoCallback(Message);
		}
//-------------------------------------------------------------------------------------------------------
		public void DoSlowCallback(string Message)
		{
			Channel.DoSlowCallback(Message);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------