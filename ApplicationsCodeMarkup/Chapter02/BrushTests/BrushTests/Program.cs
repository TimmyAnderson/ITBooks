using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
//------------------------------------------------------------------------------
namespace BrushTests
{
//------------------------------------------------------------------------------
	class Program
	{
//------------------------------------------------------------------------------
		private static void Test1()
		{
			CVaryTheBackground		Win=new CVaryTheBackground();
			Application				App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test2()
		{
			CSimpleGradientBrush.Do1();
		}
//------------------------------------------------------------------------------
		private static void Test3()
		{
			CSimpleGradientBrush.Do2();
		}
//------------------------------------------------------------------------------
		private static void Test4()
		{
			CFollowTheRainbow		Win=new CFollowTheRainbow();
			Application				App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test5()
		{
			CCircleTheRainbow		Win=new CCircleTheRainbow();
			Application				App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test6()
		{
			CClickTheGradientCenter	Win=new CClickTheGradientCenter();
			Application				App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test7()
		{
			CRotateTheGradientOrigin	Win=new CRotateTheGradientOrigin();
			Application					App=new Application();

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
				//Test1();
				//Test2();
				//Test3();
				//Test4();
				//Test5();
				//Test6();
				Test7();
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