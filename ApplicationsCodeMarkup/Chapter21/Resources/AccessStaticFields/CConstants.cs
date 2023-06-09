﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Media;
//-----------------------------------------------------------------------------------------------------------------
namespace AccessStaticFields
{
//-----------------------------------------------------------------------------------------------------------------
	public static class CConstants
	{
//-----------------------------------------------------------------------------------------------------------------
        public static readonly FontFamily						MFontFamily=new FontFamily("Times New Roman Italic");
        public static readonly LinearGradientBrush				MBrush=new LinearGradientBrush(Colors.LightGray, Colors.DarkGray, new Point(0, 0), new Point(1, 1));
//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
        public static double									FontSize
        {
            get
			{
				return(72/0.75);
			}
        }
//-----------------------------------------------------------------------------------------------------------------
	}
//-----------------------------------------------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------------------------------------------