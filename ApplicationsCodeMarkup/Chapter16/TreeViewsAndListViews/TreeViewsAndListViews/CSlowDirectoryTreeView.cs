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
	public class CSlowDirectoryTreeView : Window
	{
//------------------------------------------------------------------------------
        public CSlowDirectoryTreeView()
		{
            Title = "Recurse Directories Inefficiently";

            TreeView		MyTree=new TreeView();

            Content=MyTree;

            TreeViewItem	Item=new TreeViewItem();

            Item.Header=Path.GetPathRoot(Environment.SystemDirectory);
            Item.Tag=new DirectoryInfo(Item.Header as string);
            MyTree.Items.Add(Item);

			// Rekurzivne naplnim TreeView.
			GetSubdirectories(Item);
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		// Rekurzivna funkcia na naplnanie TREE VIEW.
        private void GetSubdirectories(TreeViewItem Item)
        {
            DirectoryInfo			Dir=Item.Tag as DirectoryInfo;
            DirectoryInfo[]			SubDirs;

            try
            {
                SubDirs=Dir.GetDirectories();
            }
            catch
            {
                return;
            }

            foreach (DirectoryInfo SubDir in SubDirs)
            {
                TreeViewItem		SubItem=new TreeViewItem();

                SubItem.Header=SubDir.Name;
                SubItem.Tag=SubDir;
                Item.Items.Add(SubItem);

				// Rekurzivne volanie.
                GetSubdirectories(SubItem);
            }
        }
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------