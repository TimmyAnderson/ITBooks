using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using MEPLibrary;
//-------------------------------------------------------------------------------------------------------
namespace MEPClient
{
//-------------------------------------------------------------------------------------------------------
	public class CRequestResponseProxy : ClientBase<IRequestResponseContract>, IRequestResponseContract
	{
//-------------------------------------------------------------------------------------------------------
		public CRequestResponseProxy(Binding ProxyBinding, string EndpointAddress)
			: base(ProxyBinding, new EndpointAddress(EndpointAddress))
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public Message SendMessage(Message SomeMessage)
		{
			return(Channel.SendMessage(SomeMessage));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------