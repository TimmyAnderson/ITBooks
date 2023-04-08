using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace Chars
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void Test1()
		{
			char												C='A';

			Console.WriteLine(string.Format("Char: [{0}] !",C));

			Console.WriteLine(string.Format("Char: [{0}] - Category: [{1}] !",C,Char.GetUnicodeCategory(C)));

			C='a';

			Console.WriteLine(string.Format("Char: [{0}] - Category: [{1}] !",C,Char.GetUnicodeCategory(C)));

			C='1';

			Console.WriteLine(string.Format("Char: [{0}] - Category: [{1}] !",C,Char.GetUnicodeCategory(C)));

			C='/';

			Console.WriteLine(string.Format("Char: [{0}] - Category: [{1}] !",C,Char.GetUnicodeCategory(C)));

			C='\'';

			Console.WriteLine(string.Format("Char: [{0}] - Category: [{1}] !",C,Char.GetUnicodeCategory(C)));

			C=' ';

			Console.WriteLine(string.Format("Char: [{0}] - Category: [{1}] !",C,Char.GetUnicodeCategory(C)));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test2()
		{
			// Velmi rychla konverzia.
			char												C1=(char) 65;

			Console.WriteLine(string.Format("C1 [{0}] !",C1));

			// Velmi rychla konverzia.
			int													C2=(int) C1;

			Console.WriteLine(string.Format("C2 [{0}] !",C2));

			// Pomalsia konverzia.
			char												C3=Convert.ToChar(65);

			Console.WriteLine(string.Format("C3 [{0}] !",C3));

			// Pomalsia konverzia.
			int													C4=Convert.ToInt32(C1);

			Console.WriteLine(string.Format("C4 [{0}] !",C4));

			// Najpomalsia konverzia.
			char												C5=((IConvertible) 65).ToChar(null);

			Console.WriteLine(string.Format("C5 [{0}] !",C5));

			// Najpomalsia konverzia.
			int													C6=((IConvertible) C1).ToInt32(null);

			Console.WriteLine(string.Format("C6 [{0}] !",C6));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			//Test1();
			Test2();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------