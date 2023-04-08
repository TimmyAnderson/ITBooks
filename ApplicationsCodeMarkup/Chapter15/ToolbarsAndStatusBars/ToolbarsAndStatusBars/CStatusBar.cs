using System;
using System.Reflection;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Shapes;
using System.Windows.Media.Imaging;
//------------------------------------------------------------------------------
namespace ToolbarsAndStatusBars
{
//------------------------------------------------------------------------------
	public class CStatusBar : Window
	{
//------------------------------------------------------------------------------
		private StatusBarItem									MSBI1;
		private StatusBarItem									MSBI2;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        public CStatusBar()
		{
            Title = "Status Toolbar";

			this.MouseMove+=new MouseEventHandler(CStatusBar_MouseMove);

            DockPanel				MyDock=new DockPanel();

            Content=MyDock;
			MyDock.LastChildFill=true;


            StatusBar				MyStatusBar=new StatusBar();

            MyDock.Children.Add(MyStatusBar);
            DockPanel.SetDock(MyStatusBar, Dock.Bottom);

			MSBI1=new StatusBarItem();
			MSBI2=new StatusBarItem();

			MyStatusBar.Items.Add(MSBI1);
			MyStatusBar.Items.Add(MSBI2);

			MSBI1.Content=string.Format("X: [{0}] !","UNKNOWN");
			MSBI2.Content=string.Format("Y: [{0}] !","UNKNOWN");

			// Vytvorim nejaky element, aby zaberal zbytok plochy DockPanel.
			TextBox					TXB=new TextBox();

			MyDock.Children.Add(TXB);
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		private void CStatusBar_MouseMove(object Sender, MouseEventArgs E)
		{
			MSBI1.Content=string.Format("X: [{0}] !",E.GetPosition(this).X);
			MSBI2.Content=string.Format("Y: [{0}] !",E.GetPosition(this).Y);
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------