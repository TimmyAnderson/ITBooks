using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Threading;
//------------------------------------------------------------------------------
namespace BrushTests
{
//------------------------------------------------------------------------------
	public class CRotateTheGradientOrigin : Window
	{
//------------------------------------------------------------------------------
        private RadialGradientBrush					MBrush;
        private double								MAngle;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        public CRotateTheGradientOrigin()
        {
            Title="Rotate the Gradient Origin";
            WindowStartupLocation=WindowStartupLocation.CenterScreen;
            Width=384;
            Height=384;

            MBrush=new RadialGradientBrush(Colors.White, Colors.Blue);
            MBrush.Center=MBrush.GradientOrigin=new Point(0.5, 0.5);
            MBrush.RadiusX=MBrush.RadiusY=0.10;
            MBrush.SpreadMethod=GradientSpreadMethod.Repeat;
            Background=MBrush;

            DispatcherTimer			Tmr=new DispatcherTimer();

            Tmr.Interval=TimeSpan.FromMilliseconds(100);
            Tmr.Tick+=TimerOnTick;
            Tmr.Start();
        }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        private void TimerOnTick(object sender, EventArgs args)
        {
            Point			PT=new Point(0.5+(0.05*Math.Cos(MAngle)), 0.5+(0.05*Math.Sin(MAngle)));

            MBrush.GradientOrigin=PT;
            MAngle+=Math.PI/6;
        }
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------