using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Windows;
using System.Windows.Ink;
using System.Windows.Input;
using System.Windows.Markup;
using System.Windows.Media;
using Microsoft.Win32;
//-----------------------------------------------------------------------------------------------------------------
namespace WindowsApplication
{
//-----------------------------------------------------------------------------------------------------------------
	public partial class YellowPadWindow : Window
	{
//-----------------------------------------------------------------------------------------------------------------
        private void NewOnExecuted(object Sender, ExecutedRoutedEventArgs Args)
        {
            MInkCanvas.Strokes.Clear();
        }
//-----------------------------------------------------------------------------------------------------------------
        private void OpenOnExecuted(object Sender, ExecutedRoutedEventArgs Args)
        {
            OpenFileDialog			Dlg=new OpenFileDialog();

            Dlg.CheckFileExists=true;
            Dlg.Filter="Ink Serialized Format (*.isf)|*.isf| All files (*.*)|*.*";

            if (((bool)Dlg.ShowDialog(this))==true)
            {
                try
                {
                    FileStream		File=new FileStream(Dlg.FileName, FileMode.Open, FileAccess.Read);

					// Nacitam StrokeCollection z File.
                    MInkCanvas.Strokes=new StrokeCollection(File);

                    File.Close();
                }
                catch(Exception Exc)
                {
                    MessageBox.Show(Exc.Message, Title);
                }
            }
        }
//-----------------------------------------------------------------------------------------------------------------
        private void SaveOnExecuted(object Sender, ExecutedRoutedEventArgs Args)
        {
            SaveFileDialog				Dlg=new SaveFileDialog();

            Dlg.Filter = "Ink Serialized Format (*.isf)|*.isf|XAML Drawing File (*.xaml)|*.xaml|All files (*.*)|*.*";

            if (((bool)Dlg.ShowDialog(this))==true)
            {
                try
                {
                    FileStream			File=new FileStream(Dlg.FileName, FileMode.Create, FileAccess.Write);
					
					// Ak pouzivam .ISF format tak ho ulozim pomocou Strokes metody Strokes.Save().
                    if (Dlg.FilterIndex==1 || Dlg.FilterIndex==3)
                        MInkCanvas.Strokes.Save(File);
                    else
                    {
						// Ak ukladam Strokes ako XAML vyuzijem to, ze KAZDY STROKE vracia pomocou GetGeometry() svoju Geometry a tak ich mozem cez DrawingGroup spojit do jedneho XAML s vektorou grafikou.
                        DrawingGroup	LDrawGroup=new DrawingGroup();

                        foreach (Stroke Strk in MInkCanvas.Strokes)
                        {
                            Color		Clr=Strk.DrawingAttributes.Color;

                            if (Strk.DrawingAttributes.IsHighlighter)
                                Clr=Color.FromArgb(128, Clr.R, Clr.G, Clr.B);

                            LDrawGroup.Children.Add(new GeometryDrawing(new SolidColorBrush(Clr),null, Strk.GetGeometry()));
                        }

                        XamlWriter.Save(LDrawGroup, File);
                    }

                    File.Close();
                }
                catch (Exception Exc)
                {
                    MessageBox.Show(Exc.Message, Title);
                }
            }
        }
//-----------------------------------------------------------------------------------------------------------------
        private void CloseOnExecuted(object Sender, ExecutedRoutedEventArgs Args)
        {
            Close();
        }
//-----------------------------------------------------------------------------------------------------------------
	}
//-----------------------------------------------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------------------------------------------