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
namespace CustomDP
{
//------------------------------------------------------------------------------
	// Trieda definuje BUTTON s DP, ktora urcuje velkost rozostupov medzi pismenami v texte BUTTON.
	public class CButtonWithDP : Button
	{
//------------------------------------------------------------------------------
        // Definujem DP pre velkost rozostupov medzi textom v Button.
        public static readonly DependencyProperty	SpaceProperty;
//------------------------------------------------------------------------------
        private string								MButtonText;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        static CButtonWithDP()
        {
			// Definujem METADATA pre DP.
            FrameworkPropertyMetadata		Metadata = new FrameworkPropertyMetadata();

			// Definujem DEFAULT HODNOTU DP.
            Metadata.DefaultValue=1;
			// Zmena DP zapricinuje ZMENU VELKOSTI ELEMENTU a preto treba vykonat LAYOUT FAZU.
            Metadata.AffectsMeasure=true;
			// DP je DEDENA. Ak je nastavena v PARENT ELEMENT, pricom CHILD ELEMENT ju NENASTAVI, tak CHILD ELEMENT bude mat hodnotu DP rovnu hodnote DP PARENT ELEMENTU.
            Metadata.Inherits=true;
			// !!!!! Definujem CALLBACK, ktory sa zavola pri ZMENE HODNOTY DP.
            Metadata.PropertyChangedCallback+=OnSpacePropertyChanged;

            // Zaregistrujem DP.
			// !!! Ako VALIDATOR definujem metodu ValidateSpaceValue().
            SpaceProperty=DependencyProperty.Register("Space", typeof(int), typeof(CButtonWithDP), Metadata, ValidateSpaceValue);
        }
//------------------------------------------------------------------------------
		public CButtonWithDP()
		{

		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		// .NET PROPERTY.
		// !!! Mohol by som ju definovat ako DP a ak by som to spravil, tak by som ziskal napriklad moznost vykonat DataBining.
        public string								ButtonText
        {
            get
            {
                return(MButtonText);
            }
            set
            {
                MButtonText=value;
                Content=SpaceOutText(MButtonText);
            }
        }
//------------------------------------------------------------------------------
		// .NET property sluziaca na pristup k DP.
        public int									Space
        {
            get
            {
                return((int)GetValue(SpaceProperty));
            }
            set
            {
                SetValue(SpaceProperty, value);
            }
        }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        // STATICKA validacna metoda, kontrolujuca korektnost hodnoty DP.
        private static bool ValidateSpaceValue(object Obj)
        {
            int			Value=(int) Obj;

			if (Value>=0)
				return(true);
			else
				return(false);
        }
//------------------------------------------------------------------------------
        // STATICKA CALLBACK metoda volana pri ZMENE HODNOT DP.
        private static void OnSpacePropertyChanged(DependencyObject Obj, DependencyPropertyChangedEventArgs Args)
        {
            CButtonWithDP		Btn=Obj as CButtonWithDP;

			// Podla hodnoty DP 'Space' vytvorim NOVY CONTENT.
			string				NewContent=Btn.SpaceOutText(Btn.ButtonText);

			// !!!!! Vdaka tomu, ze som ZMENIL hodnotu Content, dojde k RENDEROVANIU BUTTON.
            Btn.Content=NewContent;
        }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        // Metoda, ktora vytvory podla hodnoty DP 'Space' CONTENT pre BUTTON.
        private string SpaceOutText(string Str)
        {
            if (Str==null)
                return(null);

            StringBuilder	Build=new StringBuilder();

            foreach (char Ch in Str)
                Build.Append(Ch+new string(' ', Space));

            return(Build.ToString());
        }
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------