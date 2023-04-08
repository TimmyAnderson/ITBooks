using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace Optimizations
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CChoice : IEquatable<CChoice>
	{
//-------------------------------------------------------------------------------------------------------
		private readonly CNonterminal							MNonterminal;
		private readonly List<CSymbol>							MSymbols;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CChoice(CNonterminal Nonterminal)
		{
			MNonterminal=Nonterminal;
			MSymbols=new List<CSymbol>();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CNonterminal										Nonterminal
		{
			get
			{
				return(MNonterminal);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public CSymbol[]										Symbols
		{
			get
			{
				return(MSymbols.ToArray());
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Choice contains JUST EMPTY TERMINAL.
		public bool												IsEmptyChoice
		{
			get
			{
				if (Symbols.Length>1 || (Symbols[0] is CTerminal_EMPTY)==false)
				{
					return(false);
				}
				else
				{
					return(true);
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void AddChoice(CSymbol Symbol)
		{
			MSymbols.Add(Symbol);
		}
//-------------------------------------------------------------------------------------------------------
		public bool ContainsSymbols(CSymbol[] Symbols)
		{
			if (MSymbols.Count!=Symbols.Length)
			{
				return(false);
			}

			for(int Index=0;Index<MSymbols.Count;Index++)
			{
				if (MSymbols[Index].Equals(Symbols[Index])==false)
				{
					return(false);
				}
			}

			return(true);
		}
//-------------------------------------------------------------------------------------------------------
		public bool Equals(CChoice Other)
		{
			if (Other==null)
			{
				return(false);
			}

 			if (MNonterminal.Equals(Other.MNonterminal)==false)
			{
				return(false);
			}

			if (MSymbols.Count!=Other.MSymbols.Count)
			{
				return(false);
			}

			for(int Index=0;Index<MSymbols.Count;Index++)
			{
				if (MSymbols[Index].Equals(Other.MSymbols[Index])==false)
				{
					return(false);
				}
			}

			return(true);
		}
//-------------------------------------------------------------------------------------------------------
		public override string ToString()
		{
			StringBuilder										SB=new StringBuilder();
			bool												IsFirst=true;

			SB.AppendFormat("{0} ---> ",MNonterminal);

			foreach(CSymbol Symbol in MSymbols)
			{
				if (IsFirst==false)
				{
					SB.Append(" ");
				}
				else
				{
					IsFirst=false;
				}

				SB.Append(Symbol);
			}

			return(SB.ToString());
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------