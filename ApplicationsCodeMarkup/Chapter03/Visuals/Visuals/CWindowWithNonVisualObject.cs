using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
//------------------------------------------------------------------------------
namespace Visuals
{
//------------------------------------------------------------------------------
	public class CWindowWithNonVisualObject : Window
	{
//------------------------------------------------------------------------------
		public CWindowWithNonVisualObject()
		{
			// Vola sa metoda ToString().
			Content=new CNonVisualObject();
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------