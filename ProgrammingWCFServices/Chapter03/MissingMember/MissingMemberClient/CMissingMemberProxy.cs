using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace MissingMemberClient
{
//-------------------------------------------------------------------------------------------------------
	public class CMissingMemberProxy : ClientBase<IMissingMemberContract>, IMissingMemberContract
	{
//-------------------------------------------------------------------------------------------------------
		public CMissingMemberProxy(Binding ProxyBinding, string EndpointAddress)
			: base(ProxyBinding, new EndpointAddress(EndpointAddress))
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CClientName GetName()
		{
 			return(Channel.GetName());
		}
//-------------------------------------------------------------------------------------------------------
		public void SendName(CClientName Name)
		{
 			Channel.SendName(Name);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------