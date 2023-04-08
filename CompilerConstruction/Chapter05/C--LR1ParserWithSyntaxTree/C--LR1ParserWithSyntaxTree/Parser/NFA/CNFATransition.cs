using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace C__LR1ParserWithSyntaxTree
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CNFATransition : IEquatable<CNFATransition>
	{
//-------------------------------------------------------------------------------------------------------
		private readonly CLR1Item								MSourceItem;
		private readonly CSymbol								MTransitionSymbol;
		private readonly CLR1Item								MDestinationItem;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CNFATransition(CLR1Item SourceItem, CSymbol TransitionSymbol, CLR1Item DestinationItem)
		{
			MSourceItem=SourceItem;
			MTransitionSymbol=TransitionSymbol;
			MDestinationItem=DestinationItem;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CLR1Item											SourceItem
		{
			get
			{
				return(MSourceItem);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public CSymbol											TransitionSymbol
		{
			get
			{
				return(MTransitionSymbol);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public CLR1Item											DestinationItem
		{
			get
			{
				return(MDestinationItem);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public bool												IsEpsilonTransition
		{
			get
			{
				if ((MTransitionSymbol is CTerminal_EMPTY)==true)
				{
					return(true);
				}
				else
				{
					return(false);
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public bool Equals(CNFATransition Other)
		{
 			if (Other==null)
			{
				return(false);
			}

			if (MSourceItem.Equals(Other.MSourceItem)==false)
			{
				return(false);
			}

			if (MTransitionSymbol.Equals(Other.MTransitionSymbol)==false)
			{
				return(false);
			}

			if (MDestinationItem.Equals(Other.MDestinationItem)==false)
			{
				return(false);
			}

			return(true);
		}
//-------------------------------------------------------------------------------------------------------
		public override string ToString()
		{
			string			Ret=string.Format("{0} --- {1} ---> {2}",MSourceItem,MTransitionSymbol,MDestinationItem);

			return(Ret);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------