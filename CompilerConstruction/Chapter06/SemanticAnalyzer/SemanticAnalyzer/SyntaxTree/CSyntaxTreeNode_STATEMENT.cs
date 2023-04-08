using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace SemanticAnalyzer
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CSyntaxTreeNode_STATEMENT : CSyntaxTreeNode
	{
//-------------------------------------------------------------------------------------------------------
		private readonly CSyntaxTreeNode_EXPRESSION_STATEMENT	MExpressionStatement;
		private readonly CSyntaxTreeNode_COMPOUND_STATEMENT		MCompoundStatement;
		private readonly CSyntaxTreeNode_SELECTION_STATEMENT	MSelectionStatement;
		private readonly CSyntaxTreeNode_ITERATION_STATEMENT	MIterationStatement;
		private readonly CSyntaxTreeNode_RETURN_STATEMENT		MReturnStatement;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_STATEMENT(CChoice Choice, CParsingStackItem ParsingStackItem)
			: base(Choice)
		{
			if (Choice.Symbols.Length==1 && Choice.Symbols[0].Name=="EXPRESSION_STATEMENT")
			{
				MExpressionStatement=(CSyntaxTreeNode_EXPRESSION_STATEMENT) ParsingStackItem.SyntaxTreeNode;
				MChoiceNumber=1;
			}
			else if (Choice.Symbols.Length==1 && Choice.Symbols[0].Name=="COMPOUND_STATEMENT")
			{
				MCompoundStatement=(CSyntaxTreeNode_COMPOUND_STATEMENT) ParsingStackItem.SyntaxTreeNode;
				MChoiceNumber=2;
			}
			else if (Choice.Symbols.Length==1 && Choice.Symbols[0].Name=="SELECTION_STATEMENT")
			{
				MSelectionStatement=(CSyntaxTreeNode_SELECTION_STATEMENT) ParsingStackItem.SyntaxTreeNode;
				MChoiceNumber=3;
			}
			else if (Choice.Symbols.Length==1 && Choice.Symbols[0].Name=="ITERATION_STATEMENT")
			{
				MIterationStatement=(CSyntaxTreeNode_ITERATION_STATEMENT) ParsingStackItem.SyntaxTreeNode;
				MChoiceNumber=4;
			}
			else if (Choice.Symbols.Length==1 && Choice.Symbols[0].Name=="RETURN_STATEMENT")
			{
				MReturnStatement=(CSyntaxTreeNode_RETURN_STATEMENT) ParsingStackItem.SyntaxTreeNode;
				MChoiceNumber=5;
			}
			else
			{
				throw(new InvalidOperationException(string.Format("Invalid CHOICE [{0}] !",Choice)));
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_EXPRESSION_STATEMENT				ExpressionStatement
		{
			get
			{
				return(MExpressionStatement);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_COMPOUND_STATEMENT				CompoundStatement
		{
			get
			{
				return(MCompoundStatement);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_SELECTION_STATEMENT				SelectionStatement
		{
			get
			{
				return(MSelectionStatement);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_ITERATION_STATEMENT				IterationStatement
		{
			get
			{
				return(MIterationStatement);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_RETURN_STATEMENT					ReturnStatement
		{
			get
			{
				return(MReturnStatement);
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

				if (MExpressionStatement!=null)
				{
					SB.Append(MExpressionStatement.PrintTree());
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

				if (MCompoundStatement!=null)
				{
					SB.Append(MCompoundStatement.PrintTree());
				}
				else
				{
					SB.Append("NULL");
				}

				return(SB.ToString());
			}
			else if (MChoiceNumber==3)
			{
				StringBuilder			SB=new StringBuilder();

				if (MSelectionStatement!=null)
				{
					SB.Append(MSelectionStatement.PrintTree());
				}
				else
				{
					SB.Append("NULL");
				}

				return(SB.ToString());
			}
			else if (MChoiceNumber==4)
			{
				StringBuilder			SB=new StringBuilder();

				if (MIterationStatement!=null)
				{
					SB.Append(MIterationStatement.PrintTree());
				}
				else
				{
					SB.Append("NULL");
				}

				return(SB.ToString());
			}
			else if (MChoiceNumber==5)
			{
				StringBuilder			SB=new StringBuilder();

				if (MReturnStatement!=null)
				{
					SB.Append(MReturnStatement.PrintTree());
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