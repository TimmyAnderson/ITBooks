using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Shapes;
//-------------------------------------------------------------------------------------------------------
namespace XBAPTest
{
//-------------------------------------------------------------------------------------------------------
    public class Tile : Canvas
    {
//-------------------------------------------------------------------------------------------------------
        private const int										SIZE=64;
        private const int										BORD=6;
        private TextBlock										MTxtBlock;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        public Tile()
        {
            Width=SIZE;
            Height=SIZE;

            Polygon			LPoly=new Polygon();

            LPoly.Points=new PointCollection(new Point[] 
                { 
                    new Point(0, 0), new Point(SIZE, 0), 
                    new Point(SIZE-BORD, BORD),
                    new Point(BORD, BORD), 
                    new Point(BORD, SIZE-BORD), new Point(0, SIZE)
                });

            LPoly.Fill=SystemColors.ControlLightLightBrush;
            Children.Add(LPoly);

            LPoly=new Polygon();

            LPoly.Points=new PointCollection(new Point[] 
                { 
                    new Point(SIZE, SIZE), new Point(SIZE, 0), 
                    new Point(SIZE-BORD, BORD),
                    new Point(SIZE-BORD, SIZE-BORD), 
                    new Point(BORD, SIZE-BORD), new Point(0, SIZE)
                });

            LPoly.Fill=SystemColors.ControlDarkBrush;
            Children.Add(LPoly);

            Border		LBorder=new Border();

            LBorder.Width=SIZE-(2*BORD);
            LBorder.Height=SIZE-(2*BORD);
            LBorder.Background=SystemColors.ControlBrush;
            Children.Add(LBorder);
            SetLeft(LBorder,BORD);
            SetTop(LBorder,BORD);

            MTxtBlock=new TextBlock();
            MTxtBlock.FontSize=32;
            MTxtBlock.Foreground=SystemColors.ControlTextBrush;
            MTxtBlock.HorizontalAlignment=HorizontalAlignment.Center;
            MTxtBlock.VerticalAlignment=VerticalAlignment.Center;
            LBorder.Child=MTxtBlock;
        }
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        public string											Text
        {
            get
			{
				return(MTxtBlock.Text);
			}
            set
			{
				MTxtBlock.Text=value;
			}
        }
//-------------------------------------------------------------------------------------------------------
    }
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------