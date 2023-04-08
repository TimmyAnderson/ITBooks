using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Media;
//------------------------------------------------------------------------------
namespace RoutedEvents
{
//------------------------------------------------------------------------------
	class Program
	{
//------------------------------------------------------------------------------
		private static void HANDLED_Win_PreviewMySuperRE(object Sender, RoutedEventArgs E)
		{
			E.Handled=true;

			Console.WriteLine("PreviewMySuperRE RAISED and IS HANDLED !");
		}
//------------------------------------------------------------------------------
		private static void Win_PreviewMySuperRE(object Sender, RoutedEventArgs E)
		{
			Console.WriteLine("PreviewMySuperRE RAISED !");
		}
//------------------------------------------------------------------------------
		private static void Win_MySuperRE(object Sender, RoutedEventArgs E)
		{
			Console.WriteLine("MySuperRE RAISED !");
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		private static void Test1()
		{
			CExamineRoutedEvents		App=new CExamineRoutedEvents();

			App.Run();
		}
//------------------------------------------------------------------------------
		private static void Test2()
		{
			CMouseRoutedEvents			App=new CMouseRoutedEvents();

			App.Run();
		}
//------------------------------------------------------------------------------
		private static void Test3()
		{
			CMyCoustomREWindow			Win=new CMyCoustomREWindow();

			Win.PreviewMySuperRE+=new RoutedEventHandler(Win_PreviewMySuperRE);
			Win.MySuperRE+=new RoutedEventHandler(Win_MySuperRE);

			Application					App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test4()
		{
			CMyCoustomREWindow			Win=new CMyCoustomREWindow();

			Win.PreviewMySuperRE+=new RoutedEventHandler(HANDLED_Win_PreviewMySuperRE);
			Win.MySuperRE+=new RoutedEventHandler(Win_MySuperRE);

			Application					App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test5()
		{
			CMouseCapture				Win=new CMouseCapture();
			Application					App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test6()
		{
			CKeyboardEvents				Win=new CKeyboardEvents();
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
				Test6();
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