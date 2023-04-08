using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace RuntimeEnvironment
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CDFAState
	{
//-------------------------------------------------------------------------------------------------------
		private readonly List<CNFAState>						MNFAStates;
		private readonly List<CDFATransition>					MTransitions;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CDFAState(CNFAState[] NFAStates)
		{
			MNFAStates=new List<CNFAState>(NFAStates);
			MTransitions=new List<CDFATransition>();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CNFAState[]										NFAStates
		{
			get
			{
				return(MNFAStates.ToArray());
			}
		}
//-------------------------------------------------------------------------------------------------------
		public CDFATransition[]									Transitions
		{
			get
			{
				return(MTransitions.ToArray());
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void AddTransition(CDFATransition NewTransition)
		{
			bool			TransitionExists=false;

			foreach(CDFATransition ExistingTransition in MTransitions)
			{
				if (ExistingTransition.Equals(NewTransition)==true)
				{
					TransitionExists=true;
					break;
				}
			}

			if (TransitionExists==false)
			{
				MTransitions.Add(NewTransition);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public bool ContainsSameLALRCore(CLALRCore LALRCore)
		{
			foreach(CLR0Item LALRCoreLR0Item in LALRCore.LR0Items)
			{
				bool				ContainsLR0Item=false;

				for(int i=0;i<MNFAStates.Count;i++)
				{
					if (MNFAStates[i].Item.LR0Item.Equals(LALRCoreLR0Item)==true)
					{
						ContainsLR0Item=true;
						break;
					}
				}

				if (ContainsLR0Item==false)
				{
					return(false);
				}
			}

			return(true);
		}
//-------------------------------------------------------------------------------------------------------
		public bool ContainsSameNFAStates(CNFAState[] NFAStates)
		{
			if (MNFAStates.Count!=NFAStates.Length)
			{
				return(false);
			}

			for(int i=0;i<MNFAStates.Count;i++)
			{
				if (MNFAStates[i].Item.Equals(NFAStates[i].Item)==false)
				{
					return(false);
				}
			}

			return(true);
		}
//-------------------------------------------------------------------------------------------------------
		public bool ContainsSameNFAStates(CDFAState DFAState)
		{
			if (MNFAStates.Count!=DFAState.NFAStates.Length)
			{
				return(false);
			}

			for(int i=0;i<MNFAStates.Count;i++)
			{
				if (MNFAStates[i].Item.Equals(DFAState.NFAStates[i].Item)==false)
				{
					return(false);
				}
			}

			return(true);
		}
//-------------------------------------------------------------------------------------------------------
		public CSymbol[] GetAllNonEpsilonTransitionSymbols()
		{
			List<CSymbol>			TransitionSymbols=new List<CSymbol>();

			foreach(CNFAState NFAState in MNFAStates)
			{
				foreach(CNFATransition NFATransition in NFAState.Transitions)
				{
					if (NFATransition.IsEpsilonTransition==false)
					{
						bool		AlreadyContainsSymbol=false;

						foreach(CSymbol TransitionSymbol in TransitionSymbols)
						{
							if (NFATransition.TransitionSymbol.Equals(TransitionSymbol)==true)
							{
								AlreadyContainsSymbol=true;
								break;
							}
						}

						if (AlreadyContainsSymbol==false)
						{
							TransitionSymbols.Add(NFATransition.TransitionSymbol);
						}
					}
				}
			}

			return(TransitionSymbols.ToArray());
		}
//-------------------------------------------------------------------------------------------------------
		public bool ContainsCompleteLR1Item()
		{
			foreach(CNFAState NFAState in MNFAStates)
			{
				if (NFAState.Item.IsCompleteItem==true)
				{
					return(true);
				}
			}

			return(false);
		}
//-------------------------------------------------------------------------------------------------------
		public bool ContainsNonCompleteLR1Item()
		{
			foreach(CNFAState NFAState in MNFAStates)
			{
				if (NFAState.Item.IsCompleteItem==false)
				{
					return(true);
				}
			}

			return(false);
		}
//-------------------------------------------------------------------------------------------------------
		public CNFAState[] GetAllCompleteLR1Items()
		{
			List<CNFAState>			States=new List<CNFAState>();

			foreach(CNFAState NFAState in MNFAStates)
			{
				if (NFAState.Item.IsCompleteItem==true)
				{
					States.Add(NFAState);
				}
			}

			return(States.ToArray());
		}
//-------------------------------------------------------------------------------------------------------
		public CLALRCore GetLALRCore()
		{
			List<CLR0Item>			LALRCoreItems=new List<CLR0Item>();
			CLR0Item[]				AllLR01Items=MNFAStates.Select(P => P.Item.LR0Item).ToArray();

			// Vyradim duplikatne LR0 ITEMS.
			foreach(CLR0Item NewLR0Item in AllLR01Items)
			{
				bool				AlreadyContains=false;

				foreach(CLR0Item ExistingLR0Item in LALRCoreItems)
				{
					if (ExistingLR0Item.Equals(NewLR0Item)==true)
					{
						AlreadyContains=true;
						break;
					}
				}

				if (AlreadyContains==false)
				{
					LALRCoreItems.Add(NewLR0Item);
				}
			}

			CLALRCore				LALRCore=new CLALRCore(LALRCoreItems.ToArray());

			return(LALRCore);
		}
//-------------------------------------------------------------------------------------------------------
		public override string ToString()
		{
			StringBuilder		SB=new StringBuilder();
			bool				First=true;

			foreach(CNFAState NFAState in MNFAStates)
			{
				if (First==true)
				{
					First=false;
				}
				else
				{
					SB.Append("   ");
				}

				SB.Append(NFAState);
			}

			return(SB.ToString());
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------