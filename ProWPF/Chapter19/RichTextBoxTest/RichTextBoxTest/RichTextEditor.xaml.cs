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
using System.IO;
using Microsoft.Win32;
//------------------------------------------------------------------------
namespace RichTextBoxTest
{
//------------------------------------------------------------------------
	public partial class RichTextEditor:Window
	{
//------------------------------------------------------------------------
		public RichTextEditor()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
        private void CmdBold_Click(object Sender, RoutedEventArgs E)
        {
            if (MRichTextBox.Selection.Text=="")
            {
                FontWeight		FontWeight=MRichTextBox.Selection.Start.Paragraph.FontWeight;

                if (FontWeight==FontWeights.Bold)
                    FontWeight=FontWeights.Normal;
                else
                    FontWeight=FontWeights.Bold;

                MRichTextBox.Selection.Start.Paragraph.FontWeight=FontWeight;
                return;
            }
          
            Object				Obj=MRichTextBox.Selection.GetPropertyValue(TextElement.FontWeightProperty);

            if (Obj==DependencyProperty.UnsetValue)
            {
                TextRange		Range=new TextRange(MRichTextBox.Selection.Start, MRichTextBox.Selection.Start);

                MessageBox.Show(Range.GetPropertyValue(TextElement.FontWeightProperty).ToString());
            }
            else
            {
                FontWeight		FontWeight=(FontWeight) Obj;

                if (FontWeight==FontWeights.Bold)
                    FontWeight=FontWeights.Normal;
                else
                    FontWeight=FontWeights.Bold;

                MRichTextBox.Selection.ApplyPropertyValue(TextElement.FontWeightProperty, FontWeight);
            }            
        }
//------------------------------------------------------------------------
        private void CmdShowXAML_Click(object Sender, RoutedEventArgs E)
        {
            UpdateMarkupDisplay();
        }
//------------------------------------------------------------------------
        private void UpdateMarkupDisplay()
        {
            TextRange			Range;

            Range=new TextRange(MRichTextBox.Document.ContentStart, MRichTextBox.Document.ContentEnd);
            
            MemoryStream		Stream=new MemoryStream();

            Range.Save(Stream, DataFormats.Xaml);
            Stream.Position=0;

            StreamReader		R=new StreamReader(Stream);

            MTxtFlowDocumentMarkup.Text=R.ReadToEnd();
            R.Close();
            Stream.Close();
        }
//------------------------------------------------------------------------
        private void CmdOpen_Click(object Sender, RoutedEventArgs E)
        {             
            OpenFileDialog		OpenFile=new OpenFileDialog();

            OpenFile.Filter = "XAML Files (*.xaml)|*.xaml|RichText Files (*.rtf)|*.rtf|All Files (*.*)|*.*";

            if (OpenFile.ShowDialog()==true)
            {
                // Create a TextRange around the entire document.
                TextRange		DocumentTextRange=new TextRange(MRichTextBox.Document.ContentStart, MRichTextBox.Document.ContentEnd);
                                
                using (FileStream FS=File.Open(OpenFile.FileName, FileMode.Open))
                {
                    if (Path.GetExtension(OpenFile.FileName).ToLower()==".rtf")
                    {
                        DocumentTextRange.Load(FS, DataFormats.Rtf);
                    }
                    else
                    {
                        DocumentTextRange.Load(FS, DataFormats.Xaml);
                    }
                }
            }
        }
//------------------------------------------------------------------------
        private void CmdSave_Click(object Sender, RoutedEventArgs E)
        {
            SaveFileDialog		SaveFile=new SaveFileDialog();

            SaveFile.Filter = "XAML Files (*.xaml)|*.xaml|RichText Files (*.rtf)|*.rtf|All Files (*.*)|*.*";
                        
            if (SaveFile.ShowDialog() == true)
            {
                // Create a TextRange around the entire document.
                TextRange		DocumentTextRange=new TextRange(MRichTextBox.Document.ContentStart, MRichTextBox.Document.ContentEnd);

                // If this file exists, it's overwritten.
                using (FileStream FS=File.Create(SaveFile.FileName))
                {
                    if (Path.GetExtension(SaveFile.FileName).ToLower()==".rtf")
                    {
                        DocumentTextRange.Save(FS, DataFormats.Rtf);
                    }
                    else
                    {
                        DocumentTextRange.Save(FS, DataFormats.Xaml);
                    }
                }
            }
        }
//------------------------------------------------------------------------
        private void CmdNew_Click(object Sender, RoutedEventArgs E)
        {
            MRichTextBox.Document=new FlowDocument();
        }
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
        protected void RichTextBox_MouseDown(object Sender, MouseEventArgs E)
        {
            if (E.RightButton==MouseButtonState.Pressed)
            {
				TextPointer			Location=MRichTextBox.GetPositionFromPoint(Mouse.GetPosition(MRichTextBox), true);
				TextRange			Word=CWordBreaker.GetWordRange(Location);
            
				MTxtFlowDocumentMarkup.Text=Word.Text;
            }
        }
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------