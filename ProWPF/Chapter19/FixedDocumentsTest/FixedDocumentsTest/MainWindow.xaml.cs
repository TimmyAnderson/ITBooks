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
//------------------------------------------------------------------------
// 1. Program demonstruje pouzitie Fixed Documents.
// 2. FD sa pouzivaju na tlac. Maju priponu .XPS a na pozadi je to .ZIP subor, XAML pre kazdu stranku textu a prilozene obrazky a dalsi obsah.
// 3. FD ma specialnu podporu na Vistu pre tlac dokumentov a specialny driver a prehliadac.
// !!! 4. Na zobrazenie XPS sa pouziva DocumentViewer.
//------------------------------------------------------------------------
namespace FixedDocumentsTest
{
//------------------------------------------------------------------------
	public partial class MainWindow:Window
	{
//------------------------------------------------------------------------
		public MainWindow()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
        private void Window_Loaded(object Sender, RoutedEventArgs E)
        {
            XpsDocument			Doc=new XpsDocument("..\\..\\Images\\Ch19.xps", FileAccess.Read);

            MDocViewer.Document=Doc.GetFixedDocumentSequence();
            Doc.Close();
        }
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------