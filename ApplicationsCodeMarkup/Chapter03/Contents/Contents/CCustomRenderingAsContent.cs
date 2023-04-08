using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Input;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;
//------------------------------------------------------------------------------
namespace Contents
{
//------------------------------------------------------------------------------
	public class CCustomRenderingAsContent : Window
	{
//------------------------------------------------------------------------------
		public CCustomRenderingAsContent()
		{
            Title = "Render the Graphic";

            CSimpleEllipse		Elips=new CSimpleEllipse();

            Content=Elips;
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------