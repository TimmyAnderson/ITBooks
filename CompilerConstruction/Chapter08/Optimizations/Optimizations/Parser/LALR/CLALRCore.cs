﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace Optimizations
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CLALRCore
	{
//-------------------------------------------------------------------------------------------------------
		private readonly CLR0Item[]								MLR0Items;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CLALRCore(CLR0Item[] LR0Items)
		{
			MLR0Items=LR0Items;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CLR0Item[]										LR0Items
		{
			get
			{
				return(MLR0Items);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override string ToString()
		{
			StringBuilder										SB=new StringBuilder();
			bool												IsFirst=true;

			SB.Append("[");

			foreach(CLR0Item LR0Item in MLR0Items)
			{
				if (IsFirst==false)
				{
					SB.Append(", ");
				}
				else
				{
					IsFirst=false;
				}

				SB.Append(LR0Item.ToString());
			}

			SB.Append("]");

			return(SB.ToString());
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------