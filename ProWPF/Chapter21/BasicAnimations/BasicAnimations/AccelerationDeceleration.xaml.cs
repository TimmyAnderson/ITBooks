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
using System.Windows.Media.Animation;
//------------------------------------------------------------------------
namespace BasicAnimations
{
//------------------------------------------------------------------------
	public partial class AccelerationDeceleration:System.Windows.Window
	{
//------------------------------------------------------------------------
		public AccelerationDeceleration()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
		private void OnMouseEnter1(object Sender, RoutedEventArgs E)
		{
			DoubleAnimation		WidthAnimation=new DoubleAnimation();

			WidthAnimation.From=160;
			WidthAnimation.To=this.Width-30;
			WidthAnimation.Duration=TimeSpan.FromSeconds(3);
			WidthAnimation.AccelerationRatio=0.3;
			MButton1.BeginAnimation(Button.WidthProperty, WidthAnimation);
		}
//------------------------------------------------------------------------
		private void OnMouseEnter2(object Sender, RoutedEventArgs E)
		{
			DoubleAnimation		WidthAnimation=new DoubleAnimation();

			WidthAnimation.From=160;
			WidthAnimation.To=this.Width-30;
			WidthAnimation.Duration=TimeSpan.FromSeconds(3);
			WidthAnimation.DecelerationRatio=0.3;
			MButton2.BeginAnimation(Button.WidthProperty, WidthAnimation);
		}
//------------------------------------------------------------------------
		private void OnMouseEnter3(object Sender, RoutedEventArgs E)
		{
			DoubleAnimation		WidthAnimation=new DoubleAnimation();

			WidthAnimation.From=160;
			WidthAnimation.To=this.Width-30;
			WidthAnimation.Duration=TimeSpan.FromSeconds(3);
			WidthAnimation.AccelerationRatio=0.3;
			WidthAnimation.DecelerationRatio=0.3;
			MButton3.BeginAnimation(Button.WidthProperty, WidthAnimation);
		}
//------------------------------------------------------------------------
		private void OnMouseEnter4(object Sender, RoutedEventArgs E)
		{
			DoubleAnimation		WidthAnimation=new DoubleAnimation();

			WidthAnimation.From=160;
			WidthAnimation.To=this.Width-30;
			WidthAnimation.Duration=TimeSpan.FromSeconds(3);
			WidthAnimation.AccelerationRatio=1;
			MButton4.BeginAnimation(Button.WidthProperty, WidthAnimation);
		}
//------------------------------------------------------------------------
		private void OnMouseEnter5(object Sender, RoutedEventArgs E)
		{
			DoubleAnimation		WidthAnimation=new DoubleAnimation();

			WidthAnimation.From=160;
			WidthAnimation.To=this.Width-30;
			WidthAnimation.Duration=TimeSpan.FromSeconds(3);
			WidthAnimation.DecelerationRatio=1;
			MButton5.BeginAnimation(Button.WidthProperty, WidthAnimation);
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------