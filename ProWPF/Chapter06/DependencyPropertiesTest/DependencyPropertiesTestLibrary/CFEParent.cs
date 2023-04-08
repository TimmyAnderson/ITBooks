using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Text;
using System.Windows;
using System.Windows.Media;
using System.Globalization;
using System.Windows.Markup;
using System.Windows.Controls;
//------------------------------------------------------------------------
namespace DependencyPropertiesTestLibrary
{
//------------------------------------------------------------------------
	// Kedze ma obsahovat Content tak je dobre ho dedit z ContentControl.
	public class CFEParent : ContentControl
	{
//------------------------------------------------------------------------
		// AP.
		// Not derived.
		public static DependencyProperty	FEIntAP1Property;
		// Derived.
		public static DependencyProperty	FEIntAP2Property;
//------------------------------------------------------------------------
		// DP, nie AP.
		// !!! Avsak pre obe DP definujem GetXXX() a SetXXX() metody a tym padom FUNGUJU ako AP.
		// Not derived.
		public static DependencyProperty	FEIntDP1Property;
		// Derived.
		public static DependencyProperty	FEIntDP2Property;
//------------------------------------------------------------------------
		// DP s podporou notifikacnych a validacnych delegatov.
		// Podporuje Validation.
		public static DependencyProperty	FEDelegates1Property;
		// Podporuje Validation a Notification.
		public static DependencyProperty	FEDelegates2Property;
		// Podporuje Validation, Notification a Coerce.
		public static DependencyProperty	FEDelegates3Property;
//------------------------------------------------------------------------
		// Shared DP.
		// Toto je klasicka DP.
		public static DependencyProperty	FESharedBaseProperty;
		// Toto je SHARED PROPERTY ODKAZUJUCA SA NA FESharedBaseProperty.
		public static DependencyProperty	FESharedReferenceProperty;
//------------------------------------------------------------------------
		private int							MLimit=50;
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		static CFEParent()
		{
			FrameworkPropertyMetadata		FPM1=new FrameworkPropertyMetadata();

			// !!! NE-povolim dedicnost.
			FPM1.Inherits=false;
			FEIntAP1Property=DependencyProperty.RegisterAttached("FEIntAP1",typeof(int),typeof(CFEParent),FPM1);


			FrameworkPropertyMetadata		FPM2=new FrameworkPropertyMetadata();

			// !!! Povolim dedicnost.
			FPM2.Inherits=true;
			FEIntAP2Property=DependencyProperty.RegisterAttached("FEIntAP2",typeof(int),typeof(CFEParent),FPM2);


			FrameworkPropertyMetadata		FPM3=new FrameworkPropertyMetadata();

			// !!! NE-povolim dedicnost.
			FPM3.Inherits=false;
			FEIntDP1Property=DependencyProperty.Register("FEIntDP1",typeof(int),typeof(CFEParent),FPM3);


			FrameworkPropertyMetadata		FPM4=new FrameworkPropertyMetadata();

			// !!! Povolim dedicnost.
			FPM4.Inherits=true;
			FEIntDP2Property=DependencyProperty.Register("FEIntDP2",typeof(int),typeof(CFEParent),FPM4);


			FrameworkPropertyMetadata		FPM5=new FrameworkPropertyMetadata();

			// !!! Povolim dedicnost.
			FPM5.Inherits=true;
			FEDelegates1Property=DependencyProperty.Register("FEDelegates1",typeof(int),typeof(CFEParent),FPM5,CFEParent.FEDelegates1ValidationCallback);


			// !!! Povolim dedicnost.
			FrameworkPropertyMetadata		FPM6=new FrameworkPropertyMetadata(35,FrameworkPropertyMetadataOptions.Inherits,CFEParent.FEDelegates2ValueChangedCallback);

			FEDelegates2Property=DependencyProperty.Register("FEDelegates2",typeof(int),typeof(CFEParent),FPM6,CFEParent.FEDelegates2ValidationCallback);


			// !!! Povolim dedicnost.
			FrameworkPropertyMetadata		FPM7=new FrameworkPropertyMetadata(35,FrameworkPropertyMetadataOptions.Inherits,CFEParent.FEDelegates3ValueChangedCallback,CFEParent.FEDelegates3CoerceValueCallback);

			FEDelegates3Property=DependencyProperty.Register("FEDelegates7",typeof(int),typeof(CFEParent),FPM7,CFEParent.FEDelegates3ValidationCallback);


			// !!! Povolim dedicnost.
			FrameworkPropertyMetadata		FPM8=new FrameworkPropertyMetadata();

			// !!! Povolim dedicnost.
			FPM8.Inherits=true;
			FESharedBaseProperty=DependencyProperty.Register("FESharedBase",typeof(int),typeof(CFEParent),FPM8);


			// !!! Povolim dedicnost.
			FrameworkPropertyMetadata		FPM9=new FrameworkPropertyMetadata();

			// !!! Povolim dedicnost.
			FPM9.Inherits=true;
			// !!!!! Ako Owner musi byt INA TRIEDA, kedze tato uz ho ma zaregistrovanu v podobe FESharedBaseProperty.
			FESharedReferenceProperty=FESharedBaseProperty.AddOwner(typeof(CFEChild),FPM9);
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
// Ak vypnem AS_AP tak sa bude tvarit ako DP a potom sa XAML neprekompiluje, kedze DP (ak sa k nim pristupuje cez property wrapper) nie je mozne nastavovat z XAML na inych Elements ako tie, ktore ich definuju.
#if !AS_AP		
		public int							FEIntDP1
		{
			get
			{
				return((int) GetValue(CFEParent.FEIntDP1Property));
			}
			set
			{
				SetValue(CFEParent.FEIntDP1Property,value);
			}
		}
//------------------------------------------------------------------------
		public int							FEIntDP2
		{
			get
			{
				return((int) GetValue(CFEParent.FEIntDP2Property));
			}
			set
			{
				SetValue(CFEParent.FEIntDP2Property,value);
			}
		}
#endif
//------------------------------------------------------------------------
		// !!! Kedze chcem aby FEDelegates1 fungoval ako klasicky DP tak prenho definujem property wrapper.
		public int							FEDelegates1
		{
			get
			{
				return((int) GetValue(CFEParent.FEDelegates1Property));
			}
			set
			{
				SetValue(CFEParent.FEDelegates1Property,value);
			}
		}
//------------------------------------------------------------------------
		// !!! Kedze chcem aby FEDelegates2 fungoval ako klasicky DP tak prenho definujem property wrapper.
		public int							FEDelegates2
		{
			get
			{
				return((int) GetValue(CFEParent.FEDelegates2Property));
			}
			set
			{
				SetValue(CFEParent.FEDelegates2Property,value);
			}
		}
//------------------------------------------------------------------------
		// !!! Kedze chcem aby FEDelegates3 fungoval ako klasicky DP tak prenho definujem property wrapper.
		public int							FEDelegates3
		{
			get
			{
				return((int) GetValue(CFEParent.FEDelegates3Property));
			}
			set
			{
				SetValue(CFEParent.FEDelegates3Property,value);
			}
		}
//------------------------------------------------------------------------
		public int							FESharedBase
		{
			get
			{
				return((int) GetValue(CFEParent.FESharedBaseProperty));
			}
			set
			{
				SetValue(CFEParent.FESharedBaseProperty,value);
			}
		}
//------------------------------------------------------------------------
		public int							FESharedReference
		{
			get
			{
				return((int) GetValue(CFEParent.FESharedReferenceProperty));
			}
			set
			{
				SetValue(CFEParent.FESharedReferenceProperty,value);
			}
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public static int GetFEIntAP1(UIElement Element)
		{
			return((int) Element.GetValue(CFEParent.FEIntAP1Property));
		}
//------------------------------------------------------------------------
		public static void SetFEIntAP1(UIElement Element, int Value)
		{
			Element.SetValue(CFEParent.FEIntAP1Property,Value);
		}
//------------------------------------------------------------------------
		public static int GetFEIntAP2(UIElement Element)
		{
			return((int) Element.GetValue(CFEParent.FEIntAP2Property));
		}
//------------------------------------------------------------------------
		public static void SetFEIntAP2(UIElement Element, int Value)
		{
			Element.SetValue(CFEParent.FEIntAP2Property,Value);
		}
//------------------------------------------------------------------------
#if AS_AP		
		public static int GetFEIntDP1(UIElement Element)
		{
			return((int) Element.GetValue(CFEParent.FEIntDP1Property));
		}
//------------------------------------------------------------------------
		public static void SetFEIntDP1(UIElement Element, int Value)
		{
			Element.SetValue(CFEParent.FEIntDP1Property,Value);
		}
//------------------------------------------------------------------------
		public static int GetFEIntDP2(UIElement Element)
		{
			return((int) Element.GetValue(CFEParent.FEIntDP2Property));
		}
//------------------------------------------------------------------------
		public static void SetFEIntDP2(UIElement Element, int Value)
		{
			Element.SetValue(CFEParent.FEIntDP2Property,Value);
		}
#endif
//------------------------------------------------------------------------
		// Validacna funkcia pre FEDelegates1.
		private static bool FEDelegates1ValidationCallback(object Value)
		{
			int		TValue=(int) Value;

			Debug.WriteLine(string.Format("\tDP VALIDATION - VALUE: {0} !",TValue));

			if (TValue==777)
				throw(new ArgumentOutOfRangeException("Value","Value has ERROR VALUE 777 !"));

			if (TValue<=100)
				return(true);
			else
				return(false);
		}
//------------------------------------------------------------------------
		// Validacna funkcia pre FEDelegates2.
		private static bool FEDelegates2ValidationCallback(object Value)
		{
			int		TValue=(int) Value;

			Debug.WriteLine(string.Format("\tDP VALIDATION - VALUE: {0} !",TValue));

			if (TValue==777)
				throw(new ArgumentOutOfRangeException("Value","Value has ERROR VALUE 777 !"));

			if (TValue<=100)
				return(true);
			else
				return(false);
		}
//------------------------------------------------------------------------
		// Validacna funkcia pre FEDelegates3.
		private static bool FEDelegates3ValidationCallback(object Value)
		{
			int		TValue=(int) Value;

			Debug.WriteLine(string.Format("\tDP VALIDATION - VALUE: {0} !",TValue));

			if (TValue==777)
				throw(new ArgumentOutOfRangeException("Value","Value has ERROR VALUE 777 !"));

			if (TValue<=100)
				return(true);
			else
				return(false);
		}
//------------------------------------------------------------------------
		// Callback o tom, ze doslo k zmene hodnoty.
		private static void FEDelegates2ValueChangedCallback(DependencyObject D, DependencyPropertyChangedEventArgs E)
		{
			CFEParent			Parent=(CFEParent) D;

			Debug.WriteLine(string.Format("\tDP CHANGED - NewValue: {0}, OldValue: {1} !",E.NewValue,E.OldValue));
		}
//------------------------------------------------------------------------
		// Callback o tom, ze doslo k zmene hodnoty.
		private static void FEDelegates3ValueChangedCallback(DependencyObject D, DependencyPropertyChangedEventArgs E)
		{
			CFEParent			Parent=(CFEParent) D;

			Debug.WriteLine(string.Format("\tDP CHANGED - NewValue: {0}, OldValue: {1} !",E.NewValue,E.OldValue));
		}
//------------------------------------------------------------------------
		// Coerce funkcia. Ma moznost ZMENIT VALUE.
		// !!! Nemeni vsak base value - IBA JU KONVERTUJE. BaseValue sa NEMENI.
		private static object FEDelegates3CoerceValueCallback(DependencyObject D, object BaseValue)
		{
			CFEParent			Parent=(CFEParent) D;
			int					TValue=(int) BaseValue;
			int					OutValue=0;

			// Ak je nad 100 prirata 10.
			// !!! Pri 91 a vyssie sa dostane nad 100, kde zlyha validacia.
			if (TValue>Parent.MLimit)
				OutValue=TValue+10;
			else
				OutValue=TValue;

			Debug.WriteLine(string.Format("\tCOERCE - New Value: {0}, Old Value: {1} !",OutValue,TValue));

			return(OutValue);
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		protected override void OnRender(DrawingContext DrawingContext)
		{
			// Nic nerenderujem.
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public override string ToString()
		{
#if AS_AP		
			return(string.Format("FEIntAP1: {0}, FEIntAP2: {1}, FEIntDP1: {2}, FEIntDP2: {3}, CFEChild: ({4}) !",CFEParent.GetFEIntAP1(this),CFEParent.GetFEIntAP2(this),CFEParent.GetFEIntDP1(this),CFEParent.GetFEIntDP2(this),Content.ToString()));
#else
			return(string.Format("FEIntAP1: {0}, FEIntAP2: {1}, FEIntDP1: {2}, FEIntDP2: {3}, CFEChild: ({4}) !",CFEParent.GetFEIntAP1(this),CFEParent.GetFEIntAP2(this),this.FEIntDP1,this.FEIntDP2,Content.ToString()));
#endif
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public string GetFEDelegates1String()
		{
			return(string.Format("FEDelegates1: {0} !",FEDelegates1));
		}
//------------------------------------------------------------------------
		public string GetFEDelegates2String()
		{
			return(string.Format("FEDelegates2: {0} !",FEDelegates2));
		}
//------------------------------------------------------------------------
		public string GetFEDelegates3String()
		{
			return(string.Format("FEDelegates3: {0} !",FEDelegates3));
		}
//------------------------------------------------------------------------
		public void SetLimit(int Value)
		{
			MLimit=Value;

			// !!! Zmenil sa limit a tak vykonam korekciu hodnoty.
			base.CoerceValue(CFEParent.FEDelegates3Property);
		}
//------------------------------------------------------------------------
		public string GetFESharedString()
		{
			return(string.Format("FESharedBase: {0}, FESharedReference: {1} !",FESharedBase,FESharedReference));
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------