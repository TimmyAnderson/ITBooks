using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace C__LR1ParserWithSyntaxTree
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CSyntaxTreeNode_EXPRESSION : CSyntaxTreeNode
	{
//-------------------------------------------------------------------------------------------------------
		private readonly CSyntaxTreeNode_VARIABLE				MVariable;
		private readonly CSyntaxTreeNode_EXPRESSION				MExpression;
		private readonly CSyntaxTreeNode_SIMPLE_EXPRESSION		MSimpleExpression;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_EXPRESSION(CChoice Choice, CParsingStackItem Variable, CParsingStackItem Expression)
			: base(Choice)
		{
			MVariable=(CSyntaxTreeNode_VARIABLE) Variable.SyntaxTreeNode;
			MExpression=(CSyntaxTreeNode_EXPRESSION) Expression.SyntaxTreeNode;
			MChoiceNumber=1;
		}
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_EXPRESSION(CChoice Choice, CParsingStackItem SimpleExpression)
			: base(Choice)
		{
			MSimpleExpression=(CSyntaxTreeNode_SIMPLE_EXPRESSION) SimpleExpression.SyntaxTreeNode;
			MChoiceNumber=2;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_VARIABLE							Variable
		{
			get
			{
				return(MVariable);
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
		public CSyntaxTreeNode_SIMPLE_EXPRESSION				SimpleExpression
		{
			get
			{
				return(MSimpleExpression);
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

				if (MVariable!=null && MExpression!=null)
				{
					SB.Append(string.Format("{0}={1}",MVariable.PrintTree(),MExpression.PrintTree()));
				}
				else if (MVariable!=null && MExpression==null)
				{
					SB.Append(string.Format("{0}={1}",MVariable.PrintTree(),"NULL"));
				}
				else if (MVariable==null && MExpression!=null)
				{
					SB.Append(string.Format("{0}={1}","NULL",MExpression.PrintTree()));
				}
				else
				{
					SB.Append(string.Format("{0}={1}","NULL","NULL"));
				}

				return(SB.ToString());
			}
			else if (MChoiceNumber==2)
			{
				StringBuilder			SB=new StringBuilder();

				if (MSimpleExpression!=null)
				{
					SB.Append(MSimpleExpression.PrintTree());
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