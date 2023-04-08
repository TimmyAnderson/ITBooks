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
	public class CShowClassHierarchy : Window
	{
//------------------------------------------------------------------------------
        public CShowClassHierarchy()
		{
            Title="Show Class Hierarchy";

            CClassHierarchyTreeView			LTreeView=new CClassHierarchyTreeView(typeof(System.Windows.Threading.DispatcherObject));

            Content=LTreeView;
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------