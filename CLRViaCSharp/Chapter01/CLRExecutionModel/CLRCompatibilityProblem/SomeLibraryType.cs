﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
// !!! Sposobi, ze KOMPILATOR BUDE KONTROLOVAT ci assembly je CLS kompatibilna.
[assembly: CLSCompliant(true)]
//-------------------------------------------------------------------------------------------------------
#pragma warning disable 3002, 3005
//-------------------------------------------------------------------------------------------------------
namespace CLRCompatibilityProblem
{
//-------------------------------------------------------------------------------------------------------
	public sealed class SomeLibraryType
	{
//-------------------------------------------------------------------------------------------------------
		// UInt32 NIE JE CLS kompatibilny typ.
		public UInt32 Abc()
		{
			return(0);
		}
//-------------------------------------------------------------------------------------------------------
		// Identifikator SomeLibraryType.abc() sa lisi od  SomeLibraryType.Abc() iba v CASE SENSITIVITY NAZVU co nie je CLS kompatibilne.
		public void abc()
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// !!! NEGENERUJE WARNING, lebo metoda je PRIVATE a teda NEMOZE BYT PRISTUPNA MIMO ASSEMBLY.
		private UInt32 ABC()
		{
			return(0);
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.WriteLine("Hello World !");

			Console.WriteLine("\nPress any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
   }
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------