using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Input;
//------------------------------------------------------------------------------
namespace Positioning
{
//------------------------------------------------------------------------------
	class Program
	{
//------------------------------------------------------------------------------
		private static void Win_MouseDown(object Sender, MouseButtonEventArgs E)
		{
			Window			Win=(Window) Sender;
			
			Console.WriteLine(string.Format("Actual size: [{0} {1}], Width: [{2}], Height: [{3}], Left: [{4}], Top: [{5}] !",Win.ActualWidth,Win.ActualHeight,Win.Width,Win.Height,Win.Left,Win.Top));
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		private static void Test1()
		{
			Window			Win=new Window();

			Win.Title="Random position";
			Win.MouseDown+=new System.Windows.Input.MouseButtonEventHandler(Win_MouseDown);

			Application		App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test2()
		{
			Window			Win=new Window();

			Win.Height=96;
			Win.Width=96;

			Win.Title="96*96 DIU";
			Win.MouseDown+=new System.Windows.Input.MouseButtonEventHandler(Win_MouseDown);

			Application		App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test3()
		{
			Window			Win=new Window();

			Win.Height=120;
			Win.Width=120;

			Win.Title="120*120 DIU";
			Win.MouseDown+=new System.Windows.Input.MouseButtonEventHandler(Win_MouseDown);

			Application		App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test4()
		{
			Window			Win=new Window();

			Win.Height=300;
			Win.Width=200;

			Win.Left=SystemParameters.PrimaryScreenWidth-Win.Width;
			Win.Top=SystemParameters.PrimaryScreenHeight-Win.Height;

			Win.Title="Bottom Right";
			Win.MouseDown+=new System.Windows.Input.MouseButtonEventHandler(Win_MouseDown);

			Application		App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test5()
		{
			Window			Win=new Window();

			Win.Height=300;
			Win.Width=200;

			Win.Left=SystemParameters.WorkArea.Right-Win.Width;
			Win.Top=SystemParameters.WorkArea.Bottom-Win.Height;

			Win.Title="Work Area - Bottom Right";
			Win.MouseDown+=new System.Windows.Input.MouseButtonEventHandler(Win_MouseDown);

			Application		App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test6()
		{
			Window			Win=new Window();

			Win.Width=300;
			Win.Height=200;

			Win.WindowStartupLocation=WindowStartupLocation.CenterScreen;

			Win.Title="Center Screen";
			Win.MouseDown+=new System.Windows.Input.MouseButtonEventHandler(Win_MouseDown);

			Application		App=new Application();

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
				Console.WriteLine(string.Format("!!!!! EXCEPTION: [{0}] !",E));
			}

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadKey();
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------