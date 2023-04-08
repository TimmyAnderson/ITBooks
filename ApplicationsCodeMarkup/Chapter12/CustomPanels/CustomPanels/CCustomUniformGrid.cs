using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Input;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
//------------------------------------------------------------------------------
namespace CustomPanels
{
//------------------------------------------------------------------------------
	public class CCustomUniformGrid : Panel
	{
//------------------------------------------------------------------------------
		// DP urcuje pocet COLUMNS.
        public static readonly DependencyProperty	ColumnsProperty;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        static CCustomUniformGrid()
        {
            ColumnsProperty=DependencyProperty.Register("Columns", typeof(int), typeof(CCustomUniformGrid), new FrameworkPropertyMetadata(1,FrameworkPropertyMetadataOptions.AffectsMeasure));
        }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        public int									Columns
        {
            get
			{
				return((int)GetValue(ColumnsProperty));
			}
            set
			{
				SetValue(ColumnsProperty, value);
			}
        }
//------------------------------------------------------------------------------
		// Read-only property vracajuca pocet ROWS vypocitany z poctu CHILDREN.
        public int									Rows
        {
            get
			{
				return((InternalChildren.Count+Columns-1)/Columns);
			}
        }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        protected override Size MeasureOverride(Size SizeAvailable)
        {
			Console.WriteLine("SizeAvailable: [{0},{1}] !",SizeAvailable.Width,SizeAvailable.Height);

            // Z SizeAvailable vypocitam velkost, ktoru pridelim jednotlivym CELLS.
			// !!! SizeAvailable moze byt i INFINITE.
            Size		SizeChild=new Size(SizeAvailable.Width/Columns,SizeAvailable.Height/Rows);

            double		MaxWidth=0;
            double		MaxHeight=0;

			// !!! Musim prechadzat kolekciu InternalChildren.
            foreach (UIElement Child in InternalChildren)
            {
				// !!!!! Vypocet Measure() RESPEKTUJE VELKOST PRIDELENU v SizeAvailable.
                Child.Measure(SizeChild);

                // Ziskam MAXIMALNU VELKOST CELL.
                MaxWidth=Math.Max(MaxWidth, Child.DesiredSize.Width);
                MaxHeight=Math.Max(MaxHeight, Child.DesiredSize.Height);
            }

            // Vypocitam celkovu pozadovanu velkost PANEL.
			Size		Ret=new Size(Columns*MaxWidth, Rows*MaxHeight);

			Console.WriteLine("Ret: [{0},{1}] !",Ret.Width,Ret.Height);

            return(Ret);
        }
//------------------------------------------------------------------------------
        protected override Size ArrangeOverride(Size SizeFinal)
        {
			Console.WriteLine("SizeFinal: [{0},{1}] !",SizeFinal.Width,SizeFinal.Height);

            Size		SizeChild=new Size(SizeFinal.Width/Columns, SizeFinal.Height/Rows);

            for (int Index=0;Index<InternalChildren.Count;Index++)
            {
                int		Row=Index/Columns;
                int		Col=Index%Columns;

                Rect	RectChild=new Rect(new Point(Col*SizeChild.Width, Row*SizeChild.Height),SizeChild);

                InternalChildren[Index].Arrange(RectChild);
            }

            return(SizeFinal);
        }
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------