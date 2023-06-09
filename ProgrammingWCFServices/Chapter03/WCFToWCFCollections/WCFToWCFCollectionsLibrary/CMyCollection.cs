using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.Serialization;
//-------------------------------------------------------------------------------------------------------
namespace WCFToWCFCollectionsLibrary
{
//-------------------------------------------------------------------------------------------------------
	[DataContract(Name="CMyCollection_{0}")]
	public class CMyCollection<T> : IEnumerable<T>, ICollection<T>
	{
//-------------------------------------------------------------------------------------------------------
		private List<T>											MList;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CMyCollection()
		{
			MList=new List<T>();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// !!!!! Extremne dolezite aby bol List<T> [DataMember], pretoze prave on nesie informacie o obsahuj zoznamu.
		// Bez neho sa serializuje iba prazdna collection.
		// Je mozne serailizovat aj priamo data member.
		[DataMember]
		public List<T>											List
		{
			get
			{
				return(MList);
			}
			set
			{
				MList=value;
			}
		}
//-------------------------------------------------------------------------------------------------------
		public int												Count
		{
			get
			{
				return(MList.Count);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public bool												IsReadOnly
		{
			get
			{
				return(false);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public IEnumerator<T> GetEnumerator()
		{
			return(MList.GetEnumerator());
		}
//-------------------------------------------------------------------------------------------------------
		System.Collections.IEnumerator System.Collections.IEnumerable.GetEnumerator()
		{
			return(MList.GetEnumerator());
		}
//-------------------------------------------------------------------------------------------------------
		public void Add(T Item)
		{
			MList.Add(Item);
		}
//-------------------------------------------------------------------------------------------------------
		public void Clear()
		{
			MList.Clear();
		}
//-------------------------------------------------------------------------------------------------------
		public bool Contains(T Item)
		{
			return(MList.Contains(Item));
		}
//-------------------------------------------------------------------------------------------------------
		public void CopyTo(T[] Array, int ArrayIndex)
		{
			MList.CopyTo(Array, ArrayIndex);
		}
//-------------------------------------------------------------------------------------------------------
		public bool Remove(T Item)
		{
			return(MList.Remove(Item));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------