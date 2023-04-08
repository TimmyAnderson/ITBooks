using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
//------------------------------------------------------------------------------
namespace TreeViewsAndListViews
{
//------------------------------------------------------------------------------
	public class CExploreDependencyProperties : Window
	{
//------------------------------------------------------------------------------
        public CExploreDependencyProperties()
        {
            Title="Explore Dependency Properties";

            Grid						LGrid=new Grid();

            Content=LGrid;

            ColumnDefinition			Col=new ColumnDefinition();

            Col.Width=new GridLength(1, GridUnitType.Star);
            LGrid.ColumnDefinitions.Add(new ColumnDefinition());

            Col=new ColumnDefinition();
            Col.Width=GridLength.Auto;
            LGrid.ColumnDefinitions.Add(Col);

            Col=new ColumnDefinition();
            Col.Width=new GridLength(3, GridUnitType.Star);
            LGrid.ColumnDefinitions.Add(Col);

            // ClassHierarchyTreeView goes on left side.
            CClassHierarchyTreeView		LTreeView=new CClassHierarchyTreeView(typeof(DependencyObject));

            LGrid.Children.Add(LTreeView);
            Grid.SetColumn(LTreeView, 0);

            GridSplitter				Split=new GridSplitter();

            Split.HorizontalAlignment=HorizontalAlignment.Center;
            Split.VerticalAlignment=VerticalAlignment.Stretch;
            Split.Width=6;
            LGrid.Children.Add(Split);
            Grid.SetColumn(Split, 1);

            CDependencyPropertyListView	LValue=new CDependencyPropertyListView();

            LGrid.Children.Add(LValue);
            Grid.SetColumn(LValue, 2);

            LValue.SetBinding(CDependencyPropertyListView.TypeProperty, "SelectedItem.Type");
            LValue.DataContext=LTreeView;
        }
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------