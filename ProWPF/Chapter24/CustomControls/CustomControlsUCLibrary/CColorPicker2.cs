using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
//------------------------------------------------------------------------
// 1. !!!!! Teraz definujem Custom Control, ktory dedi z Control a NIE UserControl.
// 2. Tento Control bude mat moznost zadefinovat CUSTOM TEMPLATE pomocou CUSTOM Style.
// 3. Nato aby som mohol definovat Custom Style musim zmenit Metadata pomocou metody OverrideMetadata.
// 4. Prepisem Metadata pre DP DefaultStyle a to tak, aby tahal metadata asociovane s triedou CColorPicker2. Tieto standardne hlada v adresari Themes v Generic.XAML.
//------------------------------------------------------------------------
namespace CustomControlsUCLibrary
{
//------------------------------------------------------------------------
	// !!!!! Dedi z Control nie UserControl.
    [TemplatePart(Name="PART_RedSlider", Type=typeof(RangeBase))]
    [TemplatePart(Name="PART_BlueSlider", Type=typeof(RangeBase))]
    [TemplatePart(Name="PART_GreenSlider", Type=typeof(RangeBase))]
    [TemplatePart(Name="PART_PreviewBrush", Type=typeof(SolidColorBrush))]
	public partial class CColorPicker2 : Control
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
        static CColorPicker2()
        {
			// !!! Zmenim nastavenia Metadat pre DP DefaultStyleKeyProperty a tym UMOZNIM DEFINOVAT CUSTOM STYLE.
			// !!! Prepisem DefaultStyleKey tak, ze ho nastavim na to aby tahal data z CColorPicker2. Ta je ulozena v STANDARDNOM ADRESARI Themes v Generic.XAML.
            DefaultStyleKeyProperty.OverrideMetadata(typeof(CColorPicker2), new FrameworkPropertyMetadata(typeof(CColorPicker2)));

			// !!! Pre kazdu DP zaregistrujem Change Property Handler, ktory robi to, ze ak je zmenena hodnota niektorej zlozky RGB tak sa zmeni hodnota Color a vice-versa.
			ColorProperty=DependencyProperty.Register("Color", typeof(Color), typeof(CColorPicker2), new FrameworkPropertyMetadata(new PropertyChangedCallback(OnColorChanged)));
            RedProperty=DependencyProperty.Register("Red", typeof(byte), typeof(CColorPicker2), new FrameworkPropertyMetadata(new PropertyChangedCallback(OnColorRGBChanged)));
            GreenProperty=DependencyProperty.Register("Green", typeof(byte), typeof(CColorPicker2), new FrameworkPropertyMetadata(new PropertyChangedCallback(OnColorRGBChanged)));
            BlueProperty=DependencyProperty.Register("Blue", typeof(byte), typeof(CColorPicker2), new FrameworkPropertyMetadata(new PropertyChangedCallback(OnColorRGBChanged)));

			// Zaregistrujem BUBBLE RE.
			// !!! Ao typ pouzijem STANDARNY RoutedPropertyChangedEventHandler<> aby som nemusel registrovat novy delegat.
			ColorChangedEvent=EventManager.RegisterRoutedEvent("ColorChanged", RoutingStrategy.Bubble, typeof(RoutedPropertyChangedEventHandler<Color>), typeof(CColorPicker2));

			// Zaregistrujem Undo Command pre danu triedu - CColorPicker2.
			CommandManager.RegisterClassCommandBinding(typeof(CColorPicker2), new CommandBinding(ApplicationCommands.Undo, UndoCommand_Executed, UndoCommand_CanExecute));
        }
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public CColorPicker2()
		{
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
            CColorPicker2		ColorPicker=(CColorPicker2) Sender;
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
            CColorPicker2		ColorPicker=(CColorPicker2) Sender;
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

            Args.RoutedEvent=CColorPicker2.ColorChangedEvent;
            RaiseEvent(Args);
        }
//------------------------------------------------------------------------
		private static void UndoCommand_CanExecute(object Sender, CanExecuteRoutedEventArgs E)
		{
			CColorPicker2			ColorPicker=(CColorPicker2) Sender;

			E.CanExecute=ColorPicker.MPreviousColor.HasValue;
		}
//------------------------------------------------------------------------
		private static void UndoCommand_Executed(object Sender, ExecutedRoutedEventArgs E)
		{
			CColorPicker2			ColorPicker=(CColorPicker2) Sender;
			Color					CurrentColor=ColorPicker.Color;

			ColorPicker.Color=(Color) ColorPicker.MPreviousColor;
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		// Je volana ked sa zmeni Template.
        public override void OnApplyTemplate()
        {
            base.OnApplyTemplate();

            RangeBase			Slider=GetTemplateChild("PART_RedSlider") as RangeBase;

            if (Slider!=null)
            {
                Binding			Binding=new Binding("Red");

                Binding.Source=this;
                Binding.Mode=BindingMode.TwoWay;
                Slider.SetBinding(RangeBase.ValueProperty, Binding);
            }

            Slider=GetTemplateChild("PART_GreenSlider") as RangeBase;

            if (Slider!=null)
            {
                Binding			Binding=new Binding("Green");

                Binding.Source=this;
                Binding.Mode=BindingMode.TwoWay;
                Slider.SetBinding(RangeBase.ValueProperty, Binding);
            }

            Slider=GetTemplateChild("PART_BlueSlider") as RangeBase;

            if (Slider!=null)
            {
                Binding			Binding=new Binding("Blue");

                Binding.Source=this;
                Binding.Mode=BindingMode.TwoWay;
                Slider.SetBinding(RangeBase.ValueProperty, Binding);
            }

            SolidColorBrush		Brush=GetTemplateChild("PART_PreviewBrush") as SolidColorBrush;

            if (Brush!=null)
            {
                Binding			Binding=new Binding("Color");

                Binding.Source=Brush;
                Binding.Mode=BindingMode.OneWayToSource;
                this.SetBinding(CColorPicker2.ColorProperty, Binding);
            } 
        }
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------