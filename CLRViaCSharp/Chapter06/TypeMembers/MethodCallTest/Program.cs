using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace MethodCallTest
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		// Tato metoda je urcena na prezeranie cez ILDASM.
		private static void Test1()
		{
			// STATICKE metody su volane cez 'CALL'.
			/*
				call											void MethodCallTest.CSomeClass::StaticMethod()
			*/
			CSomeClass.StaticMethod();
		}
//-------------------------------------------------------------------------------------------------------
		// Tato metoda je urcena na prezeranie cez ILDASM.
		private static void Test2()
		{
			CSomeClass											SC=new CSomeClass();

			// !!! NON-VIRTUAL metody su VOLANE cez 'CALLVIRT' a to PRETO, aby doslo ku kontrole, ci SC!=NULL.
			/*
				ldloc											SC
				callvirt										instance void MethodCallTest.CSomeClass::NonVirtualMethod()
			*/
			SC.NonVirtualMethod();
		}
//-------------------------------------------------------------------------------------------------------
		// Tato metoda je urcena na prezeranie cez ILDASM.
		private static void Test3()
		{
			CSomeClass											SC=new CSomeClass();

			// VIRTUAL metody su VOLANE cez 'CALLVIRT'.
			/*
				ldloc											SC
				callvirt										instance void MethodCallTest.CSomeClass::VirtualMethod()
			*/
			SC.VirtualMethod();
		}
//-------------------------------------------------------------------------------------------------------
		// Tato metoda je urcena na prezeranie cez ILDASM.
		private static void Test4()
		{
			CSomeClass											SC=new CSomeClass();

			// OVERRIDED metody su VOLANE cez 'CALLVIRT'.
			/*
				ldloc											SC
				callvirt										instance void MethodCallTest.CBaseClass::OverridedMethod()
			*/
			SC.OverridedMethod();
		}
//-------------------------------------------------------------------------------------------------------
		// Tato metoda je urcena na prezeranie cez ILDASM.
		private static void Test5()
		{
			CSomeClass											SC=new CSomeClass();

			// OVERRIDED SEALED metody su VOLANE cez 'CALLVIRT'.
			/*
				ldloc											SC
				callvirt										instance void MethodCallTest.CBaseClass::OverridedSealedMethod()
			*/
			SC.OverridedSealedMethod();
		}
//-------------------------------------------------------------------------------------------------------
		// Tato metoda je urcena na prezeranie cez ILDASM.
		private static void Test6()
		{
			int													Value=100;
			// !!! METHOD ToString() je VIRTUAL METHOD, no C# vola VIRTUAL METHODS VALUE TYPES pomocou INSTRUCTION [call].
			/*
				ldloca.s										Value
				call											instance string [mscorlib]System.Int32::ToString()
				stloc											StringValue
			*/
			string												StringValue=Value.ToString();

			Console.WriteLine(string.Format("VALUE [{0}] !",StringValue));
		}
//-------------------------------------------------------------------------------------------------------
		// Tato metoda je urcena na prezeranie cez ILDASM.
		private static void Test7()
		{
			int													Value=100;
			// !!! METHOD GetType() je NON-VIRTUAL METHOD. C# ju volna NEVIRTUALNE.
			/*
				ldloc											Value
				box												[mscorlib]System.Int32
				call											instance class [mscorlib]System.Type [mscorlib]System.Object::GetType()
				stloc											StringValue
			*/
			Type												StringValue=Value.GetType();

			Console.WriteLine(string.Format("VALUE [{0}] !",StringValue));
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