using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.ModelBinding;
using Microsoft.AspNetCore.Mvc.RazorPages;
using ModelValidation.Model;
//----------------------------------------------------------------------------------------------------------------------
namespace ModelValidation.Pages
{
//----------------------------------------------------------------------------------------------------------------------
    public class PageManualValidationModel : PageModel
    {
//----------------------------------------------------------------------------------------------------------------------
		private readonly IChildProvider							MChildProvider;
//----------------------------------------------------------------------------------------------------------------------
		public CChild											MChild;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public PageManualValidationModel(IChildProvider ChildProvider)
		{
			MChildProvider=ChildProvider;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[BindProperty]
		public CChild											Child
		{
			get
			{
				return(MChild);
			}
			set
			{
				MChild=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult OnGet()
		{
			IActionResult										Result=Page();

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult OnPostMyHandler()
		{
			// !!! Vykona sa kontrola, ci MODEL BINDING bol schopny vykonat VALIDATION.
			ModelValidationState								ValidationStateFirstName=ModelState.GetFieldValidationState("Child.FirstName");

			// !!! Vykona sa dodatocna kontrola ci STRING VALUE je NON-EMPTY.
			if (ValidationStateFirstName==ModelValidationState.Invalid || string.IsNullOrEmpty(Child.FirstName)==true)
			{
				// !!! KEY MUSI mat PREFIX obsahujuci nazov PROPERTY 'Child'.
				ModelState.AddModelError("Child.FirstName","Enter your FIRST NAME !");
			}

			// !!! Vykona sa kontrola, ci MODEL BINDING bol schopny vykonat VALIDATION.
			ModelValidationState								ValidationStateLastName=ModelState.GetFieldValidationState("Child.LastName");

			// !!! Vykona sa dodatocna kontrola ci STRING VALUE je NON-EMPTY.
			if (ValidationStateLastName==ModelValidationState.Invalid || string.IsNullOrEmpty(Child.LastName)==true)
			{
				// !!! KEY MUSI mat PREFIX obsahujuci nazov PROPERTY 'Child'.
				ModelState.AddModelError("Child.LastName","Enter your LAST NAME !");
			}

			// !!! Vykona sa kontrola, ci MODEL BINDING bol schopny vykonat VALIDATION. V pripade NUMERIC VALUES sa kontroluje ci INPUT HTML ELEMENT obsahuje NUMBERIC VALUE.
			ModelValidationState								ValidationStateAge=ModelState.GetFieldValidationState("Child.Age");

			// !!! Vykona sa dodatocna kontrola ci NUMBERIC VALUE je KLADNA.
			if (ValidationStateAge==ModelValidationState.Invalid || Child.Age<=0)
			{
				// !!! KEY MUSI mat PREFIX obsahujuci nazov PROPERTY 'Child'.
				ModelState.AddModelError("Child.Age","Enter your AGE !");
			}

			// !!! Vykona sa kontrola, ci MODEL BINDING bol schopny vykonat VALIDATION. V pripade ENUM VALUES sa kontroluje ci INPUT HTML ELEMENT obsahuje niektoru z ENUM VALUES.
			ModelValidationState								ValidationStateSex=ModelState.GetFieldValidationState("Child.Sex");

			// !!! Vykona sa dodatocna kontrola ci ENUM VALUE obsahuje VALID VALUE.
			if (ValidationStateSex==ModelValidationState.Invalid || (Child.Sex!=ESex.Male && Child.Sex!=ESex.Female))
			{
				// !!! KEY MUSI mat PREFIX obsahujuci nazov PROPERTY 'Child'.
				ModelState.AddModelError("Child.Sex","Enter your SEX !");
			}

			// !!! Vykona sa kontrola ci MODEL VALIDATION presiel uspesne pre vsetky PROPERTIES.
			if (ModelState.IsValid==true)
			{
				MChildProvider.AddChild(Child);

				IActionResult									Result=RedirectToPage("PageViewManualValidationChildren");

				return(Result);
			}
			else
			{
				// !!! Prida sa GENERIC VALIDATION ERROR, ktora nie je asociovana so ziadnou PROPERTY.
				ModelState.AddModelError("","Please CORRECT FORM VALUES !");

				// !!! Znova sa zobrazi EDIT VIEW, ktory vsak uz bude mat u INPUT HTML ELEMENTS, ktore nepresli VALIDATION nastaveny CSS CLASS na VALUE 'input-validation-error'. Tuto CSS CLASS je mozne vyuzit na zvyraznenie, ktore INPUT HTML ELEMENTS nepresli VALIDATION.
				PageResult										Result=Page();

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
    }
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------