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
// 1. Program demontruje pouzitie BitmapEffects.
// 2. BitmapEffects umoznuje pomocou property BitmapEffects nastavit rozlicne efekty.
// !!! 3. Tieto efekty su vsak VELMI POMALE. Su implementovane na urovni SW a nie su implementovane na HW, preto ta nizka rychlost.
// !!! 4. Na vytvorenie efektu Shadow je mozne pouzit aj SystemDropShadowChrome, ktora je OVELA EFEKTIVENJSIA ako DropShadowBitmapEffect.
//------------------------------------------------------------------------
namespace BitmapEffectsTest
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