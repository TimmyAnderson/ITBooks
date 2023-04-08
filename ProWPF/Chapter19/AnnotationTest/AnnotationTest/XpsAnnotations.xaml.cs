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
using System.IO.Packaging;
using System.Windows.Annotations;
using System.Windows.Annotations.Storage;
//------------------------------------------------------------------------
namespace AnnotationTest
{
//------------------------------------------------------------------------
	public partial class XpsAnnotations:Window
	{
//------------------------------------------------------------------------
        private AnnotationService			MService;
        private XpsDocument					MDoc;
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public XpsAnnotations()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
        private void Window_Loaded(object Sender, RoutedEventArgs E)
        {
			// !!! Musi byt ReadWrite Access.
            MDoc=new XpsDocument("..\\..\\Data\\Ch19.xps", FileAccess.ReadWrite);

            MDocViewer.Document=MDoc.GetFixedDocumentSequence();
            MService=AnnotationService.GetService(MDocViewer);

            if (MService==null)
            {
				// Bytvorim Part Name Uri na identifikaciu Stramu do ktoreho budem uladat moje Annotations.
                Uri				AnnotationUri=PackUriHelper.CreatePartUri(new Uri("AnnotationStream", UriKind.Relative));
				// Vytvorim Package pre dany XPS.
                Package			Package=PackageStore.GetPackage(MDoc.Uri);
                PackagePart		AnnotationPart=null;

                if (Package.PartExists(AnnotationUri)==true)
                {
					// !!! Ak uz existuje - z predchadzajuceho pouzitia XPS tak ho ziskam.
                    AnnotationPart=Package.GetPart(AnnotationUri);
                }
                else                
                {
					// Ak Package neexistuje vytvorim ho.
                    AnnotationPart=Package.CreatePart(AnnotationUri, "Annotations/Stream");
                }

                // !!! Nacitam Stream Z XPS Package a ten pouzijem ako Store pre Annotations.
                AnnotationStore				Store=new XmlStreamStore(AnnotationPart.GetStream());

                MService=new AnnotationService(MDocViewer);
                MService.Enable(Store);
            }
        }
//------------------------------------------------------------------------
        private void Window_Unloaded(object Sender, RoutedEventArgs E)
        {
            if (MService!=null && MService.IsEnabled==true)
            {
                // Flush annotations to stream.
                MService.Store.Flush();

                // Disable annotations.
                MService.Disable();
            }

            MDoc.Close();
        }
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------