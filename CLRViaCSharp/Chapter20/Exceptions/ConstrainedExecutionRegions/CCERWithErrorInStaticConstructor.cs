using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.ConstrainedExecution;
using System.Runtime.CompilerServices;
//-------------------------------------------------------------------------------------------------------
namespace ConstrainedExecutionRegions
{
//-------------------------------------------------------------------------------------------------------
	public class CCERWithErrorInStaticConstructor
	{
//-------------------------------------------------------------------------------------------------------
		static CCERWithErrorInStaticConstructor()
		{
			Console.WriteLine("!!!!!!!!!! STATIC CONSTRUCTOR CCERWithErrorInStaticConstructor() CALLED !");

			// !!!!! UMYSELNE GENERUJEM EXCEPTION.
			throw(new Exception("EXCEPTION from STATIC CONSTRUCTOR !"));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// !!! Metoda je oznacena ako metoda ktoru MA BYT DOPREDNE JIT KOMPILOVANA.
		[ReliabilityContract(Consistency.WillNotCorruptState,Cer.Success)]
		public static void SomeStaticMethod()
		{
			Console.WriteLine("CCERWithErrorInStaticConstructor.SomeStaticMethod() CALLED !");
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------