using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace SemanticAnalyzer
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CSyntaxTreeNode_LOCAL_DECLARATIONS : CSyntaxTreeNode
	{
//-------------------------------------------------------------------------------------------------------
		private readonly CSyntaxTreeNode_LOCAL_DECLARATIONS		MLocalDeclarations;
		private readonly CSyntaxTreeNode_VARIABLE_DECLARATION	MVariableDeclaration;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_LOCAL_DECLARATIONS(CChoice Choice, CParsingStackItem LocalDeclarations, CParsingStackItem VariableDeclaration)
			: base(Choice)
		{
			MLocalDeclarations=(CSyntaxTreeNode_LOCAL_DECLARATIONS) LocalDeclarations.SyntaxTreeNode;
			MVariableDeclaration=(CSyntaxTreeNode_VARIABLE_DECLARATION) VariableDeclaration.SyntaxTreeNode;
			MChoiceNumber=1;
		}
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_LOCAL_DECLARATIONS(CChoice Choice)
			: base(Choice)
		{
			MChoiceNumber=2;
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
		public CSyntaxTreeNode_VARIABLE_DECLARATION				VariableDeclaration
		{
			get
			{
				return(MVariableDeclaration);
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

				if (MLocalDeclarations!=null)
				{
					SB.Append(MLocalDeclarations.PrintTree());
				}
				else
				{
					SB.Append("NULL");
				}

				if (MVariableDeclaration!=null)
				{
					SB.Append(MVariableDeclaration.PrintTree());
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
				throw(new InvalidOperationException(string.Format("Invalid CHOICE [{0}] !",Choice)));
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------