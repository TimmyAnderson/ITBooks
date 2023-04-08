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
	public class CDirectoryTreeView : TreeView
	{
//------------------------------------------------------------------------------
        public CDirectoryTreeView()
		{
            RefreshTree();
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        internal void RefreshTree()
        {
			// Pozastavim PREKRESLOVANIE TREE.
            BeginInit();

            Items.Clear();

            DriveInfo[]					MyDrives=DriveInfo.GetDrives();

            foreach (DriveInfo Drive in MyDrives)
            {
                char					ChDrive=Drive.Name.ToUpper()[0];
                CDirectoryTreeViewItem	Item=new CDirectoryTreeViewItem(Drive.RootDirectory);

                if (ChDrive!='A' && ChDrive!='B' && Drive.IsReady && Drive.VolumeLabel.Length>0)
                    Item.Text=string.Format("{0} ({1})", Drive.VolumeLabel, Drive.Name);
                else
                    Item.Text=string.Format("{0} ({1})", Drive.DriveType, Drive.Name);

                if (ChDrive=='A' || ChDrive=='B')
                    Item.SelectedImage = Item.UnselectedImage = new BitmapImage(new Uri("pack://application:,,/Images/35FLOPPY.BMP"));

                else if (Drive.DriveType == DriveType.CDRom)
                    Item.SelectedImage = Item.UnselectedImage = new BitmapImage(new Uri("pack://application:,,/Images/CDDRIVE.BMP"));
                else
                    Item.SelectedImage = Item.UnselectedImage = new BitmapImage(new Uri("pack://application:,,/Images/DRIVE.BMP"));
                        
                Items.Add(Item);

                if (ChDrive != 'A' && ChDrive != 'B' && Drive.IsReady)
                    Item.Populate();
            }

			// Znova umoznim PREKRESLOVANIE TREE.
            EndInit();
        }
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------