using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using UsingFilters.CustomFilters;
using UsingFilters.Model;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingFilters.Controllers
{
//----------------------------------------------------------------------------------------------------------------------
	public class FilterNoFilterController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		// !!! ACTION METHOD kontroluje ci je vyvolana cez HTTPS PROTOCOL a ak NIE, tak hodi ERROR.
		public IActionResult NoFilter()
		{
			if (Request.IsHttps==true)
			{
				CResultMessage									Model=new CResultMessage("ACTION METHOD is EXECUTED via HTTPS !");
				ViewResult										Result=View("ResultMessage",Model);

				return(Result);
			}
			else
			{
				// !!! Ak sa ACTION METHOD volala cez HTTP, tak sa hodi ERROR.
				StatusCodeResult								Result=new StatusCodeResult(403);

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! ACTION METHOD POMOCOU CUSTOM FILTER kontroluje ci je vyvolana cez HTTPS PROTOCOL a ak NIE, tak hodi ERROR.
		[CRequireHttps]
		public IActionResult Filter()
		{
			CResultMessage										Model=new CResultMessage("ACTION METHOD is EXECUTED via HTTPS !");
			ViewResult											Result=View("ResultMessage",Model);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------