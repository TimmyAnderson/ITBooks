using System;
using System.Collections.Generic;
using System.Reflection;
using System.Windows;
using System.Windows.Controls;
//------------------------------------------------------------------------------
namespace TreeViewsAndListViews
{
//------------------------------------------------------------------------------
    public class CClassHierarchyTreeView : TreeView
    {
//------------------------------------------------------------------------------
        public CClassHierarchyTreeView(Type TypeRoot)
        {
            UIElement					Dummy=new UIElement();
            List<Assembly>				Assemblies=new List<Assembly>();
            AssemblyName[]				ANames=Assembly.GetExecutingAssembly().GetReferencedAssemblies();

            foreach (AssemblyName AName in ANames)
                Assemblies.Add(Assembly.Load(AName));

            SortedList<string, Type>	Classes = new SortedList<string, Type>();

            Classes.Add(TypeRoot.Name, TypeRoot);

            foreach (Assembly LAssembly in Assemblies)
                foreach (Type Type in LAssembly.GetTypes())
                    if (Type.IsPublic==true && Type.IsSubclassOf(TypeRoot)==true)
                        Classes.Add(Type.Name, Type);
            
            CTypeTreeViewItem			Item=new CTypeTreeViewItem(TypeRoot);

            Items.Add(Item);

            CreateLinkedItems(Item, Classes);
        }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        private void CreateLinkedItems(CTypeTreeViewItem ItemBase, SortedList<string, Type> List)
        {
            foreach (KeyValuePair<string, Type> KVP in List)
			{
                if (KVP.Value.BaseType == ItemBase.Type)
                {
                    CTypeTreeViewItem		Item=new CTypeTreeViewItem(KVP.Value);

                    ItemBase.Items.Add(Item);
                    CreateLinkedItems(Item, List);
                }
			}
        }
//------------------------------------------------------------------------------
    }
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------