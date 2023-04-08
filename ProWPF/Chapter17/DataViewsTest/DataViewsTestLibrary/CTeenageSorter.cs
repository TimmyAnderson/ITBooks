using System;
using System.Collections.Generic;
using System.Text;
using System.Collections;
//------------------------------------------------------------------------
namespace DataViewsTestLibrary
{
//------------------------------------------------------------------------
	// Neteenegery budu prvi.
	public class CTeenageSorter : IComparer
	{
//------------------------------------------------------------------------
		private bool IsTeenager(CName Name)
		{
			if (Name.Age>=13 && Name.Age<=19)
				return(true);
			else
				return(false);
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public int Compare(object X, object Y)
		{
			CName				Name1=(CName) X;
			CName				Name2=(CName) Y;

			if (IsTeenager(Name1)==true && IsTeenager(Name2)==false)
				return(1);
			else if (IsTeenager(Name1)==false && IsTeenager(Name2)==true)
				return(-1);
			else
				return(Name1.Age-Name2.Age);
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------