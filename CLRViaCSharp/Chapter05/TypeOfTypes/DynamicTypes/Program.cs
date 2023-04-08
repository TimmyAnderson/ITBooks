using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Runtime.CompilerServices;
//-------------------------------------------------------------------------------------------------------
namespace DynamicTypes
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		// !!! CLR NEUMOZNUJE pouzitie LAMBDA EXPRESSIONS za [dynamic] VARIABLES.
		private static void ExecuteCallback(dynamic LambdaExpression)
		{
			LambdaExpression(10);
		}
//-------------------------------------------------------------------------------------------------------
		private static void CallbackAction(int Value)
		{
			Console.WriteLine(string.Format("CALLBACK ACTION CALLED with VALUE [{0}] !",Value));
		}
//-------------------------------------------------------------------------------------------------------
		// !!! EVENT HANDLER pre DELEGATE s [dynamic] PARAMETER.
		private static void CallbackMethod(dynamic Parameter)
		{
			Console.WriteLine(string.Format("DYNAMIC METHOD - VALUE [{0}] !",Parameter));
		}
//-------------------------------------------------------------------------------------------------------
		// !!!!! Aj ked CLR umoznuje definovat DYNAMIC VARIABLES ako TYPE PARAMETERS pre GENERICS CLASSES a GENERIC METHODS, tak pre tieto TYPE PARAMETERS sa DYNAMIC BINDING NEROBI. Je to preto, lebo TYPE PARAMETERS musia mat definovane CONSTRAINS, ktore urcuju ake MEMBERS bude mozne pre dany TYPE PARAMETER volat. Preto aj C# pre GENERIC CLASSES a METHOD NEGENERUJE CODE, ktory by realizoval DYNAMIC BINDING.
		private static void GenericMethod<TType>(TType Parameter)
		{
			Console.WriteLine(string.Format("DYNAMIC METHOD - VALUE [{0}] !",Parameter));
		}
//-------------------------------------------------------------------------------------------------------
		private static void GenericMethod<TType>(TType Operand1, dynamic Operand2)
		{
			dynamic												Result=Operand1+Operand2;

			Console.WriteLine(string.Format("DYNAMIC METHOD - RESULT [{0}] !",Result));
		}
//-------------------------------------------------------------------------------------------------------
		private static dynamic MethodWithDymamicParamsAndReutrnValue(dynamic Operand1, dynamic Operand2)
		{
			// !!! Az v RUNTIME sa ZISTI, ci dana premenna obsahuje typ, ktory IMPLEMENTUJE 'operator+'.
			dynamic												Ret=Operand1+Operand2;

			return(Ret);
		}
