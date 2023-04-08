using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.JsonPatch;
using CreatingRESTfulWebServices.Database;
using CreatingRESTfulWebServices.Model;
using Microsoft.AspNetCore.Mvc.ModelBinding;
//----------------------------------------------------------------------------------------------------------------------
namespace CreatingRESTfulWebServices.Controllers
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! CONTROLLER implementuje API CONTROLLER.
	[Route("api/APIValidation")]
	public class APIValidationController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly INameProvider							MNameProvider;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public APIValidationController(INameProvider NameProvider)
		{
			MNameProvider=NameProvider;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! Pri INSERT by sa NEMAL zadavat ID, pretoze ten generuje ENTITY FRAMEWORK. V pripade, ze by sa zadaval aj ID, mohlo by dost k OVER-BINDING.
		[HttpPost]
		public IActionResult Post([FromBody] CNameNoID NameNoID)
		{
			// !!! Vykona sa VALIDATION INPUT DATA.
			if (ModelState.IsValid==true)
			{
				CName											Name=new CName(0,NameNoID.FirstName,NameNoID.LastName,NameNoID.Age);
				CName											InsertedName=MNameProvider.AddName(Name);
				IActionResult									Result=Ok(InsertedName);

				return(Result);
			}
			else
			{
				// !!! Do COLLECTION sa ulozia vsetky VALIDATION ERRORS.
				List<CValidationError>							ValidationError=new List<CValidationError>();

				foreach(KeyValuePair<string,ModelStateEntry> KeyValue in ModelState)
				{
					List<string>								Errors=new List<string>();

					foreach(ModelError Error in KeyValue.Value.Errors)
					{
						Errors.Add(Error.ErrorMessage);
					}

					ValidationError.Add(new CValidationError(KeyValue.Key,Errors.ToArray()));
				}

				CValidationErrors								ValidationErrors=new CValidationErrors(ValidationError.ToArray());

				// !!! Vrati sa HTTP STATUS CODE 400.
				IActionResult									Result=BadRequest(ValidationErrors);

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------