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
using DataChangeNotificationLibrary;
//------------------------------------------------------------------------
namespace DataChangeNotificationClient
{
//------------------------------------------------------------------------
	public partial class INotifyPropertyChangedNotification:System.Windows.Window
	{
//------------------------------------------------------------------------
		private CNameINotifyPropertyChangedNotification	MName=new CNameINotifyPropertyChangedNotification("Timmy", "Anderson", 12);
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public INotifyPropertyChangedNotification()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void OnGetData(object Sender, RoutedEventArgs E)
		{
			MGrid.DataContext=MName;
		}
//------------------------------------------------------------------------
		private void OnPrintData(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine(MName.ToString());
		}
//------------------------------------------------------------------------
		private void OnSetFirstName(object Sender, RoutedEventArgs E)
		{
			MName.FirstName="Jenny";
		}
//------------------------------------------------------------------------
		private void OnSetLastName(object Sender, RoutedEventArgs E)
		{
			MName.LastName="Thompson";
		}
//------------------------------------------------------------------------
		private void OnSetAge(object Sender, RoutedEventArgs E)
		{
			MName.Age=13;
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------