using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using ViewComponents.Model;
//----------------------------------------------------------------------------------------------------------------------
namespace ViewComponents.Controllers
{
//----------------------------------------------------------------------------------------------------------------------
	public class UsingViewComponentsController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult UsingViaInvokeMethod()
		{
			ViewResult											Result=View("UsingViaInvokeMethod");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult UsingViaTagHelper()
		{
			ViewResult											Result=View("UsingViaTagHelper");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------