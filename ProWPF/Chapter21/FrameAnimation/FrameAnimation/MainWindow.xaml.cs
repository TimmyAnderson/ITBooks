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
//------------------------------------------------------------------------
// 1. Program demonstruje pouzitie Frame based animation.
// !!! 2. Ak chcem realizovat Frame based animation musim zaregistrovat odber udalosti CompositionTarget.Rendering.
// !!! 3. CompositionTarget.Rendering je generovana 60 krat za sekundu a ja v nej mozem vykonat custom rendering svojej vlastnej animacie. Ked animacia skonci MAL BY SOM ODREGISTROVAT ODBER UDALOSTI.
// !!!!! 4. CompositionTarget.Rendering je volana AZ PO Layout faze, ale mozem aj v nej menit pozicie Elements a vtedy sa znova spravi znova aj Layout faza.
//------------------------------------------------------------------------
namespace FrameAnimation
{
//------------------------------------------------------------------------
	public partial class MainWindow:System.Windows.Window
	{
//------------------------------------------------------------------------
        private bool					MRendering=false;
        private List<CEllipseInfo>		MEllipses=new List<CEllipseInfo>();
        private double					MAccelerationY=0.1;
        private int						MMinStartingSpeed=1;
        private int						MMaxStartingSpeed=50;
        private double					MSpeedRatio=0.1;
        private int						MMinEllipses=20;
        private int						MMaxEllipses=100;        
        private int						MEllipseRadius=10;
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public MainWindow()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
        private void CmdStart_Clicked(object Sender, RoutedEventArgs E)
        {
            if (MRendering==false)
            {
                MEllipses.Clear();
                MCanvas.Children.Clear();

				// Zaregistrujem odvber udalosti a teraz sa bude CompositionTarget.Rendering volat 60 krat za sekundu.
                CompositionTarget.Rendering+=RenderFrame;
                MRendering=true;
            }
        }
//------------------------------------------------------------------------
        private void CmdStop_Clicked(object Sender, RoutedEventArgs E)
        {
            StopRendering();
        }
//------------------------------------------------------------------------
        private void StopRendering()
        {
			// Konci sa animacia odregistrujem udalost.
            CompositionTarget.Rendering-=RenderFrame;
            MRendering=false;            
        }
//------------------------------------------------------------------------
        private void RenderFrame(object Sender, EventArgs E)
        {
            if (MEllipses.Count==0)
            {
                // Animation just started. Create the ellipses.
                int				HalfCanvasWidth=(int) MCanvas.ActualWidth/2;                
                Random			Rand=new Random();
                int				EllipseCount=Rand.Next(MMinEllipses, MMaxEllipses+1);

                for (int i=0;i<EllipseCount;i++)
                {
                    Ellipse			Ellipse=new Ellipse();

                    Ellipse.Fill=Brushes.LimeGreen;
                    Ellipse.Width=MEllipseRadius;
                    Ellipse.Height=MEllipseRadius;
                    Canvas.SetLeft(Ellipse, HalfCanvasWidth + Rand.Next(-HalfCanvasWidth, HalfCanvasWidth));
                    Canvas.SetTop(Ellipse, 0);
                    MCanvas.Children.Add(Ellipse);

                    CEllipseInfo	Info=new CEllipseInfo(Ellipse, MSpeedRatio*Rand.Next(MMinStartingSpeed, MMaxStartingSpeed));

                    MEllipses.Add(Info);
                }
            }
            else
            {
                for (int i=MEllipses.Count-1;i>=0;i--)                
                {
                    CEllipseInfo				Info=MEllipses[i];
                    double						Top=Canvas.GetTop(Info.Ellipse);

                    Canvas.SetTop(Info.Ellipse, Top+1*Info.VelocityY);                    

                    if (Top>=(MCanvas.ActualHeight-MEllipseRadius*2-10))
                    {
                        // This circle has reached the bottom.
                        // Stop animating it.
                        MEllipses.Remove(Info);
                    }
                    else
                    {
                        // Increase the velocity.
                        Info.VelocityY+=MAccelerationY;
                    }

                    if (MEllipses.Count==0)
                    {
                        // End the animation.
                        // There's no reason to keep calling this method if it has no work to do.
                        StopRendering();
                    }
                }
            }
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------