﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace RuntimeEnvironment
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CNFAStateCollection
	{
//-------------------------------------------------------------------------------------------------------
		private readonly List<CNFAState>						MNFAStates;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CNFAStateCollection()
		{
			MNFAStates=new List<CNFAState>();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CNFAState[]										NFAStates
		{
			get
			{
				return(MNFAStates.ToArray());
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void Add(CNFAState NFAState)
		{
			MNFAStates.Add(NFAState);
		}
//-------------------------------------------------------------------------------------------------------
		public CNFAState GetNFAStateWithLR1Item(CLR1Item LR1Item)
		{
			foreach(CNFAState NFAState in MNFAStates)
			{
				if (NFAState.ContainsLR1Item(LR1Item)==true)
				{
					return(NFAState);
				}
			}

			return(null);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------