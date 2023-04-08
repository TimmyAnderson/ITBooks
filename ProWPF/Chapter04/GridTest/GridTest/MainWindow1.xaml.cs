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
// 1. Program demonstruje rozlicne aspekty Grid.
// !!! 2. V ramci jednej cell MOZE BYT VIAC Elements.
// !!!!! 3. V CELL mozem pouzivat Alignment ci Margin tak ako na inych Panels.
// !!!!! 4. Ked vsak zmensim okno tak, ze sa jednotlive Elements do CELL nezmestia tak sa zacnu prekryvat. To co sa bude prekryvat zavisi ZIndex a ten zas od poradia Elements v XAML.
// 5. Pomocou properties Grid.ColumnSpan a Grid.RowSpan mozem roztahovat Elements tak aby zaberali viacero Columns, alebo Rows.
// 6. Pomocou properties ColumnDefinition.Width a RowDefinition.Height mozem definovat proporcne velkosti riadkov a sirk stlpcov. Mozem pouzit STAR konvenciu, kedy definujem specialnou konvenciu proporcne, alebo absolutne velkosti stlpcov a riadkov.
//    A. Ak definujem hodnotu Auto potom sa velkost stlpca ci riadka odvija od velkosti Content a ak je ten prazdy pootom je jeho velkosti rovna 0.
//    B. Ak definujem ABSOLUTNU hodnotu - teda cislo - potom je tato hodnota PEVNA a NEMENNA a udava absolutnu velkost stlpca ci riadku.
//    C. Ak definujem RELATIVNU hodnotu cez STAR KONVENCIU (Number*, napriklad 2*) potom su zo ZVYSKU oblasit (po odratani stlpcov a riadkov v aboslutnou velkostou) vypocitane PROPORCNE velkosti riadkov a stlpcov.
// 7. Pri pouziti GridSplitter mozem jednotlive Rows a Columns roztahovat a stahovat a vytvorit tak funkcionalitu klasickeho Splitter.
// !!!!! 8. GridSplitter roztahuje VZDY CELY RIADOK, alebo CELY STLPEC a preto ho ma zmysel roztiahnut na cely riadok, alebo cely stlpec.
// !!!!! 9. EXTREMNE DOLEZITE je definovat HorizontalAlignment a VerticalAlignment. PRAVE TIE URCUJU ORIENTACIU GridSplitter. A MUSIM definovat aj Width, resp. Height podla orientacie INAK BUDE SPLITTER NEVIDITELNY.
// !!! 10. Pomocou DP SharedSizeGroup mozem nasatvit meno skupiny na Column, ci Row, ktoreho velkost bude zdielana s inym Column ci Row DOKONCA V NIM GRIDE.
// !!!!! 11. Nato aby k zdielaniu doslo musi mat parent Element vsetkych Grid, ktore maju shared groups nastaveny Grid.IsSharedSizeScope na TRUE.
//------------------------------------------------------------------------
namespace GridTest
{
//------------------------------------------------------------------------
	public partial class MainWindow1:System.Windows.Window
	{
//------------------------------------------------------------------------
		public MainWindow1()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------