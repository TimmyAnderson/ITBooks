﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
//------------------------------------------------------------------------------
namespace Visuals
{
//------------------------------------------------------------------------------
	public class CWindowWithFrameworkElement : Window
	{
//------------------------------------------------------------------------------
		public CWindowWithFrameworkElement()
		{
			Content=new CFrameworkElement();
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------