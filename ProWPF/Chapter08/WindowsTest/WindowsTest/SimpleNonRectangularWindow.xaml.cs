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
//------------------------------------------------------------------------
namespace WindowsTest
{
//------------------------------------------------------------------------
	public partial class SimpleNonRectangularWindow:System.Windows.Window
	{
//------------------------------------------------------------------------
		private bool					MIsWiden=false;
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public SimpleNonRectangularWindow()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void OnWindowLeftButtonGrid(object Sender, MouseButtonEventArgs E)
		{
			// !!! Zapezpeci posun okna pri tahani klientskej oblasti.
			this.DragMove();
		}
//------------------------------------------------------------------------
		private void Window_InitiateWiden(object Sender, MouseEventArgs E)
		{
			MIsWiden=true;

			// !!!!! Musim nastavit Handled na TRUE aby sa nerozsirila udalost do OnWindowLeftButtonGrid() a NEBILA SA S DragMove().
			E.Handled=true;
		}
//------------------------------------------------------------------------
		private void Window_Widen(object Sender, MouseEventArgs E)
		{
			Rectangle		Rect=(Rectangle) Sender;

			if (MIsWiden==true)
			{
				// Musim zachytit mys, kedze sa pri roztahovani dostavam mimo Window.
				Rect.CaptureMouse();

				double		NewWidth=E.GetPosition(this).X+5;

				if (NewWidth>0)
					this.Width=NewWidth;
			}

			// !!!!! Musim nastavit Handled na TRUE aby sa nerozsirila udalost do OnWindowLeftButtonGrid() a NEBILA SA S DragMove().
			E.Handled=true;
		}
//------------------------------------------------------------------------
		private void Window_EndWiden(object Sender, MouseEventArgs E)
		{
			MIsWiden=false;

			// Zrusim Capture.
		
			Rectangle		Rect=(Rectangle) Sender;
		
			Rect.ReleaseMouseCapture();

			// !!!!! Musim nastavit Handled na TRUE aby sa nerozsirila udalost do OnWindowLeftButtonGrid() a NEBILA SA S DragMove().
			E.Handled=true;
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------