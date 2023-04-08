using System;
using System.Collections.Generic;
using System.Text;
using System.Windows;
using System.Windows.Media;
using System.Globalization;
//------------------------------------------------------------------------
namespace FontTestLibrary
{
//------------------------------------------------------------------------
	public class CMyClass : FrameworkElement
	{
//------------------------------------------------------------------------
		protected override void OnRender(DrawingContext DC)
		{
			FormattedText		FT=new FormattedText("Hello World !",CultureInfo.CurrentCulture,FlowDirection.LeftToRight,new Typeface(new FontFamily("Arial"),new FontStyle(),new FontWeight(),new FontStretch()),12,new SolidColorBrush(Colors.Blue));

			DC.DrawText(FT,new Point(0,0));
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------