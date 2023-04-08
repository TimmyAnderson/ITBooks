using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using ErrorHandlingExtensionsLibrary;
//-------------------------------------------------------------------------------------------------------
namespace ErrorHandlingExtensionsClient
{
//-------------------------------------------------------------------------------------------------------
	public class CErrorHandlingExtensionsProxy : ClientBase<IErrorHandlingExtensionsContract>, IErrorHandlingExtensionsContract
	{
//-------------------------------------------------------------------------------------------------------
		public CErrorHandlingExtensionsProxy(Binding ProxyBinding, string EndpointAddress)
			: base(ProxyBinding, new EndpointAddress(EndpointAddress))
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void IsAlive()
		{
			Console.WriteLine("CErrorHandlingExtensionsProxy.IsAlive() !");
			Channel.IsAlive();
		}
//-------------------------------------------------------------------------------------------------------
		public void CaughtException()
		{
			Console.WriteLine("CErrorHandlingExtensionsProxy.CaughtException() !");
			Channel.CaughtException();
		}
//-------------------------------------------------------------------------------------------------------
		public void PromoteAllException()
		{
			Console.WriteLine("CErrorHandlingExtensionsProxy.PromoteAllException() !");
			Channel.PromoteAllException();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------