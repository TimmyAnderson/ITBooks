using System;
using System.Collections.Generic;
using System.Text;
using System.Reflection;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.Windows.Markup;
using System.IO;
using System.Xml;
//------------------------------------------------------------------------
// 1. Program demonstruje ako je mozne zo standardnych Elements je mozne ziskat ich Template.
// 2. To je dolezite napriklad ked potrebujem zmenit tuto Template tak sa casto vychadza z povodnej Template.
//------------------------------------------------------------------------
namespace DissectingControls
{
//------------------------------------------------------------------------
	public partial class MainWindow:System.Windows.Window
	{
//------------------------------------------------------------------------
		public MainWindow()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void Window_Loaded(object sender, EventArgs e)
		{
			Type			ControlType=typeof(Control);
			List<Type>		DerivedTypes=new List<Type>();
			Assembly		Assembly=Assembly.GetAssembly(typeof(Control));

			foreach (Type Type in Assembly.GetTypes())
				if (Type.IsSubclassOf(ControlType)==true && Type.IsAbstract==false && Type.IsPublic==true)
					DerivedTypes.Add(Type);

			DerivedTypes.Sort(new CTypeComparer());

			MLSTTypes.ItemsSource=DerivedTypes;
		}
//------------------------------------------------------------------------
		private void MLSTTypes_SelectionChanged(object sender, SelectionChangedEventArgs e)
		{
			try
			{
				Type				Type=(Type) MLSTTypes.SelectedItem;
				ConstructorInfo		Info=Type.GetConstructor(System.Type.EmptyTypes);
				Control				Control=(Control) Info.Invoke(null);

				Control.Visibility=Visibility.Collapsed;
				MGrid.Children.Add(Control);

				ControlTemplate		Template=Control.Template;

				XmlWriterSettings	Settings=new XmlWriterSettings();
				Settings.Indent=true;

				StringBuilder		SB=new StringBuilder();
				XmlWriter			Writer=XmlWriter.Create(SB, Settings);

				XamlWriter.Save(Template, Writer);
				MTXTTemplate.Text=SB.ToString();
				MGrid.Children.Remove(Control);
			}
			catch(Exception Err)
			{
				MTXTTemplate.Text = "<< Error generating template: " + Err.Message + " >>";
			}
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------