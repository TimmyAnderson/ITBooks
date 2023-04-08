using System;
using System.Collections.Generic;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace CDCCollectionsLibrary
{
//-------------------------------------------------------------------------------------------------------
	public class CCDCCollectionsService : ICDCCollectionsContract
	{
//-------------------------------------------------------------------------------------------------------
		public CMyCollection<CName> GetCollection()
		{
			return(CCollectionHelper.GetCollection());
		}
//-------------------------------------------------------------------------------------------------------
		public void SendCollection(CMyCollection<CName> Collection)
		{
			Console.WriteLine(string.Format("SendCollection()\n{0}",CCollectionHelper.CollectionToString(Collection)));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------