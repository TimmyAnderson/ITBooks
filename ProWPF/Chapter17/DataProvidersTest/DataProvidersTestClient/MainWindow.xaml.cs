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
// 1. Program demonstruje pouzitie DataProviders.
// 2. ObjectDataProvider umoznuje inicalizovat DataSource Z XAML a to tak, ze ObjectDataProvider je schopny vytvorit a volat metodu nejakej CUSTOM triedy a tym naplnit DataSource. Je takisto schopny vykonat volanie asynchronne.
// 3. XmlDataProvider je jednoducha trieda, ktora je schopna nacitat DatSource z XML SUBOR. Avsak IBA Z XML SUBORU.
// !!! 4. Aj Binding na IsAsynchronous, ktorym je mozne realizovat DB ASYNCHRONNE. Ale je to SPROSTOST, kedze asynchronne sa realizuje IBA VOLANIE PROPERTY, KTOROU SA CITAJU DATA. Takze iba ak by tato property obsahovala komplexny a casovo narocny kod tak by to malo zmysel.
//------------------------------------------------------------------------
namespace DataProvidersTestClient
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
		private void OnClick1(object Sender1, RoutedEventArgs E)
		{
			ObjectDataProvider		Win=new ObjectDataProvider();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick2(object Sender1, RoutedEventArgs E)
		{
			XMLDataProvider			Win=new XMLDataProvider();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------