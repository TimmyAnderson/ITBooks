using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Input;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;
//------------------------------------------------------------------------------
namespace Buttons
{
//------------------------------------------------------------------------------
	public class CSimpleButton : Window
	{
//------------------------------------------------------------------------------
		public CSimpleButton()
		{
			Button		MyButton=new Button();

			MyButton.Content="Press Me !!!";
			MyButton.Click+=new RoutedEventHandler(MyButton_Click);

			Content=MyButton;
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		private void MyButton_Click(object Sender, RoutedEventArgs E)
		{
			MessageBox.Show("Button was CLICKED !");
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------