using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Diagnostics.Contracts;
//-------------------------------------------------------------------------------------------------------
namespace CodeContracts
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		// !!! Tento EVENT je volany VZDY ked dojde k PORUSENIU CONTRACTU.
		private static void Contract_ContractFailed(object Sender, ContractFailedEventArgs E)
		{
			Console.WriteLine(string.Format("!!! CODE CONTRACT HANDLER - Message: [{0}], Condition: [{1}], FailureKind: [{2}] !",E.Message,E.Condition,E.FailureKind));
			
			// !!! Ak volam SetHandled() tak tym deklarujem, ze CODE CONTRACT je HANDLED a NEBUDE z neho GENEROVANA EXCEPTION.
			E.SetHandled();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private static void Test1()
		{
			try
			{
				// !!! AK JE ZAPNUTY STATIC CHECK hodi WARINING.
				// !!! AK JE ZAPNUTY DYNAMIC CHECK hodi EXCEPTION.
				// !!!!! Ak NEZAPNEM DYNAMIC CHECK, tak EXCEPTION sa NEHODI.
				CName											Name=new CName("Timmy","Anderson",-12);

				Console.WriteLine(string.Format("Name: [{0}] !",Name));
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}], Type: [{1}] !",E.Message,E.GetType()));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test2()
		{
			Contract.ContractFailed+=new EventHandler<ContractFailedEventArgs>(Contract_ContractFailed);

			try
			{
				// !!! AK JE ZAPNUTY STATIC CHECK hodi WARINING.
				// !!! AK JE ZAPNUTY DYNAMIC CHECK hodi EXCEPTION.
				// !!!!! Ak NEZAPNEM DYNAMIC CHECK, tak EXCEPTION sa NEHODI.
				CName											Name=new CName("Timmy","Anderson",-12);

				Console.WriteLine(string.Format("Name: [{0}] !",Name));
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}], Type: [{1}] !",E.Message,E.GetType()));
			}
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