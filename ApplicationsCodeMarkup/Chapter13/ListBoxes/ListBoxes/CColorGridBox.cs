using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Data;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Shapes;
//------------------------------------------------------------------------------
namespace ListBoxes
{
//------------------------------------------------------------------------------
	public class CColorGridBox : ListBox
	{
//------------------------------------------------------------------------------
        string[]									MStrColors=
        {
            "Black", "Brown", "DarkGreen", "MidnightBlue", "Navy", "DarkBlue", "Indigo", "DimGray",
            "DarkRed", "OrangeRed", "Olive", "Green", "Teal", "Blue", "SlateGray", "Gray",
            "Red", "Orange", "YellowGreen", "SeaGreen", "Aqua", "LightBlue", "Violet", "DarkGray",
            "Pink", "Gold", "Yellow", "Lime", "Turquoise", "SkyBlue", "Plum", "LightGray",
            "LightPink", "Tan", "LightYellow", "LightGreen", "LightCyan", "LightSkyBlue", "Lavender", "White"
        };
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        public CColorGridBox()
        {
            // Definujem ItemsPanel TEMPLATE.
            FrameworkElementFactory		FactoryUnigrid=new FrameworkElementFactory(typeof(UniformGrid));

            FactoryUnigrid.SetValue(UniformGrid.ColumnsProperty, 8);

			// !!! Nastavim ItemsPanel.
            ItemsPanel=new ItemsPanelTemplate(FactoryUnigrid);

            foreach (string StrColor in MStrColors)
            {
                Rectangle				Rect=new Rectangle();

                Rect.Width=12;
                Rect.Height=12;
                Rect.Margin=new Thickness(4);
                Rect.Fill=(Brush) typeof(Brushes).GetProperty(StrColor).GetValue(null, null);

                Items.Add(Rect);

                ToolTip					Tip=new ToolTip();

                Tip.Content=StrColor;
                Rect.ToolTip=Tip;
            }

            SelectedValuePath="Fill";
        }
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------