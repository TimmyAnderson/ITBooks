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
	public class CTwoButtons : Window
	{
//------------------------------------------------------------------------------
		public CTwoButtons()
		{
			Button		MyButton1=new Button();
			Button		MyButton2=new Button();

			MyButton1.Content="Default button";
			MyButton1.Click+=new RoutedEventHandler(MyButton1_Click);
			MyButton1.IsDefault=true;

			MyButton2.Content="Cancel button";
			MyButton2.Click+=new RoutedEventHandler(MyButton2_Click);
			MyButton2.IsCancel=true;

			StackPanel	SP=new StackPanel();

			SP.Children.Add(MyButton1);
			SP.Children.Add(MyButton2);

			Content=SP;
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		private void MyButton1_Click(object Sender, RoutedEventArgs E)
		{
			MessageBox.Show("DEFAULT button was CLICKED !");
		}
//------------------------------------------------------------------------------
		private void MyButton2_Click(object Sender, RoutedEventArgs E)
		{
			MessageBox.Show("CANCEL button was CLICKED !");
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------