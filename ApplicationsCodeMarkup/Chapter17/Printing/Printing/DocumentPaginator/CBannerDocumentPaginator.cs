using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Globalization;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Documents;
using System.Windows.Media;
//------------------------------------------------------------------------------
namespace Printing
{
//------------------------------------------------------------------------------
	public class CBannerDocumentPaginator : DocumentPaginator
	{
//------------------------------------------------------------------------------
        private string											MTxt="";
        private Typeface										MFace=new Typeface("");
        private Size											MSizePage;
        private Size											MSizeMax=new Size(0, 0);
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        public string											Text
        {
            get
			{
				return(MTxt);
			}
            set
			{
				MTxt=value;
			}
        }
//------------------------------------------------------------------------------
        public Typeface											Typeface
        {
            get
			{
				return(MFace);
			}
            set
			{
				MFace=value;
			}
        }
//------------------------------------------------------------------------------
        public override bool									IsPageCountValid
        {
            get 
            {
                foreach (char Ch in MTxt)
                {
                    FormattedText		FormTxt=GetFormattedText(Ch, MFace, 100);

                    MSizeMax.Width=Math.Max(MSizeMax.Width, FormTxt.Width);
                    MSizeMax.Height=Math.Max(MSizeMax.Height, FormTxt.Height);
                }

                return(true);
            }
        }
//------------------------------------------------------------------------------
        public override int										PageCount
        {
            get
			{
				return((MTxt==null) ? 0 : MTxt.Length);
			}
        }
//------------------------------------------------------------------------------
        public override Size									PageSize
        {
            get
			{
				return(MSizePage);
			}
            set
			{
				MSizePage=value;
			}
        }
//------------------------------------------------------------------------------
        public override IDocumentPaginatorSource				Source
        {
            get
			{
				return(null);
			}
        }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        private FormattedText GetFormattedText(char Ch, Typeface Face, double Em)
        {
            return(new FormattedText(Ch.ToString(), CultureInfo.CurrentCulture, FlowDirection.LeftToRight, Face, Em, Brushes.Black));
        }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        public override DocumentPage GetPage(int NumPage)
        {
            DrawingVisual					Vis=new DrawingVisual();
            DrawingContext					DC=Vis.RenderOpen();
            double							Factor=Math.Min((PageSize.Width-96)/MSizeMax.Width,(PageSize.Height-96)/MSizeMax.Height);
            FormattedText					FormTxt=GetFormattedText(MTxt[NumPage], MFace, Factor*20);
            Point							PtText=new Point((PageSize.Width-FormTxt.Width)/2,(PageSize.Height-FormTxt.Height)/2);

            DC.DrawText(FormTxt, PtText);
            DC.Close();

            return(new DocumentPage(Vis));
        }
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------