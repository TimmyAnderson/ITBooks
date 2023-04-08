using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using WCFToWCFCollectionsLibrary;
//-------------------------------------------------------------------------------------------------------
namespace WCFToWCFCollectionsManualClient
{
//-------------------------------------------------------------------------------------------------------
	public class CWCFToWCFCollectionsProxy : ClientBase<IWCFToWCFCollectionsContract>, IWCFToWCFCollectionsContract
	{
//-------------------------------------------------------------------------------------------------------
		public CWCFToWCFCollectionsProxy(Binding ProxyBinding, string EndpointAddress)
			: base(ProxyBinding, new EndpointAddress(EndpointAddress))
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public List<CName> GetCollection1()
		{
			return(Channel.GetCollection1());
		}
//-------------------------------------------------------------------------------------------------------
		public Dictionary<int,CName> GetCollection2()
		{
			return(Channel.GetCollection2());
		}
//-------------------------------------------------------------------------------------------------------
		public CMyCollection<CName> GetCollection3()
		{
			return(Channel.GetCollection3());
		}
//-------------------------------------------------------------------------------------------------------
		public void SendCollection1(List<CName> Collection)
		{
			Channel.SendCollection1(Collection);
		}
//-------------------------------------------------------------------------------------------------------
		public void SendCollection2(Dictionary<int,CName> Collection)
		{
			Channel.SendCollection2(Collection);
		}
//-------------------------------------------------------------------------------------------------------
		public void SendCollection3(CMyCollection<CName> Collection)
		{
			Channel.SendCollection3(Collection);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------