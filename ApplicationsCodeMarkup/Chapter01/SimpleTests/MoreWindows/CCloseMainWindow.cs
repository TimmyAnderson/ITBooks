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
	public class CCloseMainWindow : Application
	{
//------------------------------------------------------------------------------
        private void WindowOnMouseDown(object Sender, MouseButtonEventArgs Args)
        {
            Window			Win=new Window();

            Win.Title="Modal Dialog Box";

			// Zobrazi sa MODALNE OKNO.
            Win.ShowDialog();
        }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        protected override void OnStartup(StartupEventArgs Args)
        {
            Window			WinMain=new Window();

            WinMain.Title="Main Window";
            WinMain.MouseDown+=WindowOnMouseDown;
            WinMain.Show();

            for (int i=0;i<2;i++)
            {
                Window		Win=new Window();

                Win.Title=string.Format("Extra Window No. [{0}]",(i + 1));
                Win.Show();
            }
        }
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------