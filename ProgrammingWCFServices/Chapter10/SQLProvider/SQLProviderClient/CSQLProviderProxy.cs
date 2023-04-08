using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using SQLProviderLibrary;
//-------------------------------------------------------------------------------------------------------
namespace SQLProviderClient
{
//-------------------------------------------------------------------------------------------------------
	public class CSQLProviderProxy : ClientBase<ISQLProviderContract>, ISQLProviderContract
	{
//-------------------------------------------------------------------------------------------------------
		public CSQLProviderProxy(Binding ProxyBinding, string EndpointAddress)
			: base(ProxyBinding, new EndpointAddress(new Uri(EndpointAddress),new DnsEndpointIdentity("TestSQL")))
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void IsAlive()
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.IsAlive();
		}
//-------------------------------------------------------------------------------------------------------
		public void AutoAuthorization()
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.AutoAuthorization();
		}
//-------------------------------------------------------------------------------------------------------
		public void ManualAuthorization()
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.ManualAuthorization();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------