using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
using CParingTableCellDictionary=System.Collections.Generic.Dictionary<LL1Parser.CTerminal,System.Collections.Generic.List<LL1Parser.CChoice>>;
//-------------------------------------------------------------------------------------------------------
namespace LL1Parser
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CParsingTableRow
	{
//-------------------------------------------------------------------------------------------------------
		private readonly CNonterminal							MNonterminal;
		private readonly CParingTableCellDictionary				MRowDictionary;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CParsingTableRow(CNonterminal Nonterminal, CTerminal[] Terminals)
		{
			MNonterminal=Nonterminal;
			MRowDictionary=new CParingTableCellDictionary();

			foreach(CTerminal Terminal in Terminals)
				MRowDictionary.Add(Terminal,new List<CChoice>());
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
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CChoice[]										this[CTerminal Terminal]
		{
			get
			{
				List<CChoice>		Choices=MRowDictionary[Terminal];

				return(Choices.ToArray());
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void AddChoice(CTerminal Terminal, CChoice Choice)
		{
			MRowDictionary[Terminal].Add(Choice);
		}
//-------------------------------------------------------------------------------------------------------
		public CTerminal[] GetTerminalWithChoices()
		{
			List<CTerminal>			Ret=new List<CTerminal>();

			foreach(CTerminal Terminal in MRowDictionary.Keys)
			{
				if (MRowDictionary[Terminal].Count>0)
				{
					Ret.Add(Terminal);
				}
			}

			return(Ret.ToArray());
		}
//-------------------------------------------------------------------------------------------------------
		public CTerminal[] GetTerminalWithNoChoices()
		{
			List<CTerminal>			Ret=new List<CTerminal>();

			foreach(CTerminal Terminal in MRowDictionary.Keys)
			{
				if (MRowDictionary[Terminal].Count==0)
				{
					Ret.Add(Terminal);
				}
			}

			return(Ret.ToArray());
		}
//-------------------------------------------------------------------------------------------------------
		public void SetPOPErrorChoice(CFollowSet FollowSet)
		{
			CChoice_ErrorPOP		ChoicePOP=new CChoice_ErrorPOP();
			CTerminal[]				FollowSetTerminals=FollowSet.Terminals;

			foreach(CTerminal FollowSetTerminal in FollowSetTerminals)
			{
				List<CChoice>		Choices=MRowDictionary[FollowSetTerminal];

				if (Choices.Count==0)
				{
					Choices.Add(ChoicePOP);
				}
			}

			CTerminal_EOF			TerminalEOF=MRowDictionary.Keys.OfType<CTerminal_EOF>().First();
			List<CChoice>			TerminalEOFChoices=MRowDictionary[TerminalEOF];

			if (TerminalEOFChoices.Count==0)
			{
				TerminalEOFChoices.Add(ChoicePOP);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public void SetSCANErrorChoice(CFirstSet FirstSet, CFollowSet FollowSet)
		{
			CChoice_ErrorSCAN		ChoiceSCAN=new CChoice_ErrorSCAN();
			HashSet<CTerminal>		TerminalsInFirstOrFollowSet=new HashSet<CTerminal>();
			CTerminal[]				FirstSetTerminals=FirstSet.GetAllButEmptyTerminals();
			CTerminal[]				FollowSetTerminals=FollowSet.Terminals;

			foreach(CTerminal FirstSetTerminal in FirstSetTerminals)
				TerminalsInFirstOrFollowSet.Add(FirstSetTerminal);

			foreach(CTerminal FollowSetTerminal in FollowSetTerminals)
				TerminalsInFirstOrFollowSet.Add(FollowSetTerminal);

			foreach(CTerminal Terminal in MRowDictionary.Keys)
			{
				List<CChoice>		Choices=MRowDictionary[Terminal];

				if (Choices.Count==0 && TerminalsInFirstOrFollowSet.Contains(Terminal)==false)
				{
					Choices.Add(ChoiceSCAN);
				}
			}
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