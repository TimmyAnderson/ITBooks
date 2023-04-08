using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using AuthorizationLibrary;
//-------------------------------------------------------------------------------------------------------
namespace AuthorizationClient
{
//-------------------------------------------------------------------------------------------------------
	public class CAuthorizationProxy : ClientBase<IAuthorizationContract>, IAuthorizationContract
	{
//-------------------------------------------------------------------------------------------------------
		public CAuthorizationProxy(Binding ProxyBinding, string EndpointAddress)
			: base(ProxyBinding, new EndpointAddress(EndpointAddress))
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
		public void AutoAuthorization1()
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.AutoAuthorization1();
		}
//-------------------------------------------------------------------------------------------------------
		public void AutoAuthorization2()
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.AutoAuthorization2();
		}
//-------------------------------------------------------------------------------------------------------
		public void AutoAuthorization3()
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.AutoAuthorization3();
		}
//-------------------------------------------------------------------------------------------------------
		public void ManualAuthorization1()
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.ManualAuthorization1();
		}
//-------------------------------------------------------------------------------------------------------
		public void ManualAuthorization2()
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.ManualAuthorization2();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------