using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using FaultContractsLibrary;
//-------------------------------------------------------------------------------------------------------
namespace FaultContractsClient
{
//-------------------------------------------------------------------------------------------------------
	public class CFaultContractsProxy : ClientBase<IFaultContractsContract>, IFaultContractsContract
	{
//-------------------------------------------------------------------------------------------------------
		public CFaultContractsProxy(Binding ProxyBinding, string EndpointAddress)
			: base(ProxyBinding, new EndpointAddress(EndpointAddress))
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void IsAlive()
		{
			Console.WriteLine("CFaultContractsProxy.IsAlive() !");
			Channel.IsAlive();
		}
//-------------------------------------------------------------------------------------------------------
		public void ThrowCFaultDetailsException()
		{
			Console.WriteLine("CFaultContractsProxy.ThrowCFaultDetailsException() !");
			Channel.ThrowCFaultDetailsException();
		}
//-------------------------------------------------------------------------------------------------------
		public void ThrowInvalidOperationException()
		{
			Console.WriteLine("CFaultContractsProxy.ThrowInvalidOperationException() !");
			Channel.ThrowInvalidOperationException();
		}
//-------------------------------------------------------------------------------------------------------
		public void ThrowInvalidOperationAsFaultException()
		{
			Console.WriteLine("CFaultContractsProxy.ThrowInvalidOperationAsFaultException() !");
			Channel.ThrowInvalidOperationAsFaultException();
		}
//-------------------------------------------------------------------------------------------------------
		public void ThrowFaultException()
		{
			Console.WriteLine("CFaultContractsProxy.ThrowFaultException() !");
			Channel.ThrowFaultException();
		}
//-------------------------------------------------------------------------------------------------------
		public void ThrowExceptionDetail()
		{
			Console.WriteLine("CFaultContractsProxy.ThrowExceptionDetail() !");
			Channel.ThrowExceptionDetail();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------