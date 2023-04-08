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
// 1. Program demonstruje pouzitie Keyboardu a zachytavanie rozlicnych eventov.
// 2. Keyboard ma velke mnozstvo udalosti, ktore je mozne zachytavat.
// 3. Tri zakladne Events su KeyDown, KeyUp a TextInput, vratane Preview verzii.
// !!! 4. TextBox pridava dalsie udalosti ako TextChanged a naopak event TextInput SKRYVA.
// !!!!! 5. Zaujimava je trieda Keyboard, ktora umoznuje registrovat Events nad Keybord nad celou aplikaciou ako aj zistovat aktualny stav tlacitok.
//------------------------------------------------------------------------
namespace KeyboardTest
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
		private void OnTextBoxPreviewKeyDown(object Sender, KeyEventArgs E)
		{
			Debug.WriteLine(string.Format("OnTextBoxPreviewKeyDown() - Key: {0}, SystemKey: {1}, IsRepeat: {2}, Modifiers: {3} !",E.Key,E.SystemKey,E.IsRepeat,E.KeyboardDevice.Modifiers));
		}
//------------------------------------------------------------------------
		private void OnTextBoxPreviewKeyUp(object Sender, KeyEventArgs E)
		{
			Debug.WriteLine(string.Format("OnTextBoxPreviewKeyUp() - Key: {0}, SystemKey: {1}, IsRepeat: {2}, Modifiers: {3} !",E.Key,E.SystemKey,E.IsRepeat,E.KeyboardDevice.Modifiers));
		}
//------------------------------------------------------------------------
		private void OnTextBoxPreviewTextInput(object Sender, TextCompositionEventArgs E)
		{
			Debug.WriteLine(string.Format("OnTextBoxPreviewTextInput() - Text: {0}, SystemText: {1}, ControlText: {2} !",E.Text,E.SystemText,E.ControlText));
		}
//------------------------------------------------------------------------
		private void OnTextBoxKeyDown(object Sender, KeyEventArgs E)
		{
			Debug.WriteLine(string.Format("OnTextBoxKeyDown() - Key: {0}, SystemKey: {1}, IsRepeat: {2}, Modifiers: {3} !",E.Key,E.SystemKey,E.IsRepeat,E.KeyboardDevice.Modifiers));
		}
//------------------------------------------------------------------------
		private void OnTextBoxKeyUp(object Sender, KeyEventArgs E)
		{
			Debug.WriteLine(string.Format("OnTextBoxKeyUp() - Key: {0}, SystemKey: {1}, IsRepeat: {2}, Modifiers: {3} !",E.Key,E.SystemKey,E.IsRepeat,E.KeyboardDevice.Modifiers));
		}
//------------------------------------------------------------------------
		private void OnTextBoxTextInput(object Sender, TextCompositionEventArgs E)
		{
			Debug.WriteLine(string.Format("OnTextBoxTextInput() - Text: {0}, SystemText: {1}, ControlText: {2} !",E.Text,E.SystemText,E.ControlText));
		}
//------------------------------------------------------------------------
		private void OnTextBoxTextChanged(object Sender, TextChangedEventArgs E)
		{
			Debug.WriteLine(string.Format("OnTextBoxTextInput() - UndoAction: {0} !",E.UndoAction));
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void OnButtonPreviewKeyDown(object Sender, KeyEventArgs E)
		{
			Debug.WriteLine(string.Format("OnButtonPreviewKeyDown() - Key: {0}, SystemKey: {1}, IsRepeat: {2}, Modifiers: {3} !",E.Key,E.SystemKey,E.IsRepeat,E.KeyboardDevice.Modifiers));
		}
//------------------------------------------------------------------------
		private void OnButtonPreviewKeyUp(object Sender, KeyEventArgs E)
		{
			Debug.WriteLine(string.Format("OnButtonPreviewKeyUp() - Key: {0}, SystemKey: {1}, IsRepeat: {2}, Modifiers: {3} !",E.Key,E.SystemKey,E.IsRepeat,E.KeyboardDevice.Modifiers));
		}
//------------------------------------------------------------------------
		private void OnButtonPreviewTextInput(object Sender, TextCompositionEventArgs E)
		{
			Debug.WriteLine(string.Format("OnButtonPreviewTextInput() - Text: {0}, SystemText: {1}, ControlText: {2} !",E.Text,E.SystemText,E.ControlText));
		}
//------------------------------------------------------------------------
		private void OnButtonKeyDown(object Sender, KeyEventArgs E)
		{
			Debug.WriteLine(string.Format("OnButtonKeyDown() - Key: {0}, SystemKey: {1}, IsRepeat: {2}, Modifiers: {3} !",E.Key,E.SystemKey,E.IsRepeat,E.KeyboardDevice.Modifiers));
		}
//------------------------------------------------------------------------
		private void OnButtonKeyUp(object Sender, KeyEventArgs E)
		{
			Debug.WriteLine(string.Format("OnButtonKeyUp() - Key: {0}, SystemKey: {1}, IsRepeat: {2}, Modifiers: {3} !",E.Key,E.SystemKey,E.IsRepeat,E.KeyboardDevice.Modifiers));
		}
//------------------------------------------------------------------------
		private void OnButtonTextInput(object Sender, TextCompositionEventArgs E)
		{
			Debug.WriteLine(string.Format("OnButtonTextInput() - Text: {0}, SystemText: {1}, ControlText: {2} !",E.Text,E.SystemText,E.ControlText));
		}
//------------------------------------------------------------------------
		private void OnGetPressedKeys(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine(string.Format("Key 'A' - state: {0} !",Keyboard.GetKeyStates(Key.A)));
			Debug.WriteLine(string.Format("Key 'B' - state: {0} !",Keyboard.GetKeyStates(Key.B)));
			Debug.WriteLine(string.Format("Key 'C' - state: {0} !",Keyboard.GetKeyStates(Key.C)));
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------