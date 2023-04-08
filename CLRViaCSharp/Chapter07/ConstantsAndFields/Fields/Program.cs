using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;
//-------------------------------------------------------------------------------------------------------
namespace Fields
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static readonly int								MSomeNumber=100;
//-------------------------------------------------------------------------------------------------------
		private string											MInstanceField;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private static void Test1()
		{
			Program												P=new Program();

			P.MInstanceField="Timmy Anderson";

			Console.WriteLine(string.Format("MInstanceField [{0}] !",P.MInstanceField));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test2()
		{
			// !!! Pri referovani na FIELD sa uklada referencia na FIELD a NIE EXTRAHOVANA hodnota ako pri KONSTANTACH.
			int													Value=MSomeNumber;

			Console.WriteLine(string.Format("READ-ONLY FIELD [{0}] !",Value));

			Type												T=typeof(Program);
			FieldInfo											FI=T.GetField("MSomeNumber",BindingFlags.NonPublic | BindingFlags.Static);

			// !!! Pomocou REFLECION je mozne zmenit hodnotu READONLY FIELD.
			FI.SetValue(null,33);

			Value=MSomeNumber;

			Console.WriteLine(string.Format("READ-ONLY FIELD after CHANGE by REFLECTION [{0}] !",Value));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			//Test1();
			Test2();

			Console.WriteLine("\nPress any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------