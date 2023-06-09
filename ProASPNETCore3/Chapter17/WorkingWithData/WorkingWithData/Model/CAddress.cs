﻿using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;
//----------------------------------------------------------------------------------------------------------------------
namespace WorkingWithData.Model
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CAddress
	{
//----------------------------------------------------------------------------------------------------------------------
		private string											MCity;
		private string											MCountry;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CAddress()
		{
		}
//----------------------------------------------------------------------------------------------------------------------
		public CAddress(string City, string Country)
		{
			MCity=City;
			MCountry=Country;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[Required(ErrorMessage="Please enter CITY !")]
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
		[Required(ErrorMessage="Please enter COUNTRY !")]
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
		public override string ToString()
		{
			return($"[{MCity}] [{MCountry}]");
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------