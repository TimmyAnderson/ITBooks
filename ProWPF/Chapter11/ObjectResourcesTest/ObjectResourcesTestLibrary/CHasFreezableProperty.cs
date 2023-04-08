using System;
using System.Collections.Generic;
using System.Text;
using System.Windows;
using System.Windows.Media.Animation;
//------------------------------------------------------------------------
namespace ObjectResourcesTestLibrary
{
//------------------------------------------------------------------------
	public class CHasFreezableProperty : Freezable
	{
//------------------------------------------------------------------------
		public static DependencyProperty		SomeFrozenValueProperty;
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		static CHasFreezableProperty()
		{
			SomeFrozenValueProperty=DependencyProperty.Register("SomeFrozenValue",typeof(CMyFreezableClass),typeof(CHasFreezableProperty));
		}
//------------------------------------------------------------------------
		// Musi mat empty konstruktor kvoli XAML.
		public CHasFreezableProperty()
		{
			this.SomeFrozenValue=new CMyFreezableClass("EMPTY");
		}
//------------------------------------------------------------------------
		public CHasFreezableProperty(CMyFreezableClass SomeFrozenValue)
		{
			this.SomeFrozenValue=SomeFrozenValue;
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public CMyFreezableClass				SomeFrozenValue
		{
			get
			{
				return((CMyFreezableClass) GetValue(SomeFrozenValueProperty));
			}
			set
			{
				SetValue(SomeFrozenValueProperty,value);
			}
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		protected override Freezable CreateInstanceCore()
		{
			return(new CHasFreezableProperty(SomeFrozenValue));
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public override string ToString()
		{
			return(string.Format("SFV: {0}",SomeFrozenValue));
		}
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------