using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace Optimizations
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CSyntaxTreeNode_TERM : CSyntaxTreeNode
	{
//-------------------------------------------------------------------------------------------------------
		private readonly CSyntaxTreeNode_TERM					MTerm;
		private readonly CSyntaxTreeNode_MUL_OPERATION			MMulOperation;
		private readonly CSyntaxTreeNode_FACTOR					MFactor;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_TERM(CChoice Choice, CParsingStackItem Term, CParsingStackItem MulOperation, CParsingStackItem Factor)
			: base(Choice)
		{
			MTerm=(CSyntaxTreeNode_TERM) Term.SyntaxTreeNode;
			MMulOperation=(CSyntaxTreeNode_MUL_OPERATION) MulOperation.SyntaxTreeNode;
			MFactor=(CSyntaxTreeNode_FACTOR) Factor.SyntaxTreeNode;
			MChoiceNumber=1;
		}
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_TERM(CChoice Choice, CParsingStackItem Factor)
			: base(Choice)
		{
			MFactor=(CSyntaxTreeNode_FACTOR) Factor.SyntaxTreeNode;
			MChoiceNumber=2;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_TERM								Term
		{
			get
			{
				return(MTerm);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_MUL_OPERATION					MulOperation
		{
			get
			{
				return(MMulOperation);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_FACTOR							Factor
		{
			get
			{
				return(MFactor);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override string PrintTree()
		{
			if (MChoiceNumber==1)
			{
				StringBuilder									SB=new StringBuilder();

				if (MTerm!=null)
				{
					SB.Append(MTerm.PrintTree());
				}
				else
				{
					SB.Append("NULL");
				}

				if (MulOperation!=null)
				{
					SB.Append(MulOperation.PrintTree());
				}
				else
				{
					SB.Append("NULL");
				}

				if (MFactor!=null)
				{
					SB.Append(MFactor.PrintTree());
				}
				else
				{
					SB.Append("NULL");
				}

				return(SB.ToString());
			}
			else if (MChoiceNumber==2)
			{
				StringBuilder									SB=new StringBuilder();

				if (MFactor!=null)
				{
					SB.Append(MFactor.PrintTree());
				}
				else
				{
					SB.Append("NULL");
				}

				return(SB.ToString());
			}
			else
			{
				throw(new CCompilerException(string.Format("Invalid CHOICE [{0}] !",Choice)));
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------