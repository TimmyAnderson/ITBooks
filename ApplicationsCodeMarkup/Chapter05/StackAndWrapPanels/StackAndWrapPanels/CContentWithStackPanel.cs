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
namespace StackAndWrapPanels
{
//------------------------------------------------------------------------------
	public class CContentWithStackPanel : Window
	{
//------------------------------------------------------------------------------
		public CContentWithStackPanel()
		{
            Title = "Design a Button";

            Button			Btn=new Button();

            Btn.HorizontalAlignment=HorizontalAlignment.Center;
            Btn.VerticalAlignment=VerticalAlignment.Center;
            Btn.Click+=ButtonOnClick;
            Content=Btn;

            StackPanel		Stack=new StackPanel();

            Btn.Content=Stack;

            Stack.Children.Add(ZigZag(10));

            Uri				Uri=new Uri("pack://application:,,/Images/Book06.ICO");
            BitmapImage		Bitmap=new BitmapImage(Uri);
            Image			Img = new Image();

            Img.Margin=new Thickness(0, 10, 0, 0);
            Img.Source=Bitmap;
            Img.Stretch=Stretch.None;
            Stack.Children.Add(Img);

            Label			Lbl=new Label();

            Lbl.Content="_Read books!";
            Lbl.HorizontalContentAlignment=HorizontalAlignment.Center;
            Stack.Children.Add(Lbl);

            Stack.Children.Add(ZigZag(0));
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        private Polyline ZigZag(int Offset)
        {
            Polyline			Poly=new Polyline();

            Poly.Stroke=SystemColors.ControlTextBrush;
            Poly.Points=new PointCollection();

            for (int x=0;x<=100;x+=10)
                Poly.Points.Add(new Point(x, (x + Offset) % 20));

            return(Poly);
        }
//------------------------------------------------------------------------------
        private void ButtonOnClick(object Sender, RoutedEventArgs Args)
        {
            MessageBox.Show("The button has been clicked !", Title);
        }
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------