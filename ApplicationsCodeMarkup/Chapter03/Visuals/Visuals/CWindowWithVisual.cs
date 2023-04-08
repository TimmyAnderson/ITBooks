using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
//------------------------------------------------------------------------------
namespace Visuals
{
//------------------------------------------------------------------------------
	public class CWindowWithVisual : Window
	{
//------------------------------------------------------------------------------
		public CWindowWithVisual()
		{
			// !!!!! Samotny Visual objekt NIE JE RENDEROVATELNY a potrebuje HOST.
			// !!! Tento priklad zobrazi iba CVisual.ToString().
			base.Content=new CVisual();
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------