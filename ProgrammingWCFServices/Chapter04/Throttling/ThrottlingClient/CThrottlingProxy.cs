using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using ThrottlingLibrary;
//-------------------------------------------------------------------------------------------------------
namespace ThrottlingClient
{
//-------------------------------------------------------------------------------------------------------
	public class CThrottlingProxy : ClientBase<IThrottlingContract>, IThrottlingContract
	{
//-------------------------------------------------------------------------------------------------------
		public CThrottlingProxy(Binding ProxyBinding, string EndpointAddress)
			: base(ProxyBinding, new EndpointAddress(EndpointAddress))
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void StartInstance()
		{
			Console.WriteLine("CThrottlingProxy.StartInstance() !");
			Channel.StartInstance();
		}
//-------------------------------------------------------------------------------------------------------
		public void DropInstance()
		{
			Console.WriteLine("CThrottlingProxy.DropInstance() !");
			Channel.DropInstance();
		}
//-------------------------------------------------------------------------------------------------------
		public void SlowMethod(int Timeout)
		{
			Console.WriteLine("CThrottlingProxy.SlowMethod() !");
			Channel.SlowMethod(Timeout);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------