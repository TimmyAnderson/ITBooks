using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Input;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
//------------------------------------------------------------------------------
namespace DockPanelAndGrid
{
//------------------------------------------------------------------------------
	public class CStandardDockPanel : Window
	{
//------------------------------------------------------------------------------
		public CStandardDockPanel()
		{
            Title = "Meet the Dockers";

            DockPanel		LDock=new DockPanel();

            Content=LDock;

            Menu			Menu=new Menu();
            MenuItem		Item=new MenuItem();

            Item.Header="Menu";
            Menu.Items.Add(Item);

            DockPanel.SetDock(Menu, Dock.Top);
            LDock.Children.Add(Menu);

            ToolBar			Tool=new ToolBar();

            Tool.Header="Toolbar";

            DockPanel.SetDock(Tool, Dock.Top);
            LDock.Children.Add(Tool);

            StatusBar		Status=new StatusBar();
            StatusBarItem	StatItem=new StatusBarItem();

            StatItem.Content="Status";
            Status.Items.Add(StatItem);
            
            DockPanel.SetDock(Status, Dock.Bottom);
            LDock.Children.Add(Status);

            ListBox			LstBox=new ListBox();

            LstBox.Items.Add("List Box Item");

            DockPanel.SetDock(LstBox, Dock.Left);
            LDock.Children.Add(LstBox);

            TextBox			TxtBox=new TextBox();

            TxtBox.AcceptsReturn=true;

            LDock.Children.Add(TxtBox);
            TxtBox.Focus();
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------