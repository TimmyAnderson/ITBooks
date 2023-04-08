﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace CodeGeneration
{
//-------------------------------------------------------------------------------------------------------
	public class CParsingTableOperation_Reduce : CParsingTableOperation
	{
//-------------------------------------------------------------------------------------------------------
		private readonly CChoice								MChoice;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CParsingTableOperation_Reduce(CChoice Choice)
		{
			MChoice=Choice;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CChoice											Choice
		{
			get
			{
				return(MChoice);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override string ToString()
		{
			StringBuilder			SB=new StringBuilder();

			SB.Append("REDUCE ");
			SB.Append(MChoice.ToString());

			return(SB.ToString());
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------