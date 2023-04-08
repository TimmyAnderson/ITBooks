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
	public class CPositionedButton : Window
	{
//------------------------------------------------------------------------------
		public CPositionedButton()
		{
			Button		MyButton=new Button();

			MyButton.Content="Press Me !!!";
			MyButton.Click+=new RoutedEventHandler(MyButton_Click);
			MyButton.Padding=new Thickness(10);

			Console.WriteLine(string.Format("HorizontalContentAlignment: [{0}] !",MyButton.HorizontalContentAlignment));
			Console.WriteLine(string.Format("VerticalContentAlignment: [{0}] !",MyButton.VerticalContentAlignment));

			MyButton.HorizontalContentAlignment=HorizontalAlignment.Left;
			MyButton.VerticalContentAlignment=VerticalAlignment.Top;

			MyButton.HorizontalContentAlignment=HorizontalAlignment.Stretch;
			MyButton.VerticalContentAlignment=VerticalAlignment.Stretch;

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