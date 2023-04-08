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
	public class APIOmitNullsController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet]
		public CName Get1()
		{
			// !!! NAME neobsahuje NULL VALUE.
			CName												Name=new CName(0,"Timmy","Anderson",12);

			return(Name);
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet]
		public CName Get2()
		{
			// !!! NAME obsahuje NULL VALUE.
			CName												Name=new CName(0,"Atreyu",null,12);

			return(Name);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------