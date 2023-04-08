﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using WorkingWithData.Model;
//----------------------------------------------------------------------------------------------------------------------
namespace WorkingWithData.Database
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CEntityPerson
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MID;
		private string											MFirstName;
		private string											MLastName;
		private int												MAge;
		private int												MSex;
		private string											MCity;
		private string											MCountry;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityPerson()
		{
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityPerson(CPerson Person)
		{
			MID=Person.ID;
			MFirstName=Person.FirstName;
			MLastName=Person.LastName;
			MAge=Person.Age;
			MSex=(int) Person.Sex;
			MCity=Person.Address.City;
			MCountry=Person.Address.Country;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public int												ID
		{
			get
			{
				return(MID);
			}
			set
			{
				MID=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public string											FirstName
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
//----------------------------------------------------------------------------------------------------------------------
		public string											LastName
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
//----------------------------------------------------------------------------------------------------------------------
		public int												Age
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
//----------------------------------------------------------------------------------------------------------------------
		public int												Sex
		{
			get
			{
				return(MSex);
			}
			set
			{
				MSex=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public string											City
		{
			get
			{
				return(MCity);
			}
			set
			{
				MCity=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public string											Country
		{
			get
			{
				return(MCountry);
			}
			set
			{
				MCountry=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CPerson ToPerson()
		{
			CAddress											Address=new CAddress(MCity,MCountry);
			CPerson												Person=new CPerson(MID,MFirstName,MLastName,MAge,(ESex) MSex,Address);

			return(Person);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------