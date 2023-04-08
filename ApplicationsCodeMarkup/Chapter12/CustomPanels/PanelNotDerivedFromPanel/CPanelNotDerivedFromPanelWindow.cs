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
namespace PanelNotDerivedFromPanel
{
//------------------------------------------------------------------------------
	public class CPanelNotDerivedFromPanelWindow : Window
	{
//------------------------------------------------------------------------------
        public CPanelNotDerivedFromPanelWindow()
        {
            Title = "Diagonalize the Buttons";

            CPanelNotDerivedFromPanel	Pnl=new CPanelNotDerivedFromPanel();

            Content=Pnl;

            Random						Rand=new Random();

            for (int i=0;i<5;i++)
            {
                Button					Btn=new Button();

                Btn.Content="Button Number " + (i + 1);
                Btn.FontSize+=Rand.Next(20);
                Pnl.Add(Btn);
            }
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------