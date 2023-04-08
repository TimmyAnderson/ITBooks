using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Input;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Controls.Primitives;
//------------------------------------------------------------------------------
namespace Buttons
{
//------------------------------------------------------------------------------
	public class CToggleButton : Window
	{
//------------------------------------------------------------------------------
		public CToggleButton()
		{
            Title="Toggle the Button";

            ToggleButton		Btn=new ToggleButton();
			
            Btn.Content="Can _Resize";
            Btn.HorizontalAlignment=HorizontalAlignment.Center;
            Btn.VerticalAlignment=VerticalAlignment.Center;
            Btn.IsChecked=(ResizeMode == ResizeMode.CanResize);
            Btn.Checked+=ButtonOnChecked;
            Btn.Unchecked+=ButtonOnChecked;
            Content=Btn;
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        private void ButtonOnChecked(object Sender, RoutedEventArgs Args)
        {
            ToggleButton		Btn=Sender as ToggleButton;

            ResizeMode=(bool) (Btn.IsChecked==true) ? ResizeMode.CanResize : ResizeMode.NoResize;
        }
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------