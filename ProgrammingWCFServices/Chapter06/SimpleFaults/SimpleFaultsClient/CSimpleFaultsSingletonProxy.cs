using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using SimpleFaultsLibrary;
//-------------------------------------------------------------------------------------------------------
namespace SimpleFaultsClient
{
//-------------------------------------------------------------------------------------------------------
	public class CSimpleFaultsSingletonProxy : ClientBase<ISimpleFaultsSingletonContract>, ISimpleFaultsSingletonContract
	{
//-------------------------------------------------------------------------------------------------------
		public CSimpleFaultsSingletonProxy(Binding ProxyBinding, string EndpointAddress)
			: base(ProxyBinding, new EndpointAddress(EndpointAddress))
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void IsAlive()
		{
			Console.WriteLine("CSimpleFaultsSingletonProxy.IsAlive() !");
			Channel.IsAlive();
		}
//-------------------------------------------------------------------------------------------------------
		public void ThrowSimpleException()
		{
			Console.WriteLine("CSimpleFaultsSingletonProxy.ThrowSimpleException() !");
			Channel.ThrowSimpleException();
		}
//-------------------------------------------------------------------------------------------------------
		public void ThrowFaultException()
		{
			Console.WriteLine("CSimpleFaultsSingletonProxy.ThrowFaultException() !");
			Channel.ThrowFaultException();
		}
//-------------------------------------------------------------------------------------------------------
		public void ThrowCMyFaultException()
		{
			Console.WriteLine("CSimpleFaultsSingletonProxy.ThrowCMyFaultException() !");
			Channel.ThrowCMyFaultException();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------