using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Media;
//------------------------------------------------------------------------------
namespace Contents
{
//------------------------------------------------------------------------------
	class Program
	{
//------------------------------------------------------------------------------
		private static void Test1()
		{
			CWindowWithText				Win=new CWindowWithText();
			Application					App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test2()
		{
			CWindowWithNonVisualObject	Win=new CWindowWithNonVisualObject();
			Application					App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test3()
		{
			CWindowWithFrameworkElement	Win=new CWindowWithFrameworkElement();
			Application					App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test4()
		{
			CWindowWithUIElement		Win=new CWindowWithUIElement();
			Application					App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test5()
		{
			CStringAsContent			Win=new CStringAsContent();
			Application					App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test6()
		{
			CStringBuilderAsContent		Win=new CStringBuilderAsContent();
			Application					App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test7()
		{
			CNewStringAsContent			Win=new CNewStringAsContent();
			Application					App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test8()
		{
			CImageAsContent				Win=new CImageAsContent(3);
			Application					App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test9()
		{
			CShapeAsContent				Win=new CShapeAsContent();
			Application					App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test10()
		{
			CTextBlockAsContent			Win=new CTextBlockAsContent();
			Application					App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test11()
		{
			CCustomRenderingAsContent	Win=new CCustomRenderingAsContent();
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