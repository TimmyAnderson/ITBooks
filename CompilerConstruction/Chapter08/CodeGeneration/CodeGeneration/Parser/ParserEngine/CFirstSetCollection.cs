﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace CodeGeneration
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CFirstSetCollection
	{
//-------------------------------------------------------------------------------------------------------
		private readonly List<CFirstSet>						MFirstSets;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CFirstSetCollection()
		{
			MFirstSets=new List<CFirstSet>();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CFirstSet[]										FirstSets
		{
			get
			{
				return(MFirstSets.ToArray());
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void AddFirstSet(CFirstSet FirstSet)
		{
			MFirstSets.Add(FirstSet);
		}
//-------------------------------------------------------------------------------------------------------
		public CFirstSet GetFirstSetByNonterminal(CNonterminal Nonterminal)
		{
			CFirstSet			FirstSet=MFirstSets.Where(P => P.Nonterminal.Name==Nonterminal.Name).FirstOrDefault();

			if (Nonterminal!=null)
				return(FirstSet);
			else
				throw(new InvalidOperationException(string.Format("Can't find FIRST SET for NONTERMINAL [{0}] !",Nonterminal)));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------