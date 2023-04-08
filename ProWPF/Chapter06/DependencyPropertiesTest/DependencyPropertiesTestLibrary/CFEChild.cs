using System;
using System.Collections.Generic;
using System.Text;
using System.Windows;
using System.Windows.Media;
using System.Globalization;
//------------------------------------------------------------------------
namespace DependencyPropertiesTestLibrary
{
//------------------------------------------------------------------------
	public class CFEChild : FrameworkElement
	{
//------------------------------------------------------------------------
		protected override void OnRender(DrawingContext DrawingContext)
		{
			// Nic nerenderujem.
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public override string ToString()
		{
			return(string.Format("FEIntAP1: {0}, FEIntAP2: {1} !",CFEParent.GetFEIntAP1(this),CFEParent.GetFEIntAP2(this)));
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------