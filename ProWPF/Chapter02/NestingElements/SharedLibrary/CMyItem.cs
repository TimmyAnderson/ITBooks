using System;
using System.Collections.Generic;
using System.Text;
using System.Windows;
using System.Windows.Data;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Markup;
//------------------------------------------------------------------------
namespace SharedLibrary
{
//------------------------------------------------------------------------
	[ContentProperty("SomeValue")]
	public class CMyItem
	{
//------------------------------------------------------------------------
		private string					MSomeValue;
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public CMyItem()
		{
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public string					SomeValue
		{
			get
			{
				return(MSomeValue);
			}
			set
			{
				MSomeValue=value;
			}
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public override string ToString()
		{
			return(string.Format("Value: {0} !",MSomeValue));
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------