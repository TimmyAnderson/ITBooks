using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace CodeGeneration
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CCodeGenerationTraverseItemList
	{
//-------------------------------------------------------------------------------------------------------
		private readonly List<CCodeGenerationTraverseItem>		MTraverseItems;
		private readonly DCodeGenerationTraverseAction			MDefaultPreOrderAction;
		private readonly DCodeGenerationInOrderTraverseAction	MDefaultInPreOrderAction;
		private readonly DCodeGenerationInOrderTraverseAction	MDefaultInPostOrderAction;
		private readonly DCodeGenerationTraverseAction			MDefaultPostOrderAction;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CCodeGenerationTraverseItemList(DCodeGenerationTraverseAction DefaultPreOrderAction, DCodeGenerationInOrderTraverseAction DefaultInPreOrderAction, DCodeGenerationInOrderTraverseAction DefaultInPostOrderAction, DCodeGenerationTraverseAction DefaultPostOrderAction)
		{
			MTraverseItems=new List<CCodeGenerationTraverseItem>();

			if (DefaultPreOrderAction!=null)
			{
				MDefaultPreOrderAction=DefaultPreOrderAction;
			}
			else
			{
				MDefaultPreOrderAction=DefaultDummyAction;
			}

			if (DefaultInPreOrderAction!=null)
			{
				MDefaultInPreOrderAction=DefaultInPreOrderAction;
			}
			else
			{
				MDefaultInPreOrderAction=DefaultDummyInOrderAction;
			}

			if (DefaultInPostOrderAction!=null)
			{
				MDefaultInPostOrderAction=DefaultInPostOrderAction;
			}
			else
			{
				MDefaultInPostOrderAction=DefaultDummyInOrderAction;
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
		public DCodeGenerationTraverseAction					DefaultPreOrderAction
		{
			get
			{
				return(MDefaultPreOrderAction);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public DCodeGenerationInOrderTraverseAction				DefaultInPreOrderAction
		{
			get
			{
				return(MDefaultInPreOrderAction);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public DCodeGenerationInOrderTraverseAction				DefaultInPostOrderAction
		{
			get
			{
				return(MDefaultInPostOrderAction);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public DCodeGenerationTraverseAction					DefaultPostOrderAction
		{
			get
			{
				return(MDefaultPostOrderAction);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private void DefaultDummyAction(CParseTreeNode Node, CCodeGenerationTraverseItem TraverseItem)
		{
			// Empty.
		}
//-------------------------------------------------------------------------------------------------------
		private void DefaultDummyInOrderAction(CParseTreeNode Node, CCodeGenerationTraverseItem TraverseItem, CParseTreeNode ChildNode)
		{
			// Empty.
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void AddTraverseItem(CCodeGenerationTraverseItem TraverseItem)
		{
			if ((TraverseItem.Symbol is CTerminal)==true)
			{
				CCodeGenerationTraverseItem		ExistingTraverseItem=MTraverseItems.Where(P => P.Symbol.Equals(TraverseItem.Symbol)==true).FirstOrDefault();

				if (ExistingTraverseItem!=null)
				{
					throw(new InvalidOperationException(string.Format("TRAVERSE ITEM LIST already contains TERMINAL [{0}] !",TraverseItem.Symbol)));
				}
			}
			else
			{
				CCodeGenerationTraverseItem		ExistingTraverseItem=MTraverseItems.Where(P => P.Choice.Equals(TraverseItem.Symbol)==true).FirstOrDefault();

				if (ExistingTraverseItem!=null)
				{
					throw(new InvalidOperationException(string.Format("TRAVERSE ITEM LIST already contains NONTERMINAL CHOICE [{0}] !",TraverseItem.Choice)));
				}
			}

			MTraverseItems.Add(TraverseItem);
		}
//-------------------------------------------------------------------------------------------------------
		public CCodeGenerationTraverseItem GetItem(CParseTreeNode TreeNode)
		{
			foreach(CCodeGenerationTraverseItem TraverseItem in MTraverseItems)
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