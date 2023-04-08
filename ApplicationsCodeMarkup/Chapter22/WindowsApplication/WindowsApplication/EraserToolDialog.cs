using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Ink;
//-----------------------------------------------------------------------------------------------------------------
namespace WindowsApplication
{
//-----------------------------------------------------------------------------------------------------------------
	public class EraserToolDialog : StylusToolDialog
	{
//-----------------------------------------------------------------------------------------------------------------
        public EraserToolDialog()
        {
            Title="Eraser Tool";

            MChkboxPressure.Visibility=Visibility.Collapsed;
            MChkboxHighlighter.Visibility=Visibility.Collapsed;
            MLstboxColor.Visibility=Visibility.Collapsed;
        }
//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
        public StylusShape										EraserShape
        {
            get
            {
                StylusShape		Eraser;
                double			Width=double.Parse(MTxtboxWidth.Text)/0.75;
                double			Height=double.Parse(MTxtboxHeight.Text)/0.75;
                double			Angle=double.Parse(MTxtboxAngle.Text);

                if (((bool) MRadioEllipse.IsChecked)==true)
                    Eraser=new EllipseStylusShape(Width, Height, Angle);
                else
                    Eraser=new RectangleStylusShape(Width, Height, Angle);

                return(Eraser);
            }
            set
            {
                MTxtboxHeight.Text=(0.75*value.Height).ToString("F1");
                MTxtboxWidth.Text=(0.75*value.Width).ToString("F1");
                MTxtboxAngle.Text=value.Rotation.ToString();

                if ((value is EllipseStylusShape)==true)
                    MRadioEllipse.IsChecked=true;
                else
                    MRadioRect.IsChecked=true;
            }
        }
//-----------------------------------------------------------------------------------------------------------------
	}
//-----------------------------------------------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------------------------------------------