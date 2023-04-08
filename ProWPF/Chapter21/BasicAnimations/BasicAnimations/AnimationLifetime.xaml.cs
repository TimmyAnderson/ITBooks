using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;
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
	public partial class AnimationLifetime:System.Windows.Window
	{
		public AnimationLifetime()
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
			MButton1.BeginAnimation(Button.WidthProperty, WidthAnimation);
		}
//------------------------------------------------------------------------
		private void OnClick1(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine(string.Format("MButton1: {0} !",MButton1.Width));
			// !!! HODNOTA SA NEZMENI, LEBO PREBIJE JU HODNOTA To z ANIMACIE.
			MButton1.Width=120;
			Debug.WriteLine(string.Format("MButton1: {0} !",MButton1.Width));
		}
//------------------------------------------------------------------------
		private void OnMouseEnter2(object Sender, RoutedEventArgs E)
		{
			DoubleAnimation		WidthAnimation=new DoubleAnimation();

			WidthAnimation.From=160;
			WidthAnimation.To=this.Width-30;
			WidthAnimation.Duration=TimeSpan.FromSeconds(5);
			MButton2.BeginAnimation(Button.WidthProperty, WidthAnimation);
		}
//------------------------------------------------------------------------
		private void OnClick2(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine(string.Format("MButton2: {0} !",MButton2.Width));
			// !!! Ani ClearValue NEFUNGUJE.
			MButton2.ClearValue(Button.WidthProperty);
			MButton2.Width=120;
			Debug.WriteLine(string.Format("MButton2: {0} !",MButton2.Width));
		}
//------------------------------------------------------------------------
		private void OnMouseEnter3(object Sender, RoutedEventArgs E)
		{
			DoubleAnimation		WidthAnimation=new DoubleAnimation();

			WidthAnimation.From=160;
			WidthAnimation.To=this.Width-30;
			WidthAnimation.Duration=TimeSpan.FromSeconds(5);
			MButton3.BeginAnimation(Button.WidthProperty, WidthAnimation);
		}
//------------------------------------------------------------------------
		private void OnClick3(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine(string.Format("MButton3: {0} !",MButton3.Width));
			MButton3.Width=100;
			Debug.WriteLine(string.Format("MButton3: {0} !",MButton3.Width));
		}
//------------------------------------------------------------------------
		private void OnRightButtonDown3(object Sender, RoutedEventArgs E)
		{
			DoubleAnimation		WidthAnimation=new DoubleAnimation();

			WidthAnimation.From=160;
			// Nenastavim To a tym padom sa hdnota AUTOMATICKY SKOCI NA POVODNU HODNOTU, kedze From==To. POTOM UZ MOZEM ZMENIT HODNOTU DP.
			//WidthAnimation.To=this.Width-30;
			WidthAnimation.Duration=TimeSpan.FromSeconds(5);
			MButton3.BeginAnimation(Button.WidthProperty, WidthAnimation);
		}
//------------------------------------------------------------------------
		private void OnMouseEnter4(object Sender, RoutedEventArgs E)
		{
			DoubleAnimation		WidthAnimation=new DoubleAnimation();

			WidthAnimation.From=160;
			WidthAnimation.To=this.Width-30;
			WidthAnimation.Duration=TimeSpan.FromSeconds(5);
			// Nastavim AutoReverse cim sa hdnota vrati na povodnu ale nastavit hodnotu DP STALE NEMOZEM.
			WidthAnimation.AutoReverse=true;
			MButton4.BeginAnimation(Button.WidthProperty, WidthAnimation);
		}
//------------------------------------------------------------------------
		private void OnClick4(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine(string.Format("MButton4: {0} !",MButton4.Width));
			MButton4.Width=120;
			Debug.WriteLine(string.Format("MButton4: {0} !",MButton4.Width));
		}
//------------------------------------------------------------------------
		private void OnMouseEnter5(object Sender, RoutedEventArgs E)
		{
			DoubleAnimation		WidthAnimation=new DoubleAnimation();

			WidthAnimation.From=160;
			WidthAnimation.To=this.Width-30;
			WidthAnimation.Duration=TimeSpan.FromSeconds(5);
			// Nastavim FillBehavior na Stop, takze po skonceni animacie skoci odnota na From a ZAORVEN SA DA NASTAVIT HODNOTA DP.
			WidthAnimation.FillBehavior=FillBehavior.Stop;
			MButton5.BeginAnimation(Button.WidthProperty, WidthAnimation);
		}
//------------------------------------------------------------------------
		private void OnClick5(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine(string.Format("MButton5: {0} !",MButton5.Width));
			MButton5.Width=120;
			Debug.WriteLine(string.Format("MButton5: {0} !",MButton5.Width));
		}
//------------------------------------------------------------------------
		private void OnMouseEnter6(object Sender, RoutedEventArgs E)
		{
			DoubleAnimation		WidthAnimation=new DoubleAnimation();

			WidthAnimation.From=160;
			WidthAnimation.To=this.Width-30;
			WidthAnimation.Duration=TimeSpan.FromSeconds(5);
			WidthAnimation.Completed+=new EventHandler(WidthAnimation_Completed);
			MButton6.BeginAnimation(Button.WidthProperty, WidthAnimation);
		}
//------------------------------------------------------------------------
		// Vola sa ked skonci animacia.
		private void WidthAnimation_Completed(object Sender, EventArgs E)
		{
			// Zrusim efekt animacie.
			MButton6.BeginAnimation(Button.WidthProperty, null);
		}
//------------------------------------------------------------------------
		private void OnClick6(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine(string.Format("MButton6: {0} !",MButton6.Width));
			MButton6.Width=120;
			Debug.WriteLine(string.Format("MButton6: {0} !",MButton6.Width));
		}
//------------------------------------------------------------------------
		private void OnShowWidth(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine("");
			Debug.WriteLine(string.Format("MButton1: {0} !",MButton1.Width));
			Debug.WriteLine(string.Format("MButton2: {0} !",MButton2.Width));
			Debug.WriteLine(string.Format("MButton3: {0} !",MButton3.Width));
			Debug.WriteLine(string.Format("MButton4: {0} !",MButton4.Width));
			Debug.WriteLine(string.Format("MButton5: {0} !",MButton5.Width));
			Debug.WriteLine(string.Format("MButton6: {0} !",MButton6.Width));
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------