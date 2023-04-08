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
    public class PageRemoteValidationModel : PageModel
    {
//----------------------------------------------------------------------------------------------------------------------
		private readonly IChildRemoteValidationRazorPageProvider	MChildProvider;
//----------------------------------------------------------------------------------------------------------------------
		public CChildRemoteValidationRazorPage					MChild;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public PageRemoteValidationModel(IChildRemoteValidationRazorPageProvider ChildProvider)
		{
			MChildProvider=ChildProvider;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[BindProperty]
		public CChildRemoteValidationRazorPage					Child
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
			// !!! Vykona sa kontrola ci MODEL VALIDATION presiel uspesne pre vsetky PROPERTIES.
			if (ModelState.IsValid==true)
			{
				MChildProvider.AddChild(Child);

				IActionResult									Result=RedirectToPage("PageViewRemoteValidationChildren");

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