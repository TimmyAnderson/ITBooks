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
//------------------------------------------------------------------------
namespace CustomButtonControlTemplate
{
//------------------------------------------------------------------------
	public partial class CustomWindowChrome : ResourceDictionary
	{
//------------------------------------------------------------------------
        private bool				MIsResizing=false;
        private ResizeType			MResizeType;
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public CustomWindowChrome()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
        private void Window_InitiateResizeWE(object Sender, MouseEventArgs E)
        {
            MIsResizing=true;
            MResizeType=ResizeType.Width;
        }
//------------------------------------------------------------------------
        private void Window_InitiateResizeNS(object Sender, MouseEventArgs E)
        {
            MIsResizing=true;
            MResizeType=ResizeType.Height;
        }
//------------------------------------------------------------------------
        private void Window_EndResize(object Sender, MouseEventArgs E)
        {
            MIsResizing=false;

            // Make sure capture is released.
            Rectangle				Rect=(Rectangle) Sender;

            Rect.ReleaseMouseCapture();
        }
//------------------------------------------------------------------------
        private void Window_Resize(object Sender, MouseEventArgs E)
        {
            Rectangle				Rect=(Rectangle) Sender;
            Window					Win=(Window) Rect.TemplatedParent;

            if (MIsResizing==true)
            {                
                Rect.CaptureMouse();

                if (MResizeType==ResizeType.Width)
					Win.Width=E.GetPosition(Win).X + 5;
                if (MResizeType==ResizeType.Height)
					Win.Height=E.GetPosition(Win).Y + 5;                 
            }            
        }
//------------------------------------------------------------------------
        private void TitleBar_MouseLeftButtonDown(object Sender, MouseButtonEventArgs E)
        {
            Window					Win=(Window) ((FrameworkElement) Sender).TemplatedParent;

			Win.DragMove();
        }
//------------------------------------------------------------------------
        private void CMDClose_Click(object Sender, RoutedEventArgs E)
        {
            Window					Win=(Window) ((FrameworkElement) Sender).TemplatedParent;

            Win.Close();
        }
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------