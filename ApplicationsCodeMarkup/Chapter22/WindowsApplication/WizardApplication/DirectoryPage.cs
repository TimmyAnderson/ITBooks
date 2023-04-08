using System;
using System.IO;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Navigation;
//-----------------------------------------------------------------------------------------------------------------
namespace WizardApplication
{
//-----------------------------------------------------------------------------------------------------------------
	// Navratova hodnota z PageFunction je DirectoryInfo.
    public partial class DirectoryPage : PageFunction<DirectoryInfo>
    {
//-----------------------------------------------------------------------------------------------------------------
        public DirectoryPage()
        {
            InitializeComponent();

            MTreeView.SelectedItemChanged+=TreeViewOnSelectedItemChanged;
        }
//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
        private void TreeViewOnSelectedItemChanged(object Sender, RoutedPropertyChangedEventArgs<object> Args)
        {
            MBtnOk.IsEnabled=(Args.NewValue!=null);
        }
//-----------------------------------------------------------------------------------------------------------------
        private void CancelButtonOnClick(object Sender, RoutedEventArgs Args)
        {
			// Pri CANCEL neprenesiem ZIADNU NAVRATOVU HODNOTU.
            OnReturn(new ReturnEventArgs<DirectoryInfo>());
        }
//-----------------------------------------------------------------------------------------------------------------
        private void OkButtonOnClick(object Sender, RoutedEventArgs Args)
        {
            DirectoryInfo		DirInfo=(MTreeView.SelectedItem as CDirectoryTreeViewItem).DirectoryInfo;

			// Volanie OnReturn() ukonci PageFunction a preda navratovu hodnotu do PAGE, ktora PageFunction volala.
			OnReturn(new ReturnEventArgs<DirectoryInfo>(DirInfo));
        }
//-----------------------------------------------------------------------------------------------------------------
    }
//-----------------------------------------------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------------------------------------------