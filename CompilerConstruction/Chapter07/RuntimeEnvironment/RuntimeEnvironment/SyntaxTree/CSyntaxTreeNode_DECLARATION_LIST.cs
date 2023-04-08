using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace RuntimeEnvironment
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CSyntaxTreeNode_DECLARATION_LIST : CSyntaxTreeNode
	{
//-------------------------------------------------------------------------------------------------------
		private readonly CSyntaxTreeNode_DECLARATION_LIST		MDeclarationList;
		private readonly CSyntaxTreeNode_DECLARATION			MDeclaration;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_DECLARATION_LIST(CChoice Choice, CParsingStackItem DeclarationList, CParsingStackItem Declaration)
			: base(Choice)
		{
			MDeclarationList=(CSyntaxTreeNode_DECLARATION_LIST) DeclarationList.SyntaxTreeNode;
			MDeclaration=(CSyntaxTreeNode_DECLARATION) Declaration.SyntaxTreeNode;
			MChoiceNumber=1;
		}
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_DECLARATION_LIST(CChoice Choice, CParsingStackItem Declaration)
			: base(Choice)
		{
			MDeclaration=(CSyntaxTreeNode_DECLARATION) Declaration.SyntaxTreeNode;
			MChoiceNumber=2;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_DECLARATION_LIST					DeclarationList
		{
			get
			{
				return(MDeclarationList);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_DECLARATION						Declaration
		{
			get
			{
				return(MDeclaration);
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

				if (MDeclarationList!=null)
				{
					SB.Append(MDeclarationList.PrintTree());
				}
				else
				{
					SB.Append("NULL");
				}

				if (MDeclaration!=null)
				{
					SB.Append(MDeclaration.PrintTree());
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

				if (MDeclaration!=null)
				{
					SB.Append(MDeclaration.PrintTree());
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