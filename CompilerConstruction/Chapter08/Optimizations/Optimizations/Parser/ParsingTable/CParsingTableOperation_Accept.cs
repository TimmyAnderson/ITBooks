﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace Optimizations
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CParsingTableOperation_Accept : CParsingTableOperation_Reduce
	{
//-------------------------------------------------------------------------------------------------------
		public CParsingTableOperation_Accept(CChoice Choice)
			: base(Choice)
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override string ToString()
		{
			StringBuilder										SB=new StringBuilder();

			SB.Append("ACCEPT ");
			SB.Append(Choice.ToString());

			return(SB.ToString());
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------