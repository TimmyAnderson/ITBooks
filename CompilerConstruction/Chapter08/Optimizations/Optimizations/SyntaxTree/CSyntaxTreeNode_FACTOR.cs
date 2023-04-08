using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace Optimizations
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CSyntaxTreeNode_FACTOR : CSyntaxTreeNode
	{
//-------------------------------------------------------------------------------------------------------
		private readonly CSyntaxTreeNode_EXPRESSION				MExpressionInBrackets;
		private readonly CSyntaxTreeNode_VARIABLE				MVariable;
		private readonly CSyntaxTreeNode_CALL					MCall;
		private readonly int									MNumber;
		private readonly string									MStringLiteral;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_FACTOR(CChoice Choice, CParsingStackItem ParsingStackItem)
			: base(Choice)
		{
			if (Choice.Symbols.Length==3 && Choice.Symbols[0].Name=="TerminalRoundBracketLeft" && Choice.Symbols[1].Name=="EXPRESSION" && Choice.Symbols[2].Name=="TerminalRoundBracketRight")
			{
				MExpressionInBrackets=(CSyntaxTreeNode_EXPRESSION) ParsingStackItem.SyntaxTreeNode;
				MChoiceNumber=1;
			}
			else if (Choice.Symbols.Length==1 && Choice.Symbols[0].Name=="VARIABLE")
			{
				MVariable=(CSyntaxTreeNode_VARIABLE) ParsingStackItem.SyntaxTreeNode;
				MChoiceNumber=2;
			}
			else if (Choice.Symbols.Length==1 && Choice.Symbols[0].Name=="CALL")
			{
				MCall=(CSyntaxTreeNode_CALL) ParsingStackItem.SyntaxTreeNode;
				MChoiceNumber=3;
			}
			else if (Choice.Symbols.Length==1 && Choice.Symbols[0].Name=="TerminalNumber")
			{
				int.TryParse(ParsingStackItem.ParseTreeNode.Token.Lexema,out MNumber);
				MChoiceNumber=4;
			}
			else if (Choice.Symbols.Length==1 && Choice.Symbols[0].Name=="TerminalString")
			{
				MStringLiteral=ParsingStackItem.ParseTreeNode.Token.Lexema;
				MChoiceNumber=5;
			}
			else
			{
				throw(new CCompilerException(string.Format("Invalid CHOICE [{0}] !",Choice)));
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_EXPRESSION						ExpressionInBrackets
		{
			get
			{
				return(MExpressionInBrackets);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_VARIABLE							Variable
		{
			get
			{
				return(MVariable);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_CALL								Call
		{
			get
			{
				return(MCall);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public int												Number
		{
			get
			{
				return(MNumber);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public string											StringLiteral
		{
			get
			{
				return(MStringLiteral);
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

				if (MExpressionInBrackets!=null)
				{
					SB.Append(string.Format("({0})",MExpressionInBrackets.PrintTree()));
				}
				else
				{
					SB.Append(string.Format("({0})","NULL"));
				}

				return(SB.ToString());
			}
			else if (MChoiceNumber==2)
			{
				StringBuilder									SB=new StringBuilder();

				if (MVariable!=null)
				{
					SB.Append(MVariable.PrintTree());
				}
				else
				{
					SB.Append("NULL");
				}

				return(SB.ToString());
			}
			else if (MChoiceNumber==3)
			{
				StringBuilder									SB=new StringBuilder();

				if (MCall!=null)
				{
					SB.Append(MCall.PrintTree());
				}
				else
				{
					SB.Append("NULL");
				}

				return(SB.ToString());
			}
			else if (MChoiceNumber==4)
			{
				StringBuilder									SB=new StringBuilder();

				SB.Append(string.Format("{0}",MNumber));

				return(SB.ToString());
			}
			else if (MChoiceNumber==5)
			{
				StringBuilder									SB=new StringBuilder();

				SB.Append(string.Format("{0}",MStringLiteral));

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