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
	public partial class SimultaneousAnimations:System.Windows.Window
	{
//------------------------------------------------------------------------
		public SimultaneousAnimations()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
		private void OnMouseEnter(object Sender, RoutedEventArgs E)
		{
			DoubleAnimation		WidthAnimation=new DoubleAnimation();

			WidthAnimation.From=160;
			WidthAnimation.To=this.Width-30;
			WidthAnimation.Duration=TimeSpan.FromSeconds(5);
			WidthAnimation.AutoReverse=true;
			MButton.BeginAnimation(Button.WidthProperty, WidthAnimation);


			DoubleAnimation		HeightAnimation=new DoubleAnimation();

			HeightAnimation.From=40;
			HeightAnimation.To=this.Height-50;
			HeightAnimation.Duration=TimeSpan.FromSeconds(5);
			HeightAnimation.AutoReverse=true;
			MButton.BeginAnimation(Button.HeightProperty, HeightAnimation);
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------