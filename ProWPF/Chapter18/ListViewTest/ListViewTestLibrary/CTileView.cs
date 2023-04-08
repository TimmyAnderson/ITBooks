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
namespace ListViewTestLibrary
{
//------------------------------------------------------------------------
	public class CTileView : ViewBase
	{
//------------------------------------------------------------------------
		private DataTemplate					MItemTemplate;
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		protected override object				DefaultStyleKey
		{
			get
			{
				return(new ComponentResourceKey(GetType(), "MTileView"));
			}
		}
//------------------------------------------------------------------------
		protected override object				ItemContainerDefaultStyleKey
		{
			get
			{
				return(new ComponentResourceKey(GetType(), "MTileViewItem"));
			}
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public DataTemplate						ItemTemplate
		{
			get
			{
				return(MItemTemplate);
			}
			set
			{
				MItemTemplate=value;
			}
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------