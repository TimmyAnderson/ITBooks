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
	// !!! Na CONTROLLER sa aplikuje ATTRIBUTE [ApiControllerAttribute], ktory modifikuje cinnost CONTROLLER.
	[ApiController]
	[Route("api/APIControllerAttribute")]
	public class APIControllerAttributeController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly INameProvider							MNameProvider;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public APIControllerAttributeController(INameProvider NameProvider)
		{
			MNameProvider=NameProvider;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! Ak je na CONTROLLER aplikovany ATTRIBUTE [ApiControllerAttribute], potom NIE JE NUTNE oznacit PARAMETER pomocou ATTRIBUTE [FromBodyAttribute].
		[HttpPost]
		public IActionResult Post(CNameNoID NameNoID)
		{
			// !!!!! Ak je na CONTROLLER aplikovany ATTRIBUTE [ApiControllerAttribute], potom NIE JE NUTNE vykonavat VALIDATION, lebo ta sa vykonava AUTOMATICKY.
			CName												Name=new CName(0,NameNoID.FirstName,NameNoID.LastName,NameNoID.Age);
			CName												InsertedName=MNameProvider.AddName(Name);
			IActionResult										Result=Ok(InsertedName);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------