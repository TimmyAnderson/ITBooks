using System;
using System.Collections.Generic;
using System.Text;
//------------------------------------------------------------------------
namespace DataViewsTestLibrary
{
//------------------------------------------------------------------------
	// Trieda realizujuca filter.
	public class CTeenagerFilter
	{
//------------------------------------------------------------------------
		// Filtrovacia metoda. Jej prototyp zodpoveda Predicate<object>.
		public bool FilterOnlyTeenegers(Object Item)
		{
			CName			Name=(CName) Item;

			if (Name.Age>=13 && Name.Age<=19)
				return(true);
			else
				return(false);
		}
//------------------------------------------------------------------------
		// Filtrovacia metoda. Jej prototyp zodpoveda Predicate<object>.
		public bool FilterOnlyNonTeenegers(Object Item)
		{
			CName			Name=(CName) Item;

			if (Name.Age>=13 && Name.Age<=19)
				return(false);
			else
				return(true);
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------