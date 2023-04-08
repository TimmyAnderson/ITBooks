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
	public partial class SimpleAnimation:System.Windows.Window
	{
//------------------------------------------------------------------------
		public SimpleAnimation()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void OnMouseEnter1(object Sender, RoutedEventArgs E)
		{
			DoubleAnimation		WidthAnimation=new DoubleAnimation();

			WidthAnimation.From=160;
			WidthAnimation.To=this.Width-30;
			WidthAnimation.Duration=TimeSpan.FromSeconds(5);
			// Nastavim aby sa animacia reverzovala.
			WidthAnimation.AutoReverse=true;
			MButton1.BeginAnimation(Button.WidthProperty, WidthAnimation);
		}
//------------------------------------------------------------------------
		private void OnMouseEnter2(object Sender, RoutedEventArgs E)
		{
			DoubleAnimation		WidthAnimation=new DoubleAnimation();

			// !!! Nedefinujem From.
			//WidthAnimation.From=160;
			WidthAnimation.To=this.Width-30;
			WidthAnimation.Duration=TimeSpan.FromSeconds(5);
			// Nastavim aby sa animacia reverzovala.
			WidthAnimation.AutoReverse=true;
			MButton2.BeginAnimation(Button.WidthProperty, WidthAnimation);
		}
//------------------------------------------------------------------------
		private void OnMouseEnter3(object Sender, RoutedEventArgs E)
		{
			DoubleAnimation		WidthAnimation=new DoubleAnimation();

			// !!! Spustim normalnu animaciu.
			WidthAnimation.From=160;
			WidthAnimation.To=this.Width-30;
			WidthAnimation.Duration=TimeSpan.FromSeconds(5);
			MButton3.BeginAnimation(Button.WidthProperty, WidthAnimation);
		}
//------------------------------------------------------------------------
		private void OnClick3(object Sender, RoutedEventArgs E)
		{
			DoubleAnimation		WidthAnimation=new DoubleAnimation();

			// !!! Spustim aminaciu bez definovania To.
			// !!! Aplikuje sa to, ze na To sa nastavi hodnota Width bez zmeny ktoru sposobila samotna animacia a teda Element sa zacne zmensovat.
			//WidthAnimation.From=160;
			//WidthAnimation.To=this.Width-30;
			WidthAnimation.Duration=TimeSpan.FromSeconds(5);
			MButton3.BeginAnimation(Button.WidthProperty, WidthAnimation);
		}
//------------------------------------------------------------------------
		private void OnMouseEnter4(object Sender, RoutedEventArgs E)
		{
			DoubleAnimation		WidthAnimation=new DoubleAnimation();

			WidthAnimation.From=160;
			// By robi iba to, ze To=From+By. Je na pouzitie v XAML, kde sa neda robit ani len sucet.
			WidthAnimation.By=50;
			WidthAnimation.Duration=TimeSpan.FromSeconds(5);
			MButton4.BeginAnimation(Button.WidthProperty, WidthAnimation);
		}
//------------------------------------------------------------------------
		private void OnMouseEnter5(object Sender, RoutedEventArgs E)
		{
			DoubleAnimation		WidthAnimation=new DoubleAnimation();

			WidthAnimation.From=160;
			WidthAnimation.To=this.Width-30;
			// Nastavim Duration na Forever. Duration je typu Duration, ale mozem ju nastavit aj cez TimeSpan, lebo EXISTUJE KONVERZNY OPERATOR.
			// Kedze Forever JE NEKONECNO TAK ANIMACIA SA ANI NEROZBEHNE.
			//WidthAnimation.Duration=Duration.Forever;
			// Duration.Automatic je 1 sekunda.
			WidthAnimation.Duration=Duration.Automatic;
			MButton5.BeginAnimation(Button.WidthProperty, WidthAnimation);
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------