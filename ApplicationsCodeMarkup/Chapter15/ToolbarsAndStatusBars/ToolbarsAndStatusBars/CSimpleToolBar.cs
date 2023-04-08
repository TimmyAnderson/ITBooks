using System;
using System.Reflection;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Shapes;
using System.Windows.Media.Imaging;
//------------------------------------------------------------------------------
namespace ToolbarsAndStatusBars
{
//------------------------------------------------------------------------------
	public class CSimpleToolBar : Window
	{
//------------------------------------------------------------------------------
        public CSimpleToolBar()
		{
            Title = "Craft the Toolbar";

            RoutedUICommand[]		Comm=
			{
                ApplicationCommands.New,
				ApplicationCommands.Open,
                ApplicationCommands.Save,
				ApplicationCommands.Print,
                ApplicationCommands.Cut,
				ApplicationCommands.Copy,
                ApplicationCommands.Paste,
				ApplicationCommands.Delete
			};

			string[]				StrImages=
			{ 
                "NewDocumentHS.png",
				"OpenHS.png",
				"SaveHS.png",
				"PrintHS.png",
				"CutHS.png",
				"CopyHS.png", 
                "PasteHS.png",
				"DeleteHS.png"
			};

            DockPanel				MyDock=new DockPanel();

            MyDock.LastChildFill=false;
            Content=MyDock;

            ToolBar					MyToolbar=new ToolBar();

            MyDock.Children.Add(MyToolbar);
            DockPanel.SetDock(MyToolbar, Dock.Top);

            for (int i=0;i<8;i++)
            {
                if (i==4)
                    MyToolbar.Items.Add(new Separator());

                Button				MyButton=new Button();

                MyButton.Command=Comm[i];
                MyToolbar.Items.Add(MyButton);

                Image				MyImage = new Image();

                MyImage.Source=new BitmapImage(new Uri("pack://application:,,/Images/" + StrImages[i]));
                MyImage.Stretch=Stretch.None;
                MyButton.Content=MyImage;

                ToolTip				MyToolTip=new ToolTip();

                MyToolTip.Content=Comm[i].Text;
                MyButton.ToolTip=MyToolTip;

                CommandBindings.Add(new CommandBinding(Comm[i], ToolBarButtonOnClick));
            }
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        private void ToolBarButtonOnClick(object Sender, ExecutedRoutedEventArgs Args)
        {
            RoutedUICommand			Comm=Args.Command as RoutedUICommand;

            MessageBox.Show(string.Format("{0} command not yet implemented !",Comm.Name),Title);
        }
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------