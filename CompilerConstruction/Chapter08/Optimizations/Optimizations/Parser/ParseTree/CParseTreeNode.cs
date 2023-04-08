using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace Optimizations
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CParseTreeNode
	{
//-------------------------------------------------------------------------------------------------------
		private readonly CSymbol								MSymbol;
		private readonly CToken									MToken;
		private readonly List<CParseTreeNode>					MChildNodes;
		private readonly List<CParseTreeNodeData>				MTreeNodeData;
		private readonly Dictionary<string,string>				MCodeGenerationProperties;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CParseTreeNode(CSymbol Symbol, CToken Token)
		{
			MSymbol=Symbol;
			MToken=Token;
			MChildNodes=new List<CParseTreeNode>();
			MTreeNodeData=new List<CParseTreeNodeData>();
			MCodeGenerationProperties=new Dictionary<string,string>();
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
		public CToken											Token
		{
			get
			{
				return(MToken);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public CParseTreeNode[]									ChildNodes
		{
			get
			{
				return(MChildNodes.ToArray());
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private void PrintTree(StringBuilder SB, int Offset)
		{
			SB.Append("".PadRight(Offset,' '));

			if (MToken==null)
			{
				SB.AppendLine(MSymbol.ToString());
			}
			else
			{
				SB.AppendLine(MToken.Lexema.ToString());
			}

			Offset++;

			foreach (CParseTreeNode ChildNode in MChildNodes)
			{
				ChildNode.PrintTree(SB,Offset);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void Traverse(CParseTreeTraverseItemList TraverseList)
		{
			CParseTreeTraverseItem								TraverseItem=TraverseList.GetItem(this);
			int[]												Order;
			
			if (TraverseItem!=null)
			{
				if (TraverseItem.PreOrderAction!=null)
				{
					TraverseItem.PreOrderAction(this,TraverseItem);
				}
				else
				{
					TraverseList.DefaultPreOrderAction(this,TraverseItem);
				}

				Order=TraverseItem.OrderIndexes;
			}
			else
			{
				TraverseList.DefaultPreOrderAction(this,TraverseItem);

				Order=new int[MChildNodes.Count];

				for(int Index=0;Index<Order.Length;Index++)
				{
					Order[Index]=Index;
				}
			}

			List<CParseTreeNode>								OrderedChildNodes;

			if ((MSymbol is CNonterminal)==true)
			{
				CNonterminal									Nonterminal=(CNonterminal) MSymbol;

				OrderedChildNodes=new List<CParseTreeNode>();

				foreach(int OrderIndex in Order)
				{
					CParseTreeNode								Node=MChildNodes[OrderIndex];

					OrderedChildNodes.Add(Node);
				}
			}
			else
			{
				OrderedChildNodes=MChildNodes;
			}

			foreach(CParseTreeNode Node in OrderedChildNodes)
			{
				Node.Traverse(TraverseList);
			}

			if (TraverseItem!=null)
			{
				if (TraverseItem.PostOrderAction!=null)
				{
					TraverseItem.PostOrderAction(this,TraverseItem);
				}
				else
				{
					TraverseList.DefaultPostOrderAction(this,TraverseItem);
				}
			}
			else
			{
				TraverseList.DefaultPostOrderAction(this,TraverseItem);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public void TraverseForCodeGeneration(CCodeGenerationTraverseItemList TraverseList)
		{
			CCodeGenerationTraverseItem							TraverseItem=TraverseList.GetItem(this);
			
			if (TraverseItem!=null)
			{
				if (TraverseItem.PreOrderAction!=null)
				{
					TraverseItem.PreOrderAction(this,TraverseItem);
				}
				else
				{
					TraverseList.DefaultPreOrderAction(this,TraverseItem);
				}
			}
			else
			{
				TraverseList.DefaultPreOrderAction(this,TraverseItem);
			}

			foreach(CParseTreeNode Node in MChildNodes)
			{
				if (TraverseItem!=null)
				{
					if (TraverseItem.InPreOrderAction!=null)
					{
						TraverseItem.InPreOrderAction(this,TraverseItem,Node);
					}
					else
					{
						TraverseList.DefaultInPreOrderAction(this,TraverseItem,Node);
					}
				}
				else
				{
					TraverseList.DefaultInPreOrderAction(this,TraverseItem,Node);
				}

				Node.TraverseForCodeGeneration(TraverseList);

				if (TraverseItem!=null)
				{
					if (TraverseItem.InPostOrderAction!=null)
					{
						TraverseItem.InPostOrderAction(this,TraverseItem,Node);
					}
					else
					{
						TraverseList.DefaultInPreOrderAction(this,TraverseItem,Node);
					}
				}
				else
				{
					TraverseList.DefaultInPreOrderAction(this,TraverseItem,Node);
				}
			}

			if (TraverseItem!=null)
			{
				if (TraverseItem.PostOrderAction!=null)
				{
					TraverseItem.PostOrderAction(this,TraverseItem);
				}
				else
				{
					TraverseList.DefaultPostOrderAction(this,TraverseItem);
				}
			}
			else
			{
				TraverseList.DefaultPostOrderAction(this,TraverseItem);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public void AddChildNode(CParseTreeNode ChildNode)
		{
			MChildNodes.Add(ChildNode);
		}
//-------------------------------------------------------------------------------------------------------
		public string PrintTree()
		{
			StringBuilder										SB=new StringBuilder();

			PrintTree(SB,0);

			return(SB.ToString());
		}
//-------------------------------------------------------------------------------------------------------
		public TTreeNodeData GetTreeNodeData<TTreeNodeData>() where TTreeNodeData : CParseTreeNodeData
		{
			TTreeNodeData										Ret=MTreeNodeData.OfType<TTreeNodeData>().FirstOrDefault();

			return(Ret);
		}
//-------------------------------------------------------------------------------------------------------
		public void SetTreeNodeData(CParseTreeNodeData TreeNodeData)
		{
			Type												TreeNodeDataType=TreeNodeData.GetType();
			CParseTreeNodeData									ExistingTreeNodeData=MTreeNodeData.Where(P => P.GetType()==TreeNodeDataType).FirstOrDefault();

			if (ExistingTreeNodeData!=null)
			{
				MTreeNodeData.Remove(ExistingTreeNodeData);
			}

			MTreeNodeData.Add(TreeNodeData);
		}
//-------------------------------------------------------------------------------------------------------
		public CParseTreeNode GetChildTreeNodeBySymbolName(string SymbolName, int SymbolIndex)
		{
			int													IndexCounter=0;

			foreach(CParseTreeNode ChildNode in MChildNodes)
			{
				if (ChildNode.MSymbol.Name==SymbolName)
				{
					if (IndexCounter<SymbolIndex)
					{
						IndexCounter++;
					}
					else
					{
						return(ChildNode);
					}
				}
			}

			throw(new CCompilerException(string.Format("Can't find CHILD SYMBOL [{0}] with INDEX [{1}] in SYMBOL [{2}] !",Symbol,SymbolIndex,MSymbol)));
		}
//-------------------------------------------------------------------------------------------------------
		public CParseTreeNode GetChildTreeNodeBySymbolNameOrNULL(string SymbolName, int SymbolIndex)
		{
			int													IndexCounter=0;

			foreach(CParseTreeNode ChildNode in MChildNodes)
			{
				if (ChildNode.MSymbol.Name==SymbolName)
				{
					if (IndexCounter<SymbolIndex)
					{
						IndexCounter++;
					}
					else
					{
						return(ChildNode);
					}
				}
			}

			return(null);
		}
//-------------------------------------------------------------------------------------------------------
		public CParseTreeNode GetChildTreeNodeBySymbolName(string[] SymbolNames, int SymbolIndex)
		{
			int													IndexCounter=0;

			foreach(CParseTreeNode ChildNode in MChildNodes)
			{
				if (SymbolNames.Contains(ChildNode.MSymbol.Name)==true)
				{
					if (IndexCounter<SymbolIndex)
					{
						IndexCounter++;
					}
					else
					{
						return(ChildNode);
					}
				}
			}

			throw(new CCompilerException(string.Format("Can't find CHILD SYMBOL [{0}] with INDEX [{1}] in SYMBOL [{2}] !",Symbol,SymbolIndex,MSymbol)));
		}
//-------------------------------------------------------------------------------------------------------
		public void ClearCodeGenerationProperties()
		{
			MCodeGenerationProperties.Clear();

			foreach(CParseTreeNode ParseTreeNode in MChildNodes)
			{
				ParseTreeNode.ClearCodeGenerationProperties();
			}
		}
//-------------------------------------------------------------------------------------------------------
		public string GetCodeGenerationProperty(string PropertyName)
		{
			return(MCodeGenerationProperties[PropertyName]);
		}
//-------------------------------------------------------------------------------------------------------
		public void SetCodeGenerationProperty(string PropertyName, string Value)
		{
			MCodeGenerationProperties.Add(PropertyName,Value);
		}
//-------------------------------------------------------------------------------------------------------
		public override string ToString()
		{
			StringBuilder										SB=new StringBuilder();

			SB.AppendFormat("Symbol: [{0}]",MSymbol);

			return(SB.ToString());
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------