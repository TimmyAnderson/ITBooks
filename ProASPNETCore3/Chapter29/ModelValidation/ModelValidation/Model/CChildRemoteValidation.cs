using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using ModelValidation.ValidationAttributes;
//----------------------------------------------------------------------------------------------------------------------
namespace ModelValidation.Model
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CChildRemoteValidation
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MID;
		private string											MFirstName;
		private string											MLastName;
		private int												MAge;
		private ESex											MSex;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CChildRemoteValidation()
		{
		}
//----------------------------------------------------------------------------------------------------------------------
		public CChildRemoteValidation(int ID, string FirstName, string LastName, int Age, ESex Sex)
		{
			MID=ID;
			MFirstName=FirstName;
			MLastName=LastName;
			MAge=Age;
			MSex=Sex;
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
		// !!! Ak sa nedefinuje CUSTOM VALIDATION ERROR MESSAGE, je treba aplikovat ATTRIBUTE [DisplayAttribute].
		[Required]
		[Display(Name="FirstName")]
		// !!! Pouzije sa REMOTE VALIDATION.
		[Remote("ValidateFirstName","RemoteErrorChecking")]
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
		[Required(ErrorMessage="Please enter LAST NAME !!!")]
		// !!! Pouzije sa REMOTE VALIDATION.
		[Remote("ValidateLastName","RemoteErrorChecking")]
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
		[Required(ErrorMessage="Please enter AGE !!!")]
		[Range(0,int.MaxValue,ErrorMessage="AGE VALUE MUST be POSITIVE !")]
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
		[Required(ErrorMessage="Please enter SEX !!!")]
		public ESex												Sex
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
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public override string ToString()
		{
			return($"[{MFirstName}] [{MLastName}] [{MAge}] [{MSex}]");
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------