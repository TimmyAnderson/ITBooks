﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
using CParingTableRowDictionary=System.Collections.Generic.Dictionary<LL1Parser.CNonterminal,LL1Parser.CParsingTableRow>;
//-------------------------------------------------------------------------------------------------------
namespace LL1Parser
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CParsingTable
	{
//-------------------------------------------------------------------------------------------------------
		private readonly CParingTableRowDictionary				MRows;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CParsingTable()
		{
			MRows=new CParingTableRowDictionary();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CParsingTableRow									this[CNonterminal Nonterminal]
		{
			get
			{
				CParsingTableRow	Row=MRows[Nonterminal];

				return(Row);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void AddRow(CParsingTableRow Row)
		{
			MRows.Add(Row.Nonterminal,Row);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------