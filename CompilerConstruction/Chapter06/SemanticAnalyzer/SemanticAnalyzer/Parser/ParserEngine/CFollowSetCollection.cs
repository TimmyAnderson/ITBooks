﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace SemanticAnalyzer
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CFollowSetCollection
	{
//-------------------------------------------------------------------------------------------------------
		private readonly List<CFollowSet>						MFollowSets;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CFollowSetCollection()
		{
			MFollowSets=new List<CFollowSet>();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CFollowSet[]										FollowSets
		{
			get
			{
				return(MFollowSets.ToArray());
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void AddFollowSet(CFollowSet FollowSet)
		{
			MFollowSets.Add(FollowSet);
		}
//-------------------------------------------------------------------------------------------------------
		public CFollowSet GetFollowSetByNonterminal(CNonterminal Nonterminal)
		{
			CFollowSet			FollowSet=MFollowSets.Where(P => P.Nonterminal.Name==Nonterminal.Name).FirstOrDefault();

			if (Nonterminal!=null)
				return(FollowSet);
			else
				throw(new InvalidOperationException(string.Format("Can't find FOLLOW SET for NONTERMINAL [{0}] !",Nonterminal)));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------