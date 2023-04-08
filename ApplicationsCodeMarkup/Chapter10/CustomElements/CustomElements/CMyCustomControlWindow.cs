using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Input;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
//------------------------------------------------------------------------------
namespace CustomElements
{
//------------------------------------------------------------------------------
	public class CMyCustomControlWindow : Window
	{
//------------------------------------------------------------------------------
		public CMyCustomControlWindow()
		{
            Title="Get Medieval";

            CMyCustomControl	Btn=new CMyCustomControl();

            Btn.Text="Click this button";
            Btn.FontSize=24;
            Btn.HorizontalAlignment=HorizontalAlignment.Center;
            Btn.VerticalAlignment=VerticalAlignment.Center;
            Btn.Padding=new Thickness(5, 20, 5, 20);
            Btn.Knock+=ButtonOnKnock;

            Content = Btn;
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        private void ButtonOnKnock(object sender, RoutedEventArgs Args)
        {
            CMyCustomControl		Btn=Args.Source as CMyCustomControl;

            MessageBox.Show(string.Format("The button labeled [{0}] has been knocked.",Btn.Text), Title);
        }
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------