using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace RuntimeEnvironment
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CSyntaxTreeNode_PARAM : CSyntaxTreeNode
	{
//-------------------------------------------------------------------------------------------------------
		private readonly CSyntaxTreeNode_TYPE_SPECIFIER			MTypeSpecifier;
		private readonly string									MParamName;
		private readonly bool									MIsArray;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_PARAM(CChoice Choice, CParsingStackItem TypeSpecifier, CParsingStackItem ParamName)
			: base(Choice)
		{
			if (Choice.Symbols.Length==2 && Choice.Symbols[0].Name=="TYPE_SPECIFIER" && Choice.Symbols[1].Name=="TerminalID")
			{
				MTypeSpecifier=(CSyntaxTreeNode_TYPE_SPECIFIER) TypeSpecifier.SyntaxTreeNode;
				MParamName=ParamName.ParseTreeNode.Token.Lexema;
				MIsArray=false;
				MChoiceNumber=1;
			}
			else if (Choice.Symbols.Length==4 && Choice.Symbols[0].Name=="TYPE_SPECIFIER" && Choice.Symbols[1].Name=="TerminalID" && Choice.Symbols[2].Name=="TerminalSquareBracketLeft" && Choice.Symbols[3].Name=="TerminalSquareBracketRight")
			{
				MTypeSpecifier=(CSyntaxTreeNode_TYPE_SPECIFIER) TypeSpecifier.SyntaxTreeNode;
				MParamName=ParamName.ParseTreeNode.Token.Lexema;
				MIsArray=true;
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
		public CSyntaxTreeNode_TYPE_SPECIFIER					TypeSpecifier
		{
			get
			{
				return(MTypeSpecifier);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public string											ParamName
		{
			get
			{
				return(MParamName);
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
					SB.Append(string.Format("{0} {1}",MTypeSpecifier.PrintTree(),MParamName));
				}
				else
				{
					SB.Append(string.Format("{0} {1}","NULL",MParamName));
				}

				return(SB.ToString());
			}
			else if (MChoiceNumber==2)
			{
				StringBuilder			SB=new StringBuilder();

				if (MTypeSpecifier!=null)
				{
					SB.Append(string.Format("{0} {1}[]",MTypeSpecifier.PrintTree(),MParamName));
				}
				else
				{
					SB.Append(string.Format("{0} {1}[]","NULL",MParamName));
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