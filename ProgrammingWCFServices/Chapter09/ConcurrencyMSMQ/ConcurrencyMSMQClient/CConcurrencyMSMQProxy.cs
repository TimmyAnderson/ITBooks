using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using ConcurrencyMSMQLibrary;
//-------------------------------------------------------------------------------------------------------
namespace ConcurrencyMSMQClient
{
//-------------------------------------------------------------------------------------------------------
	public class CConcurrencyMSMQProxy : ClientBase<IConcurrencyMSMQContract>, IConcurrencyMSMQContract
	{
//-------------------------------------------------------------------------------------------------------
		public CConcurrencyMSMQProxy(Binding ProxyBinding, string EndpointAddress)
			: base(ProxyBinding, new EndpointAddress(EndpointAddress))
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void PrintText(string Message)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.PrintText(Message);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------