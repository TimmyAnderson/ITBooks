using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Media;
//------------------------------------------------------------------------------
namespace CustomElements
{
//------------------------------------------------------------------------------
	class Program
	{
//------------------------------------------------------------------------------
		private static void Test1()
		{
			CEllipseElementWindow			Win=new CEllipseElementWindow(1);
			Application						App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test2()
		{
			CEllipseElementWindow			Win=new CEllipseElementWindow(2);
			Application						App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test3()
		{
			CEllipseElementWindow			Win=new CEllipseElementWindow(3);
			Application						App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test4()
		{
			CEllipseElementWindow			Win=new CEllipseElementWindow(4);
			Application						App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test5()
		{
			CComplexEllipseElementWindow	Win=new CComplexEllipseElementWindow(1);
			Application						App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test6()
		{
			CComplexEllipseElementWindow	Win=new CComplexEllipseElementWindow(2);
			Application						App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test7()
		{
			CComplexEllipseElementWindow	Win=new CComplexEllipseElementWindow(3);
			Application						App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test8()
		{
			CComplexEllipseElementWindow	Win=new CComplexEllipseElementWindow(4);
			Application						App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test9()
		{
			CClippedEllipseElementWindow	Win=new CClippedEllipseElementWindow(1);
			Application						App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test10()
		{
			CClippedEllipseElementWindow	Win=new CClippedEllipseElementWindow(2);
			Application						App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test11()
		{
			CMyCustomControlWindow			Win=new CMyCustomControlWindow();
			Application						App=new Application();

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
				//Test7();
				//Test8();
				//Test9();
				//Test10();
				Test11();
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