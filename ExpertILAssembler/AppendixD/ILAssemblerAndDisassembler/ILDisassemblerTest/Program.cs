﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
//-------------------------------------------------------------------------------------------------------
namespace ILDisassemblerTest
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void SimpleTest()
		{
			Console.WriteLine("Hello WORLD !");
		}
//-------------------------------------------------------------------------------------------------------
		private static void ComplexText()
		{
			string[]											Names=new string[]{"Timmy","Atreyu","Jenny"};

			foreach(string Name in Names)
			{
				Console.WriteLine(string.Format("NAME [{0}] !",Name));
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			SimpleTest();
			ComplexText();

			Console.Write("Press ENTER to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------