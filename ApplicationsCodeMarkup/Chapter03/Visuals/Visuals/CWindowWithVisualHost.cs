using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Media;
//------------------------------------------------------------------------------
namespace Visuals
{
//------------------------------------------------------------------------------
	public class CWindowWithVisualHost : Window
	{
//------------------------------------------------------------------------------
		public CWindowWithVisualHost()
		{
			Visual					V=new CVisualHost();

			base.Content=V;
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------