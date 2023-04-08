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
// 1. Program demonstruj pouzite Page v ramci inej Page.
// 2. Na vnaranie Page do Page sa pouzivaju Frames.
// !!! 3. Problem, ktry nastava, ked mam viacero Frames na jednej Page je, ze historia sa uklada ZA RADOM pre VSETKY Frames. Ak toto nie je ciel a chcem aby KAZDY FRAME MAL VLASTNU HITORIOU POTOM MUSIM NASTAVIT JournalOwnership na 'OwnsJournal'.
//------------------------------------------------------------------------
namespace PageInPage
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
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------