using System;
using System.Collections.Generic;
using System.Text;
using System.Collections;
//------------------------------------------------------------------------
namespace DataViewsTestLibrary
{
//------------------------------------------------------------------------
	public class CAgeSorter : IComparer
	{
//------------------------------------------------------------------------
		public int Compare(object X, object Y)
		{
			CName				Name1=(CName) X;
			CName				Name2=(CName) Y;

			return(Name1.Age-Name2.Age);
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------