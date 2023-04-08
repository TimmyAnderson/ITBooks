using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Input;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;
//------------------------------------------------------------------------------
namespace Buttons
{
//------------------------------------------------------------------------------
	public class CButtonWithCommand : Window
	{
//------------------------------------------------------------------------------
		public CButtonWithCommand()
		{
            Title="Command the Button";

            Button			Btn=new Button();

            Btn.HorizontalAlignment=HorizontalAlignment.Center;
            Btn.VerticalAlignment=VerticalAlignment.Center;
            Btn.Command=ApplicationCommands.Paste;
            Btn.Content=ApplicationCommands.Paste.Text;
            Content=Btn;

            // Vykonam BIDNING metod s COMMAND.
            CommandBindings.Add(new CommandBinding(ApplicationCommands.Paste, PasteOnExecute, PasteCanExecute));
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        private void PasteOnExecute(object Sender, ExecutedRoutedEventArgs Args)
        {
            Title=Clipboard.GetText();
        }
//------------------------------------------------------------------------------
        private void PasteCanExecute(object Sender, CanExecuteRoutedEventArgs Args)
        {
            Args.CanExecute=Clipboard.ContainsText();
        }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        protected override void OnMouseDown(MouseButtonEventArgs Args)
        {
            base.OnMouseDown(Args);

            Title="Command the Button";
        }
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------