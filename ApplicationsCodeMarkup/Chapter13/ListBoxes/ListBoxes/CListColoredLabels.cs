using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
//------------------------------------------------------------------------------
namespace ListBoxes
{
//------------------------------------------------------------------------------
	public class CListColoredLabels : Window
	{
//------------------------------------------------------------------------------
        public CListColoredLabels()
        {
            Title="List Colored Labels";

            ListBox			LstBox=new ListBox();

            LstBox.Height=150;
            LstBox.Width=150;
            LstBox.SelectionChanged+=ListBoxOnSelectionChanged;

            Content=LstBox;

            PropertyInfo[]	Props = typeof(Colors).GetProperties();

            foreach (PropertyInfo Prop in Props)
            {
                Color		Clr=(Color) Prop.GetValue(null, null);
                bool		IsBlack=.222 * Clr.R + .707 * Clr.G + .071 * Clr.B > 128;

                Label		Lbl=new Label();

                Lbl.Content=Prop.Name;
                Lbl.Background=new SolidColorBrush(Clr);
                Lbl.Foreground=(IsBlack==true) ? Brushes.Black : Brushes.White;
                Lbl.Width=100;
                Lbl.Margin=new Thickness(15, 0, 0, 0);
                Lbl.Tag=Clr;

                LstBox.Items.Add(Lbl);
            }
        }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        private void ListBoxOnSelectionChanged(object Sender, SelectionChangedEventArgs Args)
        {
            ListBox			LstBox=Sender as ListBox;
            Label			Lbl=LstBox.SelectedItem as Label;

            if (Lbl!=null)
            {
                Color		Clr=(Color) Lbl.Tag;

                Background=new SolidColorBrush(Clr);
            }
        }
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------