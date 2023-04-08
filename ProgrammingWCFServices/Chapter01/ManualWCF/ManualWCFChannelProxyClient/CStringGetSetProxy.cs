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
	class CStringGetSetProxy : CChannelFactoryProxyBase<IStringGetSetContract>, IStringGetSetContract
	{
//-------------------------------------------------------------------------------------------------------
		public CStringGetSetProxy(Binding ProxyBinding, string EndpointAddress)
			: base(ProxyBinding, new EndpointAddress(EndpointAddress))
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public string GetStringValue()
		{
			return(MContract.GetStringValue());
		}
//-------------------------------------------------------------------------------------------------------
		public void SetStringValue(string Value)
		{
			MContract.SetStringValue(Value);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------