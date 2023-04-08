using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
//----------------------------------------------------------------------------------------------------------------------
namespace ViewComponents.Controllers
{
//----------------------------------------------------------------------------------------------------------------------
	public class ReturnValueViewComponentsController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult ReturnPartialView1()
		{
			ViewResult											Result=View("ReturnValuePartialView1");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult ReturnPartialView2()
		{
			ViewResult											Result=View("ReturnValuePartialView2");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult ReturnPartialView3()
		{
			ViewResult											Result=View("ReturnValuePartialView3");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult ReturnEncodedHtmlString()
		{
			ViewResult											Result=View("ReturnValueEncodedHtmlString");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult ReturnNotEncodedHtmlString()
		{
			ViewResult											Result=View("ReturnValueNotEncodedHtmlString");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------