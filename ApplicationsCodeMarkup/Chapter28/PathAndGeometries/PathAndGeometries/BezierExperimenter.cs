using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
//-------------------------------------------------------------------------------------------------------
namespace PathAndGeometries
{
//-------------------------------------------------------------------------------------------------------
	public partial class BezierExperimenter : Window
	{
//-------------------------------------------------------------------------------------------------------
        public BezierExperimenter()
        {
            InitializeComponent();
            MCanvas.SizeChanged+=CanvasOnSizeChanged;
        }
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        protected virtual void CanvasOnSizeChanged(object Sender, SizeChangedEventArgs Args)
        {
            MPtStart.Center=new Point(Args.NewSize.Width/4, Args.NewSize.Height/2);
            MPtCtrl1.Center=new Point(Args.NewSize.Width/2, Args.NewSize.Height/4);
            MPtCtrl2.Center=new Point(Args.NewSize.Width/2, 3*Args.NewSize.Height/4);
            MPtEnd.Center=new Point(3*Args.NewSize.Width/4, Args.NewSize.Height/2);
        }
//-------------------------------------------------------------------------------------------------------
        protected override void OnMouseDown(MouseButtonEventArgs Args)
        {
            base.OnMouseDown(Args);

            Point		PT=Args.GetPosition(MCanvas);

            if (Args.ChangedButton==MouseButton.Left)
                MPtCtrl1.Center=PT;

            if (Args.ChangedButton==MouseButton.Right)
                MPtCtrl2.Center=PT;
        }
//-------------------------------------------------------------------------------------------------------
        protected override void OnMouseMove(MouseEventArgs Args)
        {
            base.OnMouseMove(Args);

            Point		PT=Args.GetPosition(MCanvas);

            if (Args.LeftButton==MouseButtonState.Pressed)
                MPtCtrl1.Center=PT;

            if (Args.RightButton==MouseButtonState.Pressed)
                MPtCtrl2.Center=PT;
        }
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------