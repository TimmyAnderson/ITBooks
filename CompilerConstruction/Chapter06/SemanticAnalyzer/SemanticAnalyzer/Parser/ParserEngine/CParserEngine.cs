using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace SemanticAnalyzer
{
//-------------------------------------------------------------------------------------------------------
	// Implementacia PARSERA.
	public sealed class CParserEngine
	{
//-------------------------------------------------------------------------------------------------------
		private readonly CNonterminal							MAugmentedNonterminal;
		private readonly CNonterminalCollection					MNonterminalCollection;
		private readonly CTerminalCollection					MTerminalCollection;
		private readonly CRuleCollection						MLR0RulesCollection;
		private readonly CLR0Collection							MLR0ItemsCollection;
		private readonly CFirstSetCollection					MFirstSets;
		private readonly CFollowSetCollection					MFollowSets;
		private readonly CNFAStateCollection					MNFAStateCollection;
		private readonly CDFAStateCollection					MDFAStateCollectionLR1;
		private readonly CDFAStateCollection					MDFAStateCollectionLALR1;
		private readonly CParsingTable							MParsingTableLR1;
		private readonly CParsingTable							MParsingTableLALR1;
		private readonly CParsingStack							MParsingStack;
		private readonly CSourceTerminalsQueue					MSourceTerminalsQueue;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CParserEngine(CNonterminalCollection NonterminalCollection, CTerminalCollection TerminalCollection, DSolveShiftReduceConflict SolveShiftReduceConflict, DSolveReduceReduceConflict SolveReduceReduceConflict)
		{
			MTerminalCollection=TerminalCollection;

			List<CNonterminal>						Nontermials=new List<CNonterminal>();
			CNonterminal							StartNonterminal=NonterminalCollection.Nonterminals[0];
			string									AugmentedName=string.Format("{0}'",StartNonterminal);

			MAugmentedNonterminal=new CNonterminal(AugmentedName);

			CChoice									AugmentedChoice=new CChoice(MAugmentedNonterminal);

			AugmentedChoice.AddChoice(StartNonterminal);

			MAugmentedNonterminal.AddChoice(AugmentedChoice);

			Nontermials.Add(MAugmentedNonterminal);
			Nontermials.AddRange(NonterminalCollection.Nonterminals);

			MNonterminalCollection=new CNonterminalCollection(Nontermials);

			MLR0RulesCollection=new CRuleCollection(MNonterminalCollection.Nonterminals);
			MLR0ItemsCollection=new CLR0Collection(MLR0RulesCollection);

			MFirstSets=CalculateFirstSets();
			MFollowSets=CalculateFollowSets();

			MNFAStateCollection=new CNFAStateCollection();
			MDFAStateCollectionLR1=new CDFAStateCollection();
			MDFAStateCollectionLALR1=new CDFAStateCollection();
			MParsingTableLR1=new CParsingTable(SolveShiftReduceConflict,SolveReduceReduceConflict);
			MParsingTableLALR1=new CParsingTable(SolveShiftReduceConflict,SolveReduceReduceConflict);
			MParsingStack=new CParsingStack();
			MSourceTerminalsQueue=new CSourceTerminalsQueue();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// Vypocita FIRST SETS pre CHOICE.
		private CTerminal[] CalculateFirstSet(CFirstSetCollection FirstSets, CSymbol[] Symbols)
		{
			CTerminal								EmptyTerminal=MTerminalCollection.FindTerminalByType(typeof(CTerminal_EMPTY));
			int										SymbolIndex=0;
			bool									Continue=true;
			HashSet<CTerminal>						TerminalsToReturn=new HashSet<CTerminal>();

			while(SymbolIndex<Symbols.Length && Continue==true)
			{
				CSymbol								SymbolXi=Symbols[SymbolIndex];

				if ((SymbolXi is CTerminal)==true)
				{
					CTerminal						TypedSymbolXi=(CTerminal) SymbolXi;

					TerminalsToReturn.Add(TypedSymbolXi);
					Continue=false;
				}
				else
				{
					CNonterminal					TypedSymbolXi=(CNonterminal) SymbolXi;
					CFirstSet						FirstSetXi=FirstSets.GetFirstSetByNonterminal(TypedSymbolXi);
					CTerminal[]						TerminalsToAdd=FirstSetXi.GetAllButEmptyTerminals();

					foreach(CTerminal Terminal in TerminalsToAdd)
						TerminalsToReturn.Add(Terminal);

					if (FirstSetXi.ContainEmptyTerminal()==false)
						Continue=false;
				}

				SymbolIndex++;
			}

			if (Continue==true)
			{
				TerminalsToReturn.Add(EmptyTerminal);
			}

			CTerminal[]								Ret=TerminalsToReturn.ToArray();

			return(Ret);
		}
//-------------------------------------------------------------------------------------------------------
		// Vypocita FIRST SETS pre vsetky CHOICES vsetkych RULES.
		private CFirstSetCollection CalculateFirstSets()
		{
			CFirstSetCollection						FirstSets=new CFirstSetCollection();

			foreach(CNonterminal Nonterminal in MNonterminalCollection.Nonterminals)
			{
				CFirstSet							FirstSet=new CFirstSet(Nonterminal);

				FirstSets.AddFirstSet(FirstSet);
			}

			while(true)
			{
				bool								ChangeOccured=false;

				foreach(CNonterminal Nonterminal in MNonterminalCollection.Nonterminals)
				{
					CFirstSet						FirstSetA=FirstSets.GetFirstSetByNonterminal(Nonterminal);

					foreach(CChoice Choice in Nonterminal.Choices)
					{
						CSymbol[]					Symbols=Choice.Symbols;
						CTerminal[]					TerminalsToAdd=CalculateFirstSet(FirstSets,Symbols);

						if (FirstSetA.AddTerminals(TerminalsToAdd)==true)
							ChangeOccured=true;
					}
				}

				if (ChangeOccured==false)
					break;
			}

			return(FirstSets);
		}
//-------------------------------------------------------------------------------------------------------
		// Vypocita FOLLOW SETS pre vsetky CHOICES vsetkych RULES.
		private CFollowSetCollection CalculateFollowSets()
		{
			CFirstSetCollection						FirstSets=CalculateFirstSets();
			CFollowSetCollection					FollowSets=new CFollowSetCollection();
			CTerminal								EOFTerminal=MTerminalCollection.FindTerminalByType(typeof(CTerminal_EOF));
			CTerminal								EmptyTerminal=MTerminalCollection.FindTerminalByType(typeof(CTerminal_EMPTY));
			bool									First=true;

			foreach(CNonterminal Nonterminal in MNonterminalCollection.Nonterminals)
			{
				CFollowSet							FollowSet=new CFollowSet(Nonterminal);

				if (First==true)
				{
					FollowSet.AddTerminal(EOFTerminal);
					First=false;
				}

				FollowSets.AddFollowSet(FollowSet);
			}

			while(true)
			{
				bool								ChangeOccured=false;
			
				foreach(CNonterminal Nonterminal in MNonterminalCollection.Nonterminals)
				{
					CFollowSet						FollowSetA=FollowSets.GetFollowSetByNonterminal(Nonterminal);

					foreach(CChoice Choice in Nonterminal.Choices)
					{
						int							SymbolIndex=0;
						CSymbol[]					Symbols=Choice.Symbols;
						int							SymbolsLenth=Symbols.Length;

						while(SymbolIndex<SymbolsLenth)
						{
							CSymbol					SymbolXi=Symbols[SymbolIndex];

							if ((SymbolXi is CNonterminal)==true)
							{
								CNonterminal		NontermialXi=(CNonterminal) SymbolXi;
								CFollowSet			FollowSetXi=FollowSets.GetFollowSetByNonterminal(NontermialXi);

								if ((SymbolIndex+1)==SymbolsLenth)
								{
									CTerminal[]		FollowSetATerminals=FollowSetA.Terminals;

									if (FollowSetXi.AddTerminals(FollowSetATerminals)==true)
										ChangeOccured=true;
								}
								else
								{
									int				SymbolIndexXiPlus1=SymbolIndex+1;
									int				FirstSetLength=SymbolsLenth-SymbolIndexXiPlus1;
									CSymbol[]		FirstSetSymbols=new CSymbol[FirstSetLength];
									
									for(int i=0;i<FirstSetLength;i++)
										FirstSetSymbols[i]=Symbols[i+SymbolIndexXiPlus1];

									CTerminal[]		FirstSetTerminals=CalculateFirstSet(FirstSets,FirstSetSymbols);
									bool			ContainsEmptyTerminal=false;

									foreach(CTerminal FirstSetTerminal in FirstSetTerminals)
									{
										if (FirstSetTerminal.Name!=EmptyTerminal.Name)
										{
											if (FollowSetXi.AddTerminal(FirstSetTerminal)==true)
												ChangeOccured=true;
										}
										else
										{
											ContainsEmptyTerminal=true;
										}
									}

									if (ContainsEmptyTerminal==true)
									{
										CTerminal[]	FollowSetATerminals=FollowSetA.Terminals;

										if (FollowSetXi.AddTerminals(FollowSetATerminals)==true)
											ChangeOccured=true;
									}
								}
							}

							SymbolIndex++;
						}
					}
				}

				if (ChangeOccured==false)
					break;
			}

			return(FollowSets);
		}
//-------------------------------------------------------------------------------------------------------
		// Pre NFA STATE NFAState vypocita vsekty TRANSITIONS.
		// !!! Metoda vola REKURZIVNE SAMA SEBA a vyrata VSETKY NFA TRANSITIONS pre VSETKY NFA STATES.
		private void CalculateNFATransitions(CNFAState NFAState)
		{
			// COMPLETE LR1 ITEM NEMA ZIADNE TRANSITIONS.
			if (NFAState.Item.IsCompleteItem==false)
			{
				// 1. Ako prvy krok urcim 'A' TRANSITION, kde 'A' je SYMBOL (moze byt TERMINAL i NON-TERMINAL) nachadzajuci sa HNED za PERIOD SYMBOLOM.

				// Najdem SYMBOL za PERIOD v LR1 ITEM.
				CSymbol								SymbolAfterPeriod=NFAState.Item.GetSymbolAfterPeriod();
				CTerminal_EMPTY						EmptyTerminal=MTerminalCollection.FindTerminalByType<CTerminal_EMPTY>();
				List<CNFAState>						NewNFAStates=new List<CNFAState>();
				// INKREMENTUJEM poziciu PERIOD v LR1 ITEM.
				CSymbol[]							SymbolsWithIncrementedPeriodPosition=NFAState.Item.GetSymbolsWithIncrementedPeriodPosition();
				CLR0Item							LR0Item=new CLR0Item(NFAState.Item.LR0Item.Nonterminal,SymbolsWithIncrementedPeriodPosition);
				CTerminal							LR1ItemTerminal=NFAState.Item.Terminal;
				// Urcim NOVY LR1 ITEM.
				CLR1Item							LR1Item=new CLR1Item(LR0Item,LR1ItemTerminal);
				// Zistim ci sa LR1 ITEM uz nachadza v COLLECTION MNFAStateCollection.
				CNFAState							DestinationNFAState=MNFAStateCollection.GetNFAStateWithLR1Item(LR1Item);

				// Ak sa  LR1 ITEM NENACHADZA v COLLECTION MNFAStateCollection tak VYTVORIM NOVY NFA STATE.
				if (DestinationNFAState==null)
				{
					DestinationNFAState=new CNFAState(LR1Item);
					MNFAStateCollection.Add(DestinationNFAState);
					NewNFAStates.Add(DestinationNFAState);
				}

				// Vytvorim NFA TRANSITION z NFAState do vypocitaneho NFA STATE DestinationNFAState.
				// !!! Ako TRANSITION SYMBOL je SYMBOL, ktory sa nachadzal za PERIOD SYMBOLOM, teda SymbolAfterPeriod.
				CNFATransition						NewTransition=new CNFATransition(NFAState.Item,SymbolAfterPeriod,LR1Item);

				// Do NFAState pridam novy TRANSITION.
				NFAState.AddTransition(NewTransition);

				// 2. Ako druhy krok urcim VSETKY EPSILON TRANSITIONS. Tie sa urcuju IBA ak SYMBOL 'A' je NON-TERMINAL.

				// Ak SymbolAfterPeriod je NON-TERMINAL MUSIM vypocitat aj VSETKY EPSILON TRANSITIONS z NFAState.
				if ((SymbolAfterPeriod is CNonterminal)==true)
				{
					CNonterminal					NonterminalAfterPeriod=(CNonterminal) SymbolAfterPeriod;
					// Ziskam VSETKY SYMBOLY, ktore lezia za SymbolAfterPeriod.
					CSymbol[]						SymbolsAfterNonterminal=NFAState.Item.GetSymbolsAfterPeriod().Skip(1).ToArray();
					// SYMBOLY, ktore lezia za SymbolAfterPeriod dam do COLLECTION, aby som z nej mohol vyratat FIRST SET.
					List<CSymbol>					SymbolsToCalculateFirstSet=new List<CSymbol>(SymbolsAfterNonterminal);

					// Ako POSLEDNY SYMBOL pre vypocet FIRST SET TRANSITION TERMINAL.
					// Podla algoritmu musim vyratat FIRST(Xa), kde X su SymbolsAfterTerminal a 'a' je TRANSITION TERMINAL.
					SymbolsToCalculateFirstSet.Add(NFAState.Item.Terminal);

					// Vypocitam FIRST SET.
					CTerminal[]						FirstSet=CalculateFirstSet(MFirstSets,SymbolsToCalculateFirstSet.ToArray());
					// Najdem vsetky LR0 ITEMS, ktory zacina PERIOD SYMBOLOM, za ktorym nasleduje NON-TERMINAL SymbolAfterPeriod.
					CLR0Item[]						LR0ItemsWithPeriodAsFirstSymbolAndNonterminalAsNextSymbol=MLR0RulesCollection.GetLR0ItemsWithPeriodAsFirstSymbolAndNonterminalAsNextSymbol(NonterminalAfterPeriod);

					// Prechadzam VSETKY LR0 ITEMS, ktore zacinaju PERIOD SYMBOLOM, za ktorym nasleduje NON-TERMINAL SymbolAfterPeriod.
					foreach(CLR0Item LR0ItemWithPeriodAsFirstSymbolAndNonterminalAsNextSymbol in LR0ItemsWithPeriodAsFirstSymbolAndNonterminalAsNextSymbol)
					{
						// Prechadzam vsetkymi TERMINALS v mnozine FIRST SET.
						foreach(CTerminal FirstSetTerminal in FirstSet)
						{
							// Urcim NOVY LR1 STATE.
							CLR1Item				EpsilonLR1Item=new CLR1Item(LR0ItemWithPeriodAsFirstSymbolAndNonterminalAsNextSymbol,FirstSetTerminal);
							// Zistim ci sa v COLLECTION MNFAStateCollection nachadza identicky LR1 ITEM.
							CNFAState				EpsilonDestinationNFAState=MNFAStateCollection.GetNFAStateWithLR1Item(EpsilonLR1Item);

							// Ak sa v COLLECTION MNFAStateCollection NENACHADZA identicky LR1 ITEM, tak vytvorim NOVY NFA STATE.
							if (EpsilonDestinationNFAState==null)
							{
								EpsilonDestinationNFAState=new CNFAState(EpsilonLR1Item);
								MNFAStateCollection.Add(EpsilonDestinationNFAState);

								// NOVY NFA STATE zaradim do COLLECTION NewNFAStates obahujucej NOVO-VYTVORENE NFA STATES.
								NewNFAStates.Add(EpsilonDestinationNFAState);
							}

							// Urcim novu EPSILON NFA TRANSITION medzi NFAState a EpsilonLR1Item.
							CNFATransition			EpsilonNewTransition=new CNFATransition(NFAState.Item,EmptyTerminal,EpsilonLR1Item);

							NFAState.AddTransition(EpsilonNewTransition);
						}
					}
				}

				// !!! Pre vsetky NOVE NFA STATE REKURZIVNE volam metodu, aby sa i pre ne vypocital ich NFA TRANSITIONS.
				foreach(CNFAState NewNFAState in NewNFAStates)
				{
					CalculateNFATransitions(NewNFAState);
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Metoda vypocita NFA.
		private void CalculcateNFA(bool PrintLog)
		{
			// Ziskam START LR0 ITEM.
			CLR0Item								StartLR0Item=MLR0ItemsCollection.Items[0];
			CTerminal_EOF							EOF=MTerminalCollection.FindTerminalByType<CTerminal_EOF>();
			// START LR1 ITEM obsahuje START LR0 ITEM a EMPTY SYMBOL.
			CLR1Item								StartLR1Item=new CLR1Item(StartLR0Item,EOF);
			// Urcim START NFA STATE obsahujuci START LR1 ITEM.
			CNFAState								StartNFAState=new CNFAState(StartLR1Item);

			MNFAStateCollection.Add(StartNFAState);

			// Vypocitam vsetky TRANSITIONS zo START NFA STATE.
			// !!! Kedze metoda je volana REKURZIVNE, tak vyrata KOMPLETNY NFA.
			CalculateNFATransitions(StartNFAState);

			if (PrintLog==true)
			{
				Console.WriteLine(string.Format("Number of NFA STATES: [{0}] !",MNFAStateCollection.NFAStates.Length));
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Metoda vypocita pre NFA STATE NFAState EPSILON CLAUSURE a to tak, ze najde z NFA STATE NFAState vsetky TRANSITIONS prechadzajuce cez EPSILON SYMBOL.
		private void CalculateEpsilonClausure(CNFAState NFAState, CNFAStateUniqueCollection EpsilonClausureStates)
		{
			// !!!!! MUSIM tu dat tuto podmienku, pretoze NFAState moze mat EPSILON TRANSITION i SAM na SEBA a ak by tu ta podmienka NEBOLA, tak by som mal NEKONECNU REKURZIU a STACK OVERFLOW.
			if (EpsilonClausureStates.Add(NFAState)==true)
			{
				foreach(CNFATransition Transition in NFAState.Transitions)
				{
					if (Transition.IsEpsilonTransition==true)
					{
						CLR1Item						DestinationItem=Transition.DestinationItem;
						CNFAState						DestinationState=MNFAStateCollection.GetNFAStateWithLR1Item(DestinationItem);

						// REKURZIVNE volam metodu, aby z NFA STATES do ktorych sa cez EPSILON TRANSITION da z NFAState nasiel aj ich EPSILON CLAUSURES.
						CalculateEpsilonClausure(DestinationState,EpsilonClausureStates);
					}
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Metoda najde z NFA STATE vsetky TRANSITIONS prechadzajuce cez SYMBOL TransitionSymbol.
		private void CalculateSymbolTransitions(CNFAState NFAState, CNFAStateUniqueCollection StatesBySymbolTransition, CSymbol TransitionSymbol)
		{
			foreach(CNFATransition Transition in NFAState.Transitions)
			{
				if (Transition.TransitionSymbol.Equals(TransitionSymbol)==true)
				{
					CLR1Item						DestinationItem=Transition.DestinationItem;
					CNFAState						DestinationState=MNFAStateCollection.GetNFAStateWithLR1Item(DestinationItem);

					StatesBySymbolTransition.Add(DestinationState);
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Vypocita pre DFA STATE DFAState vsetky jeho TRANSITIONS. Z KAZDEJ TRANSITION urci EPSILON CLAUSURE, ktora sa stava NOVYM DFA STATE.
		// !!! Metoda vola REKURZIVNE SEBA SAMU, takze vysledkom vypoctu je KOMPLETNY DFA.
		private void CalculateDFATransitions(CDFAState DFAState)
		{
			// Vypocitam vsetky NON-EPSILON SYMBOLS, ktore z DFA STATE DFAState (DFA STATE je tvoreny 1-N NFA STATES) vytvaraju TRANSITIONS.
			CSymbol[]								TransitionSymbols=DFAState.GetAllNonEpsilonTransitionSymbols();
			
			// Prechadzam VSETKY NON-EPSILON SYMBOLS, ktore sposobuju TRANSITIONS z DFAState.
			foreach(CSymbol TransitionSymbol in TransitionSymbols)
			{
				CNFAStateUniqueCollection			DestinationNFAStatesForTransition=new CNFAStateUniqueCollection();

				// Prechadzam vsetky NFA STATES DFA STATE DFAState a vyratava NFA STATES do ktorych sa cez SYMBOL TransitionSymbol je mozne z DFAState dostat.
				foreach(CNFAState NFAStateInDFAState in DFAState.NFAStates)
				{
					// Vypocitam NFA STATES do ktorych sa cez SYMBOL TransitionSymbol je mozne z jedneho NFA STATE patriacemu DFA STATE DFAState dostat.
					CalculateSymbolTransitions(NFAStateInDFAState,DestinationNFAStatesForTransition,TransitionSymbol);
				}

				CNFAStateUniqueCollection			DestinationEpsilonClausureNFAStatesForTransition=new CNFAStateUniqueCollection();

				// Prechadzam vsetky NFA STATES do ktorych sa cez SYMBOL TransitionSymbol z daneho DFA STATE je mozne dostat a vyratava pre ne EPSILON CLAUSURE.
				foreach(CNFAState DestinationNFAStateForTransition in DestinationNFAStatesForTransition.NFAStates)
				{
					// Vypocitam EPSILON CLAUSURE pre NFA STATE.
					CalculateEpsilonClausure(DestinationNFAStateForTransition,DestinationEpsilonClausureNFAStatesForTransition);
				}

				// EPSILON CLAUSURE vytvaram DFA STATE DestinationDFAState.
				// !!! Zistim ci sa DFA STATE DestinationDFAState uz NACHADZA v COLLECTION MDFAStateCollection - teda ci sa jedna o NOVY DFA STATE, alebo EXISTUJUCI DFA STATE.
				CDFAState							DestinationDFAState=MDFAStateCollectionLR1.GetDFAStateWithSameNFAStates(DestinationEpsilonClausureNFAStatesForTransition.NFAStates);
				bool								DestinationStateAdded=false;

				// Ak sa DFA STATE NENACHADZA v MDFAStateCollection, tak VYTVORIM NOVY DFA STATE.
				if (DestinationDFAState==null)
				{
					// VYTOVRIM NOVY DFA STATE.
					DestinationDFAState=new CDFAState(DestinationEpsilonClausureNFAStatesForTransition.NFAStates);
					// NOVY DFA STATE zaradim do COLLECTION MDFAStateCollection.
					MDFAStateCollectionLR1.Add(DestinationDFAState);
					DestinationStateAdded=true;
				}

				// Do DFA STATE DFAState pridam pre SYMBOL TransitionSymbol VSETKY DFA TRANSITIONS.
				foreach(CNFAState NewState in DestinationEpsilonClausureNFAStatesForTransition.NFAStates)
				{
					CDFATransition					DFATransition=new CDFATransition(DFAState,TransitionSymbol,DestinationDFAState);

					DFAState.AddTransition(DFATransition);
				}

				// !!! Ak sa jedna o NOVY DFA STATE, tak REKURZIVNE pre neho vyratam jeho DFA TRANSITIONS.
				if (DestinationStateAdded==true)
				{
					CalculateDFATransitions(DestinationDFAState);
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Vypocitava DFA z NFA.
		private void CalculcateDFA(bool PrintLog)
		{
			// Vypocitam NFA a vysledok ulozi do MNFAStateCollection.
			CalculcateNFA(PrintLog);

			// Zoberie START STATE z NFA.
			CNFAState								StartNFAState=MNFAStateCollection.NFAStates[0];
			CNFAStateUniqueCollection				StartNFAStateEpsilonClausure=new CNFAStateUniqueCollection();

			// Vypocitam EPSILON CLAUSURE pre START STATE.
			CalculateEpsilonClausure(StartNFAState,StartNFAStateEpsilonClausure);

			// EPSILON CLAUSURE pre START STATE urcuje START STATE pre DFA.
			CDFAState								StartDFAState=new CDFAState(StartNFAStateEpsilonClausure.NFAStates);

			// Novy DFA STATE dam do COLLECTION vsetkych DFA STATES.
			MDFAStateCollectionLR1.Add(StartDFAState);

			// Vypocitam TRANSITIONS z DFA START STATE.
			// !!! Kedze metoda pracuje REKURZIVNE, tak su zaroven vypocitane i vsetky dalsie DFA STATES a z NFA je vypocitany KOMPLETNY DFA.
			CalculateDFATransitions(StartDFAState);

			if (PrintLog==true)
			{
				Console.WriteLine(string.Format("Number of DFA STATES: [{0}] !",MDFAStateCollectionLR1.DFAStates.Length));
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Vypocitava LALR(1) DFA z DFA pre LR(1).
		private void CalculateLALRDFA(bool PrintLog)
		{
			List<CDFAState>								DFAStates=MDFAStateCollectionLR1.DFAStates.ToList();

			// Urcim vsetky DFA STATES pre LALR(1).
			while(DFAStates.Count>0)
			{
				CLALRCore								LALRCore=DFAStates[0].GetLALRCore();
				List<CDFAState>							StatesWithSameLALRCore=new List<CDFAState>();

				for(int i=0;i<DFAStates.Count;i++)
				{
					if (DFAStates[i].ContainsSameLALRCore(LALRCore)==true)
					{
						StatesWithSameLALRCore.Add(DFAStates[i]);
						DFAStates.RemoveAt(i);
						i--;
					}
				}

				CNFAStateUniqueCollection				NFAStates=new CNFAStateUniqueCollection();

				foreach(CDFAState DFAState in StatesWithSameLALRCore)
				{
					foreach(CNFAState NFAState in DFAState.NFAStates)
					{
						NFAStates.Add(NFAState);
					}
				}

				CDFAState								LALRDFAState=new CDFAState(NFAStates.NFAStates);

				MDFAStateCollectionLALR1.Add(LALRDFAState);
			}

			// Urcim vsetky TRANSITIONS DFA STATES pre LALR(1).
			foreach(CDFAState DFAState in MDFAStateCollectionLALR1.DFAStates)
			{
				CLALRCore								LALRCore=DFAState.GetLALRCore();
				CDFAState[]								DFAStatesInLR1WithSameCore=MDFAStateCollectionLR1.GetAllDFAStatesWithSameLALRCore(LALRCore);

				foreach(CDFAState DFAStateInLR1WithSameCore in DFAStatesInLR1WithSameCore)
				{
					CDFATransition[]					Transitions=DFAStateInLR1WithSameCore.Transitions;

					foreach(CDFATransition Transition in Transitions)
					{
						CDFAState						DestinationState=Transition.DestinationState;
						CLALRCore						DestinationStateLALRCore=DestinationState.GetLALRCore();
						CDFAState[]						DFAStatesInLALR1WithDestinationStateCore=MDFAStateCollectionLALR1.GetAllDFAStatesWithSameLALRCore(DestinationStateLALRCore);

						foreach(CDFAState DFAStateInLALR1WithDestinationStateCore in DFAStatesInLALR1WithDestinationStateCore)
						{
							CDFATransition				NewTransition=new CDFATransition(DFAState,Transition.TransitionSymbol,DFAStateInLALR1WithDestinationStateCore);

							DFAState.AddTransition(NewTransition);
						}
					}
				}
			}

			if (PrintLog==true)
			{
				Console.WriteLine(string.Format("Number of LALR(1) DFA STATES: [{0}] !",MDFAStateCollectionLALR1.DFAStates.Length));
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Vypocitava PARSING TABLE z DFA.
		private void CalculcateParsingTable(bool PrintLog)
		{
			if (PrintLog==true)
			{
				Console.WriteLine("CALCULATION of DFA and PARSING TABLE for LR(1) !");
			}

			CalculcateDFA(PrintLog);

			MParsingTableLR1.InitializeParsingTable(MDFAStateCollectionLR1,MNonterminalCollection,MTerminalCollection,MAugmentedNonterminal,PrintLog);

			if (PrintLog==true)
			{
				Console.WriteLine("CALCULATION of DFA and PARSING TABLE for LALR(1) !");
			}

			CalculateLALRDFA(PrintLog);

			MParsingTableLALR1.InitializeParsingTable(MDFAStateCollectionLALR1,MNonterminalCollection,MTerminalCollection,MAugmentedNonterminal,PrintLog);
		}
//-------------------------------------------------------------------------------------------------------
		private void ErrorRecoveryFindValidGotoState(CParsingTableCell[] GotoCells, CParsingTable ParsingTable, CTerminal CurrentSourceCodeTerminal, ref CParsingTableCell GotoCellWithLegalAction, ref CParsingTableCell LegalActionCell)
		{
			foreach(CParsingTableCell GotoCell in GotoCells)
			{
				CParsingTableOperation_Goto				GotoAction=(CParsingTableOperation_Goto) GotoCell.Operation;
				CParsingTableRow						GotoParsingTableRow=ParsingTable.GetParsingTableRow(GotoAction.GotoDFAState);
				CParsingTableCell						GotoParsingTableCell=GotoParsingTableRow.GetCell(CurrentSourceCodeTerminal);

				if (GotoParsingTableCell!=null)
				{
					// SHIFT ma preferenciu pred REDUCE.
					if ((GotoParsingTableCell.Operation is CParsingTableOperation_Shift)==true)
					{
						GotoCellWithLegalAction=GotoCell;
						LegalActionCell=GotoParsingTableCell;
						break;
					}

					if ((GotoParsingTableCell.Operation is CParsingTableOperation_Reduce)==true)
					{
						if (GotoCellWithLegalAction==null)
						{
							GotoCellWithLegalAction=GotoCell;
							LegalActionCell=GotoParsingTableCell;
						}
						else
						{
							// Symbol je NON-TERMINAL, kedze vznikol z GOTO ACTION.
							CNonterminal				ActualNonterminal=(CNonterminal) GotoCellWithLegalAction.Symbol;
							CNonterminal				NewNonterminal=(CNonterminal) GotoCell.Symbol;
											
							int							ActualNonterminalIndex=MNonterminalCollection.GetIndex(ActualNonterminal);
							int							NewNonterminalIndex=MNonterminalCollection.GetIndex(NewNonterminal);
											
							// Vyberiem MENEJ VSEOBECNY NON-TERMINAL, co v mojom zjednoduseni bude NON-TERMINAL uvedeny NIZSIE v BNF.
							if (NewNonterminalIndex>ActualNonterminalIndex)
							{
								GotoCellWithLegalAction=GotoCell;
								LegalActionCell=GotoParsingTableCell;
							}
						}
					}
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// Implementuje PARSING ALGORITMUS LR(1) a LALR(1).
		public bool DoParseLR1OrLALR(bool PrintLog, EParserType ParserType, CToken[] SourceCodeTokens, out CParsingStackItem RootParsingStackItem, CParsingErrorCollection ParsingErrorCollection, bool DoErrorRecovery)
		{
			CalculcateParsingTable(PrintLog);

			MParsingStack.Clear();
			MSourceTerminalsQueue.Clear();

			List<CSourceTerminalsQueueItem>							TokenItems=new List<CSourceTerminalsQueueItem>();

			// Konvertujem TOKENS na TERMINALS.
			foreach(CToken SourceCodeToken in SourceCodeTokens)
			{
				CTerminal											SourceCodeTerminal=MTerminalCollection.FindTerminalByScanerToken(SourceCodeToken);
				// Kazdy SOURCE TERMINAL QUEUE ITEM obsahuje okrem TERMINALU aj povodny TOKEN, aby som mohol ziskat jeho LEXEMU. To je dolezite napriklad pre identifikaciou nazvov premennych, alebo funkcii.
				CSourceTerminalsQueueItem							Item=new CSourceTerminalsQueueItem(SourceCodeTerminal,SourceCodeToken);

				TokenItems.Add(Item);
			}

			// Naplnim SOURCE CODE QUEUE.
			MSourceTerminalsQueue.Fill(TokenItems.ToArray());

			CParsingTable											ParsingTable;
			CDFAStateCollection										DFAStateCollection;

			if (ParserType==EParserType.E_PT_LR_1)
			{
				ParsingTable=MParsingTableLR1;
				DFAStateCollection=MDFAStateCollectionLR1;
			}
			else
			{
				ParsingTable=MParsingTableLALR1;
				DFAStateCollection=MDFAStateCollectionLALR1;
			}

			CTerminal												EOFTerminal=MTerminalCollection.FindTerminalByType(typeof(CTerminal_EOF));
			CTerminal												EMPTYTerminal=MTerminalCollection.FindTerminalByType(typeof(CTerminal_EMPTY));
			CDFAState												StartDFAState=DFAStateCollection.DFAStates[0];
			CParseTreeNode											StartTreeNode=new CParseTreeNode(EOFTerminal,null);
			CParsingStackItem										TopParsingStackItem=new CParsingStackItem(StartDFAState,StartTreeNode,null);
			CParsingStackItem										ErrorRecoveryStackItem=null;
			// Sluzi na detekciu INFINITE LOOPS pri ERROR RECOVERY.
			List<CParsingStackItem>									AddedErrorItems=new List<CParsingStackItem>();

			int														NumberOfCycles=0;
			int														NumberOfShifts=0;
			int														NumberOfReduces=0;

			// Do PARSING STACK dam START STATE z DFA automatu a znak '$'.
			MParsingStack.Add(TopParsingStackItem);

			// Cyklus je opakovany az kym nie je najdeny ACCEPT stav, alebo ERROR.
			while(true)
			{
				NumberOfCycles++;

				// Urobim PEEK nad SOURCE CODE INPUT STRING.
				CSourceTerminalsQueueItem							CurrentSourceCodeItem=MSourceTerminalsQueue.Peek();

				// Urobim PEEK nad PARSING STACK.
				CParsingStackItem									CurrentItem=MParsingStack.PeekTopOfStack();

				if (CurrentSourceCodeItem==null)
				{
					CParsingError									ParsingError=new CParsingError("END of SOURCE CODE REACHED !",(CurrentSourceCodeItem!=null) ? CurrentSourceCodeItem.Terminal : null,CurrentItem,MSourceTerminalsQueue.ToString());

					ParsingErrorCollection.AddParsingError(ParsingError);
					RootParsingStackItem=null;

					if (PrintLog==true)
					{
						Console.WriteLine(string.Format("NumberOfCycles: [{0}] !",NumberOfCycles));
						Console.WriteLine(string.Format("NumberOfShifts: [{0}] !",NumberOfShifts));
						Console.WriteLine(string.Format("NumberOfReduces: [{0}] !",NumberOfReduces));
					}

					return(false);
				}

				CTerminal											CurrentSourceCodeTerminal=CurrentSourceCodeItem.Terminal;

				if (CurrentItem==null)
				{
					CParsingError									ParsingError=new CParsingError("TOP of STACK FOUND !",CurrentSourceCodeTerminal,CurrentItem,MSourceTerminalsQueue.ToString());

					ParsingErrorCollection.AddParsingError(ParsingError);
					RootParsingStackItem=null;

					if (PrintLog==true)
					{
						Console.WriteLine(string.Format("NumberOfCycles: [{0}] !",NumberOfCycles));
						Console.WriteLine(string.Format("NumberOfShifts: [{0}] !",NumberOfShifts));
						Console.WriteLine(string.Format("NumberOfReduces: [{0}] !",NumberOfReduces));
					}

					return(false);
				}

				// Z AKTUALNEHO STATE DFA automatu v PARSING STACK a AKUTALNEHO TERMINALU z SOURCE CODE INPUT STRING ziskam PARSING TABLE CELL s operaciou, ktoru je potrebne vykonat.
				CParsingTableRow									ParsingTableRow=ParsingTable.GetParsingTableRow(CurrentItem.DFAState);
				CParsingTableCell									ParsingTableCell=ParsingTableRow.GetCell(CurrentSourceCodeTerminal);

				// Ak CELL neobsahuje ziadnu operaciu SKUSIM ERROR RECOVERY.
				// !!!!! Algoritmus ERROR RECOVERY, kedze pridava novy STATE MOZE VIEST za istych okolnosti k NEKONECNEMU CYKLU.
				if (ParsingTableCell==null)
				{
					CParsingError									ParsingError1=new CParsingError("Can't find CELL in PARSING TABLE !",CurrentSourceCodeTerminal,CurrentItem,MSourceTerminalsQueue.ToString());

					ParsingErrorCollection.AddParsingError(ParsingError1);

					if (DoErrorRecovery==false)
					{
						RootParsingStackItem=null;

						if (PrintLog==true)
						{
							Console.WriteLine(string.Format("NumberOfCycles: [{0}] !",NumberOfCycles));
							Console.WriteLine(string.Format("NumberOfShifts: [{0}] !",NumberOfShifts));
							Console.WriteLine(string.Format("NumberOfReduces: [{0}] !",NumberOfReduces));
						}

						return(false);
					}

					bool											FinishErrorRecovery=false;

					// Zacnem ERROR RECOVERY.
					while(FinishErrorRecovery==false)
					{
						CurrentItem=MParsingStack.PeekTopOfStack();

						if (CurrentItem==null)
						{
							CParsingError							ParsingError2=new CParsingError("TOP of STACK FOUND !",CurrentSourceCodeTerminal,CurrentItem,MSourceTerminalsQueue.ToString());

							ParsingErrorCollection.AddParsingError(ParsingError2);

							RootParsingStackItem=null;

							if (PrintLog==true)
							{
								Console.WriteLine(string.Format("NumberOfCycles: [{0}] !",NumberOfCycles));
								Console.WriteLine(string.Format("NumberOfShifts: [{0}] !",NumberOfShifts));
								Console.WriteLine(string.Format("NumberOfReduces: [{0}] !",NumberOfReduces));
							}

							return(false);
						}

						CParsingTableRow							ErrorParsingTableRow=ParsingTable.GetParsingTableRow(CurrentItem.DFAState);
						
						if (ErrorParsingTableRow.HasGotoCells()==true)
						{
							ErrorRecoveryStackItem=CurrentItem;

							CParsingTableCell[]						GotoCells=ErrorParsingTableRow.GetAllGotoCells();
							CParsingTableCell						GotoCellWithLegalAction=null;
							CParsingTableCell						LegalActionCell=null;

							while(true)
							{
								CurrentSourceCodeItem=MSourceTerminalsQueue.Peek();

								if (CurrentSourceCodeItem==null)
								{
									CParsingError					ParsingError=new CParsingError("END of SOURCE CODE REACHED !",(CurrentSourceCodeItem!=null) ? CurrentSourceCodeItem.Terminal : null,CurrentItem,MSourceTerminalsQueue.ToString());

									ParsingErrorCollection.AddParsingError(ParsingError);
									RootParsingStackItem=null;

									if (PrintLog==true)
									{
										Console.WriteLine(string.Format("NumberOfCycles: [{0}] !",NumberOfCycles));
										Console.WriteLine(string.Format("NumberOfShifts: [{0}] !",NumberOfShifts));
										Console.WriteLine(string.Format("NumberOfReduces: [{0}] !",NumberOfReduces));
									}

									return(false);
								}

								CurrentSourceCodeTerminal=CurrentSourceCodeItem.Terminal;

								// Zistim ci pre NOVY TERMINAL (TOKEN) nenajdem LEGALNY GOTO ACTION.
								ErrorRecoveryFindValidGotoState(GotoCells,ParsingTable,CurrentSourceCodeTerminal,ref GotoCellWithLegalAction,ref LegalActionCell);

								if (GotoCellWithLegalAction!=null)
								{
									CParsingTableOperation_Goto		GotoAction=(CParsingTableOperation_Goto) GotoCellWithLegalAction.Operation;
									CDFAState						NewDFAState=GotoAction.GotoDFAState;
									CParseTreeNode					NewParseTreeNode=new CParseTreeNode(CurrentSourceCodeTerminal,CurrentSourceCodeItem.Token);
									CParsingStackItem				NewParsingStackItem=new CParsingStackItem(NewDFAState,NewParseTreeNode,null);
									bool							InfiniteLoopDetected=false;

									// Zistim ci som uz tento STATE pri ERROR RECOVERY uz nepridal do PARSING STACK, BEZ TOHO, aby som spravil medzitym SHIFT - teda posunul sa v INPUT STRINGU.
									foreach(CParsingStackItem AddedErrorItem in AddedErrorItems)
									{
										if (AddedErrorItem.DFAState.ContainsSameNFAStates(NewParsingStackItem.DFAState.NFAStates)==true)
										{
											InfiniteLoopDetected=true;
											break;
										}
									}

									if (InfiniteLoopDetected==true)
									{
										MParsingStack.PopTopOfStack(1);
										break;
									}

									MParsingStack.Add(NewParsingStackItem);
									// Pridam STATE, aby som neskor mohol detekovat ci nesposobuje pri ERROR RECOVERY INFINITE LOOP.
									AddedErrorItems.Add(NewParsingStackItem);

									ParsingTableCell=LegalActionCell;

									FinishErrorRecovery=true;
									break;
								}

								// Vyhodim aktualny token.
								MSourceTerminalsQueue.Dequeue();

								if (PrintLog==true)
								{
									Console.WriteLine("Current TERMINAL [{0}] IGNORED because of ERROR !",CurrentSourceCodeTerminal);
								}
							}
						}
						else
						{
							// Ak STATE v PARSING STACK neobsahuje GOTO ACTION, tak ho ODSTRANIM z PARSING STACK.
							MParsingStack.PopTopOfStack(1);
						}
					}
				}

				CParsingTableOperation								ParsingTableOperation=ParsingTableCell.Operation;

				// Ak sa jedna o operaciu typu ACCEPT, tak PARSING je USPESNY a CYKLUS je UKONCENY.
				if ((ParsingTableOperation is CParsingTableOperation_Accept)==true)
				{
					if (CurrentSourceCodeTerminal.Equals(EOFTerminal)==false)
					{
						CParsingError								ParsingError=new CParsingError("Parsing FINISHED but INPUT is NOT EMPTY !",CurrentSourceCodeTerminal,CurrentItem,MSourceTerminalsQueue.ToString());

						ParsingErrorCollection.AddParsingError(ParsingError);
						RootParsingStackItem=null;

						if (PrintLog==true)
						{
							Console.WriteLine(string.Format("NumberOfCycles: [{0}] !",NumberOfCycles));
							Console.WriteLine(string.Format("NumberOfShifts: [{0}] !",NumberOfShifts));
							Console.WriteLine(string.Format("NumberOfReduces: [{0}] !",NumberOfReduces));
						}

						return(false);
					}
					else
					{
						RootParsingStackItem=CurrentItem;

						if (PrintLog==true)
						{
							Console.WriteLine(string.Format("NumberOfCycles: [{0}] !",NumberOfCycles));
							Console.WriteLine(string.Format("NumberOfShifts: [{0}] !",NumberOfShifts));
							Console.WriteLine(string.Format("NumberOfReduces: [{0}] !",NumberOfReduces));
						}

						return(true);
					}
				}
				// Ak sa jedna o operaciu typu SHIFT, presuniem TERMINAL zo SOURCE CODE INPUT STREAM do PARSING STACK.
				else if ((ParsingTableOperation is CParsingTableOperation_Shift)==true)
				{
					NumberOfShifts++;

					CParsingTableOperation_Shift					TypedParsingTableOperation=(CParsingTableOperation_Shift) ParsingTableOperation;

					CDFAState										NewDFAState=TypedParsingTableOperation.DFAState;
					CParseTreeNode									NewParseTreeNode=new CParseTreeNode(CurrentSourceCodeTerminal,CurrentSourceCodeItem.Token);
					CParsingStackItem								NewParsingStackItem=new CParsingStackItem(NewDFAState,NewParseTreeNode,null);

					MParsingStack.Add(NewParsingStackItem);
					MSourceTerminalsQueue.Dequeue();

					// Ak bol spraveny SHIFT - posunul som sa v INPUT STRING, tak ERROR RECOVERY PREBEHOL USPESNE a NESPOSOBIL INFINITE LOOP.
					AddedErrorItems.Clear();

					if (PrintLog==true)
					{
						Console.WriteLine("Current TERMINAL [{0}] SUCCESSFULLY PROCESSED !",CurrentSourceCodeTerminal);
					}
				}
				// Ak sa jedna o operaciu typu REDUCE odstranim z PARSING STACK 'N' ITEMS, kde 'N' je dlzka CHOICE A -> a, podla ktoreho robim REDUCE. V pripade CHOICE A -> ɛ je tato dlzka rovna 0. Nasledne ziskam AKTUALNY ITEM z PARSING STACK (po odstraneni ITEMS cez REDUCE). Potom NAJDEM v PARSING STACK CELL(AfterReduceState,A), kde 'AfterReduceState' je hodnota DFA STATE v AKTUALNOM ITEM a 'A' je NONTERMINAL podla ktoreho CHOICE som robil REDUCE. Novy DFA STATE je STATE na ktory spravim GOTO.
				else if ((ParsingTableOperation is CParsingTableOperation_Reduce)==true)
				{
					NumberOfReduces++;

					CParsingTableOperation_Reduce					TypedParsingTableOperation=(CParsingTableOperation_Reduce) ParsingTableOperation;
					CChoice											Choice=TypedParsingTableOperation.Choice;
					CNonterminal									ChoiceNonterminal=TypedParsingTableOperation.Choice.Nonterminal;
					CParseTreeNode									ChoiceTreeNode=new CParseTreeNode(ChoiceNonterminal,null);
					CSyntaxTreeNode									SyntaxTreeNode;

					// Pri CHOICE A -> a sa z PARSING STACK VYHODI pocet ITEMS zodpovedajuci dlzke retazca CHOICE 'a'.
					if (Choice.IsEmptyChoice==false)
					{
						int											NumberOfSymbolInChoice=TypedParsingTableOperation.Choice.Symbols.Length;
						CParsingStackItem[]							DequeuedStackItems=MParsingStack.PopTopOfStack(NumberOfSymbolInChoice);

						// Pridam do TREE NODE reprezentujuci A -> a.
						foreach(CParsingStackItem DequeuedStackItem in DequeuedStackItems)
						{
							ChoiceTreeNode.AddChildNode(DequeuedStackItem.ParseTreeNode);
						}

						SyntaxTreeNode=CSyntaxTreeNodeFactory.CreateParseTreeNode(Choice,DequeuedStackItems);
					}
					// Pri CHOICE A -> ɛ sa z PARSING STACK NIC NEVYHADZUJE.
					else
					{
						// Pridam do TREE NODE reprezentujuci A -> ɛ.
						CParseTreeNode								EmptyTreeNode=new CParseTreeNode(EMPTYTerminal,null);

						ChoiceTreeNode.AddChildNode(EmptyTreeNode);

						SyntaxTreeNode=CSyntaxTreeNodeFactory.CreateParseTreeNode(Choice,null);
					}

					// Ziskam ITEM PO VYHODENI ITEMS z PARSING STACK.
					CParsingStackItem								AfterReduceItem=MParsingStack.PeekTopOfStack();

					// Ziskam CELL(AfterReduceItem,A).
					CParsingTableRow								AfterReduceParsingTableRow=ParsingTable.GetParsingTableRow(AfterReduceItem.DFAState);
					CParsingTableCell								AfterReduceParsingTableCell=AfterReduceParsingTableRow.GetCell(ChoiceNonterminal);

					// !!! MUSI sa jednat o GOTO operaciu.
					CParsingTableOperation_Goto						GotoOperation=(CParsingTableOperation_Goto) AfterReduceParsingTableCell.Operation;

					// Spravim GOTO na State obsiahnuty v CELL(AfterReduceItem,A).
					CParsingStackItem								NewItem=new CParsingStackItem(GotoOperation.GotoDFAState,ChoiceTreeNode,SyntaxTreeNode);

					MParsingStack.Add(NewItem);
				}
				else
				{
					throw(new InvalidOperationException(string.Format("UNKNOWN PARSING TABLE OPERATION [{0}] !",ParsingTableOperation)));
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------