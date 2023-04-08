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
namespace CustomButtonControlTemplate
{
//------------------------------------------------------------------------
	public partial class SimpleTemplate:System.Windows.Window
	{
//------------------------------------------------------------------------
		public SimpleTemplate()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
        private void OnClicked(object Sender, RoutedEventArgs E)
        {
            MessageBox.Show(string.Format("You clicked: {0} !",((Button) Sender).Name));
        }
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------