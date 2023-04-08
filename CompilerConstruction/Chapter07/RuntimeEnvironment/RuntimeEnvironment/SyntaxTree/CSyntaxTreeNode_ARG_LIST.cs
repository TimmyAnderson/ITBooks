using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace RuntimeEnvironment
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CSyntaxTreeNode_ARG_LIST : CSyntaxTreeNode
	{
//-------------------------------------------------------------------------------------------------------
		private readonly CSyntaxTreeNode_ARG_LIST				MArgList;
		private readonly CSyntaxTreeNode_EXPRESSION				MExpression;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_ARG_LIST(CChoice Choice, CParsingStackItem ArgList, CParsingStackItem Expression)
			: base(Choice)
		{
			MArgList=(CSyntaxTreeNode_ARG_LIST) ArgList.SyntaxTreeNode;
			MExpression=(CSyntaxTreeNode_EXPRESSION) Expression.SyntaxTreeNode;
			MChoiceNumber=1;
		}
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_ARG_LIST(CChoice Choice, CParsingStackItem Expression)
			: base(Choice)
		{
			MExpression=(CSyntaxTreeNode_EXPRESSION) Expression.SyntaxTreeNode;
			MChoiceNumber=2;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_ARG_LIST							ArgList
		{
			get
			{
				return(MArgList);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_EXPRESSION						Expression
		{
			get
			{
				return(MExpression);
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

				if (MArgList!=null && MExpression!=null)
				{
					SB.Append(string.Format("{0},{1}",MArgList.PrintTree(),MExpression.PrintTree()));
				}
				else if (MArgList!=null && MExpression==null)
				{
					SB.Append(string.Format("{0},{1}",MArgList.PrintTree(),"NULL"));
				}
				else if (MArgList==null && MExpression!=null)
				{
					SB.Append(string.Format("{0},{1}","NULL",MExpression.PrintTree()));
				}
				else
				{
					SB.Append(string.Format("{0},{1}","NULL","NULL"));
				}

				return(SB.ToString());
			}
			else if (MChoiceNumber==2)
			{
				StringBuilder			SB=new StringBuilder();

				if (MExpression!=null)
				{
					SB.Append(MExpression.PrintTree());
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