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
// 1. Program demonstruje pouzitie TabStops a Focus.
// 2. TabStops sa prepinaju pomocou Tab-Space a iba na tych, ktore maju nastaveny IsTabStop na TRUE a takisto aj Focusable na TRUE.
// !!! 3. Rozdiel medzi Focusable a IsTabStop je, ze Focusable ak je nastaveny na FALSE, tak objekt NEMOZE DOSTAT Focus NIJAKO. Ani cez stalcenie mysky. Ked je nastaveny IsTabStop na FALSE tak sa cez TabStop nedostanem na Element, ale cez mysku ano.
// 4. Focus je mozne nastavit programovo pomocou metody Focus().
// 5. TabIndex je mozne nastavit cez property TabIndex. Hodnota 1 je default a cim vyssia hodnota tym neskor dostane Focus pri prepinani cez Tab-Space.
// !!! 6. Ked nenastavim TabIndex tak su Elements prechadzane podla stromu Elements.
//------------------------------------------------------------------------
namespace FocusAndTabStopTest
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
		private void OnSetFocusButton22(object Sender, RoutedEventArgs E)
		{
			MButton22.Focus();
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------