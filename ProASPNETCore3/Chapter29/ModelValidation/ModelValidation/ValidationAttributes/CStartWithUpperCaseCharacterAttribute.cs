using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc.ModelBinding.Validation;
//----------------------------------------------------------------------------------------------------------------------
namespace ModelValidation.ValidationAttributes
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! CLASS implementuje CUSTOM VALIDATION ATTRIBUTE, ktora robi VALIDATION PROPERTIES.
	[AttributeUsage(AttributeTargets.Property,AllowMultiple=false,Inherited=false)]
	// !!! CUSTOM VALIDATION ATTRIBUTE MUSI implementovat INTERFACE [IModelValidator].
	public sealed class CStartWithUpperCaseCharacterAttribute : Attribute, IModelValidator
	{
//----------------------------------------------------------------------------------------------------------------------
		private string											MMessage;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CStartWithUpperCaseCharacterAttribute()
		{
			MMessage="PROPERTY must start with UPPER CASE CHARACTER !";
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public string											Message
		{
			get
			{
				return(MMessage);
			}
			set
			{
				MMessage=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! METHOD vykonava VALIDATION PROPERTY MODEL OBJECT.
		public IEnumerable<ModelValidationResult> Validate(ModelValidationContext Context)
		{
			List<ModelValidationResult>							Results=new List<ModelValidationResult>();

			if ((Context.Model is string)==true)
			{
				string											PropertyValue=(string) Context.Model;

				if (PropertyValue.Length>0)
				{
					if (char.IsUpper(PropertyValue[0])==false)
					{
						Results.Add(new ModelValidationResult("",MMessage));
					}
				}
			}

			return(Results);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------