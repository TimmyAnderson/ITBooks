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
using System.Windows.Threading;
using System.Reflection;
//------------------------------------------------------------------------------
namespace ListBoxes
{
//------------------------------------------------------------------------------
	public class CSimpleListBox : Window
	{
//------------------------------------------------------------------------------
        public CSimpleListBox()
        {
            Title="List Color Names";

            ListBox			LstBox=new ListBox();

            LstBox.Width=150;
            LstBox.Height=150;
            LstBox.SelectionChanged+=ListBoxOnSelectionChanged;

            Content=LstBox;

            PropertyInfo[]	Props=typeof(Colors).GetProperties();

            foreach (PropertyInfo Prop in Props)
                LstBox.Items.Add(Prop.Name);
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        private void ListBoxOnSelectionChanged(object Sender, SelectionChangedEventArgs Args)
        {
            ListBox				LstBox=Sender as ListBox;
            string				Str=LstBox.SelectedItem as string;

            if (Str!=null)
            {
                Color			Clr=(Color)typeof(Colors).GetProperty(Str).GetValue(null, null);

                Background=new SolidColorBrush(Clr);
            }
        }
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------