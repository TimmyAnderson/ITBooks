﻿using System;
using System.Collections.Generic;
using System.Collections;
using System.Linq;
using System.Text;
//-----------------------------------------------------------------------------------------------------------
namespace Trees
{
//-----------------------------------------------------------------------------------------------------------
	internal class CGenericListEnumerator<TItemType> : IEnumerator<TItemType>
	{
//-----------------------------------------------------------------------------------------------------------
		private CGenericList<TItemType>							MList;
		private int												MPosition;
//-----------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------
		public CGenericListEnumerator(CGenericList<TItemType> List)
		{
			MList=List;
			MPosition=-1;
		}
//-----------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------
		public TItemType									Current
		{
			get
			{
				if (MPosition>=MList.Count)
					return(default(TItemType));
				else
					return(MList[MPosition]);
			}
		}
//-----------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------
		object												IEnumerator.Current
		{
			get
			{
				if (MPosition>=MList.Count)
					return(default(TItemType));
				else
					return(MList[MPosition]);
			}
		}
//-----------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------
		public void Dispose()
		{
			// Empty.
		}
//-----------------------------------------------------------------------------------------------------------
		public bool MoveNext()
		{
			MPosition++;

			if (MPosition>=MList.Count)
				return(false);
			else
				return(true);
		}
//-----------------------------------------------------------------------------------------------------------
		public void Reset()
		{
			MPosition=-1;
		}
//-----------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------
		public override string ToString()
		{
			StringBuilder		SB=new StringBuilder();

			SB.Append(this.GetType().Name);
			SB.AppendFormat(", Items.Count: [{0}]",MList.Count);

			return(SB.ToString());
		}
//-----------------------------------------------------------------------------------------------------------
	}
//-----------------------------------------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------------------------------------