﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
//------------------------------------------------------------------------------
namespace ISupportsCancelationTest
{
//------------------------------------------------------------------------------
	class Program
	{
//------------------------------------------------------------------------------
		private static void Test()
		{
			CMyThread			MT=new CMyThread();

			MT.Run();

			Thread.Sleep(4500);

			MT.Cancel();
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Test();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------