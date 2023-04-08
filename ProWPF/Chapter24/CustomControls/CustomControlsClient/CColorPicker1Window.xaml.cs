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
//------------------------------------------------------------------------
namespace CustomControlsClient
{
//------------------------------------------------------------------------
	public partial class CColorPicker1Window:Window
	{
//------------------------------------------------------------------------
		public CColorPicker1Window()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void ColorPicker_ColorChanged(object Sender, RoutedPropertyChangedEventArgs<Color> E)
		{
			if (MLBLColor!=null)
				MLBLColor.Content=string.Format("The new color is: {0} !",E.NewValue.ToString());
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------