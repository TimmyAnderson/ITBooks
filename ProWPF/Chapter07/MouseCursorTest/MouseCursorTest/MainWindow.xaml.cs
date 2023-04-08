using System;
using System.Collections.Generic;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.Windows.Resources;
//------------------------------------------------------------------------
// 1. Program demonstruje pouzitie Mouse Cursors.
// 2. Kazdy Element ma property Cursor, kde mozem nastavit Cursor pre dany Element.
// 3. Nastavenim ForceCursor mozem prednastavit aby vsetky Child Element pouzivali Cursor svojho predka.
// !!! 4. Pomocou property Mouse.OverrideCursor mozem prednastavit Cursor pre CELU APLIKACIU.
// !!! 5. Mozem pouzivat CUSTOM Cursors.
//------------------------------------------------------------------------
namespace MouseCursorTest
{
//------------------------------------------------------------------------
	public partial class MainWindow:System.Windows.Window
	{
//------------------------------------------------------------------------
		public MainWindow()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void OnClick1(object Sender, RoutedEventArgs E)
		{
			StreamResourceInfo		SRI=Application.GetResourceStream(new Uri("Cursors\\Banana.ani", UriKind.Relative));
			Cursor					CustomCursor=new Cursor(SRI.Stream);

			Mouse.OverrideCursor=CustomCursor;
		}
//------------------------------------------------------------------------
		private void OnClick2(object Sender, RoutedEventArgs E)
		{
			StreamResourceInfo		SRI=Application.GetResourceStream(new Uri("Cursors\\Cross.cur", UriKind.Relative));
			Cursor					CustomCursor=new Cursor(SRI.Stream);

			Mouse.OverrideCursor=CustomCursor;
		}
//------------------------------------------------------------------------
		private void OnClick3(object Sender, RoutedEventArgs E)
		{
			StreamResourceInfo		SRI=Application.GetResourceStream(new Uri("Cursors\\FillItUp.ani", UriKind.Relative));
			Cursor					CustomCursor=new Cursor(SRI.Stream);

			Mouse.OverrideCursor=CustomCursor;
		}
//------------------------------------------------------------------------
		private void OnClick4(object Sender, RoutedEventArgs E)
		{
			StreamResourceInfo		SRI=Application.GetResourceStream(new Uri("Cursors\\HourGlass2.ani", UriKind.Relative));
			Cursor					CustomCursor=new Cursor(SRI.Stream);

			Mouse.OverrideCursor=CustomCursor;
		}
//------------------------------------------------------------------------
		private void OnClick5(object Sender, RoutedEventArgs E)
		{
			StreamResourceInfo		SRI=Application.GetResourceStream(new Uri("Cursors\\HourGlass3.ani", UriKind.Relative));
			Cursor					CustomCursor=new Cursor(SRI.Stream);

			Mouse.OverrideCursor=CustomCursor;
		}
//------------------------------------------------------------------------
		private void OnClickClearCursor(object Sender, RoutedEventArgs E)
		{
			Mouse.OverrideCursor=null;
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------