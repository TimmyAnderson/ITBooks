using System;
using System.Reflection;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.IO;
//------------------------------------------------------------------------------
namespace WizardApplication
{
//------------------------------------------------------------------------------
	// CUSTOM TreeViewItem, ktory dokaze sa DYNAMICKY EXPANDOVAT o SUB-DIRECTORIES.
	public class CDirectoryTreeViewItem : CImagedTreeViewItem
	{
//------------------------------------------------------------------------------
        private DirectoryInfo									MDir;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        public CDirectoryTreeViewItem(DirectoryInfo Dir)
		{
            this.MDir=Dir;
            Text=Dir.Name;

            SelectedImage = new BitmapImage(new Uri("pack://application:,,/Images/OPENFOLD.BMP"));
            UnselectedImage=new BitmapImage(new Uri("pack://application:,,/Images/CLSDFOLD.BMP"));
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        public DirectoryInfo									DirectoryInfo
        {
            get
			{
				return(MDir);
			}
        }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        // !!! Na EVENT EXPANDED sa vykona pridanie CHILD NODES do NODES reprezentujucich DIRECTORIES.
        protected override void OnExpanded(RoutedEventArgs Args)
        {
            base.OnExpanded(Args);

            foreach (object Obj in Items)
            {
                CDirectoryTreeViewItem		Item=Obj as CDirectoryTreeViewItem;

                Item.Populate();
            }
        }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        public void Populate()
        {
            DirectoryInfo[]			Dirs;

            try
            {
                Dirs=MDir.GetDirectories();       
            }
            catch
            {
                return;
            }
    
            foreach (DirectoryInfo DirChild in Dirs)
                Items.Add(new CDirectoryTreeViewItem(DirChild));
        }
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------