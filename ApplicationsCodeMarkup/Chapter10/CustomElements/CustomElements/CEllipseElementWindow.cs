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
namespace CustomElements
{
//------------------------------------------------------------------------------
	public class CEllipseElementWindow : Window
	{
//------------------------------------------------------------------------------
		public CEllipseElementWindow(int Index)
		{
			CEllipseElement		Ellipse=new CEllipseElement();

			Title="Ellipse";
			Content=Ellipse;
			
			if (Index==2)
			{
				// !!! Tym, ze ZRUSIM DEFUALT hodnoty pre Alignment, ktore boli nastavene na Stretch, dostane Ellipse velkost 0 a vykresli sa IBA PEN o sirke 24 pixelov.
				Ellipse.HorizontalAlignment=HorizontalAlignment.Center;
				Ellipse.VerticalAlignment=VerticalAlignment.Center;
			}
			else if (Index==3)
			{
				Ellipse.HorizontalAlignment=HorizontalAlignment.Center;
				Ellipse.VerticalAlignment=VerticalAlignment.Center;

				Ellipse.Width=26;
				Ellipse.Height=26;
			}
			else if (Index==4)
			{
				Ellipse.HorizontalAlignment=HorizontalAlignment.Center;
				Ellipse.VerticalAlignment=VerticalAlignment.Center;

				Ellipse.Width=2;
				Ellipse.Height=2;
			}
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------