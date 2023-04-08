using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using ManualWCFLibrary;
//-------------------------------------------------------------------------------------------------------
namespace ManualWCFChannelProxyClient
{
//-------------------------------------------------------------------------------------------------------
	class CThrowExceptionProxy : CChannelFactoryProxyBase<IThrowExceptionContract>, IThrowExceptionContract
	{
//-------------------------------------------------------------------------------------------------------
		public CThrowExceptionProxy(Binding ProxyBinding, string EndpointAddress)
			: base(ProxyBinding, new EndpointAddress(EndpointAddress))
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void ThrowException()
		{
			MContract.ThrowException();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------