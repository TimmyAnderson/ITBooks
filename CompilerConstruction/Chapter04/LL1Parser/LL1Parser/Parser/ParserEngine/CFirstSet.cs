using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace LL1Parser
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CFirstSet
	{
//-------------------------------------------------------------------------------------------------------
		private readonly CNonterminal							MNonterminal;
		private readonly List<CTerminal>						MTerminals;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CFirstSet(CNonterminal Nonterminal)
		{
			MNonterminal=Nonterminal;
			MTerminals=new List<CTerminal>();
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
		public CTerminal[]										Terminals
		{
			get
			{
				return(MTerminals.ToArray());
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public bool AddTerminal(CTerminal Terminal)
		{
			CTerminal				ExistingTerminal=MTerminals.Where(P => P.Name==Terminal.Name).FirstOrDefault();

			if (ExistingTerminal==null)
			{
				MTerminals.Add(Terminal);
				return(true);
			}
			else
			{
				return(false);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public bool AddTerminals(CTerminal[] Terminals)
		{
			bool					AddedNewTerminals=false;

			foreach(CTerminal Terminal in Terminals)
			{
				if (AddTerminal(Terminal)==true)
				{
					AddedNewTerminals=true;
				}
			}

			return(AddedNewTerminals);
		}
//-------------------------------------------------------------------------------------------------------
		public CTerminal[] GetAllButEmptyTerminals()
		{
			CTerminal[]				Terminals=MTerminals.Where(P => P.GetType()!=typeof(CTerminal_EMPTY)).ToArray();

			return(Terminals);
		}
//-------------------------------------------------------------------------------------------------------
		public CTerminal[] GetAllTerminals()
		{
			return(MTerminals.ToArray());
		}
//-------------------------------------------------------------------------------------------------------
		public bool ContainEmptyTerminal()
		{
			int						NumberOfEmptyTerminals=MTerminals.Where(P => P.GetType()==typeof(CTerminal_EMPTY)).Count();

			if (NumberOfEmptyTerminals>0)
				return(true);
			else
				return(false);
		}
//-------------------------------------------------------------------------------------------------------
		public override string ToString()
		{
			return(MNonterminal.Name);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------