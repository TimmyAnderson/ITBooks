using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.Windows.Markup;
using System.IO;
using Microsoft.Win32;
//------------------------------------------------------------------------
namespace RichTextBoxTest
{
//------------------------------------------------------------------------
	public partial class LoadSaveTest:Window
	{
//------------------------------------------------------------------------
		public LoadSaveTest()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void Button_Click1(object Sender, RoutedEventArgs E)
		{
			OpenFileDialog			OpenFile=new OpenFileDialog();

			OpenFile.Filter="XAML Files (*.xaml)|*.xaml|All Files (*.*)|*.*";

			if (OpenFile.ShowDialog()==true)
			{
				using (FileStream FS=File.Open(OpenFile.FileName, FileMode.Open))
				{
					FlowDocument	Document=XamlReader.Load(FS) as FlowDocument;

					if (Document==null)
					{
						MessageBox.Show("Problem loading document.");
					}
					else
					{
						MRichTextBox.Document=Document;
					}
				}
			}
		}
//------------------------------------------------------------------------
		private void Button_Click2(object Sender, RoutedEventArgs E)
		{
			SaveFileDialog		SaveFile=new SaveFileDialog();
		
			SaveFile.Filter="XAML Files (*.xaml)|*.xaml|All Files (*.*)|*.*";

			if (SaveFile.ShowDialog()==true)
			{
				using (FileStream FS=File.Open(SaveFile.FileName, FileMode.Create))
				{
					XamlWriter.Save(MRichTextBox.Document, FS);
				}
			}
		}
//------------------------------------------------------------------------
		private void Button_Click3(object Sender, RoutedEventArgs E)
		{
			OpenFileDialog		OpenFile=new OpenFileDialog();

			OpenFile.Filter="XAML Files (*.xaml)|*.xaml|All Files (*.*)|*.*";

			if (OpenFile.ShowDialog()==true)
			{
				TextRange		DocumentTextRange=new TextRange(MRichTextBox.Document.ContentStart, MRichTextBox.Document.ContentEnd);

				using (FileStream FS=File.Open(OpenFile.FileName, FileMode.Open))
				{
					DocumentTextRange.Load(FS, DataFormats.Xaml);
				}
			}
		}
//------------------------------------------------------------------------
		private void Button_Click4(object Sender, RoutedEventArgs E)
		{
			SaveFileDialog		SaveFile=new SaveFileDialog();
		
			SaveFile.Filter="XAML Files (*.xaml)|*.xaml|All Files (*.*)|*.*";

			if (SaveFile.ShowDialog()==true)
			{
				// Create a TextRange around the entire document.
				TextRange		DocumentTextRange=new TextRange(MRichTextBox.Document.ContentStart, MRichTextBox.Document.ContentEnd);

				// If this file exists, it's overwritten.
				using (FileStream FS=File.Create(SaveFile.FileName))
				{
					DocumentTextRange.Save(FS, DataFormats.Xaml);
				}
			}
		}
//------------------------------------------------------------------------
		private void Button_Click5(object Sender, RoutedEventArgs E)
		{
			OpenFileDialog		OpenFile=new OpenFileDialog();

			OpenFile.Filter="RichText Files (*.rtf)|*.rtf|All Files (*.*)|*.*";

			if (OpenFile.ShowDialog()==true)
			{
				TextRange		DocumentTextRange=new TextRange(MRichTextBox.Document.ContentStart, MRichTextBox.Document.ContentEnd);

				using (FileStream FS=File.Open(OpenFile.FileName, FileMode.Open))
				{
					DocumentTextRange.Load(FS, DataFormats.Rtf);
				}
			}
		}
//------------------------------------------------------------------------
		private void Button_Click6(object Sender, RoutedEventArgs E)
		{
			SaveFileDialog		SaveFile=new SaveFileDialog();
		
			SaveFile.Filter="RichText Files (*.rtf)|*.rtf|All Files (*.*)|*.*";

			if (SaveFile.ShowDialog()==true)
			{
				// Create a TextRange around the entire document.
				TextRange		DocumentTextRange=new TextRange(MRichTextBox.Document.ContentStart, MRichTextBox.Document.ContentEnd);

				// If this file exists, it's overwritten.
				using (FileStream FS=File.Create(SaveFile.FileName))
				{
					DocumentTextRange.Save(FS, DataFormats.Rtf);
				}
			}
		}
//------------------------------------------------------------------------
		private void Button_Click7(object Sender, RoutedEventArgs E)
		{
			OpenFileDialog		OpenFile=new OpenFileDialog();

			OpenFile.Filter="XAML Files (*.xaml)|*.xaml|All Files (*.*)|*.*";

			if (OpenFile.ShowDialog()==true)
			{
				TextRange		DocumentTextRange=new TextRange(MRichTextBox.Document.ContentStart, MRichTextBox.Document.ContentEnd);

				using (FileStream FS=File.Open(OpenFile.FileName, FileMode.Open))
				{
					DocumentTextRange.Load(FS, DataFormats.XamlPackage);
				}
			}
		}
//------------------------------------------------------------------------
		private void Button_Click8(object Sender, RoutedEventArgs E)
		{
			SaveFileDialog		SaveFile=new SaveFileDialog();
		
			SaveFile.Filter="XAML Files (*.xaml)|*.xaml|All Files (*.*)|*.*";

			if (SaveFile.ShowDialog()==true)
			{
				// Create a TextRange around the entire document.
				TextRange		DocumentTextRange=new TextRange(MRichTextBox.Document.ContentStart, MRichTextBox.Document.ContentEnd);

				// If this file exists, it's overwritten.
				using (FileStream FS=File.Create(SaveFile.FileName))
				{
					DocumentTextRange.Save(FS, DataFormats.XamlPackage);
				}
			}
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------