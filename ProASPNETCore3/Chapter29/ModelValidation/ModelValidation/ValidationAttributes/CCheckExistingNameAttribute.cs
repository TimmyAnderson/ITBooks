using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc.ModelBinding.Validation;
using Microsoft.Extensions.DependencyInjection;
using ModelValidation.Model;
//----------------------------------------------------------------------------------------------------------------------
namespace ModelValidation.ValidationAttributes
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! CLASS implementuje CUSTOM VALIDATION ATTRIBUTE, ktora robi VALIDATION CLASSES.
	[AttributeUsage(AttributeTargets.Class,AllowMultiple=false,Inherited=false)]
	// !!! CUSTOM VALIDATION ATTRIBUTE MUSI implementovat INTERFACE [IModelValidator].
	public sealed class CCheckExistingNameAttribute : Attribute, IModelValidator
	{
//----------------------------------------------------------------------------------------------------------------------
		private string											MMessage;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CCheckExistingNameAttribute()
		{
			MMessage="NAME already EXISTS !";
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
		// !!! METHOD vykonava VALIDATION viacerych PROPERTIES MODEL OBJECT.
		public IEnumerable<ModelValidationResult> Validate(ModelValidationContext Context)
		{
			List<ModelValidationResult>							Results=new List<ModelValidationResult>();

			if ((Context.Model is CChildAutoValidation)==true)
			{
				CChildAutoValidation							PropertyValue=(CChildAutoValidation) Context.Model;
				IChildAutoValidationProvider					ChildAutoValidationProvider=Context.ActionContext.HttpContext.RequestServices.GetService<IChildAutoValidationProvider>();
				CChildAutoValidation[]							Children=ChildAutoValidationProvider.GetChildren();
				bool											ChildExists=Children.Where(P => P.FirstName==PropertyValue.FirstName && P.LastName==PropertyValue.LastName).Any();

				if (ChildExists==true)
				{
					Results.Add(new ModelValidationResult("",MMessage));
				}
			}

			return(Results);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------