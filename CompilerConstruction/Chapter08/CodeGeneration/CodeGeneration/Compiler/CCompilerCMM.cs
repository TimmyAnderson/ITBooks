using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace CodeGeneration
{
//-------------------------------------------------------------------------------------------------------
	// Kompilator C--.
	public sealed class CCompilerCMM
	{
//-------------------------------------------------------------------------------------------------------
		private readonly EParserType							MParserType;
		private readonly CNonterminalCollection					MNonterminalCollection;
		private readonly CTerminalCollection					MTerminalCollection;
		private readonly CScanerEngine							MScaner;
		private readonly CParserEngine							MParser;
		private readonly CSemanticAnalyzer						MSemanticAnalyzer;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CCompilerCMM(string ScanerDefinition, string ParserDefinition, EParserType ParserType)
		{
			MParserType=ParserType;
			
			CInputChar[]						InputChars;
			CState[]							States;

			CXMLScanerDeserializer.DeserializeFromXML(ScanerDefinition,out InputChars,out States);

			MScaner=new CScanerEngine(States,true);

			CXMLParserDeserializer.DeserializeFromXML(ParserDefinition,out MNonterminalCollection,out MTerminalCollection);

			MParser=new CParserEngine(MNonterminalCollection,MTerminalCollection,CMinusMinusSolveShiftReduceConflict,CMinusMinusSolveReduceReduceConflict);

			MSemanticAnalyzer=new CSemanticAnalyzer();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private CParsingTableCell CMinusMinusSolveShiftReduceConflict(CDFAState ConflictingDFAState, CTerminal ConflictingTerminal)
		{
			if (ConflictingTerminal.ScanerTokenID=="KEYWORD" && ConflictingTerminal.TerminalValue=="else")
			{
				// Uprednostnim SHIFT pred REDUCE RULE.
				// !!! Toto riesenie ELSE-DANGLING problem sposobi, ze ELSE bude priradene NAJBLIZSIEMU IF.
				foreach(CNFAState NFAState in ConflictingDFAState.NFAStates)
				{
					CSymbol									SymbolAfterPeriod=NFAState.Item.GetSymbolAfterPeriod();

					if ((SymbolAfterPeriod is CTerminal)==true)
					{
						CTerminal							TypedSymbolAfterPeriod=(CTerminal) SymbolAfterPeriod;

						if (NFAState.Item.Terminal.Equals(ConflictingTerminal)==true)
						{
							// Cisto stochasticky vyberiem ako DESTINATION STATE DFA STATE s VACSIM POCTOM NFA STATES.
							CDFAState						DestinationState=null;

							foreach(CDFATransition Transition in ConflictingDFAState.Transitions)
							{
								if (DestinationState==null || DestinationState.NFAStates.Length<Transition.DestinationState.NFAStates.Length)
								{
									DestinationState=Transition.DestinationState;
								}
							}

							CParsingTableOperation_Shift	Operation=new CParsingTableOperation_Shift(DestinationState);
							CParsingTableCell				Cell=new CParsingTableCell(ConflictingTerminal,Operation);

							return(Cell);
						}
					}
				}
			}

			throw(new InvalidOperationException("UNSOLVED SHIFT-REDUCE CONFLICT !"));
		}
//-------------------------------------------------------------------------------------------------------
		private CParsingTableCell CMinusMinusSolveReduceReduceConflict(CDFAState ConflictingDFAState, CTerminal ConflictingTerminal)
		{
			// !!! Gramatika by NEMALA obsahovat REDUCE-REDUCE CONFLICT. Ak obsahuje potom je to zvycajne CHYBA GRAMATIKY.
			throw(new InvalidOperationException("GRAMMAR SHOULD NOT CONTAIN REDUCE-REDUCE CONFLICT !"));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public bool Compile(CSourceCode SourceCode, CInstructionCollection Instructions, CCompilerErrorCollection Errors, out string Log)
		{
			Errors.Clear();

			StringBuilder										FullLog=new StringBuilder();

			try
			{
				CTokenCollection								TokenCollection=new CTokenCollection();

				if (MScaner.Scan(SourceCode,TokenCollection,Errors)==true)
				{
					FullLog.AppendLine("".PadLeft(79,'-'));
					FullLog.AppendLine("".PadLeft(79,'-'));
					FullLog.AppendLine("".PadLeft(79,'-'));
					FullLog.AppendLine("SCANER");
					FullLog.AppendLine("".PadLeft(79,'-'));
					FullLog.AppendLine("".PadLeft(79,'-'));
					FullLog.AppendLine("".PadLeft(79,'-'));
					FullLog.Append(MScaner.Log);
					FullLog.AppendLine("".PadLeft(79,'-'));
					FullLog.AppendLine("".PadLeft(79,'-'));
					FullLog.AppendLine("".PadLeft(79,'-'));

					CParsingStackItem							RootParsingStackItem;

					if (MParser.Parse(MParserType,TokenCollection,out RootParsingStackItem,Errors,true)==true)
					{
						FullLog.AppendLine("".PadLeft(79,'-'));
						FullLog.AppendLine("".PadLeft(79,'-'));
						FullLog.AppendLine("".PadLeft(79,'-'));
						FullLog.AppendLine("PARSER");
						FullLog.AppendLine("".PadLeft(79,'-'));
						FullLog.AppendLine("".PadLeft(79,'-'));
						FullLog.AppendLine("".PadLeft(79,'-'));
						FullLog.Append(MParser.Log);
						FullLog.AppendLine("".PadLeft(79,'-'));
						FullLog.AppendLine("".PadLeft(79,'-'));
						FullLog.AppendLine("".PadLeft(79,'-'));

						CSymbolTable							RootSymbolTable;
						CStringLiterals							StringLiterals;
						CSymbolTableData_Variable[]				GlobalVariables;

						if (MSemanticAnalyzer.Analyze(MNonterminalCollection,RootParsingStackItem.ParseTreeNode,out RootSymbolTable,out StringLiterals,out GlobalVariables,Errors)==true)
						{
							FullLog.AppendLine("".PadLeft(79,'-'));
							FullLog.AppendLine("".PadLeft(79,'-'));
							FullLog.AppendLine("".PadLeft(79,'-'));
							FullLog.AppendLine("SEMANTIC ANALYZER");
							FullLog.AppendLine("".PadLeft(79,'-'));
							FullLog.AppendLine("".PadLeft(79,'-'));
							FullLog.AppendLine("".PadLeft(79,'-'));
							FullLog.Append(MSemanticAnalyzer.Log);
							FullLog.AppendLine("".PadLeft(79,'-'));
							FullLog.AppendLine("".PadLeft(79,'-'));
							FullLog.AppendLine("".PadLeft(79,'-'));

							CCodeGenerator						CodeGenerator=new CCodeGenerator(RootSymbolTable,StringLiterals,GlobalVariables);

							CodeGenerator.GenerateCode(MNonterminalCollection,RootParsingStackItem.ParseTreeNode,Instructions);

							FullLog.AppendLine("".PadLeft(79,'-'));
							FullLog.AppendLine("".PadLeft(79,'-'));
							FullLog.AppendLine("".PadLeft(79,'-'));
							FullLog.AppendLine("CODE GENERATOR");
							FullLog.AppendLine("".PadLeft(79,'-'));
							FullLog.AppendLine("".PadLeft(79,'-'));
							FullLog.AppendLine("".PadLeft(79,'-'));
							FullLog.Append(CodeGenerator.Log);
							FullLog.AppendLine("".PadLeft(79,'-'));
							FullLog.AppendLine("".PadLeft(79,'-'));
							FullLog.AppendLine("".PadLeft(79,'-'));
						}
					}
				}
			}
			catch(Exception E)
			{
				string											ErrorDescription=string.Format("EXCEPTION: [{0}] !",E.Message);

				FullLog.AppendLine(ErrorDescription);
				Errors.AddError(new CCompilerError(ErrorDescription));
			}

			Log=FullLog.ToString();

			if (Errors.HasErrors==true)
			{
				return(false);
			}
			else
			{
				return(true);
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------