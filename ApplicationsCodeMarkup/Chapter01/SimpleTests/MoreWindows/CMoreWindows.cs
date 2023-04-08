using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Input;
//------------------------------------------------------------------------------
namespace MoreWindows
{
//------------------------------------------------------------------------------
	public class CMoreWindows : Application
	{
//------------------------------------------------------------------------------
		private void ShowWindows(string Prefix)
		{
			if (Windows.Count==0)
				Console.WriteLine("{0} NO WINDOWS !",Prefix);
			else
			{
				Console.WriteLine("{0} WINDOWS:",Prefix);

				foreach(Window Win in Windows)
					Console.WriteLine("\tWindow [{0}] !",Win.Title);
			}
		}
//------------------------------------------------------------------------------
        private void WindowOnMouseDown(object Sender, MouseButtonEventArgs Args)
        {
            Window			Win=new Window();

            Win.Title="Modal Dialog Box";
            Win.ShowDialog();
        }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        protected override void OnStartup(StartupEventArgs Args)
        {
            Window			WinMain=new Window();

			ShowWindows("WinMain CREATED");

            WinMain.Title="Main Window";
            WinMain.MouseDown+=WindowOnMouseDown;
			WinMain.Closed+=new EventHandler(Win_Closed);
            WinMain.Show();

			ShowWindows("WinMain SHOWN");

            for (int i=0;i<2;i++)
            {
                Window		Win=new Window();

				Win.Closed+=new EventHandler(Win_Closed);
                Win.Title=string.Format("Extra Window No. [{0}]",(i + 1));
                Win.Show();
            }

			ShowWindows("All windows SHOWN");
        }
//------------------------------------------------------------------------------
		private void Win_Closed(object Sender, EventArgs E)
		{
			ShowWindows("Window CLOSED");
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------