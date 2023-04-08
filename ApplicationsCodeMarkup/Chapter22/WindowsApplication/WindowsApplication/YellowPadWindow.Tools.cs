using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
//-----------------------------------------------------------------------------------------------------------------
namespace WindowsApplication
{
//-----------------------------------------------------------------------------------------------------------------
	public partial class YellowPadWindow : Window
	{
//-----------------------------------------------------------------------------------------------------------------
        private void StylusToolOnClick(object Sender, RoutedEventArgs Args)
        {
            StylusToolDialog		Dlg=new StylusToolDialog();

            Dlg.Owner=this;
            Dlg.DrawingAttributes=MInkCanvas.DefaultDrawingAttributes;

            if (((bool)Dlg.ShowDialog().GetValueOrDefault())==true)
                MInkCanvas.DefaultDrawingAttributes=Dlg.DrawingAttributes;
        }
//-----------------------------------------------------------------------------------------------------------------
        private void EraserToolOnClick(object Sender, RoutedEventArgs Args)
        {
            EraserToolDialog		Dlg=new EraserToolDialog();

            Dlg.Owner=this;
            Dlg.EraserShape=MInkCanvas.EraserShape;

            if (((bool)Dlg.ShowDialog().GetValueOrDefault())==true)
                MInkCanvas.EraserShape=Dlg.EraserShape;
        }
//-----------------------------------------------------------------------------------------------------------------
	}
//-----------------------------------------------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------------------------------------------