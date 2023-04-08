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
using System.ComponentModel;
//------------------------------------------------------------------------
namespace LifetimeEventsTest
{
//------------------------------------------------------------------------
	public partial class SubWindow:System.Windows.Window
	{
//------------------------------------------------------------------------
		public SubWindow()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		protected override void OnRender(DrawingContext DC)
		{
			Debug.WriteLine("\tOnRender() CALLED !");
 			base.OnRender(DC);
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void OnWindowInitialized(object Sender, EventArgs E)
		{
			Debug.WriteLine("\tOnWindowInitialized() CALLED !");
		}
//------------------------------------------------------------------------
		private void OnWindowLoaded(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine("\tOnWindowLoaded() CALLED !");
		}
//------------------------------------------------------------------------
		private void OnWindowUnloaded(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine("\tOnWindowUnloaded() CALLED !");
		}
//------------------------------------------------------------------------
		private void OnWindowSourceInitialized(object Sender, EventArgs E)
		{
			Debug.WriteLine("\tOnWindowSourceInitialized() CALLED !");
		}
//------------------------------------------------------------------------
		private void OnWindowContentRendered(object Sender, EventArgs E)
		{
			Debug.WriteLine("\tOnWindowContentRendered() CALLED !");
		}
//------------------------------------------------------------------------
		private void OnWindowActivated(object Sender, EventArgs E)
		{
			Debug.WriteLine("\tOnWindowActivated() CALLED !");
		}
//------------------------------------------------------------------------
		private void OnWindowDeactivated(object Sender, EventArgs E)
		{
			Debug.WriteLine("\tOnWindowDeactivated() CALLED !");
		}
//------------------------------------------------------------------------
		private void OnWindowClosing(object Sender, CancelEventArgs E)
		{
			Debug.WriteLine("\tOnWindowClosing() CALLED !");

			if (MessageBox.Show("Do you really want to CLOSE Window ?","Close Window",MessageBoxButton.YesNo)==MessageBoxResult.No)
				E.Cancel=true;
		}
//------------------------------------------------------------------------
		private void OnWindowClosed(object Sender, EventArgs E)
		{
			Debug.WriteLine("\tOnWindowClosed() CALLED !");
		}
//------------------------------------------------------------------------
		private void OnStackPanelInitialized(object Sender, EventArgs E)
		{
			Debug.WriteLine("\tOnStackPanelInitialized() CALLED !");

			Debug.WriteLine(string.Format("\tOnStackPanelInitialized() - MWindow: {0} !",MWindow));
			Debug.WriteLine(string.Format("\tOnStackPanelInitialized() - MLabel1: {0} !",MLabel1));
			Debug.WriteLine(string.Format("\tOnStackPanelInitialized() - MLabel2: {0} !",MLabel2));
		}
//------------------------------------------------------------------------
		private void OnStackPanelLoaded(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine("\tOnStackPanelLoaded() CALLED !");

			Debug.WriteLine(string.Format("\tOnStackPanelLoaded() - MWindow: {0} !",MWindow));
			Debug.WriteLine(string.Format("\tOnStackPanelLoaded() - MLabel1: {0} !",MLabel1));
			Debug.WriteLine(string.Format("\tOnStackPanelLoaded() - MLabel2: {0} !",MLabel2));
		}
//------------------------------------------------------------------------
		private void OnStackPanelUnloaded(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine("\tOnStackPanelUnloaded() CALLED !");
		}
//------------------------------------------------------------------------
		private void OnLabel1Initialized(object Sender, EventArgs E)
		{
			Debug.WriteLine("\tOnLabel1Initialized() CALLED !");
		}
//------------------------------------------------------------------------
		private void OnLabel1Loaded(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine("\tOnLabel1Loaded() CALLED !");
		}
//------------------------------------------------------------------------
		private void OnLabel1Unloaded(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine("\tOnLabel1Unloaded() CALLED !");
		}
//------------------------------------------------------------------------
		private void OnLabel2Initialized(object Sender, EventArgs E)
		{
			Debug.WriteLine("\tOnLabel2Initialized() CALLED !");
		}
//------------------------------------------------------------------------
		private void OnLabel2Loaded(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine("\tOnLabel2Loaded() CALLED !");
		}
//------------------------------------------------------------------------
		private void OnLabel2Unloaded(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine("\tOnLabel2Unloaded() CALLED !");
		}
//------------------------------------------------------------------------
		private void OnInvalidateWindow(object Sender, RoutedEventArgs E)
		{
			MWindow.InvalidateVisual();
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------