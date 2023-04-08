using System;
using System.Collections.Generic;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.ComponentModel;
//------------------------------------------------------------------------
namespace MaskedTestBoxLibrary
{
//------------------------------------------------------------------------
	// Dedim z klasickeho WPF TextBoxu.
    public class MaskedTextBox : System.Windows.Controls.TextBox
    {
//------------------------------------------------------------------------
		// DP pre Mask.
        public static DependencyProperty		MaskProperty;
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
        static MaskedTextBox()
        {
			// Vytvorim DP pre Mask.
            MaskProperty=DependencyProperty.Register("Mask", typeof(string), typeof(MaskedTextBox), new FrameworkPropertyMetadata(MaskChanged));

			// Metadata pre TextBox.Text.
            FrameworkPropertyMetadata			Metadata=new FrameworkPropertyMetadata();
            
			// Nastavim Coerce metodu pre TextBox.Text.
			Metadata.CoerceValueCallback=CoerceText;            
			// Prepipsem metadata pre TextBox.Text.
            TextProperty.OverrideMetadata(typeof(MaskedTextBox), Metadata);

			// Zrusim moznost pastovania, tym ze metodu nastavim na NULL.
            CommandManager.RegisterClassCommandBinding(typeof(MaskedTextBox), new CommandBinding(ApplicationCommands.Paste, null));
        }
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
        public MaskedTextBox()
            : base()
        {
            CommandBinding				CommandBinding1=new CommandBinding(ApplicationCommands.Paste, null, SuppressCommand);

            // Zrusim operaciu Paste.
			this.CommandBindings.Add(CommandBinding1);

            CommandBinding				CommandBinding2=new CommandBinding(ApplicationCommands.Cut, null, SuppressCommand);

            // Zrusim operaciu Cut.
            this.CommandBindings.Add(CommandBinding2);
        }
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
        public string							Mask
        {
            get
			{
				return((string) GetValue(MaskProperty));
			}
            set
			{
				SetValue(MaskProperty, value);
			}
        }          
//------------------------------------------------------------------------
		// Urcuje ci je CELY TEXT VYPLNENY PODLA MASKY.
        public bool								MaskCompleted
        {            
            get
            {
                MaskedTextProvider		MaskProvider=GetMaskProvider();

                return(MaskProvider.MaskCompleted);
            }
        }
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		// Metoda Change na DP Mask.
        private static void MaskChanged(DependencyObject D, DependencyPropertyChangedEventArgs E)
        {
            MaskedTextBox				TextBox=(MaskedTextBox) D;

			// Urobi korekciu textu, ked sa zmeni Mask.
            D.CoerceValue(TextProperty);
        }
//------------------------------------------------------------------------
		// Coerce metoda. Robi korekciu textu.
        private static object CoerceText(DependencyObject D, object Value)
        {
            MaskedTextBox				TextBox=(MaskedTextBox) D;
            MaskedTextProvider			MaskProvider=new MaskedTextProvider(TextBox.Mask);

			// Nastavim hodnotu MaskProvider A TYM SA VLASTNE VYKONA KOREKCIA.
            MaskProvider.Set((string) Value);

			// Vratim KORIGOVANU HODNOTU.
            return(MaskProvider.ToDisplayString());
        }
//------------------------------------------------------------------------
		// Vracia objekt MaskedTextProvider pre danu DANU a TEXT.
        private MaskedTextProvider GetMaskProvider()
        {
            MaskedTextProvider		MaskProvider=new MaskedTextProvider(Mask);

            MaskProvider.Set(Text);

            return(MaskProvider);
        }
//------------------------------------------------------------------------
        // Skoci na dalsi editovatelny znak.
        private int SkipToEditableCharacter(int StartPos)
        {
            MaskedTextProvider		MaskProvider=GetMaskProvider();
            int						NewPos=MaskProvider.FindEditPositionFrom(StartPos, true);

            if (NewPos==-1)
            {
                // Ak som na konci.
                return(StartPos);
            }
            else
            {
                return(NewPos);
            }
        }
//------------------------------------------------------------------------
		// Potlaci Command.
        private void SuppressCommand(object Sender, CanExecuteRoutedEventArgs E)
        {
            E.CanExecute=false;
            E.Handled=true;
        }
//------------------------------------------------------------------------
		// Robi resfresh textu a pozicie v nom.
        private void RefreshText(MaskedTextProvider MaskProvider, int Pos)
        { 
            // Refresh string.            
            this.Text=MaskProvider.ToDisplayString();

            // Position cursor.
            this.SelectionStart=Pos;
        }
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
        protected override void OnPreviewKeyDown(KeyEventArgs E)
        {
            base.OnKeyDown(E);

            MaskedTextProvider		MaskProvider=GetMaskProvider();
            int						Pos=this.SelectionStart;

			// Ak bol stlaceny Delete.
            if (E.Key==Key.Delete && Pos<(this.Text.Length))
            {
                if (MaskProvider.RemoveAt(Pos)==true)
                {
                    RefreshText(MaskProvider, Pos);
                }

                E.Handled = true;
            }
			// Ak bol stlaceny Backspace.
            else if (E.Key==Key.Back)
            {
                if (Pos>0)
                {
                    Pos--;

                    if (MaskProvider.RemoveAt(Pos)==true)
                    {
                        RefreshText(MaskProvider, Pos);
                    }
                }

                E.Handled=true;
            }
        }
//------------------------------------------------------------------------
        protected override void OnPreviewTextInput(TextCompositionEventArgs E)
        {
            MaskedTextProvider	MaskProvider=GetMaskProvider();
            int					Pos=this.SelectionStart;

            // Pridava sa novy znak.
            if (Pos<this.Text.Length)
            {
                Pos=SkipToEditableCharacter(Pos);

                // Overwrite mode is on.
                if (Keyboard.IsKeyToggled(Key.Insert)==true)
                {
                    if (MaskProvider.Replace(E.Text, Pos)==true)
                    {
                        Pos++;
                    }
                }
                // Insert mode is on.
                else
                {
                    if (MaskProvider.InsertAt(E.Text, Pos)==true)
                    {
                        Pos++;
                    }
                }

                // Najdi nasledujucu editovatelnu poziciu.
                Pos=SkipToEditableCharacter(Pos);
            }

            RefreshText(MaskProvider, Pos);
            E.Handled=true;

            base.OnPreviewTextInput(E);
        }
//------------------------------------------------------------------------
    }
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------