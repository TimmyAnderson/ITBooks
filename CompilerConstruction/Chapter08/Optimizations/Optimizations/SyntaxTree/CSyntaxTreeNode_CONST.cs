using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace Optimizations
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CSyntaxTreeNode_CONST : CSyntaxTreeNode
	{
//-------------------------------------------------------------------------------------------------------
		private readonly int									MNumber;
		private readonly string									MStringLiteral;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_CONST(CChoice Choice, CParsingStackItem ParsingStackItem)
			: base(Choice)
		{
			if (Choice.Symbols.Length==1 && Choice.Symbols[0].Name=="TerminalNumber")
			{
				int.TryParse(ParsingStackItem.ParseTreeNode.Token.Lexema,out MNumber);
				MChoiceNumber=1;
			}
			else if (Choice.Symbols.Length==1 && Choice.Symbols[0].Name=="TerminalString")
			{
				MStringLiteral=ParsingStackItem.ParseTreeNode.Token.Lexema;
				MChoiceNumber=2;
			}
			else
			{
				throw(new CCompilerException(string.Format("Invalid CHOICE [{0}] !",Choice)));
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public int												Number
		{
			get
			{
				return(MNumber);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public string											StringLiteral
		{
			get
			{
				return(MStringLiteral);
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

				SB.Append(string.Format("{0}",MNumber));

				return(SB.ToString());
			}
			else if (MChoiceNumber==2)
			{
				StringBuilder									SB=new StringBuilder();

				SB.Append(string.Format("{0}",MStringLiteral));

				return(SB.ToString());
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