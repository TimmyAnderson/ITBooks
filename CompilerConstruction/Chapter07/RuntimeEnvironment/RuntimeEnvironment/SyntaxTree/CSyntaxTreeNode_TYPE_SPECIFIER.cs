using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace RuntimeEnvironment
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CSyntaxTreeNode_TYPE_SPECIFIER : CSyntaxTreeNode
	{
//-------------------------------------------------------------------------------------------------------
		private readonly ETYPE_SPECIFIER						MTypeSpecifier;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_TYPE_SPECIFIER(CChoice Choice, CParsingStackItem ParsingStackItem)
			: base(Choice)
		{
			if (Choice.Symbols.Length==1 && Choice.Symbols[0].Name=="TerminalINT")
			{
				MTypeSpecifier=ETYPE_SPECIFIER.E_TS_INT;
				MChoiceNumber=1;
			}
			else if (Choice.Symbols.Length==1 && Choice.Symbols[0].Name=="TerminalSTRING")
			{
				MTypeSpecifier=ETYPE_SPECIFIER.E_TS_STRING;
				MChoiceNumber=2;
			}
			else if (Choice.Symbols.Length==1 && Choice.Symbols[0].Name=="TerminalVOID")
			{
				MTypeSpecifier=ETYPE_SPECIFIER.E_TS_VOID;
				MChoiceNumber=3;
			}
			else
			{
				throw(new InvalidOperationException(string.Format("Invalid CHOICE [{0}] !",Choice)));
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public ETYPE_SPECIFIER									TypeSpecifier
		{
			get
			{
				return(MTypeSpecifier);
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

				SB.Append("int");

				return(SB.ToString());
			}
			else if (MChoiceNumber==2)
			{
				StringBuilder			SB=new StringBuilder();

				SB.Append("string");

				return(SB.ToString());
			}
			else if (MChoiceNumber==3)
			{
				StringBuilder			SB=new StringBuilder();

				SB.Append("void");

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