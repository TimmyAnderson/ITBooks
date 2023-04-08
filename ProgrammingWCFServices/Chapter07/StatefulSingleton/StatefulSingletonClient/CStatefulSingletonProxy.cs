using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using StatefulSingletonLibrary;
//-------------------------------------------------------------------------------------------------------
namespace StatefulSingletonClient
{
//-------------------------------------------------------------------------------------------------------
	public class CStatefulSingletonProxy : ClientBase<IStatefulSingletonContract>, IStatefulSingletonContract
	{
//-------------------------------------------------------------------------------------------------------
		public CStatefulSingletonProxy(Binding ProxyBinding, string EndpointAddress)
			: base(ProxyBinding, new EndpointAddress(EndpointAddress))
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void DoTransaction(string Value)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.DoTransaction(Value);
		}
//-------------------------------------------------------------------------------------------------------
		public void NonTransaction()
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.NonTransaction();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------