﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
//-------------------------------------------------------------------------------------------------------
namespace Constructors
{
//-------------------------------------------------------------------------------------------------------
	public class CStaticConstructor2
	{
//-------------------------------------------------------------------------------------------------------
		static CStaticConstructor2()
		{
			Console.WriteLine("CStaticConstructor2 STATIC CONSTRUCTOR CALLED - PHASE 1 !");

			CStaticConstructor1.Print();

			Console.WriteLine("CStaticConstructor2 STATIC CONSTRUCTOR CALLED - PHASE 2 !");
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public static void Print()
		{
			Console.WriteLine("CStaticConstructor2.Print() CALLED !");
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------