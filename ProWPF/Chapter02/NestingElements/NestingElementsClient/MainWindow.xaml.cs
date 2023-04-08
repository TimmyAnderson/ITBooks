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
// 1. Program demosntruje 3 sposoby ako XAML vytavra strom objektov pri prasovani.
// 2. Prvy spsob je, ked Element, ktory mama v XAML SAM implementuje IList. Vtedy su vsetky jeho Child Elements, ktore v XAML mam zadefinovane prihodene cez IList.Add() do kolecie.
// 3. Druhy sposob je pouzitie ContentProperty, ktora NEIMPLEMENTUJE IList. Vtedy sa Element, ktory je ako Child E prihodi do takto oznacenej Property. Child E MOZE BYT IBA JEDEN.
// 4. Treti sposob je pouzitie ContentProperty, ktora IMPLEMENTUJE IList. Vtedy sa VSETKY Child E ulozia do tejto ContentProperty prave cez IList.Add().
//------------------------------------------------------------------------
namespace NestingElementsClient
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