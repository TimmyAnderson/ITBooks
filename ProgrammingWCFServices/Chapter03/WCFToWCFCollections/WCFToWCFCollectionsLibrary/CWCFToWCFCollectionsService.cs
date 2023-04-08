using System;
using System.Collections.Generic;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace WCFToWCFCollectionsLibrary
{
//-------------------------------------------------------------------------------------------------------
	public class CWCFToWCFCollectionsService : IWCFToWCFCollectionsContract
	{
//-------------------------------------------------------------------------------------------------------
		public List<CName> GetCollection1()
		{
			return(CCollectionHelper.GetCollection1());
		}
//-------------------------------------------------------------------------------------------------------
		public Dictionary<int,CName> GetCollection2()
		{
			return(CCollectionHelper.GetCollection2());
		}
//-------------------------------------------------------------------------------------------------------
		public CMyCollection<CName> GetCollection3()
		{
			return(CCollectionHelper.GetCollection3());
		}
//-------------------------------------------------------------------------------------------------------
		public void SendCollection1(List<CName> Collection)
		{
			Console.WriteLine(string.Format("SendCollection1()\n{0}",CCollectionHelper.Collection1ToString(Collection)));
		}
//-------------------------------------------------------------------------------------------------------
		public void SendCollection2(Dictionary<int,CName> Collection)
		{
			Console.WriteLine(string.Format("SendCollection2()\n{0}",CCollectionHelper.Collection2ToString(Collection)));
		}
//-------------------------------------------------------------------------------------------------------
		public void SendCollection3(CMyCollection<CName> Collection)
		{
			Console.WriteLine(string.Format("SendCollection3()\n{0}",CCollectionHelper.Collection3ToString(Collection)));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------