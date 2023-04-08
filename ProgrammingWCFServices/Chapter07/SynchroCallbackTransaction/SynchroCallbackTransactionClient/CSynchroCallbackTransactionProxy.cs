using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using SynchroCallbackTransactionLibrary;
//-------------------------------------------------------------------------------------------------------
namespace SynchroCallbackTransactionClient
{
//-------------------------------------------------------------------------------------------------------
	public class CSynchroCallbackTransactionProxy : DuplexClientBase<ISynchroCallbackTransactionContract>, ISynchroCallbackTransactionContract
	{
//-------------------------------------------------------------------------------------------------------
		public CSynchroCallbackTransactionProxy(ISynchroCallbackTransactionCallback Callback, Binding ProxyBinding, string EndpointAddress)
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
		public void DoTransaction(string Message)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.DoTransaction(Message);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------