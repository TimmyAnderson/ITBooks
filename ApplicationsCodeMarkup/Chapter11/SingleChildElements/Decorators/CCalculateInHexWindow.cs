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
using System.Windows.Threading;
//------------------------------------------------------------------------------
namespace Decorators
{
//------------------------------------------------------------------------------
	public class CCalculateInHexWindow : Window
	{
//------------------------------------------------------------------------------
        private CRoundedButton						MBtnDisplay;
        private ulong								MNumDisplay;
        private ulong								MNumFirst;
        private bool								MBNewNumber=true;
        private char								MChOperation='=';
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        public CCalculateInHexWindow()
        {
            Title="Calculate in Hex";
            SizeToContent=SizeToContent.WidthAndHeight;
            ResizeMode=ResizeMode.CanMinimize;

            Grid					MyGrid=new Grid();

            MyGrid.Margin = new Thickness(4);
            Content=MyGrid;

            for (int i=0;i<5;i++)
            {
                ColumnDefinition	Col=new ColumnDefinition();

                Col.Width=GridLength.Auto;
                MyGrid.ColumnDefinitions.Add(Col);
            }

            for (int i=0;i<7;i++)
            {
                RowDefinition		Row=new RowDefinition();

                Row.Height=GridLength.Auto;
                MyGrid.RowDefinitions.Add(Row);
            }

            string[]				StrButtons={ "0", "D", "E", "F", "+", "&", "A", "B", "C", "-", "|", "7", "8", "9", "*", "^", "4", "5", "6", "/", "<<", "1", "2", "3", "%", ">>", "0", "Back", "Equals" };
            int						IRow=0;
			int						ICol=0;

            foreach (string Str in StrButtons)
            {
                CRoundedButton		Btn=new CRoundedButton();

                Btn.Focusable=false;
                Btn.Height=32;
                Btn.Margin=new Thickness(4);
                Btn.Click+=ButtonOnClick;

                TextBlock			Txt=new TextBlock();

                Txt.Text=Str;
                Btn.Child=Txt;

                MyGrid.Children.Add(Btn);
                Grid.SetRow(Btn, IRow);
                Grid.SetColumn(Btn, ICol);

                if (IRow==0 && ICol==0)
                {
                    MBtnDisplay=Btn;
                    Btn.Margin=new Thickness(4, 4, 4, 6);
                    Grid.SetColumnSpan(Btn, 5);
                    IRow=1;
                }

                else if (IRow==6 && ICol>0)
                {
                    Grid.SetColumnSpan(Btn, 2);
                    ICol+=2;
                }
                else
                {
                    Btn.Width=32;

                    if (0==(ICol=(ICol+1)%5))
                        IRow++;
                }
            }
        }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        private void ButtonOnClick(object Sender, RoutedEventArgs Args)
        {
            CRoundedButton		Btn=Args.Source as CRoundedButton;

            if (Btn==null)
                return;

            string				StrButton=(Btn.Child as TextBlock).Text;
            char				ChButton=StrButton[0];

            if (StrButton=="Equals")
                ChButton='=';

            if (Btn==MBtnDisplay)
                MNumDisplay=0;
            else if (StrButton=="Back")
                MNumDisplay/=16;
            else if (Char.IsLetterOrDigit(ChButton)==true)
            {
                if (MBNewNumber==true)
                {
                    MNumFirst=MNumDisplay;
                    MNumDisplay=0;
                    MBNewNumber=false;
                }

                if (MNumDisplay<=(ulong.MaxValue>>4))
                    MNumDisplay=16*MNumDisplay + (ulong)(ChButton-(char.IsDigit(ChButton) ? '0' : 'A' - 10));
            }
            else
            {
                if (MBNewNumber==false)
                {
                    switch (MChOperation)
                    {
                        case '=': break;
                        case '+': MNumDisplay = MNumFirst + MNumDisplay; break;
                        case '-': MNumDisplay = MNumFirst - MNumDisplay; break;
                        case '*': MNumDisplay = MNumFirst * MNumDisplay; break;
                        case '&': MNumDisplay = MNumFirst & MNumDisplay; break;
                        case '|': MNumDisplay = MNumFirst | MNumDisplay; break;
                        case '^': MNumDisplay = MNumFirst ^ MNumDisplay; break;
                        case '<': MNumDisplay = MNumFirst << (int)MNumDisplay; break;
                        case '>': MNumDisplay = MNumFirst >> (int)MNumDisplay; break;
                        case '/': MNumDisplay = (MNumDisplay!=0) ? (MNumFirst / MNumDisplay) : ulong.MaxValue; break;
                        case '%': MNumDisplay = (MNumDisplay!=0) ? (MNumFirst % MNumDisplay) : ulong.MaxValue; break;
                        default: MNumDisplay = 0; break;
                    }
                }

                MBNewNumber=true;
                MChOperation=ChButton;
            }

			TextBlock			Text=new TextBlock();

            Text.Text=string.Format("{0:X}", MNumDisplay);
            MBtnDisplay.Child=Text;
        }
//------------------------------------------------------------------------------
        private void TimerOnTick(object Sender, EventArgs Args)
        {
            DispatcherTimer		Tmr=Sender as DispatcherTimer;
            CRoundedButton		Btn=Tmr.Tag as CRoundedButton;

            Btn.IsPressed=false;

            Tmr.Stop();
            Tmr.Tick-=TimerOnTick;
        }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        protected override void OnTextInput(TextCompositionEventArgs Args)
        {
            base.OnTextInput(Args);

            if (Args.Text.Length==0)
                return;

            char						ChKey=char.ToUpper(Args.Text[0]);

            foreach (UIElement Child in (Content as Grid).Children)
            {
                CRoundedButton			Btn=Child as CRoundedButton;
                string					StrButton=(Btn.Child as TextBlock).Text;

                if ((ChKey == StrButton[0] && Btn != MBtnDisplay && StrButton != "Equals" && StrButton != "Back") || (ChKey == '=' && StrButton == "Equals") || (ChKey == '\r' && StrButton == "Equals") || (ChKey == '\b' && StrButton == "Back") || (ChKey == '\x1B' && Btn == MBtnDisplay))
                {
                    RoutedEventArgs		ArgsClick=new RoutedEventArgs(CRoundedButton.ClickEvent, Btn);

                    Btn.RaiseEvent(ArgsClick);
                    Btn.IsPressed=true;

                    DispatcherTimer		Tmr=new DispatcherTimer();

                    Tmr.Interval=TimeSpan.FromMilliseconds(100);
                    Tmr.Tag=Btn;
                    Tmr.Tick+=TimerOnTick;
                    Tmr.Start();

                    Args.Handled=true;
                } 
            }
        }
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------