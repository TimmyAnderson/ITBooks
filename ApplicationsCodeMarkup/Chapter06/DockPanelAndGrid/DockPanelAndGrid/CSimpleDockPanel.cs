using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Input;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
//------------------------------------------------------------------------------
namespace DockPanelAndGrid
{
//------------------------------------------------------------------------------
	public class CSimpleDockPanel : Window
	{
//------------------------------------------------------------------------------
		public CSimpleDockPanel()
		{
            Title="Dock Around the Block";

            DockPanel		Dock=new DockPanel();

            Content=Dock;

            for (int i=0;i<17;i++)
            {
                Button		Btn=new Button();

				//Btn.HorizontalAlignment=HorizontalAlignment.Center;
				//Btn.VerticalAlignment=VerticalAlignment.Center;

                Btn.Content="Button No. " + (i + 1);
                Dock.Children.Add(Btn);
                Btn.SetValue(DockPanel.DockProperty, (Dock)(i % 4));
            }
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------