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
using System.Windows.Annotations;
using System.Windows.Annotations.Storage;
using System.Windows.Xps;
using System.Printing;
using System.IO;
//------------------------------------------------------------------------
namespace AnnotationTest
{
//------------------------------------------------------------------------
	public partial class CustomStickyNotes:Window
	{
//------------------------------------------------------------------------
		private MemoryStream		MAnnotationStream;
		private AnnotationService	MService;
		private AnnotationStore		MStore;
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public CustomStickyNotes()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void Window_Loaded(object Sender, RoutedEventArgs E)
		{
			// Vytvorim service, pricom ako parameter dam Document Container.
			MService=new AnnotationService(MDocReader);

			// Vytvorim Stream do ktoreho sa budu ukladat Annotations.
			MAnnotationStream=new MemoryStream();

			MStore=new XmlStreamStore(MAnnotationStream);

			// Aktivujem AnnotatonService a zadam Stream, kde sa budu ukladat data.
			MService.Enable(MStore);
		}
//------------------------------------------------------------------------
		private void Window_Unloaded(object Sender, RoutedEventArgs E)
		{
			if (MService!=null && MService.IsEnabled==true)
			{
				// Urobim Flush do Streamu.
				MService.Store.Flush();

				// Vypnem AnnotationService.
				MService.Disable();

				// Zavriem Stream.
				MAnnotationStream.Close();
			}
		}
//------------------------------------------------------------------------
		private void Button_Click(object Sender, RoutedEventArgs E)
		{
			// Zistim ci je Annotaton Service pre tento Document Contaier aktivny.
			if (AnnotationService.GetService(MDocReader)!=null)
			{
				MService.Store.Flush();
				MService.Disable();
				MDisable.Content="Enable Annotation Service";
			}
			else
			{
				MService.Enable(MStore);
				MDisable.Content="Disable Annotation Service";
			}
		}
//------------------------------------------------------------------------
        private void CmdShowAllAnotations_Click(object Sender, RoutedEventArgs E)
        {
			// Ziskam kolekciu Annotations.
            IList<Annotation>		Annotations=MService.Store.GetAnnotations();

            foreach (Annotation Annotation in Annotations)
            {
                // Check for text information.
                if (Annotation.Cargos.Count > 1)
                {
					// Text v Annotation je kodovany cez Base64.
                    string			Base64Text=Annotation.Cargos[1].Contents[0].InnerText;
                    byte[]			Decoded=Convert.FromBase64String(Base64Text);
                    MemoryStream	M=new MemoryStream();

                    M.Write(Decoded, 0, Decoded.Length);
                    M.Position=0;

                    StreamReader	R=new StreamReader(M);
                    string			AnnotationXaml=R.ReadToEnd();

                    MessageBox.Show(AnnotationXaml);
                }
            }

			/*
            PrintDialog				Dialog=new PrintDialog();
            bool?					Result=Dialog.ShowDialog();

            if (Result!=null && Result.Value)
            {
                XpsDocumentWriter			Writer=System.Printing.PrintQueue.CreateXpsDocumentWriter(Dialog.PrintQueue);
                AnnotationDocumentPaginator	Adp=new AnnotationDocumentPaginator(((IDocumentPaginatorSource) MDocReader.Document).DocumentPaginator, MService.Store);

                Writer.Write(Adp);
            }
			*/
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------