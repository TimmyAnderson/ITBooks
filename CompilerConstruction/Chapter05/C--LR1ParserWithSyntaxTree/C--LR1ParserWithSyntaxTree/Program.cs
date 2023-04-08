using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
//-------------------------------------------------------------------------------------------------------
namespace C__LR1ParserWithSyntaxTree
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		public static CParsingTableCell CMinusMinusSolveShiftReduceConflict(CDFAState ConflictingDFAState, CTerminal ConflictingTerminal)
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
		public static CParsingTableCell CMinusMinusSolveReduceReduceConflict(CDFAState ConflictingDFAState, CTerminal ConflictingTerminal)
		{
			// !!! Gramatika by NEMALA obsahovat REDUCE-REDUCE CONFLICT. Ak obsahuje potom je to zvycajne CHYBA GRAMATIKY.
			throw(new InvalidOperationException("GRAMMAR SHOULD NOT CONTAIN REDUCE-REDUCE CONFLICT !"));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private static string LoadTextFromFile(string FileName)
		{
			using(FileStream FS=new FileStream(FileName,FileMode.Open,FileAccess.Read))
			{
				using(StreamReader SR=new StreamReader(FS))
				{
					string					Ret=SR.ReadToEnd();

					return(Ret);
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static CToken[] DoScan(string ScanerRulesFile, string SourceCodeFile, bool SkipWhiteCharsAndComments, bool PrintLog)
		{
			string								ScanerXML=LoadTextFromFile(ScanerRulesFile);
			CInputChar[]						InputChars;
			CState[]							States;

			CXMLScanerDeserializer.DeserializeFromXML(ScanerXML,out InputChars,out States);

			CScanerEngine						Scaner=new CScanerEngine(States);
			string								SourceCode=LoadTextFromFile(SourceCodeFile);
			CScanerErrorList					Errors=new CScanerErrorList();
			CToken[]							Tokens=Scaner.GetAllTokens(SourceCode,Errors);

			if (Tokens!=null)
			{
				if (SkipWhiteCharsAndComments==true)
				{
					Tokens=Tokens.Where(P => P.TokenID!="WHITE CHARS" && P.TokenID!="COMMENT").ToArray();
				}

				if (PrintLog==true)
				{
					foreach(CToken Token in Tokens)
					{
						// Skip WHITE CHARS.
						if (Token.TokenID=="WHITE CHARS")
							continue;

						Console.WriteLine(string.Format("TYPE: [{0}], TOKEN: [{1}] !",Token.TokenID,Token.Lexema));
					}
				}

				Console.WriteLine("SCANER SUCCESSFULLY COMPLETED !");
			}
			else
			{
				string							Error=Errors.GetErrorString();

				Console.WriteLine("SCANER FAILED !");
				Console.WriteLine(Error);
			}

			return(Tokens);
		}
//-------------------------------------------------------------------------------------------------------
		private static void DoParse(EParserType	ParserType, string ParserRulesFile, CToken[] SourceCodeTokens, bool PrintLog)
		{
			string								ParserXML=LoadTextFromFile(ParserRulesFile);
			CNonterminalCollection				NonterminalCollection;
			CTerminalCollection					TerminalCollection;

			CXMLParserDeserializer.DeserializeFromXML(ParserXML,out NonterminalCollection,out TerminalCollection);

			CParserEngine						Parser=new CParserEngine(NonterminalCollection,TerminalCollection,CMinusMinusSolveShiftReduceConflict,CMinusMinusSolveReduceReduceConflict);
			CParsingErrorCollection				ParsingErrorCollection=new CParsingErrorCollection();
			CParsingStackItem					RootParsingStackItem;

			if (Parser.DoParseLR1OrLALR(true,ParserType,SourceCodeTokens,out RootParsingStackItem,ParsingErrorCollection,true)==false)
			{
				if (PrintLog==true)
				{
					Console.WriteLine("PARSING FAILED !");
					Console.WriteLine();
					Console.WriteLine(ParsingErrorCollection.PrintAllErrors());
				}
			}
			else
			{
				if (PrintLog==true)
				{
					string						ParseTree=RootParsingStackItem.ParseTreeNode.PrintTree();

					Console.WriteLine();
					Console.WriteLine();
					Console.WriteLine();

					Console.WriteLine(ParseTree);

					Console.WriteLine();
					Console.WriteLine();
					Console.WriteLine();

					string						SyntaxTree=RootParsingStackItem.SyntaxTreeNode.PrintTree();

					Console.WriteLine();
					Console.WriteLine();
					Console.WriteLine();

					Console.WriteLine(SyntaxTree);

					Console.WriteLine();
					Console.WriteLine();
					Console.WriteLine();

					Console.WriteLine("PARSING SUCCESSFULLY FINISHED !");

					if (ParsingErrorCollection.HasErrors)
					{
						Console.WriteLine(ParsingErrorCollection.PrintAllErrors());
					}
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.BufferHeight=2000;

			// Tato NEMODIFIKOVANA GRAMATIKA C-- je NAJVHODNEJSIA pre pouzitie v PARSERI, kedze pri riesenie ELSE-DANGLING problem ma konfliktny DFA iba 1 DESTINATION DFA STATE, takze vyber vyber SHIFT RULE na riesenie SHIFT-REDUCE CONFLICT je JEDNOZNACNY.
			string								ScanerRulesFile=@"..\..\!XML\Scaner_C--.xml";
			string								ParserRulesFile=@"..\..\!XML\BNF_C--Unmodified.xml";
			string								SourceCodeFile=@"..\..\!SourceCodes\C--Example1.txt";

			/*
			// Tato NEMODIFIKOVANA GRAMATIKA C-- je NAJVHODNEJSIA pre pouzitie v PARSERI, kedze pri riesenie ELSE-DANGLING problem ma konfliktny DFA iba 1 DESTINATION DFA STATE, takze vyber vyber SHIFT RULE na riesenie SHIFT-REDUCE CONFLICT je JEDNOZNACNY.
			// !!! SOURCE CODE obsahuje CHYBU.
			string								ScanerRulesFile=@"..\..\!XML\Scaner_C--.xml";
			string								ParserRulesFile=@"..\..\!XML\BNF_C--Unmodified.xml";
			string								SourceCodeFile=@"..\..\!SourceCodes\C--ErrorExample1.txt";
			*/

			/*
			// Tato NEMODIFIKOVANA GRAMATIKA C-- je NAJVHODNEJSIA pre pouzitie v PARSERI, kedze pri riesenie ELSE-DANGLING problem ma konfliktny DFA iba 1 DESTINATION DFA STATE, takze vyber vyber SHIFT RULE na riesenie SHIFT-REDUCE CONFLICT je JEDNOZNACNY.
			// !!! SOURCE CODE obsahuje CHYBU.
			string								ScanerRulesFile=@"..\..\!XML\Scaner_C--.xml";
			string								ParserRulesFile=@"..\..\!XML\BNF_C--Unmodified.xml";
			string								SourceCodeFile=@"..\..\!SourceCodes\C--ErrorExample2.txt";
			*/

			bool								PrintToLog=true;
			CToken[]							SourceCodeTokens=DoScan(ScanerRulesFile,SourceCodeFile,true,PrintToLog);

			EParserType							ParserType=EParserType.E_PT_LR_1;

			try
			{
				if (SourceCodeTokens!=null)
				{
					DoParse(ParserType,ParserRulesFile,SourceCodeTokens,true);
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}

			Console.WriteLine("\nPress any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------