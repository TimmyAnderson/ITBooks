using System;
using System.Collections.Generic;
using System.Text;
//------------------------------------------------------------------------
namespace BindingToNonElementsLibrary
{
//------------------------------------------------------------------------
	public class CMyName
	{
//------------------------------------------------------------------------
		private string					MFirstName;
		private string					MLastName;
		private int						MAge;
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		// Budem sa na nu odkazovat z XAML.
		private static CMyName			MTimmy=new CMyName("Timmy","Anderson",12);
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public CMyName()
		{
			MFirstName="EMPTY";
			MLastName="EMPTY";
			MAge=-1;
		}
//------------------------------------------------------------------------
		public CMyName(string FirstName, string LastName, int Age)
		{
			MFirstName=FirstName;
			MLastName=LastName;
			MAge=Age;
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public static CMyName			Timmy
		{
			get
			{
				return(MTimmy);
			}
			set
			{
				MTimmy=value;
			}
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public string					FirstName
		{
			get
			{
				return(MFirstName);
			}
			set
			{
				MFirstName=value;
			}
		}
//------------------------------------------------------------------------
		public string					LastName
		{
			get
			{
				return(MLastName);
			}
			set
			{
				MLastName=value;
			}
		}
//------------------------------------------------------------------------
		public int						Age
		{
			get
			{
				return(MAge);
			}
			set
			{
				MAge=value;
			}
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------