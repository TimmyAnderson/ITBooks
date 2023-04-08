﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.CompilerServices;
//-------------------------------------------------------------------------------------------------------
namespace ParameterlessProperties
{
//-------------------------------------------------------------------------------------------------------
	public class CNameAutomaticProperties
	{
//-------------------------------------------------------------------------------------------------------
		public CNameAutomaticProperties()
		{
		}
//-------------------------------------------------------------------------------------------------------
		public CNameAutomaticProperties(string FirstName, string LastName, int Age)
		{
			this.FirstName=FirstName;
			this.LastName=LastName;
			this.Age=Age;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public string											FirstName
		{
			get;
			set;
		}
//-------------------------------------------------------------------------------------------------------
		public string											LastName
		{
			get;
			set;
		}
//-------------------------------------------------------------------------------------------------------
		public int												Age
		{
			get;
			set;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void NoChange(string FirstName, string LastName, int Age)
		{
			ToString();
		}
//-------------------------------------------------------------------------------------------------------
		public void Change(string FirstName, string LastName, int Age)
		{
			this.FirstName=FirstName;
			this.LastName=LastName;
			this.Age=Age;

			ToString();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override string ToString()
		{
			return(string.Format("First name: [{0}], Last name: [{1}], Age: [{2}]",FirstName,LastName,Age));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------