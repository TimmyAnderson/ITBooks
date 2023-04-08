using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace Optimizations
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CParseTreeTraverseItem
	{
//-------------------------------------------------------------------------------------------------------
		private readonly CSymbol								MSymbol;
		private readonly CChoice								MChoice;
		private readonly DParseTreeTraverseAction				MPreOrderAction;
		private readonly DParseTreeTraverseAction				MPostOrderAction;
		private readonly int[]									MOrderIndexes;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CParseTreeTraverseItem(CTerminal Terminal, DParseTreeTraverseAction PreOrderAction, DParseTreeTraverseAction PostOrderAction, int[] OrderIndexes)
		{
			MSymbol=Terminal;
			MChoice=null;
			MPreOrderAction=PreOrderAction;
			MPostOrderAction=PostOrderAction;
			MOrderIndexes=OrderIndexes;
		}
//-------------------------------------------------------------------------------------------------------
		public CParseTreeTraverseItem(CChoice Choice, DParseTreeTraverseAction PreOrderAction, DParseTreeTraverseAction PostOrderAction, int[] OrderIndexes)
		{
			if (Choice.Symbols.Length!=OrderIndexes.Length)
			{
				throw(new CCompilerException(string.Format("INVALID ORDER INDEXES COUNT !")));
			}

			int[]												OrderedOrderIndexes=OrderIndexes.OrderBy(P => P).ToArray();

			for(int Index=0;Index<OrderedOrderIndexes.Length;Index++)
			{
				if (Index!=OrderedOrderIndexes[Index])
				{
					throw(new CCompilerException(string.Format("INVALID ORDER INDEXES STRUCTURE !")));
				}
			}

			MSymbol=Choice.Nonterminal;
			MChoice=Choice;
			MPreOrderAction=PreOrderAction;
			MPostOrderAction=PostOrderAction;
			MOrderIndexes=OrderIndexes;
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
		public DParseTreeTraverseAction							PreOrderAction
		{
			get
			{
				return(MPreOrderAction);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public DParseTreeTraverseAction							PostOrderAction
		{
			get
			{
				return(MPostOrderAction);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public int[]											OrderIndexes
		{
			get
			{
				return(MOrderIndexes);
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------