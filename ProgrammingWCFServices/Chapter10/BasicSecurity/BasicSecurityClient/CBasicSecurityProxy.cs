using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using BasicSecurityLibrary;
//-------------------------------------------------------------------------------------------------------
namespace BasicSecurityClient
{
//-------------------------------------------------------------------------------------------------------
	public class CBasicSecurityProxy : ClientBase<IBasicSecurityContract>, IBasicSecurityContract
	{
//-------------------------------------------------------------------------------------------------------
		public CBasicSecurityProxy(Binding ProxyBinding, string EndpointAddress)
			: base(ProxyBinding, new EndpointAddress(EndpointAddress))
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void SomeOperation()
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.SomeOperation();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------