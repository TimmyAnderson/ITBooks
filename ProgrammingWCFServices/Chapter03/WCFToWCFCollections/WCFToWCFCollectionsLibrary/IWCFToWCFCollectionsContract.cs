using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace WCFToWCFCollectionsLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract]
	public interface IWCFToWCFCollectionsContract
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract]
		List<CName> GetCollection1();
		[OperationContract]
		Dictionary<int,CName> GetCollection2();
		[OperationContract]
		CMyCollection<CName> GetCollection3();
		[OperationContract]
		void SendCollection1(List<CName> Collection);
		[OperationContract]
		void SendCollection2(Dictionary<int,CName> Collection);
		[OperationContract]
		void SendCollection3(CMyCollection<CName> Collection);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------