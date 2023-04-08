using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using DCUsingAttributesLibrary;
//-------------------------------------------------------------------------------------------------------
namespace DCUsingAttributesManualClient
{
//-------------------------------------------------------------------------------------------------------
	class CDCUsingAttributesProxy : ClientBase<IDCUsingAttributesContract>, IDCUsingAttributesContract
	{
//-------------------------------------------------------------------------------------------------------
		public CDCUsingAttributesProxy(Binding ProxyBinding, string EndpointAddress)
			: base(ProxyBinding, new EndpointAddress(EndpointAddress))
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CNameDC SayYourName()
		{
 			return(Channel.SayYourName());
		}
//-------------------------------------------------------------------------------------------------------
		public void ThisIsMyName(CNameDC NameDC)
		{
 			Channel.ThisIsMyName(NameDC);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------