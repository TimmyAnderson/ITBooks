using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
//-------------------------------------------------------------------------------------------------------
namespace Scaner
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
		private static void DoScan(string ScanerRulesFile, string SourceCodeFile, bool PrintWhiteSpaceTokens)
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
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			//string							ScanerRulesFile=@"..\..\!XML\SimpleLanguage.xml";
			string								ScanerRulesFile=@"..\..\!XML\C--.xml";

			//string							SourceCodeFile=@"..\..\!SourceCodes\SimpleLanguage.txt";
			//string							SourceCodeFile=@"..\..\!SourceCodes\C--Example1.txt";
			string								SourceCodeFile=@"..\..\!SourceCodes\C--Example2.txt";

			bool								PrintWhiteSpaceTokens=false;

			DoScan(ScanerRulesFile,SourceCodeFile,PrintWhiteSpaceTokens);

			Console.WriteLine("\nPress any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------