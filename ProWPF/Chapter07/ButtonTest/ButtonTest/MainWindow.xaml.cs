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
// 1. Program demonstruje Buttons.
// 2. Vsekty Buttons maju spolocne properties IsCancel a IsDefault, ktore maju rovanky vyznam ako vo WinForm.
// 3. ToggleButton je zakladom pre mnohe ine Buttons, ako CheckButton ci RadioButton. ToggleButton ma property IsChecked. IsChecked ne Nullable<bool> kde NULL je nedefinovany stav pri ThreeState buttons. ThreeState sa nasatvuje cez property IsThreeState.
// 4. RepeatButton pri stlaceni opakovane generuje Click events. Sluzi na vytvaranie inych controls ako SlideBars.
// !!! 5. RadioButtons tvoria logicku skupinu ak su umiestnene na tom istom Panel. Ak chcem ine choavnei mozem pouzit property GroupName, kde tie RadionButtons, ktore maju tuto property nastavenu na rovnake meno su v skupine.
// !!! 6. Na Buttons sa vztahuje '_' konvencia.
// !!!!! 7. Ked je nastaveny IsCancel na TRUE tak DIALOGOVE OKNO SA SAMO SUZAVRIE. Ked vsak ma Button nastaveny IsDefault tak ho MUSIM ZAVRIET SAM.
//------------------------------------------------------------------------
namespace ButtonTest
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
		private void OnShowDialogBox(object Sender, RoutedEventArgs E)
		{
			MyDialogBox			MDB=new MyDialogBox();

			MDB.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnCheckBox3Clicked(object Sender, RoutedEventArgs E)
		{
			if (MCheckBox3.IsChecked==null)
				Debug.WriteLine("MCheckBox3 is in INDIFERENT state !");
			else if (((bool) MCheckBox3.IsChecked)==true)
				Debug.WriteLine("MCheckBox3 is in TRUE state !");
			else
				Debug.WriteLine("MCheckBox3 is in FALSE state !");
		}
//------------------------------------------------------------------------
		private void OnToggleButtonClick(object Sender, RoutedEventArgs E)
		{
			if (((bool) MToggleButton.IsChecked)==true)
				Debug.WriteLine("MToggleButton is in TRUE state !");
			else
				Debug.WriteLine("MToggleButton is in FALSE state !");
		}
//------------------------------------------------------------------------
		private void OnThreeStateToggleButtonClick(object Sender, RoutedEventArgs E)
		{
			if (MThreeStatToggleButton.IsChecked==null)
				Debug.WriteLine("MThreeStatToggleButton is in INDIFERENT state !");
			else if (((bool) MThreeStatToggleButton.IsChecked)==true)
				Debug.WriteLine("MThreeStatToggleButton is in TRUE state !");
			else
				Debug.WriteLine("MThreeStatToggleButton is in FALSE state !");
		}
//------------------------------------------------------------------------
		private void OnRepeatButtonClick(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine("RepeatButton CLICKED !");
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------