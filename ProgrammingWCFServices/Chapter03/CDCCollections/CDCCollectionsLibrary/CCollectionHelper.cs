using System;
using System.Collections.Generic;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace CDCCollectionsLibrary
{
//-------------------------------------------------------------------------------------------------------
	public static class CCollectionHelper
	{
//-------------------------------------------------------------------------------------------------------
		public static CMyCollection<CName> GetCollection()
		{
			CMyCollection<CName>				Ret=new CMyCollection<CName>();

			CName								Timmy=new CName("Timmy","Anderson");
			CName								Jenny=new CName("Jenny","Thompson");

			Ret.Add(Timmy);
			Ret.Add(Jenny);

			return(Ret);
		}
//-------------------------------------------------------------------------------------------------------
		public static string CollectionToString(CMyCollection<CName> Collection)
		{
			StringBuilder						SB=new StringBuilder();
			IEnumerator<CName>					Enumerator=Collection.GetEnumerator();

			for (int i=0;i<Collection.Count;i++)
			{
				Enumerator.MoveNext();
				SB.AppendLine(string.Format("{0}: FirstName: {1}, LastName: {2} !",i+1,Enumerator.Current.FirstName,Enumerator.Current.LastName));
			}
			
			return(SB.ToString());
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------