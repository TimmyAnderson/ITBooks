using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.ComponentModel;
//------------------------------------------------------------------------------
namespace SimpleTests
{
//------------------------------------------------------------------------------
	public class CCurrentWindow
	{
//------------------------------------------------------------------------------
		private static void WriteMainWindow(string Prefix)
		{
			if (Application.Current==null)
				Console.WriteLine(string.Format("{0} - NO APPLICATION !",Prefix));
			else
			{
				if (Application.Current.MainWindow==null)
					Console.WriteLine(string.Format("{0} - NO MAIN WINDOW !",Prefix));
				else
					Console.WriteLine(string.Format("{0} - MAIN WINDOW Title [{1}] !",Prefix,Application.Current.MainWindow.Title));
			}
		}
//------------------------------------------------------------------------------
		private static void Win_Loaded(object Sender, RoutedEventArgs E)
		{
			Window		Win=Sender as Window;

			WriteMainWindow(string.Format("{0} LOADED",Win.Title));
		}
//------------------------------------------------------------------------------
		private static void Win_Closing(object Sender, CancelEventArgs E)
		{
			Window		Win=Sender as Window;

			WriteMainWindow(string.Format("{0} CLOSING",Win.Title));
		}
//------------------------------------------------------------------------------
		private static void Win_Closed(object Sender, EventArgs E)
		{
			Window		Win=Sender as Window;

			WriteMainWindow(string.Format("{0} CLOSED",Win.Title));
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		public static void Do1()
		{
            Window			Win1=new Window();

            Win1.Title="Window 1";
			Win1.Loaded+=new RoutedEventHandler(Win_Loaded);
			Win1.Closing+=new System.ComponentModel.CancelEventHandler(Win_Closing);
			Win1.Closed+=new EventHandler(Win_Closed);

            Win1.Show();

            Window			Win2=new Window();

            Win2.Title="Window 2";
			Win2.Loaded+=new RoutedEventHandler(Win_Loaded);
			Win2.Closing+=new System.ComponentModel.CancelEventHandler(Win_Closing);
			Win2.Closed+=new EventHandler(Win_Closed);

            Win2.Show();

			// !!! Kedze Application vytvorim az TU, tak ANI Win1, ani Win2 NIE SU MAIN WINDOWS aplikacie.
            Application		App=new Application();

			WriteMainWindow("DO 1");

            App.Run();

			WriteMainWindow("DO 2");
		}
//------------------------------------------------------------------------------
		public static void Do2()
		{
			// Application vytvorim HNED NA ZACIATKU.
            Application		App=new Application();

            Window			Win1=new Window();

            Win1.Title="Window 1";
			Win1.Loaded+=new RoutedEventHandler(Win_Loaded);
			Win1.Closing+=new System.ComponentModel.CancelEventHandler(Win_Closing);
			Win1.Closed+=new EventHandler(Win_Closed);

            Win1.Show();

            Window			Win2=new Window();

            Win2.Title="Window 2";
			Win2.Loaded+=new RoutedEventHandler(Win_Loaded);
			Win2.Closing+=new System.ComponentModel.CancelEventHandler(Win_Closing);
			Win2.Closed+=new EventHandler(Win_Closed);

            Win2.Show();

			WriteMainWindow("DO 1");

            App.Run();

			WriteMainWindow("DO 2");
		}
//------------------------------------------------------------------------------
		public static void Do3()
		{
			// Application vytvorim HNED NA ZACIATKU.
            Application		App=new Application();

            Window			Win1=new Window();

            Win1.Title="Window 1";
			Win1.Loaded+=new RoutedEventHandler(Win_Loaded);
			Win1.Closing+=new System.ComponentModel.CancelEventHandler(Win_Closing);
			Win1.Closed+=new EventHandler(Win_Closed);

            Window			Win2=new Window();

            Win2.Title="Window 2";
			Win2.Loaded+=new RoutedEventHandler(Win_Loaded);
			Win2.Closing+=new System.ComponentModel.CancelEventHandler(Win_Closing);
			Win2.Closed+=new EventHandler(Win_Closed);

			// !!! Vymenim poradie volania Show().
            Win2.Show();
            Win1.Show();

			WriteMainWindow("DO 1");

            App.Run();

			WriteMainWindow("DO 2");
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------