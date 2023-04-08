using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Input;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Controls.Primitives;
//------------------------------------------------------------------------------
namespace Buttons
{
//------------------------------------------------------------------------------
	public class CButtonWithToolTip : Window
	{
//------------------------------------------------------------------------------
		public CButtonWithToolTip()
		{
            Title="Bind theButton";

            ToggleButton		Btn=new ToggleButton();

            Btn.Content="Make _Topmost";
            Btn.HorizontalAlignment=HorizontalAlignment.Center;
            Btn.VerticalAlignment=VerticalAlignment.Center;
            Btn.SetBinding(ToggleButton.IsCheckedProperty, "Topmost");
            Btn.DataContext=this;
            Content=Btn;

            ToolTip				Tip=new ToolTip();

            Tip.Content="Toggle the button on to make the window topmost on the desktop.";
            Btn.ToolTip=Tip;
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------