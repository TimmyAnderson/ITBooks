using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using ConcurrencyMultipleLibrary;
//-------------------------------------------------------------------------------------------------------
namespace ConcurrencyMultipleClient
{
//-------------------------------------------------------------------------------------------------------
	public class CConcurrencyMultipleProxy : ClientBase<IConcurrencyMultipleContract>, IConcurrencyMultipleContract
	{
//-------------------------------------------------------------------------------------------------------
		public CConcurrencyMultipleProxy(Binding ProxyBinding, string EndpointAddress)
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
		public void MethodImplTest(string Message)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.MethodImplTest(Message);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------