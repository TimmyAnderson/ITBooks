using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
//-------------------------------------------------------------------------------------------------------
namespace Optimizations
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
					string										Ret=SR.ReadToEnd();

					return(Ret);
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void SaveTextToFile(string FileName, string Text)
		{
			using(FileStream FS=new FileStream(FileName,FileMode.Create,FileAccess.Write))
			{
				using(StreamWriter SW=new StreamWriter(FS))
				{
					SW.Write(Text);
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.BufferHeight=30000;

			string												ScanerRulesFile=@"..\..\!C--Definitions\Scaner_C--.xml";
			string												ParserRulesFile=@"..\..\!C--Definitions\Parser_C--.xml";
			string												SourceCodeFile=@"..\..\!SourceCodes\C--Example.txt";
			string												ASMOutputFile=@"..\..\!OUT\Program.asm";

			try
			{
				string											ScanerDefinition=LoadTextFromFile(ScanerRulesFile);
				string											ParserDefinition=LoadTextFromFile(ParserRulesFile);
				CSourceCode										SourceCode=new CSourceCode(LoadTextFromFile(SourceCodeFile));

				CCompilerCMM									Compiler=new CCompilerCMM(ScanerDefinition,ParserDefinition,EParserType.E_PT_LALR_1);
				CCompilerErrorCollection						Errors=new CCompilerErrorCollection();
				CInstructionCollection							Instructions=new CInstructionCollection();
				string											Log;

				if (Compiler.Compile(SourceCode,Instructions,Errors,out Log)==false)
				{
					Console.WriteLine("COMPILATION FAILED !");
					Console.WriteLine();
					Console.WriteLine();
					Console.WriteLine();

					Console.Write(Log);

					Console.WriteLine();
					Console.WriteLine();
					Console.WriteLine();
					Console.WriteLine("ERRORS:");
					Console.WriteLine();
					Console.WriteLine();
					Console.WriteLine();

					string										ErrorsString=Errors.GetAllErrors(SourceCode);

					Console.WriteLine(ErrorsString);
				}
				else
				{
					Console.WriteLine("COMPILATION SUCCEEDED !");
					Console.WriteLine();
					Console.WriteLine();
					Console.WriteLine();

					Console.Write(Log);

					Console.WriteLine();
					Console.WriteLine();
					Console.WriteLine();
					Console.WriteLine("INSTRUCTIONS:");
					Console.WriteLine();
					Console.WriteLine();
					Console.WriteLine();

					string										InstructionsString=Instructions.GetInstructionsString(true);

					Console.WriteLine(InstructionsString);

					SaveTextToFile(ASMOutputFile,InstructionsString);
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