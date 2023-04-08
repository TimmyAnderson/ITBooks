using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Shapes;
//------------------------------------------------------------------------------
namespace ListBoxes
{
//------------------------------------------------------------------------------
	public class CListColorShapes : Window
	{
//------------------------------------------------------------------------------
        public CListColorShapes()
        {
            Title="List Color Shapes";

            ListBox				LstBox=new ListBox();

            LstBox.Width=150;
            LstBox.Height=150;
            LstBox.SelectionChanged+=ListBoxOnSelectionChanged;

            Content=LstBox;

            PropertyInfo[]		Props=typeof(Brushes).GetProperties();

            foreach (PropertyInfo Prop in Props)
            {
                Ellipse			Ellip=new Ellipse();

                Ellip.Width=100;
                Ellip.Height=25;
                Ellip.Margin=new Thickness(10, 5, 0, 5);
                Ellip.Fill=Prop.GetValue(null, null) as Brush;

                LstBox.Items.Add(Ellip);
            }
        }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        private void ListBoxOnSelectionChanged(object Sender, SelectionChangedEventArgs Args)
        {
            ListBox			LstBox=Sender as ListBox;

            if (LstBox.SelectedIndex!=-1)
                Background=(LstBox.SelectedItem as Shape).Fill;
        }
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------