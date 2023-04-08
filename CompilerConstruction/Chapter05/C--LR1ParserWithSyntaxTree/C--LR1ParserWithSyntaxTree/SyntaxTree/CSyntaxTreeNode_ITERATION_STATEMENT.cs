using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace C__LR1ParserWithSyntaxTree
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CSyntaxTreeNode_ITERATION_STATEMENT : CSyntaxTreeNode
	{
//-------------------------------------------------------------------------------------------------------
		private readonly CSyntaxTreeNode_EXPRESSION				MWhileExpression;
		private readonly CSyntaxTreeNode_STATEMENT				MWhileStatement;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_ITERATION_STATEMENT(CChoice Choice, CParsingStackItem WhileExpression, CParsingStackItem WhileStatement)
			: base(Choice)
		{
			MWhileExpression=(CSyntaxTreeNode_EXPRESSION) WhileExpression.SyntaxTreeNode;
			MWhileStatement=(CSyntaxTreeNode_STATEMENT) WhileStatement.SyntaxTreeNode;
			MChoiceNumber=1;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_EXPRESSION						WhileExpression
		{
			get
			{
				return(MWhileExpression);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_STATEMENT						WhileStatement
		{
			get
			{
				return(MWhileStatement);
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

				if (MWhileExpression!=null)
				{
					SB.AppendLine(string.Format("while ({0})",MWhileExpression.PrintTree()));
				}
				else
				{
					SB.AppendLine(string.Format("while ({0})","NULL"));
				}

				if (MWhileStatement!=null)
				{
					SB.Append(MWhileStatement.PrintTree());
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