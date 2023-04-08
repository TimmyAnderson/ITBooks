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
// 1. Program demonstruje vytvornie Custom Elementu z existujuceho STANDARDNEHO WPF Elemetnu.
// 2. Pri realizacii vyuziva triedu MaskedTextProvider, ktora implementuje funkcionalitu a je maskovana.
//------------------------------------------------------------------------
namespace MaskedTestBoxClient
{
//------------------------------------------------------------------------
	public partial class MainWindow:Window
	{
//------------------------------------------------------------------------
		public MainWindow()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------