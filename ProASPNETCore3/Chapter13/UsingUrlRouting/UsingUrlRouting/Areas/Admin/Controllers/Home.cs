using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using UsingUrlRouting.Areas.Admin.Model;
using Microsoft.AspNetCore.Mvc;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingUrlRouting.Areas.Controllers
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! Pre CONTROLLERS, ak maju byt asociovane s konkrentnou AREA je NUTNE na CONTROLLER CLASSES aplikovat ATTRIBUTE [AreaAttribute].
	[Area("Admin")]
	public class Home : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult View1()
		{
			CAdmin[]											Admins=new CAdmin[]{new CAdmin("Timmy","Anderson",12),new CAdmin("Jenny","Thompson",13)};

			return(View("Index",Admins));
		}
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult View2()
		{
			CAdmin[]											Admins=new CAdmin[]{new CAdmin("Jenny","Thompson",13),new CAdmin("Timmy","Anderson",12)};

			return(View("Index",Admins));
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------