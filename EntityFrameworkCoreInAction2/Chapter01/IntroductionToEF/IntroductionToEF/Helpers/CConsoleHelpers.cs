using System;
//----------------------------------------------------------------------------------------------------------------------
namespace Helpers
{
//----------------------------------------------------------------------------------------------------------------------
	public static class CConsoleHelpers
	{
//----------------------------------------------------------------------------------------------------------------------
		public static void WriteLineSeparator()
		{
			string												Text="".PadRight(Console.WindowWidth-1,'-');

			Console.WriteLine(Text);
		}
//----------------------------------------------------------------------------------------------------------------------
		public static void WriteLineSeparators(int NumberOfSeparators)
		{
			for(int Index=0;Index<NumberOfSeparators;Index++)
			{
				WriteLineSeparator();
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public static void WriteLine(string Text)
		{
			Console.WriteLine(Text);
		}
//----------------------------------------------------------------------------------------------------------------------
		public static void Write(string Text, ConsoleColor ForegroundColor, ConsoleColor BackgroundColor=ConsoleColor.Black)
		{
			ConsoleColor										OriginalForegroundColor=Console.ForegroundColor;
			ConsoleColor										OriginalBackgroundColor=Console.BackgroundColor;

			Console.ForegroundColor=ForegroundColor;
			Console.BackgroundColor=BackgroundColor;

			Console.Write(Text);

			Console.ForegroundColor=OriginalForegroundColor;
			Console.BackgroundColor=OriginalBackgroundColor;
		}
//----------------------------------------------------------------------------------------------------------------------
		public static void WriteLine(string Text, ConsoleColor ForegroundColor, ConsoleColor BackgroundColor=ConsoleColor.Black)
		{
			ConsoleColor										OriginalForegroundColor=Console.ForegroundColor;
			ConsoleColor										OriginalBackgroundColor=Console.BackgroundColor;

			Console.ForegroundColor=ForegroundColor;
			Console.BackgroundColor=BackgroundColor;

			Console.WriteLine(Text);

			Console.ForegroundColor=OriginalForegroundColor;
			Console.BackgroundColor=OriginalBackgroundColor;
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------