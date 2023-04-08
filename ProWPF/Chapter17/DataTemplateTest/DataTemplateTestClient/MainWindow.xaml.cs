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
// 1. Program demonstruje pouzitie DataTemplate pri DB.
// 2. DT (implementovana triedou DataTemplate) sluzi na zobrazovanie dat v Elements.
// !!! 3. DT je mozne aplikovat dvoma sposobmi.
//    A. Na ContentControls pomocou property ContentTemplate, kde DT obali Content daneho Elementu.
//    B. Na ItemsControl pomocou ItemTemplate, kde tento DT je aplikovany na KAZDY ITEM.
// 4. Trieda DataTemplate ma property DataType, ktorou je mozne definovat typ dat na ktore sa tato Dt v danom Scope bude AUTOMATICKY APLIKOVAT.
// 5. Do DT mozem ukladat aj Controls ako Button. Kedze Handlers na Events z tychto Cotnrols su spolocne pre vsetky Items je dobre ich identifikovat pomocou DB napriklad vyuzitim property Tag.
// !!! 6. Pri pouziti Control v DT je treba dat pozor nato, ze Control zareaguje (stlaci sa Button) ak ked nie je Selected. Najlepsie je v Handlery na tuto udalost zmeni SelectedItem daneho ItemControl, aby v tom nemal uzivatel chaos.
// 7. DT mozem dynamicky na zaklade hodnoty Item menit troma sposobmi.
//    A. Pouzijem DT Triggers, kde zmenim hodnotu nejakej property DT na zaklade hodnoty Itemu. Pouzivam DataTrigger, ktory sledue NIE ZMENY DP, AKO Trigger, ALE ZMENY BINDINGU.
//    B. Pouzijem Converter, kde Converter konvertuje hodnotu Itemu napriklad na Brush, ak chcem aby Item s istou hodnotou bol vykresleny inou hodnotou.
//    C. Pouzijem DT Selector. DT Selector je trieda zdedena z DataTemplateSelector a v jej metode SelectTemplate() mozem vybrat DT, ktoru na dany Item aplikujem. Jednou NEVYHODOU je, ze DT sa aplikuje IBA RAZ a pri zmenach, ak su Items editable sa NEREAPLIKUJE AUTOMATICKY. Najlepsie sa ro robi pomocou znovu priradenie property ItemTemplateSelector.
// !!! 8. ItemsControls nepodporuju osobitnu DT pre SelectedItem. Tento nedostatok sa da obist pri malych zmenach - napriklad specialnom vyfarbeni Itemu pomocou Triggera. Ak chcem vecsiu zmenu, napriklad zobrazit pre selectovany Item dodatocne data mozem pouzit fintu, kedy zobrazim pre kazdy Item vsetky data a tie, ktore sa maju zobrazovat iba pri SelectedItem zatmavim - Visibility==FALSE. Ak je Item selectnuty tak nastavim VISIBILITY na TRUE pre tento Item.
// 9. Pomocou property ItemContainerStyleSelector mozem implementovat vlastny StyleSelector (triedu zdedenu z StyleSelector), ktorym mozem pre KAZDY ITEM nastavit INY STYLE. Plati podobne ombedzenie ako pri DT a to, ze sa alikuje iba raz pri nacitavani a teda ak pridam novy Item tak sa nereaplikuje. Riesenie je ho reaplikovat rucne.
// 10. Pomocou property ItemsPanel je mozne nastavit vlastnu ItemsPanelTemplate, ktora umoznuje zmenit SPOSOB ZOBRAZOVANIA ITEMS. Standardne sa Items ukladaju pod seba. Tymto je mozne zmenit zobrazenie.
//------------------------------------------------------------------------
namespace DataTemplateTestClient
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
			NoDataTemplate				Win=new NoDataTemplate();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick2(object Sender, RoutedEventArgs E)
		{
			AutoDataTemplate			Win=new AutoDataTemplate();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick3(object Sender, RoutedEventArgs E)
		{
			SimpleDataTemplate			Win=new SimpleDataTemplate();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick4(object Sender, RoutedEventArgs E)
		{
			DataTemplateWithConvertor	Win=new DataTemplateWithConvertor();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick5(object Sender, RoutedEventArgs E)
		{
			DataTemplateWithButton		Win=new DataTemplateWithButton();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick6(object Sender, RoutedEventArgs E)
		{
			DTTriggers					Win=new DTTriggers();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick7(object Sender, RoutedEventArgs E)
		{
			DTWithConvertorChanges		Win=new DTWithConvertorChanges();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick8(object Sender, RoutedEventArgs E)
		{
			DTSelector					Win=new DTSelector();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick9(object Sender, RoutedEventArgs E)
		{
			SelectedItemTrigger			Win=new SelectedItemTrigger();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick10(object Sender, RoutedEventArgs E)
		{
			SelectedItemDT				Win=new SelectedItemDT();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick11(object Sender, RoutedEventArgs E)
		{
			SelectedItemVisible			Win=new SelectedItemVisible();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick12(object Sender, RoutedEventArgs E)
		{
			StyleSelector				Win=new StyleSelector();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick13(object Sender, RoutedEventArgs E)
		{
			ChangingItemLayout			Win=new ChangingItemLayout();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------