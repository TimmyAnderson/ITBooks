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
// 1. Program demonstruje pouzitie TreeView.
// 2. TreeView dokaze zobrazovat strom Elementov. Obsahuje TreeViewItem, ktory JE ItemsControl A TEDA MOZE OBSAHOVAT VIACERO Elements. ZAROVEN AJ KAZDY TreeItemView je typu ItemsControl a teda AJ ON MOZE MAT VIACERO Child Elements. PRAVE TAKTO SA VYTVARA STROM.
// !!! 3. NIE je NUTNE pouzit TreeViewItem ako Child Element. Mozem pouzit aj iny, ale TreeViewItem je najlepsi.
// 4. Nato aby som mohol zobrazit Tree musia moje datove struktuy, ktore bude pomoou Db mapovat na TreeView obsahovat property typu Collection, ktoru namapujem na nizsiu uroven v Tree. Ta samozrejme takisto moze mat Collection a takto mozem elegantne vytvorit cely Tree.
// !!! 5. Na zobrazenie jednotlivych Items v Tree sa pouziva HierarchicalDataTemplate. Tato obsahuje ItemTemplate, ktorou viem definovat DT na 2. urovni v Tree a ak aj na tejto urovni pouzijem HierarchicalDataTemplate tak znova mozem definovat DT pre 3. uroven a tak dalej.
// !!! 6. Namiesto vnarania sa jednotlivych DT je lepsim riesenim zviazat HierarchicalDataTemplate s TYPOM pomocou property HierarchicalDataTemplate.DataType. Takto asociujem TYP s DT a to znaci, ze VZDY ked sa v TreeView ZJAVI ako Item tento Typ, tak s nim bude AUTOMATICKY ASOCIOVANY DT.
// 7. Pri pouziti DataSet je mozne priamo namapovat na TreeView ak DataTable su vzajomne prepojene cez DataRelation. Potom za ItemSource je treba dat MENO DataRelation.
// 8. TreeView obsahuje metody, ktore je mozne pouzit na pridavanie a odoberanie TreeItems. Takisto je mozne zachytavat Eventy pri otvarani a zatvarani daneho TreeItem a prave vtedy realizovat dynamicke pridavanie a odoberanie TreeItems.
//------------------------------------------------------------------------
namespace TreeViewTestClient
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
		private void OnClick1(object Sender, RoutedEventArgs E)
		{
			SimpleTreeView				Win=new SimpleTreeView();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick2(object Sender, RoutedEventArgs E)
		{
			DBTreeView					Win=new DBTreeView();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick3(object Sender, RoutedEventArgs E)
		{
			DiskExplorer				Win=new DiskExplorer();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------