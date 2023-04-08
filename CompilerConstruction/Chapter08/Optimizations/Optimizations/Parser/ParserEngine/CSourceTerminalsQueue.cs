﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace Optimizations
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CSourceTerminalsQueue
	{
//-------------------------------------------------------------------------------------------------------
		private readonly List<CSourceTerminalsQueueItem>		MQueue;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSourceTerminalsQueue()
		{
			MQueue=new List<CSourceTerminalsQueueItem>();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void Fill(CSourceTerminalsQueueItem[] Items)
		{
			MQueue.AddRange(Items);
		}
//-------------------------------------------------------------------------------------------------------
		public CSourceTerminalsQueueItem Peek()
		{
			if (MQueue.Count==0)
			{
				return(null);
			}

			CSourceTerminalsQueueItem							Item=MQueue[0];

			return(Item);
		}
//-------------------------------------------------------------------------------------------------------
		public CSourceTerminalsQueueItem Dequeue()
		{
			CSourceTerminalsQueueItem							Item=MQueue[0];

			MQueue.RemoveAt(0);

			return(Item);
		}
//-------------------------------------------------------------------------------------------------------
		public void Clear()
		{
			MQueue.Clear();
		}
//-------------------------------------------------------------------------------------------------------
		public CToken GetTokenOnTop()
		{
			if (MQueue.Count>0)
			{
				return(MQueue[0].Token);
			}
			else
			{
				return(null);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public override string ToString()
		{
			StringBuilder										SB=new StringBuilder();

			SB.AppendFormat("Length: [{0}]     ",MQueue.Count);

			for(int Index=0;Index<MQueue.Count;Index++)
			{
				SB.Append(MQueue[Index].ToString());
			}

			return(SB.ToString());
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------