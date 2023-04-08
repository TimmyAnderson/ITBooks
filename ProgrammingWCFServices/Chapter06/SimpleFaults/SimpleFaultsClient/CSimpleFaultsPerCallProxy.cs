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
	public class CSimpleFaultsPerCallProxy : ClientBase<ISimpleFaultsPerCallContract>, ISimpleFaultsPerCallContract
	{
//-------------------------------------------------------------------------------------------------------
		public CSimpleFaultsPerCallProxy(Binding ProxyBinding, string EndpointAddress)
			: base(ProxyBinding, new EndpointAddress(EndpointAddress))
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void IsAlive()
		{
			Console.WriteLine("CSimpleFaultsPerCallProxy.IsAlive() !");
			Channel.IsAlive();
		}
//-------------------------------------------------------------------------------------------------------
		public void ThrowSimpleException()
		{
			Console.WriteLine("CSimpleFaultsPerCallProxy.ThrowSimpleException() !");
			Channel.ThrowSimpleException();
		}
//-------------------------------------------------------------------------------------------------------
		public void ThrowFaultException()
		{
			Console.WriteLine("CSimpleFaultsPerCallProxy.ThrowFaultException() !");
			Channel.ThrowFaultException();
		}
//-------------------------------------------------------------------------------------------------------
		public void ThrowCMyFaultException()
		{
			Console.WriteLine("CSimpleFaultsPerCallProxy.ThrowCMyFaultException() !");
			Channel.ThrowCMyFaultException();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------