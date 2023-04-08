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
using RoutedEventsTestLibrary;
//------------------------------------------------------------------------
// 1. Simulujem Shared RE.
// 2. Shared RE je taka, ktora zdiela identifikator s inym RE.
//------------------------------------------------------------------------
namespace RoutedEventsTestClient
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
		private void OnRESharedBase(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine(string.Format("\tRESharedBase"));
		}
//------------------------------------------------------------------------
		private void OnRESharedReference(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine(string.Format("\tRESharedReference"));
		}
//------------------------------------------------------------------------
		private void OnFireMREPatentSharedBaseEvent(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine("");
			MREPatent.RaiseEvent(new RoutedEventArgs(CREPatent.RESharedBaseEvent,this));
		}
//------------------------------------------------------------------------
		private void OnFireMREPatentSharedReferenceEvent(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine("");
			MREPatent.RaiseEvent(new RoutedEventArgs(CREPatent.RESharedReferenceEvent,this));
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------