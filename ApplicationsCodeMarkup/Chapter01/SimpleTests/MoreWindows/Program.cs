using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
//------------------------------------------------------------------------------
namespace MoreWindows
{
//------------------------------------------------------------------------------
	class Program
	{
//------------------------------------------------------------------------------
		private static void Test1()
		{
			CMoreWindows			App=new CMoreWindows();

			App.Run();
		}
//------------------------------------------------------------------------------
		private static void Test2()
		{
			CCloseMainWindow		App=new CCloseMainWindow();

			// !!! Zmenim mod ukoncenia aplikacie pri uzatvoreni MAIN WINDOW.
			App.ShutdownMode=ShutdownMode.OnMainWindowClose;
			
			App.Run();
		}
//------------------------------------------------------------------------------
		private static void Test3()
		{
			CParentChild			App=new CParentChild();
		
			App.Run();
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
				Console.WriteLine(string.Format("!!!!! EXCEPTION: [{0}] !",E));
			}
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------