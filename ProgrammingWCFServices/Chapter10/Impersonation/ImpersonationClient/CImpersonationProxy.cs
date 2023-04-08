using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using ImpersonationLibrary;
//-------------------------------------------------------------------------------------------------------
namespace ImpersonationClient
{
//-------------------------------------------------------------------------------------------------------
	public class CImpersonationProxy : ClientBase<IImpersonationContract>, IImpersonationContract
	{
//-------------------------------------------------------------------------------------------------------
		public CImpersonationProxy(Binding ProxyBinding, string EndpointAddress)
			: base(ProxyBinding, new EndpointAddress(EndpointAddress))
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void AutomaticImpersonation()
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.AutomaticImpersonation();
		}
//-------------------------------------------------------------------------------------------------------
		public void ManualImpersonation()
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.ManualImpersonation();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------