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
	public class CSelectColorFromGrid : Window
	{
//------------------------------------------------------------------------------
        public CSelectColorFromGrid()
        {
            Title="Select Color from Grid";
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

            CColorGridBox		ClrGrid=new CColorGridBox();

            ClrGrid.Margin=new Thickness(24);
            ClrGrid.HorizontalAlignment=HorizontalAlignment.Center;
            ClrGrid.VerticalAlignment=VerticalAlignment.Center;

            Stack.Children.Add(ClrGrid);

            ClrGrid.SetBinding(CColorGridBox.SelectedValueProperty, "Background");
            ClrGrid.DataContext=this;

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