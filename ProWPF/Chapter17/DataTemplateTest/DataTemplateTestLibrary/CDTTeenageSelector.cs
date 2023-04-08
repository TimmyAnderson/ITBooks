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
//------------------------------------------------------------------------
namespace DataTemplateTestLibrary
{
//------------------------------------------------------------------------
	public class CDTTeenageSelector : DataTemplateSelector
	{
//------------------------------------------------------------------------
		private DataTemplate					MDT1;
		private DataTemplate					MDT2;
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public DataTemplate						DT1
		{
			get
			{
				return(MDT1);
			}
			set
			{
				MDT1=value;
			}
		}
//------------------------------------------------------------------------
		public DataTemplate						DT2
		{
			get
			{
				return(MDT2);
			}
			set
			{
				MDT2=value;
			}
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public override DataTemplate SelectTemplate(object Item, DependencyObject Container)
		{
			CName			Name=(CName) Item;

			if (Name.Age>=13 && Name.Age<=19)
				return(MDT2);
			else
				return(MDT1);
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------