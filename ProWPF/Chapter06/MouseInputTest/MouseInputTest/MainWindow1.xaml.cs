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
// 1. Program demonstruje pouzitie Mouse Events.
// 2. Mouse podporuje osobitne stlacenie Eventy pre lave a prave tlacitko, pre pohyb a Wheel.
// !!! 3. Ak chcem mat zarucene aby som na MouseDown dostal Event MouseUp musim urobit Capture mysi cez Mouse.Capture(). Odvtedy VETKY Events bude dostavat Element, ktory zaslem do metody a to az do EXPLICITNEHO VOLANIA Mouse.Capture(null). Do tej doby OSATTNE ELEMENTS NEBUDU DOSTAVAT Mouse Events. Tu ej takisto dobre spracovavat Event LostMouseCapture, ktory sa vola ak Windows si prideli sam mys, alebo klepnem na ine okno. V tomto Evente je nutne uvolnit Capture.
// !!! 4. Poziciu mysi v mozem zistit pomocou Mouse.GetPosition(). Pozicia sa urcuje relativne na Element, ktory mu zaslem ako parameter.
//------------------------------------------------------------------------
namespace MouseInputTest
{
//------------------------------------------------------------------------
	public partial class MainWindow1:System.Windows.Window
	{
//------------------------------------------------------------------------
		public MainWindow1()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void OnKeyDown(object Sender, KeyEventArgs E)
		{
			Debug.WriteLine("");
			Debug.WriteLine("");
			Debug.WriteLine("");
			Debug.WriteLine("");
			Debug.WriteLine("");
			Debug.WriteLine("");
			Debug.WriteLine("");
			Debug.WriteLine("");
			Debug.WriteLine("");
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void OnStackPanel1_MouseLeftButtonDown(object Sender, MouseButtonEventArgs E)
		{
			Debug.WriteLine(string.Format("OnStackPanel1_MouseLeftButtonDown() !"));
		}
//------------------------------------------------------------------------
		private void OnStackPanel1_MouseLeftButtonUp(object Sender, MouseButtonEventArgs E)
		{
			Debug.WriteLine(string.Format("OnStackPanel1_MouseLeftButtonUp() !"));
		}
//------------------------------------------------------------------------
		private void OnStackPanel1_MouseDown(object Sender, MouseButtonEventArgs E)
		{
			Debug.WriteLine(string.Format("OnStackPanel1_MouseDown() !"));
		}
//------------------------------------------------------------------------
		private void OnStackPanel1_MouseUp(object Sender, MouseButtonEventArgs E)
		{
			Debug.WriteLine(string.Format("OnStackPanel1_MouseUp() !"));
		}
//------------------------------------------------------------------------
		private void OnStackPanel1_MouseMove(object Sender, MouseEventArgs E)
		{
			//Debug.WriteLine(string.Format("OnStackPanel1_MouseMove() !"));
		}
//------------------------------------------------------------------------
		private void OnStackPanel1_MouseEnter(object Sender, MouseEventArgs E)
		{
			Debug.WriteLine(string.Format("OnStackPanel1_MouseEnter() !"));
		}
//------------------------------------------------------------------------
		private void OnStackPanel1_MouseLeave(object Sender, MouseEventArgs E)
		{
			Debug.WriteLine(string.Format("OnStackPanel1_MouseLeave() !"));
		}
//------------------------------------------------------------------------
		private void OnStackPanel1_MouseWheel(object Sender, MouseWheelEventArgs E)
		{
			Debug.WriteLine(string.Format("OnStackPanel1_MouseWheel() !"));
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void OnBorder_MouseLeftButtonDown(object Sender, MouseButtonEventArgs E)
		{
			Debug.WriteLine(string.Format("OnBorder_MouseLeftButtonDown() !"));
		}
//------------------------------------------------------------------------
		private void OnBorder_MouseLeftButtonUp(object Sender, MouseButtonEventArgs E)
		{
			Debug.WriteLine(string.Format("OnBorder_MouseLeftButtonUp() !"));
		}
//------------------------------------------------------------------------
		private void OnBorder_MouseDown(object Sender, MouseButtonEventArgs E)
		{
			Debug.WriteLine(string.Format("OnBorder_MouseDown() !"));
		}
//------------------------------------------------------------------------
		private void OnBorder_MouseUp(object Sender, MouseButtonEventArgs E)
		{
			Debug.WriteLine(string.Format("OnBorder_MouseUp() !"));
		}
//------------------------------------------------------------------------
		private void OnBorder_MouseMove(object Sender, MouseEventArgs E)
		{
			//Debug.WriteLine(string.Format("OnBorder_MouseMove() !"));
		}
//------------------------------------------------------------------------
		private void OnBorder_MouseEnter(object Sender, MouseEventArgs E)
		{
			Debug.WriteLine(string.Format("OnBorder_MouseEnter() !"));
		}
//------------------------------------------------------------------------
		private void OnBorder_MouseLeave(object Sender, MouseEventArgs E)
		{
			Debug.WriteLine(string.Format("OnBorder_MouseLeave() !"));
		}
//------------------------------------------------------------------------
		private void OnBorder_MouseWheel(object Sender, MouseWheelEventArgs E)
		{
			Debug.WriteLine(string.Format("OnBorder_MouseWheel() !"));
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void OnStackPanel2_MouseLeftButtonDown(object Sender, MouseButtonEventArgs E)
		{
			Debug.WriteLine(string.Format("OnStackPanel2_MouseLeftButtonDown() !"));
		}
//------------------------------------------------------------------------
		private void OnStackPanel2_MouseLeftButtonUp(object Sender, MouseButtonEventArgs E)
		{
			Debug.WriteLine(string.Format("OnStackPanel2_MouseLeftButtonUp() !"));
		}
//------------------------------------------------------------------------
		private void OnStackPanel2_MouseDown(object Sender, MouseButtonEventArgs E)
		{
			Debug.WriteLine(string.Format("OnStackPanel2_MouseDown() !"));
		}
//------------------------------------------------------------------------
		private void OnStackPanel2_MouseUp(object Sender, MouseButtonEventArgs E)
		{
			Debug.WriteLine(string.Format("OnStackPanel2_MouseUp() !"));
		}
//------------------------------------------------------------------------
		private void OnStackPanel2_MouseMove(object Sender, MouseEventArgs E)
		{
			//Debug.WriteLine(string.Format("OnStackPanel2_MouseMove() !"));
		}
//------------------------------------------------------------------------
		private void OnStackPanel2_MouseEnter(object Sender, MouseEventArgs E)
		{
			Debug.WriteLine(string.Format("OnStackPanel2_MouseEnter() !"));
		}
//------------------------------------------------------------------------
		private void OnStackPanel2_MouseLeave(object Sender, MouseEventArgs E)
		{
			Debug.WriteLine(string.Format("OnStackPanel2_MouseLeave() !"));
		}
//------------------------------------------------------------------------
		private void OnStackPanel2_MouseWheel(object Sender, MouseWheelEventArgs E)
		{
			Debug.WriteLine(string.Format("OnStackPanel2_MouseWheel() !"));
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void OnLabel_MouseLeftButtonDown(object Sender, MouseButtonEventArgs E)
		{
			Debug.WriteLine(string.Format("OnLabel_MouseLeftButtonDown() !"));
		}
//------------------------------------------------------------------------
		private void OnLabel_MouseLeftButtonUp(object Sender, MouseButtonEventArgs E)
		{
			Debug.WriteLine(string.Format("OnLabel_MouseLeftButtonUp() !"));
		}
//------------------------------------------------------------------------
		private void OnLabel_MouseDown(object Sender, MouseButtonEventArgs E)
		{
			Debug.WriteLine(string.Format("OnLabel_MouseDown() !"));
		}
//------------------------------------------------------------------------
		private void OnLabel_MouseUp(object Sender, MouseButtonEventArgs E)
		{
			Debug.WriteLine(string.Format("OnLabel_MouseUp() !"));
		}
//------------------------------------------------------------------------
		private void OnLabel_MouseMove(object Sender, MouseEventArgs E)
		{
			//Debug.WriteLine(string.Format("OnLabel_MouseMove() !"));
		}
//------------------------------------------------------------------------
		private void OnLabel_MouseEnter(object Sender, MouseEventArgs E)
		{
			Debug.WriteLine(string.Format("OnLabel_MouseEnter() !"));
		}
//------------------------------------------------------------------------
		private void OnLabel_MouseLeave(object Sender, MouseEventArgs E)
		{
			Debug.WriteLine(string.Format("OnLabel_MouseLeave() !"));
		}
//------------------------------------------------------------------------
		private void OnLabel_MouseWheel(object Sender, MouseWheelEventArgs E)
		{
			Debug.WriteLine(string.Format("OnLabel_MouseWheel() !"));
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void OnButton_MouseLeftButtonDown(object Sender, MouseButtonEventArgs E)
		{
			Debug.WriteLine(string.Format("OnButton_MouseLeftButtonDown() !"));
		}
//------------------------------------------------------------------------
		private void OnButton_MouseLeftButtonUp(object Sender, MouseButtonEventArgs E)
		{
			Debug.WriteLine(string.Format("OnButton_MouseLeftButtonUp() !"));
		}
//------------------------------------------------------------------------
		private void OnButton_MouseDown(object Sender, MouseButtonEventArgs E)
		{
			Debug.WriteLine(string.Format("OnButton_MouseDown() !"));
		}
//------------------------------------------------------------------------
		private void OnButton_MouseUp(object Sender, MouseButtonEventArgs E)
		{
			Debug.WriteLine(string.Format("OnButton_MouseUp() !"));
		}
//------------------------------------------------------------------------
		private void OnButton_MouseMove(object Sender, MouseEventArgs E)
		{
			//Debug.WriteLine(string.Format("OnButton_MouseMove() !"));
		}
//------------------------------------------------------------------------
		private void OnButton_MouseEnter(object Sender, MouseEventArgs E)
		{
			Debug.WriteLine(string.Format("OnButton_MouseEnter() !"));
		}
//------------------------------------------------------------------------
		private void OnButton_MouseLeave(object Sender, MouseEventArgs E)
		{
			Debug.WriteLine(string.Format("OnButton_MouseLeave() !"));
		}
//------------------------------------------------------------------------
		private void OnButton_MouseWheel(object Sender, MouseWheelEventArgs E)
		{
			Debug.WriteLine(string.Format("OnButton_MouseWheel() !"));
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------