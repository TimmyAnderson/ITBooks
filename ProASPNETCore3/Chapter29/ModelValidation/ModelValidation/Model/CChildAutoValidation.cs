using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;
using ModelValidation.ValidationAttributes;
//----------------------------------------------------------------------------------------------------------------------
namespace ModelValidation.Model
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! Aplikuje sa CUSTOM VALIDATION ATTRIBUTE.
	[CCheckExistingName(Message="FIRST NAME and LAST NAME you entered ALREADY EXISTS in DB !")]
	public sealed class CChildAutoValidation
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
		public CChildAutoValidation()
		{
		}
//----------------------------------------------------------------------------------------------------------------------
		public CChildAutoValidation(int ID, string FirstName, string LastName, int Age, ESex Sex)
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
		// !!! Aplikuje sa CUSTOM VALIDATION ATTRIBUTE.
		[CStartWithUpperCaseCharacter(Message="FIRST NAME must start with UPPER CASE CHARACTER !")]
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
		// !!! Aplikuje sa CUSTOM VALIDATION ATTRIBUTE.
		[CStartWithUpperCaseCharacter(Message="LAST NAME must start with UPPER CASE CHARACTER !")]
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