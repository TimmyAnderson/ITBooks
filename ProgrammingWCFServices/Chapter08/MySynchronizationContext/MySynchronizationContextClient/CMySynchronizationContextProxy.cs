using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using MySynchronizationContextLibrary;
//-------------------------------------------------------------------------------------------------------
namespace MySynchronizationContextClient
{
//-------------------------------------------------------------------------------------------------------
	public class CMySynchronizationContextProxy : ClientBase<IMySynchronizationContextContract>, IMySynchronizationContextContract
	{
//-------------------------------------------------------------------------------------------------------
		public CMySynchronizationContextProxy(Binding ProxyBinding, string EndpointAddress)
			: base(ProxyBinding, new EndpointAddress(EndpointAddress))
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void ShowText(string Message)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.ShowText(Message);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------