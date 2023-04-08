using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
//-------------------------------------------------------------------------------------------------------
namespace LL1Parser
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static CChoice DisambiguationRuleHandler(CChoice[] Choices, CSyntaxTreeNode NextNode, CToken NextToken, CToken[] TokensToParse, CParserErrorList Errors)
		{
			CSymbol						Symbol=NextNode.NodeSymbol;

			if (Symbol.Name=="DECLARATION")
			{
				if (NextToken.Lexema=="void" || NextToken.Lexema=="int" || NextToken.Lexema=="string")
				{
					if (TokensToParse.Length>2)
					{
						CToken			Token=TokensToParse[2];

						if (Token.TokenID=="SEMICOLON")
						{
							CChoice		Choice=Choices[0];

							return(Choice);
						}
						else
						{
							CChoice		Choice=Choices[1];

							return(Choice);
						}
					}
					else
					{
						CChoice			Choice=Choices[0];

						Errors.Add(string.Format("DISAMBIGUATION RULE for SYMBOL [{0}] and TOKEN [{1}] has NOT ENOUGH TOKENS do determinate CORRECT CHOICE nad CHOICE [{2}] was selected AS DEFAULT !",Symbol,NextToken,Choice));
						return(Choice);
					}
				}
				else
				{
					throw(new InvalidOperationException(string.Format("DISAMBIGUATION RULE is NOT DEFINED for SYMBOL [{0}] and TOKEN [{1}] !",Symbol,NextToken)));
				}
			}
			else if (Symbol.Name=="PARAMS")
			{
				if (NextToken.Lexema=="void")
				{
					// Always return 'void' CHOICE.
					CChoice		Choice=Choices[1];

					return(Choice);
				}
				else
				{
					throw(new InvalidOperationException(string.Format("DISAMBIGUATION RULE is NOT DEFINED for SYMBOL [{0}] and TOKEN [{1}] !",Symbol,NextToken)));
				}
			}
			else if (Symbol.Name=="MOD_SELECTION_STATEMENT")
			{
				if (NextToken.Lexema=="else")
				{
					// Always return 'else STATEMENT' CHOICE.
					CChoice		Choice=Choices[0];

					return(Choice);
				}
				else
				{
					throw(new InvalidOperationException(string.Format("DISAMBIGUATION RULE is NOT DEFINED for SYMBOL [{0}] and TOKEN [{1}] !",Symbol,NextToken)));
				}
			}
			else if (Symbol.Name=="EXPRESSION")
			{
				if (NextToken.TokenID=="IDENTIFIER")
				{
					if (TokensToParse.Length>1)
					{
						CToken			Token=TokensToParse[1];

						// ASSIGMENT.
						if (Token.TokenID=="ASSIGMENT")
						{
							CChoice		Choice=Choices[0];

							return(Choice);
						}
						// SIMPLE EXPRESSION.
						else
						{
							CChoice		Choice=Choices[1];

							return(Choice);
						}
					}
					else
					{
						CChoice			Choice=Choices[0];

						Errors.Add(string.Format("DISAMBIGUATION RULE for SYMBOL [{0}] and TOKEN [{1}] has NOT ENOUGH TOKENS do determinate CORRECT CHOICE nad CHOICE [{2}] was selected AS DEFAULT !",Symbol,NextToken,Choice));
						return(Choice);
					}
				}
				else
				{
					throw(new InvalidOperationException(string.Format("DISAMBIGUATION RULE is NOT DEFINED for SYMBOL [{0}] and TOKEN [{1}] !",Symbol,NextToken)));
				}
			}
			else if (Symbol.Name=="FACTOR")
			{
				if (NextToken.TokenID=="IDENTIFIER")
				{
					if (TokensToParse.Length>1)
					{
						CToken			Token=TokensToParse[1];

						// VARIABLE.
						if (Token.TokenID!="ROUND BRACKET LEFT")
						{
							CChoice		Choice=Choices[0];

							return(Choice);
						}
						// FUNCTION CALL.
						else
						{
							CChoice		Choice=Choices[1];

							return(Choice);
						}
					}
					else
					{
						CChoice			Choice=Choices[0];

						Errors.Add(string.Format("DISAMBIGUATION RULE for SYMBOL [{0}] and TOKEN [{1}] has NOT ENOUGH TOKENS do determinate CORRECT CHOICE nad CHOICE [{2}] was selected AS DEFAULT !",Symbol,NextToken,Choice));
						return(Choice);
					}
				}
				else
				{
					throw(new InvalidOperationException(string.Format("DISAMBIGUATION RULE is NOT DEFINED for SYMBOL [{0}] and TOKEN [{1}] !",Symbol,NextToken)));
				}
			}
			else
			{
				throw(new InvalidOperationException(string.Format("DISAMBIGUATION RULE is NOT DEFINED for SYMBOL [{0}] !",Symbol)));
			}
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
		private static void SaveTextToFile(string FileName, string TextToWrite)
		{
			using(FileStream FS=new FileStream(FileName,FileMode.Create,FileAccess.Write))
			{
				using(StreamWriter SW=new StreamWriter(FS))
				{
					SW.Write(TextToWrite);
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private static CToken[] DoScan(string ScanerRulesFile, string SourceCodeFile, bool PrintLog)
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
		private static void DoParse(string ParserRulesFile, string SourceCodeFile, CToken[] Tokens, string OutputFile, bool PrintLog)
		{
			string								ParserXML=LoadTextFromFile(ParserRulesFile);
			CNonterminalCollection				NonterminalCollection;
			CTerminalCollection					TerminalCollection;

			CXMLParserDeserializer.DeserializeFromXML(ParserXML,out NonterminalCollection,out TerminalCollection);

			CParserEngine						Parser=new CParserEngine(NonterminalCollection,TerminalCollection);

			CFirstSetCollection					FirstSetCollection=Parser.CalculateFirstSets();
			CFollowSetCollection				FollowSetCollection=Parser.CalculateFollowSets();
			CParsingTable						ParsingTable=Parser.CalculateParsingTable();

			CToken[]							TokensNoComment=Tokens.Where(P => (P.TokenID!="WHITE CHARS" && P.TokenID!="COMMENT")).ToArray();
			CParserErrorList					Errors;

			CSyntaxTreeNode						RootNode=Parser.DoParse(TokensNoComment,DisambiguationRuleHandler,out Errors);
			string								TreeText=RootNode.WriteTree();

			SaveTextToFile(OutputFile,TreeText);

			if (PrintLog==true)
			{
				Console.WriteLine(TreeText);
			}

			if (Errors.HasErrors==false)
			{
				Console.WriteLine("PARSER SUCCESSFULLY COMPLETED !");
			}
			else
			{
				string							Error=Errors.GetErrorString();

				Console.WriteLine("PARSER FAILED !");
				Console.WriteLine(Error);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.BufferHeight=10000;

			string								ScanerRulesFile=@"..\..\!XML\Scaner.xml";
			string								ParserRulesFile=@"..\..\!XML\BNF.xml";

			//string							SourceCodeFile=@"..\..\!SourceCodes\C--Example1.txt";
			string								SourceCodeFile=@"..\..\!SourceCodes\C--Example2.txt";
			//string							SourceCodeFile=@"..\..\!SourceCodes\C--ExampleError1.txt";
			//string							SourceCodeFile=@"..\..\!SourceCodes\C--ExampleError2.txt";

			string								OutputFile=@"..\..\!Output\Output.txt";

			bool								PrintWhiteSpaceTokens=false;
			CToken[]							Tokens=DoScan(ScanerRulesFile,SourceCodeFile,PrintWhiteSpaceTokens);

			if (Tokens!=null)
			{
				DoParse(ParserRulesFile,SourceCodeFile,Tokens,OutputFile,true);
			}

			Console.WriteLine("\nPress any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------