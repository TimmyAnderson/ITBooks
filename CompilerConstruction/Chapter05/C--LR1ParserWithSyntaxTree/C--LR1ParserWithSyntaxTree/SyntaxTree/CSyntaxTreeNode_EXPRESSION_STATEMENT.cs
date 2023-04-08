using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace C__LR1ParserWithSyntaxTree
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CSyntaxTreeNode_EXPRESSION_STATEMENT : CSyntaxTreeNode
	{
//-------------------------------------------------------------------------------------------------------
		private readonly CSyntaxTreeNode_EXPRESSION				MExpression;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_EXPRESSION_STATEMENT(CChoice Choice, CParsingStackItem Expression)
			: base(Choice)
		{
			MExpression=(CSyntaxTreeNode_EXPRESSION) Expression.SyntaxTreeNode;
			MChoiceNumber=1;
		}
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_EXPRESSION_STATEMENT(CChoice Choice)
			: base(Choice)
		{
			MChoiceNumber=2;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
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

				if (MExpression!=null)
				{
					SB.AppendLine(string.Format("{0};",MExpression.PrintTree()));
				}
				else
				{
					SB.AppendLine(string.Format("{0};","NULL"));
				}

				return(SB.ToString());
			}
			else if (MChoiceNumber==2)
			{
				StringBuilder			SB=new StringBuilder();

				SB.AppendLine(";");

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