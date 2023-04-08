using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using RequiringQueuingLibrary;
//-------------------------------------------------------------------------------------------------------
namespace RequiringQueuingClient
{
//-------------------------------------------------------------------------------------------------------
	public class CRequiringQueuingProxy : ClientBase<IRequiringQueuingContract>, IRequiringQueuingContract
	{
//-------------------------------------------------------------------------------------------------------
		public CRequiringQueuingProxy(Binding ProxyBinding, string EndpointAddress)
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