using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Input;
//------------------------------------------------------------------------------
namespace Contents
{
//------------------------------------------------------------------------------
	public class CNewStringAsContent : Window
	{
//------------------------------------------------------------------------------
		public CNewStringAsContent()
		{
			Content=DateTime.Now.ToLongTimeString();
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		protected override void OnMouseDown(MouseButtonEventArgs E)
		{
			// Text vo Window sa ZMENI, pretoze sa ZMENI hodnota Content - vzdy ukazujuc na NOVY OBJEKT.
			Content=DateTime.Now.ToLongTimeString();

			Console.WriteLine("OnMouseDown() CALLED !");
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------