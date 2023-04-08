using System;
using System.Collections.Generic;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.IO;
//------------------------------------------------------------------------
namespace TreeViewTestClient
{
//------------------------------------------------------------------------
	public partial class DiskExplorer:System.Windows.Window
	{
//------------------------------------------------------------------------
		public DiskExplorer()
		{
			InitializeComponent();

			foreach (DriveInfo Drive in DriveInfo.GetDrives())
			{
				TreeViewItem		Item=new TreeViewItem();

				Item.Tag=Drive;
				Item.Header=Drive.ToString();
				// Dam tam placeholder - prazny Content, ktory sa naplna pri otvoreni daneho adresara.
				Item.Items.Add("*");
				MTreeFileSystem.Items.Add(Item);
			}
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void ItemExpanded(object Sender, RoutedEventArgs E)
		{
			TreeViewItem			Item=(TreeViewItem) E.OriginalSource;

			Item.Items.Clear();

			DirectoryInfo			Dir;

			if (Item.Tag is DriveInfo)
			{
				DriveInfo			Drive=(DriveInfo) Item.Tag;

				Dir=Drive.RootDirectory;
			}
			else
			{
				Dir=(DirectoryInfo) Item.Tag;
			}

			try
			{
				foreach (DirectoryInfo SubDir in Dir.GetDirectories())
				{
					TreeViewItem	NewItem=new TreeViewItem();

					NewItem.Tag=SubDir;
					NewItem.Header=SubDir.ToString();
					NewItem.Items.Add("*");
					Item.Items.Add(NewItem);
				}
			}
			catch(Exception Ex)
			{
				MessageBox.Show(Ex.Message,"Exception");
			}
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------