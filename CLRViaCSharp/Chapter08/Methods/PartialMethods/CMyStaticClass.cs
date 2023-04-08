﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace PartialMethods
{
//-------------------------------------------------------------------------------------------------------
	public static partial class CMyStaticClass
	{
//-------------------------------------------------------------------------------------------------------
		static partial void PartialMethod1();
//-------------------------------------------------------------------------------------------------------
		static partial void PartialMethod2();
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// !!! Tato metoda sluzi na prezretie v ILDASM.
		public static void Execute()
		{
			Console.WriteLine("CMyStaticClass ---> STEP 1 !");

			PartialMethod1();

			Console.WriteLine("CMyStaticClass ---> STEP 2 !");

			PartialMethod2();

			Console.WriteLine("CMyStaticClass ---> STEP 3 !");
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------