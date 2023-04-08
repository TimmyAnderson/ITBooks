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
// 1. Program demonstruje pouzitie Styles.
// 2. Style sa definuje ako Resource a teda ma definovane meno pomocou, ktoreho potom nastavujem property Style na danom Elemente.
// 3. Style mozem mapovat bud staticky, alebo dynamicky. Pri dynamickom mapovanie ako vytvorim novy objekt Style a ulozim ho do Resource tak sa prilusnym sposobom zmeni Element.
// !!! 4. Properties pouzivaneho Style NEMOZEM ZMENIT - hodi Exception.
// !!! 5. Pomocou Style mozem zmenit LUBOVOLNU DP na LUBOVOLNOM DO. Aj NEVIZUALNU.
// 6. Ak mam na danom Element nastavenu cez Style nejaku property a lokalne na Elemente ju prepisem tak sa aplikuje tato lokalna hodnota.
// !!! 7. Property Style.TargetType sluzi na definovanie Typu na KTORY SA BUDE Style aplikovat. Funguje to nasledovne.
//    A. Ak dam takemuto Sytle meno (Key) potom to velmi nema zmysel, pretoze Style.TargetType sposobi iba tolko, ze NEBUDE MOZNE APLIKOVAT Style na nic ine, ako na dany typ Element.
//    B. AK MU NEDAM MENO (Key) potom sa Style AUTOMATICKY APLIKUJE NA VSETKY Elements DANEHO TYPU v danom Container. Ak ho definujem na urovni Window, tak vsetky Elements daneho typu budu mat tento Style. Ak ho definujem nad nejakym sub-Element tak sa nastavie vsetky Elements totho typu v tomto sub-Element. Inak Key, kedze ho nenastavujem, tak sa nastavi automaticky na meno typu.
// 8. Style samorejme nemusi definovat v Resource, ale aj priamo v danom Elemente a nastavit ju priamo do property Style.
// !!! 9. Ake DP pouzijem je dolezite. Ak napriklad chcem aplikovat Label.TextSize na Button tak NEBUDEM MAT ZIADEN EFEKT. Naopak ak v jednom Style nastavim hodnotu DP a zaroven aj Shared DP tak 'vyhra' to nastvanie, ktore je nizsie v kode.
// !!! 10. V Style pomocou EventSetter mozem nastavit aj RE pre dany Element, ktory sa stane sucastou Style. V praxi vsak pouzitie EventSetter skor prispieva k neprehladnosti sa preto sa nedoporucuje pouzivat.
// !!! 11. Pomocou property Style.BasedOn mozem docielit istu dedinost Styles. Ak v Style nastavim tuto property na iny Style, tak vsetky jeho Setters su aplikovane aj v tomto novo Style a zaroven mozem pripad nove, alebo prepisat hodnoty existujucich. V praxi sa vsak nedoporucuje pouzit, pretoze komplikovana hierachia Styles moze viest k neprehladnosti.
//------------------------------------------------------------------------
namespace StylesTest
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
			Style			S=(Style) this.Resources["MBigFontButtonStyle"];
			Setter			Set=(Setter) S.Setters[0];

			// !!! Hodi Exception.
			Set.Value=30;
		}
//------------------------------------------------------------------------
		private void OnClick2(object Sender, RoutedEventArgs E)
		{
			Style			S=new Style();

			// !!! Musi byt casting na double, aby sedel typ.
			S.Setters.Add(new Setter(Control.FontSizeProperty,(double) 8));
			S.Setters.Add(new Setter(Control.ForegroundProperty,new SolidColorBrush(Colors.Green)));

			this.Resources["MBigFontButtonStyle"]=S;
		}
//------------------------------------------------------------------------
		private void OnByEventSetterClick(object Sender, RoutedEventArgs E)
		{
			MessageBox.Show("Hi ! This Event was set by EventSetter !");
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------