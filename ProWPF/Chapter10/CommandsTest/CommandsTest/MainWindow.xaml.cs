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
// 1. Program demonstruje pouzitie Commands.
// 2. Command je zdedeny z ICommand a umoznuje naviazat tu istu akciu (napriklad Open) na viacero Elements a logicky akcii (MenuItem, ToggleButton, Shortucuts). Takto mozem docielit, ze naprpiklad operacia Open sa bude spustat bud z menu, alebo z cez ToggleButton v hornej liste, shortcut, alebo inym sposobom.
// 3. Pre zrealizovanie Command musim pouzit Command, ktory naviazem cez CommandBindings na danu akciu. Command samotny neobsahuje akciu, tu samozrejme musim definovat sam prave skrze CommandBinding.
// !!! 4. Pretoze CommandBinding je implementovany UIElement, tak nim mozem viazat Commnad NA LUBOVOLNY Element, ale NAJOBVYKLEJSIE je ho viazat na Window. Inak je to uzivatelsky metuce.
// !!! 5. CommandBinding ma event Executed (ale aj PreviewExecuted). V Executed ROBIM SAMOTNU AKCIU, KTORA SA MA VYKONAT PRI SPUSTENI Command.
// ????? 6. Vyzera to, ze pri events Executed a PreviewExecuted pri ich PRVOM ZACHYTENI SA Tunneling a Bubbling KONCI. Dokonca ked zachytim Tunneling event PreviewExecuted tak sa Bubbling event Executed NEVOLA a JE JEDNO CI SOM NASTAVIL Handled, ALEBO NIE.
// 7. Command mozem spustit aj manualne volanim Execute() na Command, alebo CommandBinding.
// 8. Event CanExecute je volany WPF na zistenie ci dany Command sa moze, alebo nemoze v danej chvili vyvolat. Aks a nemoze tak WPF tetno Command a jeho prisluchajuci Element da do Disabled state.
// !!! 9. Ak chcem WPF oznamit, ze doslo k zmene stavu aplikacie, ktora mohla zapricinit zmenustavu Commands, tak mozem WFP poziadat o preverenie stavu Commands. Robi sa to bud vyslanim eventu CanExecuteChanged (TO PRE Elemetns), alebo volanim CommandManager.InvalidateRequerySuggested().
//------------------------------------------------------------------------
namespace CommandsTest
{
//------------------------------------------------------------------------
	public partial class MainWindow:System.Windows.Window
	{
//------------------------------------------------------------------------
		private bool							MFindEnable=true;
		private bool							MReplaceEnable=true;
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public MainWindow()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		// Command mozem spustit aj manualne volanim metody Execute() na Command.
		private void OnManualNewCommandExecute(object Sender, RoutedEventArgs E)
		{
			ApplicationCommands.New.Execute("HELLO !",this);
		}
//------------------------------------------------------------------------
		// Command mozem spustit aj manualne volanim Execute() na CommandBinding.
		private void OnManualNewCommandBindingExecute(object Sender, RoutedEventArgs E)
		{
			this.CommandBindings[0].Command.Execute("HI !");
		}
//------------------------------------------------------------------------
		private void OnPreviewWindow_NewCommand(object Sender, ExecutedRoutedEventArgs E)
		{
			RoutedCommand		RC=(RoutedCommand) E.Command;
			StackFrame			SF=new StackFrame();
			MethodBase			MB=SF.GetMethod();

			Debug.WriteLine(string.Format("\t{0}() - Command: {1}, Parameter: {2}, OriginalSource: {3}, Source: {4} !",MB.Name,RC.Name,E.Parameter,E.OriginalSource,E.Source));
			E.Handled=false;
		}
//------------------------------------------------------------------------
		private void OnPreviewWindow_OpenCommand(object Sender, ExecutedRoutedEventArgs E)
		{
			RoutedCommand		RC=(RoutedCommand) E.Command;
			StackFrame			SF=new StackFrame();
			MethodBase			MB=SF.GetMethod();

			Debug.WriteLine(string.Format("\t{0}() - Command: {1}, Parameter: {2}, OriginalSource: {3}, Source: {4} !",MB.Name,RC.Name,E.Parameter,E.OriginalSource,E.Source));
			E.Handled=false;
		}
//------------------------------------------------------------------------
		private void OnWindow_NewCommand(object Sender, ExecutedRoutedEventArgs E)
		{
			RoutedCommand		RC=(RoutedCommand) E.Command;
			StackFrame			SF=new StackFrame();
			MethodBase			MB=SF.GetMethod();

			Debug.WriteLine(string.Format("\t{0}() - Command: {1}, Parameter: {2}, OriginalSource: {3}, Source: {4} !",MB.Name,RC.Name,E.Parameter,E.OriginalSource,E.Source));
		}
//------------------------------------------------------------------------
		private void OnWindow_OpenCommand(object Sender, ExecutedRoutedEventArgs E)
		{
			RoutedCommand		RC=(RoutedCommand) E.Command;
			StackFrame			SF=new StackFrame();
			MethodBase			MB=SF.GetMethod();

			Debug.WriteLine(string.Format("\t{0}() - Command: {1}, Parameter: {2}, OriginalSource: {3}, Source: {4} !",MB.Name,RC.Name,E.Parameter,E.OriginalSource,E.Source));
		}
//------------------------------------------------------------------------
		private void OnWindow_FindCommand(object Sender, ExecutedRoutedEventArgs E)
		{
			RoutedCommand		RC=(RoutedCommand) E.Command;
			StackFrame			SF=new StackFrame();
			MethodBase			MB=SF.GetMethod();

			Debug.WriteLine(string.Format("\t{0}() - Command: {1}, Parameter: {2}, OriginalSource: {3}, Source: {4} !",MB.Name,RC.Name,E.Parameter,E.OriginalSource,E.Source));
		}
//------------------------------------------------------------------------
		private void OnWindow_ReplaceCommand(object Sender, ExecutedRoutedEventArgs E)
		{
			RoutedCommand		RC=(RoutedCommand) E.Command;
			StackFrame			SF=new StackFrame();
			MethodBase			MB=SF.GetMethod();

			Debug.WriteLine(string.Format("\t{0}() - Command: {1}, Parameter: {2}, OriginalSource: {3}, Source: {4} !",MB.Name,RC.Name,E.Parameter,E.OriginalSource,E.Source));
		}
//------------------------------------------------------------------------
		private void OnButton1_SaveCommand(object Sender, ExecutedRoutedEventArgs E)
		{
			RoutedCommand		RC=(RoutedCommand) E.Command;
			StackFrame			SF=new StackFrame();
			MethodBase			MB=SF.GetMethod();

			Debug.WriteLine(string.Format("\t{0}() - Command: {1}, Parameter: {2}, OriginalSource: {3}, Source: {4} !",MB.Name,RC.Name,E.Parameter,E.OriginalSource,E.Source));
		}
//------------------------------------------------------------------------
		private void OnButton3_NewCommand(object Sender, ExecutedRoutedEventArgs E)
		{
			RoutedCommand		RC=(RoutedCommand) E.Command;
			StackFrame			SF=new StackFrame();
			MethodBase			MB=SF.GetMethod();

			Debug.WriteLine(string.Format("\t{0}() - Command: {1}, Parameter: {2}, OriginalSource: {3}, Source: {4} !",MB.Name,RC.Name,E.Parameter,E.OriginalSource,E.Source));
		}
//------------------------------------------------------------------------
		private void OnButton3_OpenCommand(object Sender, ExecutedRoutedEventArgs E)
		{
			RoutedCommand		RC=(RoutedCommand) E.Command;
			StackFrame			SF=new StackFrame();
			MethodBase			MB=SF.GetMethod();

			Debug.WriteLine(string.Format("\t{0}() - Command: {1}, Parameter: {2}, OriginalSource: {3}, Source: {4} !",MB.Name,RC.Name,E.Parameter,E.OriginalSource,E.Source));
		}
//------------------------------------------------------------------------
		private void OnButton3_SaveCommand(object Sender, ExecutedRoutedEventArgs E)
		{
			RoutedCommand		RC=(RoutedCommand) E.Command;
			StackFrame			SF=new StackFrame();
			MethodBase			MB=SF.GetMethod();

			Debug.WriteLine(string.Format("\t{0}() - Command: {1}, Parameter: {2}, OriginalSource: {3}, Source: {4} !",MB.Name,RC.Name,E.Parameter,E.OriginalSource,E.Source));
		}
//------------------------------------------------------------------------
		private void OnWindow_CanFindCommand(object sender, CanExecuteRoutedEventArgs E)
		{
			E.CanExecute=MFindEnable;
		}
//------------------------------------------------------------------------
		private void OnWindow_CanReplaceCommand(object sender, CanExecuteRoutedEventArgs E)
		{
			E.CanExecute=MReplaceEnable;
		}
//------------------------------------------------------------------------
		private void OnToggle1ButtonClick(object Sender, RoutedEventArgs E)
		{
			MFindEnable=(bool) MToggleButton1.IsChecked;
			CommandManager.InvalidateRequerySuggested();
		}
//------------------------------------------------------------------------
		private void OnToggle2ButtonClick(object Sender, RoutedEventArgs E)
		{
			MReplaceEnable=(bool) MToggleButton2.IsChecked;
			CommandManager.InvalidateRequerySuggested();
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------