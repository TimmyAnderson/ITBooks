using System;
using System.Collections.Generic;
using System.Collections;
using System.Text;
using System.Collections.Specialized;
//------------------------------------------------------------------------
namespace BindingCollectionLibrary
{
//------------------------------------------------------------------------
	public class CMyCustomCollection : CollectionBase, INotifyCollectionChanged
	{
//------------------------------------------------------------------------
		public event NotifyCollectionChangedEventHandler	CollectionChanged;
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public CName						this[int Index]
		{
			get
			{
				return((CName) this.List[Index]);
			}
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public void Add(CName Data)
		{
			base.InnerList.Add(Data);

			if (CollectionChanged!=null)
				CollectionChanged(this,new NotifyCollectionChangedEventArgs(NotifyCollectionChangedAction.Add,Data));
		}
//------------------------------------------------------------------------
		public void Remove(CName Data)
		{
			base.InnerList.Remove(Data);

			if (CollectionChanged!=null)
				CollectionChanged(this,new NotifyCollectionChangedEventArgs(NotifyCollectionChangedAction.Remove,Data));
		}
//------------------------------------------------------------------------
		public new void RemoveAt(int Index)
		{
			CName			Data=(CName) base.InnerList[Index];

			base.InnerList.RemoveAt(Index);

			if (CollectionChanged!=null)
				CollectionChanged(this,new NotifyCollectionChangedEventArgs(NotifyCollectionChangedAction.Remove,Data));
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public override string ToString()
		{
			StringBuilder			SB=new StringBuilder();
			
			SB.AppendFormat("\n");

			for (int i=0;i<base.Count;i++)
				SB.AppendFormat("{0}: {1} !\n",i+1,this.List[i].ToString());

			return(SB.ToString());
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------