using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace C__LR1ParserWithSyntaxTree
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CSyntaxTreeNode_VARIABLE_DECLARATION : CSyntaxTreeNode
	{
//-------------------------------------------------------------------------------------------------------
		private readonly CSyntaxTreeNode_TYPE_SPECIFIER			MTypeSpecifier;
		private readonly string									MVariableName;
		private readonly int									MArraySize;
		private readonly bool									MIsArray;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_VARIABLE_DECLARATION(CChoice Choice, CParsingStackItem TypeSpecifier, CParsingStackItem VariableName)
			: base(Choice)
		{
			MTypeSpecifier=(CSyntaxTreeNode_TYPE_SPECIFIER) TypeSpecifier.SyntaxTreeNode;
			MVariableName=VariableName.ParseTreeNode.Token.Lexema;
			MIsArray=false;
			MChoiceNumber=1;
		}
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_VARIABLE_DECLARATION(CChoice Choice, CParsingStackItem TypeSpecifier, CParsingStackItem VariableName, CParsingStackItem ArraySize)
			: base(Choice)
		{
			MTypeSpecifier=(CSyntaxTreeNode_TYPE_SPECIFIER) TypeSpecifier.SyntaxTreeNode;
			MVariableName=VariableName.ParseTreeNode.Token.Lexema;
			MArraySize=int.Parse(ArraySize.ParseTreeNode.Token.Lexema);
			MIsArray=true;
			MChoiceNumber=2;
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
		public string											VariableName
		{
			get
			{
				return(MVariableName);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public int												ArraySize
		{
			get
			{
				return(MArraySize);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public bool												IsArray
		{
			get
			{
				return(MIsArray);
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

				if (MTypeSpecifier!=null)
				{
					SB.AppendLine(string.Format("{0} {1};",MTypeSpecifier.PrintTree(),MVariableName));
				}
				else
				{
					SB.AppendLine(string.Format("{0} {1};","NULL",MVariableName));
				}

				return(SB.ToString());
			}
			else if (MChoiceNumber==2)
			{
				StringBuilder			SB=new StringBuilder();

				if (MTypeSpecifier!=null)
				{
					SB.AppendLine(string.Format("{0} {1}[{2}];",MTypeSpecifier.PrintTree(),MVariableName,MArraySize));
				}
				else
				{
					SB.AppendLine(string.Format("{0} {1}[{2}];","NULL",MVariableName,MArraySize));
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