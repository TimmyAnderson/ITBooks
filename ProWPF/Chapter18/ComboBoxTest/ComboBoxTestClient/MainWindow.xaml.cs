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
//------------------------------------------------------------------------
// 1. Program demonstruje pouzitie ComboBox.
// 2. ComboBox moze byt editovatelny, alebo needitovatelny. Kazdy ComboBox moze obsahovat komplexnejsi content, ktory moze obsaovat rozlicne Elements.
// !!! 3. Avsak ak dam do ComboBox Item nejake Controls, napdiklad Button tak na tomto Button NEBUDE MOZNE KLIKNUT.
// !!! 4. Ak mam velmi vela Items v ComboBoxe tak pri rozkliku sa velmi dlho otvaraju. Riesenim je pouzitie VirtualizingStackPanel v ItemsPanelTemplate.
// !!! 5. Ak pouzivam komplexny content pre Item tak sa standardne zobrazi ako SelectedItem bude SAMOTNY ITEM - ak je okno needitovatelne, alebo text. Standardne sa pouzije ToString() daneho Itemu, co mozem zmenit nastavenim TextSearch.TextPath na property, ktora sa ma zobrazit namiesto neho.
//------------------------------------------------------------------------
namespace ComboBoxTestClient
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
		private void OnClick1(object Sender, RoutedEventArgs E)
		{
			SimpleComboBox				Win=new SimpleComboBox();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick2(object Sender, RoutedEventArgs E)
		{
			EditableComboBox			Win=new EditableComboBox();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------