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
// 1. Program demonstruje niektore aspoeky Brushes a Colors.
// 2. Trieda Colors poskytuej pred pripravene farby a SystemColors zas systemove farby.
//------------------------------------------------------------------------
namespace ColorsTest
{
//------------------------------------------------------------------------
	public partial class MainWindow:System.Windows.Window
	{
//------------------------------------------------------------------------
		public MainWindow()
		{
			InitializeComponent();

			MButton2.Background=new SolidColorBrush(Colors.AliceBlue);
			MButton3.Background=new SolidColorBrush(SystemColors.ControlColor);
			MButton4.Background=new SolidColorBrush(SystemColors.ControlBrush.Color);
			// Alpha blending.
			MButton5.Background=new LinearGradientBrush(Color.FromArgb(128,255,0,0),Color.FromArgb(128,0,0,0),45);
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------