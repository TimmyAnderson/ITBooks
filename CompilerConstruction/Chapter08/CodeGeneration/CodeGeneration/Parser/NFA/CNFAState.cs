﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace CodeGeneration
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CNFAState
	{
//-------------------------------------------------------------------------------------------------------
		private readonly CLR1Item								MItem;
		private readonly List<CNFATransition>					MTransitions;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CNFAState(CLR1Item Item)
		{
			MItem=Item;
			MTransitions=new List<CNFATransition>();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CLR1Item											Item
		{
			get
			{
				return(MItem);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public CNFATransition[]									Transitions
		{
			get
			{
				return(MTransitions.ToArray());
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void AddTransition(CNFATransition NewTransition)
		{
			bool			TransitionExists=false;

			foreach(CNFATransition ExistingTransition in MTransitions)
			{
				if (ExistingTransition.Equals(NewTransition)==true)
				{
					TransitionExists=true;
					break;
				}
			}

			if (TransitionExists==false)
			{
				MTransitions.Add(NewTransition);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public bool ContainsLR1Item(CLR1Item LR1Item)
		{
			if (MItem.Equals(LR1Item)==true)
			{
				return(true);
			}
			else
			{
				return(false);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public bool ContainsLR0Item(CLR0Item LR0Item)
		{
			if (MItem.LR0Item.Equals(LR0Item)==true)
			{
				return(true);
			}
			else
			{
				return(false);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public override string ToString()
		{
			return(MItem.ToString());
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------