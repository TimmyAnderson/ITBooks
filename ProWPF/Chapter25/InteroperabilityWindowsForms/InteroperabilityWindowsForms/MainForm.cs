using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Windows.Forms.Integration;
using WPFWindowLibrary;
//------------------------------------------------------------------------
// 1. Program demonstruje pouzivanie WPF komponent vo WinForms aplikacii.
// 2. Zobrazenie modalneho WPF okna je uplne bez problemov.
// 3. Pri zobrazeni NEMODALNEHO WPF okna je treba volat najprv ElementHost.EnableModelessKeyboardInterop() a ako parameter mu predat odkaz na okno. To zabezpeci, ze nemodalne oknom bude chytat vstup z klavesnice a mysi.
// !!! 4. Ak chcem hostovat WPF Element vo WinForms okne musim pouzit ElementHost WinForms komponentu.
// !!! 5. Takisto aj hostovanie WPF UserControl je bezproblemove a vyuziva sa ElementHost WinForms komponent.
// !!!!! 6. Pred pridavanim WPF UserControl treba projekt PREKOMPILOVAT.
// !!! 7. Kontajnerove komponenty WindowsFormsHost a ElementHost su schopne niektore zakladne property prenasat na property vnorenych WPF\WinForms elementov\komponent. napriklad Foreground, Background, ci Fonty. Potom STACI NATSVIT TUTO PROPERTY NA KONTAJNERI A TA ZMENI PROPERTY SVOJEJ CHILD KOMPONENTY\ELEMENTU.
//------------------------------------------------------------------------
namespace InteroperabilityWindowsForms
{
//------------------------------------------------------------------------
	public partial class MainForm:Form
	{
//------------------------------------------------------------------------
		public MainForm()
		{
			InitializeComponent();

			MyWPFUserControl		WPFUserControl=new MyWPFUserControl();

			// !!! Musel som to pridat rucne, lebo cez GUI to neslo.
			MElementHost.Child=WPFUserControl;
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void MButton_Click1(object Sender, EventArgs E)
		{
			// Vyvolava sa MODALNE WPF okno.
			WPFTestWindow			Win=new WPFTestWindow();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void MButton2_Click(object Sender, EventArgs E)
		{
			WPFTestWindow			Win=new WPFTestWindow();

			// !!! Nato aby bol pri NEMODALNOM okne smerovany INPUT do NEMODALNEHO OKNA je potrebne pouzit metodu EnableModelessKeyboardInterop().
			ElementHost.EnableModelessKeyboardInterop(Win);

			// Okno zobrazujem NEMODALNE.
			Win.Show();
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------