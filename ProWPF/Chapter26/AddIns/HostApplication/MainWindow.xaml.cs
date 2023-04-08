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
using System.Windows.Shapes;
using System.AddIn.Hosting;
using HostView;
//------------------------------------------------------------------------
// 1. Program demonstruje vyuzitie AddIn technologie pri WPF aplikaciach, aj ked ta sa da pouzit aj vseobecne pri inych typoch aplikacii.
// !!! 2. Metoda AddInStore.Update(), ktore parametrom je ROOT cesta k AddIn adresaru vykonava ADDIN DISCOVERY.
// !!! 3. Metoda Update() vytvori 2 CACHE subory s informaciou o adapteroch a views (PipelineSegments.store) a o addins (AddIns.store).
// !!!!! 4. Ak prida novy AddIn je potrebne OPETOVNE VOLAT Update(), alebo Rebuild() na vytvorenie CACHE SUBOROV.
// 5. Vyhladavanie AddIn sa robi pomocou metod FindAddIn() a FindAddIns(). Obe vracaju objekt, alebo kolekciu objektov AddInToken.
// !!! 6. Metodou AddInToken.Activate<T>() AddIn AKTIVUJEM a mozem ho pouzivat.
// !!!!! 7. AddIn sa zvycane prida do NOVEJ APP DOMAIN.
// 8. Pomocou AddInController.Shutdown() je mozne vypnut AddIns ak je to potrebne.
//------------------------------------------------------------------------
namespace HostApplication
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
		private void Window_Loaded(object Sender, RoutedEventArgs E)
		{
			// !!! Vykonam Update() AddIn CACHE.
			string			Path=Environment.CurrentDirectory;

			AddInStore.Rebuild(Path);
			AddInStore.Update(Path);

			IList<AddInToken>	Tokens=AddInStore.FindAddIns(typeof(CImageProcessorHostView), Path);

			// Naplnim zoznam najdenymi AddIns.
			MLSTAddIns.ItemsSource=Tokens;
		}
//------------------------------------------------------------------------
		private void CmdProcessImage_Click(object Sender, RoutedEventArgs E)
		{
			if (MLSTAddIns.SelectedItem==null)
				return;

			// Copy the image information from the image to a byte array.
			BitmapSource				Source=(BitmapSource) MImage.Source;
			int							Stride=Source.PixelWidth*Source.Format.BitsPerPixel/8;

			Stride=Stride+(Stride%4)*4;

			int							ArraySize=Stride*Source.PixelHeight*Source.Format.BitsPerPixel/8;
			byte[]						OriginalPixels=new byte[ArraySize];

			Source.CopyPixels(OriginalPixels, Stride, 0);

			// Vyberiem selectovany Token.
			AddInToken					Token=(AddInToken) MLSTAddIns.SelectedItem;

			// Ziskam HostView.
			CImageProcessorHostView		Addin=Token.Activate<CImageProcessorHostView>(AddInSecurityLevel.Internet);

			// Vytvorim objekt IMPLEMENTUJUCI CALLBAK ROZHRANIE ADDIN.
			CAutomationHost				AutomationHost=new CAutomationHost(MProgressBar,this.Dispatcher);

			MProgressBar.Value=0;

			// Inicializujem Callback.
			Addin.Initialize(AutomationHost);

			// !!!!! Progress vsak nevidiet. Bolo by treba robit v AddIn volanie Callback v INOM THREADE sa samozrejme vsetko synchronizovat cez Dispatcher.

			// !!! Pouzijem AddIn na konverziu bitmapy.
			byte[]						ChangedPixels=Addin.ProcessImageBytes(OriginalPixels);

			// Vytvorim novu bitmapu S DATAMI MODIFIKOVANYMI V PLUGINE.
			BitmapSource				NewSource=BitmapSource.Create(Source.PixelWidth, Source.PixelHeight, Source.DpiX, Source.DpiY, Source.Format, Source.Palette, ChangedPixels, Stride);

			MImage.Source=NewSource;
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------