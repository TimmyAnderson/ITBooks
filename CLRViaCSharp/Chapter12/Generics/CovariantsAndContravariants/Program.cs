using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace CovariantsAndContravariants
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
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
		public static void PrintEventArgs(EventArgs Parameter)
		{
			Console.WriteLine(string.Format("PrintEventArgs() - Type: [{0}] !",Parameter));
		}
//-------------------------------------------------------------------------------------------------------
		public static void PrintCMyEventArgs(CMyEventArgs Parameter)
		{
			Console.WriteLine(string.Format("PrintCMyEventArgs() - Type: [{0}] !",Parameter));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// !!! NEPOUZIVA sa COVARIANCE a CONTRAVARIANCE.
		private static void Test1()
		{
			CBaseParameter[]									BaseParameters=new CBaseParameter[]{new CBaseParameter(1),new CBaseParameter(2),new CBaseParameter(3)};
			CDerivedParameter[]									DerivedParameters=new CDerivedParameter[]{new CDerivedParameter(1),new CDerivedParameter(2),new CDerivedParameter(3)};

			DSum_Invariance<CBaseParameter,CDerivedResult>		Delegate1=new DSum_Invariance<CBaseParameter,CDerivedResult>(Sum_VarianceBase);

			CDerivedResult										DR1=Delegate1(BaseParameters);

			Console.WriteLine(string.Format("DR1: [{0}] !",DR1.Number));

			DSum_Invariance<CDerivedParameter,CBaseResult>		Delegate2=new DSum_Invariance<CDerivedParameter,CBaseResult>(Sum_VarianceDerived);

			CBaseResult											BR1=Delegate2(DerivedParameters);

			Console.WriteLine(string.Format("BR1: [{0}] !",BR1.Number));

			/*
			// !!!!! COMPILER hodi ERROR.
			// !!!!! Kedze sa NEPOUZIVA COVARIANCE a CONTRAVARIANCE ani EXPLICITNU KONVERZIU nie je mozne VYKONAT.
			// !!!!! Keby sa vsak COVARIANCE a CONTRAVARIANCE bola by mozna IMPLICINA i EXPLICITNA konverzia.
			DSum_Invariance<CDerivedParameter,CBaseResult>		Delegate3=Delegate1;

			CBaseResult											BR2=Delegate3(DerivedParameters);

			Console.WriteLine(string.Format("BR2: [{0}] !",BR2.Number));

			// !!!!! COMPILER hodi ERROR. C# by nevykonal IMPLICITNU KONVERZIU ANI keby sa pouzival COVARIANCE a CONTRAVARIANCE, pretoze takato konverzia by umoznovala IMPLICITNE konvertovat BASE CLASS na DERIVED CLASS co C# NEUMOZNUJE.
			// !!!!! Kedze sa NEPOUZIVA COVARIANCE a CONTRAVARIANCE ani EXPLICITNU KONVERZIU nie je mozne VYKONAT.
			// !!!!! Keby sa vsak COVARIANCE a CONTRAVARIANCE bola by mozna EXPLICITNA konverzia, no NIE IMPLICITNA konverzia.
			DSum_Invariance<CBaseParameter,CDerivedResult>		Delegate4=Delegate2;

			CDerivedResult										DR2=Delegate4(BaseParameters);

			Console.WriteLine(string.Format("DR2: [{0}] !",DR2.Number));
			*/

			/*
			// !!!!! COMPILER hodi ERROR.
			// !!!!! Kedze sa NEPOUZIVA COVARIANCE a CONTRAVARIANCE ani EXPLICITNU KONVERZIU nie je mozne VYKONAT.
			// !!!!! Keby sa vsak COVARIANCE a CONTRAVARIANCE bola by mozna IMPLICINA i EXPLICITNA konverzia.
			DSum_Invariance<CDerivedParameter,CBaseResult>		Delegate5=Delegate1;

			CBaseResult											BR3=Delegate5(DerivedParameters);

			Console.WriteLine(string.Format("BR3: [{0}] !",BR3.Number));

			// !!!!! COMPILER hodi ERROR. C# by nevykonal IMPLICITNU KONVERZIU ANI keby sa pouzival COVARIANCE a CONTRAVARIANCE, pretoze takato konverzia by umoznovala IMPLICITNE konvertovat BASE CLASS na DERIVED CLASS co C# NEUMOZNUJE.
			// !!!!! Kedze sa NEPOUZIVA COVARIANCE a CONTRAVARIANCE ani EXPLICITNU KONVERZIU nie je mozne VYKONAT.
			// !!!!! Keby sa vsak COVARIANCE a CONTRAVARIANCE bola by mozna EXPLICITNA konverzia, no NIE IMPLICITNA konverzia.
			DSum_Invariance<CBaseParameter,CDerivedResult>		Delegate6=Delegate2;

			CDerivedResult										DR3=Delegate6(BaseParameters);

			Console.WriteLine(string.Format("DR3: [{0}] !",DR3.Number));
			*/
		}
//-------------------------------------------------------------------------------------------------------
		// !!! POUZIVA sa COVARIANCE a CONTRAVARIANCE.
		private static void Test2()
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
		private static void Test3()
		{
			DMyEventHandler<EventArgs>							D1=new DMyEventHandler<EventArgs>(PrintEventArgs);
			DMyEventHandler<CMyEventArgs>						D2=new DMyEventHandler<CMyEventArgs>(PrintCMyEventArgs);

			// !!!!! Aplikuje sa COVARIANCE pretoze do DELEGATE pozadujuceho CMyEventArgs davam metodu pracujucu s EventArgs.
			DMyEventHandler<CMyEventArgs>						D3=new DMyEventHandler<CMyEventArgs>(PrintEventArgs);
			
			D1(new EventArgs());
			D2(new CMyEventArgs());
			D3(new CMyEventArgs());
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test4()
		{
			// Bez VARIANCE.
			IVariantInterface<object,string>					I1=new CObjectVariantClass();

			Console.WriteLine(string.Format("I1: [{0}] !",I1.Do("XXX")));

			// !!! S vyuzitim VARIANCE.
			// !!!!! Aj ked je pozadovany IVariantInterface<string,object> a CStringVariantClass implementuje IVariantInterface<string,object>, tak IMPLICITNA KONVERZIA PREBEHNE, pretoze sa pouzila COVARIANCE a CONTRAVARIANCE.
			IVariantInterface<string,object>					I2=new CStringVariantClass();

			Console.WriteLine(string.Format("I2: [{0}] !",I2.Do("YYY")));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			//Test1();
			//Test2();
			//Test3();
			Test4();

			Console.WriteLine("\nPress any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------