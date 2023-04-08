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
namespace ElementTransformations
{
//------------------------------------------------------------------------
	public partial class RotateAnimation:System.Windows.Window
	{
//------------------------------------------------------------------------
		public RotateAnimation()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
        private void OnClicked(object Sender, RoutedEventArgs E)
        {
            MLabel.Text=string.Format("You clicked: {0} !",((Button)E.OriginalSource).Content);
        }
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------