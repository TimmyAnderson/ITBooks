﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Media;
//------------------------------------------------------------------------------
namespace Visuals
{
//------------------------------------------------------------------------------
	class Program
	{
//------------------------------------------------------------------------------
		private static void Test()
		{
			CWindowWithVisuals		Win=new CWindowWithVisuals();
			Application				App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		[STAThread]
		static void Main(string[] args)
		{
			try
			{
				Test();
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E));
			}

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadKey();
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------