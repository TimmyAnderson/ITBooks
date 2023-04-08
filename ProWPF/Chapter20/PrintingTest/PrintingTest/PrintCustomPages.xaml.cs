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
using System.Data;
//------------------------------------------------------------------------
namespace PrintingTest
{
//------------------------------------------------------------------------
	public partial class PrintCustomPages:Window
	{
//------------------------------------------------------------------------
		public PrintCustomPages()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
        private void CmdPrint_Click(object Sender, RoutedEventArgs E)
        {
            PrintDialog					PD=new PrintDialog();

            if (PD.ShowDialog()==true)
            {
                DataSet					DS=new DataSet();

                DS.ReadXmlSchema("..\\..\\Store\\Store.xsd");
                DS.ReadXml("..\\..\\Store\\Store.xml");

                CStoreDataSetPaginator	Paginator=new CStoreDataSetPaginator(DS.Tables[0], new Typeface("Calibri"), 24, 96*0.75, new Size(PD.PrintableAreaWidth, PD.PrintableAreaHeight)); 

                PD.PrintDocument(Paginator, "Custom-Printed Pages");
            }
        }
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------