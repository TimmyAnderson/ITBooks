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
using System.Windows.Navigation;
using System.Windows.Shapes;
//------------------------------------------------------------------------
namespace PageHistoryTestClient
{
//------------------------------------------------------------------------
	public partial class KeepAlivePage:System.Windows.Controls.Page
	{
//------------------------------------------------------------------------
		private string						MValue="No Value !";
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public KeepAlivePage()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void OnLoadClick(object Sender, RoutedEventArgs E)
		{
			MResult.Content=MValue;
		}
//------------------------------------------------------------------------
		private void OnSaveClick(object Sender, RoutedEventArgs E)
		{
			MValue=MTextBox.Text;
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------