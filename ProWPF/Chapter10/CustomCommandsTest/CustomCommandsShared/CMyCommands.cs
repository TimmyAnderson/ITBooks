using System;
using System.Collections.Generic;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
//------------------------------------------------------------------------
namespace CustomCommandsShared
{
//------------------------------------------------------------------------
	public class CMyCommands
	{
//------------------------------------------------------------------------
		private static RoutedUICommand			MMySuperCommand;
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		static CMyCommands()
		{
			InputGestureCollection	Inputs=new InputGestureCollection();

			Inputs.Add(new KeyGesture(Key.S, ModifierKeys.Control, "Ctrl+S"));
			MMySuperCommand=new RoutedUICommand("My Super Command", "MySuperCommand", typeof(CMyCommands), Inputs);
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public static RoutedUICommand			MySuperCommand
		{
			get
			{
				return(MMySuperCommand);
			}
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------