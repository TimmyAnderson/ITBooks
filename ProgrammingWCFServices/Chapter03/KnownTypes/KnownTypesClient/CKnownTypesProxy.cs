using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using KnownTypesLibrary;
//-------------------------------------------------------------------------------------------------------
namespace KnownTypesClient
{
	class CKnownTypesProxy : ClientBase<IKnownTypesContract>, IKnownTypesContract
	{
//-------------------------------------------------------------------------------------------------------
		public CKnownTypesProxy(Binding ProxyBinding, string EndpointAddress)
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
		public void SendName(CName Name)
		{
			Channel.SendName(Name);
		}
//-------------------------------------------------------------------------------------------------------
	}
}
//-------------------------------------------------------------------------------------------------------