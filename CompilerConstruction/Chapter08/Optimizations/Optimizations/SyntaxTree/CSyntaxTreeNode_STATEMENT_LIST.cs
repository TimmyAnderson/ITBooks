using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace Optimizations
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CSyntaxTreeNode_STATEMENT_LIST : CSyntaxTreeNode
	{
//-------------------------------------------------------------------------------------------------------
		private readonly CSyntaxTreeNode_STATEMENT_LIST			MStatementList;
		private readonly CSyntaxTreeNode_STATEMENT				MStatement;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_STATEMENT_LIST(CChoice Choice, CParsingStackItem StatementList, CParsingStackItem Statement)
			: base(Choice)
		{
			MStatementList=(CSyntaxTreeNode_STATEMENT_LIST) StatementList.SyntaxTreeNode;
			MStatement=(CSyntaxTreeNode_STATEMENT) Statement.SyntaxTreeNode;
			MChoiceNumber=1;
		}
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_STATEMENT_LIST(CChoice Choice)
			: base(Choice)
		{
			MChoiceNumber=2;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_STATEMENT_LIST					StatementList
		{
			get
			{
				return(MStatementList);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_STATEMENT						Statement
		{
			get
			{
				return(MStatement);
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

				if (MStatementList!=null)
				{
					SB.Append(MStatementList.PrintTree());
				}
				else
				{
					SB.Append("NULL");
				}

				if (MStatement!=null)
				{
					SB.Append(MStatement.PrintTree());
				}
				else
				{
					SB.Append("NULL");
				}

				return(SB.ToString());
			}
			else if (MChoiceNumber==2)
			{
				return("");
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