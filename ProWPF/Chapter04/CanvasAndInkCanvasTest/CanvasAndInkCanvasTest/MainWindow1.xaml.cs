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
// 1. Program demonstruje Canvas a InkCanvas.
// 2. Canvas sluzi ako lighweigthed Panel, ktory umoznuje definovat presne pozicie kde sa ma zobrazit dany Element pricom nedefinuje ziadne zarovanie, ci ostatne formatovanie properties.
// !!! 3. Ak je Canvas pichnuty na nejakom Panely tak vzhadom ze (NA ROZDIEL OD OSTATNYCH PANELS) ma nastaveny ClipToBounds na FALSE TAK NIE JE OREZANY a jeho Elemens PRESAHUJU MIMO SVOJICH HRANIC. Ak chce orezavanie zapnut musim tuto property zapnut na TRUE.
// 4. Pri prekryvani mozem pouzit ZIndex na urcenie hodnoty ZBuffer. Vyssia hodnota znamena, ze Element prekryje Element s nizsou hodnotu ZIndex.
// 5. InkCanvas sa sice trochu podoba Canvas, aj ked v skutocnosti sa NEJEDNA O PANEL. Sluzi pre pacu so Stylusom na PDA.
// 6. Pomocou jeho property EditingMode mozem nastavit viacere editacne mody, vratane SELECT, kde mozem premiestnovat Elements. Avsak InkCanvas je ozaj zaujimavy iba pre Stylus.
//------------------------------------------------------------------------
namespace CanvasAndInkCanvasTest
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