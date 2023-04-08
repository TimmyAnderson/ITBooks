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
using System.IO;
using System.IO.IsolatedStorage;
using System.Security;
using System.Security.Permissions;
//------------------------------------------------------------------------
// 1. Program demonstruje trivialnu XBAP aplikaciu a jej security obmedzenia.
// !!! 2. Nastavenie security obmedzeni na vyslednu XBAP aplikaciu je mozne zmenit v .csproj subore.
// !!! 3. Medzi niektore security ombedzenia patri aj vyvolavanie Window, Popup, otvaranie suborov ci pristup k DB.
// !!! 4. Pri debugingu ak som rpesunul projekt na ine miesto mozu nastat problemy. Je potrebne zmenit prislusne nastavenie projektu v Project Properties.
// !!!!! 5. Proces XBAP aplikacie nebezi v procese IE, alebo VO VLASTNOM PROCESE a IBA SA RENDERUJE DO IE.
// !!! 6. Pri deployment XBAP je potrebne distribuovat 3 subory. .exe subor, .manifest a .xbap subor. Vsetky tri v tom istom adresari. !!! Entry point do aplikacie je .xbap subor A NIE .exe subor.
// 7. XBAP nie je instalovany na lokalnom PC, ale sa vzdy stiahne z servera cim je zabepzecene verziovanie. IE ho po stiahnuti ulozi do svojej cache.
// 8. XBAP aplikacia ma kluc sluziaci na jej podpis. Tento je v projekte vygenerovany, ale bezne sa pouziva nejaky vlastny - firemny. Pri vydani UPDATE MUSIM POUZIT TEN ISTY KEY.
// !!! 9. Pri UPDATE ak chcem IE prinuti aby skontroloval ci nie je nova verzai na serveri je nutne zvysit verziu v .xbap subore. Najlehsie sa to da dosiahnut tak, ze pouzivam Build->Publish a PRCIOM na Project Properties->Publish zvysim cislo verize.
// !!! 10. Pomocou Project Properties->Security mozem zmenit Security nastavenia XBAP aplikacie.
// !!! 11. Ked dam XBAP FULL-TRUST tak NEBUDE JE MOZNE SPUSTA z Web Server pokial sa nezaregistruje certifikat a niekolko dalsich veci.
// 12. To ci na danu operaciu mam povolenie si mozem overit cez CodeAccessPermission.Demand(). Nie je to ale boh vie aka metoda, kedze vracia Exception ked nemam pristup.
// !!!!! 13. Ak musim nejake data v XBAP PERMANENTE ZAPISAT NA DISK, mozem pouzit IsolationStore, ktory simuluje virtualny file system s dlzkou 512 kB. Je to obdoba PERSISTENT COOKIES z Web aplikacii.
// !!!!! 14. POPUP BEZI, ak ho vytvorim v XAML PAGE. Ako ho vytovrim ako osobitny objekt (MyPage) TAK HODI SECURITY EXCEPTION.
// !!! 15. Ak chcem pouzit XBAP v HTML stranke musim pouzit TAG IFrame.
//------------------------------------------------------------------------
namespace XBAPSimpleTest
{
//------------------------------------------------------------------------
	public partial class MainPage:System.Windows.Controls.Page
	{
//------------------------------------------------------------------------
		public MainPage()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void OnSubPageClick(object Sender, RoutedEventArgs E)
		{
			NavigationService.Navigate(new Uri("SubPage.xaml",UriKind.RelativeOrAbsolute));
		}
//------------------------------------------------------------------------
		// !!!!! Kod vyvolania okna som musel presunut do metody ShowDialog() ak som ho mal tu tak Exception SA HODILA ESTE PRED VSTUPOM DO METODY.
		// ????? .NET asi zistil, ze meotdoa pouziva DialogBox a tak hned hodil UnhandledException.
		private void OnShowDialogBoxClick(object Sender, RoutedEventArgs E)
		{
			try
			{
				ShowDialog();
			}
			catch(Exception Ex)
			{
				MessageBox.Show(string.Format("EXCEPTION: {0} !",Ex.Message));
			}
		}
//------------------------------------------------------------------------
		// !!! Tato metoda sa spustila OK, aj ked potom hodila Exception pri pokuse o pristup na disk.
		private void OnBrowseFileSystemClick(object Sender, RoutedEventArgs E)
		{
			try
			{
				DirectoryInfo		DI=new DirectoryInfo("C:\\");

				MessageBox.Show(string.Format("Directory: {0}, Attributes: {1} !",DI.FullName,DI.Attributes));
			}
			catch(Exception Ex)
			{
				MessageBox.Show(string.Format("EXCEPTION: {0} !",Ex.Message));
			}
		}
//------------------------------------------------------------------------
		private void OnShowPopup1Click(object Sender, RoutedEventArgs E)
		{
			try
			{
				MyPopup				Popup=new MyPopup();

				Popup.IsOpen=true;
			}
			catch(Exception Ex)
			{
				MessageBox.Show(string.Format("EXCEPTION: {0} !",Ex.Message));
			}
		}
//------------------------------------------------------------------------
		private void OnShowPopup2Click(object Sender, RoutedEventArgs E)
		{
			try
			{
				MDialogPopup.IsOpen=true;
			}
			catch(Exception Ex)
			{
				MessageBox.Show(string.Format("EXCEPTION: {0} !",Ex.Message));
			}
		}
//------------------------------------------------------------------------
		private void OnBrowseFileSystemWithSecurityCheckClick(object Sender, RoutedEventArgs E)
		{
			try
			{
				FileIOPermission	Permission=new FileIOPermission(FileIOPermissionAccess.Read, @"C:\");

				if (DoSecurityCheck(Permission)==false)
				{
					MessageBox.Show("YOU DON'T HAVE SECURITY PERRMISION to work with FILE SYSTEM !");
					return;
				}

				DirectoryInfo		DI=new DirectoryInfo("C:\\");

				MessageBox.Show(string.Format("Directory: {0}, Attributes: {1} !",DI.FullName,DI.Attributes));
			}
			catch(Exception Ex)
			{
				MessageBox.Show(string.Format("EXCEPTION: {0} !",Ex.Message));
			}
		}
//------------------------------------------------------------------------
		private bool DoSecurityCheck(CodeAccessPermission RequestedPermission)
		{
			try
			{
				RequestedPermission.Demand();
				return(true);
			}
			catch
			{
				return(false);
			}
		}
//------------------------------------------------------------------------
		private void OnLoadDataFromISClick(object Sender, RoutedEventArgs E)
		{
			try
			{
				IsolatedStorageFile	ISF=IsolatedStorageFile.GetUserStoreForApplication();

				using(IsolatedStorageFileStream S=new IsolatedStorageFileStream("MyISFile.bin",FileMode.Open,FileAccess.ReadWrite,ISF))
				{
					BinaryReader	BR=new BinaryReader(S);
					
					MTextToStore.Text=BR.ReadString();
				}

				MessageBox.Show("Data ware LOADED !");
			}
			catch(Exception Ex)
			{
				MessageBox.Show(string.Format("EXCEPTION: {0} !",Ex.Message));
			}
		}
//------------------------------------------------------------------------
		private void OnSaveDataToISClick(object Sender, RoutedEventArgs E)
		{
			try
			{
				IsolatedStorageFile	ISF=IsolatedStorageFile.GetUserStoreForApplication();

				using(IsolatedStorageFileStream S=new IsolatedStorageFileStream("MyISFile.bin",FileMode.Create,FileAccess.ReadWrite,ISF))
				{
					BinaryWriter	BW=new BinaryWriter(S);
					
					BW.Write(MTextToStore.Text);
				}

				MessageBox.Show("Data ware SAVED !");
			}
			catch(Exception Ex)
			{
				MessageBox.Show(string.Format("EXCEPTION: {0} !",Ex.Message));
			}
		}
//------------------------------------------------------------------------
		private void OnPopupClose(object Sender, RoutedEventArgs E)
		{
			MDialogPopup.IsOpen=false;
		}
//------------------------------------------------------------------------
		private void ShowDialog()
		{
			DialogWindow		DW=new DialogWindow();

			DW.ShowDialog();
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------