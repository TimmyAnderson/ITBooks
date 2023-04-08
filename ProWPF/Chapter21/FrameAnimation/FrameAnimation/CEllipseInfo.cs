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
namespace FrameAnimation
{
//------------------------------------------------------------------------
    public class CEllipseInfo
    {
//------------------------------------------------------------------------
        private Ellipse						MEllipse;
        private double						MVelocityY;
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
        public CEllipseInfo(Ellipse Ellipse, double VelocityY)
        {
            MVelocityY=VelocityY;
            MEllipse=Ellipse;
        }
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
        public Ellipse						Ellipse
        {
            get
			{
				return(MEllipse);
			}
            set
			{
				MEllipse=value;
			}
        }
//------------------------------------------------------------------------
        public double						VelocityY
        {
            get
			{
				return(MVelocityY);
			}
            set
			{
				MVelocityY=value;
			}
        }
//------------------------------------------------------------------------
    }
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------