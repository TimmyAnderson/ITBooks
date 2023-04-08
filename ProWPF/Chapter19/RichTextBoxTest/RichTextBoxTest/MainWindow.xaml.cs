using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
//------------------------------------------------------------------------
// 1. Prorgam demonstruje pouzitie RichTextBox.
// 2. RichTextBox interne NEPRACUJE s RTF, alebo s FlowDocument formatom. Preto mozem jednotlive casti dokumentu aj programovo polahky ovladat.
// 3. Text do RichTextBox je mozne nacitat bud pouzitim XamlReader a zapisat cez XamlWriter. Ak chce citat a zapisovat RTF suboery potom mozem pouzit TextRange. Tento umoznuje nacitvat a zapisovat subory ine formaty ako XAML, ci XAML Package.
//------------------------------------------------------------------------
namespace RichTextBoxTest
{
//------------------------------------------------------------------------
	public partial class MainWindow:Window
	{
//------------------------------------------------------------------------
		public MainWindow()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void Button_Click1(object Sender, RoutedEventArgs E)
		{
			LoadSaveTest			Win=new LoadSaveTest();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void Button_Click2(object Sender, RoutedEventArgs E)
		{
			RichTextEditor			Win=new RichTextEditor();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------