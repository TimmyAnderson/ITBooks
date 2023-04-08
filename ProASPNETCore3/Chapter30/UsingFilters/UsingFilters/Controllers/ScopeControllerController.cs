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
	// !!! Vsetky ACTION METHODS POMOCOU CUSTOM FILTER kontroluju ci je vyvolana cez HTTPS PROTOCOL a ak NIE, tak hodia ERROR.
	[CRequireHttps]
	public class ScopeControllerController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
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