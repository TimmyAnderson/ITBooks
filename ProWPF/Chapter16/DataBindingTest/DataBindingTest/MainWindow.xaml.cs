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
// 1. Program demonstruje pouzitie DataBinding.
// !!!!! 2. Pri DB viaze Source property v jednom objekte na Destination DP v inom objekte. Destination property MUSI BYT DP. Source proporety NEMUSI BY DP, ale moze.
// !!! 3. Pri najjednoduchsom DB, kedy viazem dve Elements musim nastavit property ElementName na Source meno Elementu a Path, ktory urcuje DP, ktoru chcem naviazat.
// 4. Pomocou SetBinding() je mozne vytvorit DB v kode. Tento je mozne zrusit pomocou metody ClearAllBindings().
// !!!!! 5. ClearValue() maze nielen lokalnu hodnotu ALE AJ BINDING - teda ZRUSI BINDING.
// !!! 6. DB je moze retazit. Teda jeden DB na druhy a ten na treti.
// !!! 7. Na jednu property sice nie je mozne viazat viac ako 1 DB, ale da sa to obist tak, ze pouzijem TwoWay DB. Takto mozem dve a viacej Db naviazat na TU ISTU property.
//------------------------------------------------------------------------
namespace DataBindingTest
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
			SimpleTwoElementsDB			Win=new SimpleTwoElementsDB();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick2(object Sender, RoutedEventArgs E)
		{
			MultipleBindings			Win=new MultipleBindings();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick3(object Sender, RoutedEventArgs E)
		{
			ToOnePropertyMultiDB		Win=new ToOnePropertyMultiDB();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------