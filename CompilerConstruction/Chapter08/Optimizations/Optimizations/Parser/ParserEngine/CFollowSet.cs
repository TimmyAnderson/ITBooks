using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace Optimizations
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CFollowSet
	{
//-------------------------------------------------------------------------------------------------------
		private readonly CNonterminal							MNonterminal;
		private readonly List<CTerminal>						MTerminals;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CFollowSet(CNonterminal Nonterminal)
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
			CTerminal											ExistingTerminal=MTerminals.Where(P => P.Name==Terminal.Name).FirstOrDefault();

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
			bool												AddedNewTerminals=false;

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
		public CTerminal[] GetAllTerminals()
		{
			return(MTerminals.ToArray());
		}
//-------------------------------------------------------------------------------------------------------
		public bool ContainsTerminal(CTerminal TerminalToFind)
		{
			foreach(CTerminal Terminal in MTerminals)
			{
				if (Terminal.Equals(TerminalToFind)==true)
				{
					return(true);
				}
			}

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