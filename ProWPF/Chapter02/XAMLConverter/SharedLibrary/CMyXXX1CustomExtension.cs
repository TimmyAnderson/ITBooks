using System;
using System.Collections.Generic;
using System.Text;
using System.ComponentModel;
using System.Windows.Markup;
//------------------------------------------------------------------------
namespace SharedLibrary
{
//------------------------------------------------------------------------
	[MarkupExtensionReturnTypeAttribute(typeof(CMyCustomClassSlave1))]
	public class CMyXXX1CustomExtension : MarkupExtension
	{
//------------------------------------------------------------------------
		private string						MValue;
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public CMyXXX1CustomExtension()
		{
			MValue="EMPTY !";
		}
//------------------------------------------------------------------------
		// !!! XAML vola tento kosntruktor. Pocet parametrov sa musi zhodovat s poctom deklarovanym v XAML.
		public CMyXXX1CustomExtension(string Value)
		{
			MValue=Value;
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public string						Value
		{
			get
			{
				return(MValue);
			}
			set
			{
				MValue=value;
			}
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public override object ProvideValue(IServiceProvider ServiceProvider)
		{
			return(new CMyCustomClassSlave1(MValue));
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------