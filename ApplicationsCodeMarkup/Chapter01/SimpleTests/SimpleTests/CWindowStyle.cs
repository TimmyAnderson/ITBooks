using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Input;
//------------------------------------------------------------------------------
namespace SimpleTests
{
//------------------------------------------------------------------------------
	public class CWindowStyle
	{
//------------------------------------------------------------------------------
		public static void Do1()
		{
            Application			App=new Application();
            Window				Win=new Window();

			Win.WindowStyle=WindowStyle.None;

            Win.Title=Win.WindowStyle.ToString();

            App.Run(Win);
		}
//------------------------------------------------------------------------------
		public static void Do2()
		{
            Application			App=new Application();
            Window				Win=new Window();

			Win.WindowStyle=WindowStyle.SingleBorderWindow;

            Win.Title=Win.WindowStyle.ToString();

            App.Run(Win);
		}
//------------------------------------------------------------------------------
		public static void Do3()
		{
            Application			App=new Application();
            Window				Win=new Window();

			Win.WindowStyle=WindowStyle.ThreeDBorderWindow;

            Win.Title=Win.WindowStyle.ToString();

            App.Run(Win);
		}
//------------------------------------------------------------------------------
		public static void Do4()
		{
            Application			App=new Application();
            Window				Win=new Window();

			Win.WindowStyle=WindowStyle.ToolWindow;

            Win.Title=Win.WindowStyle.ToString();

            App.Run(Win);
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------