using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Media;
//------------------------------------------------------------------------------
namespace StackAndWrapPanels
{
//------------------------------------------------------------------------------
	class Program
	{
//------------------------------------------------------------------------------
		private static void Test1()
		{
			CStackPanelWithEvents		Win=new CStackPanelWithEvents();
			Application					App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test2()
		{
			CScrollViewer				Win=new CScrollViewer();
			Application					App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test3()
		{
			CViewBox					Win=new CViewBox();
			Application					App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test4()
		{
			CContentWithStackPanel		Win=new CContentWithStackPanel();
			Application					App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test5()
		{
			CGroupBox					Win=new CGroupBox();
			Application					App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test6()
		{
			CWrapPanel					Win=new CWrapPanel();
			Application					App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test7()
		{
			CWrapPanelSameSize			Win=new CWrapPanelSameSize();
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