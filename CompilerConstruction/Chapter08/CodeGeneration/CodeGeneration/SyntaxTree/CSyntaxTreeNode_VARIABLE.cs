using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace CodeGeneration
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CSyntaxTreeNode_VARIABLE : CSyntaxTreeNode
	{
//-------------------------------------------------------------------------------------------------------
		private readonly string									MVariableName;
		private readonly CSyntaxTreeNode_EXPRESSION				MExpressionInSquareBrackets;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_VARIABLE(CChoice Choice, CParsingStackItem VariableName)
			: base(Choice)
		{
			MVariableName=VariableName.ParseTreeNode.Token.Lexema;
			MChoiceNumber=1;
		}
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_VARIABLE(CChoice Choice, CParsingStackItem VariableName, CParsingStackItem ExpressionInSquareBrackets)
			: base(Choice)
		{
			MVariableName=VariableName.ParseTreeNode.Token.Lexema;
			MExpressionInSquareBrackets=(CSyntaxTreeNode_EXPRESSION) ExpressionInSquareBrackets.SyntaxTreeNode;
			MChoiceNumber=2;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public string											VariableName
		{
			get
			{
				return(MVariableName);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_EXPRESSION						ExpressionInSquareBrackets
		{
			get
			{
				return(MExpressionInSquareBrackets);
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

				SB.Append(MVariableName);

				return(SB.ToString());
			}
			else if (MChoiceNumber==2)
			{
				StringBuilder			SB=new StringBuilder();

				if (MExpressionInSquareBrackets!=null)
				{
					SB.Append(string.Format("{0}[{1}]",MVariableName,MExpressionInSquareBrackets.PrintTree()));
				}
				else
				{
					SB.Append(string.Format("{0}[{1}]",MVariableName,"NULL"));
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