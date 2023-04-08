using System;
using System.Collections.Generic;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace WCFToWCFCollectionsLibrary
{
//-------------------------------------------------------------------------------------------------------
	public static class CCollectionHelper
	{
//-------------------------------------------------------------------------------------------------------
		public static List<CName> GetCollection1()
		{
			List<CName>							Ret=new List<CName>();

			CName								Timmy=new CName("Timmy","Anderson");
			CName								Jenny=new CName("Jenny","Thompson");

			Ret.Add(Timmy);
			Ret.Add(Jenny);

			return(Ret);
		}
//-------------------------------------------------------------------------------------------------------
		public static Dictionary<int,CName> GetCollection2()
		{
			Dictionary<int,CName>				Ret=new Dictionary<int,CName>();

			CName								Timmy=new CName("Timmy","Anderson");
			CName								Jenny=new CName("Jenny","Thompson");

			Ret.Add(1,Timmy);
			Ret.Add(2,Jenny);

			return(Ret);
		}
//-------------------------------------------------------------------------------------------------------
		public static CMyCollection<CName> GetCollection3()
		{
			CMyCollection<CName>				Ret=new CMyCollection<CName>();

			CName								Timmy=new CName("Timmy","Anderson");
			CName								Jenny=new CName("Jenny","Thompson");

			Ret.Add(Timmy);
			Ret.Add(Jenny);

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
		public static string Collection3ToString(CMyCollection<CName> Collection)
		{
			StringBuilder						SB=new StringBuilder();
			IEnumerator<CName>					Enumerator=Collection.GetEnumerator();

			for (int i=0;i<Collection.Count;i++)
			{
				Enumerator.MoveNext();
				SB.AppendLine(string.Format("{0}: FirstName: {1}, LastName: {2}",i+1,Enumerator.Current.FirstName,Enumerator.Current.LastName));
			}
			
			return(SB.ToString());
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------