using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Input;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
//------------------------------------------------------------------------------
namespace Decorators
{
//------------------------------------------------------------------------------
	public class CRoundedButton : Control
	{
//------------------------------------------------------------------------------
		// Decorator, ktory ako CHILD pouziva CRoundedButton.
        CRoundedButtonDecorator						MDecorator;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        public static readonly RoutedEvent			ClickEvent;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        static CRoundedButton()
        {
            ClickEvent=EventManager.RegisterRoutedEvent("Click", RoutingStrategy.Bubble, typeof(RoutedEventHandler), typeof(CRoundedButton));
        }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        public CRoundedButton()
        {
            MDecorator=new CRoundedButtonDecorator();

            AddVisualChild(MDecorator);
            AddLogicalChild(MDecorator);
        }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        public UIElement							Child
        {
            get
			{
				return(MDecorator.Child);
			}
            set
			{
				MDecorator.Child=value;
			}
        }
//------------------------------------------------------------------------------
        public bool									IsPressed
        {
            get
			{
				return(MDecorator.IsPressed);
			}
            set
			{
				MDecorator.IsPressed=value;
			}
        }
//------------------------------------------------------------------------------
        public bool IsMouseReallyOver
        {
            get
            {
                Point pt = Mouse.GetPosition(this);
                return (pt.X >= 0 && pt.X < ActualWidth &&
                        pt.Y >= 0 && pt.Y < ActualHeight);
            }
        }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        protected override int						VisualChildrenCount
        {
            get
			{
				return 1;
			}
        }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        public event RoutedEventHandler				Click
        {
            add
			{
				AddHandler(ClickEvent, value);
			}
            remove
			{
				RemoveHandler(ClickEvent, value);
			}
        }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        protected override Visual GetVisualChild(int Index)
        {
            if (Index>0)
                throw(new ArgumentOutOfRangeException("Index"));

            return(MDecorator);
        }
//------------------------------------------------------------------------------
        protected override Size MeasureOverride(Size SizeAvailable)
        {
            MDecorator.Measure(SizeAvailable);

			// Vypocet posielam do Decorator.
            return(MDecorator.DesiredSize);
        }
//------------------------------------------------------------------------------
        protected override Size ArrangeOverride(Size SizeArrange)
        {
            MDecorator.Arrange(new Rect(new Point(0, 0), SizeArrange));

			// Vypocet posielam do Decorator.
            return(SizeArrange);
        }
//------------------------------------------------------------------------------
        protected override void OnMouseMove(MouseEventArgs Args)
        {
            base.OnMouseMove(Args);

            if (IsMouseCaptured==true)
                IsPressed=IsMouseReallyOver;
        }
//------------------------------------------------------------------------------
        protected override void OnMouseLeftButtonDown(MouseButtonEventArgs Args)
        {
            base.OnMouseLeftButtonDown(Args);

            CaptureMouse();
            IsPressed=true;
            Args.Handled=true;
        }
//------------------------------------------------------------------------------
        protected override void OnMouseLeftButtonUp(MouseButtonEventArgs Args)
        {
            base.OnMouseRightButtonUp(Args);

            if (IsMouseCaptured==true)
            {
                if (IsMouseReallyOver==true)
                    OnClick();

                Mouse.Capture(null);
                IsPressed=false;
                Args.Handled=true;
            }
        }
//------------------------------------------------------------------------------
        protected virtual void OnClick()
        {
            RoutedEventArgs			ArgsEvent=new RoutedEventArgs();

            ArgsEvent.RoutedEvent=CRoundedButton.ClickEvent;
            ArgsEvent.Source=this;
            RaiseEvent(ArgsEvent);
        }
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------