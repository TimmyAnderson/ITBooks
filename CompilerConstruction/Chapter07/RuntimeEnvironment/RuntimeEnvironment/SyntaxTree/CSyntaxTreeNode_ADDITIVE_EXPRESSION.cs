using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace RuntimeEnvironment
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CSyntaxTreeNode_ADDITIVE_EXPRESSION : CSyntaxTreeNode
	{
//-------------------------------------------------------------------------------------------------------
		private readonly CSyntaxTreeNode_ADDITIVE_EXPRESSION	MAdditiveExpression;
		private readonly CSyntaxTreeNode_ADD_OPERATION			MAddOperation;
		private readonly CSyntaxTreeNode_TERM					MTerm;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_ADDITIVE_EXPRESSION(CChoice Choice, CParsingStackItem AdditiveExpression, CParsingStackItem AddOperation, CParsingStackItem Term)
			: base(Choice)
		{
			MAdditiveExpression=(CSyntaxTreeNode_ADDITIVE_EXPRESSION) AdditiveExpression.SyntaxTreeNode;
			MAddOperation=(CSyntaxTreeNode_ADD_OPERATION) AddOperation.SyntaxTreeNode;
			MTerm=(CSyntaxTreeNode_TERM) Term.SyntaxTreeNode;
			MChoiceNumber=1;
		}
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_ADDITIVE_EXPRESSION(CChoice Choice, CParsingStackItem Term)
			: base(Choice)
		{
			MTerm=(CSyntaxTreeNode_TERM) Term.SyntaxTreeNode;
			MChoiceNumber=2;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_ADDITIVE_EXPRESSION				AdditiveExpression
		{
			get
			{
				return(MAdditiveExpression);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_ADD_OPERATION					AddOperation
		{
			get
			{
				return(MAddOperation);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_TERM								Term
		{
			get
			{
				return(MTerm);
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

				if (MAdditiveExpression!=null)
				{
					SB.Append(MAdditiveExpression.PrintTree());
				}
				else
				{
					SB.Append("NULL");
				}

				if (MAddOperation!=null)
				{
					SB.Append(MAddOperation.PrintTree());
				}
				else
				{
					SB.Append("NULL");
				}

				if (MTerm!=null)
				{
					SB.Append(MTerm.PrintTree());
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

				if (MTerm!=null)
				{
					SB.Append(MTerm.PrintTree());
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