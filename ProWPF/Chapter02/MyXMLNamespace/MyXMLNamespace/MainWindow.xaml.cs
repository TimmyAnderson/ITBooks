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
// 1. Program MAL demonstrovat moznost deklarovat mapovanie medzi XML namespace a CLR namespace.
// !!! 2. Bohuzial z nejakeho dovodu NEFUNGUJE. Na Webe som nasiel, zeby to fungovat malo, no kompilator kasle nato. DOVOD NEPOZNAM.
// !!!!! 3. Ked mam triedu v INEJ DLL, musim do deklaracie XML namespace pridat aj 'assembly'.
// !!!!! 4. Vyzera to, ze ked dam triedy do INEJ DLL a na nu sa referujem z XAML DOKONCA AJ POMOCOU XAML NAMESPACE tak to bezi. Ak vsak tut triedu mam v TOM ISTOM PROJEKTE AKO XAML tak to nezbehne.
// !!!!! 5. Takisto to vyzera, ze [XmlnsDefinition] MUSIM DEKLAROVAT v AssemblyInfo.cs.
//------------------------------------------------------------------------
namespace MyXMLNamespace
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