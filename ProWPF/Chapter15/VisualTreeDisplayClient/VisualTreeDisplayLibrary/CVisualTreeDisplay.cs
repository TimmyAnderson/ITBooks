using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
//------------------------------------------------------------------------
namespace VisualTreeDisplayLibrary
{
//------------------------------------------------------------------------
	public class CVisualTreeDisplay
	{
//------------------------------------------------------------------------
		public void ShowVisualTree(DependencyObject Element)
		{
			Debug.WriteLine("");
			Debug.WriteLine("Logical Tree:");
			ProcessElement(Element, "");
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void ProcessElement(DependencyObject Element, string Tabs)
		{
			Debug.WriteLine(string.Format("{0}{1} !",Tabs,Element.GetType().Name));

			for (int i=0;i<VisualTreeHelper.GetChildrenCount(Element);i++)
				ProcessElement(VisualTreeHelper.GetChild(Element, i), string.Format("{0}   ",Tabs));
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------