using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Input;
//------------------------------------------------------------------------------
namespace SimpleTests
{
//------------------------------------------------------------------------------
	public class CKeyboardInput
	{
//------------------------------------------------------------------------------
		private static void Win_TextInput(object Sender, TextCompositionEventArgs E)
		{
			Console.WriteLine(string.Format("Text input: [{0}] !",E.Text));
		}
//------------------------------------------------------------------------------
		private static void Win_KeyDown(object Sender, KeyEventArgs E)
		{
			Console.WriteLine(string.Format("Key down: [{0}] !",E.Key));
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		public static void Do()
		{
            Application			App=new Application();
            Window				Win=new Window();

            Win.Title="Keyboard";
			Win.KeyDown += new KeyEventHandler(Win_KeyDown);
			Win.TextInput += new TextCompositionEventHandler(Win_TextInput);

            App.Run(Win);
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------