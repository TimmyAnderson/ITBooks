﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace SerializationDeserialization
{
//-------------------------------------------------------------------------------------------------------
	[Serializable]
	public class CNameForBinder
	{
//-------------------------------------------------------------------------------------------------------
		private string											MFirstName;
		private string											MLastName;
		private int												MAge;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CNameForBinder(string FirstName, string LastName, int Age)
		{
			MFirstName=FirstName;
			MLastName=LastName;
			MAge=Age;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public string											FirstName
		{
			get
			{
				return(MFirstName);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public string											LastName
		{
			get
			{
				return(MLastName);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public int												Age
		{
			get
			{
				return(MAge);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override string ToString()
		{
			return(string.Format("First name: [{0}], Last name: [{1}], Age: [{2}]",MFirstName,MLastName,MAge));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------