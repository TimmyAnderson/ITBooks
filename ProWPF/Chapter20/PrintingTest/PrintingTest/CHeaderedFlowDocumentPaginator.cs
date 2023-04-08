using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Documents;
using System.Windows.Media;
using System.Windows;
using System.Globalization;
//------------------------------------------------------------------------
namespace PrintingTest
{
//------------------------------------------------------------------------
	// !!! Celu robotu prehodim na Wrapped Paginator.
	// !!! Ja iba v GetPage() dohodim Header.
	// !!! Header NEMENI velkost stranky.
	public class CHeaderedFlowDocumentPaginator  : DocumentPaginator
	{
//------------------------------------------------------------------------
        private DocumentPaginator			MFlowDocumentPaginator;
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
        public CHeaderedFlowDocumentPaginator(FlowDocument Document)
        {
            MFlowDocumentPaginator=((IDocumentPaginatorSource) Document).DocumentPaginator;
        }
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
        public override bool				IsPageCountValid
        {
            get
			{
				return(MFlowDocumentPaginator.IsPageCountValid); 
			}
        }
//------------------------------------------------------------------------
        public override int					PageCount
        {
            get
			{
				return(MFlowDocumentPaginator.PageCount);
			}
        }
//------------------------------------------------------------------------
        public override Size				PageSize
        {
            get
			{
				return(MFlowDocumentPaginator.PageSize);
			}
            set
			{
				MFlowDocumentPaginator.PageSize=value;
			}
        }
//------------------------------------------------------------------------
		public override IDocumentPaginatorSource Source
		{
			get
			{
				return(MFlowDocumentPaginator.Source);
			}
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
        public override DocumentPage GetPage(int PageNumber)
        {
            // Necham povodny Paginator nech vrati stranku.
            DocumentPage			Page=MFlowDocumentPaginator.GetPage(PageNumber);

            // Vytvorim vraprovaci VisualConatiner, kde ulozim Page.Visual a Header.
            ContainerVisual			NewVisual=new ContainerVisual();

			// Pridam Visual daneho Page.
            NewVisual.Children.Add(Page.Visual);

            // Vytvorim Header.
            DrawingVisual			Header=new DrawingVisual();

			// Vykreslim Header.
            using (DrawingContext Context=Header.RenderOpen())
            {
                Typeface			Typeface=new Typeface("Times New Roman");
				FormattedText		Text=new FormattedText(string.Format("!!! THIS IS Page: {0} !", (PageNumber + 1).ToString()), CultureInfo.CurrentCulture, FlowDirection.LeftToRight, Typeface, 14, Brushes.Black);
                
                // Leave a quarter-inch of space between the page edge and this text.
                Context.DrawText(Text, new Point(96*0.25, 96*0.25));
            }

            // Pridam Header do Visual.
            NewVisual.Children.Add(Header);

            // Vytvorim Page, ktora wrapruje novy Visual objekt.
            DocumentPage		NewPage = new DocumentPage(NewVisual);

            return(NewPage);
        }
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------