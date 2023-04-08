using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Documents;
using System.Windows.Media;
using System.Data;
using System.Globalization;
using System.Windows;
//------------------------------------------------------------------------
namespace PrintingTest
{
//------------------------------------------------------------------------
    public class CStoreDataSetPaginator : DocumentPaginator
    {
//------------------------------------------------------------------------
        private DataTable						MDT;
        private Typeface						MTypeface;
        private double							MFontSize;
        private double							MMargin;
        private int								MRowsPerPage;
        private int								MPageCount;
        private Size							MPageSize;
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
        public CStoreDataSetPaginator(DataTable DT, Typeface Typeface, double FontSize, double Margin, Size PageSize)
        {
            MDT=DT;
            MTypeface=Typeface;
            MFontSize=FontSize;
            MMargin=Margin;
            MPageSize=PageSize;

            PaginateData();
        }
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
        public override bool					IsPageCountValid
        {
            get
			{
				return(true);
			}
        }
//------------------------------------------------------------------------
        public override int						PageCount
        {
            get
			{
				return(MPageCount);
			}
        }
//------------------------------------------------------------------------
        public override Size					PageSize
        {
            get
            {
                return(MPageSize);
            }
            set
            {
                MPageSize=value;
                PaginateData();
            }
        }
//------------------------------------------------------------------------
        public override IDocumentPaginatorSource Source
        {
            get
			{
				return(null);
			}
        }
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
        private FormattedText GetFormattedText(string Text)
        {
            return(GetFormattedText(Text, MTypeface));
        }
//------------------------------------------------------------------------
        private FormattedText GetFormattedText(string Text, Typeface Typeface)
        {            
            return(new FormattedText(Text, CultureInfo.CurrentCulture, FlowDirection.LeftToRight, Typeface, MFontSize, Brushes.Black));
        }
//------------------------------------------------------------------------
		// Vypocita pocet stran.
        private void PaginateData()
        {
            // Create a test string for the purposes of measurement.
            FormattedText	Text=GetFormattedText("A");

            // Count the lines that fit on a page.
            MRowsPerPage = (int)((PageSize.Height-MMargin*2)/Text.Height);

            // Leave a row for the headings
            MRowsPerPage-= 1;

            MPageCount=(int) Math.Ceiling((double) MDT.Rows.Count/MRowsPerPage);
        }
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
        public override DocumentPage GetPage(int PageNumber)
        {
            // Create a test string for the purposes of measurement.
            FormattedText		Text=GetFormattedText("A");

            // Size columns relative to the width of one "A" letter.
            // It's a shortcut that works in this example.
            double				Col1_X=MMargin;
            double				Col2_X=Col1_X+Text.Width * 15;

            // Calculate the range of rows that fits on this page.
            int					MinRow=PageNumber*MRowsPerPage;
            int					MaxRow=MinRow+MRowsPerPage;
                                    
            // Create the visual for the page.
            DrawingVisual		Visual=new DrawingVisual();
            
            // Initial, set the position to the top-left corner of the printable area.
            Point				Point=new Point(MMargin, MMargin);

            // Print the column values.
            using (DrawingContext DC=Visual.RenderOpen())
            {
                // Draw the column headers.
                Typeface		ColumnHeaderTypeface=new Typeface(MTypeface.FontFamily, FontStyles.Normal, FontWeights.Bold, FontStretches.Normal);

                Point.X=Col1_X;
                Text=GetFormattedText("Model Number", ColumnHeaderTypeface);
                DC.DrawText(Text, Point);
                Text=GetFormattedText("Model Name", ColumnHeaderTypeface);
                Point.X=Col2_X;
                DC.DrawText(Text, Point);

                // Draw the line underneath.
                DC.DrawLine(new Pen(Brushes.Black, 2), new Point(MMargin, MMargin+Text.Height), new Point(PageSize.Width-MMargin, MMargin+Text.Height));

                Point.Y+=Text.Height;

                // Draw the column values.
                for (int i=MinRow;i<MaxRow; i++)
                {   
                    // Check for the end of the last (half-filled) page.
                    if (i>(MDT.Rows.Count-1))
						break;

                    Point.X=Col1_X;   
                    Text=GetFormattedText(MDT.Rows[i]["ModelNumber"].ToString());
                    DC.DrawText(Text, Point);

                    // Add second column.                    
                    Text=GetFormattedText(MDT.Rows[i]["ModelName"].ToString());
                    Point.X=Col2_X;
                    DC.DrawText(Text, Point);
                    Point.Y+=Text.Height;
                }
            }            

            return(new DocumentPage(Visual));
        }
//------------------------------------------------------------------------
    }
}
