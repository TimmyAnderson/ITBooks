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
	public sealed class RemoteErrorCheckingController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly IChildRemoteValidationProvider			MChildProvider;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public RemoteErrorCheckingController(IChildRemoteValidationProvider ChildProvider)
		{
			MChildProvider=ChildProvider;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public ViewResult EditChild()
		{
			ViewResult											Result=View("EditChildRemoteSideValidation");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpPost]
		public IActionResult EditChildCallback(CChildRemoteValidation Child)
		{
			// !!! Vykona sa kontrola ci MODEL VALIDATION presiel uspesne pre vsetky PROPERTIES.
			if (ModelState.IsValid==true)
			{
				MChildProvider.AddChild(Child);

				IActionResult									Result=View("ViewRemoteValidationChildren",MChildProvider.GetChildren());

				return(Result);
			}
			else
			{
				// !!! Prida sa GENERIC VALIDATION ERROR, ktora nie je asociovana so ziadnou PROPERTY.
				ModelState.AddModelError("","Please CORRECT FORM VALUES !");

				// !!! Znova sa zobrazi EDIT VIEW, ktory vsak uz bude mat u INPUT HTML ELEMENTS, ktore nepresli VALIDATION nastaveny CSS CLASS na VALUE 'input-validation-error'. Tuto CSS CLASS je mozne vyuzit na zvyraznenie, ktore INPUT HTML ELEMENTS nepresli VALIDATION.
				ViewResult										Result=View("EditChildRemoteSideValidation");

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! PARAMETER SERVER SIDE VALIDATION METHOD MUSI mat rovnaky NAME ako nazov PROPERTY, ktora ma byt VALIDATED.
		// !!! PARAMETER SERVER SIDE VALIDATION METHOD by MAL byt TYPE [string]. To preto, lebo ak by napriklad sa jednalo o PROPERTY TYPE [int] a USER by do prislusneho INPUT HTML ELEMENT zadal NON-INTEGER VALUE, tak by sa SERVER SIDE VALIDATION METHOD VOBEC NEZAVOLALA. Preto sa odporuca ako PARAMETER TYPE VZDY pouzivat TYPE [string].
		// !!! RETURN VALUE SERVER SIDE VALIDATION METHOD MUSI byt TYPE [JsonResult], kde v pripade, ze VALIDATION presla uspesne, tak je potrebne vratit VALUE 'true' a v pripade, ze VALIDATION ZLYHALA, vratit MESSAGE obsahujucu popis ERROR.
		public JsonResult ValidateFirstName(string FirstName)
		{
			string												Value=FirstName;

			if (string.IsNullOrEmpty(Value)==false)
			{
				if (Value.Length>0)
				{
					if (char.IsUpper(Value[0])==true)
					{
						return(new JsonResult(true));
					}
				}
			}

			return(new JsonResult("WARNING - FIRST NAME must start with UPPER CASE CHARACTER !"));
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! PARAMETER SERVER SIDE VALIDATION METHOD MUSI mat rovnaky NAME ako nazov PROPERTY, ktora ma byt VALIDATED.
		// !!! PARAMETER SERVER SIDE VALIDATION METHOD by MAL byt TYPE [string]. To preto, lebo ak by napriklad sa jednalo o PROPERTY TYPE [int] a USER by do prislusneho INPUT HTML ELEMENT zadal NON-INTEGER VALUE, tak by sa SERVER SIDE VALIDATION METHOD VOBEC NEZAVOLALA. Preto sa odporuca ako PARAMETER TYPE VZDY pouzivat TYPE [string].
		// !!! RETURN VALUE SERVER SIDE VALIDATION METHOD MUSI byt TYPE [JsonResult], kde v pripade, ze VALIDATION presla uspesne, tak je potrebne vratit VALUE 'true' a v pripade, ze VALIDATION ZLYHALA, vratit MESSAGE obsahujucu popis ERROR.
		public JsonResult ValidateLastName(string LastName)
		{
			string												Value=LastName;

			if (string.IsNullOrEmpty(Value)==false)
			{
				if (Value.Length>0)
				{
					if (char.IsUpper(Value[0])==true)
					{
						return(new JsonResult(true));
					}
				}
			}

			return(new JsonResult("WARNING - LAST NAME must start with UPPER CASE CHARACTER !"));
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------