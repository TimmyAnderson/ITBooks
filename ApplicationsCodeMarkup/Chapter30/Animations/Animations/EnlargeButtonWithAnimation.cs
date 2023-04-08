using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Animation;
//-------------------------------------------------------------------------------------------------------
namespace Animations
{
//-------------------------------------------------------------------------------------------------------
	// Animacia realizovana pomocou WPF ANIMATION.
	public class EnlargeButtonWithAnimation : Window
	{
//-------------------------------------------------------------------------------------------------------
        private const double									MInitFontSize=12;
        private const double									MMaxFontSize=48;
//-------------------------------------------------------------------------------------------------------
        private Button											MBtn;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        public EnlargeButtonWithAnimation()
        {
            Title="Enlarge Button with Animation";

            MBtn=new Button();
            MBtn.Content="Expanding Button";
            MBtn.FontSize=MInitFontSize;
            MBtn.HorizontalAlignment=HorizontalAlignment.Center;
            MBtn.VerticalAlignment=VerticalAlignment.Center;
            MBtn.Click+=ButtonOnClick;
            Content=MBtn;
        }
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        private void ButtonOnClick(object Sender, RoutedEventArgs Args)
        {
            DoubleAnimation			Anima=new DoubleAnimation();

            Anima.Duration=new Duration(TimeSpan.FromSeconds(2));
            Anima.From=MInitFontSize;
            Anima.To=MMaxFontSize;
            Anima.FillBehavior=FillBehavior.Stop;

			// 1. sposob spustenia animacie.
            //MBtn.BeginAnimation(Button.FontSizeProperty, Anima);

			// 2. sposob spustenia animacie.
            MBtn.ApplyAnimationClock(Button.FontSizeProperty, Anima.CreateClock());
        }
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------