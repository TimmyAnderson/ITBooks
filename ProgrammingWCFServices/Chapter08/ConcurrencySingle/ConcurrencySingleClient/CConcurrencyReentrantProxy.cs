using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using ConcurrencySingleLibrary;
//-------------------------------------------------------------------------------------------------------
namespace ConcurrencySingleClient
{
//-------------------------------------------------------------------------------------------------------
	public class CConcurrencySingleProxy : ClientBase<IConcurrencySingleContract>, IConcurrencySingleContract
	{
//-------------------------------------------------------------------------------------------------------
		public CConcurrencySingleProxy(Binding ProxyBinding, string EndpointAddress)
			: base(ProxyBinding, new EndpointAddress(EndpointAddress))
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void SlowMethod(string Message)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.SlowMethod(Message);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------