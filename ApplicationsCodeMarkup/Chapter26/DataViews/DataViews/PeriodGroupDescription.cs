using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;
using System.Globalization;
//-------------------------------------------------------------------------------------------------------
namespace DataViews
{
//-------------------------------------------------------------------------------------------------------
	// CUSTOM trieda implementujuca GroupDescription.
	public class PeriodGroupDescription : GroupDescription
	{
//-------------------------------------------------------------------------------------------------------
		// Vracia meno GROUP podla hodnoty RECORDU.
        public override object GroupNameFromItem(object Item, int Level, CultureInfo Culture)
        {
            Person			LPerson=Item as Person;

            if (LPerson.BirthDate==null)
                return("Unknown");

            int			Year=((DateTime)LPerson.BirthDate).Year;
   
            if (Year<1575)
                return("Pre-Baroque");

            if (Year<1725)
                return("Baroque");

            if (Year<1795)
                return("Classical");

            if (Year<1870)
                return("Romantic");

            if (Year<1910)
                return("20th Century");

            return("Post-War");
        }
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------