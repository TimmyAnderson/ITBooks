using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
//------------------------------------------------------------------------------
namespace ListBoxes
{
//------------------------------------------------------------------------------
	public class CSelectColorFromWheel : Window
	{
//------------------------------------------------------------------------------
        public CSelectColorFromWheel()
        {
            Title= "Select Color from Wheel";
            SizeToContent=SizeToContent.WidthAndHeight;

            StackPanel			Stack=new StackPanel();

            Stack.Orientation=Orientation.Horizontal;
            Content=Stack;

            Button				Btn=new Button();

            Btn.Content="Do-nothing button\nto test tabbing";
            Btn.Margin=new Thickness(24);
            Btn.HorizontalAlignment=HorizontalAlignment.Center;
            Btn.VerticalAlignment=VerticalAlignment.Center;

            Stack.Children.Add(Btn);

            CColorWheel			ClrWheel=new CColorWheel();

            ClrWheel.Margin=new Thickness(24);
            ClrWheel.HorizontalAlignment=HorizontalAlignment.Center;
            ClrWheel.VerticalAlignment=VerticalAlignment.Center;

            Stack.Children.Add(ClrWheel);

            ClrWheel.SetBinding(CColorWheel.SelectedValueProperty, "Background");
            ClrWheel.DataContext=this;

            Btn=new Button();
            Btn.Content="Do-nothing button\nto test tabbing";
            Btn.Margin=new Thickness(24);
            Btn.HorizontalAlignment=HorizontalAlignment.Center;
            Btn.VerticalAlignment=VerticalAlignment.Center;

            Stack.Children.Add(Btn);
        }
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------