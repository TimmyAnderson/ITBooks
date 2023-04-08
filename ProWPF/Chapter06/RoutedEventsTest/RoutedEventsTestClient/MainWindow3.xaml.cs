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
// 1. Demonstruje property RoutedEventArgs.Handled na zrusenie zachytavanie RE.
// 2. Demonstruje property HandledEventsToo na OBNOVENIE ZRUSENIA ZACHYTAVANIA RE.
//------------------------------------------------------------------------
namespace RoutedEventsTestClient
{
//------------------------------------------------------------------------
	public partial class MainWindow3:System.Windows.Window
	{
//------------------------------------------------------------------------
		public MainWindow3()
		{
			InitializeComponent();

			// !!! Ty zadefnujem Event Handlers, ale tak aby som nastavil HandledEventsToo na TRUE.
			MStack.AddHandler(CREPatent.REBubbleEvent, new RoutedEventHandler(OnStackPanelBubble_HANDLED_EVENTS_TOO), true);
			MStack.AddHandler(CREPatent.RETunnelEvent, new RoutedEventHandler(OnStackPanelTunnel_HANDLED_EVENTS_TOO), true);
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
		private void OnStackPanelBubble_HANDLED_EVENTS_TOO(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine(string.Format("\tStackPanelBubble_HANDLED_EVENTS_TOO"));
		}
//------------------------------------------------------------------------
		private void OnStackPanelTunnel_HANDLED_EVENTS_TOO(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine(string.Format("\tStackPanelTunnel_HANDLED_EVENTS_TOO"));
		}
//------------------------------------------------------------------------
		private void OnLabelBubble_HANDLED(object Sender, RoutedEventArgs E)
		{
			// !!! Nastavujem Handled na TRUE.
			E.Handled=true;
			Debug.WriteLine(string.Format("\tLabelBubble_HANDLED"));
		}
//------------------------------------------------------------------------
		private void OnLabelTunnel_HANDLED(object Sender, RoutedEventArgs E)
		{
			// !!! Nastavujem Handled na TRUE.
			E.Handled=true;
			Debug.WriteLine(string.Format("\tLabelTunnel_HANDLED"));
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
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------