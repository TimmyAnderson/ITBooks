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
using System.Windows.Threading;
//------------------------------------------------------------------------------
namespace Visuals
{
//------------------------------------------------------------------------------
	public class CWindowWithVisuals : Window
	{
//------------------------------------------------------------------------------
		public CWindowWithVisuals()
		{
			Visual					V=new CUIElement();

			base.Content=V;
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------