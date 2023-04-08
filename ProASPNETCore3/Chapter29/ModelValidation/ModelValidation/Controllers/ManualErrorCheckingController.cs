using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.ModelBinding;
using ModelValidation.Model;
//----------------------------------------------------------------------------------------------------------------------
namespace ModelValidation.Controllers
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class ManualErrorCheckingController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly IChildProvider							MChildProvider;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public ManualErrorCheckingController(IChildProvider ChildProvider)
		{
			MChildProvider=ChildProvider;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public ViewResult EditChild()
		{
			ViewResult											Result=View("EditChildManualValidation");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpPost]
		public IActionResult EditChildCallback(CChild Child)
		{
			// !!! Vykona sa kontrola, ci MODEL BINDING bol schopny vykonat VALIDATION.
			ModelValidationState								ValidationStateFirstName=ModelState.GetFieldValidationState("FirstName");

			// !!! Vykona sa dodatocna kontrola ci STRING VALUE je NON-EMPTY.
			if (ValidationStateFirstName==ModelValidationState.Invalid || string.IsNullOrEmpty(Child.FirstName)==true)
			{
				ModelState.AddModelError(nameof(Child.FirstName),"Enter your FIRST NAME !");
			}

			// !!! Vykona sa kontrola, ci MODEL BINDING bol schopny vykonat VALIDATION.
			ModelValidationState								ValidationStateLastName=ModelState.GetFieldValidationState("LastName");

			// !!! Vykona sa dodatocna kontrola ci STRING VALUE je NON-EMPTY.
			if (ValidationStateLastName==ModelValidationState.Invalid || string.IsNullOrEmpty(Child.LastName)==true)
			{
				ModelState.AddModelError(nameof(Child.LastName),"Enter your LAST NAME !");
			}

			// !!! Vykona sa kontrola, ci MODEL BINDING bol schopny vykonat VALIDATION. V pripade NUMERIC VALUES sa kontroluje ci INPUT HTML ELEMENT obsahuje NUMBERIC VALUE.
			ModelValidationState								ValidationStateAge=ModelState.GetFieldValidationState("Age");

			// !!! Vykona sa dodatocna kontrola ci NUMBERIC VALUE je KLADNA.
			if (ValidationStateAge==ModelValidationState.Invalid || Child.Age<=0)
			{
				ModelState.AddModelError(nameof(Child.Age),"Enter your AGE !");
			}

			// !!! Vykona sa kontrola, ci MODEL BINDING bol schopny vykonat VALIDATION. V pripade ENUM VALUES sa kontroluje ci INPUT HTML ELEMENT obsahuje niektoru z ENUM VALUES.
			ModelValidationState								ValidationStateSex=ModelState.GetFieldValidationState("Sex");

			// !!! Vykona sa dodatocna kontrola ci ENUM VALUE obsahuje VALID VALUE.
			if (ValidationStateSex==ModelValidationState.Invalid || (Child.Sex!=ESex.Male && Child.Sex!=ESex.Female))
			{
				ModelState.AddModelError(nameof(Child.Sex),"Enter your SEX !");
			}

			// !!! Vykona sa kontrola ci MODEL VALIDATION presiel uspesne pre vsetky PROPERTIES.
			if (ModelState.IsValid==true)
			{
				MChildProvider.AddChild(Child);

				IActionResult									Result=View("ViewManualValidationChildren",MChildProvider.GetChildren());

				return(Result);
			}
			else
			{
				// !!! Prida sa GENERIC VALIDATION ERROR, ktora nie je asociovana so ziadnou PROPERTY.
				ModelState.AddModelError("","Please CORRECT FORM VALUES !");

				// !!! Znova sa zobrazi EDIT VIEW, ktory vsak uz bude mat u INPUT HTML ELEMENTS, ktore nepresli VALIDATION nastaveny CSS CLASS na VALUE 'input-validation-error'. Tuto CSS CLASS je mozne vyuzit na zvyraznenie, ktore INPUT HTML ELEMENTS nepresli VALIDATION.
				ViewResult										Result=View("EditChildManualValidation");

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------