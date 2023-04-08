using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;
using System.Reflection.Emit;
//-------------------------------------------------------------------------------------------------------
namespace DynamicCodeGeneration
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		// Delegate pre dynamicky generovany kod.
        private delegate int Add(int A, int B);
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main()
		{
			// Definujem parametre novo generovanej metody Add().
            Type[]			Args={typeof(int), typeof(int)};
			// Deklarujem dynamicky generovanu metodu Add().
            DynamicMethod	Dyn=new DynamicMethod("Add", typeof(int), Args, typeof(Program), true);

			// Vytvorim telo metody.
            ILGenerator		Gen=Dyn.GetILGenerator();

            Gen.Emit(OpCodes.Ldarg_0);
            Gen.Emit(OpCodes.Ldarg_1);
            Gen.Emit(OpCodes.Add);
            Gen.Emit(OpCodes.Ret);

            Add				A=(Add) Dyn.CreateDelegate(typeof(Add));

            Console.WriteLine("Press any key to invoke Add() method !");
            Console.ReadKey();

			// Volam dynamicky generovanu metodu.
            int				Ret=A(1, 2);

            Console.WriteLine("1+2=[{0}] !", Ret);
			Console.WriteLine("Press any key to EXIT !");
			Console.ReadKey();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------