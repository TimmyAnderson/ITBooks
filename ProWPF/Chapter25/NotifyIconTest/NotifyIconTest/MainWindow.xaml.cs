using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
//------------------------------------------------------------------------
// 1. Program demonstruje pouzitie NotifyIcon WinForms komponenty vo WPF aplikacii.
// 2. Kedze NotifyIcon NIE JE WPF komponenta NEMAM DESIGN SUPPORT. Nato aby som to obisiel ZAOBALIM NotifyIcon DO Component triedy (NotifyIconWrapper).
//------------------------------------------------------------------------
namespace NotifyIconTest
{
//------------------------------------------------------------------------
	public partial class MainWindow:Window
	{
//------------------------------------------------------------------------
		private NotifyIconWrapper			MComponent;
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public MainWindow()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void Button_Click(object Sender, RoutedEventArgs E)
		{
			if (MComponent!=null)
			{
				MComponent.Dispose();
				MComponent=null;
			}
			else
			{
				// !!! Staci iba vytvorit instanciu NotifyIconWrapper a hned sa vytvori aj NotifyIcon.
				MComponent=new NotifyIconWrapper();
			}
		}
//------------------------------------------------------------------------
		private void Window_Unloaded(object Sender, RoutedEventArgs E)
		{
			if (MComponent!=null)
			{
				MComponent.Dispose();
				MComponent=null;
			}
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------