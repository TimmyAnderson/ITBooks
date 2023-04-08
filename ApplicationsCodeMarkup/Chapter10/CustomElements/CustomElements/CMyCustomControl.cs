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
using System.Globalization;
//------------------------------------------------------------------------------
namespace CustomElements
{
//------------------------------------------------------------------------------
	// !!! Kedze chcem zobrazovat v ELEMENT i text, tak dedim od Control, ktory ma definovane DP na pracu z fontami.
	public class CMyCustomControl : Control
	{
//------------------------------------------------------------------------------
        public static readonly DependencyProperty	TextProperty;
        public static readonly RoutedEvent			KnockEvent;
        public static readonly RoutedEvent			PreviewKnockEvent;
//------------------------------------------------------------------------------
        private FormattedText						MFormattedText;
		// Obsahuje informaciu ci je mys SKUTOCNE nad CUSTOM ELEMENT.
        private bool								MIsMouseReallyOver;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        static CMyCustomControl()
        {
            TextProperty=DependencyProperty.Register("Text", typeof(string), typeof(CMyCustomControl), new FrameworkPropertyMetadata(" ", FrameworkPropertyMetadataOptions.AffectsMeasure));

            KnockEvent=EventManager.RegisterRoutedEvent("Knock", RoutingStrategy.Bubble, typeof(RoutedEventHandler), typeof(CMyCustomControl));
            PreviewKnockEvent=EventManager.RegisterRoutedEvent("PreviewKnock", RoutingStrategy.Tunnel, typeof(RoutedEventHandler), typeof(CMyCustomControl));
        }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        public string								Text
        {
            set
			{
				SetValue(TextProperty, (value==null) ? " " : value);
			}
            get
			{
				return((string)GetValue(TextProperty));
			}
        }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        public event RoutedEventHandler				Knock
        {
            add
			{
				AddHandler(KnockEvent, value);
			}
            remove
			{
				RemoveHandler(KnockEvent, value);
			}
        }
//------------------------------------------------------------------------------
        public event RoutedEventHandler				PreviewKnock
        {
            add
			{
				AddHandler(PreviewKnockEvent, value);
			}
            remove
			{
				RemoveHandler(PreviewKnockEvent, value);
			}
        }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		// Vypocita plochu, ktoru ELEMENT potrebuje na zobrazenie svojho obsahu.
        protected override Size MeasureOverride(Size SizeAvailable)
        {
			// !!! Pri vytvoreni FormattedText pouzivam DP definovane v Control.
            MFormattedText=new FormattedText(Text, CultureInfo.CurrentCulture, FlowDirection, new Typeface(FontFamily, FontStyle, FontWeight, FontStretch),FontSize, Foreground);

            Size			SizeDesired=new Size(Math.Max(48, MFormattedText.Width) + 4, MFormattedText.Height + 4);

			// Pri vypocte RESPEKTUJEM hodnotu Padding.
            SizeDesired.Width+=Padding.Left + Padding.Right;
            SizeDesired.Height+=Padding.Top + Padding.Bottom;

            return(SizeDesired);
        }
//------------------------------------------------------------------------------
        protected override void OnRender(DrawingContext DC)
        {
            Brush			BrushBackground=SystemColors.ControlBrush;

            if (MIsMouseReallyOver==true && IsMouseCaptured==true)
                BrushBackground=SystemColors.ControlDarkBrush;

			// Ak je MYS NAD ELEMENT, tak pouzijem SIRSI PEN.
            Pen				LPen=new Pen(Foreground, IsMouseOver==true ? 2 : 1);

            // Vykreslim zaobleny obdlznik.
            DC.DrawRoundedRectangle(BrushBackground, LPen, new Rect(new Point(0, 0), RenderSize), 4, 4);

            MFormattedText.SetForegroundBrush(IsEnabled ? Foreground : SystemColors.ControlDarkBrush);

            Point			PTText=new Point(2, 2);
            
			// Pri vypocte pozicie textu sa respektuje hodnota HorizontalContentAlignment.
            switch (HorizontalContentAlignment)
            {
                case HorizontalAlignment.Left:
                    PTText.X+=Padding.Left;
				break;

                case HorizontalAlignment.Right:
                    PTText.X+=RenderSize.Width-MFormattedText.Width-Padding.Right;
                break;

                case HorizontalAlignment.Center:
                case HorizontalAlignment.Stretch:
                    PTText.X+=(RenderSize.Width-MFormattedText.Width-Padding.Left-Padding.Right)/2;
				break;
            }

			// Pri vypocte pozicie textu sa respektuje hodnota VerticalContentAlignment.
            switch (VerticalContentAlignment)
            {
                case VerticalAlignment.Top:
                    PTText.Y+=Padding.Top;
				break;

                case VerticalAlignment.Bottom:
                    PTText.Y+=RenderSize.Height-MFormattedText.Height-Padding.Bottom;
                break;

                case VerticalAlignment.Center:
                case VerticalAlignment.Stretch:
                    PTText.Y+=(RenderSize.Height-MFormattedText.Height-Padding.Top-Padding.Bottom)/2;
                break;
            }

            DC.DrawText(MFormattedText, PTText);
        }
//------------------------------------------------------------------------------
        protected override void OnMouseEnter(MouseEventArgs Args)
        {
            base.OnMouseEnter(Args);
            InvalidateVisual();
        }
//------------------------------------------------------------------------------
        protected override void OnMouseLeave(MouseEventArgs Args)
        {
            base.OnMouseLeave(Args);
            InvalidateVisual();
        }
//------------------------------------------------------------------------------
        protected override void OnMouseMove(MouseEventArgs Args)
        {
            base.OnMouseMove(Args);
			
            Point			PT=Args.GetPosition(this);

            // !!! Ak chcem zisti ci je MYS NAD ELEMENT, tak to musim VYPOCITAT. Bohuzial sa NEDA pouzit metoda IsMouseOver() VTEDY ak JE MOUSE CAPTURED, pretoze VZDY vrati TRUE.
            bool			IsReallyOverNow=(PT.X>=0 && PT.X<ActualWidth && PT.Y>=0 && PT.Y<ActualHeight);

            if (IsReallyOverNow!=MIsMouseReallyOver)
            {
                MIsMouseReallyOver=IsReallyOverNow;
                InvalidateVisual();
            }
        }
//------------------------------------------------------------------------------
        protected override void OnMouseLeftButtonDown(MouseButtonEventArgs Args)
        {
            base.OnMouseLeftButtonDown(Args);
			
			// Zrusim MOUSE CAPTURING.
            CaptureMouse();

            InvalidateVisual();
            Args.Handled=true;
        }
//------------------------------------------------------------------------------
        protected override void OnMouseLeftButtonUp(MouseButtonEventArgs Args)
        {
            base.OnMouseLeftButtonUp(Args);

            if (IsMouseCaptured==true)
            {
                if (MIsMouseReallyOver==true)
                {
                    OnPreviewKnock();
                    OnKnock();
                }

                Args.Handled=true;
                Mouse.Capture(null);
            }
        }
//------------------------------------------------------------------------------
        protected override void OnLostMouseCapture(MouseEventArgs Args)
        {
            base.OnLostMouseCapture(Args);
            InvalidateVisual();
        }
//------------------------------------------------------------------------------
        protected override void OnKeyDown(KeyEventArgs Args)
        {
            base.OnKeyDown(Args);

            if (Args.Key==Key.Space || Args.Key==Key.Enter)
                Args.Handled=true;
        }
//------------------------------------------------------------------------------
        protected override void OnKeyUp(KeyEventArgs Args)
        {
            base.OnKeyUp(Args);

            if (Args.Key==Key.Space || Args.Key==Key.Enter)
            {
                OnPreviewKnock();
                OnKnock();
                Args.Handled=true;
            }
        }
//------------------------------------------------------------------------------
        protected virtual void OnKnock()
        {
            RoutedEventArgs			ArgsEvent=new RoutedEventArgs();

            ArgsEvent.RoutedEvent=CMyCustomControl.PreviewKnockEvent;
            ArgsEvent.Source=this;
            RaiseEvent(ArgsEvent);
        }
//------------------------------------------------------------------------------
        protected virtual void OnPreviewKnock()
        {
            RoutedEventArgs			ArgsEvent=new RoutedEventArgs();

            ArgsEvent.RoutedEvent=CMyCustomControl.KnockEvent;
            ArgsEvent.Source=this;
            RaiseEvent(ArgsEvent);
        }
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------