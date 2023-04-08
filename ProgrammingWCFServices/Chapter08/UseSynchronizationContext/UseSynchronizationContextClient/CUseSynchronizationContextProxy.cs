using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using UseSynchronizationContextLibrary;
//-------------------------------------------------------------------------------------------------------
namespace UseSynchronizationContextClient
{
//-------------------------------------------------------------------------------------------------------
	public class CUseSynchronizationContextProxy : ClientBase<IUseSynchronizationContextContract>, IUseSynchronizationContextContract
	{
//-------------------------------------------------------------------------------------------------------
		public CUseSynchronizationContextProxy(Binding ProxyBinding, string EndpointAddress)
			: base(ProxyBinding, new EndpointAddress(EndpointAddress))
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void IncrementLabel()
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.IncrementLabel();
		}
//-------------------------------------------------------------------------------------------------------
		public void DecrementLabel()
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.DecrementLabel();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------