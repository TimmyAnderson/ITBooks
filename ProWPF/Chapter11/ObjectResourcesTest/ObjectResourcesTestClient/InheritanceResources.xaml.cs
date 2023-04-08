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
using ObjectResourcesTestLibrary;
//------------------------------------------------------------------------
namespace ObjectResourcesTestClient
{
//------------------------------------------------------------------------
	public partial class InheritanceResources:System.Windows.Window
	{
//------------------------------------------------------------------------
		public InheritanceResources()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void PrintResources(string Name, ResourceDictionary RD)
		{
			Debug.WriteLine(string.Format("{0}:",Name));
			
			foreach(string Key in RD.Keys)
				Debug.WriteLine(string.Format("\t{0} !",RD[Key].ToString()));
		}
//------------------------------------------------------------------------
		private void OnClick1(object Sender, RoutedEventArgs E)
		{
			PrintResources("WINDOW",MWindow.Resources);
		}
//------------------------------------------------------------------------
		private void OnClick2(object Sender, RoutedEventArgs E)
		{
			PrintResources("STACK PANEL",MStackPanel.Resources);
		}
//------------------------------------------------------------------------
		private void OnClick3(object Sender, RoutedEventArgs E)
		{
			PrintResources("LABEL",MLabel.Resources);
		}
//------------------------------------------------------------------------
		private void OnClick4(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine("");
			Debug.WriteLine(string.Format("WINDOW - MRes0: {0} !",MWindow.TryFindResource("MRes0") ?? "NULL"));
			Debug.WriteLine(string.Format("WINDOW - MRes1: {0} !",MWindow.TryFindResource("MRes1") ?? "NULL"));
			Debug.WriteLine(string.Format("WINDOW - MRes2: {0} !",MWindow.TryFindResource("MRes2") ?? "NULL"));
			Debug.WriteLine(string.Format("WINDOW - MRes3: {0} !",MWindow.TryFindResource("MRes3") ?? "NULL"));
			Debug.WriteLine(string.Format("WINDOW - MRes4: {0} !",MWindow.TryFindResource("MRes4") ?? "NULL"));
		}
//------------------------------------------------------------------------
		private void OnClick5(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine("");
			Debug.WriteLine(string.Format("STACK PANEL - MRes0: {0} !",MStackPanel.TryFindResource("MRes0") ?? "NULL"));
			Debug.WriteLine(string.Format("STACK PANEL - MRes1: {0} !",MStackPanel.TryFindResource("MRes1") ?? "NULL"));
			Debug.WriteLine(string.Format("STACK PANEL - MRes2: {0} !",MStackPanel.TryFindResource("MRes2") ?? "NULL"));
			Debug.WriteLine(string.Format("STACK PANEL - MRes3: {0} !",MStackPanel.TryFindResource("MRes3") ?? "NULL"));
			Debug.WriteLine(string.Format("STACK PANEL - MRes4: {0} !",MStackPanel.TryFindResource("MRes4") ?? "NULL"));
		}
//------------------------------------------------------------------------
		private void OnClick6(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine("");
			Debug.WriteLine(string.Format("LEBEL - MRes0: {0} !",MLabel.TryFindResource("MRes0") ?? "NULL"));
			Debug.WriteLine(string.Format("LEBEL - MRes1: {0} !",MLabel.TryFindResource("MRes1") ?? "NULL"));
			Debug.WriteLine(string.Format("LEBEL - MRes2: {0} !",MLabel.TryFindResource("MRes2") ?? "NULL"));
			Debug.WriteLine(string.Format("LEBEL - MRes3: {0} !",MLabel.TryFindResource("MRes3") ?? "NULL"));
			Debug.WriteLine(string.Format("LEBEL - MRes4: {0} !",MLabel.TryFindResource("MRes4") ?? "NULL"));
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------