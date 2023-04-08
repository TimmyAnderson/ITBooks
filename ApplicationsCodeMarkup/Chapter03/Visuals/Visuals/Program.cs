using System;
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
			CWindowWithVisual			Win=new CWindowWithVisual();
			Application					App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test6()
		{
			CWindowWithVisualHost		Win=new CWindowWithVisualHost();
			Application					App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test7()
		{
			CVisual					V=new CVisual();
			CVisualHost				VH=new CVisualHost();

			// Vrati NULL.
			DrawingGroup			DG1=VisualTreeHelper.GetDrawing(V);
			DrawingCollection		DC1=DG1.Children;

			Console.WriteLine("CVisual - Drawings:");

			foreach(Drawing D in DC1)
				Console.WriteLine(string.Format("\t[{0}] !",D));

			Console.WriteLine("\n");

			// Vrati NULL.
			DrawingGroup			DG2=VisualTreeHelper.GetDrawing(VH);
			DrawingCollection		DC2=DG2.Children;

			Console.WriteLine("CVisualHost - Drawings:");

			foreach(Drawing D in DC2)
				Console.WriteLine(string.Format("\t[{0}] !",D));
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
				Test6();
				//Test7();
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