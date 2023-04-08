using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
//-------------------------------------------------------------------------------------------------------
namespace ExpressionsRecursiveDescentScaner
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
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
		private static CToken[] DoScan(string ScanerRulesFile, string SourceCodeFile, bool PrintWhiteSpaceTokens)
		{
			string								XML=LoadTextFromFile(ScanerRulesFile);
			CInputChar[]						InputChars;
			CState[]							States;

			CXMLDeserializer.DeserializeFromXML(XML,out InputChars,out States);

			CScaner								Scaner=new CScaner(States);

			string								SourceCode=LoadTextFromFile(SourceCodeFile);

			try
			{
				CToken[]						Tokens=Scaner.GetAllTokens(SourceCode);

				foreach(CToken Token in Tokens)
				{
					if (Token.TokenID=="WHITE CHARS" && PrintWhiteSpaceTokens==false)
						continue;

					Console.WriteLine(string.Format("TYPE: [{0}], TOKEN: [{1}] !",Token.TokenID,Token.Lexema));
				}

				return(Tokens);
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
				return(null);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			string								ScanerRulesFile=@"..\..\!XML\Expressions.xml";

			string								SourceCodeFile=@"..\..\!SourceCodes\ExpressionExample1.txt";
			//string							SourceCodeFile=@"..\..\!SourceCodes\ExpressionExample2.txt";
			//string							SourceCodeFile=@"..\..\!SourceCodes\ExpressionExample3.txt";
			//string							SourceCodeFile=@"..\..\!SourceCodes\ExpressionExample4.txt";

			bool								PrintWhiteSpaceTokens=false;
			CToken[]							Tokens=DoScan(ScanerRulesFile,SourceCodeFile,PrintWhiteSpaceTokens);
			CParser								Parser=new CParser(Tokens);

			Parser.DoParse();

			Console.WriteLine("\nPress any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------