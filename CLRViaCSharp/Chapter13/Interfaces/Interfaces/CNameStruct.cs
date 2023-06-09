﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace Interfaces
{
//-------------------------------------------------------------------------------------------------------
	public struct CNameStruct : IChangeStruct
	{
//-------------------------------------------------------------------------------------------------------
		private string											MFirstName;
		private string											MLastName;
		private int												MAge;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CNameStruct(string FirstName, string LastName, int Age)
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
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override bool Equals(object Obj)
		{
			if (Obj==null)
			{
				return(false);
			}

			CNameStruct											Name=(CNameStruct) Obj;

			if (MFirstName!=Name.MFirstName)
			{
				return(false);
			}

			if (MLastName!=Name.MLastName)
			{
				return(false);
			}

			if (MAge!=Name.MAge)
			{
				return(false);
			}

			return(true);
		}
//-------------------------------------------------------------------------------------------------------
		public override int GetHashCode()
		{
			return(base.GetHashCode());
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