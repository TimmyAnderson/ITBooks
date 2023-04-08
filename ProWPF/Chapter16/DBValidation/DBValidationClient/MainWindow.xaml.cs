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
using DBValidationLibrary;
//------------------------------------------------------------------------
// 1. Program demonstruje pouzitie DB Validation.
// 2. DB Validation sluzi na kontrolu udajov, ktore uzivatel zada pomocou GUI.
// 3. Existuje niekolko moznosti, ako validovat vstup.
//    A. V Setter property CUSTOM datoveho objektu (CName) je mozne hodit Exception ak vstupny udaj nesedi. V pripade, ze je tato property mapovana na GUI cez DB tak standardne ju DB IGNORTUJE a novu hodnotu NEZOBRAZI, ale chybu neindikuje. Toto snandardne chovanie je mozne zmenit pouzitim ExceptionValidationRule.
//    B. Pouzitim ValidationRules, ktore validuju dany vstup a v pripade chyby zobrazia chybu a naplnia prislusne properties informaciou o chybe.
// !!! 4. Validovanie sa robi pomocou ValidationRules - kolekcie, ktoru ma kazdy Element. Do tejto kolekcie ukladam jednotlive instancie potomkov triedy ValidationRule, ktore VYKONAVAJU SAMOTNU VALIDACIU.
// !!! 5. Do ValidationRules mozem ulozit nasledujuce ValidationRule obejkty.
//    A. Custom ValidationRule, co je CUSTOM trieda dediaca z ValidationRule.
//    B. DataErrorValidationRule, ktory vyuziva IDataErrorInfo rozhranie, ktore musi moj datovy objekt (CName) impelentovat. Jeho implementacia spociva najme v implementacii Indexera, ktoreho parametrom je meno prperty. Indexer musi skontrolovat ci data tejto property nie su chybne a ak ano vratit chybovu hlasku, alebo NULL ak je vsetko OK.
//    C. ExceptionValidationRule, ktory zachytava VSETKY EXCEPTIONS, ako z Settera, alebo aj Convertera a konvertuju tuto Exception na chybu - pozri nizsie.
// !!! 6. Ak validacia ZLYHA potom.
//    A. Je nastavena property Validation.HasError na TRUE.
//    B. Objekt ValidationError je vytvoreny a pridany do collection Validation.Errors.
//    C. Event Validation.Error je odpaleny ak Binding.NotifyOnValidationError je nastaveny na TRUE.
//    D. Pomocou CT ulozenej v Validation.ErrorTemplate sa zobrazi nejaky chybovy indikator vedla Elementu.
// !!! 7. Pri zobrazovani chyby pomocou ErrorTemplate sa pouziva Adorner, ktory umoznuje KRESLIT NA POVRCHU Window, BEZ TOHO ABY SA ZMENIL LAYOUT Window. Je to ako virtualny layer nad celym Window. Ak chcem kreslit chybu pri Elemente, ktory ju sposobil mozem v CT pouzit Element AdornedElementPlaceholder, ktory urcuje Element, ktory chybu sposobil a ja mozem tak okolo neho vykreslit indikator chyby. Standardne je to cerveny Border okolo Elementu.
// !!!!! 8. Validacia sa uplatnuje IBA pri OneWayToSource, alebo TwoWay DB.
// !!!!! 9. VYZERA TO TAK, ZE EXCEPTIONS Z CONVERTERA ANI ExceptionValidationRule NEZACHYTAVA A SKONCIA NEOSETRENOU EXCEPTION.
// !!!!! 10. IDataErrorInfo.INDEXER sa vola OKAMZITE POTOM AKO SA vola EVENT PropertyChanged.
//------------------------------------------------------------------------
namespace DBValidationClient
{
//------------------------------------------------------------------------
	public partial class MainWindow:System.Windows.Window
	{
//------------------------------------------------------------------------
		private CName						MName1=new CName("Timmy","Anderson",12);
		private CName						MName2=new CName("Timmy","Anderson",12);
		private CName						MName3=new CName("Timmy","Anderson",12);
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public MainWindow()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void OnWindowLoaded(object Sender, RoutedEventArgs E)
		{
			MSP1.DataContext=MName1;
			MSP2.DataContext=MName2;
			MSP3.DataContext=MName3;
		}
//------------------------------------------------------------------------
		private void OnValidationError(object Sender, ValidationErrorEventArgs E)
		{
			string			Message=string.Format("A: {0}, E: {1}, R: {2}, C: {3} !",E.Action,(E.Error.Exception!=null) ? E.Error.Exception.Message : "NULL",E.Error.RuleInError,E.Error.ErrorContent);

			MessageBox.Show(Message);			
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------