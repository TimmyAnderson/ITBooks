using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace RuntimeEnvironment
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CSyntaxTreeNode_EXPRESSION : CSyntaxTreeNode
	{
//-------------------------------------------------------------------------------------------------------
		private readonly CSyntaxTreeNode_ADDITIVE_EXPRESSION	MAdditiveExpression1;
		private readonly CSyntaxTreeNode_COMPARE_OPERATION		MCompareOperation;
		private readonly CSyntaxTreeNode_ADDITIVE_EXPRESSION	MAdditiveExpression2;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_EXPRESSION(CChoice Choice, CParsingStackItem AdditiveExpression1, CParsingStackItem CompareOperation, CParsingStackItem AdditiveExpression2)
			: base(Choice)
		{
			MAdditiveExpression1=(CSyntaxTreeNode_ADDITIVE_EXPRESSION) AdditiveExpression1.SyntaxTreeNode;
			MCompareOperation=(CSyntaxTreeNode_COMPARE_OPERATION) CompareOperation.SyntaxTreeNode;
			MAdditiveExpression2=(CSyntaxTreeNode_ADDITIVE_EXPRESSION) AdditiveExpression2.SyntaxTreeNode;
			MChoiceNumber=1;
		}
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_EXPRESSION(CChoice Choice, CParsingStackItem AdditiveExpression)
			: base(Choice)
		{
			MAdditiveExpression1=(CSyntaxTreeNode_ADDITIVE_EXPRESSION) AdditiveExpression.SyntaxTreeNode;
			MChoiceNumber=2;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_ADDITIVE_EXPRESSION				Term
		{
			get
			{
				return(MAdditiveExpression1);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_COMPARE_OPERATION				CompareOperation
		{
			get
			{
				return(MCompareOperation);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_ADDITIVE_EXPRESSION				Factor
		{
			get
			{
				return(MAdditiveExpression2);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override string PrintTree()
		{
			if (MChoiceNumber==1)
			{
				StringBuilder			SB=new StringBuilder();

				if (MAdditiveExpression1!=null)
				{
					SB.Append(MAdditiveExpression1.PrintTree());
				}
				else
				{
					SB.Append("NULL");
				}

				if (MCompareOperation!=null)
				{
					SB.Append(MCompareOperation.PrintTree());
				}
				else
				{
					SB.Append("NULL");
				}

				if (MAdditiveExpression1!=null)
				{
					SB.Append(MAdditiveExpression2.PrintTree());
				}
				else
				{
					SB.Append("NULL");
				}

				return(SB.ToString());
			}
			else if (MChoiceNumber==2)
			{
				StringBuilder			SB=new StringBuilder();

				if (MAdditiveExpression1!=null)
				{
					SB.Append(MAdditiveExpression1.PrintTree());
				}
				else
				{
					SB.Append("NULL");
				}

				return(SB.ToString());
			}
			else
			{
				throw(new InvalidOperationException(string.Format("Invalid CHOICE [{0}] !",Choice)));
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------