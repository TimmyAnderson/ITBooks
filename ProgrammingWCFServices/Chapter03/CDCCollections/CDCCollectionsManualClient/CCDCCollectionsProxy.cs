using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using CDCCollectionsLibrary;
//-------------------------------------------------------------------------------------------------------
namespace CDCCollectionsManualClient
{
//-------------------------------------------------------------------------------------------------------
	public class CCDCCollectionsProxy : ClientBase<ICDCCollectionsContract>, ICDCCollectionsContract
	{
//-------------------------------------------------------------------------------------------------------
		public CCDCCollectionsProxy(Binding ProxyBinding, string EndpointAddress)
			: base(ProxyBinding, new EndpointAddress(EndpointAddress))
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CMyCollection<CName> GetCollection()
		{
			return(Channel.GetCollection());
		}
//-------------------------------------------------------------------------------------------------------
		public void SendCollection(CMyCollection<CName> Collection)
		{
			Channel.SendCollection(Collection);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------