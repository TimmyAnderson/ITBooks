using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace ExtensionMethods
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void Dummy()
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private static void Test1()
		{
			CClass												Value1=new CClass();

			Value1.EXT_Class();

			IInterface											Value2=new CClass();

			Value2.EXT_Interface();

			EEnum												Value3=new EEnum();

			Value3.EXT_Enum();

			SStruct												Value4=new SStruct();

			Value4.EXT_Struct();

			DDelegate											Value5=new DDelegate(Dummy);

			Value5.EXT_Delegate();
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test2()
		{
			object												Value1=new object();
			int													Value2=100;
			string												Value3="XXX";
			EEnum												Value4=EEnum.E_SOME_VALUE;
			CClass												Value5=new CClass();

			Value1.PrintObject();
			Value2.PrintObject();
			Value3.PrintObject();
			Value4.PrintObject();
			Value5.PrintObject();
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test3()
		{
			// !!! EXTENSION METHOD Object.PrintObject() sa priradi do DELEGATE.
			// !!!!! Tento DELEGATE sa vsak NEODKAZUJE na STATIC METHOD, ale je nastaveny tak, akoby EXTENSION METHOD Object.PrintObject() bola INSTANCE METHOD TYPE String ["Timmy Anderson"].
			Action												NewAction="Timmy Anderson".PrintObject;

			NewAction();

			Console.WriteLine(string.Format("DELEGATE TARGET [{0}] !",NewAction.Target));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			//Test1();
			//Test2();
			Test3();

			Console.WriteLine("\nPress any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------