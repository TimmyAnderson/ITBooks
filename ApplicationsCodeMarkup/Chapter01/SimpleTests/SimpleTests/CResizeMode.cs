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
	public class CResizeMode
	{
//------------------------------------------------------------------------------
		public static void Do1()
		{
            Application			App=new Application();
            Window				Win=new Window();

			Win.ResizeMode=ResizeMode.CanMinimize;
            Win.Title=Win.ResizeMode.ToString();

            App.Run(Win);
		}
//------------------------------------------------------------------------------
		public static void Do2()
		{
            Application			App=new Application();
            Window				Win=new Window();

			Win.ResizeMode=ResizeMode.CanResize;
            Win.Title=Win.ResizeMode.ToString();

            App.Run(Win);
		}
//------------------------------------------------------------------------------
		public static void Do3()
		{
            Application			App=new Application();
            Window				Win=new Window();

			Win.ResizeMode=ResizeMode.CanResizeWithGrip;
            Win.Title=Win.ResizeMode.ToString();

            App.Run(Win);
		}
//------------------------------------------------------------------------------
		public static void Do4()
		{
            Application			App=new Application();
            Window				Win=new Window();

			Win.ResizeMode=ResizeMode.NoResize;
            Win.Title=Win.ResizeMode.ToString();

            App.Run(Win);
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------