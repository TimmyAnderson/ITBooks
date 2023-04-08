using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace PrimitiveTypes
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void OverflowTest()
		{
			int													Int1=int.MaxValue;
			int													Int2=6;
			int													Result=Int1+Int2;

			Console.WriteLine(string.Format("RESULT: [{0}] !",Result));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private static void Test1()
		{
			int													InputValue1=1000;
			long												InputValue2=10000000000;

			// IMPLICIT CONVERSION.
			long												OutputValue1=InputValue1;
			// EXPLICIT CONVERSION. Dochadza ku STRATE HODNOTY.
			int													OutputValue2=(int) InputValue2;

			Console.WriteLine(string.Format("INPUT VALUE 1: [{0}] !",InputValue1));
			Console.WriteLine(string.Format("INPUT VALUE 2: [{0}] !",InputValue2));

			Console.WriteLine(string.Format("OUTPUT VALUE 1: [{0}] !",OutputValue1));
			Console.WriteLine(string.Format("OUTPUT VALUE 2: [{0}] !",OutputValue2));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test2()
		{
			Int32												InputValue1=1000;
			Int64												InputValue2=10000000000;

			// IMPLICIT CONVERSION.
			Int64												OutputValue1=InputValue1;
			// EXPLICIT CONVERSION. Dochadza ku STRATE HODNOTY.
			Int32												OutputValue2=(int) InputValue2;

			Console.WriteLine(string.Format("INPUT VALUE 1: [{0}] !",InputValue1));
			Console.WriteLine(string.Format("INPUT VALUE 2: [{0}] !",InputValue2));

			Console.WriteLine(string.Format("OUTPUT VALUE 1: [{0}] !",OutputValue1));
			Console.WriteLine(string.Format("OUTPUT VALUE 2: [{0}] !",OutputValue2));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test3()
		{
			byte												ByteValue1=20;
			byte												ByteValue2=40;

			// !!!!! Kedze BYTE ARITHMETIC OPERATIONS sa vykonavaju nad INT32, je nutne vykonat EXPLICIT CONVERSION na BYTE, inak COMPILER hodi ERROR.
			byte												ByteResult=(byte) (ByteValue1+ByteValue2);

			Console.WriteLine(string.Format("BYTE RESULT: [{0}] !",ByteResult));

			short												ShortValue1=20;
			short												ShortValue2=40;

			// !!!!! Kedze SHORT ARITHMETIC OPERATIONS sa vykonavaju nad INT32, je nutne vykonat EXPLICIT CONVERSION na SHORT, inak COMPILER hodi ERROR.
			short												ShortResult=(short) (ShortValue1+ShortValue2);

			Console.WriteLine(string.Format("SHORT RESULT: [{0}] !",ShortResult));

			int													IntValue1=20;
			int													IntValue2=40;

			// !!! Kedze INT ARITHMETIC OPERATIONS sa vykoavaju na INT32, NIE JE nutne vykonat EXPLICIT CONVERSION na INT.
			int													IntResult=IntValue1+IntValue2;

			Console.WriteLine(string.Format("INT RESULT: [{0}] !",IntResult));

			long												LongValue1=20;
			long												LongValue2=40;

			// !!! Kedze LONG ARITHMETIC OPERATIONS sa vykoavaju na INT64, NIE JE nutne vykonat EXPLICIT CONVERSION na LONG.
			long												LongResult=LongValue1+LongValue2;

			Console.WriteLine(string.Format("LONG RESULT: [{0}] !",LongResult));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test4()
		{
			byte												V1=10;
			byte												V2=20;

			// C# matematicke operacie VZDY konvertuju (podla typu operandov) na jednu z hodnot: 'int', 'long', alebo 'double'.
			// Konverzia na INT.
			object												Sum1=V1+V2;

			Console.WriteLine(string.Format("ADD BYTES - [{0}]+[{1}]=[{2}], type: [{3}] !",V1,V2,Sum1,Sum1.GetType()));

			byte												V3=10;
			long												V4=20;

			// C# matematicke operacie VZDY konvertuje (podla typu operandov) na jednu z hodnot: 'int', 'long', alebo 'double'.
			// Konverzia na LONG.
			object												Sum2=V3+V4;

			Console.WriteLine(string.Format("ADD BYTE and LONG - [{0}]+[{1}]=[{2}], type: [{3}] !",V3,V4,Sum2,Sum2.GetType()));

			float												V5=10;
			double												V6=20;

			// C# matematicke operacie VZDY konvertuje (podla typu operandov) na jednu z hodnot: 'int', 'long', alebo 'double'.
			// Konverzia na DOUBLE.
			object												Sum3=V5+V6;

			Console.WriteLine(string.Format("ADD FLOAT and DOUBLE - [{0}]+[{1}]=[{2}], type: [{3}] !",V5,V6,Sum3,Sum3.GetType()));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test5()
		{
			int													Int1=int.MaxValue;
			int													Int2=6;

			// OPERATOR [unchecked].
			int													Result1=unchecked(Int1+Int2);

			Console.WriteLine(string.Format("UNCHECKED: [{0}] !",Result1));

			try
			{
				// OPERATOR [checked].
				int												Result2=checked(Int1+Int2);

				Console.WriteLine(string.Format("CHECKED: [{0}] !",Result2));
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("CHECKED - EXCEPTION: [{0}] !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test6()
		{
			int													Int1=int.MaxValue;
			int													Int2=6;

			// STATEMENT [unchecked].
			unchecked
			{
				int												Result=Int1+Int2;

				Console.WriteLine(string.Format("UNCHECKED: [{0}] !",Result));
			}

			// STATEMENT [checked].
			checked
			{
				try
				{
					int											Result=Int1+Int2;

					Console.WriteLine(string.Format("CHECKED: [{0}] !",Result));
				}
				catch(Exception E)
				{
					Console.WriteLine(string.Format("CHECKED - EXCEPTION: [{0}] !",E.Message));
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test7()
		{
			checked
			{
				try
				{
					// !!!!! Aj ked METHOD vykona OVERFLOW, tak sa EXCEPTION NEGENERUJE, pretoze STATEMENT [checked] neovplyvnuje volane METHODS.
					OverflowTest();

					Console.WriteLine(string.Format("CODE PASSED !"));
				}
				catch(Exception E)
				{
					Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			//Test1();
			//Test2();
			//Test3();
			//Test4();
			//Test5();
			//Test6();
			Test7();

			Console.WriteLine("\nPress any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------