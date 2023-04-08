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
namespace StackAndWrapPanels
{
//------------------------------------------------------------------------------
	public class CGroupBox : Window
	{
//------------------------------------------------------------------------------
		public CGroupBox()
		{
            Title="Tune the Radio";
            SizeToContent=SizeToContent.WidthAndHeight;

            GroupBox		Group=new GroupBox();

            Group.Header="Window Style";
            Group.Margin=new Thickness(96);
            Group.Padding=new Thickness(5);
            Content=Group;

            StackPanel		Stack=new StackPanel();

            Group.Content=Stack;

            Stack.Children.Add(CreateRadioButton("No border or caption", WindowStyle.None));
            Stack.Children.Add(CreateRadioButton("Single-border window", WindowStyle.SingleBorderWindow));
            Stack.Children.Add(CreateRadioButton("3D-border window", WindowStyle.ThreeDBorderWindow));
            Stack.Children.Add(CreateRadioButton("Tool window", WindowStyle.ToolWindow));

            AddHandler(RadioButton.CheckedEvent, new RoutedEventHandler(RadioOnChecked));
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        private RadioButton CreateRadioButton(string StrText, WindowStyle WinStyle)
        {
            RadioButton			Radio=new RadioButton();

            Radio.Content=StrText;
            Radio.Tag=WinStyle;
            Radio.Margin=new Thickness(5);
            Radio.IsChecked=(WinStyle==WindowStyle);

            return(Radio);
        }
//------------------------------------------------------------------------------
        private void RadioOnChecked(object Sender, RoutedEventArgs Args)
        {
            RadioButton			Radio=Args.Source as RadioButton;

            WindowStyle=(WindowStyle)Radio.Tag;
        }
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------