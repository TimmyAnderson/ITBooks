using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using AutoCompleteSessionCloseLibrary;
//-------------------------------------------------------------------------------------------------------
namespace AutoCompleteSessionCloseClient
{
//-------------------------------------------------------------------------------------------------------
	public class CAutoCompleteSessionCloseProxy : ClientBase<IAutoCompleteSessionCloseContract>, IAutoCompleteSessionCloseContract
	{
//-------------------------------------------------------------------------------------------------------
		public CAutoCompleteSessionCloseProxy(Binding ProxyBinding, string EndpointAddress)
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
		public void ThrowException()
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.ThrowException();
		}
//-------------------------------------------------------------------------------------------------------
		public void FinishTransaction(string Value)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.FinishTransaction(Value);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------