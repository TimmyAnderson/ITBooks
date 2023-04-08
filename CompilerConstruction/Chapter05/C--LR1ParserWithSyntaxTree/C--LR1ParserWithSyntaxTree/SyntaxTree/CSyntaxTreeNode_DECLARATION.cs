using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace C__LR1ParserWithSyntaxTree
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CSyntaxTreeNode_DECLARATION : CSyntaxTreeNode
	{
//-------------------------------------------------------------------------------------------------------
		private readonly CSyntaxTreeNode_VARIABLE_DECLARATION	MVariable;
		private readonly CSyntaxTreeNode_FUNCTION_DECLARATION	MFunction;
		private readonly EDECLARATION							MDeclaration;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_DECLARATION(CChoice Choice, CParsingStackItem ParsingStackItem)
			: base(Choice)
		{
			if (Choice.Symbols.Length==1 && Choice.Symbols[0].Name=="VARIABLE_DECLARATION")
			{
				MVariable=(CSyntaxTreeNode_VARIABLE_DECLARATION) ParsingStackItem.SyntaxTreeNode;
				MDeclaration=EDECLARATION.E_D_VARIABLE;
				MChoiceNumber=1;
			}
			else if (Choice.Symbols.Length==1 && Choice.Symbols[0].Name=="FUNCTION_DECLARATION")
			{
				MFunction=(CSyntaxTreeNode_FUNCTION_DECLARATION) ParsingStackItem.SyntaxTreeNode;
				MDeclaration=EDECLARATION.E_D_FUNCTION;
				MChoiceNumber=2;
			}
			else
			{
				throw(new InvalidOperationException(string.Format("Invalid CHOICE [{0}] !",Choice)));
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_VARIABLE_DECLARATION				Variable
		{
			get
			{
				return(MVariable);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_FUNCTION_DECLARATION				Function
		{
			get
			{
				return(MFunction);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public EDECLARATION										Declaration
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
			else if (MChoiceNumber==2)
			{
				StringBuilder			SB=new StringBuilder();

				if (MFunction!=null)
				{
					SB.Append(MFunction.PrintTree());
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