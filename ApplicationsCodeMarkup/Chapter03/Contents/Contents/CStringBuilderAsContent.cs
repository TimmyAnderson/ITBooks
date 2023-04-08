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
	public class CStringBuilderAsContent : Window
	{
//------------------------------------------------------------------------------
		private StringBuilder						MContent;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		public CStringBuilderAsContent()
		{
			MContent=new StringBuilder();
				
			MContent.Append(DateTime.Now.ToLongTimeString());

			Content=MContent;
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		protected override void OnMouseDown(MouseButtonEventArgs E)
		{
			// Text vo Window sa NIKDY NEZMENI, pretoze sa hodnota Content NEMENI.
			MContent.Length=0;
			MContent.Append(DateTime.Now.ToLongTimeString());

			Console.WriteLine("OnMouseDown() CALLED !");
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------