using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using ConcurrencyModesLibrary;
//-------------------------------------------------------------------------------------------------------
namespace ConcurrencyModesClient
{
//-------------------------------------------------------------------------------------------------------
	public class CConcurrencyModesProxy : DuplexClientBase<IConcurrencyModesContract>, IConcurrencyModesContract
	{
//-------------------------------------------------------------------------------------------------------
		public CConcurrencyModesProxy(IConcurrencyModesCallback Callback, Binding ProxyBinding, string EndpointAddress)
			: base(new InstanceContext(Callback),ProxyBinding, new EndpointAddress(EndpointAddress))
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void Connect(string ClientName)
		{
			Console.WriteLine("CConcurrencyModesProxy.Connect() !");
			Channel.Connect(ClientName);
		}
//-------------------------------------------------------------------------------------------------------
		public void Disconnect()
		{
			Console.WriteLine("CConcurrencyModesProxy.Disconnect() !");
			Channel.Disconnect();
		}
//-------------------------------------------------------------------------------------------------------
		public void SlowMethod(string Message, int Timeout)
		{
			Console.WriteLine("CConcurrencyModesProxy.SlowMethod() !");
			Channel.SlowMethod(Message,Timeout);
		}
//-------------------------------------------------------------------------------------------------------
		public void DoSynchroCallbackToJustSender(string Message, int Timeout)
		{
			Console.WriteLine("CConcurrencyModesProxy.DoSynchroCallback() !");
			Channel.DoSynchroCallbackToJustSender(Message,Timeout);
		}
//-------------------------------------------------------------------------------------------------------
		public void DoSynchroCallbackForAllClients(string Message, int Timeout)
		{
			Console.WriteLine("CConcurrencyModesProxy.DoSynchroCallback() !");
			Channel.DoSynchroCallbackForAllClients(Message,Timeout);
		}
//-------------------------------------------------------------------------------------------------------
		public void DoAsynchroCallback(string Message, int Timeout)
		{
			Console.WriteLine("CConcurrencyModesProxy.DoAsynchroCallback() !");
			Channel.DoAsynchroCallback(Message,Timeout);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------