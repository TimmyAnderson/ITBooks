﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace DynamicTypes
{
//-------------------------------------------------------------------------------------------------------
	public class CName
	{
//-------------------------------------------------------------------------------------------------------
		private string											MFirstName;
		private string											MLastName;
		private int												MAge;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CName(string FirstName, string LastName, int Age)
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
		public void NoChange(string FirstName, string LastName, int Age)
		{
			ToString();
		}
//-------------------------------------------------------------------------------------------------------
		public void Change(string FirstName, string LastName, int Age)
		{
			MFirstName=FirstName;
			MLastName=LastName;
			MAge=Age;

			ToString();
		}
//-------------------------------------------------------------------------------------------------------
		public void Print()
		{
			Console.WriteLine(string.Format("First name: [{0}], Last name: [{1}], Age: [{2}] !",MFirstName,MLastName,MAge));
		}
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