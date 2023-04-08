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
using System.Windows.Controls.Primitives;
//------------------------------------------------------------------------
// 1. Program demonstruje Popups.
// 2. Popup je velmi podobny ToolTips, ale nezobrazuje sa automaticky, ale programovo a podla nastavenia sotavaju viditelne az pokym neklepnem na niekde na plochu Window.
// !!! 3. Popup MOZE MAT INTERAKTIVNE Elements NA ROZDIEL OD ToolTips.
// !!!!! 4. Kedze sa Popup NEZOBRAZUJE AUTOMATICKY tak MOZE BYT UMIESTNENY KDEKOLVEK V XAML.
// !!! 5. Ak chcem Popup zobrazit musim pouzit property IsOpen.
// !!! 6. Pomocou property PopupAnimation mozem urobit animaciu zorbazovania popup, ale property AllowsTransparency musi byt na TRUE.
// 7. Instanicu Popup na rozdiel od dialogovych okien mozem otvorit a zavriet viac krat.
// !!!!! 8. Popup NEMA IMPLICITNY BORDER a PRETO MU HO MUSIM PRIDAT ak chcem aby popup vyzeral nejako normalne.
// !!! 9. Obsah Popup moze byt zobrazeny aj mimo MAIN WINDOW.
//------------------------------------------------------------------------
namespace PopupTest
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
		private void OnShowPopupClick1(object Sender, RoutedEventArgs E)
		{
			// Zobraz Popup.
			MMyPopup1.IsOpen=true;
		}
//------------------------------------------------------------------------
		private void OnShowPopupClick2(object Sender, RoutedEventArgs E)
		{
			// Zobraz Popup.
			MMyPopup2.IsOpen=true;
		}
//------------------------------------------------------------------------
		private void OnShowPopupClickBoth(object Sender, RoutedEventArgs E)
		{
			MMyPopup1.IsOpen=true;
			MMyPopup2.IsOpen=true;
		}
//------------------------------------------------------------------------
		private void OnPopupOKClick1(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine(string.Format("TextBox: {0} !",MTextBox1.Text));
			
			// Skyjem Popup.
			MMyPopup1.IsOpen=false;
		}
//------------------------------------------------------------------------
		private void OnPopupOKClick2(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine(string.Format("TextBox: {0} !",MTextBox2.Text));
			
			// Skyjem Popup.
			MMyPopup2.IsOpen=false;
		}
//------------------------------------------------------------------------
		private void OnShowMyPopupClick(object Sender, RoutedEventArgs E)
		{
			MyPopup			MP=new MyPopup();

			MP.IsOpen=true;
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------