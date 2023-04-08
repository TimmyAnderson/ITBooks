using System;
using System.Collections.Generic;
using System.Text;
using System.Collections;
using System.Reflection;
using System.Diagnostics;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.Windows.Resources;
using System.IO;
using System.Resources;
using System.Globalization;
//------------------------------------------------------------------------
// 1. Program demonstruje pouzitie Assembly Resources.
// !!! 2. Vo WPF MUSIA byt VSETKY Resources linkovane ako 'Resource' a nie 'Embedded Resource', ktory je urceny pre Win Forms. WPF vie precovat s 'Resource' Build Action.
// 3. VSETKY Resources su ukladane do JEDNEHO BINARNEHO STREAMU (AssemblyName.g.resources) s ktorym vie WPF pracovat a vytahovat si z neho jednotlive Resources.
// 4. Aj BAML subor je ukladany do TOHTO STREAMU.
// 5. Images sa daju v XAML zaviest pomocou jednoudchej syntaxe, relativnej tak ako mam adresarovu strukturu. V tomto pripade Ak dam Source na Image Elemente na 'Images/Celestial.jpg' tak ziskam dany resource. Tento resource mozem zikat aj programovo.
// !!! 6. WPF pouziva ako standard syntax odvodenu od XPS. Je mozne pouzit aj je shortcut, kde neuvediem cast 'pack://application:,,,'.
// !!! 7. Pomocou XPS sa mozem polahky odkazat na Resource v inej assembly napriklad takto: 'pack://application:,,,/AssemblyResourcesTestLibrary;component/LibImages/SadFace.jpg'.
// !!! 8. Takisto sa mozem odkazat aj na silne podpisanu assembly cez: 'ImageLibrary;v1.25;dc642a7f5bd64912;component/images/winter.jpg', kde casti strong name su oddelene znakom ';'.
// 9. Ak nechcem mat Resources PRIAMO ZAHRNUTE DO ASSEMBLY mozem pouzit BuildAction 'Content', ktora nezahrnie Resource do DLL, ale ozaci si RELATIVNU CESTU k nemu v assembly.
// !!! 10. Obrovskou vyhodou BuildAction 'Content' je, ze MOZEM POUZIVAT TU ISTU SYNTAX NA PRISTUP K TAKEMUTO RESOURCE. Avsak MUSIM MAT NASVATEVNY 'Copy to Output Directory' na 'Copy Always', aby sa subor prekopiroval k DLL.
// !!!!! 11. WPF NEDOKAZE PREHREVAT ZVUKY PRIAMO Z RESOURCES. Preto ich musim distribuovat ako extra subory a to sa najlepsie robi prave pomocou BuildAction 'Content'.
//------------------------------------------------------------------------
namespace AssemblyResourcesTestClient
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
		private void OnButton1Click(object Sender, RoutedEventArgs E)
		{
			// Programove ziskanie resource.
			StreamResourceInfo		SRI=Application.GetResourceStream(new Uri("Images/Celestial.jpg", UriKind.Relative));
			Stream					S=SRI.Stream;

			Debug.WriteLine(string.Format("ContentType: {0}, Stream Length: {1} !",SRI.ContentType,S.Length));
		}
//------------------------------------------------------------------------
		private void OnButton2Click(object Sender, RoutedEventArgs E)
		{
			// Nacitanie Resource cez ResourceManager.
			Assembly				A=Assembly.GetAssembly(this.GetType());
			string					ResourceName=A.GetName().Name + ".g";
			ResourceManager			RM=new ResourceManager(ResourceName, A);

			using (ResourceSet Set=RM.GetResourceSet(CultureInfo.CurrentCulture, true, true))
			{
				UnmanagedMemoryStream	S;

				// Ked je 2. parameter na true, tak porovnanie mena je case-insensitive.
				S=(UnmanagedMemoryStream) Set.GetObject("Images/Celestial.jpg", true);

				Debug.WriteLine(string.Format("Name: {0}, Stream Length: {1} !","Images/Celestial.jpg",S.Length));
			}
		}
//------------------------------------------------------------------------
		private void OnButton3Click(object Sender, RoutedEventArgs E)
		{
			Assembly					A=Assembly.GetAssembly(this.GetType());
			string						ResourceName=A.GetName().Name + ".g";
			ResourceManager				RM=new ResourceManager(ResourceName, A);

			Debug.WriteLine("List of Resources:");

			using (ResourceSet Set=RM.GetResourceSet(CultureInfo.CurrentCulture, true, true))
			{
				foreach (DictionaryEntry Res in Set)
				{
					UnmanagedMemoryStream	S=(UnmanagedMemoryStream) Res.Value;

					Debug.WriteLine(string.Format("\tName: {0}, Stream Length: {1} !",Res.Key,S.Length));
				}
			}
		}
//------------------------------------------------------------------------
		private void OnButton4Click(object Sender, RoutedEventArgs E)
		{
			SubWindow			SW=new SubWindow();

			SW.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnToggleButtonClick(object Sender, RoutedEventArgs E)
		{
			if (MToggleButton.IsChecked==true)
				MSound.Play();
			else
				MSound.Stop();
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------