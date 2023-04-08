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
//-----------------------------------------------------------------------------------------------------------------
namespace ApplicationResources
{
//-----------------------------------------------------------------------------------------------------------------
	public partial class MainWindow:Window
	{
//-----------------------------------------------------------------------------------------------------------------
		public MainWindow()
		{
            Resources.Add("MThicknessMargin", new Thickness(24, 12, 24, 23));

			InitializeComponent();
		}
//-----------------------------------------------------------------------------------------------------------------
	}
//-----------------------------------------------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------------------------------------------