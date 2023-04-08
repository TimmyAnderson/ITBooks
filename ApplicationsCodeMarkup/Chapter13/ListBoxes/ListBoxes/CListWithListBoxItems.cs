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
	public class CListWithListBoxItems : Window
	{
//------------------------------------------------------------------------------
		public CListWithListBoxItems()
		{
			Title="List with ListBoxItem";

			ListBox			LstBox=new ListBox();

			LstBox.Height=150;
			LstBox.Width=150;
			LstBox.SelectionChanged+=ListBoxOnSelectionChanged;

			Content=LstBox;

			PropertyInfo[]	Props=typeof(Colors).GetProperties();

			foreach (PropertyInfo Prop in Props)
			{
				Color		Clr=(Color)Prop.GetValue(null, null);
				bool		IsBlack=.222 * Clr.R + .707 * Clr.G + .071 * Clr.B > 128;
				ListBoxItem Item=new ListBoxItem();

				Item.Content=Prop.Name;
				Item.Background=new SolidColorBrush(Clr);
				Item.Foreground=(IsBlack==true) ? Brushes.Black : Brushes.White;
				Item.HorizontalContentAlignment=HorizontalAlignment.Center;
				Item.Padding=new Thickness(2);

				LstBox.Items.Add(Item);
			}
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		private void ListBoxOnSelectionChanged(object Sender, SelectionChangedEventArgs Args)
		{
			ListBox				LstBox=Sender as ListBox;
			ListBoxItem			Item;

			if (Args.RemovedItems.Count > 0)
			{
				Item = Args.RemovedItems[0] as ListBoxItem;

				string			Str=Item.Content as string;

				Item.Content=Str.Substring(2, Str.Length-4);
				Item.FontWeight=FontWeights.Regular;
			}

			if (Args.AddedItems.Count>0)
			{
				Item = Args.AddedItems[0] as ListBoxItem;

				string			Str=Item.Content as string;

				Item.Content="[ " + Str + " ]";
				Item.FontWeight=FontWeights.Bold;
			}

			Item=LstBox.SelectedItem as ListBoxItem;

			if (Item!=null)
				Background=Item.Background;
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------