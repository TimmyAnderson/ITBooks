using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using DeliveryFailuresLibrary;
//-------------------------------------------------------------------------------------------------------
namespace DeliveryFailuresClient
{
//-------------------------------------------------------------------------------------------------------
	public class CDeliveryFailuresProxy : ClientBase<IDeliveryFailuresContract>, IDeliveryFailuresContract
	{
//-------------------------------------------------------------------------------------------------------
		public CDeliveryFailuresProxy(Binding ProxyBinding, string EndpointAddress)
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
		public void ThrowExceptionWithTransaction(string Message)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.ThrowExceptionWithTransaction(Message);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------