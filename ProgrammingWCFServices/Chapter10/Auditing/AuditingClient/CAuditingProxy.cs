using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using AuditingLibrary;
//-------------------------------------------------------------------------------------------------------
namespace AuditingClient
{
//-------------------------------------------------------------------------------------------------------
	public class CAuditingProxy : ClientBase<IAuditingContract>, IAuditingContract
	{
//-------------------------------------------------------------------------------------------------------
		public CAuditingProxy(Binding ProxyBinding, string EndpointAddress)
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
		public void DoAudit1()
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.DoAudit1();
		}
//-------------------------------------------------------------------------------------------------------
		public void DoAudit2()
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.DoAudit2();
		}
//-------------------------------------------------------------------------------------------------------
		public void DoAudit3()
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.DoAudit3();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------