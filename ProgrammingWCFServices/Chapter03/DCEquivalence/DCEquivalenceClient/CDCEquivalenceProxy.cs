using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace DCEquivalenceClient
{
//-------------------------------------------------------------------------------------------------------
	class CDCEquivalenceProxy : ClientBase<IDCEquivalenceContract>, IDCEquivalenceContract
	{
//-------------------------------------------------------------------------------------------------------
		public CDCEquivalenceProxy(Binding ProxyBinding, string EndpointAddress)
			: base(ProxyBinding, new EndpointAddress(EndpointAddress))
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CClientPerson GetPerson()
		{
 			return(Channel.GetPerson());
		}
//-------------------------------------------------------------------------------------------------------
		public void SendPerson(CClientPerson Person)
		{
			Channel.SendPerson(Person);
		}
//-------------------------------------------------------------------------------------------------------
		public CClientErrorPerson GetErrorPerson()
		{
 			return(Channel.GetErrorPerson());
		}
//-------------------------------------------------------------------------------------------------------
		public void SendErrorPerson(CClientErrorPerson Person)
		{
			Channel.SendErrorPerson(Person);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------