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
// 1. Program sluzi iba na demonstraciu ako funguje InitializeComponent().
// 2. Dohromady neobsahuje nic, iba nejake Controls s Name, aby bolo mozne pozorovat co robi metoda InitializeComponent().
// !!! 3. Pomenovat Elements mozem pomocou XAML KEYWORD 'x:Name', alebo pomocou property Name, ktoru vystavuje prakticky kazdy E. Obe MAJU TEN ISTY EFEKT. Funguje to tak, ze E musi mat oznacenu jednu properety ako property pre meno E. Ta sa oznaci atributom [RuntimeNameProperty], kde definume meno tejto property. V STANDARDNYCH E je to prave property 'Name', ktora je oznacena ako ta, ktora nesie meno. Pri pouziti 'x:Name' XAML najde property, ktora je oznacena tymto atributom a ju naplni.
//------------------------------------------------------------------------
namespace SimpleGUI
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