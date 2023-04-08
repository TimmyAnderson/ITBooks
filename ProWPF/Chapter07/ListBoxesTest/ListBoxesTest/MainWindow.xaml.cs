using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
//------------------------------------------------------------------------
// 1. Program demonstruje ListBoxes.
// 2. ListBox moze mat 3 mody selekcie. SingleSelect, MultiSelect a Extended. Posledne 2 sa lisia iba formou ako sa selectuju viacere items.
// !!!!! 3. Do ListBox je mozne umiestnost LUBOVLNE OBJEKTY. Zvycajne sa vsak vklada ListBoxItem, ktory je WRAPPEROM k inym objektom, ale NIE JE TO NUTNE.
//------------------------------------------------------------------------
namespace ListBoxesTest
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
		private void OnSelectionChanged(object Sender, SelectionChangedEventArgs E)
		{
			Debug.WriteLine("\tAdded Items:");

			foreach (StackPanel SP in E.AddedItems)
				Debug.WriteLine(string.Format("\t\tItem: {0} !",SP.Name));

			Debug.WriteLine("\tRemoved Items:");

			foreach (StackPanel SP in E.RemovedItems)
				Debug.WriteLine(string.Format("\t\tItem: {0} !",SP.Name));
		}
//------------------------------------------------------------------------
		private void OnSelected1(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine("Green SELECTED !");
		}
//------------------------------------------------------------------------
		private void OnSelected2(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine("Blue SELECTED !");
		}
//------------------------------------------------------------------------
		private void OnSelected3(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine("Yellow SELECTED !");
		}
//------------------------------------------------------------------------
		private void OnSelected4(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine("Red SELECTED !");
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------