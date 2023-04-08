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
using System.Windows.Navigation;
using System.Windows.Shapes;
//------------------------------------------------------------------------
// 1. Program demonstruje komplexny pack syntax pri odkaze na Pages a inych assemblies.
// 2. Ak chcem sa odkazovat na Page v inej assembly mui puzit komplexnu syntax, ktora bude obsahovat nazov assmbly v ktorej je Page definovana. Samozrejme tato assembly musi byt referovana z projektu.
// !!! 3. NIEKTORE Elements DOKAZU DRZAT STAV svojich DP PRI NAVIGACII. Napriklad TextBox. Avsa INE NIE. Nariklad Label, ked som nastavil z kodu a spravil navigaciu tak sa hodila Default hodnota z XAML.
// !!!!! 4. To ktore DP Elements sa budu ukladat pri navigacii urcuje Metadata - Journal. Napriklad TextBox.Text ho ma nastaveny a preto je ulozeny do Journalu a obnovi sa pri navigacii.
// !!! 5. Riesenim problemu z bodu 4 JE NASTAVIT KeepAlive na TRUE cim CELA PAGE SA PRI NAVIGACII BUDE DRZAT V PAMETI a ZACHOVA SA VSETKO VRATANE PRIVATE MEMBERS.
// !!! 6. Pri KeepAlive sa udrzuje Page pri navigacii. Ked vsak klepnem na GyperLink, veducu na tuto Page tak uz sa vytvara nova Page. Teda KeepAlive drzi Page IBA PRI NAVIGACII.
// !!!!! 7. Inym riesenim problemu z bodu 4 je pouzite CUSTOM DP, ktora MA NASTAVENY Journal METADATA NA TRUE.
//------------------------------------------------------------------------
namespace PageHistoryTestClient
{
//------------------------------------------------------------------------
	public partial class MainPage:System.Windows.Controls.Page
	{
//------------------------------------------------------------------------
		private string						MValue="No Value !";
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public MainPage()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void OnLoadClick(object Sender, RoutedEventArgs E)
		{
			MResult.Content=MValue;
		}
//------------------------------------------------------------------------
		private void OnSaveClick(object Sender, RoutedEventArgs E)
		{
			MValue=MTextBox.Text;
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------