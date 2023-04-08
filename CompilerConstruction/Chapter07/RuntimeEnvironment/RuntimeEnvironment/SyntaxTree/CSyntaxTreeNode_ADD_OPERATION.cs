using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace RuntimeEnvironment
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CSyntaxTreeNode_ADD_OPERATION : CSyntaxTreeNode
	{
//-------------------------------------------------------------------------------------------------------
		private readonly EADD_OPERATION							MAdditionSubtractionOperation;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSyntaxTreeNode_ADD_OPERATION(CChoice Choice, CParsingStackItem ParsingStackItem)
			: base(Choice)
		{
			if (Choice.Symbols.Length==1 && Choice.Symbols[0].Name=="TerminalPlus")
			{
				MAdditionSubtractionOperation=EADD_OPERATION.E_AO_ADDITION;
				MChoiceNumber=1;
			}
			else if (Choice.Symbols.Length==1 && Choice.Symbols[0].Name=="TerminalMinus")
			{
				MAdditionSubtractionOperation=EADD_OPERATION.E_AO_SUBTRACTION;
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
		public EADD_OPERATION									MultipleDivisionOperation
		{
			get
			{
				return(MAdditionSubtractionOperation);
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

				SB.Append("+");

				return(SB.ToString());
			}
			else if (MChoiceNumber==2)
			{
				StringBuilder			SB=new StringBuilder();

				SB.Append("-");

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