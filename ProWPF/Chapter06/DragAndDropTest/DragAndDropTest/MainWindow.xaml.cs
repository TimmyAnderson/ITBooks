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
//------------------------------------------------------------------------
// 1. Program demonstruje Drag and Drop operacie.
// 2. Na Drag and Drop operacie sa pouziva trieda DragDrop.
// !!! 3. Niektore Elements MAJU IMPLICITNE PODPOROVANY Drag and Drop - napriklad TextBox.
// 4. Ak chcem na ine Elements implementovat Drag and Drop musim implementovat niekolko veci.
//    A. Na nejaku akciu - napriklad stlacenie tlacitka mysky - zavolam metodu DragDrop.DoDragDrop() cim ZACNEM Drag and Drop operaciu.
//    B. Na cielovom Elemente nastavim AlowDrop na TRUE.
//    C. Na cielovom Elemente v Evente Drop zachytim a spracujem data.
// !!! 4. Medzi aplikacia sa mozu prenasat iba datove typy, ktore pozna Clipboard.
//------------------------------------------------------------------------
namespace DragAndDropTest
{
//------------------------------------------------------------------------
	public partial class MainWindow:System.Windows.Window
	{
//------------------------------------------------------------------------
		private int						MDropCounter;
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
		private void OnLeftButtonDown(object Sender, MouseButtonEventArgs E)
		{
			DragDrop.DoDragDrop(MLabelSource,"Hello World !",DragDropEffects.All);
		}
//------------------------------------------------------------------------
		private void OnDragEnter(object Sender, DragEventArgs E)
		{
			Debug.WriteLine("\tDragEnter");
		}
//------------------------------------------------------------------------
		private void OnDragLeave(object Sender, DragEventArgs E)
		{
			Debug.WriteLine("\tDragLeave");
		}
//------------------------------------------------------------------------
		private void OnDragOver(object Sender, DragEventArgs E)
		{
			Debug.WriteLine("\tDragOver");
		}
//------------------------------------------------------------------------
		private void OnDrop(object Sender, DragEventArgs E)
		{
			string[]		FormatsArray=E.Data.GetFormats();
			StringBuilder	Formats=new StringBuilder();

			for (int i=0;i<FormatsArray.Length;i++)
			{
				if (i!=0)
					Formats.Append(", ");

				Formats.Append(FormatsArray[i]);
			}

			string			Data=((string) E.Data.GetData(typeof(string))).ToUpper();

			MDropCounter++;
			MLabelDestination.Content=string.Format("Formats: {0}, Data: {1}, Drop Counter: {2} !",Formats.ToString(),Data,MDropCounter);
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------