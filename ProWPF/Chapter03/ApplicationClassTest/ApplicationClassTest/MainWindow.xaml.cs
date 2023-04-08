using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
//------------------------------------------------------------------------
// 1. Program demonstruje rozlicne aspekty Application class.
// 2. Cez triedy Aplication mozem zachytavat Events ako pri starte tak aj konci programu.
// 3. Pomocou Application.ShutdownMode mozem nastavit ukoncovaci mod programu.
// 4. Navratovu hodnotu z metody Application.Run() ziskam volanim Application.Shutdown(), ktora ukonci beh Run() metody.
// 5. Event SessionEnding je volany, ked sa konci session - napriklad pri odhlaseni usera. Mam moznost urobit Cancel ukoncenia programu.
// 6. Pamatere command line mozem ziskat zachytenim eventu Startup a citanim jeho parametra.
// !!! 7. V evente DispatcherUnhandledException mozem zachytavat Exceptions a popripade ich spracovat, alebo ich nechat tak. Ak sa ani tu nespracuju tak program spadne.
//------------------------------------------------------------------------
namespace ApplicationClassTest
{
//------------------------------------------------------------------------
	public partial class MainWindow:System.Windows.Window
	{
//------------------------------------------------------------------------
		private int							MCounter=0;
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public MainWindow()
		{
			InitializeComponent();

			MShutdownState.Content=Application.Current.ShutdownMode.ToString();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void OnSetLastWindowCloseClick(object Sender, RoutedEventArgs E)
		{
			Application.Current.ShutdownMode=ShutdownMode.OnLastWindowClose;
			MShutdownState.Content=Application.Current.ShutdownMode.ToString();
		}
//------------------------------------------------------------------------
		private void OnSetMainWindowCloseClick(object Sender, RoutedEventArgs E)
		{
			Application.Current.ShutdownMode=ShutdownMode.OnMainWindowClose;
			MShutdownState.Content=Application.Current.ShutdownMode.ToString();
		}
//------------------------------------------------------------------------
		private void OnExplicitShutdownClick(object Sender, RoutedEventArgs E)
		{
			Application.Current.ShutdownMode=ShutdownMode.OnExplicitShutdown;
			MShutdownState.Content=Application.Current.ShutdownMode.ToString();
		}
//------------------------------------------------------------------------
		private void OnDoShutdownClick(object Sender, RoutedEventArgs E)
		{
			Application.Current.Shutdown(999);
		}
//------------------------------------------------------------------------
		private void OnShowAllWindowsClick(object Sender, RoutedEventArgs E)
		{
			WindowCollection		Wins=Application.Current.Windows;

			Debug.WriteLine(string.Format("!!! Windows List:"));

			for (int i=0;i<Wins.Count;i++)
				Debug.WriteLine(string.Format("\tWindow[{0}]: {1} !",i+1,Wins[i].Title));
		}
//------------------------------------------------------------------------
		private void OnThrowException1Click(object Sender, RoutedEventArgs E)
		{
			throw(new ApplicationException());
		}
//------------------------------------------------------------------------
		private void OnThrowException2Click(object Sender, RoutedEventArgs E)
		{
			throw(new InvalidCastException());
		}
//------------------------------------------------------------------------
		private void OnCreateSubWindow(object Sender, RoutedEventArgs E)
		{
			SubWindow			SW=new SubWindow(++MCounter);

			SW.Show();
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------