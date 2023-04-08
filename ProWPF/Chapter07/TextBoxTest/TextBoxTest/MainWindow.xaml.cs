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
// 1. Program demonstruje TextBoxes.
// !!! 2. Ako Content do TextBoxu moze vystupovat iba TEXT a je ulozeny v property Text.
// 3. TextBox ma properties MinLines a MaxLines pouzivanych pri viac riadkovych TextBox, ktore umoznuju definovat eho velkost.
// 4. Podporuje ScrollBars ak je Text vecsi. Tieto je mozne nastavit cez VerticalScrollBarVisibility a HorizontalScrollBarVisibility properties.
// 5. TextBox podporuje mnozstvo properties pre text selection.
// !!! 6. V texte sa da scrolovat programovo metodami ako LineUp(), LineDown() a dalsimi.
// !!!!! 7. TextBox podporu SPELL CHECK nsatvenim property SpellCheck.IsEnabled na TRUE.
// !!!!! 8. SPELL CHECKER !!!!! NIE JE ZAVISLY NA OFFICE. !!!!! Je to WPF komponenta.
// !!! 9. Pri pouziti Undo je mozne aby vecsia cast textu bola povazovana za celok a pri Undo vratena do povodneho stavu. Robi sa to metodamu BeginChange() a EndChange() - tym sa vyznaci blok. A CELY sa pri pouziti Undo() odstrani.
// 10. Property MaxLength je mozne urcit maximalnu dlzku textu.
// 11. Element PasswordBox sluzi na vkladanie Passwordu. Samotny Password je v pameti ukladany sifrovane. Property PasswordChar umoznuje stanovit password znak.
//------------------------------------------------------------------------
namespace TextBoxTest
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
		private void OnSelectionChanged(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine("");
			Debug.WriteLine(string.Format("SelectedText: {0} !",MTextBox.SelectedText));
			Debug.WriteLine(string.Format("SelectionStart: {0} !",MTextBox.SelectionStart));
			Debug.WriteLine(string.Format("SelectionLength: {0} !",MTextBox.SelectionLength));
		}
//------------------------------------------------------------------------
		private void OnBeginChange(object Sender, RoutedEventArgs E)
		{
			// !!! Hodilo NA POZADI Exception.
			//MUndoTextBox.BeginChange();
		}
//------------------------------------------------------------------------
		private void OnEndChange(object Sender, RoutedEventArgs E)
		{
			//MUndoTextBox.EndChange();
		}
//------------------------------------------------------------------------
		private void OnUndo(object Sender, RoutedEventArgs E)
		{
			MUndoTextBox.Undo();
		}
//------------------------------------------------------------------------
		private void OnRedo(object Sender, RoutedEventArgs E)
		{
			MUndoTextBox.Redo();
		}
//------------------------------------------------------------------------
		private void OnPasswordChanged(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine(string.Format("Password: {0} !",MPasswordBox.Password));
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------