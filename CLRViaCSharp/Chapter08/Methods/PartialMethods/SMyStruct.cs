﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace PartialMethods
{
//-------------------------------------------------------------------------------------------------------
	public partial struct SMyStruct
	{
//-------------------------------------------------------------------------------------------------------
		partial void PartialMethod1();
//-------------------------------------------------------------------------------------------------------
		partial void PartialMethod2();
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// !!! Tato metoda sluzi na prezretie v ILDASM.
		public void Execute()
		{
			Console.WriteLine("CMyStruct ---> STEP 1 !");

			PartialMethod1();

			Console.WriteLine("CMyStruct ---> STEP 2 !");

			PartialMethod2();

			Console.WriteLine("CMyStruct ---> STEP 3 !");
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------