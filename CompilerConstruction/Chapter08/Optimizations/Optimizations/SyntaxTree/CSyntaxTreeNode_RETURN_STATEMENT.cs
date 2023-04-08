using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace Optimizations
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CSyntaxTreeNode_RETURN_STATEMENT : CSyntaxTreeNode
	{
//-------------------------------------------------------------------------------------------------------
		private readonly CSyntaxTreeNode_EXPRESSION				MReturnExpression;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_RETURN_STATEMENT(CChoice Choice)
			: base(Choice)
		{
			MChoiceNumber=1;
		}
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_RETURN_STATEMENT(CChoice Choice, CParsingStackItem ReturnExpression)
			: base(Choice)
		{
			MReturnExpression=(CSyntaxTreeNode_EXPRESSION) ReturnExpression.SyntaxTreeNode;
			MChoiceNumber=2;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_EXPRESSION						ReturnExpression
		{
			get
			{
				return(MReturnExpression);
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

				SB.AppendLine(string.Format("return;"));

				return(SB.ToString());
			}
			else if (MChoiceNumber==2)
			{
				StringBuilder									SB=new StringBuilder();

				if (MReturnExpression!=null)
				{
					SB.AppendLine(string.Format("return ({0});",MReturnExpression.PrintTree()));
				}
				else
				{
					SB.AppendLine(string.Format("return ({0});","NULL"));
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