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
	public class CHandleAnEvent
	{
//------------------------------------------------------------------------------
        private static void WindowOnMouseDown(object Sender, MouseButtonEventArgs Args)
        {
            Window			Win=Sender as Window;
            string			StrMessage=string.Format("Window clicked with {0} button at point ({1}) !",Args.ChangedButton,Args.GetPosition(Win));

            MessageBox.Show(StrMessage,Win.Title);
        }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		public static void Do()
		{
            Application			App=new Application();
            Window				Win=new Window();

            Win.Title="Handle An Event";
            Win.MouseDown+=WindowOnMouseDown;

            App.Run(Win);
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------