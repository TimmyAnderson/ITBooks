using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using HelloWCFLibrary;
//-------------------------------------------------------------------------------------------------------
namespace HelloWCFManualClient
{
//-------------------------------------------------------------------------------------------------------
	public class CHelloWCFProxy : ClientBase<IHelloWCFContract>, IHelloWCFContract
	{
//-------------------------------------------------------------------------------------------------------
		public CHelloWCFProxy(Binding ProxyBinding, string EndpointAddress)
			: base(ProxyBinding, new EndpointAddress(EndpointAddress))
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void Say(string Input)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.Say(Input);
		}
//-------------------------------------------------------------------------------------------------------
		public void SayWith2Params(string Input1, string Input2)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.SayWith2Params(Input1, Input2);
		}
//-------------------------------------------------------------------------------------------------------
		public void SayPurchaseOrder(string SomeParam, CPurchaseOrder PO)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.SayPurchaseOrder(SomeParam, PO);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------