using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Input;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.Windows.Documents;
//------------------------------------------------------------------------------
namespace RoutedEvents
{
//------------------------------------------------------------------------------
	public class CKeyboardEvents : Window
	{
//------------------------------------------------------------------------------
        private StackPanel							MStack;
        private ScrollViewer						MScroll;
        private string								MStrHeader="Event     Key                 Sys-Key   Text      Ctrl-Text Sys-Text  Ime       KeyStates      IsDown  IsUp   IsToggled IsRepeat ";
        private string								MStrFormatKey="{0,-10}{1,-20}{2,-10}                              {3,-10}{4,-15}{5,-8}{6,-7}{7,-10}{8,-10}";
        private string								MStrFormatText="{0,-10}                              {1,-10}{2,-10}{3,-10}";
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		public CKeyboardEvents()
		{
            Title="Examine Keystrokes";
            FontFamily=new FontFamily("Courier New");

            Grid				Grid=new Grid();

            Content=Grid;

            RowDefinition		RowDef=new RowDefinition();

            RowDef.Height=GridLength.Auto;
            Grid.RowDefinitions.Add(RowDef);
            Grid.RowDefinitions.Add(new RowDefinition());

            TextBlock			TextHeader=new TextBlock();

            TextHeader.FontWeight=FontWeights.Bold;
            TextHeader.Text=MStrHeader;
            Grid.Children.Add(TextHeader);

            MScroll=new ScrollViewer();
            Grid.Children.Add(MScroll);
            Grid.SetRow(MScroll, 1);

            MStack=new StackPanel();
            MScroll.Content=MStack;
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        private void DisplayKeyInfo(KeyEventArgs Args)
        {
            string			Str=string.Format(MStrFormatKey, Args.RoutedEvent.Name, Args.Key, Args.SystemKey, Args.ImeProcessedKey, Args.KeyStates, Args.IsDown, Args.IsUp, Args.IsToggled, Args.IsRepeat);

            DisplayInfo(Str);
        }
//------------------------------------------------------------------------------
        private void DisplayInfo(string Str)
        {
            TextBlock		Text=new TextBlock();

            Text.Text=Str;
            MStack.Children.Add(Text);
            MScroll.ScrollToBottom();
        }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        protected override void OnKeyDown(KeyEventArgs Args)
        {
            base.OnKeyDown(Args);
            DisplayKeyInfo(Args);
        }
//------------------------------------------------------------------------------
        protected override void OnKeyUp(KeyEventArgs Args)
        {
            base.OnKeyUp(Args);
            DisplayKeyInfo(Args);
        }
//------------------------------------------------------------------------------
        protected override void OnTextInput(TextCompositionEventArgs Args)
        {
            base.OnTextInput(Args);

            string				Str=string.Format(MStrFormatText, Args.RoutedEvent.Name, Args.Text, Args.ControlText, Args.SystemText);

            DisplayInfo(Str);
        }
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------