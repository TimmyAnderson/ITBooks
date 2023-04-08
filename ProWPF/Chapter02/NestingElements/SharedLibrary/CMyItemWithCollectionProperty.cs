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
	[ContentProperty("SomeCollection")]
	public class CMyItemWithCollectionProperty
	{
//------------------------------------------------------------------------
		private CMyCollectionClass		MSomeCollection=new CMyCollectionClass();
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public CMyItemWithCollectionProperty()
		{
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public CMyCollectionClass		SomeCollection
		{
			get
			{
				return(MSomeCollection);
			}
			set
			{
				MSomeCollection=value;
			}
		}
//------------------------------------------------------------------------
		public string					Name
		{
			get
			{
				return(MSomeCollection.Name);
			}
			set
			{
				MSomeCollection.Name=value;
			}
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public override string ToString()
		{
			return(string.Format("Value: {0} !",MSomeCollection));
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------