﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace LL1Parser
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CNonterminalCollection
	{
//-------------------------------------------------------------------------------------------------------
		private readonly List<CNonterminal>						MNonterminals;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CNonterminalCollection()
		{
			MNonterminals=new List<CNonterminal>();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CNonterminal[]									Nonterminals
		{
			get
			{
				return(MNonterminals.ToArray());
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void AddNonterminal(CNonterminal Nonterminal)
		{
			MNonterminals.Add(Nonterminal);
		}
//-------------------------------------------------------------------------------------------------------
		public CNonterminal FindNonterminalByName(string Name)
		{
			CNonterminal		Nonterminal=MNonterminals.Where(P => P.Name==Name).FirstOrDefault();

			if (Nonterminal!=null)
				return(Nonterminal);
			else
				throw(new InvalidOperationException(string.Format("Can't find NONTERMINAL [{0}] !",Name)));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------