using System;
using System.Collections.Generic;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.Globalization;
//------------------------------------------------------------------------
namespace DataTemplateTestLibrary
{
//------------------------------------------------------------------------
	public class CTeenagerStyleSelector : StyleSelector
	{
//------------------------------------------------------------------------
		private Style							MStyle1;
		private Style							MStyle2;
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public Style							Style1
		{
			get
			{
				return(MStyle1);
			}
			set
			{
				MStyle1=value;
			}
		}
//------------------------------------------------------------------------
		public Style							Style2
		{
			get
			{
				return(MStyle2);
			}
			set
			{
				MStyle2=value;
			}
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public override Style SelectStyle(object Item, DependencyObject Container)
		{
			CName			Name=(CName) Item;

			if (Name.Age>=13 && Name.Age<=19)
				return(MStyle2);
			else
				return(MStyle1);
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------