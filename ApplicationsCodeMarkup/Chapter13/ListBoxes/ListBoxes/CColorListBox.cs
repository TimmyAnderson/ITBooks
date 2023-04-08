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
	public class CColorListBox : ListBox
	{
//------------------------------------------------------------------------------
        public CColorListBox()
        {
            PropertyInfo[]			Props=typeof(Colors).GetProperties();

            foreach (PropertyInfo Prop in Props)
            {
                CColorListBoxItem	Item=new CColorListBoxItem();

                Item.Text=Prop.Name;
                Item.Color=(Color)Prop.GetValue(null, null);
                Items.Add(Item);
            }

            SelectedValuePath="Color";

			SelectedIndex=0;
        }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        public Color								SelectedColor
        {
            get
			{
				return((Color)SelectedValue);
			}
            set
			{
				SelectedValue=value;
			}
        }
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------