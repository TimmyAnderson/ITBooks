using System;
using System.Reflection;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Data;
using System.IO;
//------------------------------------------------------------------------------
namespace TreeViewsAndListViews
{
//------------------------------------------------------------------------------
	public class CTreeViewWithTemplate : Window
	{
//------------------------------------------------------------------------------
        public CTreeViewWithTemplate()
		{
            Title = "Template the Tree";

            TreeView					LTreeView=new TreeView();

            Content=LTreeView;

            // Vytvorim HierarchicalDataTemplate, ktora sluzi ako TEMPLATE v TREE VIEW.
            HierarchicalDataTemplate	LTemplate=new HierarchicalDataTemplate(typeof(CDiskDirectory));

            // !!! HierarchicalDataTemplate ma property ItemsSource, ktora sluzi ako SOURCE pre DATA ITEMS na NIZSEJ UROVNI HIERARCHIE.
            LTemplate.ItemsSource=new Binding("Subdirectories");

            // Template bude obsahovat pre jednoduchost IBA JEDEN TEXTBLOCK.
            FrameworkElementFactory		FactoryTextBlock=new FrameworkElementFactory(typeof(TextBlock));

            // !!! Namapujem Text property ako TEXT v TEXTBLOCK.
            FactoryTextBlock.SetBinding(TextBlock.TextProperty, new Binding("Name"));
            
            // Spravim z TextBlock ROOT VisualTree.
            LTemplate.VisualTree=FactoryTextBlock;

            // Vytvorim ROOT objekt pre TREE VIEW.
            CDiskDirectory				Dir=new CDiskDirectory(new DirectoryInfo(Path.GetPathRoot(Environment.SystemDirectory)));
			
			// Vytvorim ROOT ITEM.
            TreeViewItem				Item=new TreeViewItem();

			// Namapujem ROOT OBJEKT Dir na PROPERTIES TreeViewItem.
            Item.Header=Dir.Name;
            Item.ItemsSource=Dir.Subdirectories;

			// Namapujem TEMPLATE.
            Item.ItemTemplate=LTemplate;

            LTreeView.Items.Add(Item);
            Item.IsExpanded=true;
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------