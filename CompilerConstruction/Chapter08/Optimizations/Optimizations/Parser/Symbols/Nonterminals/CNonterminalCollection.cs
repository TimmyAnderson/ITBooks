using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace Optimizations
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CNonterminalCollection
	{
//-------------------------------------------------------------------------------------------------------
		private readonly List<CNonterminal>						MNonterminals;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CNonterminalCollection()
		{
			MNonterminals=new List<CNonterminal>();
		}
//-------------------------------------------------------------------------------------------------------
		public CNonterminalCollection(List<CNonterminal> Nonterminals)
		{
			MNonterminals=new List<CNonterminal>();

			MNonterminals.AddRange(Nonterminals);
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CNonterminal[]									Nonterminals
		{
			get
			{
				return(MNonterminals.ToArray());
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void AddNonterminal(CNonterminal Nonterminal)
		{
			MNonterminals.Add(Nonterminal);
		}
//-------------------------------------------------------------------------------------------------------
		public CNonterminal FindNonterminalByName(string Name)
		{
			CNonterminal										Nonterminal=MNonterminals.Where(P => P.Name==Name).FirstOrDefault();

			if (Nonterminal!=null)
			{
				return(Nonterminal);
			}
			else
			{
				throw(new CCompilerException(string.Format("Can't find NONTERMINAL [{0}] !",Name)));
			}
		}
//-------------------------------------------------------------------------------------------------------
		public CChoice FindChoice(CNonterminal Nonterminal, CSymbol[] Symbols)
		{
			foreach (CNonterminal ExistingNonterminal in MNonterminals)
			{
				if (ExistingNonterminal.Equals(Nonterminal)==true)
				{
					CChoice										Choice=ExistingNonterminal.GetChoiceWithSameSymbols(Symbols);

					if (Choice!=null)
					{
						return(Choice);
					}
				}
			}

			return(null);
		}
//-------------------------------------------------------------------------------------------------------
		public int GetIndex(CNonterminal Nonterminal)
		{
			for(int Index=0;Index<MNonterminals.Count;Index++)
			{
				if (MNonterminals[Index].Equals(Nonterminal)==true)
				{
					return(Index);
				}
			}

			throw(new CCompilerException(string.Format("Index of NON-TERMINAL [{0}] was NOT FOUND !",Nonterminal)));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------