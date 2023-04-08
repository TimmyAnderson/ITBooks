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
// 1. Program demosntruje pouzitie TypeConverter.
// 2. TypeConverter sluzi na konverziu medzi XAML retazcom a realnym objektom, ktory ma byt zanho nahradeny.
// 3. Mam dve moznost ako aplikovat TypeConverters. Bud ich aplkujem na property Custom Class, kde chcem aby sa pouzil. Durhou mnoznost je ju aplikovat na cielovu triedu, teda typ property, ktoru chcem z XAML naplnat.
// !!! 4. Vyzera to, ze z celej triedy TypeConverter staci IMPLEMENTOVAT IBA METODU ConvertFrom(ITypeDescriptorContext Context, CultureInfo Culture,object Value). Ostatne neboli volane.
// !!!!! 5. Program zaroven demonstruje pouztie komplexnej syntaxe pre vytvorenie obejktov v XAML.
// !!!!! 6. KEDZE XAML VYTVARA OBJEKTY VZDY TAK, ZE POUZIJE PRAZDNY OBJEKT (vytvoreny cez default konstruktor) A POTOM NASTAVUJE JEHO PROPERTIES MUSI MAT KAZDA CUSTOM CLASS DEFUALT CONSTRUCTOR.
// !!! 7. Program demonstruje pouzitie MarkupExtension. Tak sa pouziva pri incializacii komplexnejsich objektov v XAML, ktore je cez '{}' syntax dekalarovat.
// 8. Na definovanie CUSTOM MarkupExtension musim splnit nasledujuce podmienky.
//    A. Definovat triedu zdedenu z MarkupExtension.
//    B. Implementovat metodu ProvideValue().
//    C. Implementovat konstruktor s takym poctom parametrov, ktore budem naplnat v XAML.
//    D. Ak nechcem konstruktor mozem definovat aj properties a k nim pristupovat pomocou property syntaxe z XAML.
//------------------------------------------------------------------------
namespace XAMLConverter
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
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------