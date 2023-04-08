using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace RuntimeEnvironment
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CParsingTableRow
	{
//-------------------------------------------------------------------------------------------------------
		private readonly CDFAState								MDFAState;
		private readonly List<CParsingTableCell>				MCells;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CParsingTableRow(CDFAState DFAState)
		{
			MDFAState=DFAState;
			MCells=new List<CParsingTableCell>();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CDFAState										DFAState
		{
			get
			{
				return(MDFAState);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public CParsingTableCell[]								Cells
		{
			get
			{
				return(MCells.ToArray());
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void AddCell(CParsingTableCell Cell)
		{
			MCells.Add(Cell);
		}
//-------------------------------------------------------------------------------------------------------
		public CParsingTableCell GetCell(CSymbol CellSymbol)
		{
			foreach(CParsingTableCell ParsingTableCell in MCells)
			{
				if (ParsingTableCell.Symbol.Equals(CellSymbol)==true)
				{
					return(ParsingTableCell);
				}
			}

			return(null);
		}
//-------------------------------------------------------------------------------------------------------
		public bool HasGotoCells()
		{
			foreach(CParsingTableCell ParsingTableCell in MCells)
			{
				if ((ParsingTableCell.Operation is CParsingTableOperation_Goto)==true)
				{
					return(true);
				}
			}

			return(false);
		}
//-------------------------------------------------------------------------------------------------------
		public CParsingTableCell[] GetAllGotoCells()
		{
			List<CParsingTableCell>					GotoCells=new List<CParsingTableCell>();

			foreach(CParsingTableCell ParsingTableCell in MCells)
			{
				if ((ParsingTableCell.Operation is CParsingTableOperation_Goto)==true)
				{
					GotoCells.Add(ParsingTableCell);
				}
			}

			return(GotoCells.ToArray());
		}
//-------------------------------------------------------------------------------------------------------
		public override int GetHashCode()
		{
			return(MDFAState.GetHashCode());
		}
//-------------------------------------------------------------------------------------------------------
		public override string ToString()
		{
			return(MDFAState.ToString());
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------