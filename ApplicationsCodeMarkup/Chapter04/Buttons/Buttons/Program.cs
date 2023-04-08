using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Media;
//------------------------------------------------------------------------------
namespace Buttons
{
//------------------------------------------------------------------------------
	class Program
	{
//------------------------------------------------------------------------------
		private static void Test1()
		{
			CSimpleButton				Win=new CSimpleButton();
			Application					App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test2()
		{
			CPositionedButton			Win=new CPositionedButton();
			Application					App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test3()
		{
			CTwoButtons					Win=new CTwoButtons();
			Application					App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test4()
		{
			CSizeToContentButton		Win=new CSizeToContentButton();
			Application					App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test5()
		{
			CResouceImageButton			Win=new CResouceImageButton();
			Application					App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test6()
		{
			CButtonWithCommand			Win=new CButtonWithCommand();
			Application					App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test7()
		{
			CToggleButton				Win=new CToggleButton();
			Application					App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test8()
		{
			CButtonWithToolTip			Win=new CButtonWithToolTip();
			Application					App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test9()
		{
			CLabelAndTextBox			Win=new CLabelAndTextBox();
			Application					App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test10()
		{
			CEditSomeRichText			Win=new CEditSomeRichText();
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
				Test10();
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