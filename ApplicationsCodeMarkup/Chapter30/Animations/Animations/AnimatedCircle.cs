using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Media;
using System.Windows.Media.Animation;
//-------------------------------------------------------------------------------------------------------
namespace Animations
{
//-------------------------------------------------------------------------------------------------------
	// Custom FrameworkElement.
	public class AnimatedCircle : FrameworkElement
	{
//-------------------------------------------------------------------------------------------------------
        protected override void OnRender(DrawingContext DC)
        {
            DoubleAnimation			Anima=new DoubleAnimation();

            Anima.From=0;
            Anima.To=100;
            Anima.Duration=new Duration(TimeSpan.FromSeconds(1));
            Anima.AutoReverse=true;
            Anima.RepeatBehavior=RepeatBehavior.Forever;

            AnimationClock			Clock=Anima.CreateClock();

			// Pri kresleni elipsy definujem i jej animaciu.
            DC.DrawEllipse(Brushes.Blue, new Pen(Brushes.Red, 3), new Point(125, 125), null, 0, Clock, 0, Clock);
        }
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------