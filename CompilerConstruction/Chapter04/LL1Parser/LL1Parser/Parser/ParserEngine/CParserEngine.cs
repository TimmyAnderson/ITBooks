using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace LL1Parser
{
//-------------------------------------------------------------------------------------------------------
	// Implementacia PARSERA.
	public sealed class CParserEngine
	{
//-------------------------------------------------------------------------------------------------------
		private readonly CNonterminalCollection					MNonterminalCollection;
		private readonly CTerminalCollection					MTerminalCollection;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CParserEngine(CNonterminalCollection NonterminalCollection, CTerminalCollection TerminalCollection)
		{
			MNonterminalCollection=NonterminalCollection;
			MTerminalCollection=TerminalCollection;
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

			CTerminal[]							Ret=TerminalsToReturn.ToArray();

			return(Ret);
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// Vypocita FIRST SETS pre vsetky CHOICES vsetkych RULES.
		public CFirstSetCollection CalculateFirstSets()
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
		public CFollowSetCollection CalculateFollowSets()
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
		// Vypocita PARSING TABLE z FIRST SETS a FOLLOW SETS.
		public CParsingTable CalculateParsingTable()
		{
			CFirstSetCollection				FirstSets=CalculateFirstSets();
			CFollowSetCollection			FollowSets=CalculateFollowSets();
			CParsingTable					ParsingTable=new CParsingTable();
			CTerminal						EmptyTerminal=MTerminalCollection.FindTerminalByType(typeof(CTerminal_EMPTY));

			foreach(CNonterminal Nonterminal in MNonterminalCollection.Nonterminals)
			{
				CParsingTableRow			Row=new CParsingTableRow(Nonterminal,MTerminalCollection.TerminalsButEmpty);
				CFirstSet					FirstSetForNonterminal=FirstSets.GetFirstSetByNonterminal(Nonterminal);
				CFollowSet					FollowSetForNonterminal=FollowSets.GetFollowSetByNonterminal(Nonterminal);

				foreach(CChoice Choice in Nonterminal.Choices)
				{
					CSymbol[]				Symbols=Choice.Symbols;
					CTerminal[]				FirstSetForChoice=CalculateFirstSet(FirstSets,Symbols);
					bool					AddFollowSet=false;

					foreach(CTerminal Terminal in FirstSetForChoice)
					{
						if (Terminal.Name!=EmptyTerminal.Name)
						{
							Row.AddChoice(Terminal,Choice);
						}
						else
						{
							AddFollowSet=true;
						}
					}

					if (AddFollowSet==true)
					{
						CTerminal[]			FollowSetTerminals=FollowSetForNonterminal.Terminals;

						foreach(CTerminal Terminal in FollowSetTerminals)
						{
							Row.AddChoice(Terminal,Choice);
						}
					}
				}

				// Add POP ERROR RECOVERY.
				Row.SetPOPErrorChoice(FollowSetForNonterminal);

				// Add SCAN ERROR RECOVERY.
				Row.SetSCANErrorChoice(FirstSetForNonterminal,FollowSetForNonterminal);

				if (Row.GetTerminalWithNoChoices().Length>0)
					throw(new InvalidOperationException(string.Format("NONTERMINAL [{0}] contains PARSING TABLE ENTRY with NO CHOICE !",Nonterminal)));

				ParsingTable.AddRow(Row);
			}

			return(ParsingTable);
		}
//-------------------------------------------------------------------------------------------------------
		// Vykona PARSING a vrati PARSE TREE.
		public CSyntaxTreeNode DoParse(CToken[] Tokens, DDisambiguationRuleDelegate DisambiguationRuleDelegate, out CParserErrorList Errors)
		{
			Errors=new CParserErrorList();

			CParsingTable					ParsingTable=CalculateParsingTable();
			CTerminal_EOF					TerminalEOF=MTerminalCollection.Terminals.OfType<CTerminal_EOF>().First();
			CTerminal_EMPTY					TerminalEMPTY=MTerminalCollection.Terminals.OfType<CTerminal_EMPTY>().First();
			// QUEUE obsahujuci TOKENS zo SCANERA.
			Queue<CToken>					TokenQueue=new Queue<CToken>(Tokens);
			// STACK obsahujuci NONTERMINALS a TERMINALS.
			Stack<CSyntaxTreeNode>			TreeNodes=new Stack<CSyntaxTreeNode>();

			TreeNodes.Push(new CSyntaxTreeNode(TerminalEOF,TerminalEOF.Name));

			CNonterminal					StartNonterminal=MNonterminalCollection.Nonterminals.First();
			CSyntaxTreeNode					RootNode=new CSyntaxTreeNode(StartNonterminal,StartNonterminal.Name);

			TreeNodes.Push(RootNode);

			CToken							NextToken=TokenQueue.Peek();
			CSyntaxTreeNode					NextNode=TreeNodes.Peek();

			while(true)
			{
				if ((NextNode.NodeSymbol is CTerminal_EOF)==true)
					break;

				if ((NextNode.NodeSymbol is CTerminal)==true)
				{
					CTerminal				Terminal=(CTerminal) NextNode.NodeSymbol;

					// TOKEN and TERMINAL are EQUAL.
					if (Terminal.ScanerTokenID==NextToken.TokenID)
					{
						NextNode.AddChild(new CSyntaxTreeNode(Terminal,NextToken.Lexema));

						if (NextToken.TokenID!=TerminalEOF.ScanerTokenID)
							TokenQueue.Dequeue();

						TreeNodes.Pop();
					}
					// ERROR - do POP operation.
					// !!! POP is BETTER then SCAN.
					else
					{
						if (NextToken.TokenID!=TerminalEOF.ScanerTokenID)
							TokenQueue.Dequeue();

						TreeNodes.Pop();
					}
				}
				else
				{
					CNonterminal			Nonterminal=(CNonterminal) NextNode.NodeSymbol;
					CTerminal				NextTerminal;

					if ((NextToken is CToken_Keyword)==true)
					{
						CToken_Keyword		KeywordToken=(CToken_Keyword) NextToken;

						NextTerminal=MTerminalCollection.FindTerminalByTerminalValue(KeywordToken.Lexema);
					}
					else
					{
						NextTerminal=MTerminalCollection.FindTerminalByScanerTokenID(NextToken.TokenID);
					}

					CChoice[]				Choices=ParsingTable[Nonterminal][NextTerminal];
					CChoice					Choice;

					if (Choices.Length==1)
					{
						Choice=Choices[0];
					}
					else
					{
						Choice=DisambiguationRuleDelegate(Choices,NextNode,NextToken,TokenQueue.ToArray(),Errors);
					}

					if ((Choice is CChoice_ErrorPOP)==true)
					{
						Errors.Add(string.Format("Unexpected TOKEN [{0}] for NONTERMINAL [{1}] ! Executing ERROR RECOVERY operation POP !",NextToken,Nonterminal));

						TreeNodes.Pop();
					}
					else if ((Choice is CChoice_ErrorSCAN)==true)
					{
						Errors.Add(string.Format("Unexpected TOKEN [{0}] for NONTERMINAL [{1}] ! Executing ERROR RECOVERY operation SCAN !",NextToken,Nonterminal));

						if (NextToken.TokenID!=TerminalEOF.ScanerTokenID)
							TokenQueue.Dequeue();
						else
							TreeNodes.Pop();
					}
					else
					{
						CSymbol[]			ChoiceSymbols=Choice.Symbols;
						CSymbol				ChoiceSymbol0=ChoiceSymbols[0];
						bool				IsEMPTYChoice=false;

						if ((ChoiceSymbol0 is CTerminal)==true)
						{
							CTerminal		TerminalToCheck=(CTerminal) ChoiceSymbol0;

							if (TerminalToCheck.Name==TerminalEMPTY.Name)
							{
								IsEMPTYChoice=true;
							}
						}

						TreeNodes.Pop();

						CSyntaxTreeNode[]		ChoiceNodes=new CSyntaxTreeNode[ChoiceSymbols.Length];

						for(int i=0;i<ChoiceSymbols.Length;i++)
						{
							CSymbol				ChoiceSymbol=ChoiceSymbols[i];

							if ((ChoiceSymbol is CNonterminal)==true)
							{
								ChoiceNodes[i]=new CSyntaxTreeNode(ChoiceSymbol,ChoiceSymbol.Name);
							}
							else
							{
								CTerminal		ChoiceTerminal=(CTerminal) ChoiceSymbol;

								ChoiceNodes[i]=new CSyntaxTreeNode(ChoiceSymbol,ChoiceTerminal.TerminalValue);
							}
						}

						NextNode.AddChildren(ChoiceNodes);

						if (IsEMPTYChoice==false)
						{
							CSyntaxTreeNode[]	ReverseChoiceNodes=ChoiceNodes.Reverse().ToArray();

							foreach(CSyntaxTreeNode Node in ReverseChoiceNodes)
							{
								TreeNodes.Push(Node);
							}
						}
					}
				}

				NextToken=TokenQueue.Peek();
				NextNode=TreeNodes.Peek();
			}

			if (TreeNodes.Count==0 || (NextNode.NodeSymbol is CTerminal_EOF)==false)
			{
				Errors.Add(string.Format("Program was NOT COMPLETELY parsed ! Error war found near SYMBOL [{0}] !",NextNode.NodeSymbol));
			}

			if (TokenQueue.Count==0 || NextToken.TokenID!=TerminalEOF.ScanerTokenID)
			{
				Errors.Add(string.Format("Program was NOT COMPLETELY parsed ! Error war found near TOKEN [{0}] !",NextToken));
			}

			return(RootNode);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------