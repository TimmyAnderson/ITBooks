using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
using CRowDictionary=System.Collections.Generic.Dictionary<RuntimeEnvironment.CDFAState,RuntimeEnvironment.CParsingTableRow>;
//-------------------------------------------------------------------------------------------------------
namespace RuntimeEnvironment
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CParsingTable
	{
//-------------------------------------------------------------------------------------------------------
		private readonly DSolveShiftReduceConflict				MSolveShiftReduceConflict;
		private readonly DSolveReduceReduceConflict				MSolveReduceReduceConflict;
		private readonly CRowDictionary							MRows;
//-------------------------------------------------------------------------------------------------------
		private int												MNumberOfShiftReduceConflicts;
		private int												MNumberOfReduceReduceConflicts;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CParsingTable(DSolveShiftReduceConflict SolveShiftReduceConflict, DSolveReduceReduceConflict SolveReduceReduceConflict)
		{
			MSolveShiftReduceConflict=SolveShiftReduceConflict;
			MSolveReduceReduceConflict=SolveReduceReduceConflict;
			MRows=new CRowDictionary();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CParsingTableRow[]								Rows
		{
			get
			{
				return(MRows.Values.ToArray());
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private CParsingTableCell SolveShiftReduceConflict(CDFAState ConflictingDFAState, CTerminal ConflictingTerminal)
		{
			MNumberOfShiftReduceConflicts++;

			return(MSolveShiftReduceConflict(ConflictingDFAState,ConflictingTerminal));
		}
//-------------------------------------------------------------------------------------------------------
		private CParsingTableCell SolveReduceReduceConflict(CDFAState ConflictingDFAState, CTerminal ConflictingTerminal)
		{
			MNumberOfReduceReduceConflicts++;

			return(MSolveReduceReduceConflict(ConflictingDFAState,ConflictingTerminal));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void InitializeParsingTable(CDFAStateCollection DFAStateCollection, CNonterminalCollection NonterminalCollection, CTerminalCollection TerminalCollection, CNonterminal AugumentedNonterminal, bool PrintLog)
		{
			CTerminal_EMPTY											EmptyTerminal=TerminalCollection.FindTerminalByType<CTerminal_EMPTY>();

			// Vytovri ROWS pre vsetky DFA STATES.
			foreach(CDFAState DFAState in DFAStateCollection.DFAStates)
			{
				CParsingTableRow									Row=new CParsingTableRow(DFAState);

				MRows.Add(DFAState,Row);
			}

			// Naplni ROWS PARSING TABLE.
			foreach(CDFAState DFAState in DFAStateCollection.DFAStates)
			{
				CParsingTableRow									Row=MRows[DFAState];

				// Ak obsahuje COMPLETE ITEMS, tak MOZE obsahovat REDUCE RULE. Moze obsahovat i SHIFT RULE, ale to iba ak existuje SHIFT-REDUCE CONFLICT a jeho riesenim bude vola SHIFT RULE - co je obvykle riesenie SHIFT-REDUCE CONFLICTS.
				if (DFAState.ContainsCompleteLR1Item()==true)
				{
					// Ak je COMPLETE ITEM ako JEDINY NFA STATE v DFA STATE, tak NEMOZE nastat CONFLICT a COMPLETE ITEM sa zmeni na REDUCE, alebo ACCEPT RULE.
					if (DFAState.NFAStates.Length==1)
					{
						CNFAState									CompleteState=DFAState.NFAStates[0];
						CSymbol										TransitionSymbol=CompleteState.Item.Terminal;
						CNonterminal								Nonterminal=CompleteState.Item.LR0Item.Nonterminal;
						CSymbol[]									ChoiceSymbols=CompleteState.Item.GetSymbolsExceptPeriod();

						// Ak mam CHOICE A -> ., tak sa transformuje na A -> ɛ.
						if (ChoiceSymbols.Length==0)
						{
							ChoiceSymbols=new CSymbol[]{EmptyTerminal};
						}

						CChoice										Choice=NonterminalCollection.FindChoice(Nonterminal,ChoiceSymbols);

						if (Choice==null)
						{
							throw(new InvalidOperationException(string.Format("Can't find CHOICE for NON-TERMINAL [{0}] !",Nonterminal)));
						}

						if ((TransitionSymbol is CTerminal_EOF)==false)
						{
							CParsingTableOperation					Operation=new CParsingTableOperation_Reduce(Choice);
							CParsingTableCell						Cell=new CParsingTableCell(TransitionSymbol,Operation);

							Row.AddCell(Cell);
						}
						else
						{
							if (Nonterminal.Equals(AugumentedNonterminal)==true)
							{
								CParsingTableOperation				Operation=new CParsingTableOperation_Accept(Choice);
								CParsingTableCell					Cell=new CParsingTableCell(TransitionSymbol,Operation);

								Row.AddCell(Cell);
							}
							else
							{
								CParsingTableOperation				Operation=new CParsingTableOperation_Reduce(Choice);
								CParsingTableCell					Cell=new CParsingTableCell(TransitionSymbol,Operation);

								Row.AddCell(Cell);
							}
						}
					}
					else
					{
						CNFAState[]									CompleteStates=DFAState.GetAllCompleteLR1Items();

						foreach(CNFAState CompleteState in CompleteStates)
						{
							CTerminal								LR1Terminal=CompleteState.Item.Terminal;

							// Zistim moznost SHIFT-REDUCE CONFLICT.
							bool									HasShiftReduceConflict=false;

							foreach(CNFAState NFAState in DFAState.NFAStates)
							{
								if (NFAState.Item.IsCompleteItem==false)
								{
									CSymbol							SymbolAfterPeriod=NFAState.Item.GetSymbolAfterPeriod();

									if (LR1Terminal.Equals(SymbolAfterPeriod)==true)
									{
										HasShiftReduceConflict=true;
										break;
									}
								}
							}

							if (HasShiftReduceConflict==true)
							{
								CParsingTableCell					Cell=SolveShiftReduceConflict(DFAState,LR1Terminal);

								Row.AddCell(Cell);
							}
							// Zistim moznost REDUCE-REDUCE CONFLICT.
							else
							{
								int									SameTerminalCounter=0;

								foreach(CNFAState NFAState in CompleteStates)
								{
									if (CompleteState.Item.Terminal.Equals(NFAState.Item.Terminal)==true)
									{
										SameTerminalCounter++;
									}
								}

								// REDUCE-REDUCE CONFLICT.
								if (SameTerminalCounter>2)
								{
									CParsingTableCell				Cell=SolveReduceReduceConflict(DFAState,LR1Terminal);

									Row.AddCell(Cell);
								}
								// Nie je ziaden CONFLICT a mozem pridat REDUCE RULE.
								else
								{
									CSymbol							TransitionSymbol=CompleteState.Item.Terminal;
									CNonterminal					Nonterminal=CompleteState.Item.LR0Item.Nonterminal;
									CSymbol[]						ChoiceSymbols=CompleteState.Item.GetSymbolsExceptPeriod();

									// Ak mam CHOICE A -> ., tak sa transformuje na A -> ɛ.
									if (ChoiceSymbols.Length==0)
									{
										ChoiceSymbols=new CSymbol[]{EmptyTerminal};
									}

									CChoice							Choice=NonterminalCollection.FindChoice(Nonterminal,ChoiceSymbols);

									if (Choice==null)
									{
										throw(new InvalidOperationException(string.Format("Can't find CHOICE for NON-TERMINAL [{0}] !",Nonterminal)));
									}

									if ((TransitionSymbol is CTerminal_EOF)==false)
									{
										CParsingTableOperation		Operation=new CParsingTableOperation_Reduce(Choice);
										CParsingTableCell			Cell=new CParsingTableCell(TransitionSymbol,Operation);

										Row.AddCell(Cell);
									}
									else
									{
										if (Nonterminal.Equals(AugumentedNonterminal)==true)
										{
											CParsingTableOperation	Operation=new CParsingTableOperation_Accept(Choice);
											CParsingTableCell		Cell=new CParsingTableCell(TransitionSymbol,Operation);

											Row.AddCell(Cell);
										}
										else
										{
											CParsingTableOperation	Operation=new CParsingTableOperation_Reduce(Choice);
											CParsingTableCell		Cell=new CParsingTableCell(TransitionSymbol,Operation);

											Row.AddCell(Cell);
										}
									}
								}
							}
						}
					}
				}

				foreach(CDFATransition Transition in DFAState.Transitions)
				{
					CSymbol											TransitionSymbol=Transition.TransitionSymbol;
					CParsingTableOperation							Operation=null;
					CDFAState										DestinationState=Transition.DestinationState;

					// TERMINAL.
					if ((TransitionSymbol is CTerminal)==true)
					{
						Operation=new CParsingTableOperation_Shift(DestinationState);
					}
					// NON-TERMINAL.
					else
					{
						Operation=new CParsingTableOperation_Goto(DestinationState);
					}

					CParsingTableCell								Cell=new CParsingTableCell(TransitionSymbol,Operation);

					Row.AddCell(Cell);
				}
			}

			if (PrintLog==true)
			{
				Console.WriteLine(string.Format("Number of SHIFT-REDUCE conflicts: [{0}] !",MNumberOfShiftReduceConflicts));
				Console.WriteLine(string.Format("Number of REDUCE-REDUCE conflicts: [{0}] !",MNumberOfReduceReduceConflicts));
			}
		}
//-------------------------------------------------------------------------------------------------------
		public CParsingTableRow GetParsingTableRow(CDFAState DFAState)
		{
			CParsingTableRow		ParsingTableRow=MRows[DFAState];

			return(ParsingTableRow);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------