using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace RuntimeEnvironment
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CSyntaxTreeNode_EXPRESSION_STATEMENT : CSyntaxTreeNode
	{
//-------------------------------------------------------------------------------------------------------
		private readonly CSyntaxTreeNode_VARIABLE				MVariable;
		private readonly CSyntaxTreeNode_EXPRESSION				MExpression;
		private readonly CSyntaxTreeNode_CALL					MCall;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_EXPRESSION_STATEMENT(CChoice Choice, CParsingStackItem Variable, CParsingStackItem Expression)
			: base(Choice)
		{
			MVariable=(CSyntaxTreeNode_VARIABLE) Variable.SyntaxTreeNode;
			MExpression=(CSyntaxTreeNode_EXPRESSION) Expression.SyntaxTreeNode;
			MChoiceNumber=1;
		}
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_EXPRESSION_STATEMENT(CChoice Choice, CParsingStackItem Call)
			: base(Choice)
		{
			MCall=(CSyntaxTreeNode_CALL) Call.SyntaxTreeNode;
			MChoiceNumber=2;
		}
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_EXPRESSION_STATEMENT(CChoice Choice)
			: base(Choice)
		{
			MChoiceNumber=3;
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
		public CSyntaxTreeNode_CALL								Call
		{
			get
			{
				return(MCall);
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
					SB.AppendLine(string.Format("{0}={1};",MVariable.PrintTree(),MExpression.PrintTree()));
				}
				else if (MVariable!=null && MExpression==null)
				{
					SB.AppendLine(string.Format("{0}={1};",MVariable.PrintTree(),"NULL"));
				}
				else if (MVariable==null && MExpression!=null)
				{
					SB.AppendLine(string.Format("{0}={1};","NULL",MExpression.PrintTree()));
				}
				else
				{
					SB.AppendLine(string.Format("{0}={1};","NULL","NULL"));
				}

				return(SB.ToString());
			}
			else if (MChoiceNumber==2)
			{
				StringBuilder			SB=new StringBuilder();

				if (MCall!=null)
				{
					SB.AppendLine(string.Format("{0};",MCall.PrintTree()));
				}
				else
				{
					SB.AppendLine(string.Format("{0};","NULL"));
				}

				return(SB.ToString());
			}
			else if (MChoiceNumber==3)
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