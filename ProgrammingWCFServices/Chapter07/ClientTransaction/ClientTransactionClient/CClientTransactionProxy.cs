using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using ClientTransactionLibrary;
//-------------------------------------------------------------------------------------------------------
namespace ClientTransactionClient
{
//-------------------------------------------------------------------------------------------------------
	public class CClientTransactionProxy : ClientBase<IClientTransactionContract>, IClientTransactionContract
	{
//-------------------------------------------------------------------------------------------------------
		public CClientTransactionProxy(Binding ProxyBinding, string EndpointAddress)
			: base(ProxyBinding, new EndpointAddress(EndpointAddress))
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void TFAllowed(string Value)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.TFAllowed(Value);
		}
//-------------------------------------------------------------------------------------------------------
		public void TFNotAllowed(string Value)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.TFNotAllowed(Value);
		}
//-------------------------------------------------------------------------------------------------------
		public void TFMandatory(string Value)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.TFMandatory(Value);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------