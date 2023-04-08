using System;
using System.Collections.Generic;
using System.Linq;
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
// 1. Program demonstruje deployment ClickOnce.
// 2. ClickOnce ma limitovane moznosti, napriklad pri vybere cieloveho adresara, moznosti instalovat DB ci assemblies do GAC, ale zas vie bezat aj cez Web a moze byt distribovana cez lubovolne medium. Dokaze aj robit kontrolu novsej verzie SW.
// 3. Publikacia SW cez ClickOnce sa robi pomocou Build->Publish [ProjectName].
// 4. Ako adresar do ktoreho budem publikovat som dal LOKALY ADRESAR: D:\Programy\.NET\C#\ProWPF\Chapter27\MyDeploymentTestApplication\!Published.
// 5. Ako miesto odkial budu uzivatelia instalovat SW som pouzil UNC cestu \\Work\!DeplymentSharedPlace, ktory odkazuje na SHARED FOLDER: D:\Programy\.NET\C#\ProWPF\Chapter27\MyDeploymentTestApplication\!DeplymentSharedPlace.
// !!! 6. ClickOnce robi AUTOMATICKY UPADTE. Teda po uprave a publikacii novej verize ak uzivatel ju ma nainstalovanu, sa skonroluje ci neexistuje nova. Ak ano tak sa opyta uzivatela ci ju je mozne nainstalovat.
// !!!!! 7. Podrobnejsie nastavenie properties pre Publishing je v Project Properties->Publish.
//------------------------------------------------------------------------
namespace MyDeploymentTestApplication
{
//------------------------------------------------------------------------
	public partial class MainWindow:Window
	{
//------------------------------------------------------------------------
		public MainWindow()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void Button_Click(object Sender, RoutedEventArgs E)
		{
			Close();
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------