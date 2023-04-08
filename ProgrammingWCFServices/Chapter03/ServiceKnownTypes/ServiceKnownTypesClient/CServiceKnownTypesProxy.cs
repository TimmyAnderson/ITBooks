using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using ServiceKnownTypesLibrary;
//-------------------------------------------------------------------------------------------------------
namespace ServiceKnownTypesClient
{
//-------------------------------------------------------------------------------------------------------
	public class CServiceKnownTypesProxy : ClientBase<IServiceKnownTypesContract>, IServiceKnownTypesContract
	{
//-------------------------------------------------------------------------------------------------------
		public CServiceKnownTypesProxy(Binding ProxyBinding, string EndpointAddress)
			: base(ProxyBinding, new EndpointAddress(EndpointAddress))
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CName GetName()
		{
 			return(Channel.GetName());
		}
//-------------------------------------------------------------------------------------------------------
		public void SendJustName(CName Name)
		{
 			Channel.SendJustName(Name);
		}
//-------------------------------------------------------------------------------------------------------
		public void SendAllNameTypes(CName Name)
		{
 			Channel.SendAllNameTypes(Name);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------