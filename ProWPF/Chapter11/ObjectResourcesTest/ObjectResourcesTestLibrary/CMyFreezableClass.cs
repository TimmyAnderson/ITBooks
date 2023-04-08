using System;
using System.Collections.Generic;
using System.Text;
using System.Windows;
using System.Windows.Media.Animation;
//------------------------------------------------------------------------
namespace ObjectResourcesTestLibrary
{
//------------------------------------------------------------------------
	public class CMyFreezableClass : Freezable
	{
//------------------------------------------------------------------------
		public static DependencyProperty		MyCustomValueProperty;
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		static CMyFreezableClass()
		{
			MyCustomValueProperty=DependencyProperty.Register("MyCustomValue",typeof(string),typeof(CMyFreezableClass));
		}
//------------------------------------------------------------------------
		// Musi mat empty konstruktor kvoli XAML.
		public CMyFreezableClass()
		{
			this.MyCustomValue="EMPTY";
		}
//------------------------------------------------------------------------
		public CMyFreezableClass(string MyCustomValue)
		{
			this.MyCustomValue=MyCustomValue;
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public string							MyCustomValue
		{
			get
			{
				return((string) GetValue(MyCustomValueProperty));
			}
			set
			{
				SetValue(MyCustomValueProperty,value);
			}
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		protected override Freezable CreateInstanceCore()
		{
			return(new CMyFreezableClass(MyCustomValue));
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public override string ToString()
		{
			return(string.Format("CV: {0}",MyCustomValue));
		}
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------