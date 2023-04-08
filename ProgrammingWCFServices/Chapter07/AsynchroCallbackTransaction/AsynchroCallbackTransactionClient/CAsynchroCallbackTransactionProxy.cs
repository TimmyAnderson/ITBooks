using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using AsynchroCallbackTransactionLibrary;
//-------------------------------------------------------------------------------------------------------
namespace AsynchroCallbackTransactionClient
{
//-------------------------------------------------------------------------------------------------------
	public class CAsynchroCallbackTransactionProxy : DuplexClientBase<IAsynchroCallbackTransactionContract>, IAsynchroCallbackTransactionContract
	{
//-------------------------------------------------------------------------------------------------------
		public CAsynchroCallbackTransactionProxy(IAsynchroCallbackTransactionCallback Callback, Binding ProxyBinding, string EndpointAddress)
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
		public void DoTransaction(string Message, int Timeout)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.DoTransaction(Message,Timeout);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------