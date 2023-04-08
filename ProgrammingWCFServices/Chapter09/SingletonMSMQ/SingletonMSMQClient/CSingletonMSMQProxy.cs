using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using SingletonMSMQLibrary;
//-------------------------------------------------------------------------------------------------------
namespace SingletonMSMQClient
{
//-------------------------------------------------------------------------------------------------------
	public class CSingletonMSMQProxy : ClientBase<ISingletonMSMQContract>, ISingletonMSMQContract
	{
//-------------------------------------------------------------------------------------------------------
		public CSingletonMSMQProxy(Binding ProxyBinding, string EndpointAddress)
			: base(ProxyBinding, new EndpointAddress(EndpointAddress))
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void DoTransaction(string Message)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.DoTransaction(Message);
		}
//-------------------------------------------------------------------------------------------------------
		public void NonTransaction(string Message)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.NonTransaction(Message);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------