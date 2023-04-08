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
	public class CMouseRoutedEvents : Application
	{
//------------------------------------------------------------------------------
        private static readonly FontFamily			MFontFam=new FontFamily("Lucida Console");
//------------------------------------------------------------------------------
        private const string						MStrFormat="{0,-30} {1,-15} {2,-15} {3,-15}";
//------------------------------------------------------------------------------
        private StackPanel							MStackOutput;
        private DateTime							MDTLast;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        private void AllPurposeEventHandler(object Sender, RoutedEventArgs Args)
        {
			/*
			if (Args.RoutedEvent==UIElement.PreviewMouseDownEvent)
				Args.Handled=true;
			*/

            DateTime			DTNow = DateTime.Now;

            if ((DTNow-MDTLast)>TimeSpan.FromMilliseconds(100))
			{
                MStackOutput.Children.Add(new TextBlock(new Run(" ")));
				Console.WriteLine("\n\n");
			}

            MDTLast=DTNow;

            TextBlock			Text=new TextBlock();

            Text.FontFamily=MFontFam;
            Text.Text=string.Format(MStrFormat, Args.RoutedEvent.Name, TypeWithoutNamespace(Sender), TypeWithoutNamespace(Args.Source), TypeWithoutNamespace(Args.OriginalSource));
			Text.Margin=new Thickness(5);

			// Pridam text s popisom INPUT EVENT.
            MStackOutput.Children.Add(Text);

			Console.WriteLine(Text.Text);

            (MStackOutput.Parent as ScrollViewer).ScrollToBottom();
        }
//------------------------------------------------------------------------------
        private string TypeWithoutNamespace(object Obj)
        {
            string[]			Astr=Obj.GetType().ToString().Split('.');

            return(Astr[Astr.Length-1]);
        }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        protected override void OnStartup(StartupEventArgs Args)
        {
            base.OnStartup(Args);

            Window			MyWindow=new Window();

            MyWindow.Title="Examine Routed Events";

            Grid			MyGrid=new Grid();

            MyWindow.Content=MyGrid;

            RowDefinition	RowDef=new RowDefinition();

            RowDef.Height=GridLength.Auto;
            MyGrid.RowDefinitions.Add(RowDef);

            RowDef=new RowDefinition();
            RowDef.Height=GridLength.Auto;
            MyGrid.RowDefinitions.Add(RowDef);

            RowDef=new RowDefinition();
            RowDef.Height=new GridLength(100, GridUnitType.Star);
            MyGrid.RowDefinitions.Add(RowDef);

            Button			MyButton=new Button();

            MyButton.HorizontalAlignment=HorizontalAlignment.Center;
            MyButton.Margin=new Thickness(24);
            MyButton.Padding=new Thickness(24);
            MyGrid.Children.Add(MyButton);

			// !!! TextBlock je CHILD ELEMENT Button.
            TextBlock		MyTextBlock=new TextBlock();

            MyTextBlock.FontSize=24;
            MyTextBlock.Text=MyWindow.Title;
            MyButton.Content=MyTextBlock;

            TextBlock		TextHeadings=new TextBlock();

            TextHeadings.FontFamily=MFontFam;
            TextHeadings.Inlines.Add(new Underline(new Run(string.Format(MStrFormat, "Routed Event", "Sender", "Source", "OriginalSource"))));
            MyGrid.Children.Add(TextHeadings);
            Grid.SetRow(TextHeadings, 1);

            ScrollViewer	Scroll=new ScrollViewer();

            MyGrid.Children.Add(Scroll);
            Grid.SetRow(Scroll, 2);

            MStackOutput=new StackPanel();
            Scroll.Content=MStackOutput;

			// !!! RE zachytavam i na urovni TextBlock, ktory je CHILD pre Button.
            UIElement[]		Els={MyWindow,MyGrid,MyButton,MyTextBlock};

            foreach (UIElement El in Els)
            {
                // Mouse.
                El.MouseDown+=AllPurposeEventHandler;
                El.MouseUp+=AllPurposeEventHandler;
                El.PreviewMouseDown+=AllPurposeEventHandler;
                El.PreviewMouseUp+=AllPurposeEventHandler;

                // Click.
				// !!!!! Musim ho zachytavat cez AddHandler(), kedze trieda UIElement NEPOZNA EVENT Click.
                El.AddHandler(Button.ClickEvent, new RoutedEventHandler(AllPurposeEventHandler));
            }

            MyWindow.Show();
        }
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------