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
// 1. Program demonstruje pouzitie BindingCollesions v Elements.
// 2. Kazdy ItemControl moze obsahovat Collection. Musim vsak naplnit property ItemsSource objektom dediacim z IEnumerable. Pomocou property DisplayMemberPath stanovim, ktoru property objektov ulozenych v Collection mam zobrazit. Efektivnejsie je pouzit property ItemTemplate, ktoru mozem naplnit na DataTemplate umoznujuc tak zobrazit komplexnu sablonu pre dany DataItem.
// !!! 3. Ak chcem zabezpecit notifikaciu pri zmene obsahu kolekcie (pridavanie, alebo uberanie DataItems) musi Collection implementovat INotifyCollectionChanged.
// !!! 4. Alternativou voci implemnentacii INotifyCollectionChanged na notifikaciu zmeny DataItems je dedit z triedy ObservableCollection, ktora obsahuje autonotifikaciu.
//------------------------------------------------------------------------
namespace BindingCollectionClient
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
			CustomCollectionWindow		Win=new CustomCollectionWindow();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick2(object Sender, RoutedEventArgs E)
		{
			ObservableCollectionWindow	Win=new ObservableCollectionWindow();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------