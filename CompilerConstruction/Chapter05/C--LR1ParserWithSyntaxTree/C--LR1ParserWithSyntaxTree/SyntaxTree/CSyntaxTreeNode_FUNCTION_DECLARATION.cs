using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace C__LR1ParserWithSyntaxTree
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CSyntaxTreeNode_FUNCTION_DECLARATION : CSyntaxTreeNode
	{
//-------------------------------------------------------------------------------------------------------
		private readonly CSyntaxTreeNode_TYPE_SPECIFIER			MTypeSpecifier;
		private readonly string									MFunctionName;
		private readonly CSyntaxTreeNode_PARAMS					MParams;
		private readonly CSyntaxTreeNode_COMPOUND_STATEMENT		MCompoundStatement;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_FUNCTION_DECLARATION(CChoice Choice, CParsingStackItem TypeSpecifier, CParsingStackItem FunctionName, CParsingStackItem Params, CParsingStackItem CompoundStatement)
			: base(Choice)
		{
			MTypeSpecifier=(CSyntaxTreeNode_TYPE_SPECIFIER) TypeSpecifier.SyntaxTreeNode;
			MFunctionName=FunctionName.ParseTreeNode.Token.Lexema;
			MParams=(CSyntaxTreeNode_PARAMS) Params.SyntaxTreeNode;
			MCompoundStatement=(CSyntaxTreeNode_COMPOUND_STATEMENT) CompoundStatement.SyntaxTreeNode;
			MChoiceNumber=1;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_TYPE_SPECIFIER					TypeSpecifier
		{
			get
			{
				return(MTypeSpecifier);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public string											FunctionName
		{
			get
			{
				return(MFunctionName);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_PARAMS							Params
		{
			get
			{
				return(MParams);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_COMPOUND_STATEMENT				CompoundStatement
		{
			get
			{
				return(MCompoundStatement);
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

				if (MTypeSpecifier!=null && MParams!=null)
				{
					SB.AppendLine(string.Format("{0} {1}({2})",MTypeSpecifier.PrintTree(),MFunctionName,MParams.PrintTree()));
				}
				else if (MTypeSpecifier!=null && MParams==null)
				{
					SB.AppendLine(string.Format("{0} {1}({2})",MTypeSpecifier.PrintTree(),MFunctionName,"NULL"));
				}
				else if (MTypeSpecifier==null && MParams!=null)
				{
					SB.AppendLine(string.Format("{0} {1}({2})","NULL",MFunctionName,MParams.PrintTree()));
				}
				else
				{
					SB.AppendLine(string.Format("{0} {1}({2})","NULL",MFunctionName,"NULL"));
				}

				if (MCompoundStatement!=null)
				{
					SB.AppendLine(MCompoundStatement.PrintTree());
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