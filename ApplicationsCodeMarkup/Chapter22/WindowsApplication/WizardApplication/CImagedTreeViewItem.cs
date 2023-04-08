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
	// CUSTOM TreeViewItem, ktory dokaze sa DYNAMICKY MENIT SVOJU IKONU podla toho ci je, alebo nie je SELECTED.
	public class CImagedTreeViewItem : TreeViewItem
	{
//------------------------------------------------------------------------------
        private TextBlock										MText;
        private Image											MImg;
        private ImageSource										MSrcSelected;
		private ImageSource										MSrcUnselected;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        public CImagedTreeViewItem()
		{
            StackPanel				Stack=new StackPanel();

            Stack.Orientation = Orientation.Horizontal;
            Header=Stack;

            MImg=new Image();
            MImg.VerticalAlignment=VerticalAlignment.Center;
            MImg.Margin=new Thickness(0, 0, 2, 0);
            Stack.Children.Add(MImg);

            MText=new TextBlock();
            MText.VerticalAlignment=VerticalAlignment.Center;
            Stack.Children.Add(MText);
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        public string											Text
        {
            get
			{
				return(MText.Text);
			}
            set
			{
				MText.Text=value;
			}
        }
//------------------------------------------------------------------------------
        public ImageSource										SelectedImage
        {
            get
			{
				return(MSrcSelected);
			}
            set
            {
                MSrcSelected=value;

                if (IsSelected==true)
                    MImg.Source=MSrcSelected;
            }
        }
//------------------------------------------------------------------------------
        public ImageSource										UnselectedImage
        {
            get
			{
				return(MSrcUnselected);
			}
            set
            {
                MSrcUnselected=value;

                if (IsSelected==false)
                    MImg.Source=MSrcUnselected;
            }
        }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        protected override void OnSelected(RoutedEventArgs Args)
        {
            base.OnSelected(Args);
            MImg.Source=MSrcSelected;
        }
//------------------------------------------------------------------------------
        protected override void OnUnselected(RoutedEventArgs args)
        {
            base.OnUnselected(args);
            MImg.Source=MSrcUnselected;
        }
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------