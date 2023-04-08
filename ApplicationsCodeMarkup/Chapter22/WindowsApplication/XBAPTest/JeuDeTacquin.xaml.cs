using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Threading;
//-------------------------------------------------------------------------------------------------------
namespace XBAPTest
{
//-------------------------------------------------------------------------------------------------------
    public partial class JeuDeTacquin : Page
    {
//-------------------------------------------------------------------------------------------------------
        private bool											MIsLoaded=false;
        private int												MXEmpty;
		private int												MYEmpty;
		private int												MICounter;
        private Key[]											MKeys={ Key.Left, Key.Right, Key.Up, Key.Down };
        private Random											MRand;
        private UIElement										MElEmptySpare=new Empty();
//-------------------------------------------------------------------------------------------------------
        public int												MNumberRows=4;
        public int												MNumberCols=4;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        public JeuDeTacquin()
        {
            Loaded+=PageOnLoaded;
            InitializeComponent();
        }
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        protected override void OnKeyDown(KeyEventArgs Args)
        {
            base.OnKeyDown(Args);

            switch (Args.Key)
            {
                case Key.Right:
					MoveTile(MXEmpty - 1, MYEmpty); 
				break;

                case Key.Left:
					MoveTile(MXEmpty + 1, MYEmpty);
				break;

                case Key.Down:
					MoveTile(MXEmpty, MYEmpty - 1);
				break;

                case Key.Up:
					MoveTile(MXEmpty, MYEmpty + 1);
				break;

                default:
                    return;
            }

            Args.Handled=true;
        }
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        private void PageOnLoaded(object Sender, RoutedEventArgs Args)
        {
			// Iba pri prvom volani sa inicializuje Page.
            if (MIsLoaded==false)
            {
                Title=string.Format("Jeu de Tacquin ({0}\x00D7{1})", MNumberCols, MNumberRows);

                MUniGrid.Rows=MNumberRows;
                MUniGrid.Columns=MNumberCols;

                for (int i=0;i<MNumberRows*MNumberCols-1;i++)
                {
                    Tile		LTile=new Tile();

                    LTile.Text=(i + 1).ToString();
                    LTile.MouseLeftButtonDown+=TileOnMouseLeftButtonDown; ;
                    MUniGrid.Children.Add(LTile);
                }

                MUniGrid.Children.Add(new Empty());
                MXEmpty=MNumberCols-1;
                MYEmpty=MNumberRows-1;

                MIsLoaded=true;
            }

            Focus();
        }
//-------------------------------------------------------------------------------------------------------
        private void TileOnMouseLeftButtonDown(object Sender, MouseButtonEventArgs Args)
        {
            Focus();

            Tile		LTile=Sender as Tile;

            int			IMove=MUniGrid.Children.IndexOf(LTile);
            int			XMove=IMove % MNumberCols;
            int			YMove=IMove / MNumberCols;

            if (XMove==MXEmpty)
                while (YMove != MYEmpty)
                    MoveTile(XMove, MYEmpty + (YMove - MYEmpty) / Math.Abs(YMove - MYEmpty));

            if (YMove==MYEmpty)
                while (XMove!=MXEmpty)
                    MoveTile(MXEmpty + (XMove - MXEmpty) / Math.Abs(XMove - MXEmpty), YMove);

            Args.Handled=true;
        }
//-------------------------------------------------------------------------------------------------------
        private void ScrambleOnClick(object Sender, RoutedEventArgs Args)
        {
            MRand=new Random();
            MICounter=16*MNumberCols*MNumberRows;

            DispatcherTimer			Tmr=new DispatcherTimer();

            Tmr.Interval=TimeSpan.FromMilliseconds(10);
            Tmr.Tick+=TimerOnTick;
            Tmr.Start();
        }
//-------------------------------------------------------------------------------------------------------
        private void TimerOnTick(object Sender, EventArgs Args)
        {
            for (int i=0;i<5;i++)
            {
                MoveTile(MXEmpty, MYEmpty + MRand.Next(3) - 1);
                MoveTile(MXEmpty + MRand.Next(3) - 1, MYEmpty);
            }

            if (MICounter--==0)
                (Sender as DispatcherTimer).Stop();
        }
//-------------------------------------------------------------------------------------------------------
        private void MoveTile(int XTile, int YTile)
        {
            if ((XTile == MXEmpty && YTile == MYEmpty) || XTile < 0 || XTile >= MNumberCols || YTile < 0 || YTile >= MNumberRows)
                return;

            int			ITile=MNumberCols * YTile + XTile;
            int			IEmpty=MNumberCols * MYEmpty + MXEmpty;
            UIElement	ElTile=MUniGrid.Children[ITile];
            UIElement	ElEmpty=MUniGrid.Children[IEmpty];

            MUniGrid.Children.RemoveAt(ITile);
            MUniGrid.Children.Insert(ITile, MElEmptySpare);
            MUniGrid.Children.RemoveAt(IEmpty);
            MUniGrid.Children.Insert(IEmpty, ElTile);

            MXEmpty=XTile;
            MYEmpty=YTile;
            MElEmptySpare=ElEmpty;
        }
//-------------------------------------------------------------------------------------------------------
        private void NextOnClick(object Sender, RoutedEventArgs Args)
        {
            if (NavigationService.CanGoForward==false)
            {
				// !!! Vytvori sa NOVY PAGE objekt.
                JeuDeTacquin		Page=new JeuDeTacquin();

                Page.MNumberRows=MNumberRows+1;
                Page.MNumberCols=MNumberCols+1;

                NavigationService.Navigate(Page);
            }
            else
                NavigationService.GoForward();
        }
//-------------------------------------------------------------------------------------------------------
    }
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------