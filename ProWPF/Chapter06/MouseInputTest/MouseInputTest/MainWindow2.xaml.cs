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
namespace MouseInputTest
{
//------------------------------------------------------------------------
	public partial class MainWindow2:System.Windows.Window
	{
//------------------------------------------------------------------------
		public MainWindow2()
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

			Debug.WriteLine(string.Format("LeftButton: {0} !",Mouse.LeftButton));
			Debug.WriteLine(string.Format("MiddleButton: {0} !",Mouse.MiddleButton));
			Debug.WriteLine(string.Format("RightButton: {0} !",Mouse.RightButton));
			Debug.WriteLine(string.Format("XButton1: {0} !",Mouse.XButton1));
			Debug.WriteLine(string.Format("XButton2: {0} !",Mouse.XButton2));
			Debug.WriteLine(string.Format("MLabel3 - POSITION: {0} !",Mouse.GetPosition(MLabel3)));
			Debug.WriteLine(string.Format("MLabel1 - POSITION: {0} !",Mouse.GetPosition(MLabel1)));
			Debug.WriteLine(string.Format("MLabel2 - POSITION: {0} !",Mouse.GetPosition(MLabel2)));
			Debug.WriteLine(string.Format("MButton - POSITION: {0} !",Mouse.GetPosition(MButton)));
			Debug.WriteLine(string.Format("MStackPanel1 - POSITION: {0} !",Mouse.GetPosition(MStackPanel1)));
			Debug.WriteLine(string.Format("MBorder - POSITION: {0} !",Mouse.GetPosition(MBorder)));
			Debug.WriteLine(string.Format("MStackPanel2 - POSITION: {0} !",Mouse.GetPosition(MStackPanel2)));
			Debug.WriteLine(string.Format("MWindow - POSITION: {0} !",Mouse.GetPosition(MWindow)));
			Debug.WriteLine("");
			Debug.WriteLine("");
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void OnLabel1_MouseLeftButtonDown(object Sender, MouseButtonEventArgs E)
		{
			Debug.WriteLine(string.Format("OnLabel1_MouseLeftButtonDown() !"));
		}
//------------------------------------------------------------------------
		private void OnLabel1_MouseLeftButtonUp(object Sender, MouseButtonEventArgs E)
		{
			Debug.WriteLine(string.Format("OnLabel1_MouseLeftButtonUp() !"));
		}
//------------------------------------------------------------------------
		private void OnLabel2_MouseLeftButtonDown(object Sender, MouseButtonEventArgs E)
		{
			Debug.WriteLine(string.Format("OnLabel2_MouseLeftButtonDown() !"));

			// !!! Nastavim Capture.
			Mouse.Capture(MLabel2);
		}
//------------------------------------------------------------------------
		private void OnLabel2_MouseLeftButtonUp(object Sender, MouseButtonEventArgs E)
		{
			Debug.WriteLine(string.Format("OnLabel2_MouseLeftButtonUp() !"));

			// !!! Zrusim Capture.
			Mouse.Capture(null);
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void OnLabel2LostMouseCapture(object Sender, MouseEventArgs E)
		{
			// !!! Zrusim Capture.
			Mouse.Capture(null);
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void OnLabel3_MouseLeftButtonDown(object Sender, MouseButtonEventArgs E)
		{
			Debug.WriteLine(string.Format("LeftButton: {0} !",E.LeftButton));
			Debug.WriteLine(string.Format("MiddleButton: {0} !",E.MiddleButton));
			Debug.WriteLine(string.Format("RightButton: {0} !",E.RightButton));
			Debug.WriteLine(string.Format("XButton1: {0} !",E.XButton1));
			Debug.WriteLine(string.Format("XButton2: {0} !",E.XButton2));
			Debug.WriteLine(string.Format("ClickCount: {0} !",E.ClickCount));

			Debug.WriteLine(string.Format("MLabel3 - POSITION: {0} !",Mouse.GetPosition(MLabel3)));
			Debug.WriteLine(string.Format("MLabel1 - POSITION: {0} !",Mouse.GetPosition(MLabel1)));
			Debug.WriteLine(string.Format("MLabel2 - POSITION: {0} !",Mouse.GetPosition(MLabel2)));
			Debug.WriteLine(string.Format("MButton - POSITION: {0} !",Mouse.GetPosition(MButton)));
			Debug.WriteLine(string.Format("MStackPanel1 - POSITION: {0} !",Mouse.GetPosition(MStackPanel1)));
			Debug.WriteLine(string.Format("MBorder - POSITION: {0} !",Mouse.GetPosition(MBorder)));
			Debug.WriteLine(string.Format("MStackPanel2 - POSITION: {0} !",Mouse.GetPosition(MStackPanel2)));
			Debug.WriteLine(string.Format("MWindow - POSITION: {0} !",Mouse.GetPosition(MWindow)));
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------