using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using UsingDependencyInjection.Model;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingDependencyInjection.Controllers
{
//----------------------------------------------------------------------------------------------------------------------
	public class ActionInjectionController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		// !!! PARAMETER 'InterfaceService' bude vytvoreny DEPENDENCY INJECTION MANAGER.
		public IActionResult MyActionMethod([FromServices] IInterfaceService InterfaceService)
		{
			InterfaceService.AddName(new CName(1,"Timmy","Anderson",12));
			InterfaceService.AddName(new CName(2,"Jenny","Thompson",13));
			InterfaceService.AddName(new CName(3,"Josh","Hurt",12));

			CName[]												Model=InterfaceService.GetNames();
			ViewResult											Result=View("Names",Model);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------