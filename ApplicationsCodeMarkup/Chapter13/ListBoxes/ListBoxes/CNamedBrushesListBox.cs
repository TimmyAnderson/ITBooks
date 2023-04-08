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
	public class CNamedBrushesListBox : Window
	{
//------------------------------------------------------------------------------
        public CNamedBrushesListBox()
        {
            Title="List Named Brushes";

            ListBox			LstBox=new ListBox();

            LstBox.Width=150;
            LstBox.Height=150;
            Content=LstBox;

            LstBox.ItemsSource=CNamedBrush.All;
            LstBox.DisplayMemberPath="Name";
            LstBox.SelectedValuePath="Brush";

			// Realizujem BIDNING na priradenie SelectedValuePath k DP Background Window.
            LstBox.SetBinding(ListBox.SelectedValueProperty, "Background");
            LstBox.DataContext=this;
        }
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------