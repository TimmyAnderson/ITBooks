﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using MyCOMLib;
//-------------------------------------------------------------------------------------------------------
namespace COMInterop
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
            int						Result;
			BasicMathClass			S=new BasicMathClass();

            S.Add(1, 2, out Result);

            Console.WriteLine(string.Format("Result=[{0}] !",Result));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------