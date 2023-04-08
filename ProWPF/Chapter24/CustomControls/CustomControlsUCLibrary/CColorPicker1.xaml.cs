using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
//------------------------------------------------------------------------
// 1. !!!!! Aj ked to na prvy pohlad vyzera, ze sa metody OnColorChanged() a OnColorRGBChanged() pri volanie jedne z nich budu vola rekurizvne NESTANE SA TAK. Je to preto, lebo WFP NEUMOZNUJE REENTERANCIU Pri volani Change Property Handlers.
// 2. !!! NEMOZEM POUZIT Coerce metody pre DP, kedze tie iba POZMENUJUE (KORIGUJU) BASE HODNOTU. Ja namiesto korekcie JE POTREBUJEM ZMENIT a preto nepouzijem Coerce metodu.
//------------------------------------------------------------------------
namespace CustomControlsUCLibrary
{
//------------------------------------------------------------------------
	public partial class CColorPicker1 : UserControl
	{
//------------------------------------------------------------------------
		// Definujem DP pre vysledny Color, ale aj pre danu zlozku Clolr.
        public static DependencyProperty			ColorProperty;
		// Definovat DP pre zlozky je dobre preto, aby jednotlive zlozky mohli byt pomocou Bindingu viazane na ine casti GUI.
        public static DependencyProperty			RedProperty;
        public static DependencyProperty			GreenProperty;
        public static DependencyProperty			BlueProperty;
		// Definujem BUBBLE RE, ktory sa odpali, ked sa meni Color.
        public static readonly RoutedEvent			ColorChangedEvent;
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private Color?								MPreviousColor;
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
        static CColorPicker1()
        {
			// !!! Zmenim nastavenia Metadat pre DP DefaultStyleKeyProperty.
            //DefaultStyleKeyProperty.OverrideMetadata(typeof(CColorPicker1), new FrameworkPropertyMetadata(typeof(CColorPicker1)));

			// !!! Pre kazdu DP zaregistrujem Change Property Handler, ktory robi to, ze ak je zmenena hodnota niektorej zlozky RGB tak sa zmeni hodnota Color a vice-versa.
			ColorProperty=DependencyProperty.Register("Color", typeof(Color), typeof(CColorPicker1), new FrameworkPropertyMetadata(new PropertyChangedCallback(OnColorChanged)));
            RedProperty=DependencyProperty.Register("Red", typeof(byte), typeof(CColorPicker1), new FrameworkPropertyMetadata(new PropertyChangedCallback(OnColorRGBChanged)));
            GreenProperty=DependencyProperty.Register("Green", typeof(byte), typeof(CColorPicker1), new FrameworkPropertyMetadata(new PropertyChangedCallback(OnColorRGBChanged)));
            BlueProperty=DependencyProperty.Register("Blue", typeof(byte), typeof(CColorPicker1), new FrameworkPropertyMetadata(new PropertyChangedCallback(OnColorRGBChanged)));

			// Zaregistrujem BUBBLE RE.
			// !!! Ao typ pouzijem STANDARNY RoutedPropertyChangedEventHandler<> aby som nemusel registrovat novy delegat.
			ColorChangedEvent=EventManager.RegisterRoutedEvent("ColorChanged", RoutingStrategy.Bubble, typeof(RoutedPropertyChangedEventHandler<Color>), typeof(CColorPicker1));

			// Zaregistrujem Undo Command pre danu triedu - CColorPicker1.
			CommandManager.RegisterClassCommandBinding(typeof(CColorPicker1), new CommandBinding(ApplicationCommands.Undo, UndoCommand_Executed, UndoCommand_CanExecute));
        }
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public CColorPicker1()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public Color								Color
        {
            get
            {
                return((Color)GetValue(ColorProperty));
            }
            set
            {
                SetValue(ColorProperty, value);
            }
        }
//------------------------------------------------------------------------
        public byte									Red
        {
            get
			{
				return((byte)GetValue(RedProperty));
			}
            set
			{
				SetValue(RedProperty, value);
			}
        }
//------------------------------------------------------------------------
        public byte									Green
        {
            get
			{
				return((byte)GetValue(GreenProperty));
			}
            set
			{
				SetValue(GreenProperty, value);
			}
        }
//------------------------------------------------------------------------
        public byte									Blue
        {
            get
			{
				return((byte)GetValue(BlueProperty));
			}
            set
			{
				SetValue(BlueProperty, value);
			}
        }
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
        public event RoutedPropertyChangedEventHandler<Color>	ColorChanged
        {
            add
			{
				AddHandler(ColorChangedEvent, value);
			}
            remove
			{
				RemoveHandler(ColorChangedEvent, value);
			}
        }
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		// Ak sa zmeni hodnota Color tak zmeni aj hodnoty Red, Green a Blue.
        private static void OnColorChanged(DependencyObject Sender, DependencyPropertyChangedEventArgs E)
        {           
            CColorPicker1		ColorPicker=(CColorPicker1) Sender;
            Color				OldColor=(Color) E.OldValue;
            Color				NewColor=(Color) E.NewValue;

            ColorPicker.Red=NewColor.R;
            ColorPicker.Green=NewColor.G;
            ColorPicker.Blue=NewColor.B;

            ColorPicker.MPreviousColor=OldColor;
            ColorPicker.OnColorChanged(OldColor, NewColor);
        }
//------------------------------------------------------------------------
		// Ak sa zmeni hodnota Red, Green a Blue tak zmeni aj hodnota Color.
        private static void OnColorRGBChanged(DependencyObject Sender, DependencyPropertyChangedEventArgs E)
        {           
            CColorPicker1		ColorPicker=(CColorPicker1) Sender;
			Color				Color=ColorPicker.Color;
			
            if (E.Property==RedProperty)
                Color.R=(byte) E.NewValue;
            else if (E.Property==GreenProperty)
                Color.G=(byte) E.NewValue;
            else if (E.Property==BlueProperty)
                Color.B=(byte) E.NewValue;
            
            ColorPicker.Color=Color;
        }
//------------------------------------------------------------------------
		// Odpalim RE.
        private void OnColorChanged(Color OldValue, Color NewValue)
        {
            RoutedPropertyChangedEventArgs<Color>	Args=new RoutedPropertyChangedEventArgs<Color>(OldValue, NewValue);

            Args.RoutedEvent=CColorPicker1.ColorChangedEvent;
            RaiseEvent(Args);
        }
//------------------------------------------------------------------------
		private static void UndoCommand_CanExecute(object Sender, CanExecuteRoutedEventArgs E)
		{
			CColorPicker1			ColorPicker=(CColorPicker1) Sender;

			E.CanExecute=ColorPicker.MPreviousColor.HasValue;
		}
//------------------------------------------------------------------------
		private static void UndoCommand_Executed(object Sender, ExecutedRoutedEventArgs E)
		{
			CColorPicker1			ColorPicker=(CColorPicker1) Sender;
			Color					CurrentColor=ColorPicker.Color;

			ColorPicker.Color=(Color) ColorPicker.MPreviousColor;
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------