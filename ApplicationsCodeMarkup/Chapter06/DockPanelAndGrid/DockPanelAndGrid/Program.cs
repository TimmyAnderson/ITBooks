using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Media;
//------------------------------------------------------------------------------
namespace DockPanelAndGrid
{
//------------------------------------------------------------------------------
	class Program
	{
//------------------------------------------------------------------------------
		private static void Test1()
		{
			CSimpleDockPanel			Win=new CSimpleDockPanel();
			Application					App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test2()
		{
			CStandardDockPanel			Win=new CStandardDockPanel();
			Application					App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test3()
		{
			CSimpleGrid					Win=new CSimpleGrid();
			Application					App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test4()
		{
			CMoreEelementsInCellGrid	Win=new CMoreEelementsInCellGrid();
			Application					App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test5()
		{
			CGridWithSpanedElements		Win=new CGridWithSpanedElements();
			Application					App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test6()
		{
			CGridSplitterBON_Center		Win=new CGridSplitterBON_Center();
			Application					App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test7()
		{
			CGridSplitterBON_Right		Win=new CGridSplitterBON_Right();
			Application					App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test8()
		{
			CGridSplitterBON_Left		Win=new CGridSplitterBON_Left();
			Application					App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test9()
		{
			CGridSplitterCN				Win=new CGridSplitterCN();
			Application					App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test10()
		{
			CGridSplitterPC				Win=new CGridSplitterPC();
			Application					App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test11()
		{
			CGridSplitterPN				Win=new CGridSplitterPN();
			Application					App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test12()
		{
			CGridSplitterRD_Rows		Win=new CGridSplitterRD_Rows();
			Application					App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test13()
		{
			CGridSplitterShowPreview	Win=new CGridSplitterShowPreview();
			Application					App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test14()
		{
			CScrollBarTest				Win=new CScrollBarTest();
			Application					App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test15()
		{
			CUniformGridTest			Win=new CUniformGridTest();
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
				//Test11();
				//Test12();
				//Test13();
				//Test14();
				Test15();
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