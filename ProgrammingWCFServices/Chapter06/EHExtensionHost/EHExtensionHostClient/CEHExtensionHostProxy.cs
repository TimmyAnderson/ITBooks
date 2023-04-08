using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using EHExtensionHostLibrary;
//-------------------------------------------------------------------------------------------------------
namespace EHExtensionHostClient
{
//-------------------------------------------------------------------------------------------------------
	public class CEHExtensionHostProxy : ClientBase<IEHExtensionHostContract>, IEHExtensionHostContract
	{
//-------------------------------------------------------------------------------------------------------
		public CEHExtensionHostProxy(Binding ProxyBinding, string EndpointAddress)
			: base(ProxyBinding, new EndpointAddress(EndpointAddress))
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void IsAlive()
		{
			Console.WriteLine("CEHExtensionHostProxy.IsAlive() !");
			Channel.IsAlive();
		}
//-------------------------------------------------------------------------------------------------------
		public void ThrowException()
		{
			Console.WriteLine("CEHExtensionHostProxy.ThrowException() !");
			Channel.ThrowException();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------