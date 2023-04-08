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
	public sealed class ClientSideCheckingController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly IChildAutoValidationProvider			MChildProvider;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public ClientSideCheckingController(IChildAutoValidationProvider ChildProvider)
		{
			MChildProvider=ChildProvider;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public ViewResult EditChild()
		{
			ViewResult											Result=View("EditChildClientSideValidation");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpPost]
		public IActionResult EditChildCallback(CChildAutoValidation Child)
		{
			// !!! Vykona sa kontrola ci MODEL VALIDATION presiel uspesne pre vsetky PROPERTIES.
			if (ModelState.IsValid==true)
			{
				MChildProvider.AddChild(Child);

				IActionResult									Result=View("ViewAutoValidationChildren",MChildProvider.GetChildren());

				return(Result);
			}
			else
			{
				// !!! Prida sa GENERIC VALIDATION ERROR, ktora nie je asociovana so ziadnou PROPERTY.
				ModelState.AddModelError("","Please CORRECT FORM VALUES !");

				// !!! Znova sa zobrazi EDIT VIEW, ktory vsak uz bude mat u INPUT HTML ELEMENTS, ktore nepresli VALIDATION nastaveny CSS CLASS na VALUE 'input-validation-error'. Tuto CSS CLASS je mozne vyuzit na zvyraznenie, ktore INPUT HTML ELEMENTS nepresli VALIDATION.
				ViewResult										Result=View("EditChildClientSideValidation");

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------