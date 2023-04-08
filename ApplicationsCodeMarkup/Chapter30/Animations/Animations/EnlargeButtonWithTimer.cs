using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Threading;
//-------------------------------------------------------------------------------------------------------
namespace Animations
{
//-------------------------------------------------------------------------------------------------------
	// Animacia realizovana pomocou DispatcherTimer.
	public class EnlargeButtonWithTimer : Window
	{
//-------------------------------------------------------------------------------------------------------
        private const double									MInitFontSize=12;
        private const double									MMaxFontSize=48;
//-------------------------------------------------------------------------------------------------------
        private Button											MBtn;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        public EnlargeButtonWithTimer()
        {
            Title="Enlarge Button with Timer";

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
			// Vytvorim DispatcherTimer.
            DispatcherTimer			Tmr=new DispatcherTimer();

            Tmr.Interval=TimeSpan.FromSeconds(0.1);
            Tmr.Tick+=TimerOnTick;

			// Spustim animaciu.
            Tmr.Start();
        }
//-------------------------------------------------------------------------------------------------------
        private void TimerOnTick(object Sender, EventArgs Args)
        {
            MBtn.FontSize+=2;

            if (MBtn.FontSize>=MMaxFontSize)
            {
                MBtn.FontSize=MInitFontSize;

				// Zastavim animaciu.
                (Sender as DispatcherTimer).Stop();
            }
        }
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------