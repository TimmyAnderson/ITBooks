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
using RoutedEventsTestLibrary;
//------------------------------------------------------------------------
// 1. Program demostruje rozlicne moznosti pouzitia RE.
// 2. RE ako Attached RE.
//    A. Attached RE VLASTNE ANI NEEXISTUJU, KEDZE KAZDA RE MOZE BYT POUZITA Attached sposobom. Teda je definovany v jednom DO a pouzity v inom DO.
//    B. Na pouzitie Attached RE staci v XAML pouzit aj emno triedy, kde RE je definovany, teda: 'CREPatent.REBubble', ci 'CREPatent.RETunnel'.
// 3. RE sa odpaluju pomocou metody DO RaiseEvent(), kde v parametri DEFINUJEM IDENTIFIKATOR RE.
// !!!!! 4. RE FUNGUJU PRESNE AKO DP v tom, ze RE definovanu nad jednym DO mozem pouzit BA DOKONCA ODPALIT NAD UPLNE INYM DO. Napriklad trieda CREPatent je ta ktora definuje RE (REBubble) avsak kludne tento RE MOZEM ODPALIT NAD 'Label' ALEBO HOCIJAKYM INYM DO.
// !!! 5. RE su VZDY schopne sa sirit v strome Elements.
//    A. Bubble - siria sa od DO, nad ktorou bola RE odpalena az DO KORENA Elements Tree.
//    B. Tunnel - siria sa od KORENA Elements Tree do DO, KTORA RE ODPALILA.
//    C. Direct - sirenie nie je a RE odpali iba PRIAMO ZAREGISTROVANY Handler a NIC VIAC.
// 4. Shared RE.
//    A. Funguju uplne rovanko ako Shared DP. Teda ak vyvola sa Event pre RE tak sa vyvolaju aj eventy sa pre vsetky Shared RE, KEDZE SA de-facto JEDNA O TEN ISTY RE.
//    B. Zaregistruje sa cez AddOwner() podobne ako Shared DP.
// !!! 5. Nastaveni RoutedEventArgs.Handled na TRUE Handler informuje RE, ze BOLA OBSLUZENA. Znamena to tolko, ze dalsie Handlery vyssie s strome (pri bubbling), alebo nizsie v strome (pri tunneling) SA VOLAT NEBUDU, okrem vynikmy pri nastaveni HandledEventsToo na TRUE.
// !!! 6. Ak aj nastavim RoutedEventArgs.Handled na TRUE tak vyssie v strome (bubbling), alebo nizsie v strome (tunneling) MOZEM ZACHYTIT, ake Handler NA RE ZAREGISTRUJE S NASTAVENIM HandledEventsToo na TRUE. Vtedy tento Hanlder sa VYVOLA, aj ked predtym UZ BOL NASTAVENY RoutedEventArgs.Handled na TRUE.
//------------------------------------------------------------------------
namespace RoutedEventsTestClient
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
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void OnWindowPanelBubble(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine(string.Format("\tWindowPanelBubble"));
		}
//------------------------------------------------------------------------
		private void OnWindowPanelTunnel(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine(string.Format("\tWindowPanelTunnel"));
		}
//------------------------------------------------------------------------
		private void OnWindowPanelDirect(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine(string.Format("\tWindowPanelDirect"));
		}
//------------------------------------------------------------------------
		private void OnStackPanelBubble(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine(string.Format("\tStackPanelBubble"));
		}
//------------------------------------------------------------------------
		private void OnStackPanelTunnel(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine(string.Format("\tStackPanelTunnel"));
		}
//------------------------------------------------------------------------
		private void OnStackPanelDirect(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine(string.Format("\tStackPanelDirect"));
		}
//------------------------------------------------------------------------
		private void OnLabelBubble(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine(string.Format("\tLabelBubble"));
		}
//------------------------------------------------------------------------
		private void OnLabelTunnel(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine(string.Format("\tLabelTunnel"));
		}
//------------------------------------------------------------------------
		private void OnLabelDirect(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine(string.Format("\tLabelDirect"));
		}
//------------------------------------------------------------------------
		private void OnCREParentBubble(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine(string.Format("\tCREParentBubble"));
		}
//------------------------------------------------------------------------
		private void OnCREParentTunnel(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine(string.Format("\tCREParentTunnel"));
		}
//------------------------------------------------------------------------
		private void OnCREParentDirect(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine(string.Format("\tCREParentDirect"));
		}
//------------------------------------------------------------------------
		private void OnCREChildBubble(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine(string.Format("\tCREChildBubble"));
		}
//------------------------------------------------------------------------
		private void OnCREChildTunnel(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine(string.Format("\tCREChildTunnel"));
		}
//------------------------------------------------------------------------
		private void OnCREChildDirect(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine(string.Format("\tCREChildDirect"));
		}
//------------------------------------------------------------------------
		private void OnFireMREChildBubbleEvent(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine("");
			MREChild.RaiseEvent(new RoutedEventArgs(CREPatent.REBubbleEvent,this));
		}
//------------------------------------------------------------------------
		private void OnFireMREChildTunnelEvent(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine("");
			MREChild.RaiseEvent(new RoutedEventArgs(CREPatent.RETunnelEvent,this));
		}
//------------------------------------------------------------------------
		private void OnFireMREChildDirectEvent(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine("");
			MREChild.RaiseEvent(new RoutedEventArgs(CREPatent.REDirectEvent,this));
		}
//------------------------------------------------------------------------
		private void OnFireMREPatentBubbleEvent(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine("");
			MREPatent.FireBubbleEvent();
		}
//------------------------------------------------------------------------
		private void OnFireMREPatentTunnelEvent(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine("");
			MREPatent.FireTunnelEvent();
		}
//------------------------------------------------------------------------
		private void OnFireMREPatentDirectEvent(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine("");
			MREPatent.FireDirectEvent();
		}
//------------------------------------------------------------------------
		private void OnFireLabelBubbleEvent(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine("");
			// !!! Odpalujem RE z MLabel AJ KED SOM JU DEFINOVAL v CREPatent.
			MLabel.RaiseEvent(new RoutedEventArgs(CREPatent.REBubbleEvent,this));
		}
//------------------------------------------------------------------------
		private void OnFireLabelTunnelEvent(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine("");
			// !!! Odpalujem RE z MLabel AJ KED SOM JU DEFINOVAL v CREPatent.
			MLabel.RaiseEvent(new RoutedEventArgs(CREPatent.RETunnelEvent,this));
		}
//------------------------------------------------------------------------
		private void OnFireLabelDirectEvent(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine("");
			// !!! Odpalujem RE z MLabel AJ KED SOM JU DEFINOVAL v CREPatent.
			MLabel.RaiseEvent(new RoutedEventArgs(CREPatent.REDirectEvent,this));
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------