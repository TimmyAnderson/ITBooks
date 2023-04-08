using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace C__LR1ParserWithSyntaxTree
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CSyntaxTreeNode_COMPOUND_STATEMENT : CSyntaxTreeNode
	{
//-------------------------------------------------------------------------------------------------------
		private readonly CSyntaxTreeNode_LOCAL_DECLARATIONS		MLocalDeclarations;
		private readonly CSyntaxTreeNode_STATEMENT_LIST			MStatementList;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_COMPOUND_STATEMENT(CChoice Choice, CParsingStackItem LocalDeclarations, CParsingStackItem StatementList)
			: base(Choice)
		{
			MLocalDeclarations=(CSyntaxTreeNode_LOCAL_DECLARATIONS) LocalDeclarations.SyntaxTreeNode;
			MStatementList=(CSyntaxTreeNode_STATEMENT_LIST) StatementList.SyntaxTreeNode;
			MChoiceNumber=1;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_LOCAL_DECLARATIONS				LocalDeclarations
		{
			get
			{
				return(MLocalDeclarations);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_STATEMENT_LIST					StatementList
		{
			get
			{
				return(MStatementList);
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

				SB.AppendLine("{");

				if (MLocalDeclarations!=null)
				{
					SB.Append(MLocalDeclarations.PrintTree());
				}
				else
				{
					SB.Append("NULL");
				}

				if (MStatementList!=null)
				{
					SB.Append(MStatementList.PrintTree());
				}
				else
				{
					SB.Append("NULL");
				}

				SB.AppendLine("}");

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