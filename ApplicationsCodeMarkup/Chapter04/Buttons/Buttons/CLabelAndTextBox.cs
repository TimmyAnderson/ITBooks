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
	public class CLabelAndTextBox : Window
	{
//------------------------------------------------------------------------------
		private TextBox								MMyTextBox=new TextBox();
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		public CLabelAndTextBox()
		{
			Label		MyLabel=new Label();
			Button		MyButton=new Button();

			MyLabel.Content="_Set some text:";
			// Pri vybere Alt-S sa hodi FOCUS na TextBox.
			MyLabel.Target=MMyTextBox;

			MMyTextBox.MinWidth=200;

			MyButton.Content="Press me";
			MyButton.Click+=new RoutedEventHandler(MyButton_Click);

			this.Height=50;

			StackPanel	SP=new StackPanel();

			SP.Orientation=Orientation.Horizontal;

			SP.Children.Add(MyLabel);
			SP.Children.Add(MMyTextBox);
			SP.Children.Add(MyButton);

			Content=SP;
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		private void MyButton_Click(object Sender, RoutedEventArgs E)
		{
			MessageBox.Show(string.Format("You have entered: [{0}] !",MMyTextBox.Text));
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------