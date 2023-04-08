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
using System.Windows.Threading;
//------------------------------------------------------------------------------
namespace RadialPanel
{
//------------------------------------------------------------------------------
	public class CRadialPanelWindow : Window
	{
//------------------------------------------------------------------------------
        public CRadialPanelWindow()
        {
            Title="Circle the Buttons";

            CRadialPanel		Pnl=new CRadialPanel();

            Pnl.Orientation=ERadialPanel.ByWidth;
            Pnl.ShowPieLines=true;
            Content=Pnl;

            Random				Rand=new Random();

            for (int i=0;i<10;i++)
            {
                Button			Btn=new Button();

                Btn.Content="Button Number " + (i+1);
                Btn.FontSize+=Rand.Next(10);
                Pnl.Children.Add(Btn);
            }
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------