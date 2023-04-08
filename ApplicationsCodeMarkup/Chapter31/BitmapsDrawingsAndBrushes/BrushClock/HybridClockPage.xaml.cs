using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
//-------------------------------------------------------------------------------------------------------
namespace BrushClock
{
//-------------------------------------------------------------------------------------------------------
	public partial class HybridClockPage:Page
	{
//-------------------------------------------------------------------------------------------------------
        public static readonly Color							MClrBackground=Colors.Aqua;
        public static readonly Brush							MBrushBackground=Brushes.Aqua;
//-------------------------------------------------------------------------------------------------------
        private TranslateTransform[]							MXForm=new TranslateTransform[60];
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public HybridClockPage()
		{
			InitializeComponent();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        private void WindowOnLoaded(object Sender, EventArgs Args)
        {
            for (int i = 0; i < 60; i++)
            {
                Ellipse				Elips=new Ellipse();

                Elips.HorizontalAlignment=HorizontalAlignment.Center;
                Elips.VerticalAlignment=VerticalAlignment.Center;
                Elips.Fill=Brushes.Blue;
                Elips.Width=Elips.Height=((i%5)==0) ? 6 : 2;

                TransformGroup		Group=new TransformGroup();

                Group.Children.Add(MXForm[i]=new TranslateTransform(MDatetime.ActualWidth, 0));
                Group.Children.Add(new TranslateTransform(MGrd.Margin.Left/2, 0));
                Group.Children.Add(new TranslateTransform(-Elips.Width/2, -Elips.Height/2));
                Group.Children.Add(new RotateTransform(i*6));
                Group.Children.Add(new TranslateTransform(Elips.Width/2, Elips.Height/2));

                Elips.RenderTransform=Group;
                MGrd.Children.Add(Elips);
            }

			MakeMask();

            MDatetime.SizeChanged+=DateTimeOnSizeChanged;
        }
//-------------------------------------------------------------------------------------------------------
        private void DateTimeOnSizeChanged(object Sender, SizeChangedEventArgs Args)
        {
            if (Args.WidthChanged==true)
            {
                for (int i=0;i<60;i++)
                    MXForm[i].X=MDatetime.ActualWidth;

               MakeMask();
            }
        }
//-------------------------------------------------------------------------------------------------------
        private void MakeMask()
        {
            DrawingGroup				MGroup=new DrawingGroup();
            Point						PTCenter=new Point(MDatetime.ActualWidth+MGrd.Margin.Left, MDatetime.ActualWidth+MGrd.Margin.Left);

            for (int i=0;i<256;i++)
            {
                Point					PTInner1=new Point(PTCenter.X+MDatetime.ActualWidth*Math.Cos(i*2*Math.PI/256),PTCenter.Y+MDatetime.ActualWidth*Math.Sin(i*2*Math.PI/256));
                Point					PTInner2=new Point(PTCenter.X+MDatetime.ActualWidth*Math.Cos((i+2)*2*Math.PI/256),PTCenter.Y+MDatetime.ActualWidth*Math.Sin((i+2)*2*Math.PI/256));
                Point					PTOuter1=new Point(PTCenter.X+(MDatetime.ActualWidth+MGrd.Margin.Left)*Math.Cos(i*2*Math.PI/256),PTCenter.Y+(MDatetime.ActualWidth+MGrd.Margin.Left)*Math.Sin(i*2*Math.PI/256));
                Point					PTOuter2=new Point(PTCenter.X+(MDatetime.ActualWidth+MGrd.Margin.Left)*Math.Cos((i+2)*2*Math.PI/256),PTCenter.Y+(MDatetime.ActualWidth+MGrd.Margin.Left)*Math.Sin((i+2)*2*Math.PI/256));
                PathSegmentCollection	Segcoll=new PathSegmentCollection();

                Segcoll.Add(new LineSegment(PTInner2, false));
                Segcoll.Add(new LineSegment(PTOuter2, false));
                Segcoll.Add(new LineSegment(PTOuter1, false));
                Segcoll.Add(new LineSegment(PTInner1, false));

                PathFigure				Fig=new PathFigure(PTInner1, Segcoll, true);
                PathFigureCollection	Figcoll=new PathFigureCollection();

                Figcoll.Add(Fig);

                PathGeometry			Path=new PathGeometry(Figcoll);
                byte					ByOpacity=(byte)Math.Min(255, 512-(2*i));
                SolidColorBrush			BR=new SolidColorBrush(Color.FromArgb(ByOpacity, MClrBackground.R, MClrBackground.G, MClrBackground.B));
                GeometryDrawing			Draw=new GeometryDrawing(BR, new Pen(BR, 2), Path);

                MGroup.Children.Add(Draw);
            }

            DrawingBrush				Brush=new DrawingBrush(MGroup);

            MMask.Fill=Brush;
        }
//-------------------------------------------------------------------------------------------------------
        private void ContextMenuOnOpened(object Sender, RoutedEventArgs Args)
        {
            ContextMenu					Menu=Sender as ContextMenu;

            Menu.Items.Clear();

            string[]					StrFormats={ "d", "D", "f", "F", "g", "G", "M", "R", "s", "t", "T", "u", "U", "Y" };

            foreach (string StrFormat in StrFormats)
            {
                MenuItem				Item=new MenuItem();

                Item.Header=DateTime.Now.ToString(StrFormat);
                Item.Tag=StrFormat;
                Item.IsChecked=(StrFormat==(Resources["clock"] as ClockTicker).Format);
                Item.Click+=MenuItemOnClick;
                Menu.Items.Add(Item);
            }
        }
//-------------------------------------------------------------------------------------------------------
        private void MenuItemOnClick(object Sender, RoutedEventArgs Args)
        {
            MenuItem					Item=(Sender as MenuItem);

            (Resources["clock"] as ClockTicker).Format=Item.Tag as string;
        }
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------