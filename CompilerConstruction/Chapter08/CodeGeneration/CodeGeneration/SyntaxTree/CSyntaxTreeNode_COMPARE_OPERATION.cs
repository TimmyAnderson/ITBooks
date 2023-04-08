using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace CodeGeneration
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CSyntaxTreeNode_COMPARE_OPERATION : CSyntaxTreeNode
	{
//-------------------------------------------------------------------------------------------------------
		private readonly ECOMPARE_OPERATION						MCompareOperation;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_COMPARE_OPERATION(CChoice Choice, CParsingStackItem ParsingStackItem)
			: base(Choice)
		{
			if (Choice.Symbols.Length==1 && Choice.Symbols[0].Name=="TerminalLesserOrEqual")
			{
				MCompareOperation=ECOMPARE_OPERATION.E_CO_LESSER_OR_EQUAL;
				MChoiceNumber=1;
			}
			else if (Choice.Symbols.Length==1 && Choice.Symbols[0].Name=="TerminalLesser")
			{
				MCompareOperation=ECOMPARE_OPERATION.E_CO_LESSER;
				MChoiceNumber=2;
			}
			else if (Choice.Symbols.Length==1 && Choice.Symbols[0].Name=="TerminalGreater")
			{
				MCompareOperation=ECOMPARE_OPERATION.E_CO_GREATER;
				MChoiceNumber=3;
			}
			else if (Choice.Symbols.Length==1 && Choice.Symbols[0].Name=="TerminalGreaterOrEqual")
			{
				MCompareOperation=ECOMPARE_OPERATION.E_CO_GREATER_OR_EQUAL;
				MChoiceNumber=4;
			}
			else if (Choice.Symbols.Length==1 && Choice.Symbols[0].Name=="TerminalEqual")
			{
				MCompareOperation=ECOMPARE_OPERATION.E_CO_EQUAL;
				MChoiceNumber=5;
			}
			else if (Choice.Symbols.Length==1 && Choice.Symbols[0].Name=="TerminalNotEqual")
			{
				MCompareOperation=ECOMPARE_OPERATION.E_CO_NOT_EQUAL;
				MChoiceNumber=6;
			}
			else
			{
				throw(new InvalidOperationException(string.Format("Invalid CHOICE [{0}] !",Choice)));
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public ECOMPARE_OPERATION								CompareOperation
		{
			get
			{
				return(MCompareOperation);
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

				SB.Append("<=");

				return(SB.ToString());
			}
			else if (MChoiceNumber==2)
			{
				StringBuilder			SB=new StringBuilder();

				SB.Append("<");

				return(SB.ToString());
			}
			else if (MChoiceNumber==3)
			{
				StringBuilder			SB=new StringBuilder();

				SB.Append(">");

				return(SB.ToString());
			}
			else if (MChoiceNumber==4)
			{
				StringBuilder			SB=new StringBuilder();

				SB.Append(">=");

				return(SB.ToString());
			}
			else if (MChoiceNumber==5)
			{
				StringBuilder			SB=new StringBuilder();

				SB.Append("==");

				return(SB.ToString());
			}
			else if (MChoiceNumber==6)
			{
				StringBuilder			SB=new StringBuilder();

				SB.Append("!=");

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