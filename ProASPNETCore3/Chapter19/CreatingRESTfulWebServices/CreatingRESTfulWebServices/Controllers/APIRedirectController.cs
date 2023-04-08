using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.JsonPatch;
using CreatingRESTfulWebServices.Database;
using CreatingRESTfulWebServices.Model;
//----------------------------------------------------------------------------------------------------------------------
namespace CreatingRESTfulWebServices.Controllers
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! CONTROLLER implementuje API CONTROLLER.
	[Route("api/{Controller}/{Action}")]
	public class APIRedirectController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet]
		public IActionResult TestRedirect()
		{
			// !!! Vykona sa REDIRECTION na zadanu URL.
			IActionResult										Result=Redirect("/api/APIControllerName/1");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet]
		public IActionResult TestRedirectToAction()
		{
			// !!! Vykona sa REDIRECTION na zadany CONTROLLER a ACTION METHOD.
			IActionResult										Result=RedirectToAction("Get","APIName",new {ID=1});

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet]
		public IActionResult TestRedirectToRoute()
		{
			// !!! Vykona sa REDIRECTION podla definovanej ROUTE.
			IActionResult										Result=RedirectToRoute(new {Controller="APIName",Action="Get",ID=1});

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------