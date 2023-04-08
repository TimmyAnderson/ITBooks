using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace RuntimeEnvironment
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CLR0Item : IEquatable<CLR0Item>
	{
//-------------------------------------------------------------------------------------------------------
		private readonly CNonterminal							MNonterminal;
		private readonly CSymbol[]								MSymbols;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CLR0Item(CNonterminal Nonterminal, CSymbol[] Symbols)
		{
			MNonterminal=Nonterminal;
			MSymbols=Symbols;
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
				return(MSymbols);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public bool												IsCompleteItem
		{
			get
			{
				if ((MSymbols[MSymbols.Length-1] is CPeriodLRItemSymbol)==true)
				{
					return(true);
				}
				else
				{
					return(false);
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		public bool												BeginsWithPeriod
		{
			get
			{
				if ((MSymbols[0] is CPeriodLRItemSymbol)==true)
				{
					return(true);
				}
				else
				{
					return(false);
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSymbol GetSymbolAfterPeriod()
		{
			if (IsCompleteItem==false)
			{
				for(int i=0;i<MSymbols.Length;i++)
				{
					if ((MSymbols[i] is CPeriodLRItemSymbol)==true)
					{
						return(MSymbols[i+1]);
					}
				}
			}
			
			return(null);
		}
//-------------------------------------------------------------------------------------------------------
		public CSymbol[] GetSymbolsAfterPeriod()
		{
			List<CSymbol>				Symbols=new List<CSymbol>();

			if (IsCompleteItem==false)
			{
				bool					PeriodWasFound=false;

				for(int i=0;i<MSymbols.Length;i++)
				{
					if (PeriodWasFound==true)
					{
						Symbols.Add(MSymbols[i]);
					}
					else if ((MSymbols[i] is CPeriodLRItemSymbol)==true)
					{
						PeriodWasFound=true;
					}
				}
			}
			
			return(Symbols.ToArray());
		}
//-------------------------------------------------------------------------------------------------------
		public CSymbol[] GetSymbolsExceptPeriod()
		{
			List<CSymbol>			Symbols=new List<CSymbol>();

			foreach(CSymbol Symbol in MSymbols)
			{
				if ((Symbol is CPeriodLRItemSymbol)==false)
				{
					Symbols.Add(Symbol);
				}
			}

			return(Symbols.ToArray());
		}
//-------------------------------------------------------------------------------------------------------
		public CSymbol[] GetSymbolsWithIncrementedPeriodPosition()
		{
			if (IsCompleteItem==false)
			{
				List<CSymbol>				Symbols=new List<CSymbol>();

				for(int i=0;i<MSymbols.Length;i++)
				{
					if ((MSymbols[i] is CPeriodLRItemSymbol)==true)
					{
						Symbols.Add(MSymbols[i+1]);
						Symbols.Add(MSymbols[i]);

						i++;
					}
					else
					{
						Symbols.Add(MSymbols[i]);
					}
				}

				return(Symbols.ToArray());
			}
			else
			{
				return(MSymbols);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public bool Equals(CLR0Item Other)
		{
			if (Other==null)
			{
				return(false);
			}

			if (MNonterminal.Equals(Other.Nonterminal)==false)
			{
				return(false);
			}

			if (MSymbols.Length!=Other.MSymbols.Length)
			{
				return(false);
			}

			for(int i=0;i<MSymbols.Length;i++)
			{
				if (MSymbols[i].Equals(Other.MSymbols[i])==false)
				{
					return(false);
				}
			}
			
			return(true);
		}
//-------------------------------------------------------------------------------------------------------
		public override string ToString()
		{
			StringBuilder		SB=new StringBuilder();
			bool				IsFirst=true;

			SB.AppendFormat("{0} -> ",MNonterminal);

			foreach(CSymbol Symbol in MSymbols)
			{
				if (IsFirst==false)
					SB.Append(" ");
				else
					IsFirst=false;

				SB.Append(Symbol);
			}

			return(SB.ToString());
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------