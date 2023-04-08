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
	public class CListColorsElegantly : Window
	{
//------------------------------------------------------------------------------
        public CListColorsElegantly()
        {
            Title = "List Colors Elegantly";

            CColorListBox		LstBox=new CColorListBox();

            LstBox.Height=150;
            LstBox.Width=150;
            LstBox.SelectionChanged+=ListBoxOnSelectionChanged;
            Content=LstBox;

            LstBox.SelectedColor=SystemColors.WindowColor;
        }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        private void ListBoxOnSelectionChanged(object Sender, SelectionChangedEventArgs Args)
        {
            CColorListBox		LstBox=Sender as CColorListBox;

			if (LstBox.SelectedColor!=null)
				Background=new SolidColorBrush(LstBox.SelectedColor);
        }
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------