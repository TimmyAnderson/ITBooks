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
	public class CNamedColorsListBox : Window
	{
//------------------------------------------------------------------------------
        public CNamedColorsListBox()
        {
            Title="List Named Colors";

            ListBox				LstBox=new ListBox();

            LstBox.Width=150;
            LstBox.Height=150;
            LstBox.SelectionChanged+=ListBoxOnSelectionChanged;

            Content=LstBox;

            LstBox.ItemsSource=CNamedColor.All;

			// Pouzijem DisplayMemberPath na definovanie property, ktora urci DisplayName.
            LstBox.DisplayMemberPath="Name";

			// Pouzijem SelectedValuePath na definovanie property, ktora urci Value.
            LstBox.SelectedValuePath="Color";
        }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        private void ListBoxOnSelectionChanged(object Sender, SelectionChangedEventArgs Args)
        {
            ListBox				LstBox=Sender as ListBox;

            if (LstBox.SelectedValue!=null)
            {
                Color			Clr=(Color) LstBox.SelectedValue;

                Background=new SolidColorBrush(Clr);
            }
        }
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------