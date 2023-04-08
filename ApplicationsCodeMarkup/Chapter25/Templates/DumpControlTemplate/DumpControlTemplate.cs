using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Markup;
using System.Xml;
//-------------------------------------------------------------------------------------------------------
namespace NamespaceDumpControlTemplate
{
//-------------------------------------------------------------------------------------------------------
	public partial class DumpControlTemplate : Window
	{
//-------------------------------------------------------------------------------------------------------
        private Control											MCtrl;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        public DumpControlTemplate()
        {
            InitializeComponent();
        }
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        private void ControlItemOnClick(object Sender, RoutedEventArgs Args)
        {
            for (int i=0;i<MGrid.Children.Count;i++)
			{
                if (Grid.GetRow(MGrid.Children[i])==0)
                {
                    MGrid.Children.Remove(MGrid.Children[i]);
                    break;
                }
			}

            MTxtBox.Text="";

            MenuItem			Item=Args.Source as MenuItem;
            Type				LType=(Type) Item.Tag;
            ConstructorInfo		Info=LType.GetConstructor(Type.EmptyTypes);
            
            try
            {
                MCtrl=(Control)Info.Invoke(null);
            }
            catch (Exception Exc)
            {
                MessageBox.Show(Exc.Message, Title);
                return;
            }

            try
            {
                MGrid.Children.Add(MCtrl);
            }
            catch
            {
                if ((MCtrl is Window)==true)
                    (MCtrl as Window).Show();
                else
                    return;
            }

            Title=Title.Remove(Title.IndexOf('-')) + "- " + LType.Name;
        }
//-------------------------------------------------------------------------------------------------------
        private void DumpOnOpened(object Sender, RoutedEventArgs Args)
        {
            MItemTemplate.IsEnabled=(MCtrl!=null);
            MItemItemsPanel.IsEnabled=((MCtrl!=null) && (MCtrl is ItemsControl)==true);
        }
//-------------------------------------------------------------------------------------------------------
        private void DumpTemplateOnClick(object sender, RoutedEventArgs Args)
        {
            if (MCtrl!=null)
                Dump(MCtrl.Template);
        }
//-------------------------------------------------------------------------------------------------------
        private void DumpItemsPanelOnClick(object Sender, RoutedEventArgs Args)
        {
            if (MCtrl!=null && (MCtrl is ItemsControl)==true)
                Dump((MCtrl as ItemsControl).ItemsPanel);
        }
//-------------------------------------------------------------------------------------------------------
        private void Dump(FrameworkTemplate Template)
        {
            if (Template!=null)
            {
                XmlWriterSettings		Settings=new XmlWriterSettings();

                Settings.Indent=true;
                Settings.IndentChars=new string(' ', 4);
                Settings.NewLineOnAttributes=true;

                StringBuilder			StrBuild=new StringBuilder();
                XmlWriter				XMLWrite=XmlWriter.Create(StrBuild, Settings);

                try
                {
                    XamlWriter.Save(Template, XMLWrite);
                    MTxtBox.Text=StrBuild.ToString();
                }
                catch (Exception Exc)
                {
                    MTxtBox.Text=Exc.Message;
                }
            }
            else
                MTxtBox.Text="no template";
        }
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------