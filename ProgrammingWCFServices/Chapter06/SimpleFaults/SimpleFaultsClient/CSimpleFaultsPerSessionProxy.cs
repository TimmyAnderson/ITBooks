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
	public class CSimpleFaultsPerSessionProxy : ClientBase<ISimpleFaultsPerSessionContract>, ISimpleFaultsPerSessionContract
	{
//-------------------------------------------------------------------------------------------------------
		public CSimpleFaultsPerSessionProxy(Binding ProxyBinding, string EndpointAddress)
			: base(ProxyBinding, new EndpointAddress(EndpointAddress))
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void IsAlive()
		{
			Console.WriteLine("CSimpleFaultsPerSessionProxy.IsAlive() !");
			Channel.IsAlive();
		}
//-------------------------------------------------------------------------------------------------------
		public void ThrowSimpleException()
		{
			Console.WriteLine("CSimpleFaultsPerSessionProxy.ThrowSimpleException() !");
			Channel.ThrowSimpleException();
		}
//-------------------------------------------------------------------------------------------------------
		public void ThrowFaultException()
		{
			Console.WriteLine("CSimpleFaultsPerSessionProxy.ThrowFaultException() !");
			Channel.ThrowFaultException();
		}
//-------------------------------------------------------------------------------------------------------
		public void ThrowCMyFaultException()
		{
			Console.WriteLine("CSimpleFaultsPerSessionProxy.ThrowCMyFaultException() !");
			Channel.ThrowCMyFaultException();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------