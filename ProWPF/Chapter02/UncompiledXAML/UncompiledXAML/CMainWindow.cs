using System;
using System.Collections.Generic;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.IO;
using System.Windows.Markup;
//------------------------------------------------------------------------
// 1. Program demonstruje WPF program BEZ KOMPILOVANEHO XAML kodu.
// 2. Ten sa dynamicky nacita zo suboru, dalej namapujem Elements a ich events a spusim program.
// !!! 3. Vyhodou tohto postupu je vyssia variablitia, naopak nevyhodou je pomalsie spracovanie.
//------------------------------------------------------------------------
namespace UncompiledXAML
{
//------------------------------------------------------------------------
	public class CMainWindow : Window
	{
//------------------------------------------------------------------------
		private TextBox						MTextBox;
		private Button						MButton;
		private Label						MLabel;
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public CMainWindow()
		{
			this.Width=this.Height=285;
			this.Left=this.Top=100;
			this.Title="Dynamically Loaded XAML";

			FileStream			S=new FileStream("..//..//InputXAML.xml", FileMode.Open);
			DependencyObject	RootElement=(DependencyObject) XamlReader.Load(S);

			S.Close();

			this.Content=RootElement;

			MTextBox=(TextBox) LogicalTreeHelper.FindLogicalNode(RootElement, "MTextBox");
			MButton=(Button) LogicalTreeHelper.FindLogicalNode(RootElement, "MButton");
			MLabel=(Label) LogicalTreeHelper.FindLogicalNode(RootElement, "MLabel");

			MButton.Click+=OnClick;
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void OnClick(object Sender, RoutedEventArgs E)
		{
			MLabel.Content=MTextBox.Text.ToUpper();
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------