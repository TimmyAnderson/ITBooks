using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using CallbackFaultsLibrary;
//-------------------------------------------------------------------------------------------------------
namespace CallbackFaultsClient
{
//-------------------------------------------------------------------------------------------------------
	public class CCallbackFaultsProxy : DuplexClientBase<ICallbackFaultsContract>, ICallbackFaultsContract
	{
//-------------------------------------------------------------------------------------------------------
		public CCallbackFaultsProxy(ICallbackFaultsCallback Callback, Binding ProxyBinding, string EndpointAddress)
			: base(new InstanceContext(Callback),ProxyBinding, new EndpointAddress(EndpointAddress))
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void Connect(string ClientName)
		{
			Console.WriteLine("CCallbackFaultsProxy.Connect() !");
			Channel.Connect(ClientName);
		}
//-------------------------------------------------------------------------------------------------------
		public void Disconnect()
		{
			Console.WriteLine("CCallbackFaultsProxy.Disconnect() !");
			Channel.Disconnect();
		}
//-------------------------------------------------------------------------------------------------------
		public void SynchroNonFaultException(string Message, int Timeout)
		{
			Console.WriteLine("CCallbackFaultsProxy.SynchroNonFaultException() !");
			Channel.SynchroNonFaultException(Message,Timeout);
		}
//-------------------------------------------------------------------------------------------------------
		public void AsynchroNonFaultException(string Message, int Timeout)
		{
			Console.WriteLine("CCallbackFaultsProxy.AsynchroNonFaultException() !");
			Channel.AsynchroNonFaultException(Message,Timeout);
		}
//-------------------------------------------------------------------------------------------------------
		public void SynchroFaultException(string Message, int Timeout)
		{
			Console.WriteLine("CCallbackFaultsProxy.SynchroFaultException() !");
			Channel.SynchroFaultException(Message,Timeout);
		}
//-------------------------------------------------------------------------------------------------------
		public void AsynchroFaultException(string Message, int Timeout)
		{
			Console.WriteLine("CCallbackFaultsProxy.AsynchroFaultException() !");
			Channel.AsynchroFaultException(Message,Timeout);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------