using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Media;
//------------------------------------------------------------------------------
namespace Contents
{
//------------------------------------------------------------------------------
	public class CWindowWithText : Window
	{
//------------------------------------------------------------------------------
		public CWindowWithText()
		{
			Content="Timmy Anderson";

			FontFamily=new FontFamily("Arial");
			FontWeight=FontWeights.ExtraBold;
			FontStyle=FontStyles.Italic;
			FontSize=30;
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------