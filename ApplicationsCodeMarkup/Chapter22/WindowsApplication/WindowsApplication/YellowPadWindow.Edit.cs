using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Ink;
using System.Windows.Input;
//-----------------------------------------------------------------------------------------------------------------
namespace WindowsApplication
{
//-----------------------------------------------------------------------------------------------------------------
	public partial class YellowPadWindow : Window
	{
//-----------------------------------------------------------------------------------------------------------------
        private void EditOnOpened(object Sender, RoutedEventArgs Args)
        {
            MItemFormat.IsEnabled=MInkCanvas.GetSelectedStrokes().Count>0;
        }
//-----------------------------------------------------------------------------------------------------------------
        private void CutCanExecute(object sender, CanExecuteRoutedEventArgs Args)
        {
            Args.CanExecute=MInkCanvas.GetSelectedStrokes().Count>0;
        }
//-----------------------------------------------------------------------------------------------------------------
        private void CutOnExecuted(object Sender, ExecutedRoutedEventArgs Args)
        {
            MInkCanvas.CutSelection();
        }
//-----------------------------------------------------------------------------------------------------------------
        private void CopyOnExecuted(object Sender, ExecutedRoutedEventArgs Args)
        {
            MInkCanvas.CopySelection();
        }
//-----------------------------------------------------------------------------------------------------------------
        private void PasteCanExecute(object Sender, CanExecuteRoutedEventArgs Args)
        {
            Args.CanExecute=MInkCanvas.CanPaste();
        }
//-----------------------------------------------------------------------------------------------------------------
        private void PasteOnExecuted(object Sender, ExecutedRoutedEventArgs Args)
        {
            MInkCanvas.Paste();
        }
//-----------------------------------------------------------------------------------------------------------------
        private void DeleteOnExecuted(object Sender, ExecutedRoutedEventArgs Args)
        {
            foreach (Stroke Strk in MInkCanvas.GetSelectedStrokes())
                MInkCanvas.Strokes.Remove(Strk);
        }
//-----------------------------------------------------------------------------------------------------------------
        private void SelectAllOnExecuted(object Sender, ExecutedRoutedEventArgs Args)
        {
            MInkCanvas.Select(MInkCanvas.Strokes);
        }
//-----------------------------------------------------------------------------------------------------------------
        private void FormatOnClick(object Sender, RoutedEventArgs Args)
        {
            StylusToolDialog		Dlg=new StylusToolDialog();

            Dlg.Owner=this;
            Dlg.Title="Format Selection";

            StrokeCollection		Strokes=MInkCanvas.GetSelectedStrokes();

            if (Strokes.Count>0)
                Dlg.DrawingAttributes=Strokes[0].DrawingAttributes;
            else
                Dlg.DrawingAttributes=MInkCanvas.DefaultDrawingAttributes;

            if (((bool)Dlg.ShowDialog().GetValueOrDefault())==true)
                foreach (Stroke Strk in Strokes)
                    Strk.DrawingAttributes=Dlg.DrawingAttributes;
        }
//-----------------------------------------------------------------------------------------------------------------
	}
//-----------------------------------------------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------------------------------------------