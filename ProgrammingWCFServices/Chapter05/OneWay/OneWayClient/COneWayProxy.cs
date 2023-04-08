using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using OneWayLibrary;
//-------------------------------------------------------------------------------------------------------
namespace OneWayClient
{
//-------------------------------------------------------------------------------------------------------
	public class COneWayProxy : ClientBase<IOneWayContract>, IOneWayContract
	{
//-------------------------------------------------------------------------------------------------------
		public COneWayProxy(Binding ProxyBinding, string EndpointAddress)
			: base(ProxyBinding, new EndpointAddress(EndpointAddress))
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void MethodWithoutException()
		{
			Console.WriteLine("COneWayProxy.MethodWithoutException() !");
			Channel.MethodWithoutException();
		}
//-------------------------------------------------------------------------------------------------------
		public void MethodWithException()
		{
			Console.WriteLine("COneWayProxy.MethodWithException() !");
			Channel.MethodWithException();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------