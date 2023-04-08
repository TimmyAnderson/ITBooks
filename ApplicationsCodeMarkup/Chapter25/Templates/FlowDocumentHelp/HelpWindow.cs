using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Navigation;
using System.Xml;
//-------------------------------------------------------------------------------------------------------
namespace FlowDocumentHelp
{
//-------------------------------------------------------------------------------------------------------
	public partial class HelpWindow
	{
//-------------------------------------------------------------------------------------------------------
        public HelpWindow()
        {
            InitializeComponent();

            MTreevue.Focus();
        }
//-------------------------------------------------------------------------------------------------------
        public HelpWindow(string StrTopic)
			: this()
        {
            if (StrTopic != null)
                MFrame.Source=new Uri(StrTopic, UriKind.Relative);
        }
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        private void TreeViewOnSelectedItemChanged(object Sender, RoutedPropertyChangedEventArgs<object> Args)
        {
            if (MTreevue.SelectedValue!=null)
                MFrame.Source=new Uri(MTreevue.SelectedValue as string, UriKind.Relative);
        }
//-------------------------------------------------------------------------------------------------------
        private void FrameOnNavigated(object Sender, NavigationEventArgs Args)
        {
            if (Args.Uri!=null && Args.Uri.OriginalString!=null && Args.Uri.OriginalString.Length>0)
            {
                FindItemToSelect(MTreevue, Args.Uri.OriginalString);
            }
        }
//-------------------------------------------------------------------------------------------------------
        private bool FindItemToSelect(ItemsControl Ctrl, string StrSource)
        {
            foreach (object Obj in Ctrl.Items)
            {
                XmlElement			XML=Obj as XmlElement;
                string				StrAttribute=XML.GetAttribute("Source");
                TreeViewItem		Item=(TreeViewItem) Ctrl.ItemContainerGenerator.ContainerFromItem(Obj);

                if (StrAttribute!=null && StrAttribute.Length>0 && StrSource.EndsWith(StrAttribute)==true)
                {
                    if (Item!=null && Item.IsSelected==false)
                        Item.IsSelected=true;

                    return(true);
                }

                if (Item!=null)
                {
                    bool			IsExpanded=Item.IsExpanded;

                    Item.IsExpanded=true;

                    if (Item.HasItems==true && FindItemToSelect(Item, StrSource)==true)
                        return(true);

                    Item.IsExpanded=IsExpanded;
                }
            }

            return(false);
        }
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------