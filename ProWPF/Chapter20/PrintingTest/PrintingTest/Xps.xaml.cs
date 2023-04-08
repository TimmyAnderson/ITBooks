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
using System.Windows.Xps.Packaging;
using System.IO;
using System.Windows.Markup;
using System.Windows.Xps;
using System.Printing;
using System.IO.Packaging;
//------------------------------------------------------------------------
namespace PrintingTest
{
//------------------------------------------------------------------------
	public partial class Xps:Window
	{
//------------------------------------------------------------------------
        private PrintDialog			MPrintDialog=new PrintDialog();
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public Xps()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
        private void Window_Loaded(object Sender, EventArgs E)
        {            
            XpsDocument				Doc=new XpsDocument("..\\..\\Store\\Test.xps", FileAccess.ReadWrite);

            MDocViewer.Document=Doc.GetFixedDocumentSequence();
            Doc.Close();
        }
//------------------------------------------------------------------------
        private void CmdPrintXps_Click(object Sender, RoutedEventArgs E)
        {
            if (MPrintDialog.ShowDialog() == true)
            {
                MPrintDialog.PrintDocument(MDocViewer.Document.DocumentPaginator, "A Fixed Document");
            }
        }
//------------------------------------------------------------------------
        private void CmdPrintFlow_Click(object Sender, RoutedEventArgs E)
        {
            string					FilePath=System.IO.Path.Combine(Directory.GetCurrentDirectory(), "..\\..\\Store\\FlowDocument.xaml");

            if (MPrintDialog.ShowDialog()==true)
            {
                PrintQueue			Queue=MPrintDialog.PrintQueue;
                XpsDocumentWriter	Writer=PrintQueue.CreateXpsDocumentWriter(Queue);

                using (FileStream FS=File.Open(FilePath, FileMode.Open))
                {
                    FlowDocument	FlowDocument=(FlowDocument) XamlReader.Load(FS);

                    Writer.Write(((IDocumentPaginatorSource) FlowDocument).DocumentPaginator);
                }
            }
        }
//------------------------------------------------------------------------
        private void CmdShowFlow_Click(object Sender, RoutedEventArgs E)
        {
            if (File.Exists("..\\..\\Store\\Test2.xps"))
				File.Delete("..\\..\\Store\\Test2.xps");

            using (FileStream FS=File.Open("..\\..\\Store\\FlowDocument.xaml", FileMode.Open))
            {
                FlowDocument		Doc=(FlowDocument) XamlReader.Load(FS);
                XpsDocument			XpsDocument = new XpsDocument("test2.xps", FileAccess.ReadWrite);
                XpsDocumentWriter	Writer=XpsDocument.CreateXpsDocumentWriter(XpsDocument);

                Writer.Write(((IDocumentPaginatorSource) Doc).DocumentPaginator);

                // Display the new XPS document in a viewer.
                MDocViewer.Document=XpsDocument.GetFixedDocumentSequence();
                XpsDocument.Close();
            }
        }
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------