﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace SemanticAnalyzer
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CRuleCollection
	{
//-------------------------------------------------------------------------------------------------------
		private readonly CLR0Rule[]								MRules;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CRuleCollection(CNonterminal[] Nonterminals)
		{
			List<CLR0Rule>				Rules=new List<CLR0Rule>();

			foreach(CNonterminal Nonterminal in Nonterminals)
			{
				CLR0Rule				Rule=new CLR0Rule(Nonterminal);

				Rules.Add(Rule);
			}

			MRules=Rules.ToArray();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CLR0Rule[]										Rules
		{
			get
			{
				return(MRules);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public CLR0Item[] GetLR0ItemsWithPeriodAsFirstSymbolAndNonterminalAsNextSymbol(CNonterminal Nonterminal)
		{
			foreach (CLR0Rule Rule in MRules)
			{
				if (Rule.Nonterminal.Equals(Nonterminal)==true)
				{
					CLR0Item[]			Items=Rule.GetLR0ItemsWithPeriodAsFirstSymbol();

					return(Items);
				}
			}

			return(new CLR0Item[0]);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------