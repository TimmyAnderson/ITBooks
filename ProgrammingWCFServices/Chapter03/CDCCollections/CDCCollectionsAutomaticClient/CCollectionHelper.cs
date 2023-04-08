using System;
using System.Collections.Generic;
using System.Text;
using CDCCollectionsAutomaticClient.CCDCCollectionsProxy;
//-------------------------------------------------------------------------------------------------------
namespace CDCCollectionsAutomaticClient
{
//-------------------------------------------------------------------------------------------------------
	public static class CCollectionHelper
	{
//-------------------------------------------------------------------------------------------------------
		public static CMyCollection_CName GetCollection()
		{
			CMyCollection_CName					Ret=new CMyCollection_CName();

			CName								Timmy=new CName();
			CName								Jenny=new CName();

			Timmy.FirstName="Timmy";
			Timmy.LastName="Anderson";
			Jenny.FirstName="Jenny";
			Jenny.LastName="Thompson";

			Ret.Add(Timmy);
			Ret.Add(Jenny);

			return(Ret);
		}
//-------------------------------------------------------------------------------------------------------
		public static string CollectionToString(CMyCollection_CName Collection)
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