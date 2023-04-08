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
// 1. Program demonstruje moznosti Data Change Notification.
// 2. Ukazuje teda moznosti, ako je moze updateovat GUI ak v kode sa zmenil datovy objekt, ktory niesol data, ktore boli cez DB mapovane na jednotlive Elements.
// !!! 3. Existuju 4 moznosti ako to zrealizovat.
//    A. Vsetky properties na danom datovom objekte definujem ako DP.
//    B. Pre kazdu property datoveho objektu definujem event odpalime event pomenovany 'PropertyNameChanged', ktora MUSI BYT TYPU EventHandler. Vtedy sa WPF na nu AUTOMATICKY ZAVESI a ja ked volam Event TAK SA UPDATEUJE GUI.
//    C. Implementujem na datovom objekte INotifyPropertyChanged a pri zmene hodnoty property volam event PropertyChanged.
//    D. Na objekte BindingExpression volam metodu UpdateTarget().
// !!! 4. Ak pri volani PropertyChanged nedam ziadne meno property tak sa updateuju vsetky properties.
//------------------------------------------------------------------------
namespace DataChangeNotificationClient
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
		public void OnClick1(object Sender, RoutedEventArgs E)
		{
			DPNotification				Win=new DPNotification();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		public void OnClick2(object Sender, RoutedEventArgs E)
		{
			PNChangedNotification		Win=new PNChangedNotification();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		public void OnClick3(object Sender, RoutedEventArgs E)
		{
			INotifyPropertyChangedNotification	Win=new INotifyPropertyChangedNotification();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		public void OnClick4(object Sender, RoutedEventArgs E)
		{
			UpdateTargetNotification			Win=new UpdateTargetNotification();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------