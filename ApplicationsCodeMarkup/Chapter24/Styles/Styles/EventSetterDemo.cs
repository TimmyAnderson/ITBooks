using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
//-------------------------------------------------------------------------------------------------------
namespace Styles
{
//-------------------------------------------------------------------------------------------------------
	public partial class EventSetterDemo : Window
	{
//-------------------------------------------------------------------------------------------------------
        public EventSetterDemo()
        {
            InitializeComponent();
        }
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// !!! Spolocny handler pre VIACERO BUTTONS - nastaveny cez EVENT SETTER.
        private void ButtonOnClick(object Sender, RoutedEventArgs Args)
        {
            Button			Btn=Args.Source as Button;

            MessageBox.Show(string.Format("The button labeled {0} has been clicked !",Btn.Content), Title);
        }
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------