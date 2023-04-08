using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace VersionRoundTripClient
{
//-------------------------------------------------------------------------------------------------------
	public class CVersionRoundTripProxy : ClientBase<IVersionRoundTripContract>, IVersionRoundTripContract
	{
//-------------------------------------------------------------------------------------------------------
		public CVersionRoundTripProxy(Binding ProxyBinding, string EndpointAddress)
			: base(ProxyBinding, new EndpointAddress(EndpointAddress))
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CClientName DoRoundTripWithoutEDO(CClientName Name)
		{
 			return(Channel.DoRoundTripWithoutEDO(Name));
		}
//-------------------------------------------------------------------------------------------------------
		public CClientName DoRoundTripWithEDO(CClientName Name)
		{
 			return(Channel.DoRoundTripWithEDO(Name));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------