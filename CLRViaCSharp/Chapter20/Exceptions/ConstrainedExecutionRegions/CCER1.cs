﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.ConstrainedExecution;
using System.Runtime.CompilerServices;
//-------------------------------------------------------------------------------------------------------
namespace ConstrainedExecutionRegions
{
//-------------------------------------------------------------------------------------------------------
	public class CCER1
	{
//-------------------------------------------------------------------------------------------------------
		static CCER1()
		{
			Console.WriteLine("!!!!!!!!!! STATIC CONSTRUCTOR CCER1() CALLED !");
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// !!! METHOD je oznacena ako METHOD ktora MA BYT DOPREDNE JIT COMPILED.
		[ReliabilityContract(Consistency.WillNotCorruptState,Cer.Success)]
		public static void SomeStaticMethod()
		{
			Console.WriteLine("CCER1.SomeStaticMethod() CALLED !");
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------