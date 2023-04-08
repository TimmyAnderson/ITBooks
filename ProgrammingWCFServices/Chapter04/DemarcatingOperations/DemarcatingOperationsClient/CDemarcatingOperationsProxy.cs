using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using DemarcatingOperationsLibrary;
//-------------------------------------------------------------------------------------------------------
namespace DemarcatingOperationsClient
{
//-------------------------------------------------------------------------------------------------------
	public class CDemarcatingOperationsProxy : ClientBase<IDemarcatingOperationsContract>, IDemarcatingOperationsContract
	{
//-------------------------------------------------------------------------------------------------------
		public CDemarcatingOperationsProxy(Binding ProxyBinding, string EndpointAddress)
			: base(ProxyBinding, new EndpointAddress(EndpointAddress))
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void Start1()
		{
			Console.WriteLine("CDemarcatingOperationsProxy.Start1() called !");
			Channel.Start1();
		}
//-------------------------------------------------------------------------------------------------------
		public void Start2()
		{
			Console.WriteLine("CDemarcatingOperationsProxy.Start2() called !");
			Channel.Start2();
		}
//-------------------------------------------------------------------------------------------------------
		public void Inside1()
		{
			Console.WriteLine("CDemarcatingOperationsProxy.Inside1() called !");
			Channel.Inside1();
		}
//-------------------------------------------------------------------------------------------------------
		public void Inside2()
		{
			Console.WriteLine("CDemarcatingOperationsProxy.Inside2() called !");
			Channel.Inside2();
		}
//-------------------------------------------------------------------------------------------------------
		public void Inside3()
		{
			Console.WriteLine("CDemarcatingOperationsProxy.Inside3() called !");
			Channel.Inside3();
		}
//-------------------------------------------------------------------------------------------------------
		public void Terminate1()
		{
			Console.WriteLine("CDemarcatingOperationsProxy.Terminate1() called !");
			Channel.Terminate1();
		}
//-------------------------------------------------------------------------------------------------------
		public void Terminate2()
		{
			Console.WriteLine("CDemarcatingOperationsProxy.Terminate2() called !");
			Channel.Terminate2();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------