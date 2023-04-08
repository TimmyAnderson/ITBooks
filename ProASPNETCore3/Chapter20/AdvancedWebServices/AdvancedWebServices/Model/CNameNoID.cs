﻿using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;
//----------------------------------------------------------------------------------------------------------------------
namespace AdvancedWebServices.Model
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CNameNoID
	{
//----------------------------------------------------------------------------------------------------------------------
		private string											MFirstName;
		private string											MLastName;
		private int												MAge;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CNameNoID()
		{
		}
//----------------------------------------------------------------------------------------------------------------------
		public CNameNoID(string FirstName, string LastName, int Age)
		{
			MFirstName=FirstName;
			MLastName=LastName;
			MAge=Age;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! Aplikuje sa VALIDATION ATTRIBUTE.
		[Required]
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
		// !!! Aplikuje sa VALIDATION ATTRIBUTE.
		[Required]
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
		// !!! Aplikuje sa VALIDATION ATTRIBUTE.
		[Required]
		[Range(1,100)]
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
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public override string ToString()
		{
			return($"[{MFirstName}] [{MLastName}] [{MAge}]");
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------