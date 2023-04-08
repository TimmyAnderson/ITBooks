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
using System.Windows.Shapes;
using System.Windows.Media.Media3D;
//------------------------------------------------------------------------
namespace Graphics3DTest
{
//------------------------------------------------------------------------
	public partial class Materials:Window
	{
//------------------------------------------------------------------------
		public Materials()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
        private void Chk_Click(object Sender, RoutedEventArgs E)
        {
            MMaterialsGroup.Children.Clear();

            if (MChkBackground.IsChecked==true)
                MRect.Visibility=Visibility.Visible;
            else
                MRect.Visibility=Visibility.Hidden;

            if (MChkDiffuse.IsChecked==true)
                MMaterialsGroup.Children.Add((Material)FindResource("MDiffuse"));

            if (MChkSpecular.IsChecked==true)
                MMaterialsGroup.Children.Add((Material)FindResource("MSpecular"));

            if (MChkEmissive.IsChecked==true)
                MMaterialsGroup.Children.Add((Material)FindResource("MEmissive"));
        }
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------