using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;
//-------------------------------------------------------------------------------------------------------
namespace NullableTypes
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void Test1()
		{
			Nullable<int>										Value1=10;
			Nullable<int>										Value2=null;
			int?												Value3=10;
			int?												Value4=null;

			Console.WriteLine(string.Format("Value1: [{0}] !",Value1));
			Console.WriteLine(string.Format("Value2: [{0}] !",Value2));
			Console.WriteLine(string.Format("Value3: [{0}] !",Value3));
			Console.WriteLine(string.Format("Value4: [{0}] !",Value4));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test2()
		{
			int													IntValue1=20;
			// Implicitna konverzia.
			int?												NullableValue1=IntValue1;

			Console.WriteLine(string.Format("NullableValue1: [{0}] !",NullableValue1));

			int?												NullableValue2=40;
			// Explicitna konverzia.
			int													IntValue2=(int) NullableValue2;

			Console.WriteLine(string.Format("IntValue2: [{0}] !",IntValue2));

			try
			{
				int?											NullableValue3=null;
				// Explicitna konverzia - hodi EXCEPTION.
				int												IntValue3=(int) NullableValue3;

				Console.WriteLine(string.Format("IntValue3: [{0}] !",IntValue3));
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test3()
		{
			int													Value1=10;
			int?												NullableValue1=10;

			Console.WriteLine(string.Format("Value1==NullableValue1 - [{0}] !",(Value1==NullableValue1)));

			int													Value2=10;
			int?												NullableValue2=null;

			Console.WriteLine(string.Format("Value2==NullableValue2 - [{0}] !",(Value2==NullableValue2)));
			Console.WriteLine(string.Format("Value2<NullableValue2 - [{0}] !",(Value2<NullableValue2)));

			Console.WriteLine();

			SValueType											SValue=new SValueType(10);
			SValueType?											NullableSValue1=new SValueType(10);
			SValueType?											NullableSValue2=null;

			// Aplikuje sa CUSTOM OPERATOR.
			Console.WriteLine(string.Format("SValue==SNullableValue1 - [{0}] !",(SValue==NullableSValue1)));
			// !!! NEAPLIKUJE sa CUSTOM OPERATOR, lebo jeden z operandov je NULL.
			Console.WriteLine(string.Format("SValue==SNullableValue2 - [{0}] !",(SValue==NullableSValue2)));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test4()
		{
			int?												IValue1=10;
			int?												IValue2=null;
			string												SValue1="Timmy";
			string												SValue2=null;

			Console.WriteLine(string.Format("IValue1 ?? 99 - [{0}] !",(IValue1 ?? 99)));
			Console.WriteLine(string.Format("IValue2 ?? 99 - [{0}] !",(IValue2 ?? 99)));
			Console.WriteLine(string.Format("SValue1 ?? \"XYZ\" - [{0}] !",(SValue1 ?? "XYZ")));
			Console.WriteLine(string.Format("SValue2 ?? \"XYZ\" - [{0}] !",(SValue2 ?? "XYZ")));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test5()
		{
			int?												Value1=10;
			int?												Value2=null;

			object												Object1=Value1;
			// !!! Kedze Value2==NULL, tak aj Object2==NULL a BOXING sa NEVYOKNA.
			object												Object2=Value2;

			if (Object1!=null)
			{
				Console.WriteLine(string.Format("Object1 [{0}] in NOT NULL !",Object1));
			}
			else
			{
				Console.WriteLine(string.Format("Object1 [{0}] is NULL !",Object1));
			}

			if (Object2!=null)
			{
				Console.WriteLine(string.Format("Object2 [{0}] in NOT NULL !",Object2));
			}
			else
			{
				Console.WriteLine(string.Format("Object2 [{0}] is NULL !",Object2));
			}

			object												Object3=10;
			object												Object4=null;

			int?												Value3=(int?) Object3;
			// !!! Kedze Object4==NULL, tak aj Value4==NULL a UNBOXING sa NEVYOKNA.
			int?												Value4=(int?) Object4;

			if (Value3!=null)
			{
				Console.WriteLine(string.Format("Value3 [{0}] in NOT NULL !",Value3));
			}
			else
			{
				Console.WriteLine(string.Format("Value3 [{0}] is NULL !",Value3));
			}

			if (Value4!=null)
			{
				Console.WriteLine(string.Format("Value4 [{0}] in NOT NULL !",Value4));
			}
			else
			{
				Console.WriteLine(string.Format("Value4 [{0}] is NULL !",Value4));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test6()
		{
			int													IValue1=10;
			int?												IValue2=10;

			Console.WriteLine(string.Format("IValue1.GetType() - [{0}] !",IValue1.GetType()));
			
			// !!! Vracia Int32 a NIE Nullable<Int32>.
			Console.WriteLine(string.Format("IValue2.GetType() - [{0}] !",IValue2.GetType()));

			try
			{
				int?											IValue3=null;

				Console.WriteLine(string.Format("IValue3.GetType() - [{0}] !",IValue3.GetType()));
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test7()
		{
			SValueType?											Value1=new SValueType(10);
			SValueType											Value2=new SValueType(15);
			SValueType											Value3=new SValueType(10);

			// !!! Konverzia je MOZNA aj ked Nullable<T> NEIMPLEMENTUJE IComparable<SValueType>. CLR vsak STACI, aby IComparable<SValueType> implementoval SValueType.
			IComparable<SValueType>								Comparable=Value1;

			Console.WriteLine(string.Format("Comparable.Compare(Value2) - [{0}] !",Comparable.CompareTo(Value2)));
			Console.WriteLine(string.Format("Comparable.Compare(Value3) - [{0}] !",Comparable.CompareTo(Value3)));
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