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
	public partial class UpdateTargetNotification:System.Windows.Window
	{
//------------------------------------------------------------------------
		private CNameUpdateTargetNotification	MName=new CNameUpdateTargetNotification("Timmy", "Anderson", 12);
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public UpdateTargetNotification()
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

			// Musim updateovat Binding.
			BindingExpression			BE=MFirstName.GetBindingExpression(TextBox.TextProperty);

			BE.UpdateTarget();
		}
//------------------------------------------------------------------------
		private void OnSetLastName(object Sender, RoutedEventArgs E)
		{
			MName.LastName="Thompson";

			// Musim updateovat Binding.
			BindingExpression			BE=MLastName.GetBindingExpression(TextBox.TextProperty);

			BE.UpdateTarget();
		}
//------------------------------------------------------------------------
		private void OnSetAge(object Sender, RoutedEventArgs E)
		{
			MName.Age=13;

			// Musim updateovat Binding.
			BindingExpression			BE=MAge.GetBindingExpression(TextBox.TextProperty);

			BE.UpdateTarget();
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------