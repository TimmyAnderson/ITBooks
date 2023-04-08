using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
//-----------------------------------------------------------------------------------------------------------------
namespace RoutedEventInXAML
{
//-----------------------------------------------------------------------------------------------------------------
	public partial class CRoutedEventDemo : Window
	{
//-----------------------------------------------------------------------------------------------------------------
        public CRoutedEventDemo()
        {
            InitializeComponent();
        }
//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
		// Event Handler zachytavajuci Click EVENTS zo VSETKYCH MenuItems.
        private void MenuItemOnClick(object Sender, RoutedEventArgs Args)
        {
            string				Str=(Args.Source as MenuItem).Header as string;
            Color				Clr=(Color)ColorConverter.ConvertFromString(Str);

            MTextBlock.Foreground=new SolidColorBrush(Clr);
        }
//-----------------------------------------------------------------------------------------------------------------
	}
//-----------------------------------------------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------------------------------------------