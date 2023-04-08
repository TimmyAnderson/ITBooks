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
using System.ComponentModel;
using System.Windows.Data;
//------------------------------------------------------------------------------
namespace TreeViewsAndListViews
{
//------------------------------------------------------------------------------
	public class CSimpleSortedListView : Window
	{
//------------------------------------------------------------------------------
        public CSimpleSortedListView()
		{
            Title = "List Sorted System Parameters";

            ListView					LListView=new ListView();

            Content=LListView;

            // !!! Vytvorim GridView.
            GridView					LGridView=new GridView();

            LListView.View=LGridView;

            // Definujem stlpce pre GridView.
            GridViewColumn				Col=new GridViewColumn();

            Col.Header="Property Name";
            Col.Width=200;
            Col.DisplayMemberBinding=new Binding("Name");
            LGridView.Columns.Add(Col);

            Col=new GridViewColumn();
            Col.Header="Value";
            Col.Width=200;
            LGridView.Columns.Add(Col);

            // Definujem TEMPLATE pre 2. stlpec, aby bol zarovnany napravo.
            DataTemplate				LTemplate=new DataTemplate(typeof(string));

            FrameworkElementFactory		FactoryTextBlock=new FrameworkElementFactory(typeof(TextBlock));

            FactoryTextBlock.SetValue(TextBlock.HorizontalAlignmentProperty, HorizontalAlignment.Right);
            FactoryTextBlock.SetBinding(TextBlock.TextProperty, new Binding("Value"));

            LTemplate.VisualTree=FactoryTextBlock;

			// !!! Nastavim CELL TEMPLATE.
            Col.CellTemplate=LTemplate;

            PropertyInfo[]				Props=typeof(SystemParameters).GetProperties();

            SortedList<string, CSystemParam>	Sortlist=new SortedList<string, CSystemParam>();

            foreach (PropertyInfo Prop in Props)
			{
                if (Prop.PropertyType!=typeof(ResourceKey))
                {
                    CSystemParam		SysParam=new CSystemParam();

                    SysParam.Name=Prop.Name;
                    SysParam.Value=Prop.GetValue(null, null);
                    Sortlist.Add(Prop.Name, SysParam);
                }
			}

            LListView.ItemsSource=Sortlist.Values;
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------