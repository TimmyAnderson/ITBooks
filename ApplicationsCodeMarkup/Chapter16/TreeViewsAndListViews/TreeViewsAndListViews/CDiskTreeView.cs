using System;
using System.Reflection;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using System.IO;
//------------------------------------------------------------------------------
namespace TreeViewsAndListViews
{
//------------------------------------------------------------------------------
	public class CDiskTreeView : Window
	{
//------------------------------------------------------------------------------
        private StackPanel										MStack;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        public CDiskTreeView()
		{
            Title="Recurse Directories Incrementally";

            Grid				MyGrid = new Grid();

            Content=MyGrid;

            ColumnDefinition	ColDef=new ColumnDefinition();

            ColDef.Width=new GridLength(50, GridUnitType.Star);
            MyGrid.ColumnDefinitions.Add(ColDef);

            ColDef=new ColumnDefinition();
            ColDef.Width=GridLength.Auto;
            MyGrid.ColumnDefinitions.Add(ColDef);

            ColDef=new ColumnDefinition();
            ColDef.Width=new GridLength(50, GridUnitType.Star);
            MyGrid.ColumnDefinitions.Add(ColDef);

            CDirectoryTreeView	MyTree=new CDirectoryTreeView();

            MyTree.SelectedItemChanged+=TreeViewOnSelectedItemChanged;
            MyGrid.Children.Add(MyTree);
            Grid.SetColumn(MyTree, 0);

            GridSplitter		Split=new GridSplitter();

            Split.Width=6;
            Split.ResizeBehavior=GridResizeBehavior.PreviousAndNext;
            MyGrid.Children.Add(Split);
            Grid.SetColumn(Split, 1);

            ScrollViewer		Scroll=new ScrollViewer();

            MyGrid.Children.Add(Scroll);
            Grid.SetColumn(Scroll, 2);

            MStack=new StackPanel();
            Scroll.Content=MStack;
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        private void TreeViewOnSelectedItemChanged(object Sender, RoutedPropertyChangedEventArgs<object> Args)
        {
            CDirectoryTreeViewItem		Item=Args.NewValue as CDirectoryTreeViewItem;

            MStack.Children.Clear();

            FileInfo[]					Infos;

            try
            {
                Infos=Item.DirectoryInfo.GetFiles();
            }
            catch
            {
                return;
            }

            foreach (FileInfo Info in Infos)
            {
                TextBlock				Text=new TextBlock();

                Text.Text=Info.Name;
                MStack.Children.Add(Text);
            }
        }
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------