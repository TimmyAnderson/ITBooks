using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Ink;
using System.Windows.Media;
//-----------------------------------------------------------------------------------------------------------------
namespace WindowsApplication
{
//-----------------------------------------------------------------------------------------------------------------
	public partial class StylusToolDialog : Window
	{
//-----------------------------------------------------------------------------------------------------------------
        public StylusToolDialog()
        {
            InitializeComponent();

            MTxtboxWidth.TextChanged+=TextBoxOnTextChanged;
            MTxtboxHeight.TextChanged+=TextBoxOnTextChanged;
            MTxtboxAngle.TextChanged+=TextBoxOnTextChanged;

            MTxtboxWidth.Focus();
        }
//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
        public DrawingAttributes								DrawingAttributes
        {
            get 
            {
                DrawingAttributes	DrawAttr=new DrawingAttributes();

                DrawAttr.Height=double.Parse(MTxtboxHeight.Text) / 0.75;
                DrawAttr.Width=double.Parse(MTxtboxWidth.Text) / 0.75;
                DrawAttr.StylusTipTransform=new RotateTransform(double.Parse(MTxtboxAngle.Text)).Value;

                DrawAttr.IgnorePressure=(bool) MChkboxPressure.IsChecked;
                DrawAttr.IsHighlighter=(bool) MChkboxHighlighter.IsChecked;
                DrawAttr.StylusTip=((bool) MRadioEllipse.IsChecked)==true ? StylusTip.Ellipse : StylusTip.Rectangle;

                DrawAttr.Color=MLstboxColor.SelectedColor;

                return(DrawAttr);
            }
            set 
            { 
                MTxtboxHeight.Text=(0.75 * value.Height).ToString("F1");
                MTxtboxWidth.Text=(0.75 * value.Width).ToString("F1");
                MTxtboxAngle.Text=(180 * Math.Acos(value.StylusTipTransform.M11) / Math.PI).ToString("F1");

                MChkboxPressure.IsChecked=value.IgnorePressure;
                MChkboxHighlighter.IsChecked=value.IsHighlighter;

                if (value.StylusTip==StylusTip.Ellipse)
                    MRadioEllipse.IsChecked=true;
                else
                    MRadioRect.IsChecked=true;

                MLstboxColor.SelectedColor=value.Color;
                MLstboxColor.ScrollIntoView(MLstboxColor.SelectedColor);
            }
        }
//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
        private void TextBoxOnTextChanged(object Sender, TextChangedEventArgs Args)
        {
            double			Width;
			double			Height;
			double			Angle;

            MBtnOk.IsEnabled=double.TryParse(MTxtboxWidth.Text, out Width) && Width / 0.75 >= DrawingAttributes.MinWidth && Width / 0.75 <= DrawingAttributes.MaxWidth && Double.TryParse(MTxtboxHeight.Text, out Height) && Height / 0.75 >= DrawingAttributes.MinHeight && Height / 0.75 <= DrawingAttributes.MaxHeight && Double.TryParse(MTxtboxAngle.Text, out Angle);
        }
//-----------------------------------------------------------------------------------------------------------------
        private void OkOnClick(object Sender, RoutedEventArgs Args)
        {
            DialogResult=true;
        }
//-----------------------------------------------------------------------------------------------------------------
	}
//-----------------------------------------------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------------------------------------------