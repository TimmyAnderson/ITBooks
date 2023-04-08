using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;
//-------------------------------------------------------------------------------------------------------
namespace Delegates
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void ParameterRefHandler(ref string Param)
		{
			Param="Jenny Thompson";
		}
//-------------------------------------------------------------------------------------------------------
		private static void ParameterOutHandler(out string Param)
		{
			Param="Jenny Thompson";
		}
//-------------------------------------------------------------------------------------------------------
		private static void ParameterParamsHandler(params object[] Params)
		{
			foreach(object Param in Params)
			{
				Console.WriteLine(string.Format("PARAM [{0}] !",Param));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void PrintText(string Param)
		{
			Console.WriteLine(string.Format("PARAM [{0}] !",Param));
		}
//-------------------------------------------------------------------------------------------------------
		// Demonstruje COVARIANCE a CONTRAVARIANCE.
		private static object ToUpper1(string Param)
		{
			string												ReturnValue=Param.ToString().ToUpper();

			Console.WriteLine(string.Format("Conversion: [{0}] -> [{1}] !",Param,ReturnValue));

			return(ReturnValue);
		}
//-------------------------------------------------------------------------------------------------------
		// Demonstruje COVARIANCE a CONTRAVARIANCE.
		private static string ToUpper2(object Param)
		{
			string												ReturnValue=Param.ToString().ToUpper();

			Console.WriteLine(string.Format("Conversion: [{0}] -> [{1}] !",Param,ReturnValue));

			return(ReturnValue);
		}
//-------------------------------------------------------------------------------------------------------
		private static string ToUpper3(string Param)
		{
			string												ReturnValue=Param.ToString().ToUpper();

			Console.WriteLine(string.Format("Conversion: [{0}] -> [{1}] !",Param,ReturnValue));

			return(ReturnValue);
		}
//-------------------------------------------------------------------------------------------------------
		// NON-STATIC METHOD.
		private string ToUpper4(string Param)
		{
			string												ReturnValue=Param.ToString().ToUpper();

			Console.WriteLine(string.Format("Conversion: [{0}] -> [{1}] !",Param,ReturnValue));

			return(ReturnValue);
		}
//-------------------------------------------------------------------------------------------------------
		// Demonstruje GENERIC CALLBACK.
		private static void GenericCallback<TType>(TType Param)
		{
			Console.WriteLine(string.Format("GenericCallback(): [{0}] -> [{1}] !",Param.GetType(),Param));
		}
//-------------------------------------------------------------------------------------------------------
		// Algoritmus robi SUM nad BASE TYPE.
		public static CDerivedResult Sum_VarianceBase(CBaseParameter[] Parameter)
		{
			int													Ret=Parameter.Sum(P => P.Number);

			return(new CDerivedResult(Ret));
		}
//-------------------------------------------------------------------------------------------------------
		// Algoritmus robi SUM nad DERIVED TYPE.
		public static CBaseResult Sum_VarianceDerived(CDerivedParameter[] Parameter)
		{
			int													Ret=Parameter.Sum(P => P.Number);

			return(new CBaseResult(Ret));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private static void Test1()
		{
			DToUpper											Delegate=new DToUpper(ToUpper1);

			// Volam DELEGATE.
			object												ReturnValue=Delegate("Timmy");

			Console.WriteLine(string.Format("CALLBACK RESULT: [{0}] !",ReturnValue));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test2()
		{
			CSimpleClass										SC=new CSimpleClass();

			// Registrujem DELEGATE na NON-STATIC metodu.
			DToUpperTyped										Delegate1=new DToUpperTyped(SC.NonStaticToUpperTyped);

			string												ReturnValue1=Delegate1("Timmy");

			Console.WriteLine(string.Format("CALLBACK RESULT - ReturnValue1: [{0}] !",ReturnValue1));

			// Registrujem DELEGATE na STATIC metodu.
			DToUpperTyped										Delegate2=new DToUpperTyped(CSimpleClass.StaticToUpperTyped);

			string												ReturnValue2=Delegate2("Timmy");

			Console.WriteLine(string.Format("CALLBACK RESULT - ReturnValue2: [{0}] !",ReturnValue2));

			Console.WriteLine();

			Console.WriteLine(string.Format("Delegate1 - Target: [{0}], Method: [{1}] !",Delegate1.Target,Delegate1.Method));
			Console.WriteLine(string.Format("Delegate2 - Target: [{0}], Method: [{1}] !",Delegate2.Target,Delegate2.Method));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test3()
		{
			// !!! DELEGATE DToUpper ma RETURN VALUE TYPE [Object] a PARAMETER TYPE [String].
			// !!!!! METHOD ToUpper2() vsak ma RETURN VALUE TYPE [String] a PARAMETER TYPE [Object].
			DToUpper											Delegate=new DToUpper(ToUpper2);

			// Volam DELEGATE.
			// !!!!! CLR umoznuje COVARIANCE - substituciu DELEGATE RETURN VALUE TYPE [Object] za CALLBACK METHOD RETURN VALUE TYPE [String], pretoze ak CALLBACK METHOD vracia TYPE [String], tak tento TYPE je validne mozne priradit do VARIABLE 'ReturnValue', ktora je TYPE [Object].
			// !!!!! CLR umoznuje CONTRAVARIANCE - substituciu DELEGATE PARAMETER TYPE [String] za CALLBACK METHOD PARAMETER TYPE [Object], pretoze ak CALLBACK METHOD akceptuje PARAEMTER TYPE [Object], tak urcite bude akceptovat aj hodnotu 'Timmy', ktora je TYPE [String].
			object												ReturnValue=Delegate("Timmy");

			Console.WriteLine(string.Format("CALLBACK RESULT: [{0}] !",ReturnValue));
		}
//-------------------------------------------------------------------------------------------------------
		// Demonstruje GENERIC COVARIANCE a CONTRAVARIANCE.
		private static void Test4()
		{
			CBaseParameter[]									BaseParameters=new CBaseParameter[]{new CBaseParameter(1),new CBaseParameter(2),new CBaseParameter(3)};
			CDerivedParameter[]									DerivedParameters=new CDerivedParameter[]{new CDerivedParameter(1),new CDerivedParameter(2),new CDerivedParameter(3)};

			DSum_CovarianceAndContravariance<CBaseParameter,CDerivedResult>	Delegate1=new DSum_CovarianceAndContravariance<CBaseParameter,CDerivedResult>(Sum_VarianceBase);

			CDerivedResult										DR1=Delegate1(BaseParameters);

			Console.WriteLine(string.Format("DR1: [{0}] !",DR1.Number));

			DSum_CovarianceAndContravariance<CDerivedParameter,CBaseResult>	Delegate2=new DSum_CovarianceAndContravariance<CDerivedParameter,CBaseResult>(Sum_VarianceDerived);

			CBaseResult											BR1=Delegate2(DerivedParameters);

			Console.WriteLine(string.Format("BR2: [{0}] !",BR1.Number));

			// !!!!! Kedze sa pouziva COVARIANCE a CONTRAVARIANCE prebehna IMPLICITNA KONVERZIA.
			// !!!!! Konverzia PREBEHNE, lebo algoritmus pracujuci s CBaseParameters URCITE BUDE VEDIET PRACOVAT i s DERIVED OBJEKTAMI CDerivedParameter, kedze CDerivedParameter obsahuje TIE ISTE MEMBER ako CBaseParameters (ktore alogritmus pracujuci nad CBaseParameters potreboval) plus vlastne MEMBERS, ktore vsak alogritmus pracujuci nad CBaseParameters NEPOUZIVA.
			DSum_CovarianceAndContravariance<CDerivedParameter,CBaseResult>	Delegate3=Delegate1;

			CBaseResult											BR2=Delegate3(DerivedParameters);

			Console.WriteLine(string.Format("BR2: [{0}] !",BR2.Number));

			try
			{
				// !!!!! Kedze sa pouziva COVARIANCE a CONTRAVARIANCE je mozna EXPLICITNA KONVERZIA. IMPLICITNA KONVERZIA vsak NIE JE MOZNA.
				// !!!!! Aj ked C# COMPILER EXPLICITNU KONVERZIU UMOZNI, CODE hodi v RUNTIME EXCEPTION.
				DSum_CovarianceAndContravariance<CBaseParameter,CDerivedResult>	Delegate4=(DSum_CovarianceAndContravariance<CBaseParameter,CDerivedResult>) Delegate2;

				CDerivedResult									DR2=Delegate4(BaseParameters);

				Console.WriteLine(string.Format("DR2: [{0}] !",DR2.Number));
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION [{0}] !",E));
			}

			/*
			// !!!!! Hodi COMPILER ERROR, pretoze IMPLICITNA KONVERZIA [DSum_CovarianceAndContravariance<CDerivedParameter,CBaseResult>] na [DSum_CovarianceAndContravariance<CBaseParameter,CDerivedResult>] NIE JE MOZNA.
			DSum_CovarianceAndContravariance<CBaseParameter,CDerivedResult>	Delegate4=Delegate2;

			// !!!!! Ak by vyssie uvedenu IMPLICITNU KONVERZIU umoznoval, potom by to znamenalo, ze PARAMETER 'BaseParameters' typu CBaseParameter by mohol byt zaslany do DELEGATE Delegate2, ktory ocakava ako PARAMETER TYPE CDerivedParameter.
			// !!!!! Ak by vyssie uvedenu IMPLICITNU KONVERZIU umoznoval, tiez by to znamenalo, ze RETURN VALUE typu CBaseResult by mohla byt priradena do VARIABLE 'DR2' typu CDerivedParameter CDerivedResult.
			// !!!!! Kedze C# NIKDY NEUMOZNUJE, aby BASE TYPE bol priradeny bez EXPLICITNEJ KONVERZIE do BASE TYPE, C# IMPLICITNU KONVERZIU 'Delegate2' na 'Delegate4' NEUMOZNI.
			CDerivedResult										DR3=Delegate4(BaseParameters);

			Console.WriteLine(string.Format("DR3: [{0}] !",DR3.Number));
			*/
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test5()
		{
			// NESTED DELEGATE.
			CNestedDelegate.DNestedDelegate						Delegate=new CNestedDelegate.DNestedDelegate(PrintText);

			Delegate("Timmy Anderson");
		}
//-------------------------------------------------------------------------------------------------------
		// !!! METHOD demonstruje pridavanie DELEGATES do DELEGATE CHAIN, odstranovanie DELEGATES z DELEGATE CHAIN, vracanie RETURN VALUES pri DELEGATE CHAINING a CUSTOM iteraciu zaregistrovanych DELEGATES v DELEGATE CHAINING.
		private static void Test6()
		{
			Console.WriteLine("-------------------------------------------------------------------------------");

			CSimpleClass										SC1=new CSimpleClass(10);
			CSimpleClass										SC2=new CSimpleClass(20);
			CSimpleClass										SC3=new CSimpleClass(30);

			DReturnSomething									RS1=new DReturnSomething(SC1.ReturnSomething);
			DReturnSomething									RS2=new DReturnSomething(SC2.ReturnSomething);
			DReturnSomething									RS3=new DReturnSomething(SC3.ReturnSomething);

			DReturnSomething									Chain=null;

			// Vykonam CHAINING.
			Chain=(DReturnSomething) Delegate.Combine(Chain,RS1);
			Chain=(DReturnSomething) Delegate.Combine(Chain,RS2);
			Chain=(DReturnSomething) Delegate.Combine(Chain,RS3);

			// Vykonam celu CHAIN DELEGATES - cez STANDARDNY algoritmus.
			// !!! Navratova hodnota sa PREPISUJE a ja ziskam navratovu hodnotu IBA z POSLEDNEHO VOLANIA.
			int													ReturnValue1=Chain();

			Console.WriteLine(string.Format("CHAINING - STANDARD ALGORITHM - RETURN VALUE: [{0}] !",ReturnValue1));

			Console.WriteLine("-------------------------------------------------------------------------------");

			// Ziskam KOLEKCIU VSETKYCH DELEGATES v CHAIN.
			Delegate[]											ChainCollection=Chain.GetInvocationList();

			// Vykonam CUSTOM algoritmus nad CHAINED DELEGATES.
			for(int Index=0;Index<ChainCollection.Length;Index++)
			{
				DReturnSomething								ReturnDelegate=(DReturnSomething) ChainCollection[Index];

				// Volam jeden z DELEGATES v CHAIN.
				int												ReturnValueLocal=ReturnDelegate();

				Console.WriteLine(string.Format("CHAINING - CUSTOM ALGORITHM - ITEM: [{0}] - RETURN VALUE: [{1}] !",(Index+1),ReturnValueLocal));
			}

			Console.WriteLine("-------------------------------------------------------------------------------");

			// Odstanim jeden z DELEGATES z CHAIN.
			Chain=(DReturnSomething) Delegate.Remove(Chain,RS2);

			int													ReturnValue2=Chain();

			Console.WriteLine(string.Format("CHAINING - STANDARD ALGORITHM - RETURN VALUE: [{0}] !",ReturnValue2));
	
			Console.WriteLine("-------------------------------------------------------------------------------");
		}
//-------------------------------------------------------------------------------------------------------
		// !!! METHOD demonstruje pridavanie DELEGATES do DELEGATE CHAIN, odstranovanie DELEGATES z DELEGATE CHAIN, vracanie RETURN VALUES pri DELEGATE CHAINING a CUSTOM iteraciu zaregistrovanych DELEGATES v DELEGATE CHAINING.
		private static void Test7()
		{
			Console.WriteLine("-------------------------------------------------------------------------------");

			CSimpleClass										SC1=new CSimpleClass(10);
			CSimpleClass										SC2=new CSimpleClass(20);
			CSimpleClass										SC3=new CSimpleClass(30);

			DReturnSomething									RS1=new DReturnSomething(SC1.ReturnSomething);
			DReturnSomething									RS2=new DReturnSomething(SC2.ReturnSomething);
			DReturnSomething									RS3=new DReturnSomething(SC3.ReturnSomething);

			DReturnSomething									Chain=null;

			// Vykonam CHAINING.
			Chain+=RS1;
			Chain+=RS2;
			Chain+=RS3;

			// Vykonam celu CHAIN DELEGATES - cez STANDARDNY algoritmus.
			// !!! Navratova hodnota sa PREPISUJE a ja ziskam navratovu hodnotu IBA z POSLEDNEHO VOLANIA.
			int													ReturnValue1=Chain();

			Console.WriteLine(string.Format("CHAINING - STANDARD ALGORITHM - RETURN VALUE: [{0}] !",ReturnValue1));

			Console.WriteLine("-------------------------------------------------------------------------------");

			// Ziskam KOLEKCIU VSETKYCH DELEGATES v CHAIN.
			Delegate[]											ChainCollection=Chain.GetInvocationList();

			// Vykonam CUSTOM algoritmus nad CHAINED DELEGATES.
			for(int Index=0;Index<ChainCollection.Length;Index++)
			{
				DReturnSomething								ReturnDelegate=(DReturnSomething) ChainCollection[Index];

				// Volam jeden z DELEGATES v CHAIN.
				int												ReturnValueLocal=ReturnDelegate();

				Console.WriteLine(string.Format("CHAINING - CUSTOM ALGORITHM - ITEM: [{0}] - RETURN VALUE: [{1}] !",(Index+1),ReturnValueLocal));
			}

			Console.WriteLine("-------------------------------------------------------------------------------");

			// Odstanim jeden z DELEGATES z CHAIN.
			Chain-=RS2;

			int													ReturnValue2=Chain();

			Console.WriteLine(string.Format("CHAINING - STANDARD ALGORITHM - RETURN VALUE: [{0}] !",ReturnValue2));
	
			Console.WriteLine("-------------------------------------------------------------------------------");
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test8()
		{
			Action<string>										A1=new Action<string>(GenericCallback<string>);
			Action<int>											A2=new Action<int>(GenericCallback<int>);

			A1("Timmy");
			A2(12);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test9()
		{
			Console.WriteLine("-------------------------------------------------------------------------------");

			DParameterRef										Delegate1=new DParameterRef(ParameterRefHandler);
			string												ParamRef="Timmy Anderson";
			
			Console.WriteLine(string.Format("BEFORE - ParamRef [{0}] !",ParamRef));

			Delegate1(ref ParamRef);

			Console.WriteLine(string.Format("AFTER - ParamRef [{0}] !",ParamRef));

			Console.WriteLine("-------------------------------------------------------------------------------");

			DParameterOut										Delegate2=new DParameterOut(ParameterOutHandler);
			string												ParamOut;

			Delegate2(out ParamOut);

			Console.WriteLine(string.Format("ParamOut [{0}] !",ParamOut));

			Console.WriteLine("-------------------------------------------------------------------------------");

			DParameterParams									Delegate3=new DParameterParams(ParameterParamsHandler);

			Delegate3("Timmy","Atreyu","Jenny");

			Console.WriteLine("-------------------------------------------------------------------------------");
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test10()
		{
			Program												P=new Program();

			// C# AUTOMATICKY vytvori DELEGATE pre CALLBACK METHOD ToUpper3().
			DToUpperTyped										ToUpper1=ToUpper3;
			// C# AUTOMATICKY vytvori DELEGATE pre CALLBACK INSTANCE METHOD ToUpper4().
			DToUpperTyped										ToUpper2=P.ToUpper4;

			string												ReturnValue1=ToUpper1("Timmy Anderson");
			string												ReturnValue2=ToUpper2("Timmy Anderson");

			Console.WriteLine(string.Format("ReturnValue1: [{0}] !",ReturnValue1));
			Console.WriteLine(string.Format("ReturnValue2: [{0}] !",ReturnValue2));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test11()
		{
			CSimpleClass										SC=new CSimpleClass(12);

			SC.ExecuteLambdaExpressions();
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test12()
		{
			Console.WriteLine("-------------------------------------------------------------------------------");

			// DELEGATE obsahuje REF parameter a preto i v LAMBDA EXRESSION ho musi definovat ako [ref] PARAMETER.
			DToUpperRef											Delegate1=new DToUpperRef((ref string P) => P=P.ToUpper());
			string												Param="Timmy Anderson";

			Console.WriteLine(string.Format("BEFORE - Param1: [{0}] !",Param));

			Delegate1(ref Param);

			Console.WriteLine(string.Format("AFTER - Param1: [{0}] !",Param));

			Console.WriteLine("-------------------------------------------------------------------------------");

			// DELEGATE obsahuje OUT parameter a preto i v LAMBDA EXRESSION ho musi definovat ako [out] PARAMETER.
			DParameterOut										Delegate2=new DParameterOut((out string Parameter) => Parameter="Jenny Thompson");
			string												Param2;

			Delegate2(out Param2);

			Console.WriteLine(string.Format("AFTER - Param2: [{0}] !",Param2));

			Console.WriteLine("-------------------------------------------------------------------------------");
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test13()
		{
			CSimpleClass										SC=new CSimpleClass(12);

			SC.ExecuteLambdaExpressionsWithLocals();
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test14()
		{
			DToUpperTyped										Delegate=new DToUpperTyped((string P) => 
			{
				Console.WriteLine("Code exectued INSIDE LAMBDA EXPRESSION !");

				// Musi sa pouzit KEYWORD [return].
				return(P.ToUpper());
			});

			string												ReturnValue=Delegate("Timmy Anderson");

			Console.WriteLine(string.Format("ReturnValue: [{0}] !",ReturnValue));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test15()
		{
			Console.WriteLine("-------------------------------------------------------------------------------");

			CSimpleClass										SC=new CSimpleClass();

			// Ziska sa MethodInfo z CALLBACK METHOD, ktoru chcem vlozit do DELEGATE.
			MethodInfo											MI1=SC.GetType().GetMethod("NonStaticToUpperTyped",BindingFlags.Instance | BindingFlags.Public);
			MethodInfo											MI2=SC.GetType().GetMethod("StaticToUpperTyped",BindingFlags.Static | BindingFlags.Public);
			MethodInfo											MI3=SC.GetType().GetMethod("NonStaticWithoutReturnValue",BindingFlags.Instance | BindingFlags.Public);

			// !!! DYNAMICKY sa vytvori DELEGATE na NON-STATIC METHOD.
			Delegate											DynamicDelegate1=Delegate.CreateDelegate(typeof(DToUpperTyped),SC,MI1);

			// !!! DYNAMICKY sa vytvori DELEGATE na STATIC METHOD.
			Delegate											DynamicDelegate2=Delegate.CreateDelegate(typeof(DToUpperTyped),MI2);

			// !!! DYNAMICKY sa vytvori DELEGATE na NON-STATIC METHOD, ktora nema RETURN VALUE.
			Delegate											DynamicDelegate3=Delegate.CreateDelegate(typeof(DNoReturn),SC,MI3);

			// Dynamicky volam CALLBACK NON-STATIC METODU.
			string												ReturnValue1=(string) DynamicDelegate1.DynamicInvoke("Timmy Anderson");

			Console.WriteLine(string.Format("ReturnValue1: [{0}] !",ReturnValue1));

			Console.WriteLine("-------------------------------------------------------------------------------");

			// Dynamicky volam CALLBACK STATIC METODU.
			string												ReturnValue2=(string) DynamicDelegate2.DynamicInvoke("Jenny Thompson");

			Console.WriteLine(string.Format("ReturnValue2: [{0}] !",ReturnValue2));

			Console.WriteLine("-------------------------------------------------------------------------------");

			// Dynamicky volam CALLBACK NON-STATIC METODU, ktora NEMA RETURN VALUE.
			object												ReturnValue3=DynamicDelegate3.DynamicInvoke("Timmy Anderson");

			Console.WriteLine(string.Format("ReturnValue3: [{0}] !",ReturnValue3));

			Console.WriteLine("-------------------------------------------------------------------------------");

			try
			{
				// !!! Umyselne dam zle parametre.
				string											ReturnValue4=(string) DynamicDelegate2.DynamicInvoke("Jenny Thompson",13);

				Console.WriteLine(string.Format("ReturnValue4: [{0}] !",ReturnValue4));
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
			//Test15();

			Console.WriteLine("\nPress any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------