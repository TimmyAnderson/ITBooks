﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Input;
//------------------------------------------------------------------------------
namespace Contents
{
//------------------------------------------------------------------------------
	public class CStringAsContent : Window
	{
//------------------------------------------------------------------------------
		private string								MContent;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		public CStringAsContent()
		{
			MContent=DateTime.Now.ToLongTimeString();

			Content=MContent;
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		protected override void OnMouseDown(MouseButtonEventArgs E)
		{
			// Text vo Window sa NIKDY NEZMENI, pretoze sa hodnota Content NEMENI.
			MContent=DateTime.Now.ToLongTimeString();

			Console.WriteLine("OnMouseDown() CALLED !");
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------