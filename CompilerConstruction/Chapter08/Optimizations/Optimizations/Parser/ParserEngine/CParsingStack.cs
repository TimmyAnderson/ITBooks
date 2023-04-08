﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace Optimizations
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CParsingStack
	{
//-------------------------------------------------------------------------------------------------------
		private readonly List<CParsingStackItem>				MStack;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CParsingStack()
		{
			MStack=new List<CParsingStackItem>();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public bool												IsEmpty
		{
			get
			{
				return(MStack.Count==0);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void Add(CParsingStackItem NewTopParsingStackItem)
		{
			MStack.Add(NewTopParsingStackItem);
		}
//-------------------------------------------------------------------------------------------------------
		public CParsingStackItem PeekTopOfStack()
		{
			if (MStack.Count==0)
			{
				return(null);
			}

			CParsingStackItem									Top=MStack[MStack.Count-1];

			return(Top);
		}
//-------------------------------------------------------------------------------------------------------
		public CParsingStackItem DequeueTopOfStack()
		{
			CParsingStackItem									Top=MStack[MStack.Count-1];

			MStack.RemoveAt(MStack.Count-1);

			return(Top);
		}
//-------------------------------------------------------------------------------------------------------
		public CParsingStackItem[] PopTopOfStack(int NumberOfItemsToPop)
		{
			CParsingStackItem[]									RemovedItems=new CParsingStackItem[NumberOfItemsToPop];

			for(int Index=0;Index<NumberOfItemsToPop;Index++)
			{
				RemovedItems[NumberOfItemsToPop-Index-1]=DequeueTopOfStack();
			}

			return(RemovedItems);
		}
//-------------------------------------------------------------------------------------------------------
		public void Clear()
		{
			MStack.Clear();
		}
//-------------------------------------------------------------------------------------------------------
		public override string ToString()
		{
			StringBuilder										SB=new StringBuilder();

			SB.AppendFormat("Length: [{0}]     ",MStack.Count);

			for(int Index=MStack.Count-1;Index>=0;Index--)
			{
				SB.AppendLine(MStack[Index].ToString());
			}

			return(SB.ToString());
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------