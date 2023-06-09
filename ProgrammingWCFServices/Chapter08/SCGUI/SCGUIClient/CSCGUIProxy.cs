using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using SCGUILibrary;
//-------------------------------------------------------------------------------------------------------
namespace SCGUIClient
{
//-------------------------------------------------------------------------------------------------------
	public class CSCGUIProxy : ClientBase<ISCGUIContract>, ISCGUIContract
	{
//-------------------------------------------------------------------------------------------------------
		public CSCGUIProxy(Binding ProxyBinding, string EndpointAddress)
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
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------