//-------------------------------------------------------------------------------------------------------
		private static void NoReturn()
		{
			Console.WriteLine("NoReturn() CALLED !");
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private static void Test1()
		{
			/*
				ldstr											"Timmy"
				ldstr											"Anderson"
				ldc.i4.s										12
				newobj											instance void DynamicTypes.CName::.ctor(string,string,int32)
				stloc											Variable
			*/
			dynamic												Variable=new CName("Timmy","Anderson",12);

			/*
				// !!! C# prida co CLASS STATIC FIELD.
				ldsfld											class [System.Core]System.Runtime.CompilerServices.CallSite`1<class [mscorlib]System.Action`2<class [System.Core]System.Runtime.CompilerServices.CallSite,object>> DynamicTypes.Program/'<Test1>o__SiteContainer2'::'<>p__Site3'
				brtrue.s										END
				ldc.i4											0x100
				ldstr											"Print"
				ldnull
				ldtoken											DynamicTypes.Program
				call											class [mscorlib]System.Type [mscorlib]System.Type::GetTypeFromHandle(valuetype [mscorlib]System.RuntimeTypeHandle)
				ldc.i4.1
				newarr											[Microsoft.CSharp]Microsoft.CSharp.RuntimeBinder.CSharpArgumentInfo
				// !!! C# pridava do CODE LOCAL VARIABLE TYPE [class [Microsoft.CSharp]Microsoft.CSharp.RuntimeBinder.CSharpArgumentInfo[]].
				stloc											Temp
				// !!! C# pridava do CODE LOCAL VARIABLE TYPE [class [Microsoft.CSharp]Microsoft.CSharp.RuntimeBinder.CSharpArgumentInfo[]].
				ldloc											Temp
				ldc.i4.0
				ldc.i4.0
				ldnull
				call											class [Microsoft.CSharp]Microsoft.CSharp.RuntimeBinder.CSharpArgumentInfo [Microsoft.CSharp]Microsoft.CSharp.RuntimeBinder.CSharpArgumentInfo::Create(valuetype [Microsoft.CSharp]Microsoft.CSharp.RuntimeBinder.CSharpArgumentInfoFlags,string)
				stelem.ref
				// !!! C# pridava do CODE LOCAL VARIABLE TYPE [class [Microsoft.CSharp]Microsoft.CSharp.RuntimeBinder.CSharpArgumentInfo[]].
				ldloc											Temp
				call											class [System.Core]System.Runtime.CompilerServices.CallSiteBinder [Microsoft.CSharp]Microsoft.CSharp.RuntimeBinder.Binder::InvokeMember(valuetype [Microsoft.CSharp]Microsoft.CSharp.RuntimeBinder.CSharpBinderFlags,string,class [mscorlib]System.Collections.Generic.IEnumerable`1<class [mscorlib]System.Type>,class [mscorlib]System.Type,class [mscorlib]System.Collections.Generic.IEnumerable`1<class [Microsoft.CSharp]Microsoft.CSharp.RuntimeBinder.CSharpArgumentInfo>)
				call											class [System.Core]System.Runtime.CompilerServices.CallSite`1<!0> class [System.Core]System.Runtime.CompilerServices.CallSite`1<class [mscorlib]System.Action`2<class [System.Core]System.Runtime.CompilerServices.CallSite,object>>::Create(class [System.Core]System.Runtime.CompilerServices.CallSiteBinder)
				stsfld											class [System.Core]System.Runtime.CompilerServices.CallSite`1<class [mscorlib]System.Action`2<class [System.Core]System.Runtime.CompilerServices.CallSite,object>> DynamicTypes.Program/'<Test1>o__SiteContainer2'::'<>p__Site3'
				br.s											END
				END:
				ldsfld											class [System.Core]System.Runtime.CompilerServices.CallSite`1<class [mscorlib]System.Action`2<class [System.Core]System.Runtime.CompilerServices.CallSite,object>> DynamicTypes.Program/'<Test1>o__SiteContainer2'::'<>p__Site3'
				// !!! CLASS System.Runtime.CompilerServices.CallSite<T> ma PUBLIC FIELD Target.
				ldfld											!0 class [System.Core]System.Runtime.CompilerServices.CallSite`1<class [mscorlib]System.Action`2<class [System.Core]System.Runtime.CompilerServices.CallSite,object>>::Target
				ldsfld											class [System.Core]System.Runtime.CompilerServices.CallSite`1<class [mscorlib]System.Action`2<class [System.Core]System.Runtime.CompilerServices.CallSite,object>> DynamicTypes.Program/'<Test1>o__SiteContainer2'::'<>p__Site3'
				ldloc											Variable
				callvirt										instance void class [mscorlib]System.Action`2<class [System.Core]System.Runtime.CompilerServices.CallSite,object>::Invoke(!0,!1)
			*/
			Variable.Print();
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test2()
		{
			dynamic												Variable1=new CName("Timmy","Anderson",12);
			dynamic												Variable2=100;

			Console.WriteLine("-------------------------------------------------------------------------------");

			// ToString() je mozne volat, lebo KAZDY DYNAMIC je typu 'object'.
			Console.WriteLine(string.Format("Variable1: [{0}] !",Variable1.ToString()));
			Console.WriteLine(string.Format("Variable2: [{0}] !",Variable2.ToString()));

			Console.WriteLine("-------------------------------------------------------------------------------");

			try
			{
				// Kedze Variable1 obsahuje CName, tak nasledovne volanie BUDE FUNGOVAT.
				Variable1.Change("Jenny","Thompson",13);
				Console.WriteLine(string.Format("Variable1: [{0}] !",Variable1.ToString()));
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}

			Console.WriteLine("-------------------------------------------------------------------------------");

			try
			{
				// !!! Kedze Variable2 obsahuje 'int', tak nasledovne volanie HODI EXCEPTION.
				Variable2.Change("Jenny","Thompson",13);
				Console.WriteLine(string.Format("Variable2: [{0}] !",Variable2.ToString()));
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}

			Console.WriteLine("-------------------------------------------------------------------------------");

			try
			{
				// !!! Pri konvertovani DYNAMIC premennej NETREBA EXPLICITNE PRETYPOVANIE, lebo to sa vyhodnocuje az v RUNTIME.
				int												Temp1=Variable1;

				Console.WriteLine(string.Format("Temp1: [{0}] !",Temp1.ToString()));
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}

			Console.WriteLine("-------------------------------------------------------------------------------");

			try
			{
				// !!! Pri konvertovani DYNAMIC premennej NETREBA EXPLICITNE PRETYPOVANIE, lebo to sa vyhodnocuje az v RUNTIME.
				int												Temp2=Variable2;

				Console.WriteLine(string.Format("Temp2: [{0}] !",Temp2.ToString()));
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}

			Console.WriteLine("-------------------------------------------------------------------------------");
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test3()
		{
			dynamic[]											LeftOperands=new dynamic[]{10,"aaa",new CWrappedInt(33)};
			dynamic[]											RightOperands=new dynamic[]{5,"bbb",new CWrappedInt(44)};

			for(int Index=0;Index<LeftOperands.Length;Index++)
			{
				Console.WriteLine("-------------------------------------------------------------------------------");

				// Vola sa OPERATOR+ pre rozlicne TYPES, vratane CUSTOM TYPE s CUSTOM OPERATOR.
				dynamic											Result=LeftOperands[Index]+RightOperands[Index];

				Console.WriteLine(string.Format("[{0}]+[{1}]=[{2}] !",LeftOperands[Index],RightOperands[Index],Result));
			}

			Console.WriteLine("-------------------------------------------------------------------------------");
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test4()
		{
			Console.WriteLine("-------------------------------------------------------------------------------");

			try
			{
				dynamic											Param1=10;
				dynamic											Param2=6;

				Console.Write(string.Format("Param1: [{0}], Param2: [{1}]",Param1,Param2));

				dynamic											ReturnValue=MethodWithDymamicParamsAndReutrnValue(Param1,Param2);

				Console.WriteLine(string.Format(" - ReturnValue: [{0}] !",ReturnValue.ToString()));
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format(" - EXCEPTION: [{0}] !",E.Message));
			}

			Console.WriteLine("-------------------------------------------------------------------------------");

			try
			{
				dynamic											Param1=10.5;
				dynamic											Param2=6;

				Console.Write(string.Format("Param1: [{0}], Param2: [{1}]",Param1,Param2));

				dynamic											ReturnValue=MethodWithDymamicParamsAndReutrnValue(Param1,Param2);

				Console.WriteLine(string.Format(" - ReturnValue: [{0}] !",ReturnValue.ToString()));
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format(" - EXCEPTION: [{0}] !",E.Message));
			}

			Console.WriteLine("-------------------------------------------------------------------------------");

			try
			{
				dynamic											Param1=10;
				dynamic											Param2="AAA";

				Console.Write(string.Format("Param1: [{0}], Param2: [{1}]",Param1,Param2));

				dynamic											ReturnValue=MethodWithDymamicParamsAndReutrnValue(Param1,Param2);

				Console.WriteLine(string.Format(" - ReturnValue: [{0}] !",ReturnValue.ToString()));
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format(" - EXCEPTION: [{0}] !",E.Message));
			}

			Console.WriteLine("-------------------------------------------------------------------------------");

			try
			{
				dynamic											Param1=10;
				dynamic											Param2=new CName("Timmy","Anderson",12);

				Console.Write(string.Format("Param1: [{0}], Param2: [{1}]",Param1,Param2));

				// !!! Hodi EXCEPTION, pretoze OVERLOADED OPERATOR+ pre INT32 a CName NEEXISTUJE.
				dynamic											ReturnValue=MethodWithDymamicParamsAndReutrnValue(Param1,Param2);

				Console.WriteLine(string.Format(" - ReturnValue: [{0}] !",ReturnValue.ToString()));
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format(" - EXCEPTION: [{0}] !",E.Message));
			}

			Console.WriteLine("-------------------------------------------------------------------------------");
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test5()
		{
			dynamic[]											Values=new dynamic[]{10,4.6,"AAA",new CName("Timmy","Anderson",12)};

			// !!! C# konveruje VARIABLE pri enumerovani COLLECTION KEYWORD [dynamic] na TYPE IEnumerable.
			/*
				call											class [System.Core]System.Runtime.CompilerServices.CallSiteBinder [Microsoft.CSharp]Microsoft.CSharp.RuntimeBinder.Binder::InvokeMember(valuetype [Microsoft.CSharp]Microsoft.CSharp.RuntimeBinder.CSharpBinderFlags,string,class [mscorlib]System.Collections.Generic.IEnumerable`1<class [mscorlib]System.Type>,class [mscorlib]System.Type,class [mscorlib]System.Collections.Generic.IEnumerable`1<class [Microsoft.CSharp]Microsoft.CSharp.RuntimeBinder.CSharpArgumentInfo>)
			*/
			foreach(dynamic Value in Values)
			{
				Console.WriteLine("-------------------------------------------------------------------------------");

				Console.WriteLine(string.Format("VALUE [{0}] !",Value));
			}

			Console.WriteLine("-------------------------------------------------------------------------------");
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test6()
		{
			// !!! C# konveruje VARIABLE pri pouziti KEYWORD [using] na TYPE IDisposable.
			/*
				ldsfld											class [System.Core]System.Runtime.CompilerServices.CallSite`1<class [mscorlib]System.Func`3<class [System.Core]System.Runtime.CompilerServices.CallSite,object,class [mscorlib]System.IDisposable>> DynamicTypes.Program/'<Test6>o__SiteContainer39'::'<>p__Site3a'
			*/
			using(dynamic Variable=new CDisposable())
			{
				Variable.DoSomething();
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test7()
		{
			CGenericName<dynamic>								Name=new CGenericName<dynamic>("Timmy","Anderson",12);

			Console.WriteLine(string.Format("Name: [{0}] !",Name));
			
			try
			{
				// !!! Typ 'int' NA ROZDIEL od 'object' obsahuje metodu CompareTo(int).
				if (Name.Age.CompareTo(12)==0)
				{
					Console.WriteLine("SAME AGE !");
				}
				else
				{
					Console.WriteLine("DIFFERENT AGE !");
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test8()
		{
			GenericMethod<int>(10);

			GenericMethod<dynamic>(10);

			dynamic												Variable=10;

			GenericMethod<dynamic>(Variable);

			GenericMethod<int>(10,20);

			GenericMethod<string>("AAA","BBB");
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test9()
		{
			try
			{
				dynamic											Test=12;

				// Vola sa NEEXISTUJUCA METHOD.
				if (Test.ThisMethodDoesntExist()=='a')
				{
					Console.WriteLine("TRUE !");
				}
				else
				{
					Console.WriteLine("FALSE !");
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}

			try
			{
				dynamic											Test=12;

				// Vola sa EXISTUJUCU METHOD, ale BEZ PARAMETER.
				if (Test.CompareTo()==0)
				{
					Console.WriteLine("TRUE !");
				}
				else
				{
					Console.WriteLine("FALSE !");
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}

			try
			{
				dynamic											Test=12;

				// Vola sa EXISTUJUCA METHOD, ale s RETURN VALUE INT a NIE STRING.
				if (Test.CompareTo(10)=="ABC")
				{
					Console.WriteLine("TRUE !");
				}
				else
				{
					Console.WriteLine("FALSE !");
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test10()
		{
			CNameWithDynamicFields								NameWithDynamicFields=new CNameWithDynamicFields("Timmy","Anderson",12);

			Console.WriteLine("NameWithDynamicFields [{0}] !",NameWithDynamicFields);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test11()
		{
			DDynamicDelegate									Delegate=new DDynamicDelegate(CallbackMethod);
			dynamic												Parameter1="Timmy Anderson";
			dynamic												Parameter2=12;

			Delegate(Parameter1);
			Delegate(Parameter2);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test12()
		{
			try
			{
				Action<int>										Action=new Action<int>(CallbackAction);

				ExecuteCallback(Action);
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}

			try
			{
				// !!!!! COMPILER toto NEAKCEPTUJE, pretoze LAMBDA EXPRESSION NEMOZE byt pouzity ako [dynamic] PARAMETER.
				//ExecuteCallback(P => Console.WriteLine(string.Format("CALLBACK ACTION CALLED with VALUE [{0}] !",Value)));
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
		// !!! METHOD demonstruje implementaciu CUSTOM OBJECT BINDER pomocou CLASS DynamicMetaObject.
		// !!!!! Implementacia CUSTOM OBJECT BINDER je ZLOZITEJSIA ako pomocou CLASS DynamicObject, pretoze METHODS CLASS DynamicMetaObject MUSIA vracat EXPRESSIONS.
		private static void Test13()
		{
			Console.WriteLine("-------------------------------------------------------------------------------");

			try
			{
				// !!! CLASS CDynamicNameByDynamicMetaObject implementuje CUSTOM DYNAMIC BINDING.
				dynamic											Variable=new CDynamicNameByDynamicMetaObject("Timmy","Anderson",12);

				Console.WriteLine(string.Format("Variable - NAME [{0} {1}], AGE [{2}] !",Variable.FirstName,Variable.LastName,Variable.Age));
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}

			Console.WriteLine("-------------------------------------------------------------------------------");

			try
			{
				// !!! CLASS CDynamicNameByDynamicMetaObject implementuje CUSTOM DYNAMIC BINDING.
				dynamic											Variable=new CDynamicNameByDynamicMetaObject("Timmy","Anderson",12);

				// !!! Aj ked CDynamicNameByDynamicMetaObject NEOBSAHUJE FIELD MField, tak CUSTOM BINDER vracia CONSTANT VALUE 3.
				Variable.MField=100;

				// !!! Aj ked CDynamicNameByDynamicMetaObject NEOBSAHUJE FIELD MField, tak CUSTOM BINDER vracia CONSTANT VALUE 3.
				Console.WriteLine(string.Format("Variable: [{0}] !",Variable.MField));
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}

			Console.WriteLine("-------------------------------------------------------------------------------");

			try
			{
				// !!! CLASS CDynamicNameByDynamicMetaObject implementuje CUSTOM DYNAMIC BINDING.
				dynamic											Variable=new CDynamicNameByDynamicMetaObject("Timmy","Anderson",12);

				// !!! Aj ked CDynamicNameByDynamicMetaObject OBSAHUJE METHOD Print(), tak CUSTOM BINDER vrati EXPRESSION, ktora ju vyvola.
				Variable.Print();
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}

			Console.WriteLine("-------------------------------------------------------------------------------");

			try
			{
				// !!! CLASS CDynamicNameByDynamicMetaObject implementuje CUSTOM DYNAMIC BINDING.
				dynamic											Variable=new CDynamicNameByDynamicMetaObject("Timmy","Anderson",12);

				// !!! Aj ked CDynamicNameByDynamicMetaObject OBSAHUJE METHOD PrintWithParamsAndReturnValue(), tak CUSTOM BINDER vrati EXPRESSION, ktora ju vyvola.
				Console.WriteLine(string.Format("PrintWithParamsAndReturnValue() - RETURN VALUE: [{0}] !",Variable.PrintWithParamsAndReturnValue("HELLO")));
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}

			Console.WriteLine("-------------------------------------------------------------------------------");

			try
			{
				// !!! CLASS CDynamicNameByDynamicMetaObject implementuje CUSTOM DYNAMIC BINDING.
				dynamic											Variable=new CDynamicNameByDynamicMetaObject("Timmy","Anderson",12);

				// !!! Kedze CDynamicNameByDynamicMetaObject NEOBSAHUJE METHOD XXX(), tak CUSTOM BINDER vracia CONSTANT VALUE 3.
				Variable.XXX();
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}

			Console.WriteLine("-------------------------------------------------------------------------------");
		}
//-------------------------------------------------------------------------------------------------------
		// !!! METHOD demonstruje implementaciu CUSTOM OBJECT BINDER pomocou CLASS DynamicObject.
		// !!!!! Implementacia CUSTOM OBJECT BINDER je JEDNODUCHSIA ako pomocou CLASS DynamicMetaObject, pretoze METHODS CLASS DynamicMetaObject NEMUSIA vracat EXPRESSIONS, ale rovno vykonavaju pozadovane cinnosti.
		private static void Test14()
		{
			Console.WriteLine("-------------------------------------------------------------------------------");

			try
			{
				// !!! CLASS CDynamicNameByDynamicObject implementuje CUSTOM DYNAMIC BINDING.
				dynamic											Variable=new CDynamicNameByDynamicObject("Timmy","Anderson",12);

				// !!! CDynamicNameByDynamicObject OBSAHUJE pozadovane FIELDS a tak sa CUSTOM BINDER VOBEC NEVOLA.
				Console.WriteLine(string.Format("Variable - NAME [{0} {1}], AGE [{2}] !",Variable.FirstName,Variable.LastName,Variable.Age));
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}

			Console.WriteLine("-------------------------------------------------------------------------------");

			try
			{
				// !!! CLASS CDynamicNameByDynamicObject implementuje CUSTOM DYNAMIC BINDING.
				dynamic											Variable=new CDynamicNameByDynamicObject("Timmy","Anderson",12);

				// !!! Aj ked CDynamicNameByDynamicObject NEOBSAHUJE FIELD MField, tak CUSTOM BINDER vykona CUSTOM BINDING.
				Variable.MField=100;

				// !!! Aj ked CDynamicNameByDynamicObject NEOBSAHUJE FIELD MField, tak CUSTOM BINDER vykona CUSTOM BINDING.
				Console.WriteLine(string.Format("Variable: [{0}] !",Variable.MField));
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}

			Console.WriteLine("-------------------------------------------------------------------------------");

			try
			{
				// !!! CLASS CDynamicNameByDynamicObject implementuje CUSTOM DYNAMIC BINDING.
				dynamic											Variable=new CDynamicNameByDynamicObject("Timmy","Anderson",12);

				// !!! CDynamicNameByDynamicObject OBSAHUJE METHOD Print() a tak sa CUSTOM BINDER VOBEC NEVOLA.
				Variable.Print();
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}

			Console.WriteLine("-------------------------------------------------------------------------------");

			try
			{
				// !!! CLASS CDynamicNameByDynamicObject implementuje CUSTOM DYNAMIC BINDING.
				dynamic											Variable=new CDynamicNameByDynamicObject("Timmy","Anderson",12);

				// !!! CDynamicNameByDynamicObject OBSAHUJE METHOD PrintWithParamsAndReturnValue() a tak sa CUSTOM BINDER VOBEC NEVOLA.
				Console.WriteLine(string.Format("PrintWithParamsAndReturnValue() - RETURN VALUE: [{0}] !",Variable.PrintWithParamsAndReturnValue("HELLO")));
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}

			Console.WriteLine("-------------------------------------------------------------------------------");

			try
			{
				// !!! CLASS CDynamicNameByDynamicObject implementuje CUSTOM DYNAMIC BINDING.
				dynamic											Variable=new CDynamicNameByDynamicObject("Timmy","Anderson",12);

				// !!! Kedze CDynamicNameByDynamicObject NEOBSAHUJE METHOD XXX(), tak CUSTOM BINDER vykona CUSTOM BINDING a zavola METHOD SomeXXX().
				Variable.XXX();
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}

			Console.WriteLine("-------------------------------------------------------------------------------");
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
			//Test7();
			//Test8();
			//Test9();
			//Test10();
			//Test11();
			//Test12();
			//Test13();
			Test14();

			Console.WriteLine("\nPress any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------