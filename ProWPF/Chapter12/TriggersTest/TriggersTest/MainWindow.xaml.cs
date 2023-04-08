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
// 1. Program demonstruje pouzitie Trigerrs.
// 2. Triggers sluzia na to aby v XAML bola vykonana nejaka akcia, alebo akcie, ked sa zmeni hodnota nejakej DP, alebo sa vyvola RE.
// 3. Triggers mozem definovant ako sucast v Style, alebo pomocu FrameworkElement.Triggers.
// !!! 4. V pripade FrameworkElement.Triggers JE ZNACNE OMBEDZENIE, kde IBA triggre typu EventTrigger mozu byt ukladane do FrameworkElement.Triggers.
// 5. Trigger a MultiTrigger sa vyvolavaju ked sa niektora property (v pripade MultiTrigger aj viacero properties - ale VSETKY - operator 'and') je nastavenych na definovanu hodnotu. Ak sa tak stane potom sa vyvola Setter (alebo viacero Setter - V PORADI AKO SU DEFINOVANE V XAML), ktory pre Trigger som zadefinoval.
// !!! 6. Triggers vedia porovnavat sa IBA S HODNOTOU, nie S ROZAHOM HODNOT.
// 7. EventTriggers su volane KED SA VYVOLA NEJAKA RE. Nespustam vsak Setters, ale definuje Actions, ktore realizuju nejake operacie. Pouzivaju sa najme v animaciach, kde su aj blizsie vysvetlene.
// !!! 8. TU su EventTriggers IBA NACRTNUTE. Viac v kapitole o animaciach.
// !!!!! 9. Vplyv Triggers a MultiTriggers NETREBA REVERTOVAT. ROBI SA TO AUTOMATICKY, VDAKA DEDICNOSTI DP.
// !!!!! 10. Vplyv EventTriggers JE TREBA REVEROVAT SPET RUCNE.
// !!! 11. V jednom Style moze definovat aj viac Triggers, pricom AK KLIDUJU, teda chcu naraz nastavit hodnotu tej iste DP tak vyhra tak ktora je nizsie v XAML A NIE TA, KTORA BOL SKOR ZMENENA A VYVOLALA TRIGGER.
//------------------------------------------------------------------------
namespace TriggersTest
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