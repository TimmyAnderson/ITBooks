using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Media;
//------------------------------------------------------------------------------
namespace ToolbarsAndStatusBars
{
//------------------------------------------------------------------------------
	class Program
	{
//------------------------------------------------------------------------------
		private static void Test1()
		{
			CSimpleToolBar					Win=new CSimpleToolBar();
			Application						App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test2()
		{
			CToolBarsInTrays				Win=new CToolBarsInTrays();
			Application						App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test3()
		{
			CStatusBar						Win=new CStatusBar();
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
				Test3();
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