using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using MessageSecurityLibrary;
//-------------------------------------------------------------------------------------------------------
namespace MessageSecurityClient
{
//-------------------------------------------------------------------------------------------------------
	public class CMessageSecurityProxy : ClientBase<IMessageSecurityContract>, IMessageSecurityContract
	{
//-------------------------------------------------------------------------------------------------------
		public CMessageSecurityProxy(Binding ProxyBinding, string EndpointAddress)
			// !!!!!!!!! Pozor treba nastavit DNS.
			: base(ProxyBinding, new EndpointAddress(new Uri(EndpointAddress),new DnsEndpointIdentity("TestMS")))
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