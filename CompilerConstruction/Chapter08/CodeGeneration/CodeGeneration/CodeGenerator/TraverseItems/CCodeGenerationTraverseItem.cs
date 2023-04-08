using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace CodeGeneration
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CCodeGenerationTraverseItem
	{
//-------------------------------------------------------------------------------------------------------
		private readonly CSymbol								MSymbol;
		private readonly CChoice								MChoice;
		private readonly DCodeGenerationTraverseAction			MPreOrderAction;
		private readonly DCodeGenerationInOrderTraverseAction	MInPreOrderAction;
		private readonly DCodeGenerationInOrderTraverseAction	MInPostOrderAction;
		private readonly DCodeGenerationTraverseAction			MPostOrderAction;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CCodeGenerationTraverseItem(CTerminal Terminal, DCodeGenerationTraverseAction PreOrderAction, DCodeGenerationInOrderTraverseAction InPreOrderAction, DCodeGenerationInOrderTraverseAction InPostOrderAction, DCodeGenerationTraverseAction PostOrderAction)
		{
			MSymbol=Terminal;
			MChoice=null;
			MPreOrderAction=PreOrderAction;
			MInPreOrderAction=InPreOrderAction;
			MInPostOrderAction=InPostOrderAction;
			MPostOrderAction=PostOrderAction;
		}
//-------------------------------------------------------------------------------------------------------
		public CCodeGenerationTraverseItem(CChoice Choice, DCodeGenerationTraverseAction PreOrderAction, DCodeGenerationInOrderTraverseAction InPreOrderAction, DCodeGenerationInOrderTraverseAction InPostOrderAction, DCodeGenerationTraverseAction PostOrderAction)
		{
			MSymbol=Choice.Nonterminal;
			MChoice=Choice;
			MPreOrderAction=PreOrderAction;
			MInPreOrderAction=InPreOrderAction;
			MInPostOrderAction=InPostOrderAction;
			MPostOrderAction=PostOrderAction;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSymbol											Symbol
		{
			get
			{
				return(MSymbol);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public CChoice											Choice
		{
			get
			{
				return(MChoice);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public DCodeGenerationTraverseAction					PreOrderAction
		{
			get
			{
				return(MPreOrderAction);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public DCodeGenerationInOrderTraverseAction				InPreOrderAction
		{
			get
			{
				return(MInPreOrderAction);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public DCodeGenerationInOrderTraverseAction				InPostOrderAction
		{
			get
			{
				return(MInPostOrderAction);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public DCodeGenerationTraverseAction					PostOrderAction
		{
			get
			{
				return(MPostOrderAction);
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------