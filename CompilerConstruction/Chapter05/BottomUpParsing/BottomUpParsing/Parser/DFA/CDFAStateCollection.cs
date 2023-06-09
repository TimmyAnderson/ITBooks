﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace BottomUpParsing
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CDFAStateCollection
	{
//-------------------------------------------------------------------------------------------------------
		private readonly HashSet<CDFAState>						MDFAStates;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CDFAStateCollection()
		{
			MDFAStates=new HashSet<CDFAState>();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CDFAState[]										DFAStates
		{
			get
			{
				return(MDFAStates.ToArray());
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void Add(CDFAState DFAState)
		{
			MDFAStates.Add(DFAState);
		}
//-------------------------------------------------------------------------------------------------------
		public CDFAState GetDFAStateWithSameNFAStates(CNFAState[] NFAStates)
		{
			foreach(CDFAState DFAState in MDFAStates)
			{
				if (DFAState.ContainsSameNFAStates(NFAStates)==true)
				{
					return(DFAState);
				}
			}

			return(null);
		}
//-------------------------------------------------------------------------------------------------------
		public CDFAState[] GetAllDFAStatesWithSameLALRCore(CLALRCore LALRCore)
		{
			List<CDFAState>			DFAStates=new List<CDFAState>();

			foreach(CDFAState DFAState in MDFAStates)
			{
				if (DFAState.ContainsSameLALRCore(LALRCore)==true)
				{
					DFAStates.Add(DFAState);
				}
			}

			return(DFAStates.ToArray());
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------