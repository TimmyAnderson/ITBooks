using System;
using System.Collections.Generic;
using System.Text;
using System.Collections.ObjectModel;
//------------------------------------------------------------------------
namespace BindingCollectionLibrary
{
//------------------------------------------------------------------------
	public class CMyCustomObservableCollection : ObservableCollection<CName>
	{
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public override string ToString()
		{
			StringBuilder			SB=new StringBuilder();
			
			SB.AppendFormat("\n");

			for (int i=0;i<base.Count;i++)
				SB.AppendFormat("{0}: {1} !\n",i+1,base[i].ToString());

			return(SB.ToString());
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------