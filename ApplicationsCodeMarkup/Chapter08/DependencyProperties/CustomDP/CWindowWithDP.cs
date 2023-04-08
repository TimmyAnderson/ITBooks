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
	// Trieda definuje Window s ROVANKOU DP aka je definovana v CButtonWithDP.
	// !!! Vdaka definovaniu TEJ ISTEJ DP (je registrovana cez AddOwner()) je mozne DEMONSTROVAT DP INHERITANCE.
	public class CWindowWithDP : Window
	{
//------------------------------------------------------------------------------
        // Definujem DP, ktora je ROVNAKA ako DP v CButtonWithDP.
		// !!!!! DP 'Space' sa na urovni WINDOW PRIAMO NEPOUZIVA na rendering. Sluzi iba na VYTVORENIE DP INHERITANCE CHAIN.
        public static readonly DependencyProperty	SpaceProperty;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        static CWindowWithDP()
        {
			// Definujem METADATA pre DP.
            FrameworkPropertyMetadata		Metadata=new FrameworkPropertyMetadata();

			// DP je DEDENA. Ak je nastavena v PARENT ELEMENT, pricom CHILD ELEMENT ju NENASTAVI, tak CHILD ELEMENT bude mat hodnotu DP rovnu hodnote DP PARENT ELEMENTU.
            Metadata.Inherits=true;

            // Zaregistrujem DP.
			// !!!!! Na registrovanie pouzivam CButtonWithDP.AddOwner(), aby som docielil, ze DP definovana v CButtonWithDP a CWindowWithDP su V DEDICSKEJ HIERARCHII.
            SpaceProperty=CButtonWithDP.SpaceProperty.AddOwner(typeof(CWindowWithDP));
			
			// !!! Prepisem METADATA pre DP.
			SpaceProperty.OverrideMetadata(typeof(CWindowWithDP),Metadata);
        }
//------------------------------------------------------------------------------
		public CWindowWithDP()
		{
			
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
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
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------