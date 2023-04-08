using System;
using System.Collections.Generic;
using System.Text;
using WCFToWCFCollectionsAutomaticClient.CWCFToWCFCollectionsProxy;
//-------------------------------------------------------------------------------------------------------
namespace WCFToWCFCollectionsAutomaticClient
{
//-------------------------------------------------------------------------------------------------------
	public static class CCollectionHelper
	{
//-------------------------------------------------------------------------------------------------------
		public static List<CName> GetCollection1()
		{
			List<CName>							Ret=new List<CName>();

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
		public static Dictionary<int,CName> GetCollection2()
		{
			Dictionary<int,CName>				Ret=new Dictionary<int,CName>();

			CName								Timmy=new CName();
			CName								Jenny=new CName();

			Timmy.FirstName="Timmy";
			Timmy.LastName="Anderson";
			Jenny.FirstName="Jenny";
			Jenny.LastName="Thompson";

			Ret.Add(1,Timmy);
			Ret.Add(2,Jenny);

			return(Ret);
		}
//-------------------------------------------------------------------------------------------------------
		public static CMyCollection_CName GetCollection3()
		{
			CMyCollection_CName					Ret=new CMyCollection_CName();

			CName								Timmy=new CName();
			CName								Jenny=new CName();

			Timmy.FirstName="Timmy";
			Timmy.LastName="Anderson";
			Jenny.FirstName="Jenny";
			Jenny.LastName="Thompson";

			// Kedze je v proxy reprezentovana collection ako pole musim ho takto naplnit.
			CName[]								Array=new CName[]{Timmy,Jenny};

			Ret.List=Array;

			return(Ret);
		}
//-------------------------------------------------------------------------------------------------------
		public static string Collection1ToString(List<CName> Collection)
		{
			StringBuilder						SB=new StringBuilder();
			List<CName>.Enumerator				Enumerator=Collection.GetEnumerator();

			for (int i=0;i<Collection.Count;i++)
			{
				Enumerator.MoveNext();
				SB.AppendLine(string.Format("{0}: FirstName: {1}, LastName: {2}",i+1,Enumerator.Current.FirstName,Enumerator.Current.LastName));
			}
			
			return(SB.ToString());
		}
//-------------------------------------------------------------------------------------------------------
		public static string Collection2ToString(Dictionary<int,CName> Collection)
		{
			StringBuilder						SB=new StringBuilder();
			Dictionary<int,CName>.Enumerator	Enumerator=Collection.GetEnumerator();

			for (int i=0;i<Collection.Count;i++)
			{
				Enumerator.MoveNext();
				SB.AppendLine(string.Format("{0}: FirstName: {1}, LastName: {2}",i+1,Enumerator.Current.Value.FirstName,Enumerator.Current.Value.LastName));
			}
			
			return(SB.ToString());
		}
//-------------------------------------------------------------------------------------------------------
		public static string Collection3ToString(CMyCollection_CName Collection)
		{
			StringBuilder						SB=new StringBuilder();
			// V proxy reprezentovana collection ako pole.
			CName[]								Array=Collection.List;

			for (int i=0;i<Array.Length;i++)
			{
				SB.AppendLine(string.Format("{0}: FirstName: {1}, LastName: {2}",i+1,Array[i].FirstName,Array[i].LastName));
			}
			
			return(SB.ToString());
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------