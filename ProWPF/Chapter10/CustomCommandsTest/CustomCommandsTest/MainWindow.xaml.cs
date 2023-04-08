using System;
using System.Collections.Generic;
using System.Text;
using System.Reflection;
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
// 1. Program demonstruje pouzitie Custom Command.
// 2. Na vytvorenie CUSTOM COMMAND je potrebne urobit tieto kroky.
//    A. Vytvorit (najlepsie v statickej premennej) instanciu RoutedUICommand s prislunym nastavenim Gestures, Name a podobne.
//    B. Namapovat ju v CommandBinding metodu Execute().
//    C. Priradit ju nejakemu Element.
//------------------------------------------------------------------------
namespace CustomCommandsTest
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
		private void OnMyCommandExecute(object Sender, ExecutedRoutedEventArgs E)
		{
			RoutedCommand		RC=(RoutedCommand) E.Command;
			StackFrame			SF=new StackFrame();
			MethodBase			MB=SF.GetMethod();

			Debug.WriteLine(string.Format("\t{0}() - Command: {1}, Parameter: {2}, OriginalSource: {3}, Source: {4} !",MB.Name,RC.Name,E.Parameter,E.OriginalSource,E.Source));
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------