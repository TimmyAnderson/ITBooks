using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace Delegates
{
//-------------------------------------------------------------------------------------------------------
	public class CSimpleClass
	{
//-------------------------------------------------------------------------------------------------------
		private int												MID;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSimpleClass()
		{
		}
//-------------------------------------------------------------------------------------------------------
		public CSimpleClass(int ID)
		{
			MID=ID;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public static string StaticToUpperTyped(string Param)
		{
			string												ReturnValue=Param.ToString().ToUpper();

			Console.WriteLine(string.Format("CSimpleClass.StaticToUpperTyped(): [{0}] -> [{1}] !",Param,ReturnValue));

			return(ReturnValue);
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public string NonStaticToUpperTyped(string Param)
		{
			string												ReturnValue=Param.ToString().ToUpper();

			Console.WriteLine(string.Format("CSimpleClass.NonStaticToUpperTyped(): [{0}] -> [{1}] !",Param,ReturnValue));

			return(ReturnValue);
		}
//-------------------------------------------------------------------------------------------------------
		public void NonStaticWithoutReturnValue(string Param)
		{
			Console.WriteLine(string.Format("CSimpleClass.NonStaticWithoutReturnValue(): [{0}] !",Param));
		}
//-------------------------------------------------------------------------------------------------------
		public int ReturnSomething()
		{
			Console.WriteLine(string.Format("CSimpleClass.ReturnSomething(): [{0}] !",MID));

			return(MID);
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// !!! Na prezretie aky kod vygeneroval C# z LAMBDA EXPRESSION je treba pouzit [ILDASM.EXE].
		public void ExecuteLambdaExpressions()
		{
			// NON-STATIC LAMBDA EXPRESSION.
			// !!! Pre KAZDU NON-STATIC LAMBDA EXPRESSION COMPILER prida do CLASS STATIC FIELD, ktory sluzi ako CACHE na ulozenie DELEGATE, ktory LAMBDA EXPRESSION reprezentuje.
			/*
				.field private static class Delegates.DToUpperTyped 'CS$<>9__CachedAnonymousMethodDelegate2'
				.custom instance void [mscorlib]System.Runtime.CompilerServices.CompilerGeneratedAttribute::.ctor() = ( 01 00 00 00 ) 
			*/
			DToUpperTyped										Delegate1=new DToUpperTyped(P => string.Format("{0} {1}",P,MID.ToString()).ToUpper());
			string												ReturnValue1=Delegate1("Timmy Anderson");

			Console.WriteLine(string.Format("ReturnValue1: [{0}] !",ReturnValue1));

			// STATIC LAMBDA EXPRESSION.
			DToUpperTyped										Delegate2=new DToUpperTyped(P => P.ToUpper());
			string												ReturnValue2=Delegate2("Timmy Anderson");

			Console.WriteLine(string.Format("ReturnValue2: [{0}] !",ReturnValue2));
		}
//-------------------------------------------------------------------------------------------------------
		// !!! Na prezretie aky kod vygeneroval C# z LAMBDA EXPRESSION je treba pouzit [ILDASM.EXE].
		public void ExecuteLambdaExpressionsWithLocals()
		{
			string												Prefix="Hello";

			// NON-STATIC LAMBDA EXPRESSION, ktora pouziva LOKALNU PREMENNU sa nazyva CLOSURE.
			// !!!!! Pre NON-STATIC LAMBDA EXPRESSION, ktory pouziva LOCAL VARIABLES COMPILER generuje PPRIVATE CLASS.
			/*
				.class auto ansi sealed nested private beforefieldinit '<>c__DisplayClass4' extends [mscorlib]System.Object
				{
					.custom instance void [mscorlib]System.Runtime.CompilerServices.CompilerGeneratedAttribute::.ctor() = ( 01 00 00 00 ) 

					.field public class Delegates.CSimpleClass	'<>4__this'
					.field public string						Prefix

					.method public hidebysig specialname rtspecialname instance void  .ctor() cil managed
					{
						.maxstack  8
						ldarg.0
						call									instance void [mscorlib]System.Object::.ctor()
						ret
					}

					.method public hidebysig instance string '<ExecuteLambdaExpressionsWithLocals>b__3'(string P) cil managed
					{
						.maxstack  4
						.locals init ([0] string CS$1$0000)

						IL_0000:  ldstr							"{0} {1} {2}"
						IL_0005:  ldarg.0
						IL_0006:  ldfld							string Delegates.CSimpleClass/'<>c__DisplayClass4'::Prefix
						IL_000b:  ldarg.1
						IL_000c:  ldarg.0
						IL_000d:  ldfld							class Delegates.CSimpleClass Delegates.CSimpleClass/'<>c__DisplayClass4'::'<>4__this'
						IL_0012:  ldflda						int32 Delegates.CSimpleClass::MID
						IL_0017:  call							instance string [mscorlib]System.Int32::ToString()
						IL_001c:  call							string [mscorlib]System.String::Format(string,object,object,object)
						IL_0021:  callvirt						instance string [mscorlib]System.String::ToUpper()
						IL_0026:  stloc.0
						IL_0027:  br.s							IL_0029
						IL_0029:  ldloc.0

						IL_002a:  ret
					}
				}
			*/
			DToUpperTyped										Delegate=new DToUpperTyped(P => string.Format("{0} {1} {2}",Prefix,P,MID.ToString()).ToUpper());

			string												ReturnValue=Delegate("Timmy Anderson");

			Console.WriteLine(string.Format("ReturnValue: [{0}] !",ReturnValue));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------