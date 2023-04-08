using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Win32;
using System.IO;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Markup;
using System.Xml;
//-----------------------------------------------------------------------------------------------------------------
namespace XAML
{
//-----------------------------------------------------------------------------------------------------------------
	public class LoadXamlFile : Window
	{
//-----------------------------------------------------------------------------------------------------------------
        private Frame											MFrame;
//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
        public LoadXamlFile()
        {
            Title="Load XAML File";

            DockPanel				LDock=new DockPanel();

            Content=LDock;

            Button					Btn=new Button();

            Btn.Content="Open File...";
            Btn.Margin=new Thickness(12);
            Btn.HorizontalAlignment=HorizontalAlignment.Left;
            Btn.Click+=ButtonOnClick;
            LDock.Children.Add(Btn);
            DockPanel.SetDock(Btn, Dock.Top);

            MFrame=new Frame();

            LDock.Children.Add(MFrame);
        }
//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
        private void ButtonOnClick(object Sender, RoutedEventArgs Args)
        {
            OpenFileDialog			Dlg=new OpenFileDialog();

            Dlg.Filter="XAML Files (*.xaml)|*.xaml|All files (*.*)|*.*";

            if (((bool)Dlg.ShowDialog())==true)
            {
                try
                {
                    XmlTextReader		XmlReader=new XmlTextReader(Dlg.FileName);
                    object				Obj=XamlReader.Load(XmlReader);

                    if ((Obj is Window)==true)
                    {
                        Window			Win=Obj as Window;

                        Win.Owner=this;
                        Win.Show();
                    }
                    else
                        MFrame.Content=Obj;
                }
                catch (Exception Exc)
                {
                    MessageBox.Show(Exc.Message, Title);
                }
            }
        }
//-----------------------------------------------------------------------------------------------------------------
	}
//-----------------------------------------------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------------------------------------------