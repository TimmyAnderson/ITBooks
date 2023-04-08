using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace SemanticAnalyzer
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CParseTreeTraverseItemList
	{
//-------------------------------------------------------------------------------------------------------
		private readonly List<CParseTreeTraverseItem>			MTraverseItems;
		private readonly DParseTreeTraverseAction				MDefaultPreOrderAction;
		private readonly DParseTreeTraverseAction				MDefaultPostOrderAction;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CParseTreeTraverseItemList(DParseTreeTraverseAction DefaultPreOrderAction, DParseTreeTraverseAction DefaultPostOrderAction)
		{
			MTraverseItems=new List<CParseTreeTraverseItem>();

			if (DefaultPreOrderAction!=null)
			{
				MDefaultPreOrderAction=DefaultPreOrderAction;
			}
			else
			{
				MDefaultPreOrderAction=DefaultDummyAction;
			}

			if (DefaultPostOrderAction!=null)
			{
				MDefaultPostOrderAction=DefaultPostOrderAction;
			}
			else
			{
				MDefaultPostOrderAction=DefaultDummyAction;
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public DParseTreeTraverseAction							DefaultPreOrderAction
		{
			get
			{
				return(MDefaultPreOrderAction);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public DParseTreeTraverseAction							DefaultPostOrderAction
		{
			get
			{
				return(MDefaultPostOrderAction);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private void DefaultDummyAction(CParseTreeNode Node, CParseTreeTraverseItem TraverseItem)
		{
			// Empty.
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void AddTraverseItem(CParseTreeTraverseItem TraverseItem)
		{
			if ((TraverseItem.Symbol is CTerminal)==true)
			{
				CParseTreeTraverseItem			ExistingTraverseItem=MTraverseItems.Where(P => P.Symbol.Equals(TraverseItem.Symbol)==true).FirstOrDefault();

				if (ExistingTraverseItem!=null)
				{
					throw(new InvalidOperationException(string.Format("TRAVERSE ITEM LIST already contains TERMINAL [{0}] !",TraverseItem.Symbol)));
				}
			}
			else
			{
				CParseTreeTraverseItem			ExistingTraverseItem=MTraverseItems.Where(P => P.Choice.Equals(TraverseItem.Symbol)==true).FirstOrDefault();

				if (ExistingTraverseItem!=null)
				{
					throw(new InvalidOperationException(string.Format("TRAVERSE ITEM LIST already contains NONTERMINAL CHOICE [{0}] !",TraverseItem.Choice)));
				}
			}

			MTraverseItems.Add(TraverseItem);
		}
//-------------------------------------------------------------------------------------------------------
		public CParseTreeTraverseItem GetItem(CParseTreeNode TreeNode)
		{
			foreach(CParseTreeTraverseItem TraverseItem in MTraverseItems)
			{
				if ((TraverseItem.Symbol is CTerminal)==true)
				{
					if (TraverseItem.Symbol.Equals(TreeNode.Symbol)==true)
					{
						return(TraverseItem);
					}
				}
				else
				{
					if (TraverseItem.Symbol.Equals(TreeNode.Symbol)==true)
					{
						if (TraverseItem.Choice.Symbols.Length==TreeNode.ChildNodes.Length)
						{
							bool			Equal=true;

							for(int i=0;i<TraverseItem.Choice.Symbols.Length;i++)
							{
								if (TraverseItem.Choice.Symbols[i].Equals(TreeNode.ChildNodes[i].Symbol)==false)
								{
									Equal=false;
									break;
								}
							}

							if (Equal==true)
							{
								return(TraverseItem);
							}
						}
					}
				}
			}

			return(null);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------