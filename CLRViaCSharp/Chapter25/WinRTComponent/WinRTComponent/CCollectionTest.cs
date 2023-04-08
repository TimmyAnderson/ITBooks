using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Windows.UI.Xaml.Controls;
using Windows.Foundation.Collections;
//-------------------------------------------------------------------------------------------------------
namespace WinRTComponent
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CCollectionTest
	{
//-------------------------------------------------------------------------------------------------------
		private ListView										MListView;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CCollectionTest(ListView ListView)
		{
			MListView=ListView;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private void PrintCollection(string Prefix, IEnumerable<int> Collection)
		{
			StringBuilder										SB=new StringBuilder();

			SB.AppendFormat("[{0}] - {1} - [",DateTime.Now,Prefix);

			int													Counter=0;

			foreach(int Value in Collection)
			{
				if (Counter++!=0)
				{
					SB.Append(",");
				}

				SB.Append(Value);
			}

			SB.AppendLine("] !");

			MListView.Items.Add(SB.ToString());
		}
//-------------------------------------------------------------------------------------------------------
		private void PrintCollection(string Prefix, IDictionary<int,int> Collection)
		{
			StringBuilder										SB=new StringBuilder();

			SB.AppendFormat("[{0}] - {1} - [",DateTime.Now,Prefix);

			int													Counter=0;

			foreach(int Key in Collection.Keys)
			{
				if (Counter++!=0)
				{
					SB.Append(",");
				}

				SB.Append(Key);
				SB.Append(" ");
				SB.Append(Collection[Key]);
			}

			SB.AppendLine("] !");

			MListView.Items.Add(SB.ToString());
		}
//-------------------------------------------------------------------------------------------------------
		private void PrintCollection(string Prefix, PropertySet Collection)
		{
			StringBuilder										SB=new StringBuilder();

			SB.AppendFormat("[{0}] - {1} - [",DateTime.Now,Prefix);

			int													Counter=0;

			foreach(string Key in Collection.Keys)
			{
				if (Counter++!=0)
				{
					SB.Append(",");
				}

				SB.Append(Key);
				SB.Append(" ");
				SB.Append(Collection[Key]);
			}

			SB.AppendLine("] !");

			MListView.Items.Add(SB.ToString());
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// WinRT COMPONENTS NESMU vystvavovat CLR COLLECTIONS, ale iba CLR INTERFACES, ktore su MAPPED na WinRT INTERFACES.
		/*
		public void CLRCollection(List<int> List)
		{
			List.Add(999);
		}
		*/
//-------------------------------------------------------------------------------------------------------
		public void Collection1(IEnumerable<int> List)
		{
			PrintCollection("ENUMERABLE",List);
		}
//-------------------------------------------------------------------------------------------------------
		public void Collection2(IList<int> List)
		{
			List.Add(999);

			PrintCollection("LIST",List);
		}
//-------------------------------------------------------------------------------------------------------
		public void Collection3(IDictionary<int,int> Map)
		{
			Map.Add(999,999);

			PrintCollection("MAP",Map);
		}
//-------------------------------------------------------------------------------------------------------
		// CLASS PropertySet je WinRT COLLECTION typu DICTIONARY<string,object>.
		public void Collection4(PropertySet Set)
		{
			Set.Add("Jenny Thompson",13);

			PrintCollection("SET",Set);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------