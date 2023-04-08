using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace Optimizations
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CSyntaxTreeNode_SELECTION_STATEMENT : CSyntaxTreeNode
	{
//-------------------------------------------------------------------------------------------------------
		private readonly CSyntaxTreeNode_EXPRESSION				MIfExpression;
		private readonly CSyntaxTreeNode_STATEMENT				MIfStatement;
		private readonly CSyntaxTreeNode_STATEMENT				MElseStatement;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_SELECTION_STATEMENT(CChoice Choice, CParsingStackItem IfExpression, CParsingStackItem IfStatement)
			: base(Choice)
		{
			MIfExpression=(CSyntaxTreeNode_EXPRESSION) IfExpression.SyntaxTreeNode;
			MIfStatement=(CSyntaxTreeNode_STATEMENT) IfStatement.SyntaxTreeNode;
			MChoiceNumber=1;
		}
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_SELECTION_STATEMENT(CChoice Choice, CParsingStackItem IfExpression, CParsingStackItem IfStatement, CParsingStackItem ElseStatement)
			: base(Choice)
		{
			MIfExpression=(CSyntaxTreeNode_EXPRESSION) IfExpression.SyntaxTreeNode;
			MIfStatement=(CSyntaxTreeNode_STATEMENT) IfStatement.SyntaxTreeNode;
			MElseStatement=(CSyntaxTreeNode_STATEMENT) ElseStatement.SyntaxTreeNode;
			MChoiceNumber=2;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_EXPRESSION						IfExpression
		{
			get
			{
				return(MIfExpression);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_STATEMENT						IfStatement
		{
			get
			{
				return(MIfStatement);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_STATEMENT						ElseStatement
		{
			get
			{
				return(MElseStatement);
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

				if (MIfExpression!=null)
				{
					SB.AppendLine(string.Format("if ({0})",MIfExpression.PrintTree()));
				}
				else
				{
					SB.AppendLine(string.Format("if ({0})","NULL"));
				}

				if (MIfStatement!=null)
				{
					SB.Append(MIfStatement.PrintTree());
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

				if (MIfExpression!=null)
				{
					SB.AppendLine(string.Format("if ({0})",MIfExpression.PrintTree()));
				}
				else
				{
					SB.AppendLine(string.Format("if ({0})","NULL"));
				}

				if (MIfStatement!=null)
				{
					SB.Append(MIfStatement.PrintTree());
				}
				else
				{
					SB.Append("NULL");
				}

				SB.AppendLine("else");

				if (MElseStatement!=null)
				{
					SB.Append(MElseStatement.PrintTree());
